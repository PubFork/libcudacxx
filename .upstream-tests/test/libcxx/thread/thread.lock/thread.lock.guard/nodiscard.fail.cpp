//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// UNSUPPORTED: libcpp-has-no-threads

// [[nodiscard]] on constructors isn't supported by all compilers
// UNSUPPORTED: clang-6, clang-7, clang-8, clang-9
// UNSUPPORTED: apple-clang-9, apple-clang-10, apple-clang-11
// UNSUPPORTED: gcc-5

// [[nodiscard]] isn't supported in C++98 and C++03 (not even as an extension)
// UNSUPPORTED: c++98, c++03

// <cuda/std/mutex>

// template <class Mutex> class lock_guard;

// [[nodiscard]] explicit lock_guard(mutex_type& m);
// [[nodiscard]] lock_guard(mutex_type& m, adopt_lock_t);

// Test that we properly apply [[nodiscard]] to lock_guard's constructors,
// which is a libc++ extension.

// MODULES_DEFINES: _LIBCUDACXX_ENABLE_NODISCARD
#define _LIBCUDACXX_ENABLE_NODISCARD
#include <cuda/std/mutex>

int main(int, char**) {
    cuda::std::mutex m;
    cuda::std::lock_guard<cuda::std::mutex>{m}; // expected-error{{ignoring temporary created by a constructor declared with 'nodiscard' attribute}}
    cuda::std::lock_guard<cuda::std::mutex>{m, cuda::std::adopt_lock}; // expected-error{{ignoring temporary created by a constructor declared with 'nodiscard' attribute}}
    return 0;
}
