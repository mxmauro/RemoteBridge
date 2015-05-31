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

#pragma once

#include "..\RemoteBridgeHelper.h"
#include "..\..\Common\LinkedList.h"
#include "..\..\Common\WaitableObjects.h"

//-----------------------------------------------------------

namespace COM {

class CGuidList : private CNktFastMutex
{
public:
  CGuidList();
  ~CGuidList();

  HRESULT Add(__in REFGUID sGuid);
  HRESULT Remove(__in REFGUID sGuid);
  VOID RemoveAll();

  BOOL GetAt(__in SIZE_T nIndex, __out GUID &sGuid);

  BOOL Check(__in REFGUID sGuid);

private:
  SIZE_T Find(__in REFGUID sGuid);

private:
  GUID *lpList;
  SIZE_T nCount, nSize;
};

} //COM
