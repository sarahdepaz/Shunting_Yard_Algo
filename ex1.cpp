#include "Expression.h"
#include "ex1.h"
#include <string>

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




