#ifndef _w32_shl_Folder_hpp__
#define _w32_shl_Folder_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/com/Wrapper.hpp>

namespace w32 { namespace shl {

    class Item;

    class W32_SHL_EXPORT Folder :
        public com::Wrapper< ::IShellFolder >
    {
        /* construction. */
    public:
        explicit Folder ( ::IShellFolder * object );
        explicit Folder ( const Item& item );

        /* methods. */
    public:
    };

} }

template<> inline w32::com::Guid
    w32::com::guidof< ::IShellFolder > ()
{
    return (IID_IShellFolder);
}

#endif /* _w32_shl_Folder_hpp__ */
