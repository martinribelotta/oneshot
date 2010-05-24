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

#include <iglu/screen.h>

char checkpal[] = {
  EGA_LIGHTGRAY,
  EGA_BLACK,
  EGA_WHITE,
  -1
};

const char *icon_check = {
"11111111"
"10000002"
"10000112"
"10000112"
"11101102"
"10111102"
"10011002"
"12222222"
};

const char *icon_nocheck = {
"11111111"
"10000002"
"10000002"
"10000002"
"10000002"
"10000002"
"10000002"
"12222222"
};

const char *icon_radioon = {
"33111133"
"31000013"
"31011023"
"10111102"
"10111102"
"31011023"
"32000023"
"33222233"
};

const char *icon_radiooff = {
"33111133"
"31000013"
"31000023"
"10000002"
"10000002"
"31000023"
"32000023"
"33222233"
};

char resize_pal[] = {
  EGA_LIGHTGRAY,
  EGA_WHITE,
  EGA_BLACK
};

const char *resize_icon = {
/*
"2222222222"
"2000000120"
"2000001201"
"2000012012"
"2000120120"
"2001201201"
"2012012012"
"2120120120"
"2201201201"
"2012012012"*/
/*
"2222222222"
"2002000000"
"2021200022"
"2211120212"
"2021112112"
"2002111112"
"2000211112"
"2002111112"
"2021111112"
"2222222222"
*/
"0000000002"
"0000000021"
"0000000210"
"0000002102"
"0000021021"
"0000210210"
"0002102102"
"0021021021"
"0210210210"
"2102102102"
};

