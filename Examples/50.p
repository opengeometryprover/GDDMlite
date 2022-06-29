include('geometryDeductiveDatabaseMethod.ax').
fof(exemploOtherndgTest50,conjecture,( ! [ A,C,M,B,O,D,P,R,J,NWPNT1 ] :
(
coll(M,A,C) & 
perp(C,A,B,M) & circle(O,A,C,B) & 
coll(B,M,D) & circle(O,B,D,NWPNT1) & midp(P,B,A) & midp(R,D,C) & 
coll(J,M,O) & coll(J,P,R)
)
=>
(
para(P,O,M,R)
)
)).