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
#ifndef _igluTMenu_h
#define _igluTMenu_h

#include <iglu/tview.h>

class TMenuItem: public TObject { public:
  const char *caption;  int sig; TMenuItem *next;
  TMenuItem(const char *s, int c, TMenuItem *n=0L):
    caption(s), sig(c), next(n) { }
  void add(TMenuItem *q) {
    if (next) next->add(q);
    else next=q;
  }
};

class TSubMenu { public:
  const char *caption;  TMenuItem *items; TSubMenu *next;
  TSubMenu(const char *s, TMenuItem *base, TSubMenu *n=0L):
    caption(s), items(base), next(n) { }
  void add(TSubMenu *q) {
    if (next) next->add(q);
    else next=q;
  }
};

class TMenuPopUp: public TView {
  TSubMenu *menu;
  TMenuItem *actual;
public:
  char onpop;

  TMenuPopUp(int x, int y, TSubMenu *submenu);

  virtual void Draw();
  virtual void MouseEvent(TEvent& e);
};

class TMenuBar: public TView {
  TMenuPopUp *pop;
  TSubMenu *menu, *actual;
  int lactual;
public:
  TMenuBar(TRect& r, TSubMenu *sub_menu);
  virtual ~TMenuBar();

  virtual void Draw();
  virtual void MouseEvent(TEvent& e);

  void addmenu(TSubMenu *m) {
    if (menu) menu->add(m);
    else menu=m;
  }

  void PopUp();
  void PopDown();
};

#define mnuSeparatorLine    0

#endif
