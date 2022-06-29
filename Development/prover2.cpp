#include "prover.hpp"
#include <iostream>
#include <map>
#include <set>

static void DebugStatement(sqlite3_stmt* stmt){
    int numberColumns = sqlite3_column_count(stmt);

    printf("%s:\n",sqlite3_column_table_name(stmt,1));
    for(int i = 0; i < numberColumns; i++){
        printf("%10.10s | ",sqlite3_column_name(stmt,i));
    }
    printf("\n");
    for(int i = 0; i < numberColumns; i++){
        printf("%10.10s | ",sqlite3_column_text(stmt,i));
    }
    printf("\n");
    fflush(stdout);
}

//  1 coll
//  2 para
//  3 perp
//  4 midp
//  5 circle
//  6 cyclic
//  7 eqangle
//  8 cong
//  9 eqratio
// 10 simtri
// 11 contri



/*
DBinMemory Prover::rule(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6,std::string point7,std::string point8){
  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('contri')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";
  newPoint2="";

  querySecondGeoCmdA = "SELECT point3,point4 FROM NewFact INNER JOIN Cong ON (newFact=id) WHERE point1 = '"+point3+"' and point2 = '"+point4+"' and point3 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"') and point4 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point3,point4 FROM Facts INNER JOIN Cong ON (oldFact=id) WHERE point1 = '"+point3+"' and point2 = '"+point4+"' and point3 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"') and point4 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt1, 1);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt2, 1);}

  insertionColl = "INSERT INTO Contri(typeGeoCmd,point1,point2,point3,point4,point5,point6,newFact) VALUES ('contri','"+point1+"','"+point2+"','"+point3+"','"+point4+"','"+point5+"','"+point6+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}
*/


//Check
DBinMemory Prover::ruleD1(DBinMemory dbim,std::string point1,std::string point2,std::string point3){
  /*
   * rule coll(A,B,C) => coll(A,C,B)
   * insert coll(A,C,B) in the db
   */

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('coll')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3};
  if(uniquepoints.size()!=3){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );


  insertionColl = "INSERT INTO Collinear(typeGeoCmd,point1,point2,point3,newFact) VALUES ('coll','"+point1+"','"+point3+"','"+point2+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}

//Check
DBinMemory Prover::ruleD2(DBinMemory dbim,std::string point1,std::string point2,std::string point3){
  /*
   * rule coll(A,B,C) => coll(B,A,C)
   * insert coll(B,A,C) in the db
   */

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('coll')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3};
  if(uniquepoints.size()!=3){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Collinear(typeGeoCmd,point1,point2,point3,newFact) VALUES ('coll','"+point2+"','"+point1+"','"+point3+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}

//Check
DBinMemory Prover::ruleD3(DBinMemory dbim,std::string point1,std::string point2,std::string point3){
  /*
   * rule coll(A,B,C) and coll(A,B,D) => coll(C,D,A)
   * insert coll(C,D,A)
   */

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('coll')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3};
  if(uniquepoints.size()!=3){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";
  querySecondGeoCmdA = "SELECT point3 FROM NewFact INNER JOIN Collinear ON (newFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 <> '"+point3+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point3 FROM Facts INNER JOIN Collinear ON (oldFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 <> '"+point3+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);}

  insertionColl = "INSERT INTO Collinear(typeGeoCmd,point1,point2,point3,newFact) VALUES ('coll','"+point3+"','"+newPoint+"','"+point1+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}

//Check
DBinMemory Prover::ruleD4(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){
  /*
   * rule para(A,B,C,D) => para(A,B,D,C)
   * insert para(A,B,D,C)
   */

   std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('para')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=4){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Parallel(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('para','"+point1+"','"+point2+"','"+point4+"','"+point3+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}

//Check
DBinMemory Prover::ruleD5(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){
  /*
   * rule para(A,B,C,D) => para(C,D,A,B)
   * insert para(C,D,A,B)
   */

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('para')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=4){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Parallel(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('para','"+point3+"','"+point4+"','"+point1+"','"+point2+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}

//Check
DBinMemory Prover::ruleD6(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){
  /*
   * rule para(A,B,C,D) & para(C,D,E,F) => para(A,B,E.F)
   * insert para(A,B,E,F)
   */

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('para')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=4){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";
  newPoint2="";

  querySecondGeoCmdA = "SELECT point3,point4 FROM NewFact INNER JOIN Parallel ON (newFact=id) WHERE point1 = '"+point3+"' and point2 = '"+point4+"' and point3 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"') and point4 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point3,point4 FROM Facts INNER JOIN Parallel ON (oldFact=id) WHERE point1 = '"+point3+"' and point2 = '"+point4+"' and point3 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"') and point4 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt1, 1);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt2, 1);}

  insertionColl = "INSERT INTO Parallel(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('para','"+point1+"','"+point2+"','"+newPoint+"','"+newPoint2+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}

//Check
DBinMemory Prover::ruleD7(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){
  /*
   * rule perp(A,B,C,D) => perp(A,B,D,C)
   * insert perp(A,B,D,C)
   */

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('perp')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=4){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Perpendicular(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('perp','"+point1+"','"+point2+"','"+point4+"','"+point3+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}

//Check
DBinMemory Prover::ruleD8(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){
  /*
   * rule perp(A,B,C,D) => perp(C,D,A,B)
   * insert perp(C,D,A,B)
   */

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('perp')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=4){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Perpendicular(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('perp','"+point3+"','"+point4+"','"+point1+"','"+point2+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}

//Check
DBinMemory Prover::ruleD9(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){
  /*
   * rule perp(A,B,C,D) & perp(C,D,E,F) => para(A,B,E,F)
   * insert perp(A,B,E,F)
   */

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('para')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=4){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";
  newPoint2="";

  querySecondGeoCmdA = "SELECT point3,point4 FROM NewFact INNER JOIN Perpendicular ON (newFact=id) WHERE point1 = '"+point3+"' and point2 = '"+point4+"' and point3 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"') and point4 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);
  querySecondGeoCmdB = "SELECT point3,point4 FROM Facts INNER JOIN Perpendicular ON (oldFact=id) WHERE point1 = '"+point3+"' and point2 = '"+point4+"' and point3 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"') and point4 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt1, 1);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt2, 1);}

  insertionColl = "INSERT INTO Parallel(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('para','"+point1+"','"+point2+"','"+newPoint+"','"+newPoint2+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}

//Check
DBinMemory Prover::ruleD10Perp(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){
  /*
   * rule
   * insert
   */

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('para')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=4){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";
  newPoint2="";

  querySecondGeoCmdA = "SELECT point1,point2 FROM NewFact INNER JOIN Parallel ON (newFact=id) WHERE point3 = '"+point1+"' and point4 = '"+point2+"' and point1 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"') and point2 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point1)";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point1,point2 FROM Facts INNER JOIN Parallel ON (oldFact=id) WHERE point3 = '"+point1+"' and point4 = '"+point2+"' and point1 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"') and point2 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point1)";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt1, 1);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt2, 1);}


  insertionColl = "INSERT INTO Parallel(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('para','"+newPoint+"','"+newPoint2+"','"+point3+"','"+point4+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}

//Check
DBinMemory Prover::ruleD10Para(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){
  /*
   * rule para(A,B,C,D) & perp(C,D,E,F) => para(A,B,E,F)
   * insert para(A,B,E,F)
   */

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('para')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=4){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";
  newPoint2="";

  querySecondGeoCmdA = "SELECT point3,point4 FROM NewFact INNER JOIN Perpendicular ON (newFact=id) WHERE point1 = '"+point3+"' and point2 = '"+point4+"' and point3 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"') and point4 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point3)";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point3,point4 FROM Facts INNER JOIN Perpendicular ON (oldFact=id) WHERE point1 = '"+point3+"' and point2 = '"+point4+"' and point3 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"') and point4 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point3)";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt1, 1);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt2, 1);}


  insertionColl = "INSERT INTO Parallel(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('para','"+point1+"','"+point2+"','"+newPoint+"','"+newPoint2+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}

//Check
DBinMemory Prover::ruleD11(DBinMemory dbim,std::string point1,std::string point2,std::string point3){
  /*
   * rule midp(M,A,B) => midp(M,B,A)
   * insert midp(M,B,A)
   */

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('midp')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3};
  if(uniquepoints.size()!=3){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Midpoint(typeGeoCmd,point1,point2,point3,newFact) VALUES ('midp','"+point1+"','"+point3+"','"+point2+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}

//Check
DBinMemory Prover::ruleD12(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){
  /*
   * rule cong(O,A,O,B)& cong(O,A,O,C) => circle(O,A,B,C)
   * insert para(A,B,E,F)
   */

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('circle')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=3 || point1!=point3){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";

  querySecondGeoCmdA = "SELECT point4 FROM NewFact INNER JOIN Cong ON (newFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 = '"+point3+"' and point4 not in ('"+point1+"','"+point2+"','"+point4+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point4 FROM Facts INNER JOIN Cong ON (oldFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 = '"+point3+"' and point4 not in ('"+point1+"','"+point2+"','"+point4+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);}

  insertionColl = "INSERT INTO Circle(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('circle','"+point1+"','"+point2+"','"+point4+"','"+newPoint+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD13(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){
  /*
   * rule cong(O,A,O,B), cong(O,A,O,C), cong(O,A,O,D) => cyclic(A,B,C,D)
   * insert cyclic(A,B,C,D)
   */
  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('cyclic')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=3 || point1!=point3){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";
  querySecondGeoCmdA = "SELECT point4 FROM NewFact INNER JOIN Cong ON (newFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 = '"+point3+"' and point4 not in ('"+point1+"','"+point2+"','"+point4+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point4 FROM Facts INNER JOIN Cong ON (oldFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 = '"+point3+"' and point4 not in ('"+point1+"','"+point2+"','"+point4+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);}


  newPoint2="";
  querySecondGeoCmdA = "SELECT point4 FROM NewFact INNER JOIN Cong ON (newFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 = '"+point3+"' and point4 not in ('"+point1+"','"+point2+"','"+point4+"','"+newPoint+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point4 FROM Facts INNER JOIN Cong ON (oldFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 = '"+point3+"' and point4 not in ('"+point1+"','"+point2+"','"+point4+"','"+newPoint+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint2 = (char*) sqlite3_column_text(dbim.stmt1, 0);}
  else {newPoint2 = (char*) sqlite3_column_text(dbim.stmt2, 0);}

  insertionColl = "INSERT INTO Cyclic(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('cyclic','"+point2+"','"+point4+"','"+newPoint+"','"+newPoint2+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}

//Check
DBinMemory Prover::ruleD14(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){
  /*
   * rule cyclic(A,B,C,D) => cyclic(A,B,D,C)
   * insert cyclic(A,B,D,C)
   */


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('cyclic')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=4){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Cyclic(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('cyclic','"+point1+"','"+point2+"','"+point4+"','"+point3+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}

//Check
DBinMemory Prover::ruleD15(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){
  /*
   * rule cyclic(A,B,C,D) => cyclic(A,C,B,D)
   * insert cyclic(A,C,B,D)
   */


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('cyclic')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=4){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Cyclic(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('cyclic','"+point1+"','"+point3+"','"+point2+"','"+point4+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}

//Check
DBinMemory Prover::ruleD16(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){
  /*
   * rule cyclic(A,B,C,D) => cyclic(B,A,C,D)
   * insert cyclic(B,A,C,D)
   */


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('cyclic')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=4){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Cyclic(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('cyclic','"+point2+"','"+point1+"','"+point3+"','"+point4+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}

//Check
DBinMemory Prover::ruleD17(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){
  /*
   * rule para(A,B,C,D) & para(C,D,E,F) => para(A,B,E.F)
   * insert para(A,B,E,F)
   */

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('cyclic')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=4){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";

  querySecondGeoCmdA = "SELECT point4 FROM NewFact INNER JOIN Cyclic ON (newFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 = '"+point3+"' and point4 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point4 FROM Facts INNER JOIN Cyclic ON (oldFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 = '"+point3+"' and point4 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);}

  insertionColl = "INSERT INTO Cyclic(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('cyclic','"+point2+"','"+point3+"','"+point4+"','"+newPoint+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD18(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6,std::string point7,std::string point8){
  /*
   * rule eqangle(A,B,C,D,P,Q,U,V) => eqangle(B,A,C,D,P,Q,U,V)
   * insert eqangle(B,A,C,D,P,Q,U,V)
   */


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('eqangle')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3,point4,point5,point6,point7,point8};
  if(uniquepoints.size()!=8){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Eqangle(typeGeoCmd,point1,point2,point3,point4,point5,point6,point7,point8,newFact) VALUES ('eqangle','"+point2+"','"+point1+"','"+point3+"','"+point4+"','"+point5+"','"+point6+"','"+point7+"','"+point8+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD19(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6,std::string point7,std::string point8){
  /*
   * rule eqangle(A,B,C,D,P,Q,U,V) => eqangle(C,D,A,B,U,V,P,Q)
   * insert eqangle(C,D,A,B,U,V,P,Q)
   */


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('eqangle')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3,point4,point5,point6,point7,point8};
  if(uniquepoints.size()!=8){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Eqangle(typeGeoCmd,point1,point2,point3,point4,point5,point6,point7,point8,newFact) VALUES ('eqangle','"+point3+"','"+point4+"','"+point1+"','"+point2+"','"+point7+"','"+point8+"','"+point5+"','"+point6+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD20(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6,std::string point7,std::string point8){
  /*
   * rule eqangle(A,B,C,D,P,Q,U,V) => eqangle(P,Q,U,V,A,B,C,D)
   * insert eqangle(P,Q,U,V,A,B,C,D)
   */


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('eqangle')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3,point4,point5,point6,point7,point8};
  if(uniquepoints.size()!=8){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Eqangle(typeGeoCmd,point1,point2,point3,point4,point5,point6,point7,point8,newFact) VALUES ('eqangle','"+point5+"','"+point6+"','"+point7+"','"+point8+"','"+point1+"','"+point2+"','"+point3+"','"+point4+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD21(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6,std::string point7,std::string point8){
  /*
   * rule eqangle(A,B,C,D,P,Q,U,V) => eqangle(A,B,P,Q,C,D,U,V)
   * insert eqangle(A,B,P,Q,C,D,U,V)
   */


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('eqangle')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3,point4,point5,point6,point7,point8};
  if(uniquepoints.size()!=8){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Eqangle(typeGeoCmd,point1,point2,point3,point4,point5,point6,point7,point8,newFact) VALUES ('eqangle','"+point1+"','"+point2+"','"+point5+"','"+point6+"','"+point3+"','"+point4+"','"+point7+"','"+point8+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD22(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6,std::string point7,std::string point8){
  /*
   * rule eqangle(A,B,C,D,P,Q,U,V) & eqangle(P,Q,U,V,E,F,G,H) => eqangle(A,B,C,D,E,F,G,H)
   * insert eqangle(A,B,C,D,E,F,G,H)
   */

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,newPoint3,newPoint4,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('eqangle')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3,point4,point5,point6,point7,point8};
  if(uniquepoints.size()!=8){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";
  newPoint2="";
  newPoint3="";
  newPoint4="";

  querySecondGeoCmdA = "SELECT point5,point6,point7,point8 FROM NewFact INNER JOIN Eqangle ON (newFact=id) WHERE point1 = '"+point5+"' and point2 = '"+point6+"' and point3 = '"+point7+"' and point4 = '"+point8+"' and point5 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"') and point6 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point5) and point7 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point5,point6) and point8 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point5,point6,point7)";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point5,point6,point7,point8 FROM Facts INNER JOIN Eqnagle ON (oldFact=id) WHERE point1 = '"+point5+"' and point2 = '"+point6+"' and point3 = '"+point7+"' and point4 = '"+point8+"' and point5 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"') and point6 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point5) and point7 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point5,point6) and point8 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point5,point6,point7)";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt1, 1);newPoint3 = (char*) sqlite3_column_text(dbim.stmt1, 2);newPoint4 = (char*) sqlite3_column_text(dbim.stmt1, 3);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt2, 1);newPoint3 = (char*) sqlite3_column_text(dbim.stmt2, 2);newPoint4 = (char*) sqlite3_column_text(dbim.stmt2, 3);}

  insertionColl = "INSERT INTO Eqangle(typeGeoCmd,point1,point2,point3,point4,point5,point6,point7,point8,newFact) VALUES ('eqangle','"+point1+"','"+point2+"','"+point3+"','"+point4+"','"+newPoint+"','"+newPoint2+"','"+newPoint3+"','"+newPoint4+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD23(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){
  /*
   * rule cong(A,B,C,D) => cong(A,B,D,C)
   * insert cong(A,B,D,C)
   */


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('cong')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=4){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Cong(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('cong','"+point1+"','"+point2+"','"+point4+"','"+point3+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD24(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){
  /*
   * rule cong(A,B,C,D) => cong(C,D,A,B)
   * insert cong(C,D,A,B)
   */

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('cong')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=4){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Cong(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('cong','"+point3+"','"+point4+"','"+point1+"','"+point2+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}



DBinMemory Prover::ruleD25(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){
  /*
   * rule para(A,B,C,D) & para(C,D,E,F) => para(A,B,E.F)
   * insert para(A,B,E,F)
   */


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('cong')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=4){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";
  newPoint2="";

  querySecondGeoCmdA = "SELECT point3,point4 FROM NewFact INNER JOIN Cong ON (newFact=id) WHERE point1 = '"+point3+"' and point2 = '"+point4+"' and point3 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"') and point4 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point3,point4 FROM Facts INNER JOIN Cong ON (oldFact=id) WHERE point1 = '"+point3+"' and point2 = '"+point4+"' and point3 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"') and point4 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt1, 1);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt2, 1);}

  insertionColl = "INSERT INTO Cong(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('cong','"+point1+"','"+point2+"','"+newPoint+"','"+newPoint2+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD26(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6,std::string point7,std::string point8){
  /*
   * rule eqratio(A,B,C,D,P,Q,U,V) => eqratio(B,A,C,D,P,Q,U,V)
   * insert eqratio(B,A,C,D,P,Q,U,V)
   */


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('eqratio')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3,point4,point5,point6,point7,point8};
  if(uniquepoints.size()!=8){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Eqratio(typeGeoCmd,point1,point2,point3,point4,point5,point6,point7,point8,newFact) VALUES ('eqratio','"+point2+"','"+point1+"','"+point3+"','"+point4+"','"+point5+"','"+point6+"','"+point7+"','"+point8+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}



DBinMemory Prover::ruleD27(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6,std::string point7,std::string point8){
  /*
   * rule eqratio(A,B,C,D,P,Q,U,V) => eqratio(C,D,A,B,U,V,P,Q)
   * insert eqratio(C,D,A,B,U,V,P,Q)
   */


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('eqratio')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3,point4,point5,point6,point7,point8};
  if(uniquepoints.size()!=8){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Eqratio(typeGeoCmd,point1,point2,point3,point4,point5,point6,point7,point8,newFact) VALUES ('eqratio','"+point3+"','"+point4+"','"+point1+"','"+point2+"','"+point7+"','"+point8+"','"+point5+"','"+point6+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}



DBinMemory Prover::ruleD28(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6,std::string point7,std::string point8){
  /*
   * rule eqratio(A,B,C,D,P,Q,U,V) => eqratio(P,Q,U,V,A,B,C,D)
   * insert eqratio(P,Q,U,V,A,B,C,D)
   */


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('eqratio')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3,point4,point5,point6,point7,point8};
  if(uniquepoints.size()!=8){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Eqratio(typeGeoCmd,point1,point2,point3,point4,point5,point6,point7,point8,newFact) VALUES ('eqratio','"+point5+"','"+point6+"','"+point7+"','"+point8+"','"+point1+"','"+point2+"','"+point3+"','"+point4+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}



DBinMemory Prover::ruleD29(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6,std::string point7,std::string point8){
  /*
   * rule eqratio(A,B,C,D,P,Q,U,V) => eqratio(A,B,P,Q,C,D,U,V)
   * insert eqratio(A,B,P,Q,C,D,U,V)
   */


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('eqratio')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3,point4,point5,point6,point7,point8};
  if(uniquepoints.size()!=8){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Eqratio(typeGeoCmd,point1,point2,point3,point4,point5,point6,point7,point8,newFact) VALUES ('eqratio','"+point1+"','"+point2+"','"+point5+"','"+point6+"','"+point3+"','"+point4+"','"+point7+"','"+point8+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}




DBinMemory Prover::ruleD30(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6,std::string point7,std::string point8){
  /*
   * rule para(A,B,C,D) & para(C,D,E,F) => para(A,B,E.F)
   * insert para(A,B,E,F)
   */

 std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,newPoint3,newPoint4,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('eqratio')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3,point4,point5,point6,point7,point8};
  if(uniquepoints.size()!=8){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";
  newPoint2="";
  newPoint3="";
  newPoint4="";

  querySecondGeoCmdA = "SELECT point5,point6,point7,point8 FROM NewFact INNER JOIN Eqratio ON (newFact=id) WHERE point1 = '"+point5+"' and point2 = '"+point6+"' and point3 = '"+point7+"' and point4 = '"+point8+"' and point5 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"') and point6 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point5) and point7 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point5,point6) and point8 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point5,point6,point7)";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point5,point6,point7,point8 FROM Facts INNER JOIN Eqratio ON (oldFact=id) WHERE point1 = '"+point5+"' and point2 = '"+point6+"' and point3 = '"+point7+"' and point4 = '"+point8+"' and point5 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"') and point6 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point5) and point7 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point5,point6) and point8 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point5,point6,point7)";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt1, 1);newPoint3 = (char*) sqlite3_column_text(dbim.stmt1, 2);newPoint4 = (char*) sqlite3_column_text(dbim.stmt1, 3);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt2, 1);newPoint3 = (char*) sqlite3_column_text(dbim.stmt2, 2);newPoint4 = (char*) sqlite3_column_text(dbim.stmt2, 3);}

  insertionColl = "INSERT INTO Eqratio(typeGeoCmd,point1,point2,point3,point4,point5,point6,point7,point8,newFact) VALUES ('eqratio','"+point1+"','"+point2+"','"+point3+"','"+point4+"','"+newPoint+"','"+newPoint2+"','"+newPoint3+"','"+newPoint4+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD31(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6){
  /*
   * rule simtri(A,B,C,P,Q,R) => simtri(A,C,B,P,R,Q)
   * insert simtri(A,C,B,P,R,Q)
   */


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('simtri')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3,point4,point5,point6};
  if(uniquepoints.size()!=6){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Simtri(typeGeoCmd,point1,point2,point3,point4,point5,point6,newFact) VALUES ('simtri','"+point1+"','"+point3+"','"+point2+"','"+point4+"','"+point6+"','"+point5+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD32(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6){
  /*
   * rule simtri(A,B,C,P,Q,R) => simtri(B,A,C,Q,P,R)
   * insert simtri(B,A,C,Q,P,R)
   */


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('simtri')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3,point4,point5,point6};
  if(uniquepoints.size()!=6){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Simtri(typeGeoCmd,point1,point2,point3,point4,point5,point6,newFact) VALUES ('simtri','"+point2+"','"+point1+"','"+point3+"','"+point5+"','"+point4+"','"+point6+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD33(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6){
  /*
   * rule simtri(A,B,C,P,Q,R) => simtri(P,Q,R,A,B,C)
   * insert simtri(P,Q,R,A,B,C)
   */


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('simtri')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3,point4,point5,point6};
  if(uniquepoints.size()!=6){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Simtri(typeGeoCmd,point1,point2,point3,point4,point5,point6,newFact) VALUES ('simtri','"+point4+"','"+point5+"','"+point6+"','"+point1+"','"+point2+"','"+point3+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD34(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6){
  /*
   * rule simtri(A, B, C, E, F, G) & simtri(E, F, G, P , Q, R) => simtri(A, B, C, P , Q, R)
   * insert simtri(A, B, C, P , Q, R)
   */


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,newPoint3,newPoint4,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('simtri')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3,point4,point5,point6};
  if(uniquepoints.size()!=6){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";
  newPoint2="";
  newPoint3="";

  querySecondGeoCmdA = "SELECT point4,point5,point6 FROM NewFact INNER JOIN Simtri ON (newFact=id) WHERE point1 = '"+point4+"' and point2 = '"+point5+"' and point3 = '"+point6+"' and point4 not in ('"+point1+"','"+point2+"','"+point3+"') and point5 not in ('"+point1+"','"+point2+"','"+point3+"',point4) and point6 not in ('"+point1+"','"+point2+"','"+point3+"',point4,point5)";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point4,point5,point6 FROM Facts INNER JOIN Simtri ON (oldFact=id) WHERE point1 = '"+point4+"' and point2 = '"+point5+"' and point3 = '"+point6+"' and point4 not in ('"+point1+"','"+point2+"','"+point3+"') and point5 not in ('"+point1+"','"+point2+"','"+point3+"',point4) and point6 not in ('"+point1+"','"+point2+"','"+point3+"',point4,point5)";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt1, 1);newPoint3 = (char*) sqlite3_column_text(dbim.stmt1, 2);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt2, 1);newPoint3 = (char*) sqlite3_column_text(dbim.stmt2, 2);}

  insertionColl = "INSERT INTO Simtri(typeGeoCmd,point1,point2,point3,point4,point5,point6,newFact) VALUES ('simtri','"+point1+"','"+point2+"','"+point3+"','"+newPoint+"','"+newPoint2+"','"+newPoint3+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}

DBinMemory Prover::ruleD35(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6){
  /*
   * rule contri(A,B,C,P,Q,R) => contri(B,A,C,Q,P,R)
   * insert contri(B,A,C,Q,P,R)
   */


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('contri')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3,point4,point5,point6};
  if(uniquepoints.size()!=6){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Contri(typeGeoCmd,point1,point2,point3,point4,point5,point6,newFact) VALUES ('contri','"+point1+"','"+point2+"','"+point3+"','"+point4+"','"+point6+"','"+point5+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD36(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6){
  /*
   * rule contri(A,B,C,P,Q,R) => contri(P,Q,R,A,B,C)
   * insert contri(P,Q,R,A,B,C)
   */


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('contri')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3,point4,point5,point6};
  if(uniquepoints.size()!=6){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Contri(typeGeoCmd,point1,point2,point3,point4,point5,point6,newFact) VALUES ('contri','"+point2+"','"+point1+"','"+point3+"','"+point5+"','"+point4+"','"+point6+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD37(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6){
  /*
   * rule
   * insert
   */


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('contri')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3,point4,point5,point6};
  if(uniquepoints.size()!=6){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Contri(typeGeoCmd,point1,point2,point3,point4,point5,point6,newFact) VALUES ('contri','"+point4+"','"+point5+"','"+point6+"','"+point1+"','"+point2+"','"+point3+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD38(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6){
  /*
   * rule para(A,B,C,D) & para(C,D,E,F) => para(A,B,E.F)
   * insert para(A,B,E,F)
   */

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;
  std::string querySecondGeoCmdA,querySecondGeoCmdB,newPoint1,newPoint2,newPoint3;


  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('contri')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );//executing the statement
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0); // reading the 1st column of the result
  querySecondGeoCmdA = "SELECT point4,point5,point6 FROM NewFact INNER JOIN Contri ON (newFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 = '"+point3+"' and point4 <> '"+point4+"' and point5 <> '"+point5+"' and point6 <> '"+point6+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);
  querySecondGeoCmdB = "SELECT point4,point5,point6 FROM Facts INNER JOIN Contri ON (oldFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 = '"+point3+"' and point4 <> '"+point4+"' and point5 <> '"+point5+"' and point6 <> '"+point6+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);
  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0 ) {
    correctTransaction=false;
  }
  else {if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint1 = (char*) sqlite3_column_text(dbim.stmt1, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt1, 1);newPoint3 = (char*) sqlite3_column_text(dbim.stmt1, 2);}
    else {newPoint1 = (char*) sqlite3_column_text(dbim.stmt2, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt2, 1);newPoint3 = (char*) sqlite3_column_text(dbim.stmt2, 2);}
    if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
    else {
      insertionColl = "INSERT INTO Contri(typeGeoCmd,point1,point2,point3,point4,point5,point6,newFact) VALUES ('contri','"+newPoint1+"','"+newPoint2+"','"+newPoint3+"','"+point4+"','"+point5+"','"+point6+"','"+lstInsRwId+"')";
      dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
      if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
    }
  }


  //      correctTransaction=false;

  if (correctTransaction) {
    sqlite3_exec(dbim.db, "commit;", 0, 0, 0);
  }
  else { // pode acontecer que o novo facto já existe na bd
    sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);
  }
  return(dbim);
}


DBinMemory Prover::ruleD39(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6,std::string point7,std::string point8){
  /*
   * rule
   * insert
   */


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('para')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3,point4,point5,point6,point7,point8};
  if(uniquepoints.size()!=6 || point3!=point7 || point4!=point8){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Parallel(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('para','"+point1+"','"+point2+"','"+point5+"','"+point6+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD40(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){
  /*
   * rule
   * insert
   */


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('eqangle')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=4){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Eqangle(typeGeoCmd,point1,point2,point3,point4,point5,point6,point7,point8,newFact) VALUES ('eqangle','"+point1+"','"+point2+"','P','Q','"+point3+"','"+point4+"','P','Q','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD41(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){
  /*
   * rule
   * insert
   */


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('eqangle')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=4){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Eqangle(typeGeoCmd,point1,point2,point3,point4,point5,point6,point7,point8,newFact) VALUES ('eqangle','"+point3+"','"+point1+"','"+point3+"','"+point2+"','"+point4+"','"+point1+"','"+point4+"','"+point2+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}

//cyclic(A;B;P;Q) :- eqangle(P;A;P;B;Q;A;Q;B), NOT coll(P;Q;A;B).
DBinMemory Prover::ruleD42(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6,std::string point7,std::string point8){

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,querySecondGeoCmdA,querySecondGeoCmdB;
  bool Fcoll,Fcoll2,correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('cyclic')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;
  Fcoll=false;
  Fcoll2=false;

  std::set<std::string> uniquepoints={point1,point2,point3,point4,point5,point6,point7,point8};
  if(uniquepoints.size()!=4 || point1!=point3 || point4!=point8 || point5!=point7 || point2!=point6){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  querySecondGeoCmdA = "SELECT point1 FROM NewFact INNER JOIN Collinear ON (newFact=id) WHERE point1 in ('"+point1+"','"+point5+"','"+point2+"') and point2 in ('"+point1+"','"+point5+"','"+point2+"') and point2 not in (point1) and point3 in ('"+point1+"','"+point5+"','"+point2+"') and point3 not in (point1,point2)";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point1 FROM Facts INNER JOIN Collinear ON (oldFact=id) WHERE point1 in ('"+point1+"','"+point5+"','"+point2+"') and point2 in ('"+point1+"','"+point5+"','"+point2+"') and point2 not in (point1) and point3 in ('"+point1+"','"+point5+"','"+point2+"') and point3 not in (point1,point2)";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) != 0 || sqlite3_data_count(dbim.stmt2) != 0) {Fcoll=true;}


    querySecondGeoCmdA = "SELECT point1 FROM NewFact INNER JOIN Collinear ON (newFact=id) WHERE point1 in ('"+point5+"','"+point2+"','"+point4+"') and point2 in ('"+point5+"','"+point2+"','"+point4+"') and point2 not in (point1) and point3 in ('"+point5+"','"+point2+"','"+point4+"') and point3 not in (point1,point2)";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point1 FROM Facts INNER JOIN Collinear ON (oldFact=id) WHERE point1 in ('"+point5+"','"+point2+"','"+point4+"') and point2 in ('"+point5+"','"+point2+"','"+point4+"') and point2 not in (point1) and point3 in ('"+point5+"','"+point2+"','"+point4+"') and point3 not in (point1,point2)";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) != 0 || sqlite3_data_count(dbim.stmt2) != 0) {Fcoll2=true;}

  if (Fcoll==1 && Fcoll2==1) {correctTransaction=false;}

  insertionColl = "INSERT INTO Cyclic(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('cyclic','"+point2+"','"+point4+"','"+point1+"','"+point5+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}

//Note: Two searches because the program can't handle a rule that requires a Cyclic element with 6 values.
DBinMemory Prover::ruleD43Eqangle(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6,std::string point7,std::string point8){

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('cong')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3,point4,point5,point6,point7,point8};
  if(uniquepoints.size()!=6 || point1!=point3 || point5!=point7){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  querySecondGeoCmdA = "SELECT point1 FROM NewFact INNER JOIN Cyclic ON (newFact=id) WHERE point1 = '"+point2+"' and point2 = '"+point4+"' and point3 = '"+point1+"' and point4 = '"+point6+"'";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point1 FROM Facts INNER JOIN Cyclic ON (oldFact=id) WHERE point1 = '"+point2+"' and point2 = '"+point4+"' and point3 = '"+point1+"' and point4 = '"+point6+"'";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}

  querySecondGeoCmdA = "SELECT point1 FROM NewFact INNER JOIN Cyclic ON (newFact=id) WHERE point1 = '"+point3+"' and point2 = '"+point6+"' and point3 = '"+point8+"' and point4 = '"+point7+"'";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point1 FROM Facts INNER JOIN Cyclic ON (oldFact=id) WHERE point1 = '"+point2+"' and point2 = '"+point4+"' and point3 = '"+point8+"' and point4 = '"+point7+"'";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}

  insertionColl = "INSERT INTO Cong(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('cong','"+point2+"','"+point4+"','"+point6+"','"+point8+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}

/*
DBinMemory Prover::ruleD43Cyclic(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6,std::string point7,std::string point8){

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('cong')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3,point4,point5,point6};
  if(uniquepoints.size()!=6){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);
//cong(A, B, P , Q) :−cyclic(A, B, C, P , Q, R), eqangle(C, A, C, B, R, P , R, Q).
  querySecondGeoCmdA = "SELECT point1 FROM NewFact INNER JOIN Eqangle ON (newFact=id) WHERE point1 = '"+point3+"' and point2 = '"+point1+"' and point3 = '"+point3+"' and point4 = '"+point2+"' and point5 = '"+point6+"' and point6 = '"+point4+"' and point7 = '"+point6+"' and point8 = '"+point5+"'";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point1 FROM Facts INNER JOIN Eqangle ON (oldFact=id) WHERE point1 = '"+point3+"' and point2 = '"+point1+"' and point3 = '"+point3+"' and point4 = '"+point2+"' and point5 = '"+point6+"' and point6 = '"+point4+"' and point7 = '"+point6+"' and point8 = '"+point5+"'";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}


  querySecondGeoCmdA = "SELECT point1 FROM NewFact INNER JOIN Cyclic ON (newFact=id) WHERE point1 = '"+point3+"' and point2 = '"+point6+"' and point3 = '"+point8+"' and point4 = '"+point7+"'";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point1 FROM Facts INNER JOIN Cyclic ON (oldFact=id) WHERE point1 = '"+point2+"' and point2 = '"+point4+"' and point3 = '"+point8+"' and point4 = '"+point7+"'";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}

  insertionColl = "INSERT INTO Cong(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('cong','"+point1+"','"+point2+"','"+point4+"','"+point5+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}
*/

DBinMemory Prover::ruleD44(DBinMemory dbim,std::string point1,std::string point2,std::string point3){


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;
  std::string querySecondGeoCmdA,querySecondGeoCmdB,newPoint1,newPoint2;


  //      std::cout << "Derive new facts: " << typeGeoCmd << "---rule 3\n";

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('para')";

  // O valor de NewFact row id tem de ser obtido através de uma consulta
  lastInsertedRowId = "SELECT last_insert_rowid()";

  //Open transaction
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  // insertion of a new fact in NewFact table and get the lastInsertedRowId
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);

  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {
    correctTransaction = false;
  }
  // get the last Inserted Row Id
  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);

  sqlite3_step( dbim.stmt );//executing the statement
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0); // reading the 1st column of the result
  //      std::cout << "lstInsRwId: " << lstInsRwId << std::endl << std::endl;


  // Query for the second 'coll' matching the rule
  // two queries, the second coll can be still in the NewFacts or in the Facts table
  querySecondGeoCmdA = "SELECT point1,point3 FROM NewFact INNER JOIN Midpoint ON (newFact=id) WHERE point1 <> '"+point1+"' and point2 = '"+point2+"' and point3 <> '"+point3+"'";
  //      std::cout << querySecondGeoCmd <<  std::endl;

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point1,point3 FROM Facts INNER JOIN Midpoint ON (oldFact=id) WHERE point1 <> '"+point1+"' and point2 = '"+point2+"' and point3 <> '"+point3+"'";
  //      std::cout << querySecondGeoCmd <<  std::endl;

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0 ) {
    correctTransaction=false;
  }
  else { // At least one result for rule 3
    if (sqlite3_data_count(dbim.stmt1) != 0) {
      newPoint1 = (char*) sqlite3_column_text(dbim.stmt1, 0);
      newPoint2 = (char*) sqlite3_column_text(dbim.stmt1, 1);
    }
    else {
      newPoint1 = (char*) sqlite3_column_text(dbim.stmt2, 0);
      newPoint2 = (char*) sqlite3_column_text(dbim.stmt2, 1);
    }
    if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {
      // if the query result is void... it stops
      correctTransaction = false;
    }
    else {
      insertionColl = "INSERT INTO Parallel(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('para','"+point1+"','"+newPoint1+"','"+point3+"','"+newPoint2+"','"+lstInsRwId+"')";

      //	  std::cout << insertionColl << std::endl;

      dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
      if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {
	correctTransaction = false;
      }
    }
  }


  //      correctTransaction=false;

  if (correctTransaction) {
    sqlite3_exec(dbim.db, "commit;", 0, 0, 0);
  }
  else { // pode acontecer que o novo facto já existe na bd
    sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);
  }
  return(dbim);
}


DBinMemory Prover::ruleD45Coll(DBinMemory dbim,std::string point1,std::string point2,std::string point3){
  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,querySecondGeoCmdA,querySecondGeoCmdB,newPoint1,newPoint2;
  bool correctTransaction,correctTransactionA,correctTransactionB;
  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('midp')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));
  correctTransaction=true;

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  if (sqlite3_data_count(dbim.stmt1) != 0 || sqlite3_data_count(dbim.stmt2) != 0 ) {correctTransaction=false;}

  querySecondGeoCmdA = "SELECT point1,point3 FROM NewFact INNER JOIN Midpoint ON (newFact=id) WHERE point2 = '"+point2+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);
  if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint1 = (char*) sqlite3_column_text(dbim.stmt1, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt1, 1);}
  querySecondGeoCmdB = "SELECT point1,point3 FROM Facts INNER JOIN Midpoint  ON (oldFact=id) WHERE point2 = '"+point2+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);
  if (sqlite3_data_count(dbim.stmt2) != 0) {newPoint1 = (char*) sqlite3_column_text(dbim.stmt2, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt2, 1);}

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0 ) {correctTransaction=false;}
  else{

      querySecondGeoCmdA = "SELECT point1 FROM NewFact INNER JOIN Parallel ON (newFact=id) WHERE point1 = '"+newPoint1+"' and point2 = '"+point1+"' and point3 = '"+newPoint2+"' and point4 = '"+point3+"'";
      dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
      sqlite3_step(dbim.stmt1);
      querySecondGeoCmdB = "SELECT point1 FROM Facts INNER JOIN Parallel  ON (oldFact=id) WHERE point1 = '"+newPoint1+"' and point2 = '"+point1+"' and point3 = '"+newPoint2+"' and point4 = '"+point3+"'";
      dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
      sqlite3_step(dbim.stmt2);
      if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0 ) {correctTransaction=false;}}

  insertionColl = "INSERT INTO Midpoint(typeGeoCmd,point1,point2,point3,newFact) VALUES ('midp','"+point1+"','"+point2+"','"+point3+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);

  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}
  return(dbim);
}


DBinMemory Prover::ruleD45Para(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){
  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('midp')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=4){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";

  querySecondGeoCmdA = "SELECT point2 FROM NewFact INNER JOIN Midpoint ON (newFact=id) WHERE point1 = '"+point1+"' and point3 = '"+point3+"' and point2 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point2 FROM Facts INNER JOIN Midpoint ON (oldFact=id) WHERE point1 = '"+point1+"' and point3 = '"+point3+"' and point2 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);}

  querySecondGeoCmdA = "SELECT point2 FROM NewFact INNER JOIN Collinear ON (newFact=id) WHERE point1 = '"+point2+"' and point2 = '"+newPoint+"' and point3 = '"+point4+"'";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point2 FROM Facts INNER JOIN Collinear ON (oldFact=id) WHERE point1 = '"+point2+"' and point2 = '"+newPoint+"' and point3 = '"+point4+"'";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}

  insertionColl = "INSERT INTO Midpoint(typeGeoCmd,point1,point2,point3,newFact) VALUES ('midp','"+point1+"','"+newPoint+"','"+point3+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD45Midp(DBinMemory dbim,std::string point1,std::string point2,std::string point3){
  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('midp')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3};
  if(uniquepoints.size()!=3){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";
  newPoint2="";
//midp(F, A, C) :− midp(E, A, B), para(E, F, B, C), coll(F, A, C).
  querySecondGeoCmdA = "SELECT point2,point4 FROM NewFact INNER JOIN Parallel ON (newFact=id) WHERE point1 = '"+point1+"' and point3 = '"+point3+"' and point2 not in ('"+point1+"','"+point2+"','"+point3+"') and point4 not in ('"+point1+"','"+point2+"','"+point3+"',point2)";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point2 FROM Facts INNER JOIN Parallel ON (oldFact=id) WHERE point1 = '"+point1+"' and point3 = '"+point3+"' and point2 not in ('"+point1+"','"+point2+"','"+point3+"') and point4 not in ('"+point1+"','"+point2+"','"+point3+"',point2)";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt1, 1);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt2, 1);}

  querySecondGeoCmdA = "SELECT point2 FROM NewFact INNER JOIN Collinear ON (newFact=id) WHERE point1 = '"+newPoint+"' and point2 = '"+point2+"' and point3 = '"+newPoint2+"'";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point2 FROM Facts INNER JOIN Collinear ON (oldFact=id) WHERE point1 = '"+newPoint+"' and point2 = '"+point2+"' and point3 = '"+newPoint2+"'";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
//midp(F, A, C) :− midp(E, A, B), para(E, F, B, C), coll(F, A, C).
  insertionColl = "INSERT INTO Midpoint(typeGeoCmd,point1,point2,point3,newFact) VALUES ('midp','"+newPoint+"','"+point2+"','"+newPoint2+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD46(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){
  /*
   * rule
   * insert
   */


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('eqangle')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=3 || point1!=point3){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Eqangle(typeGeoCmd,point1,point2,point3,point4,point5,point6,point7,point8,newFact) VALUES ('eqangle','"+point1+"','"+point2+"','"+point2+"','"+point4+"','"+point2+"','"+point4+"','"+point1+"','"+point4+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD47(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6,std::string point7,std::string point8){
  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction,correctTransactionA,correctTransactionB;
  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('cong')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));
  correctTransaction=true;

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  if(point2!=point3 || point2!=point5 || point4!=point6 || point4!=point8){correctTransaction=false;}

  querySecondGeoCmdA = "SELECT * FROM NewFact INNER JOIN Collinear ON (newFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 = '"+point4+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);
  querySecondGeoCmdB = "SELECT * FROM Facts INNER JOIN Collinear  ON (oldFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 = '"+point4+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);
  if (sqlite3_data_count(dbim.stmt1) != 0 || sqlite3_data_count(dbim.stmt2) != 0 ) {correctTransaction=false;}

  insertionColl = "INSERT INTO Cong(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('cong','"+point1+"','"+point2+"','"+point1+"','"+point4+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}
  return(dbim);
}


DBinMemory Prover::ruleD48Circle(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){
//eqangle(A, X, A, B, C, A, C, B) :− circle(O, A, B, C), perp(O, A, A, X).

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('eqangle')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=4){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";

  querySecondGeoCmdA = "SELECT point4 FROM NewFact INNER JOIN Perpendicular ON (newFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' andpoint2 = point3 and point4 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point4 FROM Facts INNER JOIN Perpendicular ON (oldFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' andpoint2 = point3 and point4 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);}

  insertionColl = "INSERT INTO Eqangle(typeGeoCmd,point1,point2,point3,point4,point5,point6,point7,point8,newFact) VALUES ('eqangle','"+point2+"','"+newPoint+"','"+point2+"','"+point3+"','"+point4+"','"+point2+"','"+point4+"','"+point3+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD48Perp(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('eqangle')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=3 || point2!=point3){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";
  newPoint2="";

  querySecondGeoCmdA = "SELECT point3,point4 FROM NewFact INNER JOIN Circle ON (newFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 not in ('"+point1+"','"+point2+"','"+point4+"') and point4 not in ('"+point1+"','"+point2+"','"+point4+"',point3)";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point3,point4 FROM Facts INNER JOIN Circle ON (oldFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 not in ('"+point1+"','"+point2+"','"+point4+"') and point4 not in ('"+point1+"','"+point2+"','"+point4+"',point3)";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt1, 1);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt2, 1);}

  insertionColl = "INSERT INTO Eqangle(typeGeoCmd,point1,point2,point3,point4,point5,point6,point7,point8,newFact) VALUES ('eqangle','"+point2+"','"+point4+"','"+point2+"','"+newPoint+"','"+newPoint2+"','"+point2+"','"+newPoint2+"','"+newPoint+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD49Circle(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;
  std::string querySecondGeoCmdA,querySecondGeoCmdB,newPoint,newPoint2;


  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('perp')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );//executing the statement
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0); // reading the 1st column of the result

  querySecondGeoCmdA = "SELECT point2 FROM NewFact INNER JOIN Eqangle ON (newFact=id) WHERE point1 = '"+point2+"' and point3 = '"+point2+"' and point4 = '"+point3+"' and point5 = '"+point4+"' and point6 = '"+point2+"' and point7 = '"+point4+"' and point8 = '"+point3+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);
  querySecondGeoCmdB = "SELECT point2 FROM Facts INNER JOIN Eqangle ON (oldFact=id) WHERE point1 = '"+point2+"' and point3 = '"+point2+"' and point4 = '"+point3+"' and point5 = '"+point4+"' and point6 = '"+point2+"' and point7 = '"+point4+"' and point8 = '"+point3+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);
  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else {if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);}
    else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);}
    if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
    else {
      insertionColl = "INSERT INTO Perpendicular(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('perp','"+point1+"','"+point2+"','"+point2+"','"+newPoint+"','"+lstInsRwId+"')";
      dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
      if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
    }
  }

  //      correctTransaction=false;

  if (correctTransaction) {
    sqlite3_exec(dbim.db, "commit;", 0, 0, 0);
  }
  else { // pode acontecer que o novo facto já existe na bd
    sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);
  }
  return(dbim);
}


DBinMemory Prover::ruleD49Eqangle(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6,std::string point7,std::string point8){


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;
  std::string querySecondGeoCmdA,querySecondGeoCmdB,newPoint,newPoint2;


  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('perp')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );//executing the statement
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0); // reading the 1st column of the result
  if (point1!=point3 || point1!=point6 || point5!=point7 || point4!=point8) {
    correctTransaction=false;
  }
  querySecondGeoCmdA = "SELECT point1 FROM NewFact INNER JOIN Circle ON (newFact=id) WHERE point2 = '"+point6+"' and point3 = '"+point7+"' and point4 = '"+point8+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);
  querySecondGeoCmdB = "SELECT point1 FROM Facts INNER JOIN Circle ON (oldFact=id) WHERE point2 = '"+point6+"' and point3 = '"+point7+"' and point4 = '"+point8+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);
  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {
    correctTransaction=false;
  }
  else {if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);}
    else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);}
    if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
    else {
      insertionColl = "INSERT INTO Perpendicular(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('perp','"+newPoint+"','"+point1+"','"+point1+"','"+point2+"','"+lstInsRwId+"')";
      dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
      if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
    }
  }

  //      correctTransaction=false;

  if (correctTransaction) {
    sqlite3_exec(dbim.db, "commit;", 0, 0, 0);
  }
  else { // pode acontecer que o novo facto já existe na bd
    sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);
  }
  return(dbim);
}


DBinMemory Prover::ruleD50Circle(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('eqangle')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=4){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";

  querySecondGeoCmdA = "SELECT point1 FROM NewFact INNER JOIN Midpoint ON (newFact=id) WHERE point2 = '"+point3+"' and point3 = '"+point4+"' and point1 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point1 FROM Facts INNER JOIN Midpoint ON (oldFact=id) WHERE point2 = '"+point3+"' and point3 = '"+point4+"' and point1 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);}

  insertionColl = "INSERT INTO Eqangle(typeGeoCmd,point1,point2,point3,point4,point5,point6,point7,point8,newFact) VALUES ('eqangle','"+point2+"','"+point3+"','"+point2+"','"+point4+"','"+point1+"','"+point3+"','"+point1+"','"+newPoint+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD50Midp(DBinMemory dbim,std::string point1,std::string point2,std::string point3){


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;
  std::string querySecondGeoCmdA,querySecondGeoCmdB,newPoint,newPoint2;


  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('eqangle')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );//executing the statement
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0); // reading the 1st column of the result
  querySecondGeoCmdA = "SELECT point1,point2 FROM NewFact INNER JOIN Circle ON (newFact=id) WHERE point3 = '"+point2+"' and point4 = '"+point3+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);
  querySecondGeoCmdB = "SELECT point1,point2 FROM Facts INNER JOIN Circle ON (oldFact=id) WHERE point3 = '"+point2+"' and point4 = '"+point3+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);
  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {
    correctTransaction=false;
  }
  else {if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt1, 1);}
    else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt2, 1);}
    if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
    else {
      insertionColl = "INSERT INTO Eqangle(typeGeoCmd,point1,point2,point3,point4,point5,point6,point7,point8,newFact) VALUES ('eqangle','"+newPoint2+"','"+point2+"','"+newPoint2+"','"+point3+"','"+newPoint2+"','"+point2+"','"+newPoint+"','"+point1+"','"+lstInsRwId+"')";
      dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
      if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
    }
  }

  //      correctTransaction=false;

  if (correctTransaction) {
    sqlite3_exec(dbim.db, "commit;", 0, 0, 0);
  }
  else { // pode acontecer que o novo facto já existe na bd
    sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);
  }
  return(dbim);
}


DBinMemory Prover::ruleD51(DBinMemory dbim,std::string point1,std::string point2,std::string point3){
//midp(M, B, C) :−circle(O, A, B, C), coll(M, B, C), eqangle(A, B, A, C, O, B, O, M).
  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('midp')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3};
  if(uniquepoints.size()!=3){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";
  newPoint2="";

  querySecondGeoCmdA = "SELECT point1,point2 FROM NewFact INNER JOIN Circle ON (newFact=id) WHERE point3 = '"+point2+"' and point4 = '"+point3+"' and point1 not in ('"+point1+"','"+point2+"','"+point3+"') and point2 not in ('"+point1+"','"+point2+"','"+point3+"',point1)";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point1,point2 FROM Facts INNER JOIN Circle ON (oldFact=id) WHERE point3 = '"+point2+"' and point4 = '"+point3+"' and point1 not in ('"+point1+"','"+point2+"','"+point3+"') and point2 not in ('"+point1+"','"+point2+"','"+point3+"',point1)";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt1, 1);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt2, 1);}
//midp(M, B, C) :−circle(O, A, B, C), coll(M, B, C), eqangle(A, B, A, C, O, B, O, M).
  querySecondGeoCmdA = "SELECT point1 FROM NewFact INNER JOIN Eqangle ON (newFact=id) WHERE point1 = '"+newPoint2+"' and point2 = '"+point2+"' and point3 = '"+newPoint2+"' and point4 = '"+point3+"' and point5 = '"+newPoint+"' and point6 = '"+point2+"' and point7 = '"+newPoint+"' and point8 = '"+point1+"'";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point1 FROM Facts INNER JOIN Eqangle ON (oldFact=id) WHERE point1 = '"+newPoint2+"' and point2 = '"+point2+"' and point3 = '"+newPoint2+"' and point4 = '"+point3+"' and point5 = '"+newPoint+"' and point6 = '"+point2+"' and point7 = '"+newPoint+"' and point8 = '"+point1+"'";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}

  insertionColl = "INSERT INTO Midpoint(typeGeoCmd,point1,point2,point3,newFact) VALUES ('midp','"+point1+"','"+point2+"','"+point3+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}

DBinMemory Prover::ruleD52Perp(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('cong')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=3 || point2!=point3){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";

  querySecondGeoCmdA = "SELECT point1 FROM NewFact INNER JOIN Midpoint ON (newFact=id) WHERE point2 = '"+point1+"' and point3 = '"+point4+"' and point1 not in ('"+point1+"','"+point2+"','"+point4+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point1 FROM Facts INNER JOIN Midpoint ON (oldFact=id) WHERE point2 = '"+point1+"' and point3 = '"+point4+"' and point1 not in ('"+point1+"','"+point2+"','"+point4+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);}

  insertionColl = "INSERT INTO Cong(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('cong','"+point1+"','"+newPoint+"','"+point2+"','"+newPoint+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD52Midp(DBinMemory dbim,std::string point1,std::string point2,std::string point3){

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('cong')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3};
  if(uniquepoints.size()!=3){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";

  querySecondGeoCmdA = "SELECT point3,point4 FROM NewFact INNER JOIN Perpendicular ON (newFact=id) WHERE point1 = '"+point2+"' and point4 = '"+point3+"' and point2 = point3 and point2 not in ('"+point1+"','"+point2+"','"+point3+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point3,point4 FROM Facts INNER JOIN Perpendicular ON (oldFact=id) WHERE point1 = '"+point2+"' and point4 = '"+point3+"' and point2 = point3 and point2 not in ('"+point1+"','"+point2+"','"+point3+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);}

  insertionColl = "INSERT INTO Cong(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('cong','"+point2+"','"+point1+"','"+newPoint+"','"+point1+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD53Circle(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;
  std::string querySecondGeoCmdA,querySecondGeoCmdB;


  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('perp')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );//executing the statement
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0); // reading the 1st column of the result

  querySecondGeoCmdA = "SELECT * FROM NewFact INNER JOIN Collinear ON (newFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 = '"+point4+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);
  querySecondGeoCmdB = "SELECT * FROM Facts INNER JOIN Collinear ON (oldFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 = '"+point4+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);
  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else{
    insertionColl = "INSERT INTO Perpendicular(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('perp','"+point2+"','"+point3+"','"+point3+"','"+point4+"','"+lstInsRwId+"')";
    dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);}
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {
    correctTransaction = false;
  }

  if (correctTransaction) {
    sqlite3_exec(dbim.db, "commit;", 0, 0, 0);
  }
  else { // pode acontecer que o novo facto já existe na bd
    sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);
  }

  return(dbim);
}


DBinMemory Prover::ruleD53Coll(DBinMemory dbim,std::string point1,std::string point2,std::string point3){
  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('perp')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3};
  if(uniquepoints.size()!=3){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";
//perp(A, B, B, C) :− circle(O, A, B, C), coll(O, A, C).
  querySecondGeoCmdA = "SELECT point3 FROM NewFact INNER JOIN Circle ON (newFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point4 = '"+point3+"' and point3 not in ('"+point1+"','"+point2+"','"+point3+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point3 FROM Facts INNER JOIN Circle ON (oldFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point4 = '"+point3+"' and point3 not in ('"+point1+"','"+point2+"','"+point3+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);}

  insertionColl = "INSERT INTO Perpendicular(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('perp','"+point2+"','"+newPoint+"','"+newPoint+"','"+point3+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}

DBinMemory Prover::ruleD54Cyclic(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('eqangle')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=4){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  querySecondGeoCmdA = "SELECT point1 FROM NewFact INNER JOIN Parallel ON (newFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 = '"+point3+"' and point4 = '"+point4+"'";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point1 FROM Facts INNER JOIN Parallel ON (oldFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 = '"+point3+"' and point4 = '"+point4+"'";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}

  insertionColl = "INSERT INTO Eqangle(typeGeoCmd,point1,point2,point3,point4,point5,point6,point7,point8,newFact) VALUES ('eqangle','"+point1+"','"+point4+"','"+point3+"','"+point4+"','"+point3+"','"+point4+"','"+point3+"','"+point2+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD54Para(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;
  std::string querySecondGeoCmdA,querySecondGeoCmdB;


  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('eqangle')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );//executing the statement
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0); // reading the 1st column of the result

  querySecondGeoCmdA = "SELECT point1 FROM NewFact INNER JOIN Cyclic ON (newFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 = '"+point3+"' and point4 = '"+point4+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);
  querySecondGeoCmdB = "SELECT point1 FROM Facts INNER JOIN Cyclic ON (oldFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 = '"+point3+"' and point4 = '"+point4+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);
  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else{
    insertionColl = "INSERT INTO Eqangle(typeGeoCmd,point1,point2,point3,point4,point5,point6,point7,point8,newFact) VALUES ('eqangle','"+point1+"','"+point4+"','"+point3+"','"+point4+"','"+point3+"','"+point4+"','"+point3+"','"+point2+"','"+lstInsRwId+"')";
    dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);}
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {
    correctTransaction = false;
  }

  if (correctTransaction) {
    sqlite3_exec(dbim.db, "commit;", 0, 0, 0);
  }
  else { // pode acontecer que o novo facto já existe na bd
    sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);
  }


  return(dbim);
}


DBinMemory Prover::ruleD55Perp(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;
  std::string querySecondGeoCmdA,querySecondGeoCmdB;


  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('cong')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );//executing the statement
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0); // reading the 1st column of the result

  querySecondGeoCmdA = "SELECT * FROM NewFact INNER JOIN Midpoint ON (newFact=id) WHERE point1 = '"+point2+"' and point2 = '"+point3+"' and point3 = '"+point4+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);
  querySecondGeoCmdB = "SELECT * FROM Facts INNER JOIN Midpoint ON (oldFact=id) WHERE point1 = '"+point2+"' and point2 = '"+point3+"' and point3 = '"+point4+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);
  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else{
    insertionColl = "INSERT INTO Cong(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('cong','"+point1+"','"+point3+"','"+point1+"','"+point4+"','"+lstInsRwId+"')";
    dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);}
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {
    correctTransaction = false;
  }

  //      correctTransaction=false;

  if (correctTransaction) {
    sqlite3_exec(dbim.db, "commit;", 0, 0, 0);
  }
  else { // pode acontecer que o novo facto já existe na bd
    sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);
  }
  return(dbim);
}


DBinMemory Prover::ruleD55Midp(DBinMemory dbim,std::string point1,std::string point2,std::string point3){
  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('cong')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3};
  if(uniquepoints.size()!=3){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";
//cong(O, A, O, B) :− midp(M, A, B), perp(O, M, A, B).
  querySecondGeoCmdA = "SELECT point1 FROM NewFact INNER JOIN Perpendicular ON (newFact=id) WHERE point2 = '"+point1+"' and point3 = '"+point2+"' and point4 = '"+point3+"' and point1 not in ('"+point1+"','"+point2+"','"+point3+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point1 FROM Facts INNER JOIN Perpendicular ON (oldFact=id) WHERE point2 = '"+point1+"' and point3 = '"+point2+"' and point4 = '"+point3+"' and point1 not in ('"+point1+"','"+point2+"','"+point3+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);}

  insertionColl = "INSERT INTO Cong(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('cong','"+newPoint+"','"+point2+"','"+newPoint+"','"+point3+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD56(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('perp')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3};
  if(uniquepoints.size()!=3 || point2!=point4){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";

  querySecondGeoCmdA = "SELECT point2 FROM NewFact INNER JOIN Cong ON (newFact=id) WHERE point1 = '"+point1+"' and point3 = '"+point3+"' and point2=point4 and point2 not in ('"+point1+"','"+point2+"','"+point3+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point2 FROM Facts INNER JOIN Cong ON (oldFact=id) WHERE point1 = '"+point1+"' and point3 = '"+point3+"' and point2=point4 and point2 not in ('"+point1+"','"+point2+"','"+point3+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);}

  insertionColl = "INSERT INTO Perpendicular(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('perp','"+point1+"','"+point3+"','"+point4+"','"+newPoint+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD57Circle(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){
  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction,correctTransactionA,correctTransactionB;
  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('perp')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));
  correctTransaction=true;

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  querySecondGeoCmdA = "SELECT point1 FROM NewFact INNER JOIN Cong ON (newFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point4+"' and point3 = '"+point2+"' and point4 = '"+point4+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);
  querySecondGeoCmdB = "SELECT point1 FROM Facts INNER JOIN Cong  ON (oldFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point4+"' and point3 = '"+point2+"' and point4 = '"+point4+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);
  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0 ) {correctTransaction=false;}


  querySecondGeoCmdA = "SELECT point1 FROM NewFact INNER JOIN Cong ON (newFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point3+"' and point3 = '"+point2+"' and point4 = '"+point3+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);
  querySecondGeoCmdB = "SELECT point1 FROM Facts INNER JOIN Cong  ON (oldFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point3+"' and point3 = '"+point2+"' and point4 = '"+point3+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);
  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0 ) {correctTransaction=false;}

  insertionColl = "INSERT INTO Perpendicular(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('perp','"+point3+"','"+point1+"','"+point1+"','"+point4+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}
  return(dbim);
}


DBinMemory Prover::ruleD57Cong(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){
  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('perp')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=3 || point2!=point4){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";
//perp(P , A, A, Q) :−cong(A, P , B, P ), cong(A, Q, B, Q), cyclic(A, B, P , Q).
  querySecondGeoCmdA = "SELECT point2 FROM NewFact INNER JOIN Cong ON (newFact=id) WHERE point1 = '"+point1+"' and point3 = '"+point3+"' and point2 not in ('"+point1+"','"+point2+"','"+point3+"') and point2 = point4 ";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point2 FROM Facts INNER JOIN Cong ON (oldFact=id) WHERE point1 = '"+point1+"' and point3 = '"+point3+"' and point2 not in ('"+point1+"','"+point2+"','"+point3+"') and point2 = point4 ";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);}

  querySecondGeoCmdA = "SELECT point2 FROM NewFact INNER JOIN Cyclic ON (newFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point3+"' and point3 = '"+point2+"' and point4 = '"+newPoint+"'";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point2 FROM Facts INNER JOIN Cyclic ON (oldFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point3+"' and point3 = '"+point2+"' and point4 = '"+newPoint+"'";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}

  insertionColl = "INSERT INTO Perpendicular(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('perp','"+point2+"','"+point1+"','"+point1+"','"+newPoint+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}

DBinMemory Prover::ruleD58B(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6,std::string point7,std::string point8){
  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction,correctTransactionA,correctTransactionB;
  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('simtri')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));
  correctTransaction=true;

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  if(point2!=point3 || point6!=point7){correctTransaction=false;}

  querySecondGeoCmdA = "SELECT * FROM NewFact INNER JOIN Eqangle ON (newFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point4+"' and point3 = '"+point2+"' and point4 = '"+point4+"' and point5 = '"+point5+"' and point6 = '"+point8+"' and point7 = '"+point6+"' and point8 = '"+point8+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);
  querySecondGeoCmdB = "SELECT * FROM Facts INNER JOIN Eqangle  ON (oldFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point4+"' and point3 = '"+point2+"' and point4 = '"+point4+"' and point5 = '"+point5+"' and point6 = '"+point8+"' and point7 = '"+point6+"' and point8 = '"+point8+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);
  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0 ) {correctTransaction=false;}

  querySecondGeoCmdA = "SELECT * FROM NewFact INNER JOIN Collinear ON (newFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 = '"+point4+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);
  querySecondGeoCmdB = "SELECT * FROM Facts INNER JOIN Collinear  ON (oldFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 = '"+point4+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);
  if (sqlite3_data_count(dbim.stmt1) != 0 || sqlite3_data_count(dbim.stmt2) != 0 ) {correctTransaction=false;}

  insertionColl = "INSERT INTO Simtri(typeGeoCmd,point1,point2,point3,point4,point5,point6,newFact) VALUES ('simtri','"+point1+"','"+point3+"','"+point4+"','"+point5+"','"+point7+"','"+point8+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}
  return(dbim);
}


DBinMemory Prover::ruleD58A(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6,std::string point7,std::string point8){
  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction,correctTransactionA,correctTransactionB;
  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('simtri')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));
  correctTransaction=true;

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  if(point2!=point4 || point6!=point8){correctTransaction=false;}

  querySecondGeoCmdA = "SELECT * FROM NewFact INNER JOIN Eqangle ON (newFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point3+"' and point3 = '"+point3+"' and point4 = '"+point4+"' and point5 = '"+point5+"' and point6 = '"+point7+"' and point7 = '"+point7+"' and point8 = '"+point8+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);
  querySecondGeoCmdB = "SELECT * FROM Facts INNER JOIN Eqangle  ON (oldFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point3+"' and point3 = '"+point3+"' and point4 = '"+point4+"' and point5 = '"+point5+"' and point6 = '"+point7+"' and point7 = '"+point7+"' and point8 = '"+point8+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);
  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0 ) {correctTransaction=false;}

  querySecondGeoCmdA = "SELECT * FROM NewFact INNER JOIN Collinear ON (newFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 = '"+point3+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);
  querySecondGeoCmdB = "SELECT * FROM Facts INNER JOIN Collinear  ON (oldFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 = '"+point3+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);
  if (sqlite3_data_count(dbim.stmt1) != 0 || sqlite3_data_count(dbim.stmt2) != 0 ) {correctTransaction=false;}

  insertionColl = "INSERT INTO Simtri(typeGeoCmd,point1,point2,point3,point4,point5,point6,newFact) VALUES ('simtri','"+point1+"','"+point3+"','"+point4+"','"+point5+"','"+"','"+point7+"','"+point8+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}
  return(dbim);
}

