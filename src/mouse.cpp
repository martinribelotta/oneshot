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

#include <iglu/mouse.h>
//#include <dos.h>

/* Driver del raton a bajo nivel... cuerto!!! esto me voy a sacar
 * el gusto de escrivirlo en ensamblador!!!! (aunque el codigo que
 * esta comentado por ahi genera el mismo resultado :-(((( )
 */

void gui_mouse_show ()
{
  asm mov ax, 0x01
  asm int 0x33
//  _AX = 1;
//  geninterrupt( 0x33 );
}

void gui_mouse_hide ()
{
  asm mov ax, 0x02
  asm int 0x33
//  _AX = 2;
//  geninterrupt( 0x33 );
}

void gui_mouse_init ()
{
  /* reset mouse */
  asm xor ax,ax
  asm int 0x33
//  _AX = 0;
//  geninterrupt( 0x33 );
}

void gui_mouse_done ()
{
  /* reset mouse */
  asm xor ax,ax
  asm int 0x33
//  _AX = 0;
//  geninterrupt( 0x33 );
}
