#include <iostream>

#include "ex1.h"
#include "Expression.h"



int main() {

    // 1
    Variable *x1 = new Variable("x1", 3);// x1=3
    Expression* e1 = new Mul( new UMinus(new Value(5.0) ) , new Plus( new Value(3.5) , &(++(*x1))) );// -5*(3.5+(++x1))
    cout << "1: " << e1->calculate() <<endl; //-37.5
    delete e1;

    // 2
    Variable *x2 = new Variable("x2", 5.0);// x2=5.0
    Variable *x3 = new Variable("x3", 10.0);// x3=10.0
    Expression* e2 = new Div(x2, new UMinus(new UPlus(new UMinus(x3))));// 5/-(+(-(10.0)))
    cout << "2: " << e2->calculate() << endl; //0.5
    delete e2;

    // 3
    Variable *x4 = new Variable("x4", 2.0);// x4=2.0
    Variable *x5 = new Variable("x5", -4.5);// x5=-4.5
    Expression* e3 = new Mul(&(++(*x4)), &((*x5)++));// (++x4)*(x5++)
    cout << "3: " << e3->calculate() << endl; //-10.5
    delete e3;
  // 5
  Interpreter* i2 = new Interpreter();
  Expression* e5 = nullptr;
    i2->setVariables("x=2");
    i2->setVariables("x=3");
  return 0;

}