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
#ifndef _igluMsgBox_h
#define _igluMsgBox_h

#include <iglu/structs.h>
#include <iglu/tlabel.h>
#include <iglu/tbutton.h>
#include <iglu/commands.h>

extern int MessageBox(const char *fmt, ...);
extern int MessageBoxRect(TRect& r, const char *msg);

// int InputBox(const char *title, const char *label, int limits);

// Standar messages titles
#define mfWarning        0x0001
#define mfInformation    0x0002
#define mfError          0x0003
#define mfConfirmation   0x0004

// Standar buttons format
#define mfYesButton      0x0100
#define mfNoButton       0x0200
#define mfOkButton       0x0400
#define mfCancelButton   0x0800


#endif /* _igluMsgBox_h */

