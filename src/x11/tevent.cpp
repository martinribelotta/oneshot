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
#include <iglu/tevent.h>
#include <iglu/tprogram.h>
#include <time.h>
#include <X11/Xlib.h>

extern Display *dis;
extern Window win;

static int oldb=0;
static clock_t tick_actual=0, tick_anterior=0;

void TEvent::GetEvent()
{
  type = 0;
  tick_actual = clock();
  if (tick_actual>tick_anterior)
    type |= evTimerOut;
  if (XPending(dis)) {
    XEvent e;
    XNextEvent(dis, &e);
    switch (e.type) {
	case Expose: {
	  TRect exposeArea (
		e.xgraphicsexpose.x,
		e.xgraphicsexpose.y,
		e.xgraphicsexpose.x+e.xgraphicsexpose.width,
		e.xgraphicsexpose.y+e.xgraphicsexpose.height);
	  Application->RedrawRect(exposeArea);
	  break; }
	case ButtonPress:
	  type |= evMouseDown;
	  oldb = btn;
	  btn = e.xbutton.button;
	  pos.assign(e.xbutton.x, e.xbutton.y);
	  break;
	case ButtonRelease:
	  type |= evMouseUp;
	  oldb = 0;
	  btn = e.xbutton.button;
	  pos.assign(e.xbutton.x, e.xbutton.y);
	  break;
	case MotionNotify:
	  type |= evMouseMove;
	  btn = oldb;
	  pos.assign(e.xmotion.x, e.xmotion.y);
	  break;
	case KeyPress:
	  type |= evKeyDown;
	  keycode = XKeycodeToKeysym(dis, e.xkey.keycode, 0);
	break;
    }
  }
  tick_anterior = tick_actual;
}
