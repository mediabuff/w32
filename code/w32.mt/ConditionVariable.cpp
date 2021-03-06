// Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <w32.mt/ConditionVariable.hpp>
#include <w32/Error.hpp>

#if _WIN32_WINNT >= _WIN32_WINNT_VISTA

namespace w32 { namespace mt {

    ConditionVariable::ConditionVariable ()
    {
        ::InitializeConditionVariable(&myData);
    }

    ConditionVariable::~ConditionVariable ()
    {
    }

    ConditionVariable::Data& ConditionVariable::data ()
    {
        return (myData);
    }

    const ConditionVariable::Data& ConditionVariable::data () const
    {
        return (myData);
    }

    void ConditionVariable::signal ()
    {
        ::WakeConditionVariable(&myData);
    }

    void ConditionVariable::broadcast ()
    {
        ::WakeAllConditionVariable(&myData);
    }

    void ConditionVariable::sleep ( CriticalSection& lock )
    {
        const ::BOOL result = ::SleepConditionVariableCS(
            &myData, &lock.data(), INFINITE
            );
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(SleepConditionVariableCS, error);
        }
    }

    void ConditionVariable::sleep ( ReadWriteLock& lock, bool shared )
    {
        const ::ULONG flags = ((shared)? CONDITION_VARIABLE_LOCKMODE_SHARED:0);
        const ::BOOL result = ::SleepConditionVariableSRW(
            &myData, &lock.data(), INFINITE, flags
            );
        if ( result == 0 )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(SleepConditionVariableCS, error);
        }
    }

} }

#endif
