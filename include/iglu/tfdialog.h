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
#ifndef igluTFileDialog_h
#define igluTFileDialog_h

#include <iglu/twindow.h>
#include <iglu/tflist.h>
#include <iglu/tinput.h>
#include <iglu/tbutton.h>

class TFileDialog: public TWindow {
public:
  TFileList *filelist;
  TInputLine *filename;
  TCallBack *cb1;
  TTextButton *bOk, *bCancel;
  int isok;

  TFileDialog (const char *title, const char *ext);
  ~TFileDialog ();
  virtual void MessageEvent (TEvent& e);
};

#endif /* igluTFileDialog_h */
