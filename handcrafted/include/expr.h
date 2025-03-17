#include "token.h"
#include <iostream>
struct Expr;
struct Unary;
struct Binary;
struct Grouping;
struct Literal;
class Visitor
{
public:
    std::string visitBinary(Binary expr);
    std::string visitUnary(Unary expr);
    std::string visitLiteral(Literal expr);
    std::string visitGrouping(Grouping expr);
    std::string parenthesize(std::string name, std::vector<Expr*> exprs);
};
typedef struct Expr
{
public:
    virtual std::string accept(Visitor &visitor) {
        return "";
    };
} Expr;

typedef struct Unary : public Expr
{
    Token op;
    Expr* right;
    Unary(Token op, Expr* right) : op(op), right(right) {}
    std::string accept(Visitor &visitor) override
    {
        return visitor.visitUnary(*this);
    }
} Unary;

typedef struct Binary : public Expr
{
    Expr* left;
    Token op;
    Expr* right;
    Binary(Expr* left, Token op, Expr* right) : left(left), op(op), right(right) {}
    std::string accept(Visitor &visitor) override
    {
        return visitor.visitBinary(*this);
    }
} Binary;

typedef struct Grouping : public Expr
{
    Expr* expression;
    Grouping(Expr* expression) : expression(expression) {}
    std::string accept(Visitor &visitor) override
    {
        return visitor.visitGrouping(*this);
    }
} Grouping;

typedef struct Literal : public Expr
{
    std::string value;
    Literal(std::string value) : value(value) {}
    std::string accept(Visitor &visitor) override
    {
        return visitor.visitLiteral(*this);
    }
} Literal;

std::string Visitor::visitUnary(Unary expr)
{
    std::vector<Expr*> args = {expr.right};
    return parenthesize(std::string(expr.op.lexeme), args);
}
std::string Visitor::visitBinary(Binary expr)
{
    std::vector<Expr*> args = {expr.right, expr.left};
    return parenthesize(std::string(expr.op.lexeme), args);
}
std::string Visitor::visitGrouping(Grouping expr)
{
    std::vector<Expr*> args = {expr.expression};
    return parenthesize("group", args);
}
std::string Visitor::visitLiteral(Literal expr)
{
    return expr.value;
}
std::string Visitor::parenthesize(std::string name, std::vector<Expr*> exprs)
{
    std::string val = "";
    val += "( " + name;
    for (auto expr : exprs)
    {
        val += " ";
        val += expr->accept(*this);
    }
    val += ")";
    return val;
}