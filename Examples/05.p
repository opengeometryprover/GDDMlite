include('geometryDeductiveDatabaseMethod.ax').
fof(exemploOtherndgs05,conjecture,( ! [ A,B,C,D,E,F,G,H ] :
(
para(A,B,C,D) & para(B,C,A,D) & 
perp(E,D,A,C) & coll(E,A,C) & 
perp(F,B,A,C) & coll(F,A,C) & 
perp(G,C,B,D) & coll(G,B,D) & 
perp(H,A,B,D) & coll(H,B,D)
)
=>
(
para(G,E,H,F)
)
)).
