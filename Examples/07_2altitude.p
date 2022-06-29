include('geometryDeductiveDatabaseMethod.ax').
fof(exemplo1TOPTEN072altitude,conjecture,( ! [ A,B,C,D,E,F,G ] :
(
perp(D,C,A,B) & coll(D,A,B) & 
perp(E,B,A,C) & coll(E,A,C) & midp(F,E,D) & midp(G,B,C)
)
=>
(
perp(D,E,G,F)
)
)).