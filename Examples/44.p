include('geometryDeductiveDatabaseMethod.ax').
fof(exemploOtherndgTest44,conjecture,( ! [ A,B,C,O,D,A1,C1,NWPNT1 ] :
(circle(O,A,B,C) & 
circle(O,A,D,NWPNT1) & 
coll(A1,C,D) & coll(A1,A,B) & 
coll(C1,A,B) & coll(C1,C,D)
)
=>
(
para(D,B,A1,C1)
)
)).