#include "Expression.h"
#include "ex1.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "regex"
#include <map>
#include <stack>
#include<string.h>
#include <stdlib.h>
//using namespace std;
Expression* BinaryOperator :: getLeft() {
  return this->left;
}
Expression* BinaryOperator :: getRight() {
  return this->right;
}
void BinaryOperator :: setRight(Expression* r) {
  this->right = r;
}
void BinaryOperator :: setLeft(Expression* l) {
  this->left = l;
}
double Plus :: calculate() {
  return this->getLeft()->calculate() + this->getRight()->calculate();
}
double Minus :: calculate() {
  return this->getLeft()->calculate() - this->getRight()->calculate();
}
double Mul :: calculate(){
  return this->getLeft()->calculate() * this->getRight()->calculate();
}
double Div :: calculate(){
  return this->getLeft()->calculate() / this->getRight()->calculate();
}
double Value :: calculate() {
  return this->value;
}
double Variable :: calculate() {
  return this->value;
}
Variable& Variable :: operator+=(double plusEqual) {
  this->value +=  plusEqual;
  return *this;
}
Variable& Variable ::operator-=(double minusEqual) {
  this->value -= minusEqual;
  return *this;
}
Variable& Variable :: operator--(){
  this->value -=  1;
  return *this;
}
// Postfix
Variable& Variable :: operator--(int) {
  this->value -= 1;
  return *this;
}
// Prefix
Variable& Variable :: operator++() {
  this->value += 1;
  return *this;
}
// Postfix
Variable& Variable :: operator++(int) {
  this->value += 1;
  return *this;
}
Expression* UnaryOperator :: getExp() {
  return exp;
}
void UnaryOperator :: setExp(Expression* e) {
  this->exp = e;
}
double UPlus :: calculate() {
  return this->getExp()->calculate();
}
double UMinus :: calculate() {
  return -(this->getExp()->calculate());
}
void Interpreter :: setVariables(string input) {
  bool varGood = false;
  bool valGood = false;
  std::vector<std::string> varNames, varValues;
  for (std::istringstream in(input);;) {
    std::string lhs, rhs;
    if (!std::getline(in, lhs, '=') || !std::getline(in, rhs, ';'))
      break;
    varNames.push_back(lhs);
    varValues.push_back(rhs);
  }
  regex validVar("[a-zA-Z]+[_a-zA-Z0-9]*");
  regex validVal("[0-9].?[0-9]*");
  for (size_t i = 0, n = varValues.size(); i < n; ++i) {
    //if (regex_match(varNames[i], validVar)) {
    //varGood = true;
    //if (regex_match(varValues[i], validVal)) {
    //valGood = true;
    map<string, string>::iterator check = varMap.find(varNames[i]);
    if (check != varMap.end()) {
      check->second = varValues[i];
    } else {
      this->varMap.insert(pair<string, string>(varNames[i], varValues[i]));
    }
  }
}
    //if (varGood==false || valGood==false) {
      //cout << "\nillegal variable assignment! \n";
      //break;
    //}
  //}

/*
bool Interpreter::isValid(map<string, double> varMap) {
  regex validVar("[a-zA-Z]+[_a-zA-Z0-9]*");
  regex validVal("[0-9].?[0-9]+[0-9]*");
  map<string, double>::iterator itr;
  for (itr = varMap.begin(); itr != varMap.end(); ++itr) {
    if(regex_match(itr->first, validVar)){
      if(regex_match(to_string(itr->second),validVal)){
        return true;
      }
    }
  }
  return false;
}
*/

Expression* Interpreter::interpret(string str) {
  // Replacing in the string the var by their numberic value
  int counter = 0;
  string varBuffer[this->varMap.size()];
  for (int i = 0; i < str.length(); i++) {
    if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) {
      while (str[i] != '+' && str[i] != '-' && str[i] != '*' && str[i] != '/' && str[i] != '(' && str[i] != ')') {
        varBuffer[counter] += str[i];
        i++;
      }
      counter++;
    }
  }
  for (int j = 0; j < counter; j++) {
    if (this->varMap.find(varBuffer[j]) == varMap.end()) {
      throw "no such variable";
    } else {
      string var = varMap.find(varBuffer[j])->first;
      string value = varMap.find(varBuffer[j])->second;
      size_t position = str.find(var);
      str.replace(position, var.length(), value);
    }
  }
  // ShuntingYard
  stack<char> opStack;
  deque<char> valQueue;
  for (int i = 0; i < str.length(); i++) {
    char curr = str[i];
    if (isdigit(curr)) {
      valQueue.push_back(curr);
    } else if (curr == '+' || curr == '-' || curr == '*' || curr == '/') {
      if ((curr == '+' || curr == '-') && i == 0) {
        if (curr == '+') {
          curr = '$';
        } else {
          curr = '#';
        }
      } else if ((curr == '+' || curr == '-') && str[i - 1] == '(') {
        if (curr == '+') {
          curr = '$';
        } else {
          curr = '#';
        }
      }
      while (!opStack.empty() && isPrecedence(curr) < isPrecedence(opStack.top())) {
        valQueue.push_back(opStack.top());
        opStack.pop();
      }
      opStack.push(curr);
    }
    if (curr == '(') {
      opStack.push(curr);
    }
    if (curr == ')') {
      while (opStack.top() != '(') {
        valQueue.push_back(opStack.top());
        opStack.pop();
      }
      opStack.pop();
    }
  }
  while (!opStack.empty()) {
    valQueue.push_back(opStack.top());
    opStack.pop();
  }
  Expression *e = buildExpression(valQueue);
  return e;
}
// Priority of operators
int Interpreter::isPrecedence(char curr) {
  int priority = -27;
  switch(curr) {
    default: break;
    case '+': priority=1; break;
    case '-': priority=1; break;
    case '*': priority=2; break;
    case '/': priority=2; break;
    case '$': priority=3; break;
    case '#': priority=3; break;
  }
  return priority;
}
// Build expression
Expression* Interpreter::buildExpression(deque <char> postfix){
  stack<Expression*> expStack;
  char curr = postfix.front();
  string currStr(1,curr);
  while(!postfix.empty() && isdigit(currStr[0])) {
    double var = stod(currStr);
    expStack.push(new Value(var));
    postfix.pop_front();
    currStr = postfix.front();
  }
  while(!postfix.empty()) {
    if (currStr == "+" || currStr == "-" || currStr == "*" || currStr == "/") {
      Expression *right = expStack.top();
      expStack.pop();
      Expression *left = expStack.top();
      expStack.pop();
      if (currStr == "+") {
        Expression *plus = new Plus(left, right);
        expStack.push(plus);
      } else if (currStr == "-") {
        Expression *minus = new Minus(left, right);
        expStack.push(minus);
      } else if (currStr == "*") {
        Expression *mul = new Mul(left, right);
        expStack.push(mul);
      } else if (currStr == "/") {
        Expression *div = new Div(left, right);
        expStack.push(div);
      }
    } else if (currStr == "$" || currStr == "#") {
      Expression *one = expStack.top();
      expStack.pop();
      if (currStr == "$") {
        Expression *uplus = new UPlus(one);
        expStack.push(uplus);
      } else {
        Expression *uminus = new UMinus(one);
        expStack.push(uminus);
      }
    }
    postfix.pop_front();
    currStr = postfix.front();
  }
  return expStack.top();
}

