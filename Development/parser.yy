/*
 * Parser
 */

%skeleton "lalr1.cc" // -*- C++ -*-
%require "3.7.5"
%defines

%define api.token.raw

%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
  # include <string>
  class Driver;
}

// The parsing context.
%param { Driver& drv }

%locations

%define parse.trace
%define parse.error detailed
%define parse.lac full

%code {
# include "foftodb.hpp"
}

%define api.token.prefix {TOK_}
%token
  MINUS   "-"
  PLUS    "+"
  STAR    "*"
  SLASH   "/"
  LPAREN  "("
  RPAREN  ")"
  LRPAREN  "["
  RRPAREN  "]"
  VIRGULA ","
  FINALDOT "."
  SYNTACTICCONSEQUENCE "=>"
  CONJUNCTION "&"
  FORALL "!"
  TWODOTS ":"
  COLLINEAR "coll"
  PARALLEL "para"
  PERPENDICULAR "perp"
  MIDPOINT "midp"
  CIRCLE "circle"
  CYCLIC "cyclic"
  EQUALANGLE "eqangle"
  CONGRUENCE "cong"
  EQUALRATIO "eqratio"
  SIMETRI "simtri"
  CONGRUTRIC "contri"
  FOF "fof"
  CONJECTURE "conjecture"

;

%token <std::string> IDENTIFIER "identifier"
%token <int> NUMBER "number"

%printer { yyo << $$; } <*>;

%%
%start unit;
unit: fof  { };

fof:
  "fof" "(" "identifier" "," "conjecture" "," "("  forall ":" "(" antecedents ")" "=>" "(" consequent ")" ")" ")" "."
    { };

forall:
  "!" "[" varList "]"
  {};

antecedents:
  %empty                   {}
| antecedents antecedent   {}
| antecedents antecedent "&"  {}

antecedent:
  geocmd
  {
    drv.antconcedent[drv.numGeoCmd] = 0;
    drv.numGeoCmd++;
  };

consequent:
  geocmd
  {
    drv.antconcedent[drv.numGeoCmd] = 1;
    drv.numGeoCmd++;
  };

geocmd:
  collinear { };
  | parallel { };
  | perpendicular { };
  | midpoint { };
  | circle { };
  | cyclic { };
  | equalangle { };
  | congruence { };
  | equalratio { };
  | simetri { };
  | congrutric { };

collinear:
  "coll" "(" "identifier" "," "identifier" "," "identifier" ")"
  { drv.typeGeoCmd[drv.numGeoCmd]="coll";
    drv.point1[drv.numGeoCmd]=$3;
    drv.point2[drv.numGeoCmd]=$5;
    drv.point3[drv.numGeoCmd]=$7;
  };

parallel:
  "para" "(" "identifier" "," "identifier" "," "identifier" "," "identifier" ")"
  { drv.typeGeoCmd[drv.numGeoCmd]="para";
    drv.point1[drv.numGeoCmd]=$3;
    drv.point2[drv.numGeoCmd]=$5;
    drv.point3[drv.numGeoCmd]=$7;
    drv.point4[drv.numGeoCmd]=$9;
  };

perpendicular:
  "perp" "(" "identifier" "," "identifier" "," "identifier" "," "identifier"  ")"
  { drv.typeGeoCmd[drv.numGeoCmd]="perp";
    drv.point1[drv.numGeoCmd]=$3;
    drv.point2[drv.numGeoCmd]=$5;
    drv.point3[drv.numGeoCmd]=$7;
    drv.point4[drv.numGeoCmd]=$9;
  };

midpoint:
  "midp" "(" "identifier" "," "identifier" "," "identifier" ")"
  { drv.typeGeoCmd[drv.numGeoCmd]="midp";
    drv.point1[drv.numGeoCmd]=$3;
    drv.point2[drv.numGeoCmd]=$5;
    drv.point3[drv.numGeoCmd]=$7;
  };

circle:
 "circle" "(" "identifier" "," "identifier" "," "identifier" "," "identifier" ")"
  { drv.typeGeoCmd[drv.numGeoCmd]="circle";
    drv.point1[drv.numGeoCmd]=$3;
    drv.point2[drv.numGeoCmd]=$5;
    drv.point3[drv.numGeoCmd]=$7;
    drv.point4[drv.numGeoCmd]=$9;
  };

cyclic:
 "cyclic" "(" "identifier" "," "identifier" "," "identifier" "," "identifier" ")"
  { drv.typeGeoCmd[drv.numGeoCmd]="cyclic";
    drv.point1[drv.numGeoCmd]=$3;
    drv.point2[drv.numGeoCmd]=$5;
    drv.point3[drv.numGeoCmd]=$7;
    drv.point4[drv.numGeoCmd]=$9;
  };


equalangle:
  "eqangle" "(" "identifier" "," "identifier" "," "identifier" "," "identifier" "," "identifier" "," "identifier" "," "identifier" "," "identifier" ")"
  { drv.typeGeoCmd[drv.numGeoCmd]="eqangle";
    drv.point1[drv.numGeoCmd]=$3;
    drv.point2[drv.numGeoCmd]=$5;
    drv.point3[drv.numGeoCmd]=$7;
    drv.point4[drv.numGeoCmd]=$9;
    drv.point5[drv.numGeoCmd]=$11;
    drv.point6[drv.numGeoCmd]=$13;
    drv.point7[drv.numGeoCmd]=$15;
    drv.point8[drv.numGeoCmd]=$17;
  };

congruence:
  "cong" "(" "identifier" "," "identifier" "," "identifier" "," "identifier" ")"
  { drv.typeGeoCmd[drv.numGeoCmd]="cong";
    drv.point1[drv.numGeoCmd]=$3;
    drv.point2[drv.numGeoCmd]=$5;
    drv.point3[drv.numGeoCmd]=$7;
    drv.point4[drv.numGeoCmd]=$9;
  };

equalratio:
  "eqratio" "(" "identifier" "," "identifier" "," "identifier" "," "identifier" "," "identifier" "," "identifier" "," "identifier" "," "identifier" ")"
  { drv.typeGeoCmd[drv.numGeoCmd]="eqratio";
    drv.point1[drv.numGeoCmd]=$3;
    drv.point2[drv.numGeoCmd]=$5;
    drv.point3[drv.numGeoCmd]=$7;
    drv.point4[drv.numGeoCmd]=$9;
    drv.point5[drv.numGeoCmd]=$11;
    drv.point6[drv.numGeoCmd]=$13;
    drv.point7[drv.numGeoCmd]=$15;
    drv.point8[drv.numGeoCmd]=$17;
  };

simetri:
 "simtri" "(" "identifier" "," "identifier" "," "identifier" "," "identifier" "," "identifier" "," "identifier" ")"
  { drv.typeGeoCmd[drv.numGeoCmd]="simtri";
    drv.point1[drv.numGeoCmd]=$3;
    drv.point2[drv.numGeoCmd]=$5;
    drv.point3[drv.numGeoCmd]=$7;
    drv.point4[drv.numGeoCmd]=$9;
    drv.point5[drv.numGeoCmd]=$11;
    drv.point6[drv.numGeoCmd]=$13;
  };


congrutric:
 "contri" "(" "identifier" "," "identifier" "," "identifier" "," "identifier" "," "identifier" "," "identifier" ")"
  { drv.typeGeoCmd[drv.numGeoCmd]="contri";
    drv.point1[drv.numGeoCmd]=$3;
    drv.point2[drv.numGeoCmd]=$5;
    drv.point3[drv.numGeoCmd]=$7;
    drv.point4[drv.numGeoCmd]=$9;
    drv.point5[drv.numGeoCmd]=$11;
    drv.point6[drv.numGeoCmd]=$13;
  };


varList:
  %empty                   {}
| varList "identifier" {}
| varList "identifier" "," {}


%left "+" "-";
%left "*" "/";

%%

void
yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
