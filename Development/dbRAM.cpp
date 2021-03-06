/*
 * SQLite data base in memory
 */

#include <iostream>
#include <string>

#include "dbRAM.hpp"

void DBinMemory::openInMemoryDB(){
  // try to open the database
  //  rc = sqlite3_open(databasename.c_str(), &db);
  rc = sqlite3_open(":memory:", &db);

  if( rc ){
    std::cout << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    exit(2);
  }
}


void DBinMemory::createDBforGDDM(){
  std::string createTableNewFact,createTableFacts;
  std::string createTableConsequent;
  std::string createTableCollinear,createTableParallel,createTablePerpendicular;
  std::string createTableMidpoint,createTableCircle,createTableCyclic;
  std::string createTableEqangle,createTableCong,createTableEqratio;
  std::string createTableSimtri,createTableContri;
  std::string deleteFromSqliteSequence;

  // to be able to re-create the database, without any violation issue.
  sqlite3_prepare_v2(db, "PRAGMA foreign_keys = OFF", -1, &stmt, NULL);
  sqlite3_step(stmt);

  // The create tables statements

  createTableNewFact = "CREATE TABLE IF NOT EXISTS 'NewFact' ('id' INTEGER NOT NULL,'typeGeoCmd' TEXT NOT NULL, PRIMARY KEY('id' AUTOINCREMENT))";

  createTableFacts = "CREATE TABLE IF NOT EXISTS 'Facts' ('id' INTEGER NOT NULL, 'typeGeoCmd' TEXT NOT NULL, PRIMARY KEY('id'))";

  createTableConsequent = "CREATE TABLE IF NOT EXISTS 'Consequent' ('id' INTEGER NOT NULL,'typeGeoCmd' TEXT NOT NULL,'point1' TEXT,'point2' TEXT,'point3' TEXT,'point4' TEXT,'point5' TEXT,'point6' TEXT,'point7' TEXT,'point8' TEXT,PRIMARY KEY('id' AUTOINCREMENT))";

  createTableCollinear = "CREATE TABLE IF NOT EXISTS 'Collinear' ('typeGeoCmd' TEXT NOT NULL,'point1' TEXT,'point2' TEXT,'point3' TEXT,'newFact' INTEGER,'oldFact' INTEGER, FOREIGN KEY('oldFact') REFERENCES 'Facts'('id'),FOREIGN KEY('newFact') REFERENCES 'NewFact'('id') ON DELETE SET NULL,PRIMARY KEY('point1','point2','point3'))";
  createTableParallel = "CREATE TABLE IF NOT EXISTS 'Parallel' ('typeGeoCmd' TEXT NOT NULL,'point1' TEXT,'point2' TEXT,'point3' TEXT,'point4' TEXT,'newFact' INTEGER,'oldFact' INTEGER,FOREIGN KEY('oldFact') REFERENCES 'Facts'('id'),FOREIGN KEY('newFact') REFERENCES 'NewFact'('id') ON DELETE SET NULL,PRIMARY KEY('point1','point2','point3','point4'))";
  createTablePerpendicular = "CREATE TABLE IF NOT EXISTS 'Perpendicular' ('typeGeoCmd' TEXT NOT NULL,'point1' TEXT,'point2' TEXT,'point3' TEXT,'point4' TEXT,'newFact' INTEGER,'oldFact' INTEGER,FOREIGN KEY('oldFact') REFERENCES 'Facts'('id'),PRIMARY KEY('point1','point2','point3','point4'),FOREIGN KEY('newFact') REFERENCES 'NewFact'('id') ON DELETE SET NULL)";
  createTableMidpoint = "CREATE TABLE IF NOT EXISTS 'Midpoint' ('typeGeoCmd' TEXT NOT NULL,'point1' TEXT,'point2' TEXT,'point3' TEXT,'newFact' INTEGER,'oldFact' INTEGER,FOREIGN KEY('oldFact') REFERENCES 'Facts'('id'),PRIMARY KEY('point1','point2','point3'),FOREIGN KEY('newFact') REFERENCES 'NewFact'('id') ON DELETE SET NULL)";
  createTableCircle = "CREATE TABLE IF NOT EXISTS 'Circle' ('typeGeoCmd' TEXT NOT NULL,'point1' TEXT,'point2' TEXT,'point3' TEXT,'point4' TEXT,'newFact' INTEGER,'oldFact' INTEGER,FOREIGN KEY('oldFact') REFERENCES 'Facts'('id'),PRIMARY KEY('point1','point2','point3','point4'),FOREIGN KEY('newFact') REFERENCES 'NewFact'('id') ON DELETE SET NULL)";
  createTableCyclic = "CREATE TABLE IF NOT EXISTS 'Cyclic' ('typeGeoCmd' TEXT NOT NULL,'point1' TEXT,'point2' TEXT,'point3' TEXT,'point4' TEXT,'newFact' INTEGER,'oldFact' INTEGER,FOREIGN KEY('oldFact') REFERENCES 'Facts'('id'),PRIMARY KEY('point1','point2','point3','point4'),FOREIGN KEY('newFact') REFERENCES 'NewFact'('id') ON DELETE SET NULL)";
  createTableEqangle = "CREATE TABLE IF NOT EXISTS 'Eqangle' ('typeGeoCmd' TEXT NOT NULL,'point1' TEXT,'point2' TEXT,'point3' TEXT,'point4' TEXT,'point5' TEXT,'point6' TEXT,'point7' TEXT,'point8' TEXT,'newFact' INTEGER,'oldFact' INTEGER,FOREIGN KEY('oldFact') REFERENCES 'Facts'('id'),PRIMARY KEY('point1','point2','point3','point4','point5','point6','point7','point8'),FOREIGN KEY('newFact') REFERENCES 'NewFact'('id') ON DELETE SET NULL)";
  createTableCong = "CREATE TABLE IF NOT EXISTS 'Cong' ('typeGeoCmd' TEXT NOT NULL,'point1' TEXT,'point2' TEXT,'point3' TEXT,'point4' TEXT,'newFact' INTEGER,'oldFact' INTEGER,FOREIGN KEY('oldFact') REFERENCES 'Facts'('id'),FOREIGN KEY('newFact') REFERENCES 'NewFact'('id') ON DELETE SET NULL,PRIMARY KEY('point1','point2','point3','point4'))";
  createTableEqratio = "CREATE TABLE IF NOT EXISTS 'Eqratio' ('typeGeoCmd' TEXT NOT NULL,'point1' TEXT,'point2' TEXT,'point3' TEXT,'point4' TEXT,'point5' TEXT,'point6' TEXT,'point7' TEXT,'point8' TEXT,'newFact' INTEGER,'oldFact' INTEGER,FOREIGN KEY('oldFact') REFERENCES 'Facts'('id'),PRIMARY KEY('point1','point2','point3','point4','point5','point6','point7','point8'),FOREIGN KEY('newFact') REFERENCES 'NewFact'('id') ON DELETE SET NULL)";
  createTableSimtri = "CREATE TABLE IF NOT EXISTS 'Simtri' ('typeGeoCmd' TEXT NOT NULL,'point1' TEXT,'point2' TEXT,'point3' TEXT,'point4' TEXT,'point5' TEXT,'point6' TEXT,'newFact' INTEGER,'oldFact' INTEGER,FOREIGN KEY('oldFact') REFERENCES 'Facts'('id'),PRIMARY KEY('point1','point2','point3','point4','point5','point6'),FOREIGN KEY('newFact') REFERENCES 'NewFact'('id') ON DELETE SET NULL)";
  createTableContri = "CREATE TABLE IF NOT EXISTS 'Contri' ('typeGeoCmd' TEXT NOT NULL,'point1' TEXT,'point2' TEXT,'point3' TEXT,'point4' TEXT,'point5' TEXT,'point6' TEXT,'newFact' INTEGER,'oldFact' INTEGER,FOREIGN KEY('oldFact') REFERENCES 'Facts'('id'),PRIMARY KEY('point1','point2','point3','point4','point5','point6'),FOREIGN KEY('newFact') REFERENCES 'NewFact'('id') ON DELETE SET NULL)";

  deleteFromSqliteSequence = "DELETE FROM sqlite_sequence";

  //Open transaction
  sqlite3_exec(db, "begin;", 0, 0, &zErrMsg);

  rc = sqlite3_prepare_v2(db, createTableNewFact.c_str() , createTableNewFact.size(), &stmt, NULL);
  sqlite3_step( stmt );
  rc = sqlite3_prepare_v2(db, createTableFacts.c_str() , createTableFacts.size(), &stmt, NULL);
  sqlite3_step( stmt );

  rc = sqlite3_prepare_v2(db, createTableCollinear.c_str() , createTableCollinear.size(), &stmt, NULL);
  sqlite3_step( stmt );
  rc = sqlite3_prepare_v2(db, createTableParallel.c_str() , createTableParallel.size(), &stmt, NULL);
  sqlite3_step( stmt );
  rc = sqlite3_prepare_v2(db, createTablePerpendicular.c_str() , createTablePerpendicular.size(), &stmt, NULL);
  sqlite3_step( stmt );
  rc = sqlite3_prepare_v2(db, createTableMidpoint.c_str() , createTableMidpoint.size(), &stmt, NULL);
  sqlite3_step( stmt );
  rc = sqlite3_prepare_v2(db, createTableCircle.c_str() , createTableCircle.size(), &stmt, NULL);
  sqlite3_step( stmt );
  rc = sqlite3_prepare_v2(db, createTableCyclic.c_str() , createTableCyclic.size(), &stmt, NULL);
  sqlite3_step( stmt );
  rc = sqlite3_prepare_v2(db, createTableEqangle.c_str() , createTableEqangle.size(), &stmt, NULL);
  sqlite3_step( stmt );
  rc = sqlite3_prepare_v2(db, createTableCong.c_str() , createTableCong.size(), &stmt, NULL);
  sqlite3_step( stmt );
  rc = sqlite3_prepare_v2(db, createTableEqratio.c_str() , createTableEqratio.size(), &stmt, NULL);
  sqlite3_step( stmt );
  rc = sqlite3_prepare_v2(db, createTableSimtri.c_str() , createTableSimtri.size(), &stmt, NULL);
  sqlite3_step( stmt );
  rc = sqlite3_prepare_v2(db, createTableContri.c_str() , createTableContri.size(), &stmt, NULL);
  sqlite3_step( stmt );

  rc = sqlite3_prepare_v2(db, createTableConsequent.c_str() , createTableConsequent.size(), &stmt, NULL);
  sqlite3_step( stmt );
  rc = sqlite3_prepare_v2(db, deleteFromSqliteSequence.c_str() , deleteFromSqliteSequence.size(), &stmt, NULL);
  sqlite3_step( stmt );

  // Close the transaction
  sqlite3_exec(db, "commit;", 0, 0, 0);

}

void DBinMemory::closeDB() {
  sqlite3_close(db);
}
