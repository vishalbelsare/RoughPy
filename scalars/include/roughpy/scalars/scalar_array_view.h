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

#ifndef ROUGHPY_SCALARS_SCALAR_ARRAY_VIEW_H_
#define ROUGHPY_SCALARS_SCALAR_ARRAY_VIEW_H_

#include "packed_scalar_type_ptr.h"
#include "scalar_array.h"
#include "scalars_fwd.h"

#include <roughpy/core/types.h>
#include <roughpy/platform/devices/memory_view.h>

namespace rpy { namespace scalars {


class ROUGHPY_SCALARS_EXPORT ScalarArrayView {
    friend class ScalarArray;

    using type_pointer = PackedScalarTypePointer<dtl::ScalarArrayStorageModel>;

    devices::MemoryView m_view;
    type_pointer p_type_and_mode;
    dimn_t m_size;

    // Private constructor
    explicit ScalarArrayView(ScalarArray& array);

    ScalarArrayView(devices::MemoryView view, type_pointer type, dimn_t size)
        : m_view(view),
          p_type_and_mode(type),
          m_size(size) {}

public:

    RPY_NO_DISCARD const devices::MemoryView& memory_view() const noexcept
    {
        return m_view;
    }

    RPY_NO_DISCARD optional<const ScalarType*> type() const noexcept;

    RPY_NO_DISCARD dimn_t size() const noexcept { return m_size; }

    RPY_NO_DISCARD bool empty() const noexcept { return m_size == 0; }

    const void* pointer() const noexcept { return m_view.raw_ptr(); }

    RPY_NO_DISCARD
    Scalar operator[](dimn_t i) const noexcept;

    RPY_NO_DISCARD
    ScalarArrayView operator[](SliceIndex i) const;

    template <typename T>
    RPY_NO_DISCARD Slice<const T> as_slice() const
    {
        return {m_view.raw_ptr(), m_size};
    }
};


}}

#endif // ROUGHPY_SCALARS_SCALAR_ARRAY_VIEW_H_
