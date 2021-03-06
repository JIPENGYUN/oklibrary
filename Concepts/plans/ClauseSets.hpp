// Oliver Kullmann, 24.7.2005 (Swansea)
/* Copyright 2005 - 2007 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Concepts/plans/ClauseSets.hpp
  \brief Plans for concepts for clause-sets, clause-sets with history, virtual clause-sets and active
  clause-sets.

  \todo Update with
  <ul>
   <li> Concepts/plans/ActiveClauseSets.hpp </li>
   <li> Concepts/plans/Clauses.hpp </li>
  </ul> (the text below is no longer up-to-date).

  \todo Shouldn't we differentiate between
   - "ClauseSets"
   - "VirtualClauseSets"
   - "ActiveClauseSets"

  ?!

  \todo Concepts for clause-sets as collections of clauses, which are collections of
  literals, holding a reference to a domain-assignment for the variables.

  \todo For an earlier attempt see
  OKsolver/Experimental/AllgKlassen200203/ClauseSets.hpp.

  \todo An important refinement is the concept of a "clause-set with history",
  which holds a reference to a structure consisting of a domain-assignment
  together with a partial assignment refining it, and the state of the update
  process (how much of the partial assignment has been processed). Processed
  parts of the partial assignment may be transferred to the domain assignment.
  Clause-sets with history support the reversal of the assignment process (controlled
  by the assignment structure).

  \todo Actually clause-sets with history are only special cases of *virtual clause-sets*,
  which support sat_status() (may return "unknown"), and which in general do
  not enable access to the clauses (which in general are "not there").
  Active clause-sets refine virtual clause-sets by returning a partial assignment themselves
  (the set of unit-clauses which the inference mechanism found; "strong active
  clause-sets" infer all clauses of length <= 1). More generally for k-active clause-sets
  sequences of derived clauses of length at most k are computed (so virtual clause-sets
  are 0-active clause-sets).

  \todo Clause-sets should allow efficient access to the related hypergraphs
  and graphs (so that we can use general hypergraph and graph algorithms;
  examples for graphs are the resolution graph and the resolution-subsumption
  graph). This access should happen via simple wrapping of for example clauses
  or variables into node classes (the type of these node classes specifies
  the type of graph; no additional computations should be necessary).

  \todo The bipartite clause-literal graph likely should be accessed through
  the hypergraph-interface. The two refinements "clause-sets with history"
  and "clause-sets with bipartite structure" should be independent of each other, and
  there should be a common refinement.

  \todo Clause-literal graphs for clause-sets should contain all possible literals; however
  for P-clause-sets this is not sensible anymore, and so only occurring literals are mentioned,
  and they are connected to a new type of node, the value nodes (connected also with
  the variables).

  \todo An autarky for a P-clause-set is a partial assignment, such that for P-clauses which
  are not satisfied by the assignment no literal exists with a restricted set of satisfying
  values.

  \todo A virtual clause-set is like a dynamic constraint with the additional possibility of
  handling partial assignments; the sat_status must be 0 or 1 in case all variables have
  been fixed. But they have an underlying P-clause-set model, so that they can tell, whether
  the current partial assignment is an autarky or not, and so that they can perform
  statistical evaluations (the deduction mechanism must at least deliver what the
  underlying P-clause-set can (immediately) deliver, but might be (much) stronger).

  \todo An aliance of active clause-sets owns the structure consisting of the domain
  assignment and the partial assignment (but this is controlled by external
  algorithms); by some strategy it processes (and potentially enhances) a given
  partial assignment (only when the partial assignment is completely processed by
  all active clause-sets and no decision was reached, then the domain assignment finally
  gets updated). Learning (local or global) is controlled from the outside;
  in case of a "conflict" a resolvent may be computed (potentially compressed).

  \todo Links:
  See modules UnitClausePropagation and Learning for further thoughts on
  the concept of "active clause-sets". And in SATAlgorithms/plans/GenericBacktracking.hpp
  the first prototype is being developed.

  \todo Sat status:
  For an active clause-set F,
  \code F.sat_status() \endcode
  perhaps should return an object
  from a hierarchy with root <code>Unknown</code>, derived classes
  <code>Satisfiable</code>, <code>Unsatisfiable</code>,
  and furthermore <code>Satisfied</code> derived from <code>Satisfiable</code>.

  And there should be
  \code F.assignment_status(), \endcode
  returning an object of type <code>Unknown</code>, or, derived from it,
  <code> Conservative </code> (every satisfying assignment
  for F is also satisfying for phi * F), or <code> Autarky </code>
  (derived from <code>Conservative</code>).
  <code>Satisfied</code> implies <code>Autarky</code>.
*/

