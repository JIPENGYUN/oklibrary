// Matthew Gwynne, 20.5.2011 (Swansea)
/* Copyright 2011 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Investigations/Cryptography/AdvancedEncryptionStandard/plans/SAT2011/KeyDiscovery/016/2_1_8/1_13.hpp
  \brief Investigations into small scale AES key discovery for 1 + 1/3 round AES with a 2x1 plaintext matrix and 8-bit field elements


  \todo Problem specification
  <ul>
   <li> In this file, we collect the investigations into translations of
   1 + 1/3 round small scale AES with two rows, one columns, using the 8-bit
   field size. </li>
   <li> The AES encryption scheme we model takes a 16-bit plaintext and
   16-bit key and outputs a 16-bit ciphertext. </li>
   <li> The plaintext, key and ciphertext are all considered, column by
   column, as 2x1 matrices of 8-bit elements. </li>
   <li> In other words, the 8-bit element at position (i,1) in the AES matrix
   is the i-th 8-bit word of the 16-bits. </li>
   <li> The 8-bit element (b_0,b_1,b_2,b_3,b_4,b_5,b_6,b_7) is considered as
   the polynomial b_0 * x^3 + b_1 * x^2 + b_2 * x + b_3. </li>
   <li> Addition and multiplication on these polynomials is defined as usual,
   modulo the polynomial x^8+x^4+x^3+x+1. </li>
   <li> The encryption scheme applies the following operations:
   <ol>
    <li> Addition of round key 0 (input key) to plaintext. </li>
    <li> Application of SubBytes (Sbox to each 8-bit element) operation. </li>
    <li> Application of MixColumns operation.. </li>
    <li> Addition of round key 1, resulting in the ciphertext. </li>
   </ol>
   </li>
   <li> The small scale AES variant is decomposed into small boolean functions
   which are then translated to SAT. </li>
   <li> The decompositions and translations are listed in "Investigating
   dimensions" in
   Investigations/Cryptography/AdvancedEncryptionStandard/plans/SAT2011/Experimentation.hpp.
   </li>
   <li> Note that we consider the canonical CNF translation, as
   this is an example of the "hardest" representation without
   new variables. See "Hardness of boolean function representations"
   in
   Experimentation/Investigations/BooleanFunctions/plans/general.hpp. </li>
  </ul>


  \todo Using the canonical box translation
  <ul>
   <li> Translating the AES cipher treating Sboxes and field multiplications
   as whole boxes and translating these boxes using the canonical translation.
   </li>
   <li> Generating small scale AES for 1 + 1/3 rounds:
   \verbatim
shell> mkdir aes_2_1_8/canon
shell> cd aes_2_1_8/canon
shell> oklib --maxima
oklib_load_all()$
num_rounds : 1$
num_rows : 2$
num_columns : 1$
exp : 8$
final_round_b : false$
box_tran : aes_ts_box$
mc_tran : aes_mc_bidirectional$
oklib_monitor : true$
output_ss_fcl_std(num_rounds, num_columns, num_rows, exp, final_round_b, box_tran, mc_tran)$

shell> cat ssaes_r1_c1_rw2_e8_f0.cnf | ExtendedDimacsFullStatistics-O3-DNDEBUG n
 n non_taut_c red_l taut_c orig_l comment_count finished_bool
3264 52532 154472 0 154472 3265 1
 length count
1 8
2 49152
3 288
17 3072
256 12
   \endverbatim
   </li>
   <li> In this translation, we have:
   <ul>
    <li> One full round (Key Addition, SubBytes, and MixColumn operation).
    </li>
    <li> 4 Sboxes (2 from SubBytes; 2 from key schedule). </li>
    <li> 72 additions (32 from key additions; 32 from MixColumns; 8 from
    key schedule). </li>
    <li> 4 multiplications by 02, 03 (from MixColumns).
    </li>
    <li> 8 bits for the constant in the key schedule. </li>
   </ul>
   </li>
   <li> Note that as this variant has only one column, the key schedule
   applies Sbox(K_i) + C rather than Sbox(K_i) + K_j + C where K_i and
   K_j are key words from the previous round key. </li>
   <li> The Sboxes and multiplications use the canonical translation,
   which has the following number of clauses of each length:
   \verbatim
maxima> ncl_list_full_dualts(16,256);
[[2,4096],[17,256],[256,1]]
   \endverbatim
   </li>
   <li> The number of clauses of each length in the translation are:
    <ul>
     <li> 8 unit-clauses (key schedule constant). </li>
     <li> 49152 binary clauses (4 Sboxes; 4 multiplications * 2). </li>
     <li> 288 ternary clauses (72 arity two additions). </li>
     <li> 3072 clauses of length seventeen (4 Sboxes; 4 multiplications * 2).
     </li>
     <li> 12 clauses of length 256 (4 Sboxes; 4 multiplications * 2). </li>
    </ul>
   </li>
   <li> Generate random assignments for the plaintext and ciphertext, leaving
   the key unknown with a single plaintext-ciphertext pair:
    <ul>
     <li> Generating the key:
     \verbatim
maxima> output_ss_random_pc_pair(seed,rounds,num_columns,num_rows,exp,final_round_b);
     \endverbatim
     Merge the assignments with the translations:
     \verbatim
shell> AppendDimacs-O3-DNDEBUG ssaes_r1_c1_rw2_e4_f0.cnf ssaes_pkpair_r1_c1_rw2_e4_f0_s1.cnf > r1_keyfind.cnf; done
     \endverbatim
     </li>
     <li> All solvers solve in <1s:
      <ul>
       <li> minisat-2.2.0:
       \verbatim
shell> minisat-2.2.0 r1_keyfind.cnf
restarts              : 6
conflicts             : 647            (5882 /sec)
decisions             : 7432           (0.00 % random) (67564 /sec)
propagations          : 641324         (5830218 /sec)
conflict literals     : 145083         (27.42 % deleted)
Memory used           : 22.00 MB
CPU time              : 0.11 s
       \endverbatim
       </li>
       <li> glucose:
       \verbatim
shell> glucose r1_keyfind.cnf
<snip>
c restarts              : 1
c conflicts             : 653            (5023 /sec)
c decisions             : 4658           (1.70 % random) (35831 /sec)
c propagations          : 380621         (2927854 /sec)
c conflict literals     : 202983         (17.84 % deleted)
c Memory used           : 5.82 MB
c CPU time              : 0.13 s
       \endverbatim
       </li>
       <li> cryptominisat:
       \verbatim
shell> cryptominisat r1_keyfind.cnf
c restarts                 : 1
c dynamic restarts         : 0
c static restarts          : 1
c conflicts                : 0           (0.00      / sec)
c decisions                : 1           (0.00      % random)
c bogo-props               : 39978329    (105206128.95 / sec)
c conflict literals        : 0           (-nan      % deleted)
c Memory used              : 32.11       MB
c CPU time                 : 0.38        s
       \endverbatim
       </li>
       <li> precosat236
       \verbatim
shell> precosat236 r1_keyfind.cnf
c 0 conflicts, 0 decisions, 0 random
c prps: 851728 propagations, 7.74 megaprops
c
c 0.1 seconds, 4 MB max, 2 MB recycled
     \endverbatim
     </li>
     <li> precosat-570.1:
     \verbatim
shell> precosat-570.1 r1_keyfind.cnf
c 414 conflicts, 10588 decisions, 2 random
c 10 iterations, 22 restarts, 0 skipped
c 0.4 seconds, 4 MB max, 0 MB recycled
     \endverbatim
     </li>
     <li> OKsolver_2002:
     \verbatim
shell> OKsolver_2002-O3-DNDEBUG r1_keyfind.cnf
c running_time(sec)                     0.7
c number_of_nodes                       1
c number_of_single_nodes                0
c number_of_quasi_single_nodes          0
c number_of_2-reductions                255
c number_of_pure_literals               0
c number_of_autarkies                   0
c number_of_missed_single_nodes         0
c max_tree_depth                        0
c number_of_1-autarkies                 0
c number_of_new_2-clauses               0
     \endverbatim
     </li>
     <li> Cryptominisat and the OKsolver solve the instance by UCP. Why
     don't the others? Is this just luck or stronger reductions? </li>
    </ul>
   </li>
   <li> We can check we get the right result with:
   \verbatim
shell> OKsolver_2002-O3-DNDEBUG -O r1_keyfind.cnf | grep "^v" | $OKlib/Experimentation/Investigations/Cryptography/AdvancedEncryptionStandard/validate_aes_assignment 1 1 2 8 0 && echo "VALID"
VALID
     \endverbatim
     </li>
    </ul>
   </li>
   <li> Generating 20 random plaintext-ciphertext pairs and running
   solvers instances instantiated with these pairs to find the key:
    <ul>
     <li> Computing the random plaintext-ciphertext pairs:
     \verbatim
for seed : 1 thru 20 do output_ss_random_pc_pair(seed,num_rounds,num_columns,num_rows,exp,final_round_b);
     \endverbatim
     </li>
     <li> Running minisat-2.2.0:
     \verbatim
shell> col=1; row=2; e=8; r=1; for s in $(seq 1 5); do
  for k in $(seq 1 20); do
    echo "Seed ${s}; Key ${k} Round ${r}";
    AppendDimacs-O3-DNDEBUG ssaes_r${r}_c${col}_rw${row}_e${e}_f0.cnf ssaes_pcpair_r${r}_c${col}_rw${row}_e${e}_f0_s${k}.cnf | RandomShuffleDimacs-O3-DNDEBUG $s > r${r}_k${k}_s${s}.cnf;
    minisat-2.2.0 r${r}_k${k}_s${s}.cnf > minisat_r${r}_k${k}_s${s}.result 2>&1;
  done;
done;
shell> echo "n  c  t  sat  cfs dec rts r1 mem ptime stime cfl r k s" > minisat_results; for s in $(seq 1 5); do
  for k in $(seq 1 20); do
    cat minisat_r${r}_k${k}_s${s}.result | awk -f $OKlib/Experimentation/ExperimentSystem/SolverMonitoring/ExtractMinisat.awk | awk " { print \$0 \"  $r  $k $s\" }";
  done;
done >> minisat_results;
     \endverbatim
     yields:
     \verbatim
shell> oklib --R
E = read.table("minisat_results", header=TRUE)
EM = aggregate(E, by=list(r=E$r), FUN=mean)
EM
  r    n        c      t sat   cfs     dec  rts       r1 mem  ptime  stime
1 1 3264 52483.23 0.1425   1 471.5 7827.61 4.09 416099.2  22 0.0375 0.0452
       cfl r    k s
1 137249.9 1 10.5 3
     \endverbatim
     </li>
     <li> Running OKsolver_2002:
     \verbatim
shell> col=1; row=2; e=8; r=1; for s in $(seq 1 5); do
  for k in $(seq 1 20); do
    echo "Seed ${s}; Key ${k} Round ${r}";
    AppendDimacs-O3-DNDEBUG ssaes_r${r}_c${col}_rw${row}_e${e}_f0.cnf ssaes_pcpair_r${r}_c${col}_rw${row}_e${e}_f0_s${k}.cnf | RandomShuffleDimacs-O3-DNDEBUG $s > r${r}_k${k}_s${s}.cnf;
    OKsolver_2002-O3-DNDEBUG r${r}_k${k}_s${s}.cnf > oksolver_r${r}_k${k}_s${s}.result 2>&1;
  done;
done;
shell> echo "n  c  l  t  sat  nds  r1  r2  pls  ats h file n2cr  dmcl dn  dc  dl snds qnds mnds  tel  oats  n2cs  m2cs r k s" > oksolver_results; for s in $(seq 1 5); do
  for k in $(seq 1 20); do
    cat oksolver_r${r}_k${k}_s${s}.result | awk -f $OKlib/Experimentation/ExperimentSystem/SolverMonitoring/ExtractOKsolver.awk | awk " { print \$0 \"  $r  $k $s\" }";
  done;
done >> oksolver_results;
     \endverbatim
     yields:
     \verbatim
shell> oklib --R
E = read.table("oksolver_results", header=TRUE)
EM = aggregate(E, by=list(r=E$r), FUN=mean)
EM
  r    n     c      l     t sat nds r1      r2 pls  ats h file  n2cr dmcl dn
1 1 3264 52564 154504 2.829   1   1 40 2556.63   0 0.55 0   NA 49232    0 40
   dc  dl snds qnds mnds tel oats n2cs m2cs r    k s
1 120 360    0    0    0   0    0    0    0 1 10.5 3
     \endverbatim
     </li>
    </ul>
   </li>
  </ul>


  \todo Using the "minimum" box translation
  <ul>
   <li> Translating the AES cipher treating Sboxes and field multiplications
   as whole boxes and translating these boxes using small CNFs.
   </li>
   <li> The CNFs for the Sbox and multiplications:
   \verbatim
/* Multiplication by 02: */
maxima> FieldMul2CNF : [{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16},{{-9,2},{-2,9},{-10,3},{-3,10},{-11,4},{-4,11},{-12,-5,-1},{-12,1,5},{-5,1,12},{-1,5,12},{-13,-6,-1},{-1,6,13},{-14,7},{-7,14},{-15,1,8},{-8,1,15},{-16,-15,-8},{-16,8,15},{-13,6,16},{-6,13,16}}]$
set_hm(ss_field_cnfs,[8,2], FieldMul2CNF));
/* Multiplication by 03: */
maxima> FieldMul3CNF :
 [[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16],
  [{-9,-2,-1},{-2,1,9},{-10,2,3},{-10,-9,-3,1},{-10,-3,-1,9},{-3,2,10},{-9,1,3,10},{-1,3,9,10},{-11,-4,-3},{-11,3,4},{-4,3,11},{-3,4,11},{-12,-5,-4,1},{-12,-4,-1,5},{-5,1,4,12},{-1,4,5,12},{-13,-5,-1,6},{-13,1,5,6},{-13,-12,-6,4},{-13,-6,-4,12},{-6,-5,-1,13},{-6,1,5,13},
   {-12,4,6,13},{-4,6,12,13},{-14,-7,-6},{-14,6,7},{-7,6,14},{-6,7,14},{-16,-8,-1},{-16,1,8},{-16,-15,-7},{-16,7,15},{-8,1,16},{-1,8,16},{-15,7,16},{-7,15,16}]]$
set_hm(ss_field_cnfs,[8,2], FieldMul3CNF));
/* Sbox: */
maxima> output_rijnsbox_fullcnf_stdname();
shell> QuineMcCluskeySubsumptionHypergraph-n16-O3-DNDEBUG AES_Sbox_full.cnf > AES_Sbox_shg.cnf
shell> cat AES_Sbox_shg.cnf | MinOnes2WeightedMaxSAT-O3-DNDEBUG > AES_Sbox_shg.wcnf
shell> ubcsat-okl  -alg gsat -w -runs 100 -cutoff 40000000 -wtarget 294 -solve 1 -seed 3213901809 -i AES_Sbox_shg.wcnf -r model AES_Sbox_s294.ass;
shell> cat  AES_Sbox_full.cnf_primes | FilterDimacs AES_Sbox_s294.ass > AES_Sbox_s294.cnf
maxima> SboxMinCNF : read_fcl_f("AES_Sbox_s294.cnf");
maxima> set_hm(ss_sbox_cnfs,8, SboxMinCNF));
   \endverbatim
   </li>
   <li> Generating small scale AES for 1 + 1/3 rounds:
   \verbatim
shell> mkdir aes_1_1_8/canon
shell> cd aes_1_1_8/canon
shell> oklib --maxima
oklib_load_all()$
num_rounds : 1$
num_rows : 2$
num_columns : 1$
exp : 8$
final_round_b : false$
box_tran : aes_small_box$
oklib_monitor : true$
mc_tran : aes_mc_bidirectional$
output_ss_fcl_std(rounds, num_columns, num_rows, exp, final_round_b, box_tran, mc_tran)$

shell> cat ssaes_r1_c1_rw2_e8_f0.cnf | ExtendedDimacsFullStatistics-O3-DNDEBUG n
 n non_taut_c red_l taut_c orig_l comment_count finished_bool
3264 52532 154472 0 154472 3265 1
 length count
 n non_taut_c red_l taut_c orig_l comment_count finished_bool
192 1696 9332 0 9332 193 1
 length count
1 8
2 32
3 416
4 64
6 572
7 508
8 96
   \endverbatim
   </li>
   <li> In this translation, we have:
   <ul>
    <li> One full round (Key Addition, SubBytes, and MixColumn operation).
    </li>
    <li> 4 Sboxes (2 from SubBytes; 2 from key schedule). </li>
    <li> 72 additions (32 from key additions; 32 from MixColumns; 8 from
    key schedule). </li>
    <li> 4 multiplications by 02, 03 (from MixColumns).
    </li>
    <li> 8 bits for the constant in the key schedule. </li>
   </ul>
   </li>
   <li> Note that as this variant has only one column, the key schedule
   applies Sbox(K_i) + C rather than Sbox(K_i) + K_j + C where K_i and
   K_j are key words from the previous round key. </li>
   <li> The Sboxes and multiplications use the "minimum" translations,
   which have the following number of clauses of each length:
   \verbatim
maxima> ncl_list_fcs(ev_hm(ss_sbox_cnfs,8));
[[6,143],[7,127],[8,24]]
maxima> ncl_list_fcs(ev_hm(ss_field_cnfs,[8,2]))
[[2,8],[3,12]]
maxima> ncl_list_fcs(ev_hm(ss_field_cnfs,[8,3]))
[[3,20],[4,16]]
   \endverbatim
   </li>
   <li> The number of clauses of each length in the translation are:
    <ul>
     <li> 8 unit-clauses (key schedule constant). </li>
     <li> 32 binary clauses (4 multiplications by 02). </li>
     <li> 416 ternary clauses (72 arity two additions; 4 multiplications * 2).
     </li>
     <li> 64 clauses of length four (4 multiplications by 03). </li>
     <li> 572 clauses of length six (4 Sboxes). </li>
     <li> 508 clauses of length seven (4 Sboxes). </li>
     <li> 96 clauses of length eight (4 Sboxes). </li>
    </ul>
   </li>
   <li> Generate random assignments for the plaintext and ciphertext, leaving
   the key unknown with a single plaintext-ciphertext pair:
    <ul>
     <li> Generate random assignments for the plaintext and ciphertext, leaving
     the key unknown:
     \verbatim
maxima> output_ss_random_pc_pair(seed,rounds,num_columns,num_rows,exp,final_round_b);
     \endverbatim
     Merge the assignments with the translations:
     \verbatim
shell> AppendDimacs-O3-DNDEBUG ssaes_r1_c1_rw2_e4_f0.cnf ssaes_pkpair_r1_c1_rw2_e4_f0_s1.cnf > r1_keyfind.cnf; done
     \endverbatim
     </li>
     <li> All solvers solve in <1s:
      <ul>
       <li> precosat236
       \verbatim
shell> precosat236 r1_keyfind.cnf
c 2084 conflicts, 2673 decisions, 1 random
c 0 iterations, 3 restarts, 10 skipped
c prps: 29841 propagations, 0.99 megaprops
c 0.0 seconds, 0 MB max, 0 MB recycled
       \endverbatim
       </li>
       <li> precosat-570.1:
       \verbatim
shell> precosat-570.1 r1_keyfind.cnf
c 2899 conflicts, 3880 decisions, 0 random
c 1 iterations, 28 restarts, 43 skipped
c 0.0 seconds, 0 MB max, 0 MB recycled
       \endverbatim
       </li>
       <li> minisat-2.2.0:
       \verbatim
shell> minisat-2.2.0 r1_keyfind.cnf
restarts              : 11
conflicts             : 1684           (168400 /sec)
decisions             : 1938           (0.00 % random) (193800 /sec)
propagations          : 23607          (2360700 /sec)
conflict literals     : 16248          (15.68 % deleted)
Memory used           : 19.00 MB
CPU time              : 0.01 s
       \endverbatim
       </li>
       <li> cryptominisat:
       \verbatim
shell> cryptominisat r1_keyfind.cnf
c restarts                 : 6
c dynamic restarts         : 0
c static restarts          : 6
c conflicts                : 1827        (60900.00  / sec)
c decisions                : 2367        (0.00      % random)
c bogo-props               : 3357007     (111900233.33 / sec)
c conflict literals        : 17009       (18.35     % deleted)
c Memory used              : 29.82       MB
c CPU time                 : 0.03        s
       \endverbatim
       </li>
       <li> glucose:
       \verbatim
shell> glucose r1_keyfind.cnf
<snip>
c restarts              : 1
c conflicts             : 5583           (62033 /sec)
c decisions             : 5897           (1.56 % random) (65522 /sec)
c propagations          : 114998         (1277756 /sec)
c conflict literals     : 55877          (22.00 % deleted)
c Memory used           : 2.53 MB
c CPU time              : 0.09 s
       \endverbatim
       </li>
       <li> OKsolver_2002:
       \verbatim
shell> OKsolver_2002-O3-DNDEBUG r1_keyfind.cnf
c running_time(sec)                     2.2
c number_of_nodes                       21651
c number_of_single_nodes                4
c number_of_quasi_single_nodes          0
c number_of_2-reductions                39101
c number_of_pure_literals               0
c number_of_autarkies                   0
c number_of_missed_single_nodes         4
c max_tree_depth                        16
c number_of_table_enlargements          0
c number_of_1-autarkies                 0
c number_of_new_2-clauses               0
       \endverbatim
       </li>
      </ul>
     </li>
     <li> We can check we get the right result with:
     \verbatim
shell> OKsolver_2002-O3-DNDEBUG -O r1_keyfind.cnf | grep "^v" | $OKlib/Experimentation/Investigations/Cryptography/AdvancedEncryptionStandard/validate_aes_assignment 1 1 2 8 0 && echo "VALID"
VALID
     \endverbatim
     </li>
    </ul>
   </li>
   <li> Generating 20 random plaintext-ciphertext pairs and running
   solvers instances instantiated with these pairs to find the key:
    <ul>
     <li> Computing the random plaintext-ciphertext pairs:
     \verbatim
for seed : 1 thru 20 do output_ss_random_pc_pair(seed,num_rounds,num_columns,num_rows,exp,final_round_b);
     \endverbatim
     </li>
     <li> Running minisat-2.2.0:
     \verbatim
shell> col=1; row=2; e=8; r=1; for s in $(seq 1 5); do
  for k in $(seq 1 20); do
    echo "Seed ${s}; Key ${k} Round ${r}";
    AppendDimacs-O3-DNDEBUG ssaes_r${r}_c${col}_rw${row}_e${e}_f0.cnf ssaes_pcpair_r${r}_c${col}_rw${row}_e${e}_f0_s${k}.cnf | RandomShuffleDimacs-O3-DNDEBUG $s > r${r}_k${k}_s${s}.cnf;
    minisat-2.2.0 r${r}_k${k}_s${s}.cnf > minisat_r${r}_k${k}_s${s}.result 2>&1;
  done;
done;
shell> echo "n  c  t  sat  cfs dec rts r1 mem ptime stime cfl r k s" > minisat_results; for s in $(seq 1 5); do
  for k in $(seq 1 20); do
    cat minisat_r${r}_k${k}_s${s}.result | awk -f $OKlib/Experimentation/ExperimentSystem/SolverMonitoring/ExtractMinisat.awk | awk " { print \$0 \"  $r  $k $s\" }";
  done;
done >> minisat_results;
     \endverbatim
     yields:
     \verbatim
shell> oklib --R
E = read.table("minisat_results", header=TRUE)
EM = aggregate(E, by=list(r=E$r), FUN=mean)
EM
  r   n       c      t sat     cfs     dec  rts       r1 mem ptime stime
1 1 192 1646.96 0.0096   1 1578.48 1836.57 9.69 22142.69  19     0 5e-04
       cfl r    k s
1 15286.49 1 10.5 3
     \endverbatim
     </li>
     <li> Running OKsolver_2002:
     \verbatim
shell> col=1; row=2; e=8; r=1; for s in $(seq 1 5); do
  for k in $(seq 1 20); do
    echo "Seed ${s}; Key ${k} Round ${r}";
    AppendDimacs-O3-DNDEBUG ssaes_r${r}_c${col}_rw${row}_e${e}_f0.cnf ssaes_pcpair_r${r}_c${col}_rw${row}_e${e}_f0_s${k}.cnf | RandomShuffleDimacs-O3-DNDEBUG $s > r${r}_k${k}_s${s}.cnf;
    OKsolver_2002-O3-DNDEBUG r${r}_k${k}_s${s}.cnf > oksolver_r${r}_k${k}_s${s}.result 2>&1;
  done;
done;
shell> echo "n  c  l  t  sat  nds  r1  r2  pls  ats h file n2cr  dmcl dn  dc  dl snds qnds mnds  tel  oats  n2cs  m2cs r k s" > oksolver_results; for s in $(seq 1 5); do
  for k in $(seq 1 20); do
    cat oksolver_r${r}_k${k}_s${s}.result | awk -f $OKlib/Experimentation/ExperimentSystem/SolverMonitoring/ExtractOKsolver.awk | awk " { print \$0 \"  $r  $k $s\" }";
  done;
done >> oksolver_results;
     \endverbatim
     yields:
     \verbatim
shell> oklib --R
E = read.table("oksolver_results", header=TRUE)
EM = aggregate(E, by=list(r=E$r), FUN=mean)
EM
  r   n    c    l     t sat      nds r1       r2 pls ats    h file n2cr dmcl dn
1 1 192 1728 9364 1.448   1 12638.98 40 23778.04   0   0 16.3   NA  112    0 40
   dc  dl snds qnds mnds tel oats n2cs m2cs r    k s
1 120 360 2.93    0 2.01   0    0    0    0 1 10.5 3
     \endverbatim
     </li>
    </ul>
   </li>
  </ul>


  \todo Using the 1-base box translation
  <ul>
   <li> Generating a 1-base for the S-box from
   Cryptography/AdvancedEncryptionStandard/plans/SAT2011/Representations/Sbox_8.hpp. :
   \verbatim
maxima> output_rijnsbox_fullcnf_stdname();
shell> QuineMcCluskey-n16-O3-DNDEBUG AES_Sbox_full.cnf > AES_Sbox_pi.cnf
shell> RandomShuffleDimacs-O3-DNDEBUG 103 < AES_Sbox_pi.cnf | SortByClauseLength-O3-DNDEBUG > AES_Sbox_sortedpi.cnf
shell> RUcpGen-O3-DNDEBUG AES_Sbox_sortedpi.cnf > AES_Sbox_gen.cnf
shell> RandomShuffleDimacs-O3-DNDEBUG 1 < AES_Sbox_gen.cnf | SortByClauseLengthDescending-O3-DNDEBUG | RUcpBase-O3-DNDEBUG > AES_Sbox_base.cnf
shell> cat AES_Sbox_base.cnf | ExtendedDimacsFullStatistics-O3-DNDEBUG n
 n non_taut_c red_l taut_c orig_l comment_count finished_bool
16 4398 30108 0 30108 0 1
 length count
5 1
6 1187
7 2703
8 503
9 4
   \endverbatim
   </li>
   <li> Generating a 1-base for the multiplication by 02 and 03 from
   Cryptography/AdvancedEncryptionStandard/plans/SAT2011/Representations/Sbox_8.hpp. :
   \verbatim
maxima> output_rijn_mult_fullcnf_stdname(2);
shell> QuineMcCluskey-n16-O3-DNDEBUG AES_byte_field_mul_full_2.cnf > AES_byte_field_mul_2_pi.cnf
shell> RandomShuffleDimacs-O3-DNDEBUG 1 < AES_byte_field_mul_2_pi.cnf | SortByClauseLength-O3-DNDEBUG > AES_byte_field_mul_2_sortedpi.cnf
shell> RUcpGen-O3-DNDEBUG AES_byte_field_mul_2_sortedpi.cnf > AES_byte_field_mul_2_gen.cnf
shell> RandomShuffleDimacs-O3-DNDEBUG 1 < AES_byte_field_mul_2_gen.cnf | SortByClauseLengthDescending-O3-DNDEBUG | RUcpBase-O3-DNDEBUG > AES_byte_field_mul_2_base.cnf
shell> cat AES_byte_field_mul_2_base.cnf | ExtendedDimacsFullStatistics-O3-DNDEBUG n
 n non_taut_c red_l taut_c orig_l comment_count finished_bool
16 22 56 0 56 0 1
 length count
2 10
3 12
maxima> output_rijn_mult_fullcnf_stdname(3);
shell> QuineMcCluskey-n16-O3-DNDEBUG AES_byte_field_mul_full_3.cnf > AES_byte_field_mul_3_pi.cnf
shell> RandomShuffleDimacs-O3-DNDEBUG 1 < AES_byte_field_mul_3_pi.cnf | SortByClauseLength-O3-DNDEBUG > AES_byte_field_mul_3_sortedpi.cnf
shell> RUcpGen-O3-DNDEBUG AES_byte_field_mul_3_sortedpi.cnf > AES_byte_field_mul_3_gen.cnf
shell> RandomShuffleDimacs-O3-DNDEBUG 1 < AES_byte_field_mul_3_gen.cnf | SortByClauseLengthDescending-O3-DNDEBUG | RUcpBase-O3-DNDEBUG > AES_byte_field_mul_3_base.cnf
shell> cat AES_byte_field_mul_3_base.cnf | ExtendedDimacsFullStatistics-O3-DNDEBUG n
 n non_taut_c red_l taut_c orig_l comment_count finished_bool
16 80 328 0 328 0 1
 length count
3 24
4 24
5 32
   \endverbatim
   </li>
   <li> Translating the AES cipher treating Sboxes and field multiplications
   as whole boxes and translating these boxes using 1-bases.
   </li>
   <li> Generating small scale AES for 1 + 1/3 rounds:
   \verbatim
shell> mkdir aes_1_1_8/canon
shell> cd aes_1_1_8/canon
shell> oklib --maxima
oklib_load_all()$
num_rounds : 1$
num_rows : 2$
num_columns : 1$
exp : 8$
final_round_b : false$
box_tran : aes_rbase_box$
oklib_monitor : true$
mc_tran : aes_mc_bidirectional$
set_hm(ss_sbox_rbase_cnfs,8,read_fcl_f("AES_Sbox_base.cnf"))$
set_hm(ss_field_rbase_cnfs,[8,2],read_fcl_f("AES_byte_field_mul_2_base.cnf"))$
set_hm(ss_field_rbase_cnfs,[8,3],read_fcl_f("AES_byte_field_mul_3_base.cnf"))$
output_ss_fcl_std(num_rounds, num_columns, num_rows, exp, final_round_b, box_tran, mc_tran)$

shell> cat ssaes_r1_c1_rw2_e8_f0.cnf | ExtendedDimacsFullStatistics-O3-DNDEBUG n
 n non_taut_c red_l taut_c orig_l comment_count finished_bool
192 18296 122840 0 122840 193 1
 length count
1 8
2 40
3 432
4 96
5 132
6 4748
7 10812
8 2012
9 16
   \endverbatim
   </li>
   <li> In this translation, we have:
   <ul>
    <li> One full round (Key Addition, SubBytes, and MixColumn operation).
    </li>
    <li> 4 Sboxes (2 from SubBytes; 2 from key schedule). </li>
    <li> 72 additions (32 from key additions; 32 from MixColumns; 8 from
    key schedule). </li>
    <li> 4 multiplications by 02, 03 (from MixColumns).
    </li>
    <li> 8 bits for the constant in the key schedule. </li>
   </ul>
   </li>
   <li> Note that as this variant has only one column, the key schedule
   applies Sbox(K_i) + C rather than Sbox(K_i) + K_j + C where K_i and
   K_j are key words from the previous round key. </li>
   <li> The Sboxes and multiplications use 1-base translations,
   which have the following number of clauses of each length:
   \verbatim
maxima> ncl_list_fcs(ev_hm(ss_sbox_rbase_cnfs,8));
[[5,1],[6,1187],[7,2703],[8,503],[9,4]]
maxima> ncl_list_fcs(ev_hm(ss_field_rbase_cnfs,[8,2]))
[[2,10],[3,12]]
maxima> ncl_list_fcs(ev_hm(ss_field_rbase_cnfs,[8,3]))
[[3,24],[4,24],[5,32]]
   \endverbatim
   </li>
   <li> The number of clauses of each length in the translation are:
    <ul>
     <li> 8 unit-clauses (key schedule constant). </li>
     <li> 40 binary clauses (4 multiplications by 02). </li>
     <li> 432 ternary clauses (72 arity two additions; 4 multiplications * 2).
     </li>
     <li> 96 clauses of length four (4 multiplications by 03). </li>
     <li> 132 clauses of length five (4 S-boxes; 4 multiplications by 03).
     </li>
     <li> 4748 clauses of length six (4 S-boxes). </li>
     <li> 10812 clauses of length seven (4 S-boxes). </li>
     <li> 2012 clauses of length eight (4 S-boxes). </li>
     <li> 16 clauses of length nine (4 S-boxes). </li>
    </ul>
   </li>
   <li> Generating 20 random plaintext-ciphertext pairs and running
   solvers instances instantiated with these pairs to find the key:
    <ul>
     <li> Computing the random plaintext-ciphertext pairs:
     \verbatim
for seed : 1 thru 20 do output_ss_random_pc_pair(seed,num_rounds,num_columns,num_rows,exp,final_round_b);
     \endverbatim
     </li>
     <li> Running minisat-2.2.0:
     \verbatim
shell> col=1; row=2; e=8; r=1; for s in $(seq 1 5); do
  for k in $(seq 1 20); do
    echo "Seed ${s}; Key ${k} Round ${r}";
    AppendDimacs-O3-DNDEBUG ssaes_r${r}_c${col}_rw${row}_e${e}_f0.cnf ssaes_pcpair_r${r}_c${col}_rw${row}_e${e}_f0_s${k}.cnf | RandomShuffleDimacs-O3-DNDEBUG $s > r${r}_k${k}_s${s}.cnf;
    minisat-2.2.0 r${r}_k${k}_s${s}.cnf > minisat_r${r}_k${k}_s${s}.result 2>&1;
  done;
done;
shell> echo "n  c  t  sat  cfs dec rts r1 mem ptime stime cfl r k s" > minisat_results; for s in $(seq 1 5); do
  for k in $(seq 1 20); do
    cat minisat_r${r}_k${k}_s${s}.result | awk -f $OKlib/Experimentation/ExperimentSystem/SolverMonitoring/ExtractMinisat.awk | awk " { print \$0 \"  $r  $k $s\" }";
  done;
done >> minisat_results;
     \endverbatim
     yields:
     \verbatim
shell> oklib --R
E = read.table("minisat_results", header=TRUE)
EM = aggregate(E, by=list(r=E$r), FUN=mean)
EM
  r   n        c      t sat    cfs    dec  rts       r1 mem  ptime stime
1 1 192 18248.62 0.5836   1 335.81 363.35 3.33 14769.97  20 0.0066 0.551
      cfl r    k s
1 2638.52 1 10.5 3
     \endverbatim
     </li>
     <li> Running OKsolver_2002:
     \verbatim
shell> col=1; row=2; e=8; r=1; for s in $(seq 1 5); do
  for k in $(seq 1 20); do
    echo "Seed ${s}; Key ${k} Round ${r}";
    AppendDimacs-O3-DNDEBUG ssaes_r${r}_c${col}_rw${row}_e${e}_f0.cnf ssaes_pcpair_r${r}_c${col}_rw${row}_e${e}_f0_s${k}.cnf | RandomShuffleDimacs-O3-DNDEBUG $s > r${r}_k${k}_s${s}.cnf;
    OKsolver_2002-O3-DNDEBUG r${r}_k${k}_s${s}.cnf > oksolver_r${r}_k${k}_s${s}.result 2>&1;
  done;
done;
shell> echo "n  c  l  t  sat  nds  r1  r2  pls  ats h file n2cr  dmcl dn  dc  dl snds qnds mnds  tel  oats  n2cs  m2cs r k s" > oksolver_results; for s in $(seq 1 5); do
  for k in $(seq 1 20); do
    cat oksolver_r${r}_k${k}_s${s}.result | awk -f $OKlib/Experimentation/ExperimentSystem/SolverMonitoring/ExtractOKsolver.awk | awk " { print \$0 \"  $r  $k $s\" }";
  done;
done >> oksolver_results;
     \endverbatim
     yields:
     \verbatim
shell> oklib --R
E = read.table("oksolver_results", header=TRUE)
EM = aggregate(E, by=list(r=E$r), FUN=mean)
EM
  r   n     c      l     t sat    nds r1     r2 pls ats    h file n2cr dmcl dn
1 1 192 18328 122872 2.572   1 620.29 40 913.57   0 0.3 11.8   NA  120    0 40
   dc  dl snds qnds mnds tel oats n2cs m2cs r    k s
1 120 360 0.26    0 0.26   0    0    0    0 1 10.5 3
     \endverbatim
     </li>
    </ul>
   </li>
  </ul>

*/
