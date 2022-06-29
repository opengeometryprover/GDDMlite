include('geometryDeductiveDatabaseMethod.ax').
fof(exemplo3JARJAR01new9point,conjecture,( ! [ A,B,C,D,E,F,N,M,NWPNT4 ] :
(
perp(D,A,B,C) & coll(D,B,C) & 
perp(E,B,A,C) & coll(E,A,C) & 
perp(F,C,A,B) & coll(F,A,B) & 
midp(MIDPNT1,D,F) & perp(D,F,MIDPNT1,N) & midp(MIDPNT2,D,E) & perp(D,E,MIDPNT2,N) & midp(MIDPNT3,F,E) & perp(F,E,MIDPNT3,N) & 
coll(A,B,M) & circle(N,D,M,NWPNT4)
)
=>
(midp(M,A,B)
)
)).