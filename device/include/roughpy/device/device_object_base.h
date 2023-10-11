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

#ifndef ROUGHPY_DEVICE_DEVICE_OBJECT_BASE_H_
#define ROUGHPY_DEVICE_DEVICE_OBJECT_BASE_H_
#include "core.h"

#include <roughpy/core/macros.h>
#include <roughpy/core/traits.h>
#include <roughpy/core/types.h>

namespace rpy {
namespace device {
namespace dtl {

class RPY_EXPORT InterfaceBase
{
public:
    virtual ~InterfaceBase();

    RPY_NO_DISCARD virtual void* clone(void* content) const;

    virtual void clear(void* content) const;
};

template <typename Interface, typename Derived>
class ObjectBase
{
    static_assert(
            is_base_of<InterfaceBase, Interface>::value,
            "Interface must be derived from InterfaceBase"
    );

    using interface_type = Interface;

    const interface_type* p_interface;
    void* p_content;

public:
    ObjectBase() : p_content(nullptr), p_interface(nullptr) {}

    explicit ObjectBase(
            const interface_type* interface,
            void* content = nullptr
    )
        : p_interface(interface),
          p_content(content)
    {}

    RPY_NO_DISCARD void* content() const noexcept { return p_content; }
    RPY_NO_DISCARD const interface_type* interface() const noexcept
    {
        return p_interface;
    }

    RPY_NO_DISCARD Derived clone() const;
};

template <typename Interface, typename Derived>
Derived ObjectBase<Interface, Derived>::clone() const
{
    RPY_CHECK(p_interface != nullptr);
    return Derived(p_interface, p_interface->clone(p_content));
}

}// namespace dtl
}// namespace device
}// namespace rpy

#endif // ROUGHPY_DEVICE_DEVICE_OBJECT_BASE_H_
