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
#ifndef _igluTEvent_h
#define _igluTEvent_h

#include <iglu/structs.h>

// Tipos de eventos:
#define evNoting                      (0)

// Los del raton...
#define evMouseDown                   (1<<0)
#define evMouseUp                     (1<<1)
#define evMouseMove                   (1<<2)
// Si!!! con dobule click (iva a ponerte triple y cuadruple pero
// me llamaron a comer ese dia X-DDDDD)
#define evMouseClick                  (1<<3)
#define evMouseDClick                 (1<<4)
#define evMouse             (evMouseDown+evMouseMove+evMouseUp+evMouseClick+evMouseDClick)

#define evKeyDown                     (1<<5)

// Por que era que tenia distinguidos los mensajes Broadcast de los
// mensajes Command??? Bue, no me acuedo, pero vamos a ponerle (para
// disimular) que evCommand lo manda un Menu o un Boton cuando se
// pide una se~nal y evBroadcas lo usa internamente el mecanismo de
// la GUI si quiere mandar mensages entre objetos por afuera del
// mecanismo de conandos... en realidad me quise hacer la gran
// TurboVision y no me salio :-(
#define evBroadcast                   (1<<6)
#define evCommand                     (1<<7)
#define evMessage           (evBroadcast+evCommand)

// Cuando cambia el Tick... (esto tiene menos precicion que el Papa
// JuanPablo II tratando de enebrar una aguja despues de un ataque
// de parquinson)
#define evTimerOut                    (1<<8)

/********************************************/

// Bueno, el consavido NULL que no puede faltar (pa no incluir stdlib.h)
#ifndef NULL
#define NULL  0
#endif

class TObject;

class TMessage {
  union t_data
   { char c; int i; short s; long l; void *p; float f; } d;
public:
  // Un numero que identifica el mensaje (propio de la palicacion...)
  int message;
  // El puntero al objeto (porque todos descienden de ese) que mando
  // el mensaje...
  TObject *sender;

  TMessage (): message(0), sender(NULL) { }
  TMessage (int m, TObject *s, char a):  message(m), sender(s) { d.c=a; }
  TMessage (int m, TObject *s, int a):   message(m), sender(s) { d.i=a; }
  TMessage (int m, TObject *s, short a): message(m), sender(s) { d.s=a; }
  TMessage (int m, TObject *s, long a):  message(m), sender(s) { d.l=a; }
  TMessage (int m, TObject *s, void *a): message(m), sender(s) { d.p=a; }
  TMessage (int m, TObject *s, float a): message(m), sender(s) { d.f=a; }

  inline char  getchar ()  { return d.c; }
  inline int   getint ()   { return d.i; }
  inline short getshort () { return d.s; }
  inline long  getlong ()  { return d.l; }
  inline void *getptr ()   { return d.p; }
  inline float getfloat () { return d.f; }
};

/***********************************/

/* La idea tras esta gigantesca estructura en vez de una union
 * es que pueda recivir varios eventos al mismo tiempo (tener en
 * cuanta la velicidad con que se proceza el loop principal)
 */
class TEvent { public:
  int type; // Los flags de tipo
  TEvent *next; // Esto es para la lista de TEvents
  TPoint pos; // Pocicion del cursor actualmente
  int btn, keycode; // Botones y teclas
  TMessage msg; // Mensjae (si se mando alguno)

  TEvent(): next(NULL), type(evNoting) { }
  TEvent (int t): next(NULL), type(t) { }
  TEvent (TMessage m): next(NULL), type(evMessage), msg(m) { }
  // Est funcion rellena la estructura con las condiciones actuales
  // de los perifericos en el instante en que se la llama.
  void GetEvent();
};

/*******************************************/

/* El manejadro de eventos es el responsable de mantener la cola
 * de eventos andando...
 * Hay un objeto global que se encarga de eso...
 */
class TEventManager {
  TEvent *base, *head;
  int cnt;
public:
  TEventManager (): cnt(0), base(NULL), head(NULL) { }
  ~TEventManager () { clearqueue(); }

  void putevent (TEvent& e);
  void getevent (TEvent& e);
  void SendMessage (TMessage& m);

  void clearqueue ();

  inline int isempty () { return ((cnt==0)&&(base==NULL)&&(head==NULL)); }
};

// ...este...
extern TEventManager EventManager;

#endif
