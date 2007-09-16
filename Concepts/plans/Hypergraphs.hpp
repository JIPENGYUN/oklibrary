// Oliver Kullmann, 26.7.2005 (Swansea)
/* Copyright 2005 - 2007 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Concepts/plans/Hypergraphs.hpp
  \brief Plans for concepts for (general) hypergraphs

  \todo Writing the basic concepts for hypergraphs, similar to the concepts for graphs
  from the Boost graph library (sequences of vertices and hyperedges, where hyperedges
  are sequences of vertices). The direct access from vertices to incident edges
  could be "outsourced" to the concept of an associated bipartite graph (the vertex-hyperedge
  bipartite graph; associated, so that update operations are reflected), but it seems better
  to only "embed" this bipartite graph into the hypergraph data structure, as the
  bipartite vertex-edge graph is embedded into the boost graph concept via the
  refinement of an "incidence graph": This seems to model better the main nature
  of that bipartite graph as a data structure; and also in this way generalisations like
  access only to hyperedges where the vertex is the "first" or the "last" vertex are
  perhaps modelled more easily (in this way we then can model directed graphs,
  and also methods like "watched literals" (such bipartite graphs are actually
  vertex-edge graphs)!). However, it should be the case
  that such "incidence hypergraphs" directly yield models of bipartite graphs via
  regarding either the vertices or the hyperedges as "left part".

  \todo Clarify the relations to module Graphs (see Graphs/plans/Graphs.hpp).

  \todo Clarify the relation to Concepts/plans/BipartiteGraphs.hpp.

  \todo Clause-sets are refinements of hypergraphs, where also application of
  partial assignments may be supported (perhaps also resolution etc. ?).

  \todo See QuantumPhysics/plans/OrthogonalTriples.hpp for some examples.
*/

