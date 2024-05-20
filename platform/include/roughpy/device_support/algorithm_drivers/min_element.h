#ifndef ROUGHPY_DEVICE_SUPPORT_MIN_ELEMENT_H_
#define ROUGHPY_DEVICE_SUPPORT_MIN_ELEMENT_H_

#include "algorithm_base.h"
#include <roughpy/core/ranges.h>
#include <roughpy/core/traits.h>

namespace rpy {
namespace devices {

namespace __min_element {

template <typename S, typename T, bool Cond>
struct Func : dtl::AlgorithmFunctionBase<S, T, Cond> {
    void operator()(const Buffer& buffer, Reference out) const
    {
        auto buffer_view = buffer.map();
        auto buffer_slice = buffer_view.as_slice<S>();
        out.value<S>() = static_cast<S>(
                *std::min_element(buffer_slice.begin(), buffer_slice.end())
        );
    }
};

template <typename S, typename T>
struct Func<S, T, false> : dtl::AlgorithmFunctionBase<S, T, false> {
    void operator()(const Buffer&, Reference) const
    {
        RPY_THROW(std::runtime_error, "bad types");
    }
};

template <typename S, typename T>
using func = Func<S, T, is_less_comparable_v<S> && is_convertible_v<S, T>>;

}// namespace __min_element

template <typename S, typename T>
inline constexpr __min_element::func<S, T> min_element_func{};

}// namespace devices
}// namespace rpy

#endif// ROUGHPY_DEVICE_SUPPORT_MIN_ELEMENT_H_
