include('geometryDeductiveDatabaseMethod.ax').
fof(exemplo5MANUAL5446,conjecture,( ! [ A,B,C,D,E,F,G,H,I,J ] :
(
coll(D,A,B) & 
coll(D,A,B) & 
coll(E,A,C) & 
coll(E,A,C) & 
cong(B,D,C,E) & 
cong(B,D,C,E) & midp(F,E,B) & midp(F,E,B) & midp(G,C,D) & midp(G,C,D) & 
coll(H,A,B) & coll(H,F,G) & 
coll(H,A,B) & coll(H,F,G) & 
coll(I,A,C) & coll(I,F,G) & 
coll(I,A,C) & coll(I,F,G) & midp(J,C,B)
)
=>
(
cong(A,H,A,I)
)
)).