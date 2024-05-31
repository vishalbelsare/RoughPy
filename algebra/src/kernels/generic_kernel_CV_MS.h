//
// Created by sam on 15/04/24.
//

#ifndef GENERIC_KERNEL_VS_H
#define GENERIC_KERNEL_VS_H

#include "arg_data.h"
#include "argument_specs.h"
#include "common.h"
#include "generic_kernel.h"

#include <functional>

namespace rpy {
namespace algebra {
namespace dtl {

template <>
class GenericKernel<ConstVectorArg, MutableScalarArg>
{

    GenericUnaryFunction m_func;
    const Basis* p_basis;

public:
    explicit GenericKernel(GenericUnaryFunction&& arg, const Basis* basis)
        : m_func(std::move(arg)),
          p_basis(basis)
    {}

    void operator()(const VectorData& data, scalars::ScalarRef scalar) const;
};

}// namespace dtl
}// namespace algebra
}// namespace rpy

#endif// GENERIC_KERNEL_VS_H
