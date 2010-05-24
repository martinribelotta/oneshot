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
#ifndef _igluTListBox_h
#define _igluTListBox_h

#include <iglu/tview.h>
#include <iglu/tbutton.h>
#include <iglu/tlist.h>
#include <iglu/tscroll.h>

class TListBox: public TView {
protected:
  TList *list;
  TScroll *bar;
  int topitem, bottomitem, flags;

  void calculateparams ();

  void drawitems ();
  void drawdecorate ();
  void dodrawitems ();
  void dodrawdecorate ();
public:
  int pos, height_item;
  void (*onSelect) (TPoint& pos, TListBox *list);

  TListBox (TRect& r);
  ~TListBox ();

  void selectn (int n);

  inline int nitems () { return list->count; }

  virtual void Draw ();
  virtual void HandleEvent (TEvent& e);
  virtual void moverel(int dx, int dy);
  virtual void RecuestAlign (TRect& o, TRect& n);
  virtual void getClientArea (TRect& r, int absolute);

  virtual void GotFocus ();
  virtual void LostFocus ();

  void additem (char *name, TObject *obj=NULL);
  int finditem (char *name);

  char *getn(int n) { return list->getname (n); }

  void clearlist ();
};

#endif /* _igluTListBox_h */
