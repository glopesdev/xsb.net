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

namespace XsbDotNet {

    public ref class PrologTerm
    {
    private:
#ifdef MULTI_THREAD
        th_context *th;
#endif
        prolog_term term;
    internal:
        PrologTerm(CTXTdeclc prolog_term term);
        property prolog_term Term {
            prolog_term get() { return term; }
        }
    public:
        void BindInt(int integer);
        void BindDouble(double decimal);
        void BindAtom(System::String ^symbol);
        void BindFunctor(System::String ^symbol, int arity);
        void BindList();
        void BindNil();
        bool Unify(PrologTerm ^term);

        bool IsVariable();
        bool IsInt();
        bool IsFloat();
        bool IsString();
        bool IsAtom();
        bool IsList();
        bool IsNil();
        bool IsFunctor();
        bool IsCharList();
        bool IsAttributedVariable();

        System::String ^ GetFunctorName();
        int GetFunctorArity();
        PrologTerm ^ GetFunctorArgument(int index);

        PrologTerm ^ GetListHead();
        PrologTerm ^ GetListTail();

        int GetIntValue();
        double GetDoubleValue();
        System::String ^ GetAtomName();
    };

}