DBinMemory Prover::ruleD59(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6){
  /*
   * rule
   * insert
   */


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('eqratio')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3,point4,point5,point6};
  if(uniquepoints.size()!=6){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Eqratio(typeGeoCmd,point1,point2,point3,point4,point5,point6,point7,point8,newFact) VALUES ('eqratio','"+point1+"','"+point2+"','"+point1+"','"+point3+"','"+point4+"','"+point5+"','"+point4+"','"+point6+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}



DBinMemory Prover::ruleD60(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6){
  /*
   * rule
   * insert
   */


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('eqangle')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3,point4,point5,point6};
  if(uniquepoints.size()!=6){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Eqangle(typeGeoCmd,point1,point2,point3,point4,point5,point6,point7,point8,newFact) VALUES ('eqangle','"+point1+"','"+point2+"','"+point2+"','"+point3+"','"+point4+"','"+point5+"','"+point5+"','"+point6+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}




DBinMemory Prover::ruleD61(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6){

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('contri')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3,point4,point5,point6};
  if(uniquepoints.size()!=6){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  insertionColl = "INSERT INTO Contri(typeGeoCmd,point1,point2,point3,point4,point5,point6,newFact) VALUES ('contri','"+point1+"','"+point2+"','"+point3+"','"+point4+"','"+point5+"','"+point6+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD62(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6){
  /*
   * rule
   * insert
   */


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('cong')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3,point4,point5,point6};
  if(uniquepoints.size()!=6){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Cong(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('cong','"+point1+"','"+point2+"','"+point4+"','"+point5+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}



DBinMemory Prover::ruleD63(DBinMemory dbim,std::string point1,std::string point2,std::string point3){

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('para')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3};
  if(uniquepoints.size()!=3){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";
  newPoint2="";

  querySecondGeoCmdA = "SELECT point2,point3 FROM NewFact INNER JOIN Midpoint ON (newFact=id) WHERE point1 = '"+point1+"' and point2 not in ('"+point1+"','"+point2+"','"+point3+"') and point3 not in ('"+point1+"','"+point2+"','"+point3+"',point2)";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point2,point3 FROM Facts INNER JOIN Midpoint ON (oldFact=id) WHERE point1 = '"+point1+"' and point2 not in ('"+point1+"','"+point2+"','"+point3+"') and point3 not in ('"+point1+"','"+point2+"','"+point3+"',point2)";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt1, 1);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt2, 1);}

  insertionColl = "INSERT INTO Parallel(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('para','"+point2+"','"+newPoint+"','"+point3+"','"+newPoint2+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}

DBinMemory Prover::ruleD64Para(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){
//midp(M, C, D) :− midp(M, A, B), para(A, C, B, D), para(A, D, B, C).
  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('midp')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=4){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";

  querySecondGeoCmdA = "SELECT point1 FROM NewFact INNER JOIN Midpoint ON (newFact=id) WHERE point2 = '"+point1+"' and point3 = '"+point3+"' and point1 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point1 FROM Facts INNER JOIN Midpoint ON (oldFact=id) WHERE point2 = '"+point1+"' and point3 = '"+point3+"' and point1 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);}


  querySecondGeoCmdA = "SELECT point1 FROM NewFact INNER JOIN Parallel ON (newFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point4+"' and point3 = '"+point3+"' and point4 = '"+point2+"'";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point1 FROM Facts INNER JOIN Parallel ON (oldFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point4+"' and point3 = '"+point3+"' and point4 = '"+point2+"'";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}

  insertionColl = "INSERT INTO Midpoint(typeGeoCmd,point1,point2,point3,newFact) VALUES ('midp','"+newPoint+"','"+point2+"','"+point4+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}



DBinMemory Prover::ruleD64Midp(DBinMemory dbim,std::string point1,std::string point2,std::string point3){
  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('midp')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3};
  if(uniquepoints.size()!=3){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";
  newPoint2="";

  querySecondGeoCmdA = "SELECT point2,point4 FROM NewFact INNER JOIN Parallel ON (newFact=id) WHERE point1 = '"+point2+"' and point3 = '"+point3+"' and point2 not in ('"+point1+"','"+point2+"','"+point3+"') and point4 not in ('"+point1+"','"+point2+"','"+point3+"',point3)";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point2,point4 FROM Facts INNER JOIN Parallel ON (oldFact=id) WHERE point1 = '"+point2+"' and point3 = '"+point3+"' and point2 not in ('"+point1+"','"+point2+"','"+point3+"') and point4 not in ('"+point1+"','"+point2+"','"+point3+"',point3)";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt1, 1);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt2, 1);}

  querySecondGeoCmdA = "SELECT * FROM NewFact INNER JOIN Parallel ON (newFact=id) WHERE point1 = '"+point2+"' and point3 = '"+point3+"' and point2 = '"+newPoint2+"' and point4 = '"+newPoint+"'";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT * FROM Facts INNER JOIN Parallel ON (oldFact=id) WHERE point1 = '"+point2+"' and point3 = '"+point3+"' and point2 not in ('"+point1+"','"+point2+"','"+point3+"') and point4 not in ('"+point1+"','"+point2+"','"+point3+"',point3)";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}

  insertionColl = "INSERT INTO Midpoint(typeGeoCmd,point1,point2,point3,newFact) VALUES ('midp','"+point1+"','"+newPoint+"','"+newPoint2+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD65Para(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('eqratio')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=4){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";

  querySecondGeoCmdA = "SELECT point1 FROM NewFact INNER JOIN Collinear ON (newFact=id) WHERE point2 = '"+point1+"' and point3 = '"+point3+"' and point1 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point1 FROM Facts INNER JOIN Collinear ON (oldFact=id) WHERE point2 = '"+point1+"' and point3 = '"+point3+"' and point1 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);}

  querySecondGeoCmdA = "SELECT point1 FROM NewFact INNER JOIN Collinear ON (newFact=id) WHERE point2 = '"+point2+"' and point3 = '"+point4+"' and point1 = '"+newPoint+"'";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point1 FROM Facts INNER JOIN Collinear ON (oldFact=id) WHERE point2 = '"+point2+"' and point3 = '"+point4+"' and point1 = '"+newPoint+"'";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}

  insertionColl = "INSERT INTO Eqratio(typeGeoCmd,point1,point2,point3,point4,point5,point6,point7,point8,newFact) VALUES ('eqratio','"+newPoint+"','"+point1+"','"+point1+"','"+point3+"','"+newPoint+"','"+point2+"','"+point2+"','"+point4+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD65Coll(DBinMemory dbim,std::string point1,std::string point2,std::string point3){
  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('eqratio')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3};
  if(uniquepoints.size()!=3){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";
  newPoint2="";

  querySecondGeoCmdA = "SELECT point2,point4 FROM NewFact INNER JOIN Parallel ON (newFact=id) WHERE point1 = '"+point2+"' and point3 = '"+point3+"' and point2 not in ('"+point1+"','"+point2+"','"+point3+"') and point4 not in ('"+point1+"','"+point2+"','"+point3+"',point2)";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point2,point4 FROM Facts INNER JOIN Parallel ON (oldFact=id) WHERE point1 = '"+point2+"' and point3 = '"+point3+"' and point2 not in ('"+point1+"','"+point2+"','"+point3+"') and point4 not in ('"+point1+"','"+point2+"','"+point3+"',point2)";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt1, 1);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt2, 1);}

  querySecondGeoCmdA = "SELECT * FROM NewFact INNER JOIN Collinear ON (newFact=id) WHERE point1 = '"+point1+"' and point2 = '"+newPoint+"' and point3 = '"+newPoint2+"'";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT * FROM Facts INNER JOIN Collinear ON (oldFact=id) WHERE point1 = '"+point1+"' and point2 = '"+newPoint+"' and point3 = '"+newPoint2+"'";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}

  insertionColl = "INSERT INTO Eqratio(typeGeoCmd,point1,point2,point3,point4,point5,point6,newFact) VALUES ('eqratio','"+point1+"','"+point2+"','"+point2+"','"+point3+"','"+point1+"','"+newPoint+"','"+newPoint+"','"+newPoint2+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD66(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){
  /*
   * rule
   * insert
   */


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('coll')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=3 || point1!=point3){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Collinear(typeGeoCmd,point1,point2,point3,newFact) VALUES ('coll','"+point1+"','"+point4+"','"+point2+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD67Cong(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('midp')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=3 || point1!=point3){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);
  querySecondGeoCmdA = "SELECT point1 FROM NewFact INNER JOIN Collinear ON (newFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 = '"+point4+"'";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point1 FROM Facts INNER JOIN Collinear ON (oldFact=id) WHERE point1 = '"+point3+"' and point2 = '"+point4+"' and point3 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"') and point4 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}

  insertionColl = "INSERT INTO Midpoint(typeGeoCmd,point1,point2,point3,newFact) VALUES ('midp','"+point1+"','"+point2+"','"+point4+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}

DBinMemory Prover::ruleD67Coll(DBinMemory dbim,std::string point1,std::string point2,std::string point3){
  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('midp')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3};
  if(uniquepoints.size()!=3){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  querySecondGeoCmdA = "SELECT * FROM NewFact INNER JOIN Cong ON (newFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 = '"+point1+"' and point4 = '"+point3+"'";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT * FROM Facts INNER JOIN Cong ON (oldFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 = '"+point1+"' and point4 = '"+point3+"'";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  insertionColl = "INSERT INTO Midpoint(typeGeoCmd,point1,point2,point3,newFact) VALUES ('midp','"+point1+"','"+point2+"','"+point3+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}

DBinMemory Prover::ruleD68(DBinMemory dbim,std::string point1,std::string point2,std::string point3){
  /*
   * rule
   * insert
   */


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('cong')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3};
  if(uniquepoints.size()!=3){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Cong(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('cong','"+point1+"','"+point2+"','"+point1+"','"+point3+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}



DBinMemory Prover::ruleD69(DBinMemory dbim,std::string point1,std::string point2,std::string point3){
  /*
   * rule
   * insert
   */


  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('coll')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  //Unique points check
  std::set<std::string> uniquepoints={point1,point2,point3};
  if(uniquepoints.size()!=3){correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

  insertionColl = "INSERT INTO Collinear(typeGeoCmd,point1,point2,point3,newFact) VALUES ('coll','"+point1+"','"+point2+"','"+point3+"','"+lstInsRwId+"')";

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD70(DBinMemory dbim,std::string point1,std::string point2,std::string point3){

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;
  std::string querySecondGeoCmdA,querySecondGeoCmdB,newPoint1,newPoint2,newPoint3;


  //      std::cout << "Derive new facts: " << typeGeoCmd << "---rule 3\n";

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('eqratio')";

  // O valor de NewFact row id tem de ser obtido através de uma consulta
  lastInsertedRowId = "SELECT last_insert_rowid()";

  //Open transaction
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  // insertion of a new fact in NewFact table and get the lastInsertedRowId
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);

  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {
    correctTransaction = false;
  }
  // get the last Inserted Row Id
  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);

  sqlite3_step( dbim.stmt );//executing the statement
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0); // reading the 1st column of the result
  //      std::cout << "lstInsRwId: " << lstInsRwId << std::endl << std::endl;


  // Query for the second 'coll' matching the rule
  // two queries, the second coll can be still in the NewFacts or in the Facts table
  querySecondGeoCmdA = "SELECT point1,point2,point3 FROM NewFact INNER JOIN Midpoint ON (newFact=id) WHERE point1 <> '"+point1+"' and point1 <> '"+point2+"' and point1 <> '"+point3+"' and point2 <> '"+point1+"' and point2 <> '"+point2+"' and point2 <> '"+point3+"' and point3 <> '"+point1+"' and point3 <> '"+point2+"' and point3 <> '"+point3+"'";
  //      std::cout << querySecondGeoCmd <<  std::endl;

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point1,point2,point3 FROM Facts INNER JOIN Midpoint ON (oldFact=id) WHERE point1 <> '"+point1+"' and point1 <> '"+point2+"' and point1 <> '"+point3+"' and point2 <> '"+point1+"' and point2 <> '"+point2+"' and point2 <> '"+point3+"' and point3 <> '"+point1+"' and point3 <> '"+point2+"' and point3 <> '"+point3+"'";
  //      std::cout << querySecondGeoCmd <<  std::endl;

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0 ) {
    correctTransaction=false;
  }
  else { // At least one result for rule 3
    if (sqlite3_data_count(dbim.stmt1) != 0) {
      newPoint1 = (char*) sqlite3_column_text(dbim.stmt1, 0);
      newPoint2 = (char*) sqlite3_column_text(dbim.stmt1, 1);
      newPoint3 = (char*) sqlite3_column_text(dbim.stmt1, 2);
    }
    else {
      newPoint1 = (char*) sqlite3_column_text(dbim.stmt2, 0);
      newPoint2 = (char*) sqlite3_column_text(dbim.stmt2, 1);
      newPoint3 = (char*) sqlite3_column_text(dbim.stmt2, 2);
    }
    if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {
      // if the query result is void... it stops
      correctTransaction = false;
    }
    else {
      insertionColl = "INSERT INTO Eqratio(typeGeoCmd,point1,point2,point3,point4,point5,point6,point7,point8,newFact) VALUES ('eqratio','"+point1+"','"+point2+"','"+point2+"','"+point3+"','"+newPoint1+"','"+newPoint2+"','"+newPoint2+"','"+newPoint3+"','"+lstInsRwId+"')";

      //	  std::cout << insertionColl << std::endl;

      dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
      if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {
	correctTransaction = false;
      }
    }
  }


  //      correctTransaction=false;

  if (correctTransaction) {
    sqlite3_exec(dbim.db, "commit;", 0, 0, 0);
  }
  else { // pode acontecer que o novo facto já existe na bd
    sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);
  }
  return(dbim);
}


DBinMemory Prover::ruleD71(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6,std::string point7,std::string point8){
  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction,correctTransactionA,correctTransactionB;
  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('perp')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));
  correctTransaction=true;

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );



  querySecondGeoCmdA = "SELECT * FROM NewFact INNER JOIN Parallel ON (newFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 = '"+point3+"' and point4 = '"+point4+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);
  querySecondGeoCmdB = "SELECT * FROM Facts INNER JOIN Parallel  ON (oldFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 = '"+point3+"' and point4 = '"+point4+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);
  if (sqlite3_data_count(dbim.stmt1) != 0 || sqlite3_data_count(dbim.stmt2) != 0 ) {correctTransaction=false;}

  insertionColl = "INSERT INTO Perpendicular(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('perp','"+point1+"','"+point2+"','"+point3+"','"+point4+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}
  return(dbim);
}

DBinMemory Prover::ruleD72(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6,std::string point7,std::string point8){
  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction,correctTransactionA,correctTransactionB;
  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('para')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));
  correctTransaction=true;

  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );



  querySecondGeoCmdA = "SELECT * FROM NewFact INNER JOIN Perpendicular ON (newFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 = '"+point3+"' and point4 = '"+point4+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);
  querySecondGeoCmdB = "SELECT * FROM Facts INNER JOIN Perpendicular  ON (oldFact=id) WHERE point1 = '"+point1+"' and point2 = '"+point2+"' and point3 = '"+point3+"' and point4 = '"+point4+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);
  if (sqlite3_data_count(dbim.stmt1) != 0 || sqlite3_data_count(dbim.stmt2) != 0 ) {correctTransaction=false;}

  insertionColl = "INSERT INTO Parallel(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('para','"+point1+"','"+point2+"','"+point3+"','"+point4+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}
  return(dbim);
}

DBinMemory Prover::ruleD73Eqangle(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6,std::string point7,std::string point8){

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;
  std::string querySecondGeoCmdA,querySecondGeoCmdB,newPoint1,newPoint2,newPoint3;


  //      std::cout << "Derive new facts: " << typeGeoCmd << "---rule 3\n";

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('para')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));
  correctTransaction=true;
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );//executing the statement
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0); // reading the 1st column of the result
  querySecondGeoCmdA = "SELECT point1,point2,point3 FROM NewFact INNER JOIN Parallel ON (newFact=id) WHERE point1 = '"+point5+"' and point2 = '"+point6+"' and point3 = '"+point7+"' and point4 = '"+point8+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);
  querySecondGeoCmdB = "SELECT point1,point2,point3 FROM Facts INNER JOIN Parallel ON (oldFact=id) WHERE point1 = '"+point5+"' and point2 = '"+point6+"' and point3 = '"+point7+"' and point4 = '"+point8+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0 ) {correctTransaction=false;}
  insertionColl = "INSERT INTO Parallel(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('para','"+point1+"','"+point2+"','"+point3+"','"+point4+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}
  return(dbim);
}


DBinMemory Prover::ruleD73Para(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){
  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,newPoint3,newPoint4,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('para')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=4){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";
  newPoint2="";
  newPoint3="";
  newPoint4="";

  querySecondGeoCmdA = "SELECT point1,point2,point3,point4 FROM NewFact INNER JOIN Eqangle ON (newFact=id) WHERE point5 = '"+point1+"' and point6 = '"+point2+"' and point7 = '"+point3+"' and point8 = '"+point4+"' and point1 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"') and point2 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point1) and point3 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point1,point2) and point4 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point1,point2,point3)";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point1,point2,point3,point4 FROM Facts INNER JOIN Eqangle ON (oldFact=id) WHERE point5 = '"+point1+"' and point6 = '"+point2+"' and point7 = '"+point3+"' and point8 = '"+point4+"' and point1 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"') and point2 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point1) and point3 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point1,point2) and point4 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point1,point2,point3)";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt1, 1);newPoint3 = (char*) sqlite3_column_text(dbim.stmt1, 2);newPoint4 = (char*) sqlite3_column_text(dbim.stmt1, 3);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt2, 1);newPoint3 = (char*) sqlite3_column_text(dbim.stmt2, 2);newPoint4 = (char*) sqlite3_column_text(dbim.stmt2, 3);}

  insertionColl = "INSERT INTO Parallel(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('para','"+newPoint+"','"+newPoint2+"','"+newPoint3+"','"+newPoint4+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::ruleD74Eqangle(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6,std::string point7,std::string point8){

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;
  std::string querySecondGeoCmdA,querySecondGeoCmdB,newPoint1,newPoint2,newPoint3;


  //      std::cout << "Derive new facts: " << typeGeoCmd << "---rule 3\n";

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('perp')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));
  correctTransaction=true;
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );//executing the statement
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0); // reading the 1st column of the result
  querySecondGeoCmdA = "SELECT point1,point2,point3 FROM NewFact INNER JOIN Perpendicular ON (newFact=id) WHERE point1 = '"+point5+"' and point2 = '"+point6+"' and point3 = '"+point7+"' and point4 = '"+point8+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);
  querySecondGeoCmdB = "SELECT point1,point2,point3 FROM Facts INNER JOIN Perpendicular ON (oldFact=id) WHERE point1 = '"+point5+"' and point2 = '"+point6+"' and point3 = '"+point7+"' and point4 = '"+point8+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0 ) {correctTransaction=false;}
  insertionColl = "INSERT INTO Perpendicular(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('perp','"+point1+"','"+point2+"','"+point3+"','"+point4+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}
  return(dbim);
}

DBinMemory Prover::ruleD74Perp(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){
  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,newPoint3,newPoint4,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('perp')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=4){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";
  newPoint2="";
  newPoint3="";
  newPoint4="";

  querySecondGeoCmdA = "SELECT point1,point2,point3,point4 FROM NewFact INNER JOIN Eqangle ON (newFact=id) WHERE point5 = '"+point1+"' and point6 = '"+point2+"' and point7 = '"+point3+"' and point8 = '"+point4+"' and point1 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"') and point2 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point1) and point3 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point1,point2) and point4 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point1,point2,point3)";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point1,point2,point3,point4 FROM Facts INNER JOIN Eqangle ON (oldFact=id) WHERE point5 = '"+point1+"' and point6 = '"+point2+"' and point7 = '"+point3+"' and point8 = '"+point4+"' and point1 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"') and point2 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point1) and point3 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point1,point2) and point4 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point1,point2,point3)";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt1, 1);newPoint3 = (char*) sqlite3_column_text(dbim.stmt1, 2);newPoint4 = (char*) sqlite3_column_text(dbim.stmt1, 3);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt2, 1);newPoint3 = (char*) sqlite3_column_text(dbim.stmt2, 2);newPoint4 = (char*) sqlite3_column_text(dbim.stmt2, 3);}

  insertionColl = "INSERT INTO Perpendicular(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('perp','"+newPoint+"','"+newPoint2+"','"+newPoint3+"','"+newPoint4+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}

DBinMemory Prover::ruleD75Eqangle(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4,std::string point5,std::string point6,std::string point7,std::string point8){

  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl;
  bool correctTransaction;
  std::string querySecondGeoCmdA,querySecondGeoCmdB,newPoint1,newPoint2,newPoint3;


  //      std::cout << "Derive new facts: " << typeGeoCmd << "---rule 3\n";

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('cong')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));
  correctTransaction=true;
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );//executing the statement
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0); // reading the 1st column of the result
  querySecondGeoCmdA = "SELECT point1,point2,point3 FROM NewFact INNER JOIN Cong ON (newFact=id) WHERE point1 = '"+point5+"' and point2 = '"+point6+"' and point3 = '"+point7+"' and point4 = '"+point8+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);
  querySecondGeoCmdB = "SELECT point1,point2,point3 FROM Facts INNER JOIN Cong ON (oldFact=id) WHERE point1 = '"+point5+"' and point2 = '"+point6+"' and point3 = '"+point7+"' and point4 = '"+point8+"'";
  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0 ) {correctTransaction=false;}
  insertionColl = "INSERT INTO Cong(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('cong','"+point1+"','"+point2+"','"+point3+"','"+point4+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}
  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}
  return(dbim);
}

DBinMemory Prover::ruleD75Cong(DBinMemory dbim,std::string point1,std::string point2,std::string point3,std::string point4){
  std::string insertNewFact,lastInsertedRowId,lstInsRwId,insertionColl,newPoint,newPoint2,newPoint3,newPoint4,querySecondGeoCmdA,querySecondGeoCmdB;
  bool correctTransaction;

  insertNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('cong')";
  lastInsertedRowId = "SELECT last_insert_rowid()";
  sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

  correctTransaction=true;

  std::set<std::string> uniquepoints={point1,point2,point3,point4};
  if(uniquepoints.size()!=4){correctTransaction = false;}


  dbim.rc = sqlite3_prepare_v2(dbim.db, insertNewFact.c_str() , insertNewFact.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);
  sqlite3_step( dbim.stmt );
  lstInsRwId = (char*) sqlite3_column_text(dbim.stmt,0);

  newPoint="";
  newPoint2="";
  newPoint3="";
  newPoint4="";

  querySecondGeoCmdA = "SELECT point1,point2,point3,point4 FROM NewFact INNER JOIN Eqratio ON (newFact=id) WHERE point5 = '"+point1+"' and point6 = '"+point2+"' and point7 = '"+point3+"' and point8 = '"+point4+"' and point1 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"') and point2 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point1) and point3 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point1,point2) and point4 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point1,point2,point3)";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdA.c_str(),querySecondGeoCmdA.size(), &(dbim.stmt1), NULL);
  sqlite3_step(dbim.stmt1);

  querySecondGeoCmdB = "SELECT point1,point2,point3,point4 FROM Facts INNER JOIN Eqratio ON (oldFact=id) WHERE point5 = '"+point1+"' and point6 = '"+point2+"' and point7 = '"+point3+"' and point8 = '"+point4+"' and point1 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"') and point2 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point1) and point3 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point1,point2) and point4 not in ('"+point1+"','"+point2+"','"+point3+"','"+point4+"',point1,point2,point3)";

  dbim.rc = sqlite3_prepare_v2(dbim.db,querySecondGeoCmdB.c_str(),querySecondGeoCmdB.size(), &(dbim.stmt2), NULL);
  sqlite3_step(dbim.stmt2);

  if (sqlite3_data_count(dbim.stmt1) == 0 && sqlite3_data_count(dbim.stmt2) == 0) {correctTransaction=false;}
  else if (sqlite3_data_count(dbim.stmt1) != 0) {newPoint = (char*) sqlite3_column_text(dbim.stmt1, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt1, 1);newPoint3 = (char*) sqlite3_column_text(dbim.stmt1, 2);newPoint4 = (char*) sqlite3_column_text(dbim.stmt1, 3);}
  else {newPoint = (char*) sqlite3_column_text(dbim.stmt2, 0);newPoint2 = (char*) sqlite3_column_text(dbim.stmt2, 1);newPoint3 = (char*) sqlite3_column_text(dbim.stmt2, 2);newPoint4 = (char*) sqlite3_column_text(dbim.stmt2, 3);}

  insertionColl = "INSERT INTO Cong(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('cong','"+newPoint+"','"+newPoint2+"','"+newPoint3+"','"+newPoint4+"','"+lstInsRwId+"')";
  dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
  if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {correctTransaction = false;}

  if (correctTransaction) {sqlite3_exec(dbim.db, "commit;", 0, 0, 0);}
  else {sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);}

  return(dbim);
}


