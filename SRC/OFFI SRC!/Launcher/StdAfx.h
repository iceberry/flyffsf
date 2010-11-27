// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__CAAD281D_A9EB_491C_B445_131A9C0B13D2__INCLUDED_)
#define AFX_STDAFX_H__CAAD281D_A9EB_491C_B445_131A9C0B13D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#define	_WIN32_WINNT	0x0500
#define	WINVER		0x0500

#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <iostream>
#include <mmsystem.h>
//#include "compile.h"
#include "cmnhdr.h"

#include "MemTrace.h"
#include "XUtil.h"

#include "dxutil.h"
#include "data.h"
#include "file.h"
#include "scanner.h"
#include "timer.h"
#include "vutil.h"
#include "targa.h"
#include "debug.h"

#include <list>
using	namespace	std;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__CAAD281D_A9EB_491C_B445_131A9C0B13D2__INCLUDED_)