// Copyright (c) 2023 RoughPy Developers. All rights reserved.
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
// Created by user on 28/03/23.
//

#include "algebra_iterator.h"

#include <roughpy/algebra/algebra_iterator.h>
#include <roughpy/algebra/free_tensor.h>
#include <roughpy/algebra/lie.h>
#include <roughpy/algebra/shuffle_tensor.h>
#include <roughpy/core/macros.h>

#include "lie_key.h"
#include "tensor_key.h"

using namespace rpy;
using namespace rpy::algebra;

template <typename Algebra, typename KeyType>
static void init_iterator(py::module_ &m, const char *iter_name)
{

    py::class_<AlgebraIteratorItem<Algebra>> klass(m, iter_name);

    klass.def("key", [](const AlgebraIteratorItem<Algebra> &item) {
        return KeyType(item.basis(), item.key());
    });
    klass.def("value", &AlgebraIteratorItem<Algebra>::value);
}

#define MAKE_ITERATOR_TYPE(ALG, KEY)                                           \
    init_iterator<ALG, KEY>(m, RPY_STRINGIFY(ALG##IteratorItem))

void python::init_algebra_iterator(py::module_ &m)
{

    MAKE_ITERATOR_TYPE(Lie, PyLieKey);
    MAKE_ITERATOR_TYPE(FreeTensor, PyTensorKey);
    MAKE_ITERATOR_TYPE(ShuffleTensor, PyTensorKey);
}
#undef MAKE_ITERATOR_TYPE
