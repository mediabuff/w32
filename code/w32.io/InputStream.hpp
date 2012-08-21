#ifndef _w32_io_InputStream_hpp__
#define _w32_io_InputStream_hpp__

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

/*!
 * @file w32.io/InputStream.hpp
 * @author Andre Caron (andre.l.caron@gmail.com)
 */

#include "__configure__.hpp"
#include <w32/types.hpp>
#include <w32.io/Stream.hpp>

namespace w32 {

    class Waitable;

}

namespace w32 { namespace io {

    class Transfer;

    /*!
     * @ingroup w32-io
     */
    class InputStream :
        public Stream
    {
        /* construction. */
    public:
        explicit InputStream ( const Handle& handle );

        /* methods. */
    public:
           /*!
            * @param data Pointer to the first free character in the buffer.
            * @param size Number of bytes in the buffer.
            *
            * @return The number of characters successfully read.
            */
        dword get ( void * data, dword size );

        bool get ( void * data, dword size, ::OVERLAPPED& xfer );
        bool get ( void * data, dword size, Transfer& xfer );

        bool get ( void * data, dword size, Transfer& xfer, dword& xferred );

        /* operators. */
    public:
        operator w32::Waitable () const;
    };

} }

#endif /* _w32_io_InputStream_hpp__ */
