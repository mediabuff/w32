#ifndef _w32_string_hpp__
#define _w32_string_hpp__

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
#include <w32/Codepage.hpp>
#include <w32/types.hpp>
#include <iostream>
#include <string>

namespace w32 {

    class astring;
    class bstring;

    /*!
     * @ingroup w32
     * @brief Unicode character string.
     */
    class string
    {
        /* nested types. */
    public:
        typedef dword size_type;
        typedef wchar_t char_type;
        typedef char_type * pointer;
        typedef const char_type * const_pointer;
        typedef pointer iterator;
        typedef const_pointer const_iterator;

        class box;

        /* class data. */
    public:
        static const size_type npos;

        /* data. */
    private:
        size_type mySize;
        pointer myData;

        /* construction. */
    public:
        string ();
        string ( const char * other, Codepage encoding=Codepage::ansi() );
        string ( const char * other, size_type size,
            Codepage encoding=Codepage::ansi() );
        string ( const astring& other );
        string ( const std::string& other,
            Codepage encoding=Codepage::ansi() );
        string ( const_pointer other );
        string ( const_pointer other, size_type size );
        string ( const bstring& other );
        string ( const std::wstring& other );

        string ( const dword size, char_type filler = L'\0' );

        explicit string ( const box& value );
        string ( const string& other );
        ~string ();

        /* methods. */
    public:
        size_type size () const;
        size_type length () const;
        bool empty () const;

        pointer data ();
        const_pointer data () const;
        pointer c_str ();
        const_pointer c_str () const;

        void swap ( string& other );

        void erase ( iterator begin, iterator end );
        void resize ( size_type length, char_type filler = L'\0' );

        string substr ( size_type offset, size_type length = npos ) const;

        void clear ();

        iterator begin ();
        iterator end ();
        const_iterator begin () const;
        const_iterator end () const;

        /* operators. */
    public:
        string& operator= ( const string& other );
        string& operator= ( const_pointer other );
        string& operator= ( const std::wstring& other );

        char_type& operator[] ( size_type i );
        char_type operator[] ( size_type i ) const;

        operator const std::wstring () const;

        bool operator== ( const string& rhs ) const;
        bool operator!= ( const string& rhs ) const;

        bool operator< ( const string& rhs ) const;
        bool operator<= ( const string& rhs ) const;
        bool operator> ( const string& rhs ) const;
        bool operator>= ( const string& rhs ) const;

        string& operator+= ( const string& rhs );
        string operator+ ( const string& rhs ) const;

        string& operator+= ( wchar_t rhs );
        string operator+ ( wchar_t rhs ) const;
    };

    string operator+
        ( const wchar_t * lhs, const string& rhs );

    inline void swap ( string& lhs, string& rhs ) {
        lhs.swap(rhs);
    }

    inline string::char_type& string::operator[] ( size_type i )
    {
        return (myData[i]);
    }

    inline string::char_type string::operator[] ( size_type i ) const
    {
        return (myData[i]);
    }

    inline string::string ( const std::wstring& other )
        : mySize(other.size()), myData(new wchar_t[mySize+1])
    {
        *std::copy(other.begin(), other.end(), begin()) = L'\0';
    }

    inline string::operator const std::wstring () const
    {
        return (std::wstring(begin(), end()));
    }

    std::wostream& operator<<
        ( std::wostream& out, const string& value );

    inline bool operator== ( const wchar_t * lhs, const string& rhs )
    {
        return (std::wcscmp(lhs, rhs.data()) == 0);
    }

    inline bool operator== ( const string& lhs, const wchar_t * rhs )
    {
        return (std::wcscmp(lhs.data(), rhs) == 0);
    }

    inline bool operator!= ( const wchar_t * lhs, const string& rhs )
    {
        return (std::wcscmp(lhs, rhs.data()) != 0);
    }

    inline bool operator!= ( const string& lhs, const wchar_t * rhs )
    {
        return (std::wcscmp(lhs.data(), rhs) != 0);
    }

    class string::box
    {
        /* data. */
    private:
        size_type mySize;
        pointer myData;

        /* construction. */
    public:
        explicit box ( pointer data );
        box ( pointer data, size_type size );

        /* methods. */
    public:
        size_type size () const;
        pointer data () const;
    };

    inline std::wistream& getline
        ( std::wistream& in, string& value, const wchar_t delimiter )
    {
        typedef std::wistream::traits_type traits;
        std::wios::iostate state = std::wios::goodbit;
        bool changed = false;
        const std::wistream::sentry ok(in,true);
        if ( in )
        {
            value.clear();
            const int stop = traits::to_int_type(delimiter);
            for ( traits::int_type meta = in.rdbuf()->sgetc();
                ; meta = in.rdbuf()->snextc() )
            {
                if ( traits::eq_int_type(traits::eof(),meta) ) {
                    state |= std::wios::eofbit; break;
                }
                else if ( traits::eq_int_type(meta, stop) ) {
                    changed = true; in.rdbuf()->sbumpc(); break;
                }
                else {
                    value += traits::to_char_type(meta); changed = true;
                }
            }
            if ( !changed ) {
                state |= std::wios::failbit;
            }
            in.setstate(state);
        }
        return (in);
    }

}

#endif /* _w32_string_hpp__ */
