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
#include <queue>
//using namespace std;
Expression* BinaryOperator :: getLeft() {
  return this->left;
}
Expression* BinaryOperator :: getRight() {
  return this->right;
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
  if (this->getRight()->calculate() == 0) {
    throw "division by zero";
  }
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
void Interpreter::setVariables (string givenString) {
  string buffer, sLeft, sRight, varName;
  bool flag = false;
  for (unsigned int i = 0; i < givenString.length(); i++) {
    if (givenString[i] == ';') {
      for (unsigned int j = 0; j < buffer.length(); j++) {
        if (buffer[j] == '=') {
          sLeft = varName;
          varName = "";
          flag = true;
        }
        else if (flag) {
          sRight += buffer[j];
        }
        else {
          varName += buffer[j];
        }
      }
      this->varMap.insert(pair<string, string>(sLeft, sRight));
      flag = false;
      buffer = "";
      sRight="";
    }
    else {
      buffer += givenString[i];
    }
  }
  if(givenString[givenString.length()-1] != ';') {
    for (unsigned int j = 0; j < buffer.length(); j++) {
      if (buffer[j] == '=') {
        sLeft = varName;
        varName = "";
        flag = true;
      }
      else if (flag) {
        sRight +=  buffer[j];
      }
      else {
        varName += buffer[j];
      }
    }
    map<string,string>::iterator duplicated = varMap.find(sLeft);
    if(duplicated != varMap.end()){
      duplicated->second = sRight;
    }
    else {
      this->varMap.insert(pair<string, string>(sLeft, sRight));
    }
  }
}

/*
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
  regex validVal("-?[0-9].?[0-9]*");
  varGood = false;
  valGood = false;
  for (size_t i = 0, n = varValues.size(); i < n; ++i) {
    if (regex_match(varNames[i], validVar)) {
      varGood = true;
      if (regex_match(varValues[i], validVal)) {
        valGood = true;
        map<string, string>::iterator check = varMap.find(varNames[i]);
        if (check != varMap.end()) {
          check->second = varValues[i];
        } else {
          this->varMap.insert(pair<string, string>(varNames[i], varValues[i]));
        }
      }
    }
    if (varGood == false || valGood == false) {
      cout << "\nillegal variable assignment! \n";
    }
  }
}
 */

/*
bool Interpreter::isValid(map<string, double> varMap) {
  regex validVar("[a-zA-Z]+[_a-zA-Z0-9]*");
  regex validVal("-?[0-9].?[0-9]+[0-9]*");
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
bool Interpreter::isChar(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
Expression* Interpreter::interpret(string str) {
  stack <string> opStack;
  deque <string> valueQ;
  // Replacing in the string the var by their numeric value
  unsigned int counter = 0;
  string varBuffer[20];
  for (unsigned int i = 0; i < str.length(); i++) {
    if (isChar(str[i])) {
      while (str[i] != '+' && str[i] != '-' && str[i] != '*' && str[i] != '/' && str[i] != '(' && str[i] != ')') {
        varBuffer[counter] += str[i];
        i++;
      }
      counter++;
    }
  }
  for (unsigned int j = 0; j < counter; j++) {
    if (this->varMap.find(varBuffer[j]) == varMap.end()) {
      throw "illegal variable assignment!";
    } else {
      string var = varMap.find(varBuffer[j])->first;
      string value = varMap.find(varBuffer[j])->second;
      size_t position = str.find(var);
      str.replace(position, var.length(), value);
    }
  }
  // Shunting Yard
  for(unsigned int i=0; i<str.length(); i++) {
    string buffer = "";
    char currChar = str[i];
    string strCurr(1, currChar);
    bool variableFlag = false;
    while (!isOperator(strCurr) && i < str.length()) {
      variableFlag = true;
      buffer += strCurr;
      i++;
      currChar = str[i];
      strCurr = currChar;
    }
    if(variableFlag) {
      valueQ.push_back(buffer);
      variableFlag = false;
    }
    if(strCurr == "+" || strCurr == "-" || strCurr == "*" || strCurr == "/") {
      // Unary
      if((strCurr=="+" || strCurr=="-") && i==0) {
        if(strCurr=="+") {
          strCurr="$";
        }
        else {
          strCurr="#";
        }
      }
      else if ((strCurr=="+" || strCurr=="-") && str[i-1]=='(') {
        if(strCurr =="+") {
          strCurr="$";
        }
        else {
          strCurr="#";
        }
      }
      while(!opStack.empty() && isPrecedence(strCurr)< isPrecedence(opStack.top())) {
        valueQ.push_back(opStack.top());
        opStack.pop();
      }
      opStack.push(strCurr);
    }
    if(strCurr == "(") {
      opStack.push(strCurr);
    }
    if(strCurr == ")") {
      while(opStack.top()!="(") {
        valueQ.push_back(opStack.top());
        opStack.pop();
      }
      opStack.pop();
    }
  }
  while(!opStack.empty()) {
    valueQ.push_back(opStack.top());
    opStack.pop();
  }
  Expression* e = buildExpression(valueQ);
  return e;
}
// Is an operator
bool Interpreter::isOperator(string operatorC) {
  return operatorC == "+" || operatorC == "-" || operatorC == "*" || operatorC == "/" || operatorC == "$" || operatorC == "#" || operatorC == "(" || operatorC == ")";
}
// Priority of operators
int Interpreter::isPrecedence(string str) {
  int priority = -27;
  char curr = str[0];
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
Expression* Interpreter::buildExpression(deque <string> postfix) {
  stack<Expression*> expStack;
  string currStr;
  while(!postfix.empty()) {
    currStr = postfix.front();
    postfix.pop_front();
    if(!isOperator(currStr)) {
      double var = stod(currStr);
      expStack.push(new Value(var));
    }
    else if (currStr == "+" || currStr == "-" || currStr == "*" || currStr == "/") {
      Expression *right = expStack.top();
      expStack.pop();
      Expression *left = expStack.top();
      expStack.pop();
      if (currStr == "+") {
        Expression* plus = new Plus(left, right);
        expStack.push(plus);
      } else if (currStr == "-") {
        Expression* minus = new Minus(left, right);
        expStack.push(minus);
      } else if (currStr == "*") {
        Expression* mult = new Mul(left, right);
        expStack.push(mult);
      } else if (currStr == "/") {
        Expression* div = new Div(left, right);
        expStack.push(div);
      }
    } else if (currStr == "$" || currStr == "#") {
      Expression *one = expStack.top();
      expStack.pop();
      if (currStr == "$") {
        Expression* uplus = new UPlus(one);
        expStack.push(uplus);
      } else {
        Expression* uminus = new UMinus(one);
        expStack.push(uminus);
      }
    }
  }
  return expStack.top();
}
