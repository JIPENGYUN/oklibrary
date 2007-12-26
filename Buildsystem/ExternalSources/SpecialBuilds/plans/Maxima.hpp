// Oliver Kullmann, 7.10.2007 (Swansea)
/* Copyright 2007 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Buildsystem/ExternalSources/SpecialBuilds/plans/Maxima.hpp
  \brief Plans regarding installation of Maxima


  \todo Install CLisp : DONE
  <ul>
   <li> We should provide "oklib libsigsegv" (yet only system-wide), but
   documentation only as part of the installation of CLisp.
    <ol>
     <li> Perhaps the target "libsigsegv" is just realised as a sub-target
     in the installation-makefile for clisp. </li>
    </ol>
   </li>
   <li> Write configuration file for clisp DONE </li>
   <li> Write installation script for clisp. DONE
    <ol>
     <li> Apparently the clisp-maxima system is faulty and doesn't admit
     automatic installation. </li>
     <li> We keep the clisp.mak for the installation, and perhaps something
     changes in the future (and one can use it to install libsigsegv),
     however in the docu we give instruction on manual (syste-wide)
     building. </li>
     <li> Apparently on cs-wsok one needs to use "ulimit -s 16384; make" ? </li>
     <li> Perhaps one should better use "ulimit -s 16384 -S; make", so that in
     case actually "ulimit -s" was already greater than 16384, it is not
     reduced?? Or should we just use "ulimit -s unlimited" ?? Or should
     we first find out whether "ulimit -s" yields a value which is at least
     16384 ?? The strange thing is that with "ulimit -s XXX" apparently the
     stacksize can actually only be reduced ??? </li>
     <li> And in order to compile for 64 bit on cs-wsok, apparently CC has to
     be set to "gcc -m64" ?? By using 'make CC="gcc -m64"' ?? </li>
    </ol>
   </li>
   <li> Write docu for installation of clisp. DONE </li>
   <li> Provide links to the documentation for clisp. DONE </li>
   <li> Put information on the main-external-sources-page. DONE </li>
  </ul>


  \todo Install Maxima
  <ul>
   <li> Write configuration file for Maxima. DONE </li>
   <li> Write installation script for Maxima. DONE </li>
   <li> Provide links to the documentation for Maxima (including
   the maxima-book and the tutorial. </li>
   <li> What about the documentation for Maxima provided with Sage? </li>
   <li> Write docu for installation of Maxima. </li>
   <li> Put information on the main-external-sources-page. </li>
  </ul>


  \todo Install Maxima 5.13 on csltok : DONE (works now (with 5.14))
  <ul>
   <li> First install clisp (should we supply this?); see below. </li>
   <li>
   \verbatim
Installations> mkdir Maxima
builds> mkdir Maxima
Maxima> tar -xzf ../../sources/Maxima/maxima-5.13.0.tar.gz
Maxima> cd maxima-5.13.0/
maxima-5.13.0> LANG=C ./configure --prefix=${OKplatform}/ExternalSources/Installations/Maxima
maxima-5.13.0> LANG=C make
   \endverbatim
   yields
   \verbatim
Compiling file /home/kullmann/csoliver/SAT-Algorithmen/OKplatform/ExternalSources/builds/Maxima/maxima-5.13.0/src/clmacs.lisp ...
*** - READ from
#<INPUT BUFFERED FILE-STREAM CHARACTER
  #P"/home/kullmann/csoliver/SAT-Algorithmen/OKplatform/ExternalSources/builds/Maxima/maxima-5.13.0/src/clmacs.lisp"
  @317>: #<PACKAGE CUSTOM> has no external symbol with name "*FLOATING-POINT-RATIONAL-CONTAGION-ANSI*"
The following functions were used but not defined:
 MAXIMA::MFUNCALL
0 errors, 0 warnings
make[1]: *** [binary-clisp/maxima.mem] Error 1
make[1]: Leaving directory `/home/kullmann/csoliver/SAT-Algorithmen/OKplatform/ExternalSources/builds/Maxima/maxima-5.13.0/src'
make: *** [all-recursive] Error 1
   \endverbatim
   ??? The same error without setting prefix.
   \verbatim
maxima-5.13.0> clisp --version
WARNING: *FOREIGN-ENCODING*: reset to ASCII
GNU CLISP 2.33.2 (2004-06-02) (built on g242.suse.de [10.10.103.242])
Software: GNU-C 3.3.4 (pre 3.3.5 20040809) ANSI-C-Programm
Features:
(CLOS LOOP COMPILER CLISP ANSI-CL COMMON-LISP LISP=CL INTERPRETER SOCKETS GENERIC-STREAMS
 LOGICAL-PATHNAMES SCREEN FFI GETTEXT UNICODE BASE-CHAR=CHARACTER PC386 UNIX)
Installation directory: /usr/lib/clisp/
User language: ENGLISH
Machine: I686 (I686) csltok.swan.ac.uk [128.163.146.167]
   \endverbatim
   </li>
   <li> The installation has a sub-target "access-script":
    <ol>
     <li> This Bash-script is copied to ~/bin (overwriting existing
     files), under the name "Maxima", and it calls the maxima-program,
     passing parameters and loading all functions from the OKlibrary. </li>
     <li> All path-information is hardcoded into this script, and it is
     created from a template with "m4_SHELL"-use. </li>
     <li> Perhaps a different script is used for performing tests. </li>
    </ol>
   </li>
   <li> Move all maxima-documention-links from the Sage-documentation
   page to the Maxima documentation. </li>
  </ul>


  \todo Install Maxima 5.13 on cs-wsok
  <ul>
   <li>
   \verbatim
Installations> mkdir Maxima
Installations> cd Maxima/
Maxima> tar -xzf ../../sources/Maxima/maxima-5.13.0.tar.gz
Maxima> cd maxima-5.13.0
maxima-5.13.0> ./configure --prefix=${OKplatform}/ExternalSources/Installations/Maxima
   \endverbatim
   yields, as above
   \verbatim
Compiling file /home/csoliver/SAT-Algorithmen/OKplatform/ExternalSources/Installations/Maxima/maxima-5.13.0/src/clmacs.lisp ...
*** - READ from
#<INPUT BUFFERED FILE-STREAM CHARACTER
  #P"/home/csoliver/SAT-Algorithmen/OKplatform/ExternalSources/Installations/Maxima/maxima-5.13.0/src/clmacs.lisp"
  @317>: #<PACKAGE CUSTOM> has no external symbol with name "*FLOATING-POINT-RATIONAL-CONTAGION-ANSI*"
The following functions were used but not defined:
 MAXIMA::MFUNCALL
0 errors, 0 warnings
make[1]: *** [binary-clisp/maxima.mem] Error 1
make[1]: Leaving directory `/home/csoliver/SAT-Algorithmen/OKplatform/ExternalSources/Installations/Maxima/maxima-5.13.0/src'
make: *** [all-recursive] Error 1
   \endverbatim
   again with cslisp version 2.33.
   </li>
   <li> After installation of clisp version 2.43
   \verbatim
maxima-5.13.0> ./configure --prefix=$OKPLATFORM/ExternalSources/Installations/Maxima
maxima-5.13.0> make
maxima-5.13.0> make check
maxima-5.13.0> make install
   \endverbatim
   </li>
   <li> Now under Maxima/bin one finds the executable, and under Maxima/share
   one finds the documentation. </li>
  </ul>


  \todo Install clisp (version 2.43) on csltok: DONE (manual installation must suffice)
  <ul>
   <li> 
   \verbatim
Installations> mkdir CLisp
Installations> cd CLisp/
CLisp> tar -xjf ../../sources/Maxima/clisp-2.43.tar.bz2
CLisp> cd clisp-2.43/
clisp-2.43> ./configure
   \endverbatim
   results in
   \verbatim
  libsigsegv: no, consider installing GNU libsigsegv
./configure: libsigsegv was not detected, thus some features, such as
  generational garbage collection and
  stack overflow detection in interpreted Lisp code
cannot be provided.
Please do this:
  mkdir tools; cd tools; prefix=`pwd`/i686-pc-linux-gnu
  wget http://ftp.gnu.org/pub/gnu/libsigsegv/libsigsegv-2.5.tar.gz
  tar xfz libsigsegv-2.5.tar.gz
  cd libsigsegv-2.5
  ./configure --prefix=${prefix} && make && make check && make install
  cd ../..
  ./configure --with-libsigsegv-prefix=${prefix}
If you insist on building without libsigsegv, please pass
  --ignore-absence-of-libsigsegv
to this script:
  ./configure --ignore-absence-of-libsigsegv
   \endverbatim
   </li>
   <li> So apparently we need to install "libsigsegv" first. </li>
   <li> What about those "modules" ? It seems we don't need any optional
   module. </li>
  </ul>


  \todo Install clisp (version 2.43) on cs-wsok (system-wide)
  <ul>
   <li> Same problem with libsigsegv. </li>
   <li> Installing libsigsegv (system-wide)
   \verbatim
Installations> tar -xzf ../sources/Maxima/libsigsegv-2.5.tar.gz
Installations> cd libsigsegv-2.5
libsigsegv-2.5> ./configure
libsigsegv-2.5> make 
libsigsegv-2.5> make check
libsigsegv-2.5> sudo make install
   \endverbatim
   </li>
   <li> Now try again to install clisp. 
   \verbatim
Installations> cd CLisp/
CLisp> tar -xjf ../../sources/Maxima/clisp-2.43.tar.bz2
CLisp>  cd clisp-2.43/
clisp-2.43> ./configure
   </li>
   yields the recommendation
   \verbatim
   cd src
   vi config.lisp
# The default stack size on your platform is insufficient
# and must be increased to at least 16384.  You must do either
# 'ulimit -s 16384' (for Bourne shell derivatives, e.g., bash and zsh)
# or 'limit stacksize 16384' (for C shell derivarives, e.g., tcsh)
   \endverbatim
   So well, looked into src/config.lisp, but didn't tell me much. The recommendation
   "ulimit -s 16384" is just for compilation??
   \verbatim
lisp-2.43/src> ulimit -s 16384
clisp-2.43/src> make
clisp-2.43/src> make check
clisp-2.43/src> make install
   </li>
   <li> Perhaps the above installation is not a 64-bit installation?
   One had to set CC to "gcc -m64" ?? </li>
  </ul>

*/
