/*
 * Driver, FOF parser
 * FOF format to GDDM database FOFtoDB
 *
 */

#ifndef FOFTODB
#define FOFTODB

#include <map>
#include "parser.hpp"

class DBinMemory; // só declarar o nome

/* 
 * classes Driver (parser FOF)
 */
// Give Flex the prototype of yylex we want ...
# define YY_DECL \
  yy::parser::symbol_type yylex (Driver& drv)
// ... and declare it for the parser's sake.
YY_DECL;

// Conducting the whole scanning and parsing of Calc++.
class Driver {
public:
  Driver ();

  int numGeoCmd=0;
  int antconcedent[500];
  std::string typeGeoCmd[500];
  std::string point1[500],point2[500],point3[500],point4[500];
  std::string point5[500],point6[500],point7[500],point8[500];
  
  std::map<std::string, int> variables;

  int result;

  // Run the parser on file F.  Return 0 on success.
  int parse (const std::string& f);
  // The name of the file being parsed.
  std::string file;
  // Whether to generate parser debug traces.
  bool trace_parsing;

  // Handling the scanner.
  void scan_begin ();
  void scan_end ();
  // Whether to generate scanner debug traces.
  bool trace_scanning;
  // The token's location used by the scanner.
  yy::location location;
};

class FOFtoDB {
private:

public:
  /*
   * Read (parse) de FOF file and populate the database
   */
  DBinMemory readFileLoadDB(Driver,DBinMemory);

  void showDB(DBinMemory);
};

#endif
