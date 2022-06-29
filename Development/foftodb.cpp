
#include "parser.hpp"
#include "dbRAM.hpp"
#include "foftodb.hpp"

// Ligação a uma base de dados SQLite
// https://www.sqlite.org/cintro.html
#include <sqlite3.h>

Driver::Driver () : trace_parsing (false), trace_scanning (false) {
}

int Driver::parse (const std::string &f) {
  file = f;
  location.initialize (&file);
  scan_begin ();
  yy::parser parse (*this);
  parse.set_debug_level (trace_parsing);
  int res = parse ();
  scan_end ();
  return res;
}


DBinMemory FOFtoDB::readFileLoadDB(Driver drv, DBinMemory dbim) {

  std::string insertionNewFact,lastInsertedRowId,insertionColl, insertionPara,insertionPerp,insertionMidp;
  std::string lstInsRwId,insertionNewConsequent;
  bool correctTransaction;

  // Having made the parsing of the file, upload the antecedents and
  // consequentes into the database
  int i;
  int numGeoCmd = drv.numGeoCmd;

  for (i=0;i<numGeoCmd; i++) {
    if (drv.antconcedent[i] == 0) { // antecendents
      // The strings with the SQL command
      insertionNewFact = "INSERT INTO NewFact(typeGeoCmd) VALUES ('"+ drv.typeGeoCmd[i]+"')";

      // O valor de NewFact row id tem de ser obtido através de uma consulta
      lastInsertedRowId = "SELECT last_insert_rowid()";

      //Open transaction
      sqlite3_exec(dbim.db, "begin;", 0, 0, &(dbim.zErrMsg));

      correctTransaction=true;

      // insert the new fact into NewFacts
      dbim.rc = sqlite3_prepare_v2(dbim.db, insertionNewFact.c_str() , insertionNewFact.size(), &(dbim.stmt), NULL);
      if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {
	correctTransaction = false;
      }
      // get the last Inserted Row Id
      dbim.rc = sqlite3_prepare_v2(dbim.db, lastInsertedRowId.c_str() , lastInsertedRowId.size(), &(dbim.stmt), NULL);

      sqlite3_step(dbim.stmt);  //executing the statement
      lstInsRwId = (char*) sqlite3_column_text( dbim.stmt, 0 );

      auto val = dbim.geoCmds[drv.typeGeoCmd[i]];
      switch (val) {
      case 1: // Collinear command
	// Insert the GeoCmd in the correct table connecting it to the new fact
	insertionColl = "INSERT INTO Collinear(typeGeoCmd,point1,point2,point3,newFact) VALUES ('"+drv.typeGeoCmd[i]+"','"+drv.point1[i]+"','"+drv.point2[i]+"','"+drv.point3[i]+"',"+lstInsRwId+")";

	dbim.rc = sqlite3_prepare_v2(dbim.db, insertionColl.c_str() , insertionColl.size(), &(dbim.stmt), NULL);
	if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {
	  correctTransaction = false;
	}
	break;
		case 2: // Parallel
	// Insert the GeoCmd in the correct table connecting it to the new fact
	insertionPara = "INSERT INTO Parallel(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('"+drv.typeGeoCmd[i]+"','"+drv.point1[i]+"','"+drv.point2[i]+"','"+drv.point3[i]+"','"+drv.point4[i]+"',"+lstInsRwId+")";

	dbim.rc = sqlite3_prepare_v2(dbim.db, insertionPara.c_str() , insertionPara.size(), &(dbim.stmt), NULL);
	if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {
	  correctTransaction = false;
	}
	break;
		case 3: // Perpendicular
	insertionPerp = "INSERT INTO Perpendicular(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('"+drv.typeGeoCmd[i]+"','"+drv.point1[i]+"','"+drv.point2[i]+"','"+drv.point3[i]+"','"+drv.point4[i]+"',"+lstInsRwId+")";

	dbim.rc = sqlite3_prepare_v2(dbim.db, insertionPerp.c_str() , insertionPerp.size(), &(dbim.stmt), NULL);
	if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {
	  correctTransaction = false;
	}

	break;
		case 4: // Midpoint
	// Insert the GeoCmd in the correct table connecting it to the new fact
	insertionMidp = "INSERT INTO Midpoint(typeGeoCmd,point1,point2,point3,newFact) VALUES ('"+drv.typeGeoCmd[i]+"','"+drv.point1[i]+"','"+drv.point2[i]+"','"+drv.point3[i]+"',"+lstInsRwId+")";
	dbim.rc = sqlite3_prepare_v2(dbim.db, insertionMidp.c_str() , insertionMidp.size(), &(dbim.stmt), NULL);
	if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {
	  correctTransaction = false;
	}
	break;
		case 5: // Circle
	insertionPerp = "INSERT INTO Circle(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('"+drv.typeGeoCmd[i]+"','"+drv.point1[i]+"','"+drv.point2[i]+"','"+drv.point3[i]+"','"+drv.point4[i]+"',"+lstInsRwId+")";

	dbim.rc = sqlite3_prepare_v2(dbim.db, insertionPerp.c_str() , insertionPerp.size(), &(dbim.stmt), NULL);
	if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {
	  correctTransaction = false;
	}
	break;
        case 6: // Cyclic
	insertionPerp = "INSERT INTO Cyclic(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('"+drv.typeGeoCmd[i]+"','"+drv.point1[i]+"','"+drv.point2[i]+"','"+drv.point3[i]+"','"+drv.point4[i]+"',"+lstInsRwId+")";

	dbim.rc = sqlite3_prepare_v2(dbim.db, insertionPerp.c_str() , insertionPerp.size(), &(dbim.stmt), NULL);
	if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {
	  correctTransaction = false;
	}
    break;
		case 7:
	insertionPerp = "INSERT INTO Eqangle(typeGeoCmd,point1,point2,point3,point4,point5,point6,point7,point8,newFact) VALUES ('"+drv.typeGeoCmd[i]+"','"+drv.point1[i]+"','"+drv.point2[i]+"','"+drv.point3[i]+"','"+drv.point4[i]+"','"+drv.point5[i]+"','"+drv.point6[i]+"','"+drv.point7[i]+"','"+drv.point8[i]+"',"+lstInsRwId+")";

	dbim.rc = sqlite3_prepare_v2(dbim.db, insertionPerp.c_str() , insertionPerp.size(), &(dbim.stmt), NULL);
	if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {
	  correctTransaction = false;
	}
	break;
		case 8:
	insertionPerp = "INSERT INTO Cong(typeGeoCmd,point1,point2,point3,point4,newFact) VALUES ('"+drv.typeGeoCmd[i]+"','"+drv.point1[i]+"','"+drv.point2[i]+"','"+drv.point3[i]+"','"+drv.point4[i]+"',"+lstInsRwId+")";

	dbim.rc = sqlite3_prepare_v2(dbim.db, insertionPerp.c_str() , insertionPerp.size(), &(dbim.stmt), NULL);
	if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {
	  correctTransaction = false;
	}
	break;
		case 9:
	insertionPerp = "INSERT INTO Eqratio(typeGeoCmd,point1,point2,point3,point4,point5,point6,point7,point8,newFact) VALUES ('"+drv.typeGeoCmd[i]+"','"+drv.point1[i]+"','"+drv.point2[i]+"','"+drv.point3[i]+"','"+drv.point4[i]+"','"+drv.point5[i]+"','"+drv.point6[i]+"','"+drv.point7[i]+"','"+drv.point8[i]+"',"+lstInsRwId+")";

	dbim.rc = sqlite3_prepare_v2(dbim.db, insertionPerp.c_str() , insertionPerp.size(), &(dbim.stmt), NULL);
	if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {
	  correctTransaction = false;
	}
	break;
		case 10:
	insertionPerp = "INSERT INTO Simtri(typeGeoCmd,point1,point2,point3,point4,point5,point6,newFact) VALUES ('"+drv.typeGeoCmd[i]+"','"+drv.point1[i]+"','"+drv.point2[i]+"','"+drv.point3[i]+"','"+drv.point4[i]+"','"+drv.point5[i]+"','"+drv.point6[i]+"',"+lstInsRwId+")";

	dbim.rc = sqlite3_prepare_v2(dbim.db, insertionPerp.c_str() , insertionPerp.size(), &(dbim.stmt), NULL);
	if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {
	  correctTransaction = false;
	}
	break;
		case 11:
    insertionPerp = "INSERT INTO Contri(typeGeoCmd,point1,point2,point3,point4,point5,point6,newFact) VALUES ('"+drv.typeGeoCmd[i]+"','"+drv.point1[i]+"','"+drv.point2[i]+"','"+drv.point3[i]+"','"+drv.point4[i]+"','"+drv.point5[i]+"','"+drv.point6[i]+"',"+lstInsRwId+")";

	dbim.rc = sqlite3_prepare_v2(dbim.db, insertionPerp.c_str() , insertionPerp.size(), &(dbim.stmt), NULL);
	if (sqlite3_step(dbim.stmt) != SQLITE_DONE) {
	  correctTransaction = false;
	}
	break;
		default:
	// erro, comando não implementado
	std::cout << "Error: <codigo de erro>\n";
      }
      // close the transaction: commit or rollback
      if (correctTransaction) {
	sqlite3_exec(dbim.db, "commit;", 0, 0, 0);
      }
      else {
	sqlite3_exec(dbim.db, "rollback;", 0, 0, 0);
      }

    }
    else { // drv.antconcedent[i] != 0 ... consequent
      switch (dbim.geoCmds[drv.typeGeoCmd[i]]) {
      case 1: // collinear, 3 points
	// insert the new consequent into the table Consequents
	insertionNewConsequent = "INSERT INTO Consequent(typeGeoCmd,point1,point2,point3) VALUES ('"+ drv.typeGeoCmd[i]+"','"+drv.point1[i]+"','"+drv.point2[i]+"','"+drv.point3[i]+"')";
	dbim.rc = sqlite3_prepare_v2(dbim.db, insertionNewConsequent.c_str() , insertionNewConsequent.size(), &(dbim.stmt), NULL);
	sqlite3_step(dbim.stmt);
	break;
      case 2:
	insertionNewConsequent = "INSERT INTO Consequent(typeGeoCmd,point1,point2,point3,point4) VALUES ('"+ drv.typeGeoCmd[i]+"','"+drv.point1[i]+"','"+drv.point2[i]+"','"+drv.point3[i]+"','"+drv.point4[i]+"')";

	dbim.rc = sqlite3_prepare_v2(dbim.db, insertionNewConsequent.c_str() , insertionNewConsequent.size(), &(dbim.stmt), NULL);
	sqlite3_step(dbim.stmt);
    break;
      case 3: // para perp, 4 points
	insertionNewConsequent = "INSERT INTO Consequent(typeGeoCmd,point1,point2,point3,point4) VALUES ('"+ drv.typeGeoCmd[i]+"','"+drv.point1[i]+"','"+drv.point2[i]+"','"+drv.point3[i]+"','"+drv.point4[i]+"')";

	dbim.rc = sqlite3_prepare_v2(dbim.db, insertionNewConsequent.c_str() , insertionNewConsequent.size(), &(dbim.stmt), NULL);
	sqlite3_step(dbim.stmt);
	break;
      case 4: // para midp, 3 points
	insertionNewConsequent = "INSERT INTO Consequent(typeGeoCmd,point1,point2,point3) VALUES ('"+ drv.typeGeoCmd[i]+"','"+drv.point1[i]+"','"+drv.point2[i]+"','"+drv.point3[i]+"')";

	dbim.rc = sqlite3_prepare_v2(dbim.db, insertionNewConsequent.c_str() , insertionNewConsequent.size(), &(dbim.stmt), NULL);
	sqlite3_step(dbim.stmt);
    break;
      case 5:
	insertionNewConsequent = "INSERT INTO Consequent(typeGeoCmd,point1,point2,point3,point4) VALUES ('"+ drv.typeGeoCmd[i]+"','"+drv.point1[i]+"','"+drv.point2[i]+"','"+drv.point3[i]+"','"+drv.point4[i]+"')";

	dbim.rc = sqlite3_prepare_v2(dbim.db, insertionNewConsequent.c_str() , insertionNewConsequent.size(), &(dbim.stmt), NULL);
	sqlite3_step(dbim.stmt);
    break;
      case 6: // para cyclic, 4 points
	insertionNewConsequent = "INSERT INTO Consequent(typeGeoCmd,point1,point2,point3,point4) VALUES ('"+ drv.typeGeoCmd[i]+"','"+drv.point1[i]+"','"+drv.point2[i]+"','"+drv.point3[i]+"','"+drv.point4[i]+"')";

	dbim.rc = sqlite3_prepare_v2(dbim.db, insertionNewConsequent.c_str() , insertionNewConsequent.size(), &(dbim.stmt), NULL);
	sqlite3_step(dbim.stmt);
	break;
      case 7:
	insertionNewConsequent = "INSERT INTO Consequent(typeGeoCmd,point1,point2,point3,point4,point5,point6,point7,point8) VALUES ('"+ drv.typeGeoCmd[i]+"','"+drv.point1[i]+"','"+drv.point2[i]+"','"+drv.point3[i]+"','"+drv.point4[i]+"','"+drv.point5[i]+"','"+drv.point6[i]+"','"+drv.point7[i]+"','"+drv.point8[i]+"')";

	dbim.rc = sqlite3_prepare_v2(dbim.db, insertionNewConsequent.c_str() , insertionNewConsequent.size(), &(dbim.stmt), NULL);
	sqlite3_step(dbim.stmt);
    break;
      case 8:
	insertionNewConsequent = "INSERT INTO Consequent(typeGeoCmd,point1,point2,point3,point4) VALUES ('"+ drv.typeGeoCmd[i]+"','"+drv.point1[i]+"','"+drv.point2[i]+"','"+drv.point3[i]+"','"+drv.point4[i]+"')";

	dbim.rc = sqlite3_prepare_v2(dbim.db, insertionNewConsequent.c_str() , insertionNewConsequent.size(), &(dbim.stmt), NULL);
	sqlite3_step(dbim.stmt);
    break;
      case 9:
	insertionNewConsequent = "INSERT INTO Consequent(typeGeoCmd,point1,point2,point3,point4,point5,point6,point7,point8) VALUES ('"+ drv.typeGeoCmd[i]+"','"+drv.point1[i]+"','"+drv.point2[i]+"','"+drv.point3[i]+"','"+drv.point4[i]+"','"+drv.point5[i]+"','"+drv.point6[i]+"','"+drv.point7[i]+"','"+drv.point8[i]+"')";

	dbim.rc = sqlite3_prepare_v2(dbim.db, insertionNewConsequent.c_str() , insertionNewConsequent.size(), &(dbim.stmt), NULL);
	sqlite3_step(dbim.stmt);
    break;
       case 10:
	insertionNewConsequent = "INSERT INTO Consequent(typeGeoCmd,point1,point2,point3,point4,point5,point6) VALUES ('"+ drv.typeGeoCmd[i]+"','"+drv.point1[i]+"','"+drv.point2[i]+"','"+drv.point3[i]+"','"+drv.point4[i]+"','"+drv.point5[i]+"','"+drv.point6[i]+"')";

	dbim.rc = sqlite3_prepare_v2(dbim.db, insertionNewConsequent.c_str() , insertionNewConsequent.size(), &(dbim.stmt), NULL);
	sqlite3_step(dbim.stmt);
      case 11:
	insertionNewConsequent = "INSERT INTO Consequent(typeGeoCmd,point1,point2,point3,point4,point5,point6) VALUES ('"+ drv.typeGeoCmd[i]+"','"+drv.point1[i]+"','"+drv.point2[i]+"','"+drv.point3[i]+"','"+drv.point4[i]+"','"+drv.point5[i]+"','"+drv.point6[i]+"')";

	dbim.rc = sqlite3_prepare_v2(dbim.db, insertionNewConsequent.c_str() , insertionNewConsequent.size(), &(dbim.stmt), NULL);
	sqlite3_step(dbim.stmt);
        }
    }
  }

  return(dbim);
}


void FOFtoDB::showDB(DBinMemory dbim) {

  std::string selectDB = "SELECT typeGeoCmd,point1,point2,point3  FROM Collinear";
  dbim.rc = sqlite3_prepare_v2(dbim.db, selectDB.c_str() , selectDB.size(), &(dbim.stmt), NULL);
  sqlite3_step(dbim.stmt);
  std::cout << sqlite3_column_text(dbim.stmt, 0) << "("
	    << sqlite3_column_text(dbim.stmt, 1)
	    << "," << sqlite3_column_text(dbim.stmt, 2) << ","
	    << sqlite3_column_text(dbim.stmt, 3)
	    << ")\n";

  while (sqlite3_step(dbim.stmt) != SQLITE_DONE) { //
    std::cout << sqlite3_column_text(dbim.stmt, 0) << "(" << sqlite3_column_text(dbim.stmt, 1)
	      << "," << sqlite3_column_text(dbim.stmt, 2) << ","
	      << sqlite3_column_text(dbim.stmt, 3)
	      << ")\n";
  }
}
