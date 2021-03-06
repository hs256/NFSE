#include <iostream>
#include <vector>

#ifndef CONSTRAINT_H
#define CONSTRAINT_H

using namespace std;

class Constraint {
  string name;
  string c1;
  string op1;
  string c2;
  string op2;
  string cval;
  Constraint *next;
public:
  Constraint(string n, string c01, string op01, string c02, string op02, string c03);
  string getname();
  string getc1();
  string getc2();
  string getcval();
  string getop1();
  string getop2();
  friend class CTTable;
};

#endif 
