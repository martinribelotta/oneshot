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
#ifndef _igluTProgram_h
#define _igluTProgram_h

#include <iglu/tview.h>
#include <iglu/screen.h>
#include <stddef.h>

class TProgram: public TGroup { public:
  int bg;
  TProgram(int argc, char **argv, int _bg=EGA_CYAN);
  virtual ~TProgram();
  int mainLoop();
  virtual void KeyEvent(TEvent& e);
  virtual void MessageEvent(TEvent& e);
  virtual void Draw ();

  void SelectNext(int prv=0);
};

extern TProgram *Application;

void *operator new (size_t size);

#define makeStdMain(nameclass)                \
int main (int argc, char **argv) {            \
  int exitcode;                               \
  nameclass *ptr = new nameclass(argc, argv); \
  exitcode = ptr->mainLoop();                 \
  delete ptr;                                 \
  return exitcode;                            \
}

#endif
