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
#include "PrologTermTests.h"

void XsbDotNet::UnitTests::PrologTermTests::SetUp()
{
    engine = gcnew XsbDotNet::XsbPrologEngine();
    //engine = XsbDotNet::XsbPrologEngine::Instance;
}

void XsbDotNet::UnitTests::PrologTermTests::TearDown()
{
    XsbDotNet::XsbPrologEngine::CloseXsb();
}

void XsbDotNet::UnitTests::PrologTermTests::PrologTermConstructors()
{
    XsbDotNet::PrologTerm ^variable = engine->CreateTerm();
    Assert(variable->IsVariable());

    XsbDotNet::PrologTerm ^fact = engine->CreateTerm("test");
    Assert(fact->IsAtom());
    Assert(fact->GetAtomName() == "test");

    XsbDotNet::PrologTerm ^term = engine->CreateTerm("test", 2);
    Assert(term->IsFunctor());
    Assert(term->GetFunctorName() == "test");
    Assert(term->GetFunctorArgument(2)->IsVariable());
}

void XsbDotNet::UnitTests::PrologTermTests::PrologTermBindings()
{
    XsbDotNet::PrologTerm ^term = engine->CreateTerm();
    term->BindInt(5);
    Assert(term->GetIntValue() == 5);
}

void XsbDotNet::UnitTests::PrologTermTests::PrologCommands()
{
    XsbDotNet::PrologTerm ^term = engine->CreateTerm("ensure_loaded", 1);
    term->GetFunctorArgument(1)->BindAtom("basics");
    bool res = engine->Command(term);
}

void XsbDotNet::UnitTests::PrologTermTests::PrologQueries()
{
    engine->Command("ensure_loaded(basics).");
    QueryHandle ^result = engine->Query("member(X,[1,2,3]).");
    for each (XsbDotNet::PrologAnswer ^answer in result)
    {
        System::Console::Out->WriteLine(answer->AnswerTerm->GetFunctorArgument(1)->GetIntValue());
    }
}

bool PrologDelegatedCall(cli::array<XsbDotNet::PrologTerm ^> ^arguments)
{
    if (arguments->Length != 0)
    {
        return true;
    }
    else return false;
}

void XsbDotNet::UnitTests::PrologTermTests::PrologCallbacks()
{
    engine->RegisterManagedPredicate("sharp_code", gcnew PrologPredicate(PrologDelegatedCall));
    bool ret = engine->Command("managed(sharp_code(5)).");
}