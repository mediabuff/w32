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

#include <w32.shl.ext/Namespace.hpp>
#include <iostream>

namespace {

    template<typename I, typename T>
    void query ( void **alias, const ::IID& model, T * object )
    {
        if ( (*alias) != 0 ) { return; }
        if ( model == w32::com::guidof<I>() ) {
            (*alias) = dynamic_cast<I*>(object);
        }
    }

}

namespace w32 { namespace shl { namespace ext {

    class Listing :
        public ::IEnumIDList
    {
        /* data. */
    private:
        long myReferences;

        /* construction. */
    public:
        Listing ()
            : myReferences(1)
        {}

        /* overrides. */
    public:
        virtual hresult __stdcall Clone ( ::IEnumIDList ** clone )
        {
            (*clone) = new Listing(*this); return (S_OK);
        }

        virtual hresult __stdcall Reset ()
        {
            return (S_OK);
        }

        virtual hresult __stdcall Skip ( ulong count )
        {
            return (S_OK);
        }

        virtual hresult __stdcall Next
            ( ulong count, ::LPITEMIDLIST * items, ulong * fetched )
        {
                // No items for now...
            if ( fetched != 0 ) {
                (*fetched) = 0;
            }
            return (S_FALSE);
        }

        virtual hresult __stdcall QueryInterface
            ( const ::IID& type, void ** alias )
        {
            (*alias) = 0;
            ::query< ::IEnumIDList >(alias, type, this);
            if ( type == ::IID_IUnknown ) {
                (*alias) = reinterpret_cast< ::IUnknown* >(this);
            }
            if ( (*alias) == 0 ) {
                return (E_NOINTERFACE);
            }
            static_cast< ::IEnumIDList* >(this)->AddRef();
            return (S_OK);
        }

        virtual w32::ulong __stdcall AddRef () {
            return (::InterlockedIncrement(&myReferences));
        }

        virtual w32::ulong __stdcall Release ()
        {
            if ( ::InterlockedDecrement(&myReferences) == 0 )
            {
                delete this; return (0);
            }
            return (myReferences);
        }
    };

    const Path& Namespace::root ()
    {
        return (myRoot);
    }

    const Path& Namespace::path ()
    {
        return (myPath);
    }

    int Namespace::maxlength ( const string& path )
    {
            // Don't impose arbitrary limit.
        return (path.length());
    }

    const wchar_t * Namespace::validchars ()
    {
            // Don't impose arbitrary limit.
        return (0);
    }

    const wchar_t * Namespace::invalidchars ()
    {
            // Don't impose arbitrary limit.
        return (0);
    }

    hresult __stdcall Namespace::QueryInterface
        ( const ::IID& model, void ** alias )
    {
        (*alias) = 0;
        ::query< ::IItemNameLimits >(alias, model, this);
        ::query< ::IObjectProvider >(alias, model, this);
        ::query< ::IPersistFolder  >(alias, model, this);
        ::query< ::IPersistFolder2 >(alias, model, this);
        ::query< ::IShellFolder    >(alias, model, this);
        ::query< ::IShellFolder2   >(alias, model, this);
        ::query< ::IStorage        >(alias, model, this);
        if ( model == ::IID_IUnknown ) {
            (*alias) = reinterpret_cast< ::IUnknown* >(this);
        }
        if ( (*alias) == 0 ) {
            return (E_NOINTERFACE);
        }
        std::cout << "QueryInterface(): incrementing reference...";
        static_cast< ::IStorage* >(this)->AddRef();
        std::cout << " [OK]" << std::endl;
        return (S_OK);
    }

    hresult __stdcall Namespace::GetMaxLength
        ( const wchar_t * file, int * length )
    {
        (*length) = maxlength(file);
        return (S_OK);
    }

    hresult __stdcall Namespace::GetValidCharacters
        ( wchar_t ** valid, wchar_t ** invalid )
    {
        if ( const wchar_t * set = validchars() )
        {
            (*valid) = com::strdup(set);
        }
        if ( const wchar_t * set = invalidchars() )
        {
            (*valid) = com::strdup(set);
        }
        return (S_OK);
    }

    hresult __stdcall Namespace::QueryObject
        ( const ::GUID& object, const ::IID& model, void ** instance )
    {
        (*instance) = 0;
        return (E_NOTIMPL);
    }

    hresult __stdcall Namespace::GetClassID ( ::CLSID * guid )
    {
        (*guid) = server();
        return (S_OK);
    }

    hresult __stdcall Namespace::Initialize ( ::LPCITEMIDLIST path )
    {
        myRoot = Path(path);
        myPath = myRoot;
        gdi::messagebox("namespace-ftp", (w32::string)myPath);
        return (S_OK);
    }

    hresult __stdcall Namespace::GetCurFolder ( ::LPITEMIDLIST * path )
    {
        Path clone(myPath);
        (*path) = clone.release();
        return (S_OK);
    }

    hresult __stdcall Namespace::GetIDList ( ::LPITEMIDLIST * path )
    {
        return (GetCurFolder(path));
    }

    hresult __stdcall Namespace::SetIDList ( ::LPCITEMIDLIST path )
    {
        return (E_NOTIMPL);
    }

    hresult __stdcall Namespace::BindToObject (
        ::LPCITEMIDLIST path, ::IBindCtx * context,
        const ::IID& model, void ** instance )
    {
            // Return requested item.
        if ( model == ::IID_IShellFolder ) {}
        if ( model == ::IID_IShellFolder2 ) {}
        if ( model == ::IID_IStorage ) {}
        if ( model == ::IID_IObjectProvider ) {}
        if ( model == ::IID_IStream ) {}
        return (E_NOTIMPL);
    }

    hresult __stdcall Namespace::BindToStorage (
        ::LPCITEMIDLIST path, ::IBindCtx * context,
        const ::IID& model, void ** instance )
    {
        return (BindToObject(path, context, model, instance));
    }

    hresult __stdcall Namespace::CompareIDs (
        lparam param, ::LPCITEMIDLIST lhs, ::LPCITEMIDLIST rhs )
    {
        return (E_NOTIMPL);
    }

    hresult __stdcall Namespace::CreateViewObject
        ( hwnd owner, const ::IID& model, void ** instance )
    {
        if ( model == IID_IShellView )
        {
            gdi::messagebox(L"namespace-ftp", L"CreateViewObject");
            ::SFV_CREATE settings;
            ::ZeroMemory(&settings, sizeof(settings));
            settings.cbSize = sizeof(settings);
            return (::SHCreateShellFolderView
                (&settings, (::IShellView**)instance));
        }
        else if ( model == IID_IDropTarget )
        {
        }
        else if ( model == IID_ITransferSource )
        {
        }
        else if ( model == IID_ITransferDestination )
        {
        }
        return (QueryInterface(model, instance));
    }

    hresult __stdcall Namespace::EnumObjects
        ( hwnd owner, ::SHCONTF flags, ::IEnumIDList ** list )
    {
        (*list) = new Listing();
        return (S_OK);
    }

    hresult __stdcall Namespace::GetAttributesOf
        ( uint count, ::LPCITEMIDLIST * paths, ::SFGAOF * mask )
    {
        return (E_NOTIMPL);
    }

    hresult __stdcall Namespace::GetDisplayNameOf
        ( ::LPCITEMIDLIST path, ::SHGDNF flags, ::STRRET * name )
    {
        return (E_NOTIMPL);
    }

    hresult __stdcall Namespace::GetUIObjectOf (
        hwnd owner, uint count, ::LPCITEMIDLIST * paths,
        const ::IID& model, uint *, void ** instance )
    {
        return (E_NOTIMPL);
    }

    hresult __stdcall Namespace::ParseDisplayName (
        hwnd owner, ::IBindCtx * context, wchar_t * name,
        ulong * eaten, ::LPITEMIDLIST * path, ulong * attributes )
    {
        return (E_NOTIMPL);
    }

    hresult __stdcall Namespace::SetNameOf (
        hwnd owner, ::LPCITEMIDLIST path, const wchar_t * name,
        ::SHGDNF flags, ::LPITEMIDLIST * npath )
    {
        return (E_NOTIMPL);
    }

    hresult __stdcall Namespace::EnumSearches
        ( ::IEnumExtraSearch ** searchs )
    {
        return (E_NOTIMPL);
    }

    hresult __stdcall Namespace::GetDefaultColumn
        ( dword resource, ulong * sort, ulong * display )
    {
        if ( sort != 0 ) {
            (*sort) = 0;
        }
        if ( display != 0 ) {
            (*display) = 0;
        }
        return (S_OK);
    }

    hresult __stdcall Namespace::GetDefaultColumnState
        ( uint column, ::SHCOLSTATEF * flags )
    {
        return (E_NOTIMPL);
    }

    hresult __stdcall Namespace::GetDefaultSearchGUID ( ::GUID * search )
    {
        return (E_NOTIMPL);
    }

    hresult __stdcall Namespace::GetDetailsEx (
        ::LPCITEMIDLIST path, const ::SHCOLUMNID * column,
        ::VARIANT * variant )
    {
        return (E_NOTIMPL);
    }

    hresult __stdcall Namespace::GetDetailsOf
        ( ::LPCITEMIDLIST path, uint column, ::SHELLDETAILS * details )
    {
        return (E_NOTIMPL);
    }

    hresult __stdcall Namespace::MapColumnToSCID
        ( uint column, ::SHCOLUMNID * identifier )
    {
        return (E_NOTIMPL);
    }

    hresult __stdcall Namespace::CreateStream
        ( const wchar_t * name, dword mode, dword, dword, ::IStream ** stream )
    {
        return (E_NOTIMPL);
    }

    hresult __stdcall Namespace::OpenStream
        ( const wchar_t * name, void*, dword mode, dword, ::IStream ** stream )
    {
        return (E_NOTIMPL);
    }

    hresult __stdcall Namespace::CreateStorage (
        const wchar_t * name, dword mode, dword, dword, ::IStorage ** storage )
    {
        return (E_NOTIMPL);
    }

    hresult __stdcall Namespace::OpenStorage (
        const wchar_t * name, ::IStorage * priority, dword mode,
        ::SNB exclude, dword, ::IStorage ** storage )
    {
        return (E_NOTIMPL);
    }

    hresult __stdcall Namespace::CopyTo (
        dword count, const ::IID * excludes,
        ::SNB exclude, ::IStorage * destination )
    {
        return (E_NOTIMPL);
    }

    hresult __stdcall Namespace::MoveElementTo (
        const wchar_t * name, ::IStorage * destination,
        const wchar_t * newname, dword flags )
    {
        return (E_NOTIMPL);
    }

    hresult __stdcall Namespace::Commit ( dword flags )
    {
        return (E_NOTIMPL);
    }

    hresult __stdcall Namespace::Revert ()
    {
        return (E_NOTIMPL);
    }

    hresult __stdcall Namespace::EnumElements
        ( dword, void*, dword, ::IEnumSTATSTG ** elements )
    {
        return (E_NOTIMPL);
    }

    hresult __stdcall Namespace::DestroyElement ( const wchar_t * name )
    {
        return (E_NOTIMPL);
    }

    hresult __stdcall Namespace::RenameElement (
        const wchar_t * name, const wchar_t * newname )
    {
        return (E_NOTIMPL);
    }

    hresult __stdcall Namespace::SetElementTimes (
        const wchar_t * name, const ::FILETIME * creation,
        const ::FILETIME * access, const ::FILETIME * modification )
    {
        return (E_NOTIMPL);
    }

    hresult __stdcall Namespace::SetClass ( const ::IID& model )
    {
        return (E_NOTIMPL);
    }

    hresult __stdcall Namespace::SetStateBits ( dword state, dword mask )
    {
        return (E_NOTIMPL);
    }

    hresult __stdcall Namespace::Stat (::STATSTG * stats, dword hints )
    {
        return (E_NOTIMPL);
    }

} } }

template<> inline w32::com::Guid
    w32::com::guidof< ::IItemNameLimits > ()
{
    return (IID_IItemNameLimits);
}

template<> inline w32::com::Guid
    w32::com::guidof< ::IObjectProvider > ()
{
    return (IID_IObjectProvider);
}

template<> inline w32::com::Guid
    w32::com::guidof< ::IPersistFolder > ()
{
    return (IID_IPersistFolder);
}

template<> inline w32::com::Guid
    w32::com::guidof< ::IPersistFolder2 > ()
{
    return (IID_IPersistFolder2);
}

template<> inline w32::com::Guid
    w32::com::guidof< ::IPersistIDList > ()
{
    return (IID_IPersistIDList);
}

template<> inline w32::com::Guid
    w32::com::guidof< ::IShellFolder > ()
{
    return (IID_IShellFolder);
}

template<> inline w32::com::Guid
    w32::com::guidof< ::IShellFolder2 > ()
{
    return (IID_IShellFolder2);
}

template<> inline w32::com::Guid
    w32::com::guidof< ::IStorage > ()
{
    return (IID_IStorage);
}

template<> inline w32::com::Guid
    w32::com::guidof< ::IEnumIDList > ()
{
    return (IID_IEnumIDList);
}
