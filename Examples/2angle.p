include('geometryDeductiveDatabaseMethod.ax').
fof(exemploOtherAuxiliaryyeaux2angle,conjecture,( ! [ A,B,C,D,E,F,G,H ] :
(
cong(A,D,C,B) & midp(E,C,D) & midp(F,B,A) & 
coll(G,A,D) & 
coll(G,E,F) & 
coll(H,E,F) & 
coll(H,B,C) & 
coll(H,B,C)
)
=>
(
eqangle(A,G,G,F,F,H,H,B)
)
)).