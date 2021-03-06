// Oliver Kullmann, 6.2.2001 (Toronto)
/* Copyright 2001 - 2007 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file OKsolver/SAT2002/Abstand.h
  \brief Header file for distance functions and choice of first branch
*/

                       /* OKsolver; 5.3.1998 */

/* Autor: Oliver Kullmann, Universitaet Frankfurt am Main, Germany */
/* ab Februar 1999: University of Toronto, Computer Science Department */

/* Angelegt: 6.2.2001 */

#ifndef GELESENABSTAND_37Teewq
#define GELESENABSTAND_37Teewq

/* -------------------------------------------------------------------------- */


extern float d0, d1;

extern unsigned int d0S, d1S; /* "sekundaer" */

extern void Abstand ( void );

#ifdef DYNAMISCH

extern void InitAbstand2( void );

#endif

extern const char *Abstandsname;

#endif
