// Oliver Kullmann, 22.11.2010 (Swansea)
/* Copyright 2010, 2011 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Experimentation/Investigations/RamseyTheory/VanderWaerdenProblems/plans/3-k/14.hpp
  \brief On investigations into vdw_2(3,14) = 186


  \todo OKsolver
  <ul>
   <li> n=185,186:
   \verbatim
> OKsolver_2002-O3-DNDEBUG -M -D21 -F VanDerWaerden_2-3-14_185.cnf
  1029:   1111   1896.56  3.98E+09     4.16s     8.55s     0y 207d  8h  0m 42s     0     0   52

s SATISFIABLE
c sat_status                            1
c initial_maximal_clause_length         14
c initial_number_of_variables           185
c initial_number_of_clauses             9689
c initial_number_of_literal_occurrences 42542
c number_of_initial_unit-eliminations   0
c reddiff_maximal_clause_length         0
c reddiff_number_of_variables           0
c reddiff_number_of_clauses             0
c reddiff_number_of_literal_occurrences 0
c number_of_2-clauses_after_reduction   0
c running_time(sec)                     8812.1
c number_of_nodes                       1956023
c number_of_single_nodes                0
c number_of_quasi_single_nodes          0
c number_of_2-reductions                17875997
c number_of_pure_literals               185
c number_of_autarkies                   0
c number_of_missed_single_nodes         0
c max_tree_depth                        52
c number_of_table_enlargements          0
c number_of_1-autarkies                 4074
c number_of_new_2-clauses               0
c maximal_number_of_added_2-clauses     0
c file_name                             VanDerWaerden_2-3-14_185.cnf

> OKsolver_2002-O3-DNDEBUG -M -D21 -F VanDerWaerden_2-3-14_186.cnf
s UNSATISFIABLE
c sat_status                            0
c initial_maximal_clause_length         14
c initial_number_of_variables           186
c initial_number_of_clauses             9795
c initial_number_of_literal_occurrences 43014
c number_of_initial_unit-eliminations   0
c reddiff_maximal_clause_length         0
c reddiff_number_of_variables           0
c reddiff_number_of_clauses             0
c reddiff_number_of_literal_occurrences 0
c number_of_2-clauses_after_reduction   0
c running_time(sec)                     103496.6
c number_of_nodes                       22469535
c number_of_single_nodes                0
c number_of_quasi_single_nodes          0
c number_of_2-reductions                210989012
c number_of_pure_literals               2150
c number_of_autarkies                   0
c number_of_missed_single_nodes         8
c max_tree_depth                        52
c number_of_table_enlargements          0
c number_of_1-autarkies                 60129
c number_of_new_2-clauses               0
c maximal_number_of_added_2-clauses     0
c file_name                             VanDerWaerden_2-3-14_186.cnf

> E = read_oksolver_mon("VanDerWaerden_2-3-14_186.cnf.mo")
450700
> plot_oksolver_mon_nodes(E)
ldstep= 18 step= 262144 left= 128 right= 2097152
obs/count= 4.654129 nodes-range= 1 70632 ave-nodes-range= 10.713 2631.656
> summary_oksolver(E)
Nodes:
    Min.  1st Qu.   Median     Mean  3rd Qu.     Max.
    1.00     2.00     3.00    49.85     7.00 70630.00
2-reductions:
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
   0.20    7.50    9.92   11.76   13.46   70.00
Single nodes:
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
      0       0       0       0       0       0
Autarkies:
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
      0       0       0       0       0       0
Time ~ nodes:
[1] 0.9735288
 (Intercept)      E$nodes
-0.011336484  0.004833474
> hist_oksolver_mon_nodes(E)
Median= 1.584963
Mean= 5.639659
> hist_oksolver_mon_nodes(E,breaks="st")
Median= 1.584963
Mean= 5.639659
   \endverbatim
   The node-average continously decreases, and the initially very hard-looking
   problem turned out to be relatively easy. Since it ran on csltok, perhaps
   performance is actually not so much worse than that of satz215.
   Here it seems very interesting to optimise the heuristics! </li>
  </ul>


  \todo satz215
  <ul>
   <li> k=14, n=186:
   \verbatim
> satz215 VanDerWaerden_2-3-14_186.cnf
**** The instance is unsatisfiable. *****
NB_MONO= 1435, NB_UNIT= 277867725, NB_BRANCHE= 10822316, NB_BACK= 5500793
Program terminated in 14939.760 seconds.
satz215 VanDerWaerden_2-3-14_186.cnf 14939.760 10822316 5500793 1573930613 58462301 0 186 9795 0 29371201 12582731
   \endverbatim
   </li>
  </ul>


  \todo SplittingViaOKsolver
  <ul>
   <li> Depth 11 with minisat-2.2.0:
   \verbatim
> SplittingViaOKsolver -D11 VanDerWaerden_2-3-14_186.cnf
> cd SplitViaOKsolver_D11VanDerWaerden_2314_186cnf_2011-05-18-184528
> more Md5sum
22faa6218bd2cfaa3b81690bed15e2f1
> more Statistics
> E=read.table("Data")
> summary(E$n)
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
  11.00   26.00   35.00   37.64   46.00   95.00
> table(E$n)
11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36
12  8 25 22  1 18 23 61 33 29  5 22 38 85 98 37 31 16 33 38 76 79 91 69 44 21
37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62
24 34 61 56 70 75 55 45 29 22 26 25 30 31 45 25 32 30 19 22 19 15 12  8 12 15
63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 80 82 83 85 86 88 89 95
17 16 13  8 11 12  8  3  1  4  5  3  5  4  2  4  3  3  1  1  2  1  1  1
csoliver@cs-oksvr:~/OKplatform/SplitViaOKsolver_D11VanDerWaerden_2314_186cnf_2011-05-18-184528> more Result
s UNKNOWN
c sat_status                            2
c initial_maximal_clause_length         14
c initial_number_of_variables           186
c initial_number_of_clauses             9795
c initial_number_of_literal_occurrences 43014
c number_of_initial_unit-eliminations   0
c reddiff_maximal_clause_length         0
c reddiff_number_of_variables           0
c reddiff_number_of_clauses             0
c reddiff_number_of_literal_occurrences 0
c number_of_2-clauses_after_reduction   0
c running_time(sec)                     44.1
c number_of_nodes                       4073
c number_of_single_nodes                0
c number_of_quasi_single_nodes          0
c number_of_2-reductions                2019
c number_of_pure_literals               0
c number_of_autarkies                   0
c number_of_missed_single_nodes         0
c max_tree_depth                        11
c number_of_table_enlargements          0
c number_of_1-autarkies                 0
c number_of_new_2-clauses               0
c maximal_number_of_added_2-clauses     0
c file_name                             VanDerWaerden_2-3-14_186.cnf
c splitting_directory                   SplitViaOKsolver_D11VanDerWaerden_2314_186cnf_2011-05-18-184528/Instances
c splitting_cases                       1981

> cd Instances
> I="../$(cat ../F)"; echo " i n t cfs" > Stats; time tail -n +2 ../Data | while read C F N; do cat $I | ApplyPass-O3-DNDEBUG $F > Temp.cnf; minisat-2.2.0 Temp.cnf >Temp.out 2>&1; S=$?; if [[ $S != 20 ]]; then echo -e "UNEXPECTED RETURN VALUE ${S}\!"; break; else T=$(cat Temp.out | awk '/CPU time/ {print $4}'); CF=$(cat Temp.out | awk '/conflicts/ {print $3}'); echo "$C $F $N $T $CF" >> Stats; echo -n "$C:$T "; fi; done
   \endverbatim
   </li>
   <li> Depth 14 with minisat-2.2.0:
   \verbatim
> SplittingViaOKsolver -D14 VanDerWaerden_2-3-14_186.cnf
> cd SplitViaOKsolver_D14VanDerWaerden_2314_186cnf_2011-05-18-211753
> more Md5sum
bc7f0029b0598d58508739368d0ce4d0
> more Statistics
> E=read.table("Data")
> summary(E$n)
   Min. 1st Qu.  Median    Mean 3rd Qu.    Max.
  14.00   38.00   49.00   49.54   60.00  107.00
> table(E$n)
 14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33
  8  16  36  31  27  69  65  77  53  64  38  97 156 212 201 128  85  66  99 203
 34  35  36  37  38  39  40  41  42  43  44  45  46  47  48  49  50  51  52  53
320 384 351 211 178 135 170 215 313 352 402 417 368 282 226 189 206 229 317 348
 54  55  56  57  58  59  60  61  62  63  64  65  66  67  68  69  70  71  72  73
365 363 324 285 227 194 167 175 168 210 216 222 182 187 175 145 118 106  77  90
 74  75  76  77  78  79  80  81  82  83  84  85  86  87  88  89  90  91  92  93
 85  82  80  95  68  62  53  53  50  33  33  18  26  26  13  11  17   9  12   8
 94  95  96  98  99 100 101 102 107
  3   3   3   2   1   2   2   1   1
kullmann-0:SplitViaOKsolver_D14VanDerWaerden_2314_186cnf_2011-05-18-211753> more Result
s UNKNOWN
c sat_status                            2
c initial_maximal_clause_length         14
c initial_number_of_variables           186
c initial_number_of_clauses             9795
c initial_number_of_literal_occurrences 43014
c number_of_initial_unit-eliminations   0
c reddiff_maximal_clause_length         0
c reddiff_number_of_variables           0
c reddiff_number_of_clauses             0
c reddiff_number_of_literal_occurrences 0
c number_of_2-clauses_after_reduction   0
c running_time(sec)                     151.0
c number_of_nodes                       29309
c number_of_single_nodes                0
c number_of_quasi_single_nodes          0
c number_of_2-reductions                65529
c number_of_pure_literals               0
c number_of_autarkies                   0
c number_of_missed_single_nodes         0
c max_tree_depth                        14
c number_of_table_enlargements          0
c number_of_1-autarkies                 1
c number_of_new_2-clauses               0
c maximal_number_of_added_2-clauses     0
c file_name                             VanDerWaerden_2-3-14_186.cnf
c splitting_directory                   SplitViaOKsolver_D14VanDerWaerden_2314_186cnf_2011-05-18-211753/Instances
c splitting_cases                       12192

> cd Instances
> I="../$(cat ../F)"; echo " i n t cfs" > Stats; time tail -n +2 ../Data | while read C F N; do cat $I | ApplyPass-O3-DNDEBUG $F > Temp.cnf; minisat-2.2.0 Temp.cnf >Temp.out 2>&1; S=$?; if [[ $S != 20 ]]; then echo -e "UNEXPECTED RETURN VALUE ${S}\!"; break; else T=$(cat Temp.out | awk '/CPU time/ {print $4}'); CF=$(cat Temp.out | awk '/conflicts/ {print $3}'); echo "$C $F $N $T $CF" >> Stats; echo -n "$C:$T "; fi; done
real    70m20.221s
user    69m42.983s
sys     2m20.526s

# Monitoring in R via
#> E=read.table("Stats",header=TRUE,colClasses=c("integer","integer","integer","numeric","numeric")); plot(E$t); cat(sprintf("%d: %.2fh, sum-cfs=%e, mean-t=%.3fs, mean-cfs=%.0f",length(E$t),sum(E$t)/60/60,sum(E$cfs),mean(E$t),mean(E$cfs)),"\n")
12192: 1.01h, sum-cfs=8.851248e+07, mean-t=0.297s, mean-cfs=7260

#> summary(E)
        i               n                t                  cfs
 Min.   :    1   Min.   : 14.00   Min.   : 0.000999   Min.   :     10
 1st Qu.: 3049   1st Qu.: 38.00   1st Qu.: 0.007998   1st Qu.:    161
 Median : 6096   Median : 49.00   Median : 0.013997   Median :    413
 Mean   : 6096   Mean   : 49.54   Mean   : 0.297203   Mean   :   7260
 3rd Qu.: 9144   3rd Qu.: 60.00   3rd Qu.: 0.037994   3rd Qu.:   1663
 Max.   :12192   Max.   :107.00   Max.   :92.735900   Max.   :1734015
   \endverbatim
   </li>
  </ul>


  \todo Palindromic numbers
  <ul>
   <li> pdvanderwaerden([3,14])[2] = 183 = vanderwaerden([3,14])-3 . </li>
   <li> pdvanderwaerden([3,14])[1] = 174. </li>
   <li> OKsolver_2002 easily determines n=182 as satisfiable and n=174,
   183,...,186 as unsatisfiable. </li>
   <li> So does satz215, march_pl and minisat2. </li>
   <li> "RunPdVdWk1k2 3 14 gsat-tabu 100 100000" yields
   \verbatim
Break point 1: 174
Break point 2: 183
   \endverbatim
   </li>
  </ul>

*/
