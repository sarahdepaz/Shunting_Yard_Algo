#ifndef EX1_ALL_IN_ONE_EX1_H
#define EX1_ALL_IN_ONE_EX1_H
#include <deque>
#include "string"
#include "Expression.h"
#include <stack>
#include <vector>
#include <map>
#include <queue>

class BinaryOperator : public Expression {
  Expression* left {nullptr};
  Expression* right {nullptr};
 protected:
  BinaryOperator(Expression* l, Expression* r) : left(l), right(r) {}
  Expression* getLeft();
  Expression* getRight();
};
class Plus : public BinaryOperator {
 public:
  Plus(Expression* l, Expression* r) : BinaryOperator(l,r){}
  double calculate() override;
};
class Minus : public BinaryOperator {
 public:
  Minus(Expression* l, Expression* r) : BinaryOperator(l,r){}
  double calculate() override ;
};
class Mul : public BinaryOperator {
 public:
  Mul(Expression* l, Expression* r) : BinaryOperator(l,r){}
  double calculate() override;
};
class Div : public BinaryOperator {
 public:
  Div(Expression* l, Expression* r) : BinaryOperator(l,r){}
  double calculate() override;
};
class Variable : public Expression {
 private:
  string name;
  double value;
 public:
  double calculate() override;
  Variable(string n, double val) : name(n), value(val) {}
  Variable& operator+=(double);
  Variable& operator-=(double);
  Variable& operator--();
  Variable& operator--(int);
  // Prefix
  Variable& operator++();
  // Postfix
  Variable& operator++(int);
};
class Value : public Expression {
 private:
  double value;
 public:
  explicit Value(double v) : value(v) {}
  double calculate() override;
};
class UnaryOperator : public Expression {
 protected:
  Expression* exp {nullptr};
 public:
  explicit UnaryOperator(Expression* e) : exp(e) {}
  Expression* getExp();
  void setExp(Expression* e);
};
class UPlus : public UnaryOperator {
 protected:
  Expression* exp {nullptr};
 public:
  explicit UPlus(Expression* e) : UnaryOperator(e){}
  double calculate() override;
};
class UMinus : public UnaryOperator {
 protected:
  Expression* exp {nullptr};
 public:
  explicit UMinus(Expression* e) : UnaryOperator(e){}
  double calculate() override;
};
class Interpreter {
 private:
  map<string, string> varMap;
 public:
  Interpreter(){};
  ~Interpreter(){};
  void setVariables(string);
  bool isOperator(string);
  bool isChar(char c);
  //bool isValid(map<string, double>);
  Expression* interpret(string);
  int isPrecedence (string);
  Expression* buildExpression(deque<string>);
};

#endif //EX1_ALL_IN_ONE_EX1_H