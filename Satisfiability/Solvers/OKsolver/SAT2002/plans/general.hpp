// Oliver Kullmann, 17.8.2007 (Swansea)

/*!
  \file Solvers/OKsolver/SAT2002/plans/general.hpp
  \brief Plans on the maintenance of the code for the
  old OKsolver


  \todo Enable finding all solutions
  <ul>
   <li> MJHH made the request, that the OKsolver can continue
   after a solution was found (and thus can find all solutions). </li>
   <li> The easiest (and most natural) way seems to be to treat a
   satisfying assignment found just as a falsifying assignment:
    <ol>
     <li> Special operations like counting the number of satisfying
     assignments found, output of the assignment or turning
     off tree pruning have to be carried out. </li>
     <li> Then backtracking is performed as for falsifying
     assignments. </li>
     <li> If the whole tree has been processed, then one has to check
     (perhaps best by some dedicated boolean variable) whether
     somewhere a satisfying assignment was found (for the overall
     return value). </li>
     <li> If already the input was found satisfiabile, then no further
     search for another satisfying assignment is needed, since the
     assignment was forced. </li>
    </ol>
   </li>
   <li> All places need to be identified where a solution
   can be found:
    <ol>
     <li> The global variable "erfuellt" (declared in
     Solvers/OKsolver/SAT2002/Filter.h) communicates wether the "filter"
     found the formula satisfiable. </li>
     <li> There is only one place, the loop in
     OKsolver/SAT2002/OKsolver_2002_lnk.c over all variables, where "erfuellt"
     is used, and where a satisfying assignment can be found. </li>
     <li> Currently in case the filter found a satisfying assignment,
     the assignment is actually applied (the filter uses a lazy
     data structure to perform assignments, without actually changing
     the formula). Why is this needed?? The comment says it is needed
     for the output?
      <ol>
       <li> The reason is simply convenience: The satisfying assignment
       is split in the current working assignment and the look-ahead
       assignment, and by applying the look-ahead assignment we have
       everything "in one place". </li>
       <li> This hack should be eliminated, and the function for outputting
       the satisfying assignment should just accept to partial assignments
       as input. </li>
      </ol>
     </li>
     <li> Now the problem is the simulation of the recursion:
      <ol>
       <li> The question is whether we are in branch 1 or in branch 2. </li>
       <li> If in branch 1, then we should go to label nachSAT1, however without
       undoing the branching, that is, we go directly to the second branch. </li>
       <li> If in branch 2, then we go to label nachSAT2, however
       without undoing the branching; and also the output "UNSAT" at
       the root must be prevented. </li>
      </ol>
     </li>
    </ol>
   </li>
   <li> With the new option "ALLSAT" in principle we have another
   factor of 2 for the test cases. There is no way out, must be done. </li>
   <li> DONE
   So another "#ifdef" needs to be introduced:
    <ol>
     <li> Macro ALLSAT if set means all satisfying assignments will
     be determined; default is unset. </li>
     <li> If ALLSAT is set then macro NSAT_BITS determines in the
     number N of bits in type uint_fastN_t (obtained by conditional
     inclusion of stdint.h). "nsat_t" is a typedef for this type. </li>
     <li> Default value of NSAT_BITS is 64. </li>
     <li> Variable nsat of type nsat_t counts satisfying assignments. </li>
     <li> DONE (yet we only count in modular arithmetic)
     Can we determine overflow? </li>
     <li> DONE (ignored yet)
     This would be easier with an int type? </li>
    </ol>
   </li>
   <li> DONE (first excluded; to be done later)
   Interaction with option BELEGUNG
    <ol>
     <li> Hopefully only function AusgabeBelegung needs to be called
     additionally. </li>
     <li> For that to work, the file pointer needed in case of output
     to a file needs to be computed in advance, and a global variable
     stores the output-stream pointer (either the file or stdout; null
     if no output of satisfying assignments). </li>
     <li> In case of file-output we just output all satisfying
     assignments into the file. </li>
     <li> A problem arises with option OUTPUTTREEDATAXML --- what
     to do here (and what is this option about?)?
     </li>
    </ol>
   </li>
   <li> DONE (first excluded; to be done later)
   Interaction with option BAUMRES
    <ol>
     <li> As soon as one satisfying assignment was found, then
     above that point tree pruning is turned off. </li>
     <li> Perhaps easiest by using a null pointer. </li>
    </ol>
   </li>
  </ul>


  \todo Documentation problems
  <ul>
   <li> A lot of code (and doxygen-documentation) is conditionalised
   --- and thus doesn't show up in the doxygen-documentation! </li>
   <li> However we want the documentation of the whole code; how to
   achieve this? </li>
   <li> On the other hand, it it informative what is (and what is not)
   defined by default. </li>
  </ul>


  \todo Language standards
  <ul>
   <li> The old OKsolver is a C99 program. </li>
   <li> Use standard include-guards. </li>
   <li> Why are there these comments that string.h is included because of C++? Seems we should
   remove them. </li>
   <li> For the xml-output we should then state that C is the programming language. </li>
   <li> Where we touch the code, we change the style to the standard
   (otherwise we leave it). </li>
   <li> All includes need to be changed to the library-style. Or? Perhaps, due to the
   exceptional "historical" character, we don't do this here? Emphasising, that there
   are no reusable components here?! </li>
   <li> Since the function specifier "inline" is available with C99, we should
   remove the little apparatus with "KEININLINE" and "__inline__" (and replace
   "__inline__" everywhere with "inline"). </li>
   <li> Deeper changes like const-introduction only later. </li>
   <li> DONE (stick to C) Perhaps move everything to C++ (but no real changes to any data structures, etc.,
   only using C++ header files etc.). Or?? </li>
   <li> DONE (GesamtOKs.cpp removed) Why does GesamtOKs.cpp want to be a C++ program --- maybe we just stick to C?
   Would be more honest! On the other hand, we are more knowledgeable with C++.)
   The purpose of GesamtOKs.cpp likely was to enable the use of C++ inlining --- but
   also C99 has the inline keyword. </li>
   <li>  DONE (stick to C) The program uses typical C-methods to simulate abstract data types (a functional
   interface is build, hiding all pointer access, which happens in the implementation files).
   So it appears that we better stick to C. </li>
  </ul>


  \todo Buildsystem (replacing Buildtools/UebersetzungOKs.plx)
  <ul>
   <li> That Perl-script had the following purpose:
    <ol>
     <li> Reflect the settings of macro, compilation-options and
     the choice of heuristics etc. in the name of the
     executable (with suffix ".sa"). </li>
     <li> Compile always a standard selection of combinations of
     macro-settings (for the different variants of the OKsolver). </li>
     <li> Create directories with a running number, containing
     the created executables, for ease of archiving. </li>
     <li> Take all compilation units, and insert them into one big
     stand-alone file "GesamtOKs.cpp". </li>
    </ol>
   </li>
   <li> We need to incorporate this functionality with our
   build system. </li>
   <li> Since we do not do any more experiments on variations of
   the old OKsolver, we do not need to create the sequence
   of directories anymore here. </li>
   <li> There are three programs:
    <ol>
     <li> OKsolver_2002.c : standard C program (assumes linking with the other compilation units) </li>
     <li> OKsolver_2002_lnk.c : Same as OKsolver_2002.c, but includes all other compilation units, and thus
     needs no linking. </li>
     <li> DONE (removed) GesamtOKs.cpp : Produced by UebersetzungOKs.plx out of all the compilation units
     (and is treated as C++). (However OK.h and Parameter.h are not inserted, but included.) </li>
    </ol>
   <li> There is no need anymore for the created file GesamtOKs.cpp, however we need some
   tests on the running times of GesamtOKs, OKsolver_2002 and OKsolver_2002_lnk, and this also
   compared with the existing OKsolver-binaries. Optimally, we could do this simply with our build system
   (as planned), but perhaps for the time being we just do some ad-hoc testing.
   </li>
   <li> The difference between OKsolver_2002.c and OKsolver_2002_lnk.c is that the latter enables more inlining ---
   can't this be achieved otherwise (through inline-specifications)? </li>
   <li> The build system links the C programs as C++ programs; shouldn't make a big
   difference for now, but should be rectified with the new system. </li>
   <li> The build system doesn't know about the dependency of OKsolver_2002.c on the other .c-programs
   (to which it links) --- this needs to be addressed!
    <ol>
     <li> For each program P, one additional dependency file has to be created which contains
     the rule with target P, where the prerequisites are all the files P links together. </li>
     <li> See the plans under Buildsystem. </li>
    </ol>
   </li>
   <li> Compilation of lokalesLernen.c on its own should only happen with LOKALLERNEN defined
   (without it a compile-time error should ensue). </li>
  </ul>


  \todo Complete the help facilities of the OKsolver
  <ul>
   <li> There are quite a few options available, and these should be documented. </li>
  </ul>


  \todo Add doxygen-documentation
  <ul>
   <li> We want to leave the code mainly as it is, but we can add doxygen
   documentation. </li>
  </ul>


  \todo Write docus-pages
  <ul>
   <li> Should explain the history and usage. </li>
   <li> Also the extension possibilities. </li>
  </ul>


  \todo Add asserts throughout


  \todo Create systematic application tests
  <ul>
   <li> Differentiate between solver runs which are expected to succeed and runs which
   are expected to fail (so that in the latter case the output to stderr can be suppressed). </li>
   <li> All possible syntactic errors diagnosed by the OKsolver need be checked. </li>
   <li> Tautological clauses and repeated literals in clauses need to be checked. </li>
   <li> Output of satisfying assignments needs to be checked. </li>
   <li> We need also to check the other output formats. </li>
  </ul>


  \todo Investigate unit-testing
  <ul>
   <li> Optimally, we write unit tests for all main components. </li>
   <li> Possibly, the code doesn't allow easy unit testing? </li>
  </ul>


  \todo Apply time-measurements
  <ul>
   <li> Apply the time-measurement-system (assuming it is available by now). </li>
  </ul>


  \todo Declare variable as close to their first usage as possible
  <ul>
   <li> Since C99 also allows to appear declaration everywhere, one
   should move many variable declarations to their first usage point. </li>
   <li> And, as with C++, one can now declare loop-variables inside the loop. </li>
  </ul>


  \todo Use const-qualification
  <ul>
   <li> Where possible, const-qualification should be applied. </li>
  </ul>


  \todo Use restrict-qualification
  <ul>
   <li> We should investigate at which places this pointer-qualification can be used. </li>
  </ul>


  \todo Correct computation of basic statistics
  <ul>
   <li> Counting for example test_cases/TwoUnit.cnf is not correct. </li>
   <li> See whether this can be easily rectified. </li>
   <li> Possibly this is not the case; then we need a precise specification what
   actually is counted, so that then the output can be declared as correct. </li>
  </ul>

*/