DBinMemory Prover::fixedPoint(DBinMemory dbim) {

  // Fixed Point cycle

  // Pick an element from the new facts database
  std::string newFact,typeGeoCmd,newFactId,deleteNewFact,insertFact,updateGeoCmd;
  std::string toDeriveGeoCmd,insertNewFact,querySecondGeoCmdA,querySecondGeoCmdB;
  std::string point1,point2,point3,point4,point5,point6,point7,point8,newPoint3;

  bool correctTransaction;
  std::string lastInsertedRowId,lstInsRwId,insertionColl,insertionNewFact;

  // set foreign keys ON
  sqlite3_prepare_v2(dbim.db, "PRAGMA foreign_keys = ON", -1, &(dbim.stmt), NULL);
  sqlite3_step(dbim.stmt);

  newFact = "SELECT id,typeGeoCmd FROM NewFact  LIMIT 1";
  dbim.rc = sqlite3_prepare_v2(dbim.db, newFact.c_str() , newFact.size(), &(dbim.stmt), NULL);
  // enquanto esta consulta é bem sucedidada faz
  //  rc = sqlite3_step(stmt);

  //  std::cout << "fixed point cycle up to no new facts exist to explore\n";
  while (sqlite3_step(dbim.stmt) != SQLITE_DONE) { //
    newFactId = (char*) sqlite3_column_text(dbim.stmt, 0);
    typeGeoCmd = (char*) sqlite3_column_text(dbim.stmt, 1);



	switch (dbim.geoCmds[typeGeoCmd]) {
    case 1: // Collinear command
      // save the geometric command for the derivation of new facts
      toDeriveGeoCmd = "SELECT point1,point2,point3 FROM Collinear WHERE newFact = "+newFactId;
      //      std::cout << toDeriveGeoCmd << std::endl;
      dbim.rc = sqlite3_prepare_v2(dbim.db,toDeriveGeoCmd.c_str(),toDeriveGeoCmd.size(),&(dbim.stmt),NULL);
      sqlite3_step(dbim.stmt);
      point1 = (char*) sqlite3_column_text(dbim.stmt, 0);
      point2 = (char*) sqlite3_column_text(dbim.stmt, 1);
      point3 = (char*) sqlite3_column_text(dbim.stmt, 2);
      //      std::cout << "coll(" << point1 << ",";
      //      std::cout << point2 << ",";
      //      std::cout << point3 << ")" << std::endl;
      // insert a new fact in table Facts
      insertFact = "INSERT INTO Facts (id,typeGeoCmd) VALUES ("+newFactId+",'"+typeGeoCmd+"')";
      dbim.rc = sqlite3_prepare_v2(dbim.db,insertFact.c_str(),insertFact.size(),&(dbim.stmt),NULL);
      sqlite3_step( dbim.stmt );
      //      std::cout << insertFact << std::endl;
      // update table collinear with the Facts foreign key
      updateGeoCmd = "UPDATE Collinear SET oldFact = "+newFactId+" WHERE newFact = "+newFactId;
      dbim.rc = sqlite3_prepare_v2(dbim.db,updateGeoCmd.c_str(),updateGeoCmd.size(),&(dbim.stmt),NULL);
      sqlite3_step( dbim.stmt );
      //      std::cout << updateGeoCmd << std::endl;
      // delete that line of table NewFacts
      deleteNewFact = "DELETE FROM NewFact where id = "+newFactId;
      //      std::cout << deleteNewFact << std::endl;
      dbim.rc = sqlite3_prepare_v2(dbim.db, deleteNewFact.c_str() , deleteNewFact.size(), &(dbim.stmt), NULL);
      sqlite3_step( dbim.stmt );
      break;
    case 2: // Parallel
      // save the geometric command for the derivation of new facts
      toDeriveGeoCmd = "SELECT point1,point2,point3,point4 FROM Parallel WHERE newFact = "+newFactId;
      //      std::cout << toDeriveGeoCmd << std::endl;
      dbim.rc = sqlite3_prepare_v2(dbim.db,toDeriveGeoCmd.c_str(),toDeriveGeoCmd.size(),&(dbim.stmt),NULL);
      sqlite3_step(dbim.stmt);

      point1 = (char*) sqlite3_column_text(dbim.stmt, 0);
      point2 = (char*) sqlite3_column_text(dbim.stmt, 1);
      point3 = (char*) sqlite3_column_text(dbim.stmt, 2);
      point4 = (char*) sqlite3_column_text(dbim.stmt, 3);
      //      std::cout << "coll(" << point1 << ",";
      //      std::cout << point2 << ",";
      //      std::cout << point3 << ")" << std::endl;
      // insert a new fact in table Facts
      insertFact = "INSERT INTO Facts (id,typeGeoCmd) VALUES ("+newFactId+",'"+typeGeoCmd+"')";
      dbim.rc = sqlite3_prepare_v2(dbim.db,insertFact.c_str(),insertFact.size(),&(dbim.stmt),NULL);
      sqlite3_step( dbim.stmt );
      //      std::cout << insertFact << std::endl;
      // update table collinear with the Facts foreign key
      updateGeoCmd = "UPDATE Parallel SET oldFact = "+newFactId+" WHERE newFact = "+newFactId;
      dbim.rc = sqlite3_prepare_v2(dbim.db,updateGeoCmd.c_str(),updateGeoCmd.size(),&(dbim.stmt),NULL);
      sqlite3_step( dbim.stmt );
      //      std::cout << updateGeoCmd << std::endl;
      // delete that line of table NewFacts
      deleteNewFact = "DELETE FROM NewFact where id = "+newFactId;
      //      std::cout << deleteNewFact << std::endl;
      dbim.rc = sqlite3_prepare_v2(dbim.db, deleteNewFact.c_str() , deleteNewFact.size(), &(dbim.stmt), NULL);
      sqlite3_step( dbim.stmt );
      break;
    case 3: // Perpendicular
      toDeriveGeoCmd = "SELECT point1,point2,point3,point4 FROM Perpendicular WHERE newFact = "+newFactId;
      //      std::cout << toDeriveGeoCmd << std::endl;
      dbim.rc = sqlite3_prepare_v2(dbim.db,toDeriveGeoCmd.c_str(),toDeriveGeoCmd.size(),&(dbim.stmt),NULL);
      sqlite3_step(dbim.stmt);
      point1 = (char*) sqlite3_column_text(dbim.stmt, 0);
      point2 = (char*) sqlite3_column_text(dbim.stmt, 1);
      point3 = (char*) sqlite3_column_text(dbim.stmt, 2);
      point4 = (char*) sqlite3_column_text(dbim.stmt, 3);
      //      std::cout << "Perp(" << point1 << ",";
      //      std::cout << point2 << ",";
      //      std::cout << point3 << ",";
      //      std::cout << point4 << ")" << std::endl;
      // insert a new fact in table Facts
      insertFact = "INSERT INTO Facts (id,typeGeoCmd) VALUES ("+newFactId+",'"+typeGeoCmd+"')";
      dbim.rc = sqlite3_prepare_v2(dbim.db,insertFact.c_str(),insertFact.size(),&(dbim.stmt),NULL);
      sqlite3_step( dbim.stmt );
      //      std::cout << insertFact << std::endl;
      // update table collinear with the Facts foreign key
      updateGeoCmd = "UPDATE Perpendicular SET oldFact = "+newFactId+" WHERE newFact = "+newFactId;
      dbim.rc = sqlite3_prepare_v2(dbim.db,updateGeoCmd.c_str(),updateGeoCmd.size(),&(dbim.stmt),NULL);
      sqlite3_step( dbim.stmt );
      // delete that line of table NewFacts
      deleteNewFact = "DELETE FROM NewFact where id = "+newFactId;
      //      std::cout << deleteNewFact << std::endl;
      dbim.rc = sqlite3_prepare_v2(dbim.db, deleteNewFact.c_str() , deleteNewFact.size(), &(dbim.stmt), NULL);
      sqlite3_step( dbim.stmt );
      break;
    case 4: // Midpoint
     toDeriveGeoCmd = "SELECT point1,point2,point3 FROM Midpoint WHERE newFact = "+newFactId;
      dbim.rc = sqlite3_prepare_v2(dbim.db,toDeriveGeoCmd.c_str(),toDeriveGeoCmd.size(),&(dbim.stmt),NULL);
      sqlite3_step(dbim.stmt);
      point1 = (char*) sqlite3_column_text(dbim.stmt, 0);
      point2 = (char*) sqlite3_column_text(dbim.stmt, 1);
      point3 = (char*) sqlite3_column_text(dbim.stmt, 2);
      insertFact = "INSERT INTO Facts (id,typeGeoCmd) VALUES ("+newFactId+",'"+typeGeoCmd+"')";
      dbim.rc = sqlite3_prepare_v2(dbim.db,insertFact.c_str(),insertFact.size(),&(dbim.stmt),NULL);
      sqlite3_step( dbim.stmt );
      updateGeoCmd = "UPDATE Midpoint SET oldFact = "+newFactId+" WHERE newFact = "+newFactId;
      dbim.rc = sqlite3_prepare_v2(dbim.db,updateGeoCmd.c_str(),updateGeoCmd.size(),&(dbim.stmt),NULL);
      sqlite3_step( dbim.stmt );
      deleteNewFact = "DELETE FROM NewFact where id = "+newFactId;
      dbim.rc = sqlite3_prepare_v2(dbim.db, deleteNewFact.c_str() , deleteNewFact.size(), &(dbim.stmt), NULL);
      sqlite3_step( dbim.stmt );
      break;
    case 5:
     toDeriveGeoCmd = "SELECT point1,point2,point3,point4 FROM Circle WHERE newFact = "+newFactId;
      dbim.rc = sqlite3_prepare_v2(dbim.db,toDeriveGeoCmd.c_str(),toDeriveGeoCmd.size(),&(dbim.stmt),NULL);
      sqlite3_step(dbim.stmt);
      point1 = (char*) sqlite3_column_text(dbim.stmt, 0);
      point2 = (char*) sqlite3_column_text(dbim.stmt, 1);
      point3 = (char*) sqlite3_column_text(dbim.stmt, 2);
      point4 = (char*) sqlite3_column_text(dbim.stmt, 3);
      insertFact = "INSERT INTO Facts (id,typeGeoCmd) VALUES ("+newFactId+",'"+typeGeoCmd+"')";
      dbim.rc = sqlite3_prepare_v2(dbim.db,insertFact.c_str(),insertFact.size(),&(dbim.stmt),NULL);
      sqlite3_step( dbim.stmt );
      updateGeoCmd = "UPDATE Circle SET oldFact = "+newFactId+" WHERE newFact = "+newFactId;
      dbim.rc = sqlite3_prepare_v2(dbim.db,updateGeoCmd.c_str(),updateGeoCmd.size(),&(dbim.stmt),NULL);
      sqlite3_step( dbim.stmt );
      deleteNewFact = "DELETE FROM NewFact where id = "+newFactId;
      dbim.rc = sqlite3_prepare_v2(dbim.db, deleteNewFact.c_str() , deleteNewFact.size(), &(dbim.stmt), NULL);
      sqlite3_step( dbim.stmt );
      break;
    case 6:
     toDeriveGeoCmd = "SELECT point1,point2,point3,point4 FROM Cyclic WHERE newFact = "+newFactId;
      dbim.rc = sqlite3_prepare_v2(dbim.db,toDeriveGeoCmd.c_str(),toDeriveGeoCmd.size(),&(dbim.stmt),NULL);
      sqlite3_step(dbim.stmt);
      point1 = (char*) sqlite3_column_text(dbim.stmt, 0);
      point2 = (char*) sqlite3_column_text(dbim.stmt, 1);
      point3 = (char*) sqlite3_column_text(dbim.stmt, 2);
      point4 = (char*) sqlite3_column_text(dbim.stmt, 3);
      insertFact = "INSERT INTO Facts (id,typeGeoCmd) VALUES ("+newFactId+",'"+typeGeoCmd+"')";
      dbim.rc = sqlite3_prepare_v2(dbim.db,insertFact.c_str(),insertFact.size(),&(dbim.stmt),NULL);
      sqlite3_step( dbim.stmt );
      updateGeoCmd = "UPDATE Cyclic SET oldFact = "+newFactId+" WHERE newFact = "+newFactId;
      dbim.rc = sqlite3_prepare_v2(dbim.db,updateGeoCmd.c_str(),updateGeoCmd.size(),&(dbim.stmt),NULL);
      sqlite3_step( dbim.stmt );
      deleteNewFact = "DELETE FROM NewFact where id = "+newFactId;
      dbim.rc = sqlite3_prepare_v2(dbim.db, deleteNewFact.c_str() , deleteNewFact.size(), &(dbim.stmt), NULL);
      sqlite3_step( dbim.stmt );
      break;
    case 7:
     toDeriveGeoCmd = "SELECT point1,point2,point3,point4,point5,point6,point7,point8 FROM Eqangle WHERE newFact = "+newFactId;
      dbim.rc = sqlite3_prepare_v2(dbim.db,toDeriveGeoCmd.c_str(),toDeriveGeoCmd.size(),&(dbim.stmt),NULL);
      sqlite3_step(dbim.stmt);
      point1 = (char*) sqlite3_column_text(dbim.stmt, 0);
      point2 = (char*) sqlite3_column_text(dbim.stmt, 1);
      point3 = (char*) sqlite3_column_text(dbim.stmt, 2);
      point4 = (char*) sqlite3_column_text(dbim.stmt, 3);
      point5 = (char*) sqlite3_column_text(dbim.stmt, 4);
      point6 = (char*) sqlite3_column_text(dbim.stmt, 5);
      point7 = (char*) sqlite3_column_text(dbim.stmt, 6);
      point8 = (char*) sqlite3_column_text(dbim.stmt, 7);
      insertFact = "INSERT INTO Facts (id,typeGeoCmd) VALUES ("+newFactId+",'"+typeGeoCmd+"')";
      dbim.rc = sqlite3_prepare_v2(dbim.db,insertFact.c_str(),insertFact.size(),&(dbim.stmt),NULL);
      sqlite3_step( dbim.stmt );
      updateGeoCmd = "UPDATE Eqangle SET oldFact = "+newFactId+" WHERE newFact = "+newFactId;
      dbim.rc = sqlite3_prepare_v2(dbim.db,updateGeoCmd.c_str(),updateGeoCmd.size(),&(dbim.stmt),NULL);
      sqlite3_step( dbim.stmt );
      deleteNewFact = "DELETE FROM NewFact where id = "+newFactId;
      dbim.rc = sqlite3_prepare_v2(dbim.db, deleteNewFact.c_str() , deleteNewFact.size(), &(dbim.stmt), NULL);
      sqlite3_step( dbim.stmt );
      break;
    case 8:
     toDeriveGeoCmd = "SELECT point1,point2,point3,point4 FROM Cong WHERE newFact = "+newFactId;
      dbim.rc = sqlite3_prepare_v2(dbim.db,toDeriveGeoCmd.c_str(),toDeriveGeoCmd.size(),&(dbim.stmt),NULL);
      sqlite3_step(dbim.stmt);

      point1 = (char*) sqlite3_column_text(dbim.stmt, 0);
      point2 = (char*) sqlite3_column_text(dbim.stmt, 1);
      point3 = (char*) sqlite3_column_text(dbim.stmt, 2);
      point4 = (char*) sqlite3_column_text(dbim.stmt, 3);
      insertFact = "INSERT INTO Facts (id,typeGeoCmd) VALUES ("+newFactId+",'"+typeGeoCmd+"')";
      dbim.rc = sqlite3_prepare_v2(dbim.db,insertFact.c_str(),insertFact.size(),&(dbim.stmt),NULL);
      sqlite3_step( dbim.stmt );
      updateGeoCmd = "UPDATE Cong SET oldFact = "+newFactId+" WHERE newFact = "+newFactId;
      dbim.rc = sqlite3_prepare_v2(dbim.db,updateGeoCmd.c_str(),updateGeoCmd.size(),&(dbim.stmt),NULL);
      sqlite3_step( dbim.stmt );
      deleteNewFact = "DELETE FROM NewFact where id = "+newFactId;
      dbim.rc = sqlite3_prepare_v2(dbim.db, deleteNewFact.c_str() , deleteNewFact.size(), &(dbim.stmt), NULL);
      sqlite3_step( dbim.stmt );
      break;
    case 9:
     toDeriveGeoCmd = "SELECT point1,point2,point3,point4,point5,point6,point7,point8 FROM Eqratio WHERE newFact = "+newFactId;
      dbim.rc = sqlite3_prepare_v2(dbim.db,toDeriveGeoCmd.c_str(),toDeriveGeoCmd.size(),&(dbim.stmt),NULL);
      sqlite3_step(dbim.stmt);
      point1 = (char*) sqlite3_column_text(dbim.stmt, 0);
      point2 = (char*) sqlite3_column_text(dbim.stmt, 1);
      point3 = (char*) sqlite3_column_text(dbim.stmt, 2);
      point4 = (char*) sqlite3_column_text(dbim.stmt, 3);
      point5 = (char*) sqlite3_column_text(dbim.stmt, 4);
      point6 = (char*) sqlite3_column_text(dbim.stmt, 5);
      point7 = (char*) sqlite3_column_text(dbim.stmt, 6);
      point8 = (char*) sqlite3_column_text(dbim.stmt, 7);
      insertFact = "INSERT INTO Facts (id,typeGeoCmd) VALUES ("+newFactId+",'"+typeGeoCmd+"')";
      dbim.rc = sqlite3_prepare_v2(dbim.db,insertFact.c_str(),insertFact.size(),&(dbim.stmt),NULL);
      sqlite3_step( dbim.stmt );
      updateGeoCmd = "UPDATE Eqratio SET oldFact = "+newFactId+" WHERE newFact = "+newFactId;
      dbim.rc = sqlite3_prepare_v2(dbim.db,updateGeoCmd.c_str(),updateGeoCmd.size(),&(dbim.stmt),NULL);
      sqlite3_step( dbim.stmt );
      deleteNewFact = "DELETE FROM NewFact where id = "+newFactId;
      dbim.rc = sqlite3_prepare_v2(dbim.db, deleteNewFact.c_str() , deleteNewFact.size(), &(dbim.stmt), NULL);
      sqlite3_step( dbim.stmt );
      break;
    case 10:
     toDeriveGeoCmd = "SELECT point1,point2,point3,point4,point5,point6 FROM Simtri WHERE newFact = "+newFactId;
      dbim.rc = sqlite3_prepare_v2(dbim.db,toDeriveGeoCmd.c_str(),toDeriveGeoCmd.size(),&(dbim.stmt),NULL);
      sqlite3_step(dbim.stmt);
      point1 = (char*) sqlite3_column_text(dbim.stmt, 0);
      point2 = (char*) sqlite3_column_text(dbim.stmt, 1);
      point3 = (char*) sqlite3_column_text(dbim.stmt, 2);
      point4 = (char*) sqlite3_column_text(dbim.stmt, 3);
      point5 = (char*) sqlite3_column_text(dbim.stmt, 4);
      point6 = (char*) sqlite3_column_text(dbim.stmt, 5);
      insertFact = "INSERT INTO Facts (id,typeGeoCmd) VALUES ("+newFactId+",'"+typeGeoCmd+"')";
      dbim.rc = sqlite3_prepare_v2(dbim.db,insertFact.c_str(),insertFact.size(),&(dbim.stmt),NULL);
      sqlite3_step( dbim.stmt );
      updateGeoCmd = "UPDATE Simtri SET oldFact = "+newFactId+" WHERE newFact = "+newFactId;
      dbim.rc = sqlite3_prepare_v2(dbim.db,updateGeoCmd.c_str(),updateGeoCmd.size(),&(dbim.stmt),NULL);
      sqlite3_step( dbim.stmt );
      deleteNewFact = "DELETE FROM NewFact where id = "+newFactId;
      dbim.rc = sqlite3_prepare_v2(dbim.db, deleteNewFact.c_str() , deleteNewFact.size(), &(dbim.stmt), NULL);
      sqlite3_step( dbim.stmt );
      break;
    case 11:
      toDeriveGeoCmd = "SELECT point1,point2,point3,point4,point5,point6 FROM Contri WHERE newFact = "+newFactId;
      dbim.rc = sqlite3_prepare_v2(dbim.db,toDeriveGeoCmd.c_str(),toDeriveGeoCmd.size(),&(dbim.stmt),NULL);
      sqlite3_step(dbim.stmt);
      point1 = (char*) sqlite3_column_text(dbim.stmt, 0);
      point2 = (char*) sqlite3_column_text(dbim.stmt, 1);
      point3 = (char*) sqlite3_column_text(dbim.stmt, 2);
      point4 = (char*) sqlite3_column_text(dbim.stmt, 3);
      point5 = (char*) sqlite3_column_text(dbim.stmt, 4);
      point6 = (char*) sqlite3_column_text(dbim.stmt, 5);
      insertFact = "INSERT INTO Facts (id,typeGeoCmd) VALUES ("+newFactId+",'"+typeGeoCmd+"')";
      dbim.rc = sqlite3_prepare_v2(dbim.db,insertFact.c_str(),insertFact.size(),&(dbim.stmt),NULL);
      sqlite3_step( dbim.stmt );
      updateGeoCmd = "UPDATE Contri SET oldFact = "+newFactId+" WHERE newFact = "+newFactId;
      dbim.rc = sqlite3_prepare_v2(dbim.db,updateGeoCmd.c_str(),updateGeoCmd.size(),&(dbim.stmt),NULL);
      sqlite3_step( dbim.stmt );
      deleteNewFact = "DELETE FROM NewFact where id = "+newFactId;
      dbim.rc = sqlite3_prepare_v2(dbim.db, deleteNewFact.c_str() , deleteNewFact.size(), &(dbim.stmt), NULL);
      sqlite3_step( dbim.stmt );
      break;
    default:
      // erro, comando não implementado
      std::cout << "Error: <codigo de erro>\n";
    }
    /*
     * Derive new facts
     * -- from the 'newFact' that has been selected, try to prove a new fact
     *
     */
    switch (dbim.geoCmds[typeGeoCmd]) {
    case 1:  // Collinear command
      dbim = ruleD1(dbim,point1,point2,point3);
      dbim = ruleD2(dbim,point1,point2,point3);
      dbim = ruleD3(dbim,point1,point2,point3);

  	  dbim = ruleD45Coll(dbim,point1,point2,point3);
  	  dbim = ruleD51(dbim,point1,point2,point3);
  	  dbim = ruleD53Coll(dbim,point1,point2,point3);
  	  dbim = ruleD65Coll(dbim,point1,point2,point3);
  	  dbim = ruleD67Coll(dbim,point1,point2,point3);
      break;

    case 2: // Parallel
      dbim = ruleD4(dbim,point1,point2,point3,point4);
      dbim = ruleD5(dbim,point1,point2,point3,point4);
      dbim = ruleD40(dbim,point1,point2,point3,point4);
      dbim = ruleD66(dbim,point1,point2,point3,point4);

      dbim = ruleD6(dbim,point1,point2,point3,point4);
      dbim = ruleD10Para(dbim,point1,point2,point3,point4);
      dbim = ruleD45Para(dbim,point1,point2,point3,point4);
      dbim = ruleD54Para(dbim,point1,point2,point3,point4);
      dbim = ruleD64Para(dbim,point1,point2,point3,point4);
      dbim = ruleD65Para(dbim,point1,point2,point3,point4);
      dbim = ruleD73Para(dbim,point1,point2,point3,point4);
      break;

    case 3: // Perpendicular
      dbim = ruleD7(dbim,point1,point2,point3,point4);
      dbim = ruleD8(dbim,point1,point2,point3,point4);

      dbim = ruleD9(dbim,point1,point2,point3,point4);
      dbim = ruleD10Perp(dbim,point1,point2,point3,point4);
      dbim = ruleD48Perp(dbim,point1,point2,point3,point4);
      dbim = ruleD52Perp(dbim,point1,point2,point3,point4);
      dbim = ruleD55Perp(dbim,point1,point2,point3,point4);
      dbim = ruleD74Perp(dbim,point1,point2,point3,point4);
      break;

    case 4: // Midpoint
      dbim = ruleD11(dbim,point1,point2,point3);
      dbim = ruleD68(dbim,point1,point2,point3);
      dbim = ruleD69(dbim,point1,point2,point3);

      dbim = ruleD44(dbim,point1,point2,point3);
      dbim = ruleD45Midp(dbim,point1,point2,point3);
      dbim = ruleD50Midp(dbim,point1,point2,point3);
      dbim = ruleD52Midp(dbim,point1,point2,point3);
      dbim = ruleD55Midp(dbim,point1,point2,point3);
      dbim = ruleD63(dbim,point1,point2,point3);
      dbim = ruleD64Midp(dbim,point1,point2,point3);
      dbim = ruleD70(dbim,point1,point2,point3);
      break;

    case 5: //Circle
      dbim = ruleD48Circle(dbim,point1,point2,point3,point4);
      dbim = ruleD49Circle(dbim,point1,point2,point3,point4);
      dbim = ruleD50Circle(dbim,point1,point2,point3,point4);
  	  dbim = ruleD53Circle(dbim,point1,point2,point3,point4);


      break;

    case 6: //Cyclic
      dbim = ruleD14(dbim,point1,point2,point3,point4);
      dbim = ruleD15(dbim,point1,point2,point3,point4);
      dbim = ruleD16(dbim,point1,point2,point3,point4);
      dbim = ruleD41(dbim,point1,point2,point3,point4);

      dbim = ruleD17(dbim,point1,point2,point3,point4);
      dbim = ruleD57Circle(dbim,point1,point2,point3,point4);
      dbim = ruleD54Cyclic(dbim,point1,point2,point3,point4);
      break;

    case 7: //Eqangle
      dbim = ruleD18(dbim,point1,point2,point3,point4,point5,point6,point7,point8);
      dbim = ruleD19(dbim,point1,point2,point3,point4,point5,point6,point7,point8);
      dbim = ruleD20(dbim,point1,point2,point3,point4,point5,point6,point7,point8);
      dbim = ruleD21(dbim,point1,point2,point3,point4,point5,point6,point7,point8);
      dbim = ruleD39(dbim,point1,point2,point3,point4,point5,point6,point7,point8);

      dbim = ruleD22(dbim,point1,point2,point3,point4,point5,point6,point7,point8);
      dbim = ruleD42(dbim,point1,point2,point3,point4,point5,point6,point7,point8);
	  dbim = ruleD43Eqangle(dbim,point1,point2,point3,point4,point5,point6,point7,point8);
      dbim = ruleD47(dbim,point1,point2,point3,point4,point5,point6,point7,point8);
	  dbim = ruleD49Eqangle(dbim,point1,point2,point3,point4,point5,point6,point7,point8);
      dbim = ruleD58A(dbim,point1,point2,point3,point4,point5,point6,point7,point8);
	  dbim = ruleD58B(dbim,point1,point2,point3,point4,point5,point6,point7,point8);
      dbim = ruleD71(dbim,point1,point2,point3,point4,point5,point6,point7,point8);
      dbim = ruleD72(dbim,point1,point2,point3,point4,point5,point6,point7,point8);
      dbim = ruleD73Eqangle(dbim,point1,point2,point3,point4,point5,point6,point7,point8);
      dbim = ruleD74Eqangle(dbim,point1,point2,point3,point4,point5,point6,point7,point8);
      break;

    case 8: //Cong
      dbim = ruleD23(dbim,point1,point2,point3,point4);
      dbim = ruleD24(dbim,point1,point2,point3,point4);
      dbim = ruleD46(dbim,point1,point2,point3,point4);

      dbim = ruleD12(dbim,point1,point2,point3,point4);
      dbim = ruleD13(dbim,point1,point2,point3,point4);
      dbim = ruleD25(dbim,point1,point2,point3,point4);
      dbim = ruleD56(dbim,point1,point2,point3,point4);
      dbim = ruleD57Cong(dbim,point1,point2,point3,point4);
      dbim = ruleD67Cong(dbim,point1,point2,point3,point4);
      dbim = ruleD75Cong(dbim,point1,point2,point3,point4);
      break;

    case 9: //Eqratio
      dbim = ruleD26(dbim,point1,point2,point3,point4,point5,point6,point7,point8);
      dbim = ruleD27(dbim,point1,point2,point3,point4,point5,point6,point7,point8);
      dbim = ruleD28(dbim,point1,point2,point3,point4,point5,point6,point7,point8);
      dbim = ruleD29(dbim,point1,point2,point3,point4,point5,point6,point7,point8);

      dbim = ruleD30(dbim,point1,point2,point3,point4,point5,point6,point7,point8);
      dbim = ruleD75Eqangle(dbim,point1,point2,point3,point4,point5,point6,point7,point8);
      break;

    case 10: //Simtri
      dbim = ruleD31(dbim,point1,point2,point3,point4,point5,point6);
      dbim = ruleD32(dbim,point1,point2,point3,point4,point5,point6);
      dbim = ruleD33(dbim,point1,point2,point3,point4,point5,point6);

      dbim = ruleD34(dbim,point1,point2,point3,point4,point5,point6);
      dbim = ruleD59(dbim,point1,point2,point3,point4,point5,point6);
      dbim = ruleD60(dbim,point1,point2,point3,point4,point5,point6);
      dbim = ruleD61(dbim,point1,point2,point3,point4,point5,point6);
      break;

    case 11: //Contri
      dbim = ruleD35(dbim,point1,point2,point3,point4,point5,point6);
      dbim = ruleD36(dbim,point1,point2,point3,point4,point5,point6);
      dbim = ruleD37(dbim,point1,point2,point3,point4,point5,point6);
      dbim = ruleD62(dbim,point1,point2,point3,point4,point5,point6);

      dbim = ruleD38(dbim,point1,point2,point3,point4,point5,point6);
      break;
    default:
      // no new fact, something wrong
      std::cout << "ERROR: <codigo_erro>\n";
    }

    // new query to restart the cycle
    newFact = "SELECT id,typeGeoCmd FROM NewFact ORDER BY typeGeoCmd LIMIT 1";
    dbim.rc = sqlite3_prepare_v2(dbim.db, newFact.c_str() , newFact.size(), &(dbim.stmt), NULL);
  }
  return(dbim);
}

