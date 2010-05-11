// Oliver Kullmann, 25.4.2010 (Swansea)
/* Copyright 2010 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Experimentation/Investigations/RamseyTheory/GreenTaoProblems/Transversals/plans/Datak9.hpp
  \brief Investigating the transversal hypergraph of Green-Tao hypergraphs for k = 9 (length of arithmetic progressions)


  \todo Elementary statistics
  <ul>
   <li> Investigating tr_arithprog_hg(9,n). </li>
   <li> The numbers of minimum hyperedges:
   \verbatim
L9 : [];
minimum_transversals_decomp_gen(inf,lambda([n],arithprog_primes_hg(9,n)),'L9)$

T : transform_steps_l(map(lambda([d],d[4][1]),reverse(L9)));
   \endverbatim
   </li>
   <li> For orientation, those n-values where at least one hyperedge has been
   added (compared to n-1), and the number of hyperedges added:
   \verbatim
for n: 8 thru 5000 do block(
 [d:nhyp_arithprog_primes_ohg(9,n)-nhyp_arithprog_primes_ohg(9,n-1)],
  if d>0 then print(n, d));
289 1
316 1
690 1
1453 1
1497 1
1523 1
2022 1
2499 1
2823 1
2915 1
3315 1
3602 1
3775 1
4137 1
4551 1
4653 1
4711 1
4774 1
   \endverbatim
   </li>
   <li> These hyperedges are nearly disjoint, only number 1 and number 2 have
   some elements in common:
   \verbatim
G : arithprog_primes_ohg(9,5000)$
non_disjoint_pairs(G[2]);
 [[1,2]]
intersection(G[2][1], G[2][2]);
 {409,619,829,1039,1249,1459,1669,1879}
   \endverbatim
   These two hyperedges are just the two 9-progressions contained in the one
   10-progression which exists for n <= 5000 (see
   RamseyTheory/GreenTaoProblems/Transversals/plans/Datak10.hpp). </li>
   <li> It follows from the above disjointness-property, that tau always
   increases by one when a new hyperedge aries in the above list, except for
   the second hyperedge which is left out. </li>
  </ul>


  \todo Only computing the transversal numbers
  <ul>
   <li> Just computing the transversal numbers, using minisat2 and the
   direct translation:
   \verbatim
> GTTransversalsInc 9 1 0 GT_9 GT_9_SAT

L : transform_steps_l(map(third,rest(read_nested_list("GT_9"))));
 [288,689,1452,1496,1522,2021,2498,2822,2914,3314,3601,3774,4136,4550]
length(L);
 14

> tail -1 GT_9
9 4652 14

> tail -40 GT_9_SAT
|         0 |    8671    38516   128230 |    12838        0    nan |  0.000 % |
|       101 |    8671    38516   128230 |    14122      101      9 |  8.805 % |

...
|  17044357 |    8671    38516   128230 |   185146    83508     84 |  8.805 % |
*** INTERRUPTED ***
restarts              : 29
conflicts             : 24608505       (429 /sec)
decisions             : 46478865       (1.40 % random) (810 /sec)
propagations          : 4415348685     (76943 /sec)
conflict literals     : 2107067304     (60.14 % deleted)
Memory used           : 171.43 MB
CPU time              : 57384.7 s
   \endverbatim
   </li>
  </ul>

*/
