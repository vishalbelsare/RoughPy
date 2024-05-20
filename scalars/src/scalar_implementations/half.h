//
// Created by sam on 3/26/24.
//

#ifndef HALF_H
#define HALF_H

#include <roughpy/devices/core.h>

#include <Eigen/Core>

namespace rpy {
namespace scalars {

using Half = Eigen::half;
}

namespace devices { namespace dtl {

template <>
struct type_code_of_impl<scalars::Half>
{
    static constexpr TypeCode value = TypeCode::Float;
};

template <>
struct type_id_of_impl<scalars::Half>
{
    static constexpr string_view value = "f16";
};


}}



}// namespace rpy

#endif// HALF_H
