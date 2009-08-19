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

#include "StdAfx.h"
#include "XsbPrologEngine.h"
#include "XsbException.h"

using namespace XsbDotNet;
using namespace System::Runtime::InteropServices;

[SuppressUnmanagedCodeSecurity]
[DllImport("managed.dll")]
extern void set_managed_callback(CTXTdeclc PrologCallback ^callback);

XsbPrologEngine::XsbPrologEngine()
{
#ifdef MULTI_THREAD
    if (main_th == NULL)
    {
#endif
        managedPredicates = gcnew Dictionary<System::String ^, PrologPredicate ^>();
        System::String ^xsb_home = System::Environment::GetEnvironmentVariable("XSB_HOME");
        System::IntPtr cstring = Marshal::StringToHGlobalAnsi(xsb_home);
		char *argv[1] = { (char *)cstring.ToPointer() };
		try
		{
			if (xsb_init(1, argv) != XSB_SUCCESS)
			{
				throw gcnew XsbException(
					"Failed to initialize XSB engine.\n" +
					"Error code: " + gcnew System::String(xsb_get_init_error_type()) + "\n" +
					"Error message: " + gcnew System::String(xsb_get_init_error_message()));
			}
		}
		finally { Marshal::FreeHGlobal(cstring); }
#ifdef MULTI_THREAD
        main_th = xsb_get_main_thread();
    }
    pin_ptr<th_context *> p_th = &th;
    xsb_ccall_thread_create(main_th, p_th);
#endif
    Command("ensure_loaded(managed).");
    callback = gcnew PrologCallback(this, &XsbPrologEngine::CallManagedPredicate);
    set_managed_callback(CTXTc callback);
}

#ifdef MULTI_THREAD
XsbPrologEngine::~XsbPrologEngine()
{
    xsb_kill_thread(CTXT);
}
#endif

PrologTerm ^ XsbPrologEngine::CreateTerm()
{
    prolog_term term = p2p_new(CTXT);
    return gcnew PrologTerm(CTXTc term);
}

PrologTerm ^ XsbPrologEngine::CreateTerm(System::String ^symbol)
{
    PrologTerm ^term = CreateTerm();
    term->BindAtom(symbol);
    return term;
}

PrologTerm ^ XsbPrologEngine::CreateTerm(System::String ^symbol, int arity)
{
    PrologTerm ^term = CreateTerm();
    term->BindFunctor(symbol, arity);
    return term;
}

bool XsbPrologEngine::Command(System::String ^command)
{
    System::IntPtr cstring = Marshal::StringToHGlobalAnsi(command);
    int result = xsb_command_string(CTXTc (char *)cstring.ToPointer());
    Marshal::FreeHGlobal(cstring);
    return result == 0;
}

bool XsbPrologEngine::Command(PrologTerm ^command)
{
    prolog_term reg1 = reg_term(CTXTc 1);
    p2p_unify(CTXTc command->Term, reg1);
    return xsb_command(CTXT) == 0;
}

QueryHandle ^ XsbPrologEngine::Query(System::String ^query)
{
    System::IntPtr cstring = Marshal::StringToHGlobalAnsi(query);
    int result = xsb_query_string(CTXTc (char *)cstring.ToPointer());
    Marshal::FreeHGlobal(cstring);
    return gcnew QueryHandle(CTXTc result == 0);
}

QueryHandle ^ XsbPrologEngine::Query(PrologTerm ^query)
{
    prolog_term reg1 = reg_term(CTXTc 1);
    p2p_unify(CTXTc query->Term, reg1);
    return gcnew QueryHandle(CTXTc xsb_query(CTXT) == 0);
}

void XsbPrologEngine::RegisterManagedPredicate(System::String ^name, PrologPredicate ^predicate)
{
    managedPredicates->Add(name, predicate);
}

bool XsbPrologEngine::CallManagedPredicate(prolog_term term)
{
    PrologTerm ^goal = gcnew PrologTerm(CTXTc term);
    System::String ^functor = goal->GetFunctorName();
    int arity = goal->GetFunctorArity();
    PrologPredicate ^predicate = managedPredicates[functor];
    cli::array<PrologTerm ^> ^arguments = gcnew cli::array<PrologTerm ^>(arity);
    for (int i = 0 ; i < arity ; ++i)
    {
        arguments[i] = goal->GetFunctorArgument(i + 1);
    }
    return predicate(arguments);
}

void XsbPrologEngine::CloseXsb()
{
#ifdef MULTI_THREAD
    if (main_th != NULL)
    {
        xsb_close(main_th);
    }
#else
    xsb_close();
#endif
}