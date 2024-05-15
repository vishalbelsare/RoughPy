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
#include "devices/device_handle.h"

#include "devices/core.h"
#include "devices/event.h"
#include "devices/queue.h"

#include "devices/host/host_buffer.h"

#include <roughpy/core/errors.h>
#include <roughpy/core/macros.h>

using namespace rpy;
using namespace rpy::devices;

namespace rpy {
namespace devices {
namespace dtl {

template class RPY_DLL_EXPORT ObjectBase<BufferInterface, Buffer>;
}
}// namespace devices
}// namespace rpy

Buffer::Buffer(
        rpy::devices::Device device,
        void* ptr,
        rpy::dimn_t size,
        rpy::devices::TypeInfo type
)
{
    Buffer tmp(ptr, size, type);
    tmp.to_device(*this, device);
}

Buffer::Buffer(
        rpy::devices::Device device,
        const void* ptr,
        rpy::dimn_t size,
        rpy::devices::TypeInfo type
)
{
    Buffer tmp(ptr, size, type);
    tmp.to_device(*this, device);
}

Buffer::Buffer(void* ptr, dimn_t size, TypeInfo info)
    : base_t(new CPUBuffer(ptr, size, info))
{}

Buffer::Buffer(const void* ptr, dimn_t size, TypeInfo info)
    : base_t(new CPUBuffer(ptr, size, info))
{}

Buffer::Buffer(Device device, dimn_t size, TypeInfo type)
{
    *this = device->alloc(type, size);
}

Buffer::Buffer(rpy::dimn_t size, rpy::devices::TypeInfo type)
    : base_t(new CPUBuffer(size, type))
{}

Buffer::Buffer(const Type* tp, dimn_t size) : base_t(new CPUBuffer(tp, size)) {}
Buffer::Buffer(const Type* tp, void* ptr, dimn_t size)
    : base_t(new CPUBuffer(tp, ptr, size))
{}
Buffer::Buffer(const Type* tp, const void* ptr, dimn_t size)
    : base_t(new CPUBuffer(tp, ptr, size))
{}

Buffer::Buffer(const Type* tp, dimn_t size, Device device)
    : Buffer(device->alloc(tp, size))
{}
Buffer::Buffer(const Type* tp, void* ptr, dimn_t size, Device device)
    : base_t(nullptr)
{
    if (device == nullptr || device->is_host()) {
        construct_inplace(this, Buffer(tp, ptr, size));
    } else {
        construct_inplace(this, device->alloc(tp, size));
    }
}
Buffer::Buffer(const Type* tp, const void* ptr, dimn_t size, Device device) {}

BufferMode Buffer::mode() const
{
    if (impl() == nullptr) { return BufferMode::Read; }
    return impl()->mode();
}

dimn_t Buffer::size() const
{
    if (impl() == nullptr) { return 0; }
    return impl()->size();
}
dimn_t Buffer::bytes() const
{
    if (impl() == nullptr) { return 0; }
    return impl()->size() * impl()->type_info().bytes;
}

static inline bool check_device_compatibility(Buffer& dst, const Device& device)
{
    if (dst.is_null() || !device) { return true; }

    RPY_CHECK(dst.device() == device);
    // Get clangd to shut up about always true statements
    volatile bool result = true;

    return result;
}

void Buffer::to_device(Buffer& dst, const Device& device) const
{
    if (impl() != nullptr && check_device_compatibility(dst, device)) {
        auto queue = device->get_default_queue();
        impl()->to_device(dst, device, queue).wait();
    }
}
Event Buffer::to_device(Buffer& dst, const Device& device, Queue& queue) const
{
    if (impl() != nullptr && check_device_compatibility(dst, device)) {
        return impl()->to_device(dst, device, queue);
    }
    return {};
}

Buffer Buffer::map(rpy::dimn_t size, rpy::dimn_t offset)
{
    if (impl() == nullptr) { return Buffer(); }
    if (size == 0) { size = this->size(); }
    return impl()->map_mut(size, offset);
}

Buffer Buffer::map(rpy::dimn_t size, rpy::dimn_t offset) const
{
    if (impl() == nullptr) { return Buffer(); }
    if (size == 0) { size = this->size(); }
    return impl()->map(size, offset);
}

TypeInfo Buffer::type_info() const noexcept
{
    if (impl() == nullptr) { return rpy::devices::type_info<char>(); }
    return impl()->type_info();
}

Buffer Buffer::memory_owner() const noexcept
{
    if (impl() == nullptr) { return Buffer(); }
    return impl()->memory_owner();
}

Buffer Buffer::slice(dimn_t offset, dimn_t size)
{
    if (impl() == nullptr) { return Buffer(); }

    return impl()->mut_slice(size, offset);
}
Buffer Buffer::slice(dimn_t offset, dimn_t size) const
{
    if (impl() == nullptr) { return Buffer(); }
    return impl()->slice(size, offset);
}
