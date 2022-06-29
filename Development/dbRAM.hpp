/*
 * SQLite data base in memory
 */

#ifndef DBINMEMORY
#define DBINMEMORY

#include <sqlite3.h>
#include <map>
#include <iostream>


class DBinMemory {
  friend class Prover;
  friend class FOFtoDB;
protected:
  // SQLite variables
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;
  sqlite3_stmt *stmt,*stmt1,*stmt2;
  // end SQLite variables

  int res = 0;

  std::map<std::string,int> geoCmds = {{"coll", 1}, {"para", 2}, {"perp", 3}, {"midp", 4},{"circle",5},{"cyclic",6},{"eqangle",7},{"cong",8},{"eqratio",9},{"simtri",10},{"contri",11}};

public:

  /*
   * Open the database (in memory)
   * --->
   * <--- *db (pointer to the database
   */
  void openInMemoryDB();

  /*
   * Create DB, make all the create table commands
   * ---> *db
   * <--- *db (with all the tables created)
   */
  void createDBforGDDM();

  /*
   * Close the database
   */
  void closeDB();
};

#endif

