#ifndef _w32_http_Response_hpp__
#define _w32_http_Response_hpp__

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
#include <w32/astring.hpp>
#include <w32/types.hpp>

namespace w32 { namespace http {

    typedef ushort Status;

    class Chunk;
    class Header;

    class Response
    {
        /* nested types. */
    public:
        typedef ::HTTP_RESPONSE_V2 Data;

        class Header;

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        Response ();

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;

        void clear ();
        void status ( Status status, const astring& reason );

        void add ( const http::Header& header, const astring& content );
        void add ( const Header& header, const astring& content );
        void add ( Chunk& chunk );
    };

    class Response::Header
    {
        /* nested types. */
    public:
        typedef ::HTTP_HEADER_ID Value;

        /* class data. */
    public:
        static const Header acceptranges ();
        static const Header age ();
        static const Header etag ();
        static const Header location ();
        static const Header proxyauthenticate ();
        static const Header retryafter ();
        static const Header server ();
        static const Header setcookie ();
        static const Header vary ();
        static const Header wwwauthenticate ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        Header ( Value value );

        /* operators. */
    public:
        operator Value () const;

        bool operator== ( const Header& rhs ) const;
        bool operator!= ( const Header& rhs ) const;
    };

} }

#endif /* _w32_http_Response_hpp__ */
