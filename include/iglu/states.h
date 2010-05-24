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
#ifndef _igluViewStates_h
#define _igluViewStates_h

/* Estados pocibles de la variable TView::State */

// Estado visible (creo que no se usa)
#define stVisible                  (1<<0)
// Tiene el foco (para un TGroup significa que puede recivir eventos)
#define stFocus                    (1<<1)
// Esta seleccionado (por ejemplo, cuando un boton esta seleccionado
// y se pasa con el cursor sobre el y hay botones precionados se muestrta
// precionado.
#define stSelect                   (1<<2)
// Se esta moviendo (una ventana, creo que no se usa)
#define stDraggin                  (1<<3)
// INPORTANTE: En los TGroup mantiene el ciclo de toma-procezado de eventos
// Escencial para que funcione la interfaz grafica (el programa principal es
// un TGroup que se mantiene en este ciclo gracias a eso)
#define stModal                    (1<<4)
// ?????? Creo que era para indicar que un TView estaba seabilitado (no se usa)
#define stDisable                  (1<<5)
// ??????!!!!! Si uviera implementado vien la interfaz grafica esto indicaba
// que hace falta repintar... (no se usa, es de cuando miraba XWindow)
#define stExpose                   (1<<6)
// Estado pulsado (para el boton... era para no usar otra varibale)
#define stDown                     (1<<7)
// Maximizado (cuando queria implementar eso, no se usa)
#define stMaximise                 (1<<8)
// Iconificado (tampoco se usa)
#define stIconify                  (1<<9)
// El objeto se dibuja irrestrictamente en cualquier pocicion sin  hacer
// caso del recortado de dibujo actual.
#define stNoClipped                (1<<10)
// Indica que la ventana no se puede mover.
#define stNoMoveable               (1<<11)
// Indica que la ventana puede obtener el foco.
#define stFocusheable		   (1<<12)
// Indica que el objeto no usara getClientArea (que puede diferir con Bounds)
// cuando calcule su area de recorte sino que usara el Bounds real del padre
// Usado para que se puedan dibujar el boton de "X" y el titulo en las
// ventanas.
#define stAbsoluteClipped	   (1<<13)

/* Algunas vanderas podrian no tener la interpretacion que se les da
 * aqui (o agregar alguna a la ya mencionada) en algun objeto especifico.
 * Por favor, mirar lo que dice cada objeto en su SetState.
 */
#endif
