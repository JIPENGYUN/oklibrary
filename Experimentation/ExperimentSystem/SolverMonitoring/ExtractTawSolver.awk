# Oliver Kullmann, 9.7.2013 (Swansea)
# Copyright 2013 Oliver Kullmann
# This file is part of the OKlibrary. OKlibrary is free software; you can redistribute 
# it and/or modify it under the terms of the GNU General Public License as published by
# the Free Software Foundation and included in this library; either version 3 of the 
# License, or any later version.


# Extracts the numerical data from output of tawSolver, in a single line.

BEGIN {
  rn=0; rc=0; mcl=0; t=0; sat=2; nds=0; r1=0; file=""; bnds=0
}

/^s UNSATISFIABLE/ { sat=0 }
/^s SATISFIABLE/ { sat=1 }
/^s UNKNOWN/ { sat=2 }
/^c number_of_variables/ { rn = $3 }
/^c number_of_clauses/ { rc = $3 }
/^c maximal_clause_length/ { mcl=$3 }
/^c running_time\(sec\)/ { t = $3 }
/^c number_of_nodes/ { nds = $3 }
/^c number_of_binary_nodes/ { bnds = $3 }
/^c number_of_1-reductions/ { r1 = $3 }
/^c file_name/ { file = $3 }

END { 
  print rn " " rc " " mcl " " t " " sat " " nds " " r1 " \"" file "\" " bnds
}
