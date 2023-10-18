// Copyright (c) 2023 the RoughPy Developers. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors
// may be used to endorse or promote products derived from this software without
// specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
// USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

//
// Created by user on 25/02/23.
//

#ifndef ROUGHPY_SCALARS_SCALARS_PREDEF_H
#define ROUGHPY_SCALARS_SCALARS_PREDEF_H

#include <roughpy/core/helpers.h>
#include <roughpy/core/macros.h>
#include <roughpy/core/traits.h>
#include <roughpy/core/types.h>
#include <roughpy/device/core.h>

#include <functional>

namespace rpy {
namespace scalars {

using ScalarTypeCode = devices::TypeCode;
using BasicScalarInfo = devices::TypeInfo;

/// Marker for signed size type (ptrdiff_t)
struct signed_size_type_marker {
};

/// Marker for unsigned size type (size_t)
struct unsigned_size_type_marker {
};

/**
 * @brief A collection of basic information for identifying a scalar type.
 */
struct ScalarTypeInfo {
    string name;
    string id;
    size_t n_bytes;
    size_t alignment;
    BasicScalarInfo basic_info;
    devices::DeviceInfo device;
};

// Forward declarations

class ScalarType;

class ScalarInterface;

class ScalarPointer;

class Scalar;

class ScalarArray;

class OwnedScalarArray;

class KeyScalarArray;

class ScalarStream;

class RandomGenerator;

class BlasInterface;

//template <typename T>
//inline remove_cv_ref_t<T> scalar_cast(const Scalar& arg);
//
using conversion_function
        = std::function<void(ScalarPointer, ScalarPointer, dimn_t)>;

constexpr bool
operator==(const BasicScalarInfo& lhs, const BasicScalarInfo& rhs) noexcept
{
    return lhs.code == rhs.code && lhs.bits == rhs.bits
            && lhs.lanes == rhs.lanes;
}

/**
 * @brief Register a new type with the scalar type system
 * @param type Pointer to newly created ScalarType
 *
 *
 */
RPY_EXPORT void register_type(const ScalarType* type);

/**
 * @brief Get a type registered with the scalar type system
 * @param id Id string of type to be retrieved
 * @return pointer to ScalarType representing id
 */
RPY_EXPORT const ScalarType* get_type(const string& id);

RPY_EXPORT const ScalarType*
get_type(const string& id, const devices::DeviceInfo& device);

/**
 * @brief Get a list of all registered ScalarTypes
 * @return vector of ScalarType pointers.
 */
RPY_NO_DISCARD RPY_EXPORT std::vector<const ScalarType*> list_types();

RPY_NO_DISCARD RPY_EXPORT const ScalarTypeInfo& get_scalar_info(string_view id);

RPY_NO_DISCARD RPY_EXPORT const std::string&
id_from_basic_info(const BasicScalarInfo& info);

RPY_NO_DISCARD RPY_EXPORT const conversion_function&
get_conversion(const string& src_id, const string& dst_id);

RPY_EXPORT void register_conversion(
        const string& src_id,
        const string& dst_id,
        conversion_function converter
);

}// namespace scalars
}// namespace rpy

#endif// ROUGHPY_SCALARS_SCALARS_PREDEF_H
