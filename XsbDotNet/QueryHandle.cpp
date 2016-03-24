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
#include "QueryHandle.h"

XsbDotNet::QueryHandle::QueryHandle(CTXTdeclc bool succeeded):
#ifdef MULTI_THREAD
th(th),
#endif
succeeded(succeeded),
closed(!succeeded),
answers(nullptr)
{
    answers = gcnew PrologAnswerEnumerator(CTXTc this);
}

void XsbDotNet::QueryHandle::Close()
{
    xsb_close_query(CTXT);
    closed = true;
}

bool XsbDotNet::QueryHandle::PrologAnswerEnumerator::MoveNext()
{            
    if (!query->Closed && (current == nullptr || xsb_next(CTXT) == 0))
    {
        current = gcnew XsbDotNet::PrologAnswer(
            gcnew XsbDotNet::PrologTerm(CTXTc reg_term(CTXTc 1)),
            gcnew XsbDotNet::PrologTerm(CTXTc reg_term(CTXTc 2))
        );
        return true;
    }
    else 
    {
        query->Close();
        return false;
    }
}