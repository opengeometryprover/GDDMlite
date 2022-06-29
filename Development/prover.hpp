
/*
 * Prover
 */


#ifndef PROVER
#define PROVER

#include <string>
#include "dbRAM.hpp"

class DBinMemory; // just the name

class Prover {
private:

  void deriveNewColl(std::string,std::string,std::string);

public:
  /*
   * Show Fixed Point - display Facts table after findind a fixed-point
   */
  void showFixedPoint(DBinMemory);

  /*
   * Find the fixed point of the antecedents
   * ---> assume the database of the method, already opened and populated
   * <--- databased modified, adding all the new facts derived from the
   * antecedents
   */
  DBinMemory fixedPoint(DBinMemory);

  /*
   * Verify if the conjecture was proved, or not
   * ---> database with all the facts in the fixed point
   * <--- true the consequent is in the facts table, false in the othe case
   */
  bool proved(DBinMemory);










  DBinMemory ruleP1Coll(DBinMemory,std::string,std::string,std::string);
  DBinMemory ruleP1Perp(DBinMemory,std::string,std::string,std::string,std::string);

  DBinMemory ruleP2CircleA(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleP2CircleB(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleP2CircleC(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleP2CyclicA(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleP2CyclicB(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleP2CyclicC(DBinMemory,std::string,std::string,std::string,std::string);

  DBinMemory ruleD1(DBinMemory,std::string,std::string,std::string);
  DBinMemory ruleD2(DBinMemory,std::string,std::string,std::string);
  DBinMemory ruleD3(DBinMemory,std::string,std::string,std::string);
  DBinMemory ruleD4(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD5(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD6(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD7(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD8(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD9(DBinMemory,std::string,std::string,std::string,std::string);

  DBinMemory ruleD10Perp(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD10Para(DBinMemory,std::string,std::string,std::string,std::string);

  DBinMemory ruleD11(DBinMemory,std::string,std::string,std::string);
  DBinMemory ruleD12(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD13(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD14(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD15(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD16(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD17(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD18(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD19(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD20(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD21(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD22(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD23(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD24(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD25(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD26(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD27(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD28(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD29(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD30(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD31(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD32(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD33(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD34(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD35(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD36(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD37(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD38(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD39(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD40(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD41(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD42(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD43Eqangle(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD43Cyclic(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD44(DBinMemory,std::string,std::string,std::string);
  DBinMemory ruleD45Coll(DBinMemory,std::string,std::string,std::string);
  DBinMemory ruleD45Para(DBinMemory,std::string,std::string,std::string,std::string); //Check
  DBinMemory ruleD45Midp(DBinMemory,std::string,std::string,std::string); //Check
  DBinMemory ruleD46(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD47(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD48Circle(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD48Perp(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD49Circle(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD49Eqangle(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD50Circle(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD50Midp(DBinMemory,std::string,std::string,std::string);
  DBinMemory ruleD51Eqangle(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD51Coll(DBinMemory,std::string,std::string,std::string);
  DBinMemory ruleD51Circle(DBinMemory,std::string,std::string,std::string,std::string);

  DBinMemory ruleD52Perp(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD52Midp(DBinMemory,std::string,std::string,std::string);
  DBinMemory ruleD53Circle(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD53Coll(DBinMemory,std::string,std::string,std::string); //Check
  DBinMemory ruleD54Para(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD54Cyclic(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD55Perp(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD55Midp(DBinMemory,std::string,std::string,std::string); //Check
  DBinMemory ruleD56(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD57Circle(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD57Cong(DBinMemory,std::string,std::string,std::string,std::string); //Check
  DBinMemory ruleD58A(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD58B(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD59(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD60(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD61Simtri(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD61Cong(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD62(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD63(DBinMemory,std::string,std::string,std::string);
  DBinMemory ruleD64Para(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD64Midp(DBinMemory,std::string,std::string,std::string); //Check
  DBinMemory ruleD65Para(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD65Coll(DBinMemory,std::string,std::string,std::string); //Check
  DBinMemory ruleD66(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD67Cong(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD67Coll(DBinMemory,std::string,std::string,std::string); //Check
  DBinMemory ruleD68(DBinMemory,std::string,std::string,std::string);
  DBinMemory ruleD69(DBinMemory,std::string,std::string,std::string);
  DBinMemory ruleD70(DBinMemory,std::string,std::string,std::string);
  DBinMemory ruleD71(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD72(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD73Eqangle(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD73Para(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD74Eqangle(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD74Perp(DBinMemory,std::string,std::string,std::string,std::string);
  DBinMemory ruleD75Eqangle(DBinMemory,std::string,std::string,std::string,std::string,std::string,std::string,std::string,std::string);
  DBinMemory ruleD75Cong(DBinMemory,std::string,std::string,std::string,std::string);

  void testDBim(DBinMemory);
};

#endif

