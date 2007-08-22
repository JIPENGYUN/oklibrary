// Oliver Kullmann, 13.9.2005 (Swansea)

/*!
  \file RandomGenerator/plans/general.hpp
  \brief Plans regarding the random generation of problem instances


  \todo Update namespaces.


  \todo Basic revision:
  The first thing is to make the OKgenerator and accompanying tools
  compiling and running correctly again. This should proceed in the
  following stages:
  <ol>
   <li> Creating the basic concept for BigIntegers
   (see BigIntegers/plans/GMPWrapper.hpp), together with the wrapper for GMP. </li>
   <li> Replacing the current big-integer implementation in OKgenerator
   (files flint*; they are sub-standard, introducing macros like "isxdigit",
   many(!) others written with small letter and additional "_I", and even
   "ggT", "xggT", "kgV", "chinrest" and "zweianteil"; perhaps one could have
   a look, whether there is a web page of Michael Welschenbach with improved code). </li>
   <li> Creating the concept for AES in the (new) module Cryptology (see
   Kryptologie/plans/Kryptologie.hpp). </li>
   <li> Replacing the current AES implementation (Kryptologie/aes*)
   by Kryptologie/rijndael*). </li>
   <li> Correct General/Kommandozeile.hpp (there are input-errors,
   likely undefined behaviour). </li>
  </ol>


  \todo Improvements
  <ul>
   <li> Replacing General/Kommandozeile (see General/Kommandozeile.hpp)
   by module Transitional/ProgramOptions. </li>
  </ul>

*/

/*!
  \namespace OKlib::RandomGenerator
  \brief Components for the generation of random problems
*/

namespace OKlib {
  namespace RandomGenerator {
  }
}

