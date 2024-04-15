#include "generic_kernel_MV_CV.h"

#include <roughpy/core/container/unordered_map.h>
#include <roughpy/core/ranges.h>

#include "basis.h"

using namespace rpy;
using namespace rpy::algebra;

namespace {

using KeyScalarMap = containers::
        FlatHashMap<BasisKey, scalars::Scalar, KeyHash, KeyEquals>;

template <typename IndexAndKeyRange>
void write_with_sparse(
        KeyScalarMap& mapped,
        IndexAndKeyRange&& range,
        const scalars::ScalarArray& scalars
)
{
    for (auto [i, k] : range) { mapped[k] += scalars[i]; }
}

template <typename IndexAndKeyRange>
void preload_map(
        KeyScalarMap& mapped,
        IndexAndKeyRange&& range,
        const scalars::ScalarArray& scalars
)
{
    for (auto [i, k] : range) { mapped[k] = scalars[i]; }
}

bool filter_pairs(typename KeyScalarMap::reference val) noexcept
{
    return val.second.is_zero();
}

inline void write_sparse_result(VectorData& data, KeyScalarMap& mapped)
{
    const auto mapped_size = mapped.size();
    if (data.capacity() < mapped_size) { data.reserve(mapped_size); }

    auto keys = data.mut_keys().mut_view();
    auto scalars = data.mut_scalars().mut_view();

    dimn_t count = 0;
    for (auto&& [k, v] : mapped | views::filter(filter_pairs) | views::move) {
        keys[count] = std::move(k);
        scalars[count] = v;
        ++count;
    }

    data.set_size(count);
}

}// namespace

void rpy::algebra::dtl::GenericKernel<
        rpy::algebra::dtl::MutableVectorArg,
        rpy::algebra::dtl::ConstVectorArg>::
        eval_sparse_sparse(VectorData& out, const VectorData& arg) const
{
    const auto scalars_in = arg.scalars().view();
    const auto keys_in = arg.keys().view();

    KeyScalarMap tmp_map;
    {
        const auto keys_out = out.keys().view();
        const auto scalars_out = out.scalars().view();

        auto out_key_view = keys_out.as_slice();
        preload_map(tmp_map, views::enumerate(out_key_view), scalars_out);

        auto in_key_view = keys_in.as_slice();
        write_with_sparse(tmp_map, views::enumerate(in_key_view), scalars_in);
    }

    write_sparse_result(out, tmp_map);
}
void rpy::algebra::dtl::GenericKernel<
        rpy::algebra::dtl::MutableVectorArg,
        rpy::algebra::dtl::ConstVectorArg>::
        eval_sparse_dense(VectorData& out, const VectorData& arg) const
{
    const auto size = arg.size();

    const auto scalars_in = arg.scalars().view();

    KeyScalarMap tmp_map;
    {
        // We need to make sure the scalar views are unmapped before the writing
        // happens later
        const auto out_keys = out.keys().view();
        const auto out_scalars = out.scalars().view();

        auto key_view = out_keys.as_slice();
        preload_map(tmp_map, views::enumerate(key_view), out_scalars);

        write_with_sparse(
                tmp_map,
                views::ints(dimn_t(0), size)
                        | views::transform([basis = p_basis](dimn_t idx) {
                              return std::make_tuple(idx, basis->to_key(idx));
                          }),
                scalars_in
        );
    }

    write_sparse_result(out, tmp_map);
}
void rpy::algebra::dtl::GenericKernel<
        rpy::algebra::dtl::MutableVectorArg,
        rpy::algebra::dtl::ConstVectorArg>::
        eval_dense_sparse(VectorData& out, const VectorData& arg) const
{
    RPY_CHECK(p_basis->is_ordered());

    const auto size = arg.size();
    const auto keys_in = arg.keys().view();
    const auto scalars_in = arg.scalars().view();

    RPY_DBG_ASSERT(size > 0);
    const auto max_size
            = p_basis->dense_dimension(p_basis->to_index(keys_in[size - 1]));

    out.resize(max_size);

    auto scalars_out = out.mut_scalars().mut_view();
    for (dimn_t i = 0; i < size; ++i) {
        auto tmp = scalars_out[p_basis->to_index(keys_in[i])];
        m_func(tmp, scalars_in[i]);
    }
}
void rpy::algebra::dtl::GenericKernel<
        rpy::algebra::dtl::MutableVectorArg,
        rpy::algebra::dtl::ConstVectorArg>::
        eval_dense_dense(VectorData& out, const VectorData& arg) const
{
    const auto size = std::min(out.size(), arg.size());
    auto scalars_out = out.mut_scalars().mut_view();
    const auto scalars_in = out.scalars().view();

    for (dimn_t i = 0; i < size; ++i) {
        auto tmp = scalars_out[i];
        m_func(tmp, scalars_in[i]);
    }
}

void rpy::algebra::dtl::GenericKernel<
        rpy::algebra::dtl::MutableVectorArg,
        rpy::algebra::dtl::ConstVectorArg>::
operator()(VectorData& out, const VectorData& arg) const
{
    switch (get_sparse_dense_config(out, arg)) {
        case 0b00: eval_sparse_sparse(out, arg); break;
        case 0b01: eval_sparse_dense(out, arg); break;
        case 0b10: eval_dense_sparse(out, arg); break;
        case 0b11: eval_dense_dense(out, arg); break;
        default: break;
    }
}
