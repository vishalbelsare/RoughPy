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
// Created by user on 16/10/23.
//

#ifndef ROUGHPY_DEVICE_SRC_CPUDEVICE_CPU_EVENT_H_
#define ROUGHPY_DEVICE_SRC_CPUDEVICE_CPU_EVENT_H_

#include "devices/device_object_base.h"
#include "devices/event.h"

#include <condition_variable>
#include <exception>
#include <mutex>

namespace rpy {
namespace devices {

struct HostEventContext {
    std::mutex lock;
    std::condition_variable condition;
    EventStatus status;
    std::exception_ptr error_state;
};

class CPUEvent : public dtl::RefCountBase<EventInterface>
{
    using guard_type = std::unique_lock<std::mutex>;

    mutable HostEventContext m_ctx;

public:
    void wait() override;
    bool is_host() const noexcept override;
    EventStatus status() const override;
    bool is_user() const noexcept override;
    void set_status(EventStatus status) override;
};

}// namespace devices
}// namespace rpy

#endif// ROUGHPY_DEVICE_SRC_CPUDEVICE_CPU_EVENT_H_
