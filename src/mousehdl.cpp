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
#include <iglu/mousehdl.h>
#include <iglu/mouse.h>

/*
 * Rutinas del raton de 'alto' (visto con buen ojo) nivel
 */

static int mouse_uses=0; // Contador de visibilidad del raton

// Rutina que maneja la visivilidad del raton. Asi, cuando se lo
// muentra (MouseShow()) y esconde (MouseHide()) varias veces, no
// hay problemas.
// Esta rutina implementa un contador de visibilidad (incrementado con
// st!=0 y decrementado con st==0) que solo muestra el raton cuando la
// cuetna pasa de 0 a 1 y lo oculta cuando pasa de 1 a 0
void setMouseState(int st)
{
  if (st) {
    if (++mouse_uses==1)
      gui_mouse_show ();
  } else
    if (--mouse_uses==0)
      gui_mouse_hide ();
}

void initMouseHandle()
{
  gui_mouse_init (); // Iniciar el controlador del raton
  setMouseState(1); // Mostrarlo
}

void doneMouseHandle()
{
  setMouseState(0); // Ocultarlo
  gui_mouse_done (); // Terminar el controlador del raton.
}
