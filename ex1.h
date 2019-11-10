#ifndef EX1_ALL_IN_ONE_EX1_H
#define EX1_ALL_IN_ONE_EX1_H
#include "string"
#include "Expression.h"
class BinaryOperator : public Expression {
    Expression* left {nullptr};
    Expression* right {nullptr};
protected:
    BinaryOperator(Expression *left, Expression *right) : left(left), right
            (right) {}
    Expression* getLeft();
    Expression* getRight();
public:
    void setRight(Expression* r);
    void setLeft(Expression* l);
};
class Plus : public BinaryOperator {
public:
    Plus(Expression *left, Expression *right) : BinaryOperator(right,left){}
    double calculate() override;
};
class Minus : public BinaryOperator {
public:
    Minus(Expression *left, Expression *right) : BinaryOperator(right,left){}
    double calculate() override ;
};
class Mul : public BinaryOperator {
public:
    Mul(Expression *left, Expression *right) : BinaryOperator(right,left){}
    double calculate() override;
};
class Div : public BinaryOperator {
public:
    Div(Expression *left, Expression *right) : BinaryOperator(right,left){}
    double calculate() override;
};
class Variable : public Expression {
private:
    string name;
    double value;
public:
    double calculate() override;
    Variable(string name, double value) : name(name), value(value) {}
    Variable& operator+=(double plusEqual);
    Variable& operator-=(double minusEqual);
    Variable& operator--();
    Variable& operator--(int);
    // Prefix
    Variable& operator++();
    // Postfix
    //todo check with daniela
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
    explicit UnaryOperator(Expression* exp) : exp(exp) {}
    Expression* getExp();
    void setExp(Expression* e);
};
class UPlus : public UnaryOperator {
protected:
    Expression* exp {nullptr};
public:
    explicit UPlus(Expression *exp) : UnaryOperator(exp){}
    double calculate() override;
};
class UMinus : public UnaryOperator {
protected:
    Expression* exp {nullptr};
public:
    explicit UMinus(Expression *exp) : UnaryOperator(exp){}
    double calculate() override;
};

#endif //EX1_ALL_IN_ONE_EX1_H