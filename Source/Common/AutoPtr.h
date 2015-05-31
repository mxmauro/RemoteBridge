/*
 * Copyright (C) 2010-2015 Nektra S.A., Buenos Aires, Argentina.
 * All rights reserved. Contact: http://www.nektra.com
 *
 *
 * This file is part of Remote Bridge
 *
 *
 * Commercial License Usage
 * ------------------------
 * Licensees holding valid commercial Remote Bridge licenses may use this
 * file in accordance with the commercial license agreement provided with
 * the Software or, alternatively, in accordance with the terms contained
 * in a written agreement between you and Nektra.  For licensing terms and
 * conditions see http://www.nektra.com/licensing/. Use the contact form
 * at http://www.nektra.com/contact/ for further information.
 *
 *
 * GNU General Public License Usage
 * --------------------------------
 * Alternatively, this file may be used under the terms of the GNU General
 * Public License version 3.0 as published by the Free Software Foundation
 * and appearing in the file LICENSE.GPL included in the packaging of this
 * file.  Please visit http://www.gnu.org/copyleft/gpl.html and review the
 * information to ensure the GNU General Public License version 3.0
 * requirements will be met.
 *
 **/

#ifndef _NKT_AUTOPTR_H
#define _NKT_AUTOPTR_H

#include <windows.h>
#include <crtdbg.h>
#include <intrin.h>
#include "MallocMacros.h"

//-----------------------------------------------------------

template <class T>
class TNktAutoPtrBase
{
public:
  TNktAutoPtrBase()
    {
    lpPtr = NULL;
    return;
    };

  TNktAutoPtrBase(__in T* _lpPtr)
    {
    lpPtr = _lpPtr;
    return;
    };

  T* Get()
    {
    return lpPtr;
    };

  VOID Reset()
    {
    if (lpPtr != NULL)
    {
      Delete(lpPtr);
      lpPtr = NULL;
    }
    return;
    };

  operator T*() const
    {
    return lpPtr;
    };

  T& operator*() const
    {
    _ASSERT(lpPtr != NULL);
    return *lpPtr;
    };

  //The assert on operator& usually indicates a bug.  If this is really
  //what is needed, however, take the address of the lpPtr member explicitly.
  T** operator&()
    {
    _ASSERT(lpPtr == NULL);
    return &lpPtr;
    };

  T* operator->() const
    {
    _ASSERT(lpPtr != NULL);
    return lpPtr;
    };

  T* operator=(__in T* _lpPtr)
    {
    if (_lpPtr != lpPtr)
      Attach(_lpPtr);
    return _lpPtr;
    };

  BOOL operator!() const
    {
    return (lpPtr == NULL) ? TRUE : FALSE;
    };

  BOOL operator==(__in T* _lpPtr) const
    {
    return (lpPtr == _lpPtr) ? TRUE : FALSE;
    };

  VOID Attach(__in T* _lpPtr)
    {
    if (lpPtr != NULL)
      Delete(lpPtr);
    lpPtr = _lpPtr;
    return;
  };

  T* Detach()
    {
    T* _lpPtr = lpPtr;
    lpPtr = NULL;
    return _lpPtr;
    };

protected:
  virtual VOID Delete(__inout T *lpObj)=0;

protected:
  T *lpPtr;
};

//-----------------------------------------------------------

template <class T>
class TNktAutoFreePtr : public TNktAutoPtrBase<T>
{
public:
  TNktAutoFreePtr() : TNktAutoPtrBase<T>()
    {
    return;
    };

  ~TNktAutoFreePtr()
    {
    if (lpPtr != NULL)
      Delete(lpPtr);
    };

protected:
  VOID Delete(__inout T *lpObj)
    {
    NKT_FREE(lpObj);
    return;
    };
};

//-----------------------------------------------------------

template <class T>
class TNktAutoDeletePtr : public TNktAutoPtrBase<T>
{
public:
  TNktAutoDeletePtr() : TNktAutoPtrBase<T>()
    {
    return;
    };

  ~TNktAutoDeletePtr()
    {
    if (lpPtr != NULL)
      Delete(lpPtr);
    return;
    };

protected:
  VOID Delete(__inout T *lpObj)
    {
    delete lpObj;
    return;
    };
};

//-----------------------------------------------------------

template <class T>
class TNktAutoDeleteArrayPtr : public TNktAutoPtrBase<T>
{
public:
  TNktAutoDeleteArrayPtr() : TNktAutoPtrBase<T>()
    {
    return;
    };

  ~TNktAutoDeleteArrayPtr()
    {
    if (lpPtr != NULL)
      Delete(lpPtr);
    return;
    };

protected:
  VOID Delete(__inout T *lpObj)
    {
    delete [] lpObj;
    return;
    }
};

//-----------------------------------------------------------

#endif //_NKT_AUTOPTR_H
