#ifndef _w32_tp_Pool_hpp__
#define _w32_tp_Pool_hpp__

// Copyright(c) Andre Caron, 2009-2011
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/types.hpp>
#include <w32/Reference.hpp>

namespace w32 { namespace tp {

    /*!
     * @ingroup w32-tp
     * @brief Group of threads.
     */
    class Pool
    {
        /* nested types. */
    public:
        typedef Reference< ::PTP_POOL > Handle;

        /* class methods. */
    public:
        static const Handle claim ( ::PTP_POOL handle );
        static const Handle proxy ( ::PTP_POOL handle );

        /* data. */
    private:
        Handle myHandle;

        /* construction. */
    public:
        Pool ();
        explicit Pool ( const Handle& handle );

        /* methods. */
    public:
        const Handle& handle () const;

        void minimum_threads ( dword count );
        void maximum_threads ( dword count );

        void threads ( dword count );
        void threads ( dword minimum, dword maximum );
    };

} }

#endif /* _w32_tp_Pool_hpp__ */