bool Prover::proved(DBinMemory dbim) {

  std::string proving;
  // CONJECTURE  coll(A,B,D) - in table Consequent

  /*
   * I'm assuming one single consequent
   */

  std::string sqlConsequent;
  std::string idConsequent,typeGeoCmd;

  sqlConsequent = "SELECT id,typeGeoCmd FROM Consequent";
  dbim.rc = sqlite3_prepare_v2(dbim.db, sqlConsequent.c_str() , sqlConsequent.size(), &(dbim.stmt), NULL);
  sqlite3_step(dbim.stmt);
  idConsequent = (char*) sqlite3_column_text(dbim.stmt, 0);
  typeGeoCmd = (char*) sqlite3_column_text(dbim.stmt, 1);
  //  std::cout << "typeGeoCmd: " << typeGeoCmd << "\n";
  switch (dbim.geoCmds[typeGeoCmd]) {
  case 1:  // coll

    //    std::cout << "Caso Coll \n";
    proving = "SELECT * FROM Consequent INNER JOIN Collinear USING(typeGeoCmd) WHERE Consequent.point1 = Collinear.point1 and Consequent.point2 = Collinear.point2 and Consequent.point3 = Collinear.point3";

    dbim.rc = sqlite3_prepare_v2(dbim.db,proving.c_str(),proving.size(), &(dbim.stmt), NULL);
    sqlite3_step(dbim.stmt);

    if (sqlite3_data_count(dbim.stmt) == 0) {
      return false;
    }
    else {
      return true;
    }
    break;
  case 2: // para
 proving = "SELECT * FROM Consequent INNER JOIN Parallel USING(typeGeoCmd) WHERE Consequent.point1 = Parallel.point1 and Consequent.point2 = Parallel.point2 and Consequent.point3 = Parallel.point3 and Consequent.point4 = Parallel.point4";

    dbim.rc = sqlite3_prepare_v2(dbim.db,proving.c_str(),proving.size(), &(dbim.stmt), NULL);
    sqlite3_step(dbim.stmt);

    if (sqlite3_data_count(dbim.stmt) == 0) {
      return false;
    }
    else {
      return true;
    }
    break;
  case 3: // perp
 proving = "SELECT * FROM Consequent INNER JOIN Perpendicular USING(typeGeoCmd) WHERE Consequent.point1 = Perpendicular.point1 and Consequent.point2 = Perpendicular.point2 and Consequent.point3 = Perpendicular.point3 and Consequent.point4 = Perpendicular.point4";

    dbim.rc = sqlite3_prepare_v2(dbim.db,proving.c_str(),proving.size(), &(dbim.stmt), NULL);
    sqlite3_step(dbim.stmt);

    if (sqlite3_data_count(dbim.stmt) == 0) {
      return false;
    }
    else {
      return true;
    }
    break;
  case 4: // midpoint
 proving = "SELECT * FROM Consequent INNER JOIN Midpoint USING(typeGeoCmd) WHERE Consequent.point1 = Midpoint.point1 and Consequent.point2 = Midpoint.point2 and Consequent.point3 = Midpoint.point3";

    dbim.rc = sqlite3_prepare_v2(dbim.db,proving.c_str(),proving.size(), &(dbim.stmt), NULL);
    sqlite3_step(dbim.stmt);

    if (sqlite3_data_count(dbim.stmt) == 0) {
      return false;
    }
    else {
      return true;
    }
    break;
case 5: // circle
    proving = "SELECT * FROM Consequent INNER JOIN Circle USING(typeGeoCmd) WHERE Consequent.point1 = Circle.point1 and Consequent.point2 = Circle.point2 and Consequent.point3 = Circle.point3 and Consequent.point4 = Circle.point4";

    dbim.rc = sqlite3_prepare_v2(dbim.db,proving.c_str(),proving.size(), &(dbim.stmt), NULL);
    sqlite3_step(dbim.stmt);

    if (sqlite3_data_count(dbim.stmt) == 0) {
      return false;
    }
    else {
      return true;
    }
    break;
case 6: // cyclic
    proving = "SELECT * FROM Consequent INNER JOIN Cyclic USING(typeGeoCmd) WHERE Consequent.point1 = Cyclic.point1 and Consequent.point2 = Cyclic.point2 and Consequent.point3 = Cyclic.point3 and Consequent.point4 = Cyclic.point4";

    dbim.rc = sqlite3_prepare_v2(dbim.db,proving.c_str(),proving.size(), &(dbim.stmt), NULL);
    sqlite3_step(dbim.stmt);

    if (sqlite3_data_count(dbim.stmt) == 0) {
      return false;
    }
    else {
      return true;
    }
    break;
case 7: // eqangle
    proving = "SELECT * FROM Consequent INNER JOIN Eqangle USING(typeGeoCmd) WHERE Consequent.point1 = Eqangle.point1 and Consequent.point2 = Eqangle.point2 and Consequent.point3 = Eqangle.point3 and Consequent.point4 = Eqangle.point4 and Consequent.point5 = Eqangle.point5 and Consequent.point6 = Eqangle.point6 and Consequent.point7 = Eqangle.point7 and Consequent.point8 = Eqangle.point8";

    dbim.rc = sqlite3_prepare_v2(dbim.db,proving.c_str(),proving.size(), &(dbim.stmt), NULL);
    sqlite3_step(dbim.stmt);

    if (sqlite3_data_count(dbim.stmt) == 0) {
      return false;
    }
    else {
      return true;
    }
    break;
case 8: // cong
    proving = "SELECT * FROM Consequent INNER JOIN Cong USING(typeGeoCmd) WHERE Consequent.point1 = Cong.point1 and Consequent.point2 = Cong.point2 and Consequent.point3 = Cong.point3 and Consequent.point4 = Cong.point4";

    dbim.rc = sqlite3_prepare_v2(dbim.db,proving.c_str(),proving.size(), &(dbim.stmt), NULL);
    sqlite3_step(dbim.stmt);

    if (sqlite3_data_count(dbim.stmt) == 0) {
      return false;
    }
    else {
      return true;
    }
    break;
case 9: // Eqratio
    proving = "SELECT * FROM Consequent INNER JOIN Eqratio USING(typeGeoCmd) WHERE Consequent.point1 = Eqratio.point1 and Consequent.point2 = Eqratio.point2 and Consequent.point3 = Eqratio.point3 and Consequent.point4 = Eqratio.point4 and Consequent.point5 = Eqratio.point5 and Consequent.point6 = Eqratio.point6 and Consequent.point7 = Eqratio.point7 and Consequent.point8 = Eqratio.point8";

    dbim.rc = sqlite3_prepare_v2(dbim.db,proving.c_str(),proving.size(), &(dbim.stmt), NULL);
    sqlite3_step(dbim.stmt);

    if (sqlite3_data_count(dbim.stmt) == 0) {
      return false;
    }
    else {
      return true;
    }
    break;
case 10: // cyclic
    proving = "SELECT * FROM Consequent INNER JOIN Simtri USING(typeGeoCmd) WHERE Consequent.point1 = Simtri.point1 and Consequent.point2 = Simtri.point2 and Consequent.point3 = Simtri.point3 and Consequent.point4 = Simtri.point4 and Consequent.point5 = Simtri.point5 and Consequent.point6 = Simtri.point6";

    dbim.rc = sqlite3_prepare_v2(dbim.db,proving.c_str(),proving.size(), &(dbim.stmt), NULL);
    sqlite3_step(dbim.stmt);

    if (sqlite3_data_count(dbim.stmt) == 0) {
      return false;
    }
    else {
      return true;
    }
    break;
case 11: // cyclic
    proving = "SELECT * FROM Consequent INNER JOIN Contri USING(typeGeoCmd) WHERE Consequent.point1 = Contri.point1 and Consequent.point2 = Contri.point2 and Consequent.point3 = Contri.point3 and Consequent.point4 = Contri.point4 and Consequent.point5 = Contri.point5 and Consequent.point6 = Contri.point6";

    dbim.rc = sqlite3_prepare_v2(dbim.db,proving.c_str(),proving.size(), &(dbim.stmt), NULL);
    sqlite3_step(dbim.stmt);

    if (sqlite3_data_count(dbim.stmt) == 0) {
      return false;
    }
    else {
      return true;
    }
    break;

  default:
    return false;
  }
}

void Prover::showFixedPoint(DBinMemory dbim){

  sqlite3_stmt *stmt1;

  std::string sqlFacts,fixedPointFact;
  std::string idFact,typeGeoCmd;
  std::string point1,point2,point3,point4,point5,point6,point7,point8;

  std::cout << "\n\nshowFixedPoint\n\n";

  sqlFacts = "SELECT id,typeGeoCmd FROM Facts";
  dbim.rc = sqlite3_prepare_v2(dbim.db, sqlFacts.c_str() , sqlFacts.size(), &(dbim.stmt), NULL);
  while (sqlite3_step(dbim.stmt) == SQLITE_ROW) { //
    idFact = (char*) sqlite3_column_text(dbim.stmt, 0);
    typeGeoCmd = (char*) sqlite3_column_text(dbim.stmt, 1);

    switch (dbim.geoCmds[typeGeoCmd]) {
    case 1:  // coll

      // save the geometric command for the derivation of new facts
      fixedPointFact = "SELECT point1,point2,point3 FROM Collinear WHERE oldFact = "+idFact;
      //      std::cout << toDeriveGeoCmd << std::endl;
      dbim.rc = sqlite3_prepare_v2(dbim.db,fixedPointFact.c_str(),fixedPointFact.size(),&(dbim.stmt1),NULL);
      sqlite3_step(dbim.stmt1);
      point1 = (char*) sqlite3_column_text(dbim.stmt1, 0);
      point2 = (char*) sqlite3_column_text(dbim.stmt1, 1);
      point3 = (char*) sqlite3_column_text(dbim.stmt1, 2);
      std::cout << "Coll(" << point1 << "," << point2 << "," << point3 << ")\n";
      break;
    case 2:
      fixedPointFact = "SELECT point1,point2,point3,point4 FROM Parallel WHERE oldFact = "+idFact;
      //      std::cout << toDeriveGeoCmd << std::endl;
      dbim.rc = sqlite3_prepare_v2(dbim.db,fixedPointFact.c_str(),fixedPointFact.size(),&(dbim.stmt1),NULL);
      sqlite3_step(dbim.stmt1);
      //DebugStatement(dbim.stmt1);

      point1 = (char*) sqlite3_column_text(dbim.stmt1, 0);
      point2 = (char*) sqlite3_column_text(dbim.stmt1, 1);
      point3 = (char*) sqlite3_column_text(dbim.stmt1, 2);
      point4 = (char*) sqlite3_column_text(dbim.stmt1, 3);
      std::cout << "Para(" << point1 << "," << point2 << "," << point3 << "," << point4 << ")\n";
      break;
    case 3:  // perp
      fixedPointFact = "SELECT point1,point2,point3,point4 FROM Perpendicular WHERE oldFact = "+idFact;
      //      std::cout << toDeriveGeoCmd << std::endl;
      dbim.rc = sqlite3_prepare_v2(dbim.db,fixedPointFact.c_str(),fixedPointFact.size(),&(dbim.stmt1),NULL);
      sqlite3_step(dbim.stmt1);
      point1 = (char*) sqlite3_column_text(dbim.stmt1, 0);
      point2 = (char*) sqlite3_column_text(dbim.stmt1, 1);
      point3 = (char*) sqlite3_column_text(dbim.stmt1, 2);
      point4 = (char*) sqlite3_column_text(dbim.stmt1, 3);
      std::cout << "Perp(" << point1 << "," << point2 << "," << point3 << "," << point4 << ")\n";
      break;
    case 4:  // Midpoint
      fixedPointFact = "SELECT point1,point2,point3 FROM Midpoint WHERE oldFact = "+idFact;
      dbim.rc = sqlite3_prepare_v2(dbim.db,fixedPointFact.c_str(),fixedPointFact.size(),&(dbim.stmt1),NULL);
      sqlite3_step(dbim.stmt1);
      point1 = (char*) sqlite3_column_text(dbim.stmt1, 0);
      point2 = (char*) sqlite3_column_text(dbim.stmt1, 1);
      point3 = (char*) sqlite3_column_text(dbim.stmt1, 2);

      std::cout << "Midp(" << point1 << "," << point2 << "," << point3<<")\n";
      break;
    case 5:
      fixedPointFact = "SELECT point1,point2,point3,point4 FROM Circle WHERE oldFact = "+idFact;
      //      std::cout << toDeriveGeoCmd << std::endl;
      dbim.rc = sqlite3_prepare_v2(dbim.db,fixedPointFact.c_str(),fixedPointFact.size(),&(dbim.stmt1),NULL);
      sqlite3_step(dbim.stmt1);
      point1 = (char*) sqlite3_column_text(dbim.stmt1, 0);
      point2 = (char*) sqlite3_column_text(dbim.stmt1, 1);
      point3 = (char*) sqlite3_column_text(dbim.stmt1, 2);
      point4 = (char*) sqlite3_column_text(dbim.stmt1, 3);
      std::cout << "Circle(" << point1 << "," << point2 << "," << point3 << "," << point4 << ")\n";
      break;
    case 6:
      fixedPointFact = "SELECT point1,point2,point3,point4 FROM Cyclic WHERE oldFact = "+idFact;
      //      std::cout << toDeriveGeoCmd << std::endl;
      dbim.rc = sqlite3_prepare_v2(dbim.db,fixedPointFact.c_str(),fixedPointFact.size(),&(dbim.stmt1),NULL);
      sqlite3_step(dbim.stmt1);
      point1 = (char*) sqlite3_column_text(dbim.stmt1, 0);
      point2 = (char*) sqlite3_column_text(dbim.stmt1, 1);
      point3 = (char*) sqlite3_column_text(dbim.stmt1, 2);
      point4 = (char*) sqlite3_column_text(dbim.stmt1, 3);
      std::cout << "Cyclic(" << point1 << "," << point2 << "," << point3 << "," << point4 << ")\n";
      break;
    case 7:
      fixedPointFact = "SELECT point1,point2,point3,point4,point5,point6,point7,point8 FROM Eqangle WHERE oldFact = "+idFact;
      //      std::cout << toDeriveGeoCmd << std::endl;
      dbim.rc = sqlite3_prepare_v2(dbim.db,fixedPointFact.c_str(),fixedPointFact.size(),&(dbim.stmt1),NULL);
      sqlite3_step(dbim.stmt1);
      point1 = (char*) sqlite3_column_text(dbim.stmt1, 0);
      point2 = (char*) sqlite3_column_text(dbim.stmt1, 1);
      point3 = (char*) sqlite3_column_text(dbim.stmt1, 2);
      point4 = (char*) sqlite3_column_text(dbim.stmt1, 3);
      point5 = (char*) sqlite3_column_text(dbim.stmt1, 4);
      point6 = (char*) sqlite3_column_text(dbim.stmt1, 5);
      point7 = (char*) sqlite3_column_text(dbim.stmt1, 6);
      point8 = (char*) sqlite3_column_text(dbim.stmt1, 7);
      std::cout << "Eqangle(" << point1 << "," << point2 << "," << point3 << "," << point4 << "," << point5 << "," << point6 << "," << point7 << "," << point8 << ")\n";
      break;
    case 8:
      fixedPointFact = "SELECT point1,point2,point3,point4 FROM Cong WHERE oldFact = "+idFact;
      //      std::cout << toDeriveGeoCmd << std::endl;
      dbim.rc = sqlite3_prepare_v2(dbim.db,fixedPointFact.c_str(),fixedPointFact.size(),&(dbim.stmt1),NULL);
      sqlite3_step(dbim.stmt1);
      point1 = (char*) sqlite3_column_text(dbim.stmt1, 0);
      point2 = (char*) sqlite3_column_text(dbim.stmt1, 1);
      point3 = (char*) sqlite3_column_text(dbim.stmt1, 2);
      point4 = (char*) sqlite3_column_text(dbim.stmt1, 3);

      std::cout << "Cong(" << point1 << "," << point2 << "," << point3 << "," << point4 << ")\n";
      break;
    case 9:
      fixedPointFact = "SELECT point1,point2,point3,point4,point5,point6,point7,point8 FROM Eqratio WHERE oldFact = "+idFact;
      //      std::cout << toDeriveGeoCmd << std::endl;
      dbim.rc = sqlite3_prepare_v2(dbim.db,fixedPointFact.c_str(),fixedPointFact.size(),&(dbim.stmt1),NULL);
      sqlite3_step(dbim.stmt1);
      point1 = (char*) sqlite3_column_text(dbim.stmt1, 0);
      point2 = (char*) sqlite3_column_text(dbim.stmt1, 1);
      point3 = (char*) sqlite3_column_text(dbim.stmt1, 2);
      point4 = (char*) sqlite3_column_text(dbim.stmt1, 3);
      point5 = (char*) sqlite3_column_text(dbim.stmt1, 4);
      point6 = (char*) sqlite3_column_text(dbim.stmt1, 5);
      point7 = (char*) sqlite3_column_text(dbim.stmt1, 6);
      point8 = (char*) sqlite3_column_text(dbim.stmt1, 7);
      std::cout << "Eqratio(" << point1 << "," << point2 << "," << point3 << "," << point4 << "," << point5 << "," << point6 << "," << point7 << "," << point8 << ")\n";
      break;
    case 10:
      fixedPointFact = "SELECT point1,point2,point3,point4,point5,point6 FROM Simtri WHERE oldFact = "+idFact;
      //      std::cout << toDeriveGeoCmd << std::endl;
      dbim.rc = sqlite3_prepare_v2(dbim.db,fixedPointFact.c_str(),fixedPointFact.size(),&(dbim.stmt1),NULL);
      sqlite3_step(dbim.stmt1);
      point1 = (char*) sqlite3_column_text(dbim.stmt1, 0);
      point2 = (char*) sqlite3_column_text(dbim.stmt1, 1);
      point3 = (char*) sqlite3_column_text(dbim.stmt1, 2);
      point4 = (char*) sqlite3_column_text(dbim.stmt1, 3);
      point5 = (char*) sqlite3_column_text(dbim.stmt1, 4);
      point6 = (char*) sqlite3_column_text(dbim.stmt1, 5);
      std::cout << "Simtri(" << point1 << "," << point2 << "," << point3 << "," << point4 << "," << point5 << "," << point6 << ")\n";
      break;
    case 11:
      fixedPointFact = "SELECT point1,point2,point3,point4,point5,point6 FROM Contri WHERE oldFact = "+idFact;
      //      std::cout << toDeriveGeoCmd << std::endl;
      dbim.rc = sqlite3_prepare_v2(dbim.db,fixedPointFact.c_str(),fixedPointFact.size(),&(dbim.stmt1),NULL);
      sqlite3_step(dbim.stmt1);
      point1 = (char*) sqlite3_column_text(dbim.stmt1, 0);
      point2 = (char*) sqlite3_column_text(dbim.stmt1, 1);
      point3 = (char*) sqlite3_column_text(dbim.stmt1, 2);
      point4 = (char*) sqlite3_column_text(dbim.stmt1, 3);
      point5 = (char*) sqlite3_column_text(dbim.stmt1, 4);
      point6 = (char*) sqlite3_column_text(dbim.stmt1, 5);
      std::cout << "Contri(" << point1 << "," << point2 << "," << point3 << "," << point4 << "," << point5 << "," << point6 << ")\n";
      break;
    default:
      std::cout << "Geometric command not implemented\n";
    }
  }

}

