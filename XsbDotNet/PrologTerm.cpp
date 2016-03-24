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
#include "PrologTerm.h"

using namespace XsbDotNet;
using namespace System::Runtime::InteropServices;

PrologTerm::PrologTerm(CTXTdeclc prolog_term term):
#ifdef MULTI_THREAD
th(th),
#endif
term(term)
{
}

void PrologTerm::BindInt(int integer)
{
    c2p_int(CTXTc integer, term);
}

void PrologTerm::BindDouble(double decimal)
{
    c2p_float(CTXTc decimal, term);
}

void PrologTerm::BindAtom(System::String ^symbol)
{
    System::IntPtr cstring = Marshal::StringToHGlobalAnsi(symbol);
    c2p_string(CTXTc (char *)cstring.ToPointer(), term);
    Marshal::FreeHGlobal(cstring);
}

void PrologTerm::BindFunctor(System::String ^symbol, int arity)
{
    System::IntPtr cstring = Marshal::StringToHGlobalAnsi(symbol);
    int res = c2p_functor(CTXTc (char *)cstring.ToPointer(), arity, term);
    Marshal::FreeHGlobal(cstring);
}

void PrologTerm::BindList()
{
    c2p_list(CTXTc term);
}

void PrologTerm::BindNil()
{
    c2p_nil(CTXTc term);
}

bool PrologTerm::Unify(PrologTerm ^term)
{
    return p2p_unify(CTXTc this->term, term->term) != 0;
}

bool PrologTerm::IsVariable()
{
    return is_var(term) != 0;
}

bool PrologTerm::IsInt()
{
    return is_int(term) != 0;
}

bool PrologTerm::IsFloat()
{
    return is_float(term) != 0;
}

bool PrologTerm::IsString()
{
    return is_string(term) != 0;
}

bool PrologTerm::IsAtom()
{
    return is_atom(term) != 0;
}

bool PrologTerm::IsList()
{
    return is_list(term) != 0;
}

bool PrologTerm::IsNil()
{
    return is_nil(term) != 0;
}

bool PrologTerm::IsFunctor()
{
    return is_functor(term) != 0;
}

bool PrologTerm::IsCharList()
{
    int list_size;
    return is_charlist(term, &list_size) != 0;
}

bool PrologTerm::IsAttributedVariable()
{
    return is_attv(term) != 0;
}

System::String ^ PrologTerm::GetFunctorName()
{
    return gcnew System::String(p2c_functor(term));
}

int PrologTerm::GetFunctorArity()
{
    return p2c_arity(term);
}

PrologTerm ^ PrologTerm::GetFunctorArgument(int index)
{
    return gcnew PrologTerm(CTXTc p2p_arg(term, index));
}

PrologTerm ^ PrologTerm::GetListHead()
{
    return gcnew PrologTerm(CTXTc p2p_car(term));
}

PrologTerm ^ PrologTerm::GetListTail()
{
    return gcnew PrologTerm(CTXTc p2p_cdr(term));
}

int PrologTerm::GetIntValue()
{
    return p2c_int(term);
}

double PrologTerm::GetDoubleValue()
{
    return p2c_float(term);
}

System::String ^ PrologTerm::GetAtomName()
{
    return gcnew System::String(p2c_string(term));
}