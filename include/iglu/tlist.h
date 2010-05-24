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

#ifndef _iglu_TList_h
#define _iglu_TList_h

#include <iglu/structs.h>

class TANode {
  char *name;
  TObject *object;
public:
  TANode *next, *prev;

  TANode (char *s, TObject *o);
  ~TANode ();
  inline char *getname () { return name; }
  inline TObject *getobject () { return object; }
};

#define TLISTMAXITEMS     ((0xFFFFL)/sizeof(TANode))

class TList {
protected:
  TANode *base, *head;

  TANode *getnode (int idx);
public:
  int count;

  TList ();
  ~TList ();

  void addObject (char *name, TObject *obj);
  int indexOf (char *name);
  int indexOf (TObject *obj);
  void delObject (int idx);
  char *getname (int idx);
  TObject *getobject (int idx);
};


#endif
