/*
 * IGLU Iterfaz Grafica Libre del Usuario. (libre de usuarios) (Graphics user interface "free of users")
 * Copyright (C) 2005 Martin Alejandro Ribelotta
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <iglu/tflist.h>
#ifdef __TURBOC__
#include <direct.h>
#else
#include <unistd.h>
#endif
#include <string.h>
#include <dirent.h>
#include <ctype.h>

static char *uniformpath (char *s) {
  int i;
  if (s[1]==':') // if contain driver info
    for (i=1; s[i]; i++)
      s[i-1] = s[i+1];
  for (i=0; s[i]; i++)
    if (s[i]=='\\') // Replace backslash for "unix style bar"
      s[i]='/';
  return s;
}

static void my_getcwd (char *b, int l)
{
  getcwd (b, l);
  uniformpath (b);
}

int isDir (char *s) {
  int r=0;
  char olddir[256];
  my_getcwd (olddir, 255);
  if (chdir (s)==0) {
    r = 1;
    chdir (olddir);
  }
  return r;
}

/*********************************************************************/

TFileList::TFileList (TRect& r, char *_ext): TListBox (r), ext(_ext)
{
  my_getcwd (path, 80);
  OnSelectFile = NULL;
  scandir ();
}

TFileList::~TFileList ()
{
}

char *TFileList::getabsolute ()
{
  return getabsolute (pos);
}

char *TFileList::getfilename ()
{
  return getn (pos);
}

char *TFileList::getabsolute (int n)
{
  return getabsolute (getn(n));
}

char *TFileList::getabsolute (char *s)
{
  char c[2];
  static char b[80];
  c[0] = '/'; c[1] = 0;
  strcpy (b, path);
  if (!((path[0]=='/') && path[1]==0))
    strcat (b, c);
  strcat (b, s);
  return &b[0];
}

void TFileList::HandleEvent (TEvent& e)
{
  int oldpos=pos;
  TListBox::HandleEvent (e);
  if (oldpos!=pos)
    doOnSelectFile ();
  TRect a;
  getClientArea (a, 1);
  if ((e.type&evMouseUp) && a.contain (e.pos))
    doOnChangeDir ();
}

void TFileList::doOnSelectFile ()
{
  char tmp[80], *dir;
  my_getcwd (tmp, 80);    // Guardar el path actual.
  dir = getabsolute ();   // Tomar el nombre como absoluto al path
  if (chdir (dir)==0) {   // intentar cambiar el directorio.
    chdir (tmp);          // reestablecer el directorio.
  } else                  // Sino, era archivo regular, llamar selector
    if (OnSelectFile)     // (sy hay callback)
      OnSelectFile->do_callback (this);
}

void TFileList::doOnChangeDir ()
{
  char tmp[80], *dir;
  my_getcwd (tmp, 80);    // Guardar el path actual.
  dir = getabsolute ();   // Tomar el nombre como absoluto al path
  if (chdir (dir)==0) {   // intentar cambiar el directorio.
    my_getcwd (path, 80); // si se pudo, era directorio, reescanearlo.
    chdir (tmp);
    scandir ();
    doDraw ();
  }
}

void TFileList::scandir ()
{
  char olddir[256];
  DIR *d;
  clearlist ();
  my_getcwd (olddir, 255);
  chdir (path);
  d = opendir (path);
  if (d) {
    struct dirent *ent;
    rewinddir (d);
    while ((ent=readdir(d))!=NULL)
      if (passFilt (ent->d_name))
	additem (ent->d_name);
    closedir (d);
  }
  chdir (olddir);
}

int TFileList::passFilt (char *s)
{
  // TODO: Que esto sea por regExp (como *.*)
  int equ = 1;
  if (!isDir (s) && ext) {
    char *se=ext, *e = strrchr (s, '.');
    if ( !e )
      e = "";
    while (equ && *e && *se)
      if (tolower(*e++)!=tolower(*se++))
	equ=0;
    return *e == *se;
    return 0;
  }
  return equ;
}
