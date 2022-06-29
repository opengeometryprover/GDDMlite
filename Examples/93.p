include('geometryDeductiveDatabaseMethod.ax').
fof(exemploOtherndgTest93,conjecture,( ! [ A,B,C,O,D1,D,F,G,G1,F1,NWPNT1,NWPNT2 ] :
(circle(O,A,B,C) & 
circle(O,A,D1,NWPNT1) & 
coll(D1,O,D) & circle(O,D1,D,NWPNT2) & 
perp(F,D,A,C) & coll(F,A,C) & 
perp(G,D,A,B) & coll(G,A,B) & 
perp(G1,D1,A,B) & coll(G1,A,B) & 
perp(F1,D1,A,C) & coll(F1,A,C)
)
=>
(
perp(G1,F1,G,F)
)
)).