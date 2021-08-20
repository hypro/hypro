/* thread.h (pthread emulation for Windows) */

/***********************************************************************
 *  This code is part of GLPK (GNU Linear Programming Kit).
 *  Copyright (C) 2011-2017 Free Software Foundation, Inc.
 *  Written by Heinrich Schuchardt <xypron.glpk@gmx.de>.
 *
 *  GLPK is free software: you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  GLPK is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 *  License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with GLPK. If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************/

#ifndef THREAD_H

#define THREAD_H 1

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif	// HAVE_CONFIG_H

#ifdef __WOE__
#include <windows.h>
typedef CRITICAL_SECTION pthread_mutex_t;
typedef HANDLE pthread_t;
// @todo The return type of routine C is "DWORD" for Windows and
//       "void *" for Posix.
#define pthread_create( A, B, C, D ) \
	(int)( ( *A = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)&C, D, 0, NULL ) ) == NULL )
#define pthread_exit( A ) ExitThread( 0 )
#define pthread_mutex_destroy( A ) DeleteCriticalSection( A )
#define pthread_mutex_init( A, B ) ( InitializeCriticalSection( A ), 0 )
#define pthread_mutex_lock( A ) ( EnterCriticalSection( A ), 0 )
#define pthread_mutex_unlock( A ) ( LeaveCriticalSection( A ), 0 )
#define pthread_self() GetCurrentThreadId()
#define pthread_join( A, B ) \
	( WaitForSingleObject( A, INFINITE ), CloseHandle( A ), 0 )
#else
#include <pthread.h>
#endif

#endif	// THREAD_H
