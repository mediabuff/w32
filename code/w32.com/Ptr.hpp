#ifndef _w32_com_Ptr_hpp__
#define _w32_com_Ptr_hpp__

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

namespace w32{ namespace com {

        /*!
         * @brief Hold a COM object's reference count.
         *
         * This classe's invariant is that it points to a COM object (an
         * instance of a class that derives directly or indirectly from
         * \c IUnknown) and owns one of that object's reference counts or
         * points to 0.
         */
    template<typename Interface>
    class Ptr
    {
        /* class methods. */
    public:
            /*!
             * @brief Acquire extra COM reference to object.
             * @param object COM Object to acquire.
             *
             * This function exists mainly to enforce that the class compiles
             * only for classes that derive from IUnknown.
             */
        static Interface * acquire ( Interface * object )
        {
            if ( object ) {
                object->AddRef();
            }
            return (object);
        }

            /*!
             * @brief Release COM reference to object.
             * @param object COM object to release.
             *
             * This function exists mainly to enforce that the class compiles
             * only for classes that derive from IUnknown.
             */
        static Interface * release ( Interface * object )
        {
            if ( object ) {
                object->Release();
            }
            return (0);
        }

            // Pass-though hook for pointer validation.
        static Interface * dereference ( Interface * object )
        {
            return (object);
        }

        /* data. */
    private:
        Interface * myValue;

        /* construction. */
    public:
        Ptr ()
            : myValue(0)
        {}

            /*!
             * @brief Gain ownership of a COM object.
             *
             * This assigns a particular reference count to a COM object. Use
             * this constructor after creating the object's instance or after
             * calling AddRef (no both as this will leak the object).
             *
             * To perform similar work on an existing handle, call \c reset().
             *
             * @see reset()
             */
        Ptr ( Interface * value )
            : myValue(value)
        {
        }

            /*!
             * @brief Create new reference to COM object.
             * @param other Ptr to clone.
             *
             * This increments the object's reference count such that the two
             * objects refer to the same handle.
             */
        Ptr ( const Ptr<Interface>& other )
            : myValue(acquire(other.value()))
        {
        }

            /*!
             * @brief Release object.
             *
             * This decrements the object's reference count acquired in the
             * constructor or in a call to \c reset().
             *
             * To perform similar work on an existing handle, call \c reset().
             *
             * @see reset()
             */
        ~Ptr () {
            reset();
        }

        /* methods. */
    public:
            /*!
             * @brief Check if the handle points to something.
             * @return \c true if the handle does not point to 0.
             *
             * This funciton supposes that the pointer is not dangling.
             */
        bool ok () const {
            return (myValue != 0);
        }

        bool bad () const {
            return (myValue == 0);
        }

            /*!
             * @brief Access the COM object.
             * @return The current pointer of the handle.
             *
             * This funciton supposes that the pointer is not dangling.
             */
        Interface * value () const {
            return (myValue);
        }

        void swap ( Ptr<Interface>& other )
        {
            Interface *const temporary = other.myValue;
            other.myValue = myValue;
            myValue = temporary;
        }

            /*!
             * @brief Relinquish ownership of the object's reference count.
             * @return The previous value of the pointer.
             *
             * This function returns the handle's current pointer, assigns it
             * to 0, but does not release the object's reference count. Calling
             * this method means you wish to manage the reference count
             * manually.
             */
        Interface * release ()
        {
            Interface * const old = myValue;
            myValue = 0;
            return (old);
        }

            /*!
             * @brief Release old object and optionally assign new one.
             * @param value New object to own a reference count.
             *
             * This function is equivalent to assignement in that it performs
             * work equivalent to the destructor and then work equivalent to
             * the parametric contructor. See those functions for more detail.
             *
             * @see Ptr()
             * @see ~Ptr()
             */
        void reset ( Interface * value = 0 )
        {
            if ( ok() ) {
                myValue = release(myValue);
            }
            myValue = value;
        }

        /* operators. */
    public:
        Ptr<Interface>& operator= ( const Ptr<Interface>& other )
        {
            Ptr<Interface>(other).swap(*this); return (*this);
        }

        Interface * operator-> () const
        {
            return (dereference(myValue));
        }

        Interface& operator* () const
        {
            return (*dereference(myValue));
        }

        bool operator== ( const Ptr<Interface>& other ) const {
            return (myValue == other.myValue);
        }

        bool operator!= ( const Ptr<Interface>& other ) const {
            return ( !((*this) == other) );
        }
    };

    template<typename Interface>
    void swap ( Ptr<Interface>& lhs, Ptr<Interface>& rhs )
    {
        lhs.swap(rhs);
    }

        /*!
         * @brief Shortcut to create a handle and call AddRef() for an object.
         */
    template<typename Interface>
    Ptr<Interface> manage ( Interface * object )
    {
        if ( object == 0 ) {
            return (Ptr<Interface>());
        }
        return (Ptr<Interface>(Ptr<Interface>::acquire(object)));
    }

} }

#endif /* _w32_com_Ptr_hpp__ */
