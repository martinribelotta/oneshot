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
#include <iglu/tprogram.h>
#include <iglu/mousehdl.h>
#include <stdio.h>
#include <stdlib.h>

TProgram *Application = NULL;

void OutOfMemory()
{
  doneGUI();
  puts("Out of memory");
  exit(2);
}

void *operator new (size_t size)
{
  void *ptr;
  ptr = malloc (size);
  if (size && !ptr)
    OutOfMemory ();
  return ptr;
}

TProgram::TProgram(int /*argc*/, char **/*argv*/, int _bg):
  TGroup(Rect(0,0,0,0)), bg(_bg)
{
  if (!Application)
    Application = this;
  initGUI();
  gui_getclip(Bounds);
}

TProgram::~TProgram()
{
  doneGUI();
}

void TProgram::SelectNext(int prv)
{
  TView *tmp = base;
  while (tmp) {
    if (tmp->State&stFocus)
      break;
    tmp=tmp->next;
  }
  if (tmp) {
    if (prv) tmp=tmp->prev;
    else tmp=tmp->next;
    if (tmp)
      tmp->GotFocus();
    else if (base)
      base->GotFocus();
  }
}

void TProgram::MessageEvent(TEvent& e)
{
  if ((e.type&evBroadcast) && (e.msg.message==cmQuit))
    SetState(stModal, 0);
}

void TProgram::KeyEvent(TEvent& e)
{
  TGroup::KeyEvent(e);
  if ((e.keycode&0xff) == '\t')
      SelectNext();
  if (e.keycode==0x0E7F) {
    TMessage m ((int)cmQuit, this, 0L);
    EventManager.SendMessage(m);
  }
}

int TProgram::mainLoop()
{
  Draw();
  SetState(stModal, 1);
  Execute();
  return 0;
}

void TProgram::Draw()
{
  gui_drawrectfill(Bounds, bg);
  TGroup::Draw ();
}
