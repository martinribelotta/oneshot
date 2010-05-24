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
#include <iglu/tlabel.h>
#include <string.h> // Only for strdup
#include <stdlib.h> // Omly for free

TLabel::TLabel (TRect& r, const char *s, int fore, int back):
  TView(r), caption(strdup(s)), fg(fore), bg(back)
{
  State &=~stFocusheable;
}

TLabel::~TLabel ()
{
  free(caption);
}

void TLabel::SetText (const char *s)
{
  free(caption);
  caption = strdup(s);
  doDraw();
}

void TLabel::Draw ()
{
  int i, p=0 , n=8;
  char s[256];
  if (bg>=0)
    gui_drawrectfill(Bounds, bg);
  while (caption[p]) {
    i=0;
    do {
      s[i++] = caption[p];
    } while (caption[p] && (caption[p++]!= '\n'));
    s[i-1] = 0;
    gui_outtextxy (Bounds.a.x+Bounds.deltax()/2,Bounds.a.y+n,s,1,fg,-1);
    n+=gui_texth(caption)+2;
  }
}
