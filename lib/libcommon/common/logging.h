/*
   eXokernel Development Kit (XDK)

   Based on code by Samsung Research America Copyright (C) 2013
 
   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.

   As a special exception, if you link the code in this file with
   files compiled with a GNU compiler to produce an executable,
   that does not cause the resulting executable to be covered by
   the GNU Lesser General Public License.  This exception does not
   however invalidate any other reasons why the executable file
   might be covered by the GNU Lesser General Public License.
   This exception applies to code released by its copyright holders
   in files containing the exception.  
*/

/*
  Author(s):
  @author Daniel Waddington (d.waddington@samsung.com)
*/

#ifndef __COMMON_LOGGING_H__
#define __COMMON_LOGGING_H__

#include <stdio.h>

#define NORMAL_CYAN "\033[36m"
#define NORMAL_MAGENTA "\033[35m"
#define NORMAL_BLUE "\033[34m"
#define NORMAL_YELLOW "\033[33m"
#define NORMAL_GREEN "\033[32m"
#define NORMAL_RED "\033[31m"

#define BRIGHT "\033[1m"
#define NORMAL "\033[0m"
#define RESET "\033[0m"

#define BRIGHT_CYAN "\033[1m\033[36m"
#define BRIGHT_MAGENTA "\033[1m\033[35m"
#define BRIGHT_BLUE "\033[1m\033[34m"
#define BRIGHT_YELLOW "\033[1m\033[33m"
#define BRIGHT_GREEN "\033[1m\033[32m"
#define BRIGHT_RED "\033[1m\033[31m"

#define WHITE_ON_RED "\033[41m"
#define WHITE_ON_GREEN "\033[41m"

#define ESC_LOG  NORMAL_GREEN
#define ESC_DBG  BRIGHT_CYAN
#define ESC_INF  NORMAL_CYAN
#define ESC_WRN  NORMAL_RED
#define ESC_ERR  BRIGHT_RED
#define ESC_END  "\033[0m"


#define PDBG(f, a...)   fprintf( stderr, "[XDK]: %s:" f "\n",  __func__ , ## a)
#define PLOG(f, a...)   fprintf( stderr, "[XDK]: %s:" f "\n",  __func__ , ## a)
#define PINF(f, a...)   fprintf( stderr, "" f "\n", ## a)
#define PWRN(f, a...)   fprintf( stderr, "[XDK]: %s:" f "\n",  __func__ , ## a)
#define PERR(f, a...)   fprintf( stderr, "[XDK]: ERROR %s:" f "\n",  __func__ , ## a); 


#define TRACE()  fprintf( stderr, "[XDK]: %s\n", __FUNCTION__)

#endif // __COMMON_LOGGING_H__
