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

#include <w32.ts-2/Executions.hpp>
#include <w32.ts-2/Service.hpp>

namespace {

    ::IRunningTaskCollection * fetch ( ::ITaskService * service )
    {
        ::IRunningTaskCollection * tasks = 0;
        const w32::com::Result result = service->GetRunningTasks(0, &tasks);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(ITaskService, GetRunningTasks, result);
        }
        return (tasks);
    }

    ::IRunningTaskCollection * fetch ( ::IRegisteredTask * task )
    {
        ::IRunningTaskCollection * tasks = 0;
        const w32::com::Result result = task->GetInstances(0, &tasks);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IRegisteredTask, GetInstances, result);
        }
        return (tasks);
    }

}

namespace w32 { namespace ts {

    Executions::Executions ( Service& service )
        : com::Wrapper< ::IRunningTaskCollection >
              ( ::fetch(service.ptr().value()) )
    {
    }

    long Executions::count () const
    {
        long value = 0;
        const com::Result result = ptr()->get_Count(&value);
        if ( result.bad() ) {
            UNCHECKED_COM_ERROR(IRunningTaskCollection, get_Count, result);
        }
        return (value);
    }

} }
