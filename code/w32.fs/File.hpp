#ifndef _w32_fs_File_hpp__
#define _w32_fs_File_hpp__

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
#include <w32/Object.hpp>
#include <w32/string.hpp>
#include <w32/types.hpp>

namespace w32 { namespace fs {

    /*!
     * @ingroup w32-fs
     * @brief Manipulation of a file's metadata and state.
     */
    class File :
        public Object
    {
        /* nested types. */
    public:
        typedef qword size_type;
        class Access;

        /* class methods. */
    public:
        static void remove ( const string& path );
        static bool is ( const string& path );
        static bool compressed ( const string& path );
        static void encrypt ( const string& path );
        static void decrypt ( const string& path );
        static bool encrypted ( const string& path );
        static void prevent_encryption ( const string& path );

        /* construction. */
    public:
        explicit File ( const string& path );
        File ( const string& path, Access access );

        /* methods. */
    public:
        string path () const;
        void compress ();
        void decompress ();
        void sparsify ();
        size_type size () const;
    };

    class File::Access
    {
        /* nested types. */
    public:
        typedef ::DWORD Value;

        /* values. */
    public:
        static Access i ();
        static Access o ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        Access ( Value value );

        /* methods. */
    public:
        Value value () const;

        /* operators. */
    public:
        operator Value () const;
    };

} }

#endif /* _w32_fs_File_hpp__ */
