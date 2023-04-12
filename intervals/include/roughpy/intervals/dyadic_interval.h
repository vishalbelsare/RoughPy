// Copyright (c) 2023 Datasig Group. All rights reserved.
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

#ifndef ROUGHPY_INTERVALS_DYADIC_INTERVAL_H_
#define ROUGHPY_INTERVALS_DYADIC_INTERVAL_H_

#include "dyadic.h"
#include "interval.h"

#include <iosfwd>
#include <vector>

namespace rpy {
namespace intervals {

class ROUGHPY_INTERVALS_EXPORT DyadicInterval : public Dyadic, public Interval {
    using Dyadic::m_multiplier;
    using Dyadic::m_power;

protected:
    using Interval::m_interval_type;

public:
    using typename Dyadic::multiplier_t;
    using typename Dyadic::power_t;

    using Dyadic::Dyadic;

    DyadicInterval() = default;

    explicit DyadicInterval(IntervalType itype) : Dyadic(), Interval(itype) {
        assert(itype == IntervalType::Clopen || itype == IntervalType::Opencl);
    }
    explicit DyadicInterval(Dyadic dyadic) : Dyadic(dyadic), Interval() {}
    DyadicInterval(Dyadic dyadic, IntervalType itype) : Dyadic(dyadic), Interval(itype) {}
    DyadicInterval(multiplier_t k, power_t n, IntervalType itype) : Dyadic(k, n), Interval(itype) {
        assert(itype == IntervalType::Clopen || itype == IntervalType::Opencl);
    }
    DyadicInterval(Dyadic dyadic, power_t resolution, IntervalType itype = IntervalType::Clopen);
    DyadicInterval(param_t val, power_t resolution, IntervalType itype = IntervalType::Clopen);

    multiplier_t unit() const noexcept {
        return (m_interval_type == IntervalType::Clopen) ? 1 : -1;
    }

    using Dyadic::operator++;
    using Dyadic::operator--;
    using Dyadic::multiplier;
    using Dyadic::power;

    Dyadic dincluded_end() const;
    Dyadic dexcluded_end() const;
    Dyadic dinf() const;
    Dyadic dsup() const;

    param_t inf() const override;
    param_t sup() const override;
    param_t included_end() const override;
    param_t excluded_end() const override;

    DyadicInterval shrink_to_contained_end(power_t arg = 1) const;
    DyadicInterval shrink_to_omitted_end() const;
    DyadicInterval &shrink_interval_right();
    DyadicInterval &shrink_interval_left(power_t arg = 1);
    DyadicInterval &expand_interval(power_t arg = 1);

    bool contains(const DyadicInterval &other) const;
    bool aligned() const;

    DyadicInterval &flip_interval();

    DyadicInterval shift_forward(multiplier_t arg = 1) const;
    DyadicInterval shift_back(multiplier_t arg = 1) const;

    DyadicInterval &advance() noexcept;
};


ROUGHPY_INTERVALS_EXPORT
std::ostream& operator<<(std::ostream& os, const DyadicInterval& di);


ROUGHPY_INTERVALS_EXPORT
std::vector<DyadicInterval> to_dyadic_intervals(const Interval& interval, typename Dyadic::power_t tol, IntervalType itype=IntervalType::Clopen);

ROUGHPY_INTERVALS_EXPORT
bool operator<(const DyadicInterval& lhs, const DyadicInterval& rhs) noexcept;


}// namespace intervals
}// namespace rpy

#endif// ROUGHPY_INTERVALS_DYADIC_INTERVAL_H_
