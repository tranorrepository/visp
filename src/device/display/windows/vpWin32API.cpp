/****************************************************************************
 *
 * $Id$
 *
 * This file is part of the ViSP software.
 * Copyright (C) 2005 - 2013 by INRIA. All rights reserved.
 * 
 * This software is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * ("GPL") version 2 as published by the Free Software Foundation.
 * See the file LICENSE.txt at the root directory of this source
 * distribution for additional information about the GNU GPL.
 *
 * For using ViSP with software that can not be combined with the GNU
 * GPL, please contact INRIA about acquiring a ViSP Professional 
 * Edition License.
 *
 * See http://www.irisa.fr/lagadic/visp/visp.html for more information.
 * 
 * This software was developed at:
 * INRIA Rennes - Bretagne Atlantique
 * Campus Universitaire de Beaulieu
 * 35042 Rennes Cedex
 * France
 * http://www.irisa.fr/lagadic
 *
 * If you have questions regarding the use of this file, please contact
 * INRIA at visp@inria.fr
 * 
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *
 * Description:
 * GDI renderer for windows 32 display
 *
 * Authors:
 * Filip Novotny
 *
 *****************************************************************************/

#include <visp/vpConfig.h>
#include <visp/vpWin32API.h>
#include <visp/vpTime.h>
#include <iostream>

#if ( defined(VISP_HAVE_GDI) || defined(VISP_HAVE_D3D9) )
DWORD vpProcessErrors(const std::string &api_name){
  LPVOID lpMsgBuf;
  DWORD err = GetLastError();
  
  FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        err,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );
  std::cout << "call to " << api_name << " failed with the following error code: " << err << "(" << (LPTSTR)lpMsgBuf << ")" << std::endl;
  return err;
}

BOOL vpLineTo(HDC hdc, int nXEnd, int nYEnd){
  BOOL ret = LineTo(hdc, nXEnd, nYEnd);
  if(ret == 0)
    vpProcessErrors("LineTo");
  return ret;
}

BOOL vpMoveToEx(HDC hdc, int X, int Y, LPPOINT lpPoint){
  BOOL ret = MoveToEx(hdc, X, Y, lpPoint);
  if(ret == 0)
    vpProcessErrors("MoveToEx");
  return ret;
}

BOOL vpBitBlt(HDC hdcDest, int nXDest, int nYDest, int nWidth, int nHeight, HDC hdcSrc, int nXSrc, int nYSrc, DWORD dwRop){
  BOOL ret = BitBlt(hdcDest,nXDest,nYDest, nWidth, nHeight, hdcSrc, nXSrc, nYSrc, dwRop);
  if(ret == 0)
    vpProcessErrors("BitBlt");
  return ret;
}

BOOL vpInvalidateRect(HWND hWnd, const RECT *lpRect, BOOL bErase){
  BOOL ret = InvalidateRect(hWnd,lpRect,bErase);  
  if(ret == 0)
    vpProcessErrors("InvalidateRect");
  return ret;
}

void vpSelectObject(HWND hWnd, HDC hDC, HDC hDCMem, HGDIOBJ h){
  
  HGDIOBJ ret = SelectObject(hDCMem,h);  
  if(ret==NULL){
    vpProcessErrors("SelectObject");
        
    double ms = vpTime::measureTimeMs();

    while(ret==NULL && vpTime::measureTimeMs()-ms<5000){
      DeleteObject(h);
      DeleteDC(hDCMem);
      ReleaseDC(hWnd, hDC);
    }
  }    
}

BOOL vpReleaseSemaphore(HANDLE hSemaphore,LONG IReleaseCount,LPLONG lpPreviousCount){
  BOOL ret = ReleaseSemaphore(hSemaphore,IReleaseCount,lpPreviousCount);
  if(ret==0){
    vpProcessErrors("ReleaseSemaphore");
  }
  return ret;
  
}

void vpEnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection){
  EnterCriticalSection(lpCriticalSection);
}
void vpLeaveCriticalSection(LPCRITICAL_SECTION lpCriticalSection){
  LeaveCriticalSection(lpCriticalSection);
}

COLORREF vpSetPixel(HDC hdc, int X, int Y, COLORREF crColor){
  COLORREF ret = SetPixel(hdc, X, Y, crColor);
  if(ret == 0)
    vpProcessErrors("SetPixel");
  return ret;
}

HBITMAP vpCreateBitmap(int nWidth, int nHeight, UINT cPlanes, UINT cBitsPerPel, const VOID *lpvBits){
  HBITMAP ret = CreateBitmap(nWidth, nHeight, cPlanes, cBitsPerPel, lpvBits);
  if (ret==NULL)
    vpProcessErrors("CreateBitmap");

  return ret;
}

#endif
