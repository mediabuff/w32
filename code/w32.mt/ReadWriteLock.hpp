#ifndef _w32_mt_ReadWriteLock_hpp__
#define _w32_mt_ReadWriteLock_hpp__

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

#include <w32/NotCopyable.hpp>

#if _WIN32_WINNT >= _WIN32_WINNT_VISTA

namespace w32 { namespace mt {

    /*!
     * @ingroup w32-mt
     * @brief Mutual exclusion lock with exclusive or shared access.
     *
     * For some problems, pure mutual exclusion locks are too restrictive.  When
     * read-only access to a resource is already thread-safe, it makes no sense
     * for reader threads to deny each other concurrent access.  Reader-writer
     * locks grant exclusive write-safe access for write operations (this blocks
     * any other reader or writer) or shared read-safe access for read
     * operations (this blocks out all writers but allows other readers).
     *
     * @see CriticalSection
     * @see Mutex
     */
    class ReadWriteLock :
        private NotCopyable
    {
        /* nested types. */
    public:
        typedef ::SRWLOCK Data;

        class ReadGuard :
            private w32::NotCopyable
        {
            /* data. */
        private:
            Data& myLock;

            /* construction. */
        public:
            ReadGuard ( ReadWriteLock& lock );
            ~ReadGuard ();
        };

        class WriteGuard :
            private w32::NotCopyable
        {
            /* data. */
        private:
            Data& myLock;

            /* construction. */
        public:
            WriteGuard ( ReadWriteLock& lock );
            ~WriteGuard ();
        };

        /* data. */
    private:
        Data myData;

        /* construction. */
    public:
        ReadWriteLock ();
        ~ReadWriteLock ();

        /* methods. */
    public:
        Data& data ();
        const Data& data () const;
    };

} }

#endif

#endif /* _w32_mt_ReadWriteLock_hpp__ */
