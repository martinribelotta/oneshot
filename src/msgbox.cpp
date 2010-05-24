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
#include <iglu/msgbox.h>
#include <iglu/twindow.h>
#include <iglu/screen.h>
#include <iglu/tprogram.h>
#include <stdarg.h>
#include <stdio.h>

#define StdBtnW   80
#define StdBtnH   24

int MessageBox(const char *fmt, ...)
{
  va_list arg_ptr;
  va_start(arg_ptr, fmt);

  char msg[256];
  TRect a, r;
  Application->getClientArea (a);
  r = TRect (0,0,a.deltax()>>1, a.deltay()/3);
  r.centeron (a, 1);

  vsprintf(msg, fmt, arg_ptr);
  MessageBoxRect(r, msg);
  va_end(arg_ptr);
  return 0;
}

int MessageBoxRect(TRect& r, const char *msg)
{
  TWindow *w = new TWindow(r, "Message");
  if (w) {
    TRect b, cr;
    w->Align = vaFixedSize;
    w->getClientArea (cr);
    w->insert(new TLabel(Rect(0,0,cr.deltax(), cr.deltay()),
		  (char*)msg, EGA_BLACK, EGA_LIGHTGRAY));
    b = TRect(0,0,80,24);
    b.moverel(cr.deltax()/2-40, cr.deltay()-30);
    w->insert(new TTextButton(b, "Ok", cmCancel));

    w->Show();
    Application->ExecView(w);
    delete w;
  }
  return 0;
}
