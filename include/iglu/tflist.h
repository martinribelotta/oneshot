/*
 * IGLU Iterfaz Grafica Libre del Usuario.
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
#ifndef _iglu_TFileList_h
#define _iglu_TFileList_h

#include <iglu/callback.h>
#include <iglu/tlistbox.h>

class TFileList: public TListBox {
public:
  char *ext;
  char path[80];
  TCallBack *OnSelectFile;

  TFileList (TRect& r, char *_ext=NULL);
  ~TFileList ();

  virtual void HandleEvent (TEvent& e);

  virtual void doOnSelectFile ();
  virtual void doOnChangeDir ();

  char *getabsolute (); // Select name
  char *getabsolute (int n); // on especific point
  char *getabsolute (char *s); // concatenate path+s
  char *getfilename ();

  void scandir ();
  int passFilt (char *name);
};

#endif
