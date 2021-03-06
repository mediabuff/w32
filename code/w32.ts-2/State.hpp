#ifndef _w32_ts2_State_hpp__
#define _w32_ts2_State_hpp__

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

#include "__configure__.hpp"

namespace w32 { namespace ts {

    class Execution;
    class Registration;

    class State
    {
        /* nested types. */
    public:
        typedef ::TASK_STATE Value;

        /* class data. */
    public:
        static const State unknown ();
        static const State disabled ();
        static const State queued ();
        static const State ready ();
        static const State running ();

        /* class methods. */
    public:
        static State of ( const Execution& task );
        static State of ( const Registration& task );

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
            // For internal use only.
        State ( Value value );

        /* methods. */
    public:
        Value value () const;

        /* operators. */
    public:
        operator Value () const;

        bool operator== ( const State& other ) const;
        bool operator!= ( const State& other ) const;
    };

} }

#endif /* _w32_ts2_State_hpp__ */

