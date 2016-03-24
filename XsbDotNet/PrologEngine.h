/*************************************************************************
 *                                                                       *
 * XSBDotNet, Copyright (C) 2007 Gonçalo C. Lopes.                       *
 * All rights reserved. Email: netode@gmail.com                          *
 *                                                                       *
 * This library is free software; you can redistribute it and/or         *
 * modify it under the terms of EITHER:                                  *
 *   (1) The GNU Lesser General Public License as published by the Free  *
 *       Software Foundation; either version 2.1 of the License, or (at  *
 *       your option) any later version. The text of the GNU Lesser      *
 *       General Public License is included with this library in the     *
 *       file LICENSE.TXT.                                               *
 *   (2) The BSD-style license that is included with this library in     *
 *       the file LICENSE-BSD.TXT.                                       *
 *                                                                       *
 * This library is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the files    *
 * LICENSE.TXT and LICENSE-BSD.TXT for more details.                     *
 *                                                                       *
 *************************************************************************/

#pragma once

#include "cinterf.h"
#ifdef MULTI_THREAD
#include "thread_xsb.h"
#endif
#include "PrologTerm.h"
#include "QueryHandle.h"

using namespace System::Security;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

namespace XsbDotNet
{
    public delegate bool PrologPredicate(cli::array<PrologTerm ^> ^arguments);

    [UnmanagedFunctionPointer(CallingConvention::Cdecl)]
    delegate bool PrologCallback(prolog_term term);

    public ref class PrologEngine
    {
    private:
#ifdef MULTI_THREAD
        th_context *th;
#endif
        IDictionary<System::String ^, PrologPredicate ^> ^managedPredicates;
        PrologCallback ^callback;
	private:
		PrologEngine(CTXTdecl);
        bool CallManagedPredicate(prolog_term term);
		static PrologEngine ^mainThread;
    public:
#ifdef MULTI_THREAD
        ~PrologEngine();
#endif
        XsbDotNet::PrologTerm ^ CreateTerm();
        XsbDotNet::PrologTerm ^ CreateTerm(System::String ^symbol);
        XsbDotNet::PrologTerm ^ CreateTerm(System::String ^symbol, int arity);
        bool Command(System::String ^command);
        bool Command(XsbDotNet::PrologTerm ^command);
        QueryHandle ^ Query(System::String ^query);
        QueryHandle ^ Query(XsbDotNet::PrologTerm ^query);
        void RegisterManagedPredicate(System::String ^name, PrologPredicate ^predicate);

		static void InitXsb(System::String ^xsbHome);
        static void CloseXsb();
#ifdef MULTI_THREAD
		static PrologEngine ^ CreateThread();
#endif

        static property PrologEngine ^ MainThread {
			PrologEngine ^ get() { return mainThread; }
        }
    };

}