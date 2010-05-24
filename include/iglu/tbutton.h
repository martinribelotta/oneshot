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
#ifndef _igluTButton_h
#define _igluTButton_h

#include <iglu/tview.h>

/* Boton abstracto. Base para todos los tipos de botones.
 * Se encarga de recivir los eventos del raton/teclado y generar
 * las acciones correspondientes que seran reimplementadas en
 * los derivados.
 */
class TAbstButton: public TView {
public:
  int sig; // Se¤al enviada cuando se preciona el boton (0 por defecto)
  // Si es 0 se puede determinar que boton fue precionado mirando el
  // puntero "Sender" del mensaje.

  TAbstButton(TRect& r, int signal=0): TView(r), sig(signal) { }
  virtual void Draw() { DrawState((State&stDown)? 1:0); }
  // Dibuja el boton en el estado st.
  // st!=0: cuando el boton deve estar pulsado
  // st==0: cuando el boton deve estar normal.
  virtual void DrawState(int st) = 0;
  // Reimplementados para detectar los eventos
  virtual void MouseEvent(TEvent& e); //
  virtual void KeyEvent(TEvent& e);   //
  // Llamado al reconocer que se solto el raton con el cursor dentro
  // de la geometria del boton.
  virtual void Assert(TEvent&) = 0;
  virtual void LostFocus(); // Reimplementado para mejor apariencia visual
  virtual void GotFocus(); // idem.
  // Reimplementado para llamar a doDraw en el momento oportuno.
  virtual void SetState(int Stat, int active);
};

// Boton pulsable.
class TPushButton: public TAbstButton {
public:
  // Funcion llamada al hacerse click sobre el. (llamada al ejecutar Assert)
  // Si es un puntero a NULL (0) no se llama.
  void (*onClick) (TPushButton *sender);

  TPushButton (TRect& r, int s=0):
    TAbstButton(r, s), onClick(NULL) { }
  virtual void DrawState(int st); // Reimplementado
  virtual void Assert(TEvent&); // Reimplementado
};

// Boton con texto.
class TTextButton: public TPushButton {
public:
  char *caption;
  TTextButton (TRect& r, char *c, int s=0): TPushButton(r, s), caption(c) { }
  virtual void DrawState(int st); // Reimplementado para mostrar el texto.
};

// Boton con solo un caracter.
class TCharButton: public TPushButton {
public:
  char caption;
  TCharButton (TRect& r, char c, int s=0): TPushButton(r, s), caption(c) { }
  virtual void DrawState(int st); // Reimplementado para mostrar "caption"
};

#endif
