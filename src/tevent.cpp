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
#include <iglu/tevent.h>
#include <iglu/mousehdl.h>
#include <iglu/mouse.h>
#include <time.h>

/* Implementacion para DOS del controlador de eventos
 * ...Y sin usar interrupciones!!! (je, que capo no?)
 */

static int mbo, mxo, myo; // Estados anteriores del raton.

static clock_t tick_anterior;

// Funcion, (en ensamblador durito)... que lee el estado del
// raton a travez del servicio 3 de la interrupcion 0x33
static void mouse_read (int *px, int *py, int *pb)
{
  int x,y,b;
  asm mov ax,0x3
  asm int 0x33
  asm mov b, bx
  asm mov x, cx
  asm mov y, dx
  *px = x;
  *py = y;
  *pb = b;
}

// Esto hace lo mismo que kbhit pero como soy malarreado la reescrivi!
static int kbd_ispress ()
{
  asm mov ah,1
  asm int 0x16
  asm jz noKey
  return 1;
noKey:
  return 0;
}

// Esto hace lo mismo que getch pero como soy muy malo (grrrrr) la reescriv.
static int kbd_key ()
{
  int r;
  asm xor ax,ax
  asm int 0x16
  asm mov r, ax
  return r;
}

/* Y aqui esta la mas grande hobra de arte de este mugriento codigo:
 * El capturador de eventos asincronicos que tiene una latencia orrible
 * en XT de 4.77 Mhz y no anda ni patras ahi si no hacemos que el loop
 * principal sea cortito...
 */
void TEvent::GetEvent()
{
  type = evNoting; // Por defecto no hay ningun evento (valor 0)

  // Toma el tick actual y lo compara con el que guardo en la
  // vuelta anterior. Si son diferentes dispara (va, pone un bit
  // de "type" a uno) el evento TimerOUT
  clock_t tick_actual = clock();
  if (tick_actual!=tick_anterior)
    type |= evTimerOut;

  if (kbd_ispress ()) { // Si se preciono una tecla
    type |= evKeyDown;  // Disparar el evento KeyDown
    keycode = kbd_key (); // con la tecla (parte baja de keycode)
    // y el codigo de la tecla (para teclas especiales, en la parte alta)
  }

  int mx, my, mb;
  mouse_read (&mx, &my, &mb);	// Leer el estado actual del mouse

  if (mb && !mbo)               // Si hay teclas ahora y antes no
    type |= evMouseDown;	// disparar el evento de "Boton precionado"
  if (!mb && mbo)               // Si ahora no hay tecla y antes si
    type |= evMouseUp; 		// Disparar el evento de "Boton soltado"
  if ((mx!=mxo) || (my!=myo))	// Si las coorenadas en x o en y son
    type |= evMouseMove;	// distintas a la otra vuelta disparar
				// el evento "Cursor movido"

  // En pos tenemos siempre las coordenadas del raton no importa si
  // hay o no evento...
  pos.assign(mx, my);
  // y en btn los botones (pero si se solto deven ser los botones
  // anteriores para que se pueda determinar que botones eran)
  btn = (type&evMouseUp)? mbo:mb;

  // ...Guardamos el estado actual para la proxima pasada...
  mbo = mb;
  mxo = mx;
  myo = my;
  tick_anterior=tick_actual;
}
