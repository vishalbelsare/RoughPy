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
// Created by user on 11/10/23.
//

#include <roughpy/device/event.h>
#include <roughpy/device/kernel.h>
#include <roughpy/device/queue.h>

#include <roughpy/core/helpers.h>

using namespace rpy;
using namespace rpy::devices;


string Kernel::name() const
{
    if (!p_impl) { return ""; }
    return p_impl->name();
}

dimn_t Kernel::num_args() const
{
    if (!p_impl) { return 0; }
    return p_impl->num_args();
}

Event Kernel::launch_async(
        Queue& queue,
        Slice<void*> args,
        Slice<dimn_t> arg_sizes,
        const KernelLaunchParams& params
)
{
    if (!p_impl) { return Event(); }
    if (!params.has_work()) { return Event(); }

    auto nargs = p_impl->num_args();
    if (nargs != args.size() || nargs != arg_sizes.size()) {
        RPY_THROW(std::runtime_error, "incorrect number of arguments provided");
    }

    return p_impl->launch_kernel_async(queue, args, arg_sizes, params);
}
EventStatus Kernel::launch_sync(
        Queue& queue,
        Slice<void*> args,
        Slice<dimn_t> arg_sizes,
        const KernelLaunchParams& params
)
{
    if (!params.has_work()) { return EventStatus::CompletedSuccessfully; }
    auto event = launch_async(queue, args, arg_sizes, params);
    event.wait();
    return event.status();
}




std::vector<bitmask_t>
Kernel::construct_work_mask(const KernelLaunchParams& params)
{
    RPY_DBG_ASSERT(params.has_work());
    std::vector<bitmask_t> result;

    auto total_work = params.total_work_size();
    auto num_masks = round_up_divide(total_work, CHAR_BIT*sizeof(bitmask_t));
    result.reserve(num_masks);
    result.resize(num_masks-1, ~bitmask_t(0));

    auto underflow = num_masks*CHAR_BIT*sizeof(bitmask_t) - total_work;
    auto final_mask = ~((bitmask_t(1) << (underflow + 1)) - 1);
    result.push_back(final_mask);

    return result;
}
