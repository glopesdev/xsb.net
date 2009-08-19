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

using namespace System::Runtime::InteropServices;

namespace XsbDotNet {

    namespace UnitTests {

        public ref class PrologTermTests
        {
        private:
            XsbDotNet::PrologEngine ^engine;
        public:
            void SetUp();
            void TearDown();
            void PrologTermConstructors();
            void PrologTermBindings();
            void PrologCommands();
            void PrologQueries();
            void PrologCallbacks();
        private:
            void Assert(bool condition) {
                if (!condition) throw gcnew System::Exception("Assertion failed!");
            }
        };

    }

}
