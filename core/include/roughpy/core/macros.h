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

//
// Created by user on 04/03/23.
//

#ifndef ROUGHPY_CORE_MACROS_H
#define ROUGHPY_CORE_MACROS_H



#if (defined(_DEBUG) || !defined(NDEBUG) || !defined(__OPTIMIZE__)) && !defined(RPY_DEBUG)
#   define RPY_DEBUG
#endif

#if defined(_MSC_VER) && defined(_MSVC_LANG)
#   define RPY_CPP_VERSION _MSVC_LANG
#else
#   define RPY_CPP_VERSION __cplusplus
#endif


#if defined(__GNUC__) || defined(__clang__)
#   define RPY_UNUSED __attribute__((unused))
#   define RPY_USED __attribute__((used))
#else
#   define RPY_UNUSED
#   define RPY_USED
#endif


#if defined(__GNUC__) || defined(__clang__)
#    define RPY_UNREACHABLE() (__builtin_unreachable())
#    define RPY_UNREACHABLE_RETURN(...) RPY_UNREACHABLE()
#elif defined(_MSC_VER)
#    define RPY_UNREACHABLE() (__assume(false))
#    define RPY_UNREACHABLE_RETURN(...) RPY_UNREACHABLE(); return __VA_ARGS__
#else
#    define RPY_UNREACHABLE()
#    define RPY_UNREACHABLE_RETURN(...) RPY_UNREACHABLE(); return __VA_ARGS__
#endif


// Macros that control optimisations

#if defined(__OPTIMIZE__) || !defined(RPY_DEBUG)
#   if defined(_WIN32) || defined(_WIN64)
#       define RPY_INLINE_ALWAYS __forceinline
#   elif defined(__GNUC__) || defined(__clang__)
#       define RPY_INLINE_ALWAYS inline __attribute__((always_inline))
#   else
#       define RPY_INLINE_ALWAYS inline
#   endif
#endif

#if defined(_WIN32) || defined(_WIN64)
#   define RPY_INLINE_NEVER __declspec(noinline)
#elif defined(__GNUC__) || defined(__clang__)
#   define RPY_INLINE_NEVER __attribute__((never_inline))
#else
#   define RPY_INLINE_NEVER
#endif

#if defined(__GNUC__) || defined(__clang__)
#   define RPY_RESTRICT(ARG) ARG __restrict__
#elif defined(_MSC_VER)
#   define RPY_RESTRICT(ARG) ARG __restrict
#endif



#define RPY_STRINGIFY_IMPL(ARG) #ARG
#define RPY_STRINGIFY(ARG) RPY_STRINGIFY_IMPL(ARG)

#define RPY_JOIN_IMPL_IMPL(LHS, RHS) X ## Y
#define RPY_JOIN_IMPL(LHS, RHS) RPY_JOIN_IMPL_IMPL(LHS, RHS)
#define RPY_JOIN(LHS, RHS) RPY_JOIN_IMPL(LHS, RHS)


#endif//ROUGHPY_CORE_MACROS_H
