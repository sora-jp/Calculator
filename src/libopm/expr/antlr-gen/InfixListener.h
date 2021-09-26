
// Generated from Infix.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "InfixParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by InfixParser.
 */
class  InfixListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterEval(InfixParser::EvalContext *ctx) = 0;
  virtual void exitEval(InfixParser::EvalContext *ctx) = 0;

  virtual void enterExpression(InfixParser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(InfixParser::ExpressionContext *ctx) = 0;

  virtual void enterTerm(InfixParser::TermContext *ctx) = 0;
  virtual void exitTerm(InfixParser::TermContext *ctx) = 0;

  virtual void enterFactor(InfixParser::FactorContext *ctx) = 0;
  virtual void exitFactor(InfixParser::FactorContext *ctx) = 0;

  virtual void enterSecondary(InfixParser::SecondaryContext *ctx) = 0;
  virtual void exitSecondary(InfixParser::SecondaryContext *ctx) = 0;

  virtual void enterPrimary(InfixParser::PrimaryContext *ctx) = 0;
  virtual void exitPrimary(InfixParser::PrimaryContext *ctx) = 0;

  virtual void enterVariable(InfixParser::VariableContext *ctx) = 0;
  virtual void exitVariable(InfixParser::VariableContext *ctx) = 0;

  virtual void enterConstant(InfixParser::ConstantContext *ctx) = 0;
  virtual void exitConstant(InfixParser::ConstantContext *ctx) = 0;

  virtual void enterFunc(InfixParser::FuncContext *ctx) = 0;
  virtual void exitFunc(InfixParser::FuncContext *ctx) = 0;

  virtual void enterParams(InfixParser::ParamsContext *ctx) = 0;
  virtual void exitParams(InfixParser::ParamsContext *ctx) = 0;


};

