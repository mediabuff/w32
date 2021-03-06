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

#include <w32.ts-2/State.hpp>
#include <w32.ts-2/Execution.hpp>
#include <w32.ts-2/Registration.hpp>

namespace w32 { namespace ts {

    const State State::unknown ()
    {
        return (TASK_STATE_UNKNOWN);
    }

    const State State::disabled ()
    {
        return (TASK_STATE_DISABLED);
    }

    const State State::queued ()
    {
        return (TASK_STATE_QUEUED);
    }

    const State State::ready ()
    {
        return (TASK_STATE_READY);
    }

    const State State::running ()
    {
        return (TASK_STATE_RUNNING);
    }

    State State::of ( const Execution& task )
    {
        ::TASK_STATE value = TASK_STATE_UNKNOWN;
        const com::Result result = task.ptr()->get_State(&value);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IRunningTask,get_State,result);
        }
        return (State(value));
    }

    State State::of ( const Registration& task )
    {
        ::TASK_STATE value = TASK_STATE_UNKNOWN;
        const com::Result result = task.ptr()->get_State(&value);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IRegisteredTask,get_State,result);
        }
        return (State(value));
    }

    State::State ( Value value )
        : myValue(value)
    {
    }

    State::Value State::value () const
    {
        return (myValue);
    }

    State::operator State::Value () const
    {
        return (myValue);
    }

    bool State::operator== ( const State& other ) const
    {
        return (myValue == other.myValue);
    }

    bool State::operator!= ( const State& other ) const
    {
        return (myValue != other.myValue);
    }

} }
