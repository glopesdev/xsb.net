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

using namespace System::Collections::Generic;

#include "PrologAnswer.h"

namespace XsbDotNet {

    public ref class QueryHandle
        : public IEnumerable<PrologAnswer ^>
    {
    private:
        ref class PrologAnswerEnumerator
            : public IEnumerator<PrologAnswer ^>
        {
        private:
#ifdef MULTI_THREAD
            th_context *th;
#endif
            PrologAnswer ^current;
            QueryHandle ^query;
        public:
            PrologAnswerEnumerator(CTXTdeclc QueryHandle ^query):
#ifdef MULTI_THREAD
              th(th),
#endif
              query(query) { }
            virtual ~PrologAnswerEnumerator() { }
            virtual property PrologAnswer ^ Current {
                PrologAnswer ^ get() {
                    return current;
                }
            }
            virtual Object ^ get_CurrentNonGeneric() = System::Collections::IEnumerator::Current::get {
                return current;
            }
            virtual bool MoveNext();
            virtual void Reset() { }
        };
    private:
#ifdef MULTI_THREAD
        th_context *th;
#endif
        bool succeeded;
        bool closed;
        PrologAnswerEnumerator ^answers;
    internal:
        QueryHandle(CTXTdeclc bool succeeded);
    public:
        property bool Succeeded {
            bool get() { return succeeded; }
        }
        property bool Closed {
            bool get() { return closed; }
        }
        void Close();
        virtual IEnumerator<PrologAnswer ^> ^ GetEnumerator() {
            return answers;
        }
        virtual System::Collections::IEnumerator ^ GetEnumeratorNonGeneric() = System::Collections::IEnumerable::GetEnumerator {
            return answers;
        }
    };    

}