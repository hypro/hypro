/* scfint.h (interface to Schur-complement-based factorization) */

/***********************************************************************
*  This code is part of GLPK (GNU Linear Programming Kit).
*
*  Copyright (C) 2013, 2014 Andrew Makhorin, Department for Applied
*  Informatics, Moscow Aviation Institute, Moscow, Russia. All rights
*  reserved. E-mail: <mao@gnu.org>.
*
*  GLPK is free software: you can redistribute it and/or modify it
*  under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  GLPK is distributed in the hope that it will be useful, but WITHOUT
*  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
*  or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
*  License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with GLPK. If not, see <http://www.gnu.org/licenses/>.
***********************************************************************/

#ifndef SCFINT_H
#define SCFINT_H

#include "scf.h"
#include "lufint.h"
#include "btfint.h"

typedef struct SCFINT SCFINT;

struct SCFINT
{     /* interface to SC-factorization */
      int valid;
      /* factorization is valid only if this flag is set */
      SCF scf;
      /* Schur-complement based factorization */
      union
      {  LUFINT *lufi; /* scf.type = 1 */
         BTFINT *btfi; /* scf.type = 2 */
      }  u;
      /* interface to factorize initial matrix A0 */
      /*--------------------------------------------------------------*/
      /* working arrays */
      double *w1; /* double w1[1+n0_max]; */
      double *w2; /* double w2[1+n0_max]; */
      double *w3; /* double w3[1+n0_max]; */
      double *w4; /* double w4[1+n0_max+nn_max]; */
      double *w5; /* double w5[1+n0_max+nn_max]; */
      /*--------------------------------------------------------------*/
      /* control parameters */
      int nn_max;
      /* required maximal number of updates */
};

SCFINT *scfint_create(int type);
/* create interface to SC-factorization */

int scfint_factorize(SCFINT *fi, int n, int (*col)(void *info, int j,
      int ind[], double val[]), void *info);
/* compute SC-factorization of specified matrix A */

int scfint_update(SCFINT *fi, int upd, int j, int len, const int ind[],
      const double val[]);
/* update SC-factorization after replacing j-th column of A */

void scfint_ftran(SCFINT *fi, double x[]);
/* solve system A * x = b */

void scfint_btran(SCFINT *fi, double x[]);
/* solve system A'* x = b */

void scfint_delete(SCFINT *fi);
/* delete interface to SC-factorization */

#endif

/* eof */
