
/*
 * GDDM método
 */

#include <iostream>  // cin, cout, cerr, etc.
#include <ctime>
#include <string>
#include <map>
#include <sqlite3.h>
#include <set>


#include "dbRAM.hpp"
#include "parser.hpp"
#include "foftodb.hpp"
#include "prover.hpp"


using namespace std;

int main(int argc, char *argv[]){

  FOFtoDB fdb;
  Driver drv;
  Prover gddmetodo;
  DBinMemory dbim;

  int res = 0;

  /*
   * Stage 1 -  Parse de FOF problem
   *
   * Class: Driver (readFOFintoDB.hpp)
   */

  if (argc < 2) {
    std::cout << "Usage: ./gddm [-p|-s] <problemaFOF.p>\n";
    return(res=1);
  }
  else {
    if (argv[1] == std::string ("-p")) {
      drv.trace_parsing = true;
    }
    else if (argv[1] == std::string ("-s")) {
      drv.trace_scanning = true;
    }
    else if (!drv.parse (argv[1])) {
            std::cout << drv.result << '\n';
    }
    else {
      return(res = 2);
    }
  }

  /*
   * Stage 2 - Populate the database
   *
   * Class: FOFtoDB (readFOFintoDB.hpp)
   */
  // Open and re-create the database in memory
  dbim.openInMemoryDB();
  dbim.createDBforGDDM();
  //dbim.testDB();

  // populate the database (
  dbim = fdb.readFileLoadDB(drv,dbim);

  clock_t start_t, end_t;

  srand ( time(NULL) );

  start_t = clock();
  gddmetodo.showFixedPoint(dbim);
  dbim = gddmetodo.fixedPoint(dbim);

  gddmetodo.showFixedPoint(dbim);

  if (gddmetodo.proved(dbim)) {
    std::cout << "\nProved\n";
  }
  else {
    std::cout << "\nNot Proved\n";
  }

  end_t = clock();

  cout << "Time spent: " << ((double)(end_t - start_t)) / CLOCKS_PER_SEC << "\n\n";


  return 0;
};
