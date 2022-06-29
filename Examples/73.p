include('geometryDeductiveDatabaseMethod.ax').
fof(exemploOtherndgTest73,conjecture,( ! [ A,B,C,D,E,F,G,H,NWPNT1,NWPNT2 ] :
(circle(D,A,B,C) & 
circle(D,A,E,NWPNT1) & 
perp(F,E,A,C) & coll(F,A,C) & 
perp(G,E,A,B) & coll(G,A,B) & 
coll(E,G,H) & circle(D,E,H,NWPNT2)
)
=>
(
para(G,F,H,C)
)
)).