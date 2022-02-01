
// Generated from Infix.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"
#include "InfixListener.h"


/**
 * This class provides an empty implementation of InfixListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  InfixBaseListener : public InfixListener {
public:

  virtual void enterEval(InfixParser::EvalContext * /*ctx*/) override { }
  virtual void exitEval(InfixParser::EvalContext * /*ctx*/) override { }

  virtual void enterAssignment(InfixParser::AssignmentContext * /*ctx*/) override { }
  virtual void exitAssignment(InfixParser::AssignmentContext * /*ctx*/) override { }

  virtual void enterFunctionDef(InfixParser::FunctionDefContext * /*ctx*/) override { }
  virtual void exitFunctionDef(InfixParser::FunctionDefContext * /*ctx*/) override { }

  virtual void enterFuncWVars(InfixParser::FuncWVarsContext * /*ctx*/) override { }
  virtual void exitFuncWVars(InfixParser::FuncWVarsContext * /*ctx*/) override { }

  virtual void enterExpression(InfixParser::ExpressionContext * /*ctx*/) override { }
  virtual void exitExpression(InfixParser::ExpressionContext * /*ctx*/) override { }

  virtual void enterTerm(InfixParser::TermContext * /*ctx*/) override { }
  virtual void exitTerm(InfixParser::TermContext * /*ctx*/) override { }

  virtual void enterFactor(InfixParser::FactorContext * /*ctx*/) override { }
  virtual void exitFactor(InfixParser::FactorContext * /*ctx*/) override { }

  virtual void enterSecondary(InfixParser::SecondaryContext * /*ctx*/) override { }
  virtual void exitSecondary(InfixParser::SecondaryContext * /*ctx*/) override { }

  virtual void enterPrimary(InfixParser::PrimaryContext * /*ctx*/) override { }
  virtual void exitPrimary(InfixParser::PrimaryContext * /*ctx*/) override { }

  virtual void enterVariable(InfixParser::VariableContext * /*ctx*/) override { }
  virtual void exitVariable(InfixParser::VariableContext * /*ctx*/) override { }

  virtual void enterHistref(InfixParser::HistrefContext * /*ctx*/) override { }
  virtual void exitHistref(InfixParser::HistrefContext * /*ctx*/) override { }

  virtual void enterConstant(InfixParser::ConstantContext * /*ctx*/) override { }
  virtual void exitConstant(InfixParser::ConstantContext * /*ctx*/) override { }

  virtual void enterFunc(InfixParser::FuncContext * /*ctx*/) override { }
  virtual void exitFunc(InfixParser::FuncContext * /*ctx*/) override { }

  virtual void enterParams(InfixParser::ParamsContext * /*ctx*/) override { }
  virtual void exitParams(InfixParser::ParamsContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

