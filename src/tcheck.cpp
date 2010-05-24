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

#include <iglu/tcheck.h>
#include <iglu/screen.h>

extern char checkpal[], *icon_check, *icon_nocheck,
			*icon_radioon, *icon_radiooff;

void TCheckBox::DrawState (int)
{
  int centery = Bounds.a.y+Bounds.deltay()/2-Ht/2;
  gui_drawpixmap (Bounds.a.x+2, centery, 8, 8,
		  (checked)? icon_check:icon_nocheck, checkpal);
  gui_outtextxy (Bounds.a.x+12, centery, caption, 0, EGA_BLACK, -1);
}

void TCheckBox::Assert (TEvent& ) { checked = !checked; doDraw(); }

/********************************************************************/

void TRadioBox::DrawState (int)
{
  int centery = Bounds.a.y+Bounds.deltay()/2-Ht/2;
  gui_drawpixmap (Bounds.a.x+2, centery, 8, 8,
		  isSelect()? icon_radioon:icon_radiooff, checkpal);
  gui_outtextxy (Bounds.a.x+12, centery, caption, 0, EGA_BLACK, -1);
}

void TRadioBox::Assert (TEvent&)
{

}


