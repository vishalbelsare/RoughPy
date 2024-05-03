// Copyright (c) 2023 the RoughPy Developers. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
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
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

//
// Created by user on 11/10/23.
//

#include "devices/buffer.h"
#include "devices/device_object_base.h"
#include "devices/event.h"
#include "devices/type.h"

using namespace rpy;
using namespace rpy::devices;

BufferMode BufferInterface::mode() const { return BufferMode::Read; }

TypeInfo BufferInterface::type_info() const noexcept
{
    RPY_DBG_ASSERT(p_type != nullptr);
    return p_type->type_info();
}
dimn_t BufferInterface::size() const { return 0; }
dimn_t BufferInterface::bytes() const { return size() * type_info().bytes; }
Event BufferInterface::to_device(
        Buffer& dst,
        const Device& device,
        Queue& queue
) const
{
    RPY_THROW(std::runtime_error, "unable to migrate data to this device");
}

Buffer BufferInterface::map_mut(dimn_t size, dimn_t offset) { return {}; }
Buffer BufferInterface::map(dimn_t size, dimn_t offset) const { return {}; }

Buffer BufferInterface::slice(dimn_t size, dimn_t offset) const
{
    return Buffer();
}
Buffer BufferInterface::mut_slice(dimn_t size, dimn_t offset)
{
    return Buffer();
}

void BufferInterface::unmap(BufferInterface& ptr) const noexcept {}

Buffer BufferInterface::memory_owner() const noexcept
{
    // This const-cast is fine, because we are creating a new counted reference
    // to *this.
    return Buffer(const_cast<BufferInterface*>(this));
}
