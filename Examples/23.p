INTERSECTION_TC B A O C O A 
include('geometryDeductiveDatabaseMethod.ax').
fof(exemploOtherndgTest23,conjecture,( ! [ A,C,D,O,B,M,E,F,G,NWPNT1 ] :
(circle(O,A,C,D) & 
coll(M,C,O) & coll(M,A,B) & 
circle(O,A,E,NWPNT1) & 
coll(F,A,B) & coll(F,C,D) & 
coll(G,A,B) & coll(G,C,E)
)
=>
(
eqangle(A,G,G,C,C,D,D,E)
)
)).