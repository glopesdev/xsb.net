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

#include "cinterf.h"
#include "thread_defs_xsb.h"

typedef xsbBool (*prolog_callback)(prolog_term arg);

#ifdef MULTI_THREAD
static prolog_callback managed_callback[MAX_THREADS];
#define MANAGED_CALLBACK managed_callback[xsb_get_thread_entry(xsb_thread_id)]
#else
static prolog_callback managed_callback = 0;
#define MANAGED_CALLBACK managed_callback
#endif

DllExport void call_conv set_managed_callback(CTXTdeclc prolog_callback callback)
{
    MANAGED_CALLBACK = callback;
}

DllExport xsbBool call_conv managed(CTXTdecl)
{
    prolog_term arg = reg_term(CTXTc 1);
    if (MANAGED_CALLBACK != 0) return (*(MANAGED_CALLBACK))(arg);
    return 0;
}
