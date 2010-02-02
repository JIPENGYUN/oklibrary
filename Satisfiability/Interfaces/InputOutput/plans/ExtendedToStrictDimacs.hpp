// Oliver Kullmann, 2.1.2010 (Belgrade)
/* Copyright 2010 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Interfaces/InputOutput/plans/ExtendedToStrictDimacs.hpp
  \brief Plans regarding the translation from extended forms of Dimacs form to the strict form


  \todo Parameter handling
  <ul>
   <li> The new parameter-values should be the correct (i.e., precise) ones,
   not the original ones.
   <li> It should be an option whether the original parameter values should be
   checked for errors, or just completely ignored. </li>
   <li> Perhaps the current behaviour, just taking over the original
   values, could also be an option. </li>
   <li> We should add a comment-line (optionally) for the original
   file-name, for the original parameter values, and if some cleaning
   happened (tautological clauses or repeated literals), then these
   numbers are also stated. </li>
  </ul>


  \todo Extended Dimacs format
  <ul>
   <li> Really handle extended Dimacs format, using a policy for
   OKlib::InputOutput::StandardDIMACSInput.
   <li> We should have an option for adding to the comment-section
   the map index -> original name. </li>
   <li> This map should be produced by the CLSAdaptor, and a standard
   format is needed, so that it can be extracted by some tool. </li>
   <li> Should we have a command-line option to turn on extended Dimacs
   format? Seems useless: turn it always on (this can handle also standard
   Dimacs input). DONE </li>
  </ul>


  \todo Complete doxygen-documentation


  \todo Write docus
  <ul>
   <li> The output is cleaned of tautological clauses and repeated
   literals, and the output of clauses is sorted according to natural
   order for integers. </li>
   <li> Mention the public link. </li>
  </ul>


  \todo Use Messages


  \todo Use ProgramOptions


  \todo Organisation
  <ul>
   <li> Move InputOutput/ExtendedToStrictDimacs.cpp to sub-directory
   applications, once buildsystem is ready; update then public link. </li>
  </ul>

*/
