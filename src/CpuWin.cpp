/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2021 EnyxSA
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "Cpu.hpp"

#include <windows.h>
#include <processthreadsapi.h>
#include <errhandlingapi.h>

#include <system_error>

namespace enyx {
namespace net_tester {

void
pin_current_thread_to_cpu_core(CpuCoreId id)
{
    auto const mask = DWORD_PTR(1) << id;
    if (! SetThreadAffinityMask(GetCurrentThread(), mask))
        throw std::system_error{int(GetLastError()), std::system_category()};
}

} // namespace net_tester
} // namespace enyx
