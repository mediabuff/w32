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
 * @file w32.sy/Impersonation.cpp
 * @brief User context impersonation services.
 */

#include <w32.sy/Impersonation.hpp>
#include <w32.sy/Token.hpp>
#include <w32/Error.hpp>
#include <w32/string.hpp>

namespace w32 { namespace sy {

    void clear ( string& password )
    {
        ::SecureZeroMemory(password.data(), password.size()*sizeof(wchar_t));
    }

    void impersonate ( const Token& token )
    {
        const ::BOOL result = ::ImpersonateLoggedOnUser(token.handle());
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(ImpersonateLoggedOnUser, error);
        }
    }

    void revert ()
    {
        const ::BOOL result = ::RevertToSelf();
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(RevertToSelf, error);
        }
    }

    Token logon ( const string& domain,
        const string& username, const string& password )
    {
        ::HANDLE token = 0;
        const ::BOOL result = ::LogonUserW(
            username.data(), domain.data(), password.data(),
            LOGON32_LOGON_BATCH, LOGON32_PROVIDER_DEFAULT, &token
            );
        if ( result == FALSE )
        {
            const ::DWORD error = ::GetLastError();
            UNCHECKED_WIN32C_ERROR(LogonUser, error);
        }
        return (Token(Token::claim(token)));
    }

    Impersonation::Impersonation ( const Token& token )
    {
        impersonate(token);
    }

    Impersonation::~Impersonation ()
    try
    {
        revert();
    }
        // Don't leak exceptions from destructor.
    catch ( ... ) {}

} }
