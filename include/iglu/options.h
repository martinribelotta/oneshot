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
#ifndef _igluViewOptions_h
#define _igluViewOptions_h

/* Opciones de alineacion para TView::Align */

// Ninguna alineacion (por defecto)
#define vaNone            (0)
// Con el borde izquierdo pegado al izquierdo del padre (Owner)
#define vaLeft            (1<<0)
// Con el borde derecho pegado al derecho del padre (Owner)
#define vaRight           (1<<1)
// Con el borde superior pegado al superior del padre (Owner)
#define vaTop             (1<<2)
// Con el borde inferior pegado al inferior del padre (Owner)
#define vaBottom          (1<<3)
// Con los bordes iguales a los del padre.
#define vaClient          (vaLeft|vaRight|vaTop|vaBottom)
// Preserva el borde de la izquierda (Left) que hay entre el padre y el TView
#define vaPreservGapL	  (1<<4)
// Preserva el borde de la derecha (Right) que hay entre el padre y el TView
#define vaPreservGapR	  (1<<5)
// Preserva el borde superior (Top) que hay entre el padre y el TView
#define vaPreservGapT	  (1<<6)
// Preserva el borde inferior (Bottom) que hay entre el padre y el TView
#define vaPreservGapB	  (1<<7)
// Preserva el ancho (Width) del TView en cuestion
#define vaPreservW        (1<<8)
// Preserva el alto (Width) del TView en cuestion
#define vaPreservH        (1<<9)
// Preserva ancho y alto
#define vaFixedSize       (vaPreservW|vaPreservH)
// Proporcional al ancho del padre pero con los mismos bordes que antes
#define vaPropW           (vaPreservGapR|vaPreservGapL)
// Proporcional al alto del padre pero con los mismos bordes que antes
#define vaPropH           (vaPreservGapT|vaPreservGapB)
/* Todas las opciones se pueden conbinar (+ u |) entre si, pero las
 * opciones sin sentido (como vaFixedSize+vaPropW+vaPropH, es decir
 * tamaño fijo y proporcional al padre) causaran comportamientos
 * inesperados, inprwedesibles y podrian hacer que el universo como lo
 * conocemos desaparesca...
 */

#endif /* _igluViewOptions_h */
