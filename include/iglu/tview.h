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
#ifndef _igluTView_h
#define _igluTView_h

#include <iglu/structs.h>
#include <iglu/tevent.h>
#include <iglu/states.h>
#include <iglu/commands.h>
#include <iglu/options.h>

class TGroup;	// Declaracion "hacia atras" para poder declarar
// un puntero de este tipo

/* Objeto principal de la interfaz grafica. Define un area
 * en pantalla y sus atributos, ademas maneja los eventos que
 * se producen sobre esta despachandolos a la funcion adecuada
 */
class TView: public TObject {
public:
  TRect Bounds;		// Geometria
  TGroup *Owner;	// Padre (en donde esta insertado
  TView *next, *prev;	// Para la lista doblemente enlazada

  // Estados y alineacion (ver stadus.h y options.h
  int State, Align;

  TView (const TRect& r);	// El contructor define la geometria
  virtual ~TView ();	// el destructor deve ser virtual para
			// que al destruir un objeto TView se
			// llame al constructor derivado
			// correspondiente.

  /* Funcion que redibuja el contenido del area (por defecto
   * no hace nada) Esta fimuncion no deve ser llamada directamente
   * exepto que se este seguro de que esta ocultado el raton y el
   * area de recorte este configurada adecuadamente (de eso se ocupa
   * doDraw) como ocurre dentro de las redefiniciones de Draw en otros
   * objetos TView
   */
  virtual void Draw();
  virtual void HandleEvent(TEvent& e);	// Manejador de eventos.

  // Estas funciones son llamadas por HandleEvent cuando se
  // detecta el evento:
  virtual void MouseEvent(TEvent&) { }		// de raton
  virtual void KeyEvent(TEvent&) { }		// De tecla precionada
  virtual void MessageEvent(TEvent&) { }	// Un mensaje
  virtual void TimerEvent(TEvent&) { }		// TimerOUT
  virtual void idle() { }	// Cuando no hay ningun evento.

  virtual void Execute() { }	// Redefinida en TGroup

  // Toma el area recortada 
  void getClipArea(TRect& r);

  virtual void GotFocus();	// Ganar el foco
  virtual void LostFocus();	// Avandonar el foco

  /* Reconoce la alineacion.
   *	o: Geometria del padre bieja
   *	n: Geometria del padre nueva
   */
  virtual void RecuestAlign (TRect& o, TRect& n);

  // Debuelve Bounds por defecto pero en agunos tipos de
  // contenedores debuelve el area que se puede usar para
  // insertar componentes.
  virtual void getClientArea (TRect& r, int=1) { r = Bounds; }

  /* Cambia el estado de los bits de "State" segun la mascara
   * stat y la variable active.
   *	- Si active es distinto de 0 se activan (ponen a uno)
   *	los bits en uno de Stat
   *	- Si active es cero (0) se desactivan (ponen a cero)
   *	los bits en uno de Stat
   */
  virtual void SetState(int Stat, int active);

  // Llamar para redibujar el componente. Prepara el terreno para luego
  // llamar a Draw.
  void doDraw ();

  void move(int x, int y)
    { moverel(x-Bounds.a.x, y-Bounds.a.y); }
  virtual void moverel(int dx, int dy)	// Mueve (relativamente)
  { Bounds.moverel(dx,dy); }		// La pocicion del TView
  virtual void resize (int w, int h);	// Cambia de tamaño el TView
};

/* Grupo de objetos TView que se redibujan y toman sus eventos en
 * forma conjunta. Base del ciclo de eventos.
 */
class TGroup: public TView {
public:
  TView *base, *head;	// Primero y ultimo en la lista doblemente enlazada

  TGroup(const TRect& r);	// Constrructor. Mismo parametro que para TView
  virtual ~TGroup();	// Destructor (destrulle la lista tambien)

  virtual void Draw();
  virtual void HandleEvent(TEvent& e);
  // Redefinido: ejecuta los componentes en un cilo mientras tenga stModal
  // a uno en la variable State.
  virtual void Execute();
  virtual void moverel (int dx, int dy);	// Redefinido.
  virtual void RecuestAlign (TRect& o, TRect& n);	// Redefinido.
  virtual void resize (int w, int h);	// Redefinido.

  /* Ejecuta "q" insertandolo en la lista de este TGroup y luego
   * restaura el estado anterior que tenia "q" sacandolo de la lista
  * (cuando termina de ejecutarse)
   */
  virtual void ExecView(TView *q);

  virtual void insert(TView *q);	// Agregar un TView a la lista
  virtual void detach(TView *q);	// Sacar el TView q de la lista
  int indexOf(TView *q);	// Pocicion de q en la lista o -1 si no.

  void moveTop(TView *q);	// Mueve q al frente de la lista.

  // Dibuja los componentes de la lista HACIA ADELANTE para que los objetos
  // de atras que estan tapados queden tapados por los de mas adelante
  void DrawSubViews(TView *initial);
  // Pasa el evento e por la lista de TViews empezando por initial
  // (normlamente head) HACIA ATRAS para que los objetos del frente
  // oculten los eventos que ocurren sobre ellos a los de abajo que
  // estan tapando.
  void HandleEventSubViews(TEvent& e, TView *initial);

  // Manda el mensaje m a los objetos de la lista en el mismo orden
  // que HandleventSubViews
  void SendToChild (TMessage& m);

  // Dibuja el TGroup en cuestion pero solo la region "r" (para esto se
  // usa el recortado)
  void RedrawRect(TRect& r);
};

#endif
