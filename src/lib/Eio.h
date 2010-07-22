/* EIO - EFL data type library
 * Copyright (C) 2010 Enlightenment Developers:
 *           Cedric Bail <cedric.bail@free.fr>
 *           Vincent "caro" Torri  <vtorri at univ-evry dot fr>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library;
 * if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef EIO_H__
# define EIO_H__

#ifdef _MSC_VER
# include <Evil.h>
#endif

#include <Eina.h>

#ifdef EAPI
# undef EAPI
#endif

#ifdef _WIN32
# ifdef EFL_ECORE_BUILD
#  ifdef DLL_EXPORT
#   define EAPI __declspec(dllexport)
#  else
#   define EAPI
#  endif /* ! DLL_EXPORT */
# else
#  define EAPI __declspec(dllimport)
# endif /* ! EFL_ECORE_BUILD */
#else
# ifdef __GNUC__
#  if __GNUC__ >= 4
#   define EAPI __attribute__ ((visibility("default")))
#  else
#   define EAPI
#  endif
# else
#  define EAPI
# endif
#endif /* ! _WIN32 */

typedef struct _Eio_List Eio_List;

typedef Eina_Bool (*Eio_Filter_Cb)(const char *file, void *data);
typedef void (*Eio_Main_Cb)(const char *file, void *data);

typedef Eina_Bool (*Eio_Filter_Direct_Cb)(const Eina_File_Direct_Info *info, void *data);
typedef void (*Eio_Main_Direct_Cb)(const Eina_File_Direct_Info *info, void *data);

typedef void (*Eio_Done_Cb)(void *data);

EAPI int eio_init(void);
EAPI int eio_shutdown(void);

EAPI Eio_List *eio_file_ls(const char *dir,
				 Eio_Filter_Cb filter,
				 Eio_Main_Cb main,
				 Eio_Done_Cb done,
				 const void *data);

EAPI Eio_List *eio_file_direct_ls(const char *dir,
					Eio_Filter_Direct_Cb filter,
					Eio_Main_Direct_Cb main,
					Eio_Done_Cb done,
					const void *data);

EAPI Eina_Bool eio_file_cancel(Eio_List *list);

#endif
