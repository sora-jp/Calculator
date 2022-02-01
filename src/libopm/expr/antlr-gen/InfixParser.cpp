
// Generated from Infix.g4 by ANTLR 4.9.2


#include "InfixListener.h"

#include "InfixParser.h"


using namespace antlrcpp;
using namespace antlr4;

InfixParser::InfixParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

InfixParser::~InfixParser() {
  delete _interpreter;
}

std::string InfixParser::getGrammarFileName() const {
  return "Infix.g4";
}

const std::vector<std::string>& InfixParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& InfixParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- EvalContext ------------------------------------------------------------------

InfixParser::EvalContext::EvalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

InfixParser::ExpressionContext* InfixParser::EvalContext::expression() {
  return getRuleContext<InfixParser::ExpressionContext>(0);
}

InfixParser::AssignmentContext* InfixParser::EvalContext::assignment() {
  return getRuleContext<InfixParser::AssignmentContext>(0);
}

InfixParser::FunctionDefContext* InfixParser::EvalContext::functionDef() {
  return getRuleContext<InfixParser::FunctionDefContext>(0);
}


size_t InfixParser::EvalContext::getRuleIndex() const {
  return InfixParser::RuleEval;
}

void InfixParser::EvalContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InfixListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEval(this);
}

void InfixParser::EvalContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InfixListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEval(this);
}

InfixParser::EvalContext* InfixParser::eval() {
  EvalContext *_localctx = _tracker.createInstance<EvalContext>(_ctx, getState());
  enterRule(_localctx, 0, InfixParser::RuleEval);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(31);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(28);
      expression(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(29);
      assignment();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(30);
      functionDef();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentContext ------------------------------------------------------------------

InfixParser::AssignmentContext::AssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

InfixParser::VariableContext* InfixParser::AssignmentContext::variable() {
  return getRuleContext<InfixParser::VariableContext>(0);
}

tree::TerminalNode* InfixParser::AssignmentContext::EQUALS() {
  return getToken(InfixParser::EQUALS, 0);
}

InfixParser::ExpressionContext* InfixParser::AssignmentContext::expression() {
  return getRuleContext<InfixParser::ExpressionContext>(0);
}


size_t InfixParser::AssignmentContext::getRuleIndex() const {
  return InfixParser::RuleAssignment;
}

void InfixParser::AssignmentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InfixListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignment(this);
}

void InfixParser::AssignmentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InfixListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignment(this);
}

InfixParser::AssignmentContext* InfixParser::assignment() {
  AssignmentContext *_localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
  enterRule(_localctx, 2, InfixParser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(33);
    variable();
    setState(34);
    match(InfixParser::EQUALS);
    setState(35);
    expression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDefContext ------------------------------------------------------------------

InfixParser::FunctionDefContext::FunctionDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

InfixParser::FuncWVarsContext* InfixParser::FunctionDefContext::funcWVars() {
  return getRuleContext<InfixParser::FuncWVarsContext>(0);
}

tree::TerminalNode* InfixParser::FunctionDefContext::EQUALS() {
  return getToken(InfixParser::EQUALS, 0);
}

InfixParser::ExpressionContext* InfixParser::FunctionDefContext::expression() {
  return getRuleContext<InfixParser::ExpressionContext>(0);
}


size_t InfixParser::FunctionDefContext::getRuleIndex() const {
  return InfixParser::RuleFunctionDef;
}

void InfixParser::FunctionDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InfixListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionDef(this);
}

void InfixParser::FunctionDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InfixListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionDef(this);
}

InfixParser::FunctionDefContext* InfixParser::functionDef() {
  FunctionDefContext *_localctx = _tracker.createInstance<FunctionDefContext>(_ctx, getState());
  enterRule(_localctx, 4, InfixParser::RuleFunctionDef);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(37);
    funcWVars();
    setState(38);
    match(InfixParser::EQUALS);
    setState(39);
    expression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncWVarsContext ------------------------------------------------------------------

InfixParser::FuncWVarsContext::FuncWVarsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* InfixParser::FuncWVarsContext::ID() {
  return getToken(InfixParser::ID, 0);
}

tree::TerminalNode* InfixParser::FuncWVarsContext::LPAREN() {
  return getToken(InfixParser::LPAREN, 0);
}

std::vector<InfixParser::VariableContext *> InfixParser::FuncWVarsContext::variable() {
  return getRuleContexts<InfixParser::VariableContext>();
}

InfixParser::VariableContext* InfixParser::FuncWVarsContext::variable(size_t i) {
  return getRuleContext<InfixParser::VariableContext>(i);
}

tree::TerminalNode* InfixParser::FuncWVarsContext::RPAREN() {
  return getToken(InfixParser::RPAREN, 0);
}

std::vector<tree::TerminalNode *> InfixParser::FuncWVarsContext::COMMA() {
  return getTokens(InfixParser::COMMA);
}

tree::TerminalNode* InfixParser::FuncWVarsContext::COMMA(size_t i) {
  return getToken(InfixParser::COMMA, i);
}


size_t InfixParser::FuncWVarsContext::getRuleIndex() const {
  return InfixParser::RuleFuncWVars;
}

void InfixParser::FuncWVarsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InfixListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncWVars(this);
}

void InfixParser::FuncWVarsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InfixListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncWVars(this);
}

InfixParser::FuncWVarsContext* InfixParser::funcWVars() {
  FuncWVarsContext *_localctx = _tracker.createInstance<FuncWVarsContext>(_ctx, getState());
  enterRule(_localctx, 6, InfixParser::RuleFuncWVars);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    setState(58);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(41);
      match(InfixParser::ID);
      setState(42);
      match(InfixParser::LPAREN);
      setState(43);
      variable();
      setState(44);
      match(InfixParser::RPAREN);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(46);
      match(InfixParser::ID);
      setState(47);
      match(InfixParser::LPAREN);
      setState(51); 
      _errHandler->sync(this);
      alt = 1;
      do {
        switch (alt) {
          case 1: {
                setState(48);
                variable();
                setState(49);
                match(InfixParser::COMMA);
                break;
              }

        default:
          throw NoViableAltException(this);
        }
        setState(53); 
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
      } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
      setState(55);
      variable();
      setState(56);
      match(InfixParser::RPAREN);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

InfixParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

InfixParser::TermContext* InfixParser::ExpressionContext::term() {
  return getRuleContext<InfixParser::TermContext>(0);
}

InfixParser::ExpressionContext* InfixParser::ExpressionContext::expression() {
  return getRuleContext<InfixParser::ExpressionContext>(0);
}

tree::TerminalNode* InfixParser::ExpressionContext::PLUS() {
  return getToken(InfixParser::PLUS, 0);
}

tree::TerminalNode* InfixParser::ExpressionContext::MINUS() {
  return getToken(InfixParser::MINUS, 0);
}


size_t InfixParser::ExpressionContext::getRuleIndex() const {
  return InfixParser::RuleExpression;
}

void InfixParser::ExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InfixListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpression(this);
}

void InfixParser::ExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InfixListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpression(this);
}


InfixParser::ExpressionContext* InfixParser::expression() {
   return expression(0);
}

InfixParser::ExpressionContext* InfixParser::expression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  InfixParser::ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, parentState);
  InfixParser::ExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 8;
  enterRecursionRule(_localctx, 8, InfixParser::RuleExpression, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(61);
    term(0);
    _ctx->stop = _input->LT(-1);
    setState(71);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(69);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(63);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(64);
          match(InfixParser::PLUS);
          setState(65);
          term(0);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(66);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(67);
          match(InfixParser::MINUS);
          setState(68);
          term(0);
          break;
        }

        default:
          break;
        } 
      }
      setState(73);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- TermContext ------------------------------------------------------------------

InfixParser::TermContext::TermContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

InfixParser::FactorContext* InfixParser::TermContext::factor() {
  return getRuleContext<InfixParser::FactorContext>(0);
}

InfixParser::TermContext* InfixParser::TermContext::term() {
  return getRuleContext<InfixParser::TermContext>(0);
}

tree::TerminalNode* InfixParser::TermContext::MULT() {
  return getToken(InfixParser::MULT, 0);
}

tree::TerminalNode* InfixParser::TermContext::DIV() {
  return getToken(InfixParser::DIV, 0);
}

tree::TerminalNode* InfixParser::TermContext::MOD() {
  return getToken(InfixParser::MOD, 0);
}


size_t InfixParser::TermContext::getRuleIndex() const {
  return InfixParser::RuleTerm;
}

void InfixParser::TermContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InfixListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTerm(this);
}

void InfixParser::TermContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InfixListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTerm(this);
}


InfixParser::TermContext* InfixParser::term() {
   return term(0);
}

InfixParser::TermContext* InfixParser::term(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  InfixParser::TermContext *_localctx = _tracker.createInstance<TermContext>(_ctx, parentState);
  InfixParser::TermContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 10;
  enterRecursionRule(_localctx, 10, InfixParser::RuleTerm, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(75);
    factor();
    _ctx->stop = _input->LT(-1);
    setState(88);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(86);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<TermContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTerm);
          setState(77);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(78);
          match(InfixParser::MULT);
          setState(79);
          factor();
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<TermContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTerm);
          setState(80);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(81);
          match(InfixParser::DIV);
          setState(82);
          factor();
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<TermContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTerm);
          setState(83);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(84);
          match(InfixParser::MOD);
          setState(85);
          factor();
          break;
        }

        default:
          break;
        } 
      }
      setState(90);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- FactorContext ------------------------------------------------------------------

InfixParser::FactorContext::FactorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

InfixParser::SecondaryContext* InfixParser::FactorContext::secondary() {
  return getRuleContext<InfixParser::SecondaryContext>(0);
}

tree::TerminalNode* InfixParser::FactorContext::MINUS() {
  return getToken(InfixParser::MINUS, 0);
}

InfixParser::FactorContext* InfixParser::FactorContext::factor() {
  return getRuleContext<InfixParser::FactorContext>(0);
}

tree::TerminalNode* InfixParser::FactorContext::PLUS() {
  return getToken(InfixParser::PLUS, 0);
}


size_t InfixParser::FactorContext::getRuleIndex() const {
  return InfixParser::RuleFactor;
}

void InfixParser::FactorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InfixListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFactor(this);
}

void InfixParser::FactorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InfixListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFactor(this);
}

InfixParser::FactorContext* InfixParser::factor() {
  FactorContext *_localctx = _tracker.createInstance<FactorContext>(_ctx, getState());
  enterRule(_localctx, 12, InfixParser::RuleFactor);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(96);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case InfixParser::LPAREN:
      case InfixParser::LBRACK:
      case InfixParser::INTEGER:
      case InfixParser::NUMBER:
      case InfixParser::IINTEGER:
      case InfixParser::INUMBER:
      case InfixParser::ID: {
        enterOuterAlt(_localctx, 1);
        setState(91);
        secondary(0);
        break;
      }

      case InfixParser::MINUS: {
        enterOuterAlt(_localctx, 2);
        setState(92);
        match(InfixParser::MINUS);
        setState(93);
        factor();
        break;
      }

      case InfixParser::PLUS: {
        enterOuterAlt(_localctx, 3);
        setState(94);
        match(InfixParser::PLUS);
        setState(95);
        factor();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SecondaryContext ------------------------------------------------------------------

InfixParser::SecondaryContext::SecondaryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

InfixParser::PrimaryContext* InfixParser::SecondaryContext::primary() {
  return getRuleContext<InfixParser::PrimaryContext>(0);
}

InfixParser::SecondaryContext* InfixParser::SecondaryContext::secondary() {
  return getRuleContext<InfixParser::SecondaryContext>(0);
}

tree::TerminalNode* InfixParser::SecondaryContext::POW() {
  return getToken(InfixParser::POW, 0);
}

InfixParser::FactorContext* InfixParser::SecondaryContext::factor() {
  return getRuleContext<InfixParser::FactorContext>(0);
}


size_t InfixParser::SecondaryContext::getRuleIndex() const {
  return InfixParser::RuleSecondary;
}

void InfixParser::SecondaryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InfixListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSecondary(this);
}

void InfixParser::SecondaryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InfixListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSecondary(this);
}


InfixParser::SecondaryContext* InfixParser::secondary() {
   return secondary(0);
}

InfixParser::SecondaryContext* InfixParser::secondary(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  InfixParser::SecondaryContext *_localctx = _tracker.createInstance<SecondaryContext>(_ctx, parentState);
  InfixParser::SecondaryContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 14;
  enterRecursionRule(_localctx, 14, InfixParser::RuleSecondary, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(99);
    primary();
    _ctx->stop = _input->LT(-1);
    setState(106);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<SecondaryContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleSecondary);
        setState(101);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(102);
        match(InfixParser::POW);
        setState(103);
        factor(); 
      }
      setState(108);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- PrimaryContext ------------------------------------------------------------------

InfixParser::PrimaryContext::PrimaryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

InfixParser::FuncContext* InfixParser::PrimaryContext::func() {
  return getRuleContext<InfixParser::FuncContext>(0);
}

InfixParser::HistrefContext* InfixParser::PrimaryContext::histref() {
  return getRuleContext<InfixParser::HistrefContext>(0);
}

InfixParser::VariableContext* InfixParser::PrimaryContext::variable() {
  return getRuleContext<InfixParser::VariableContext>(0);
}

InfixParser::ConstantContext* InfixParser::PrimaryContext::constant() {
  return getRuleContext<InfixParser::ConstantContext>(0);
}

tree::TerminalNode* InfixParser::PrimaryContext::LPAREN() {
  return getToken(InfixParser::LPAREN, 0);
}

InfixParser::ExpressionContext* InfixParser::PrimaryContext::expression() {
  return getRuleContext<InfixParser::ExpressionContext>(0);
}

tree::TerminalNode* InfixParser::PrimaryContext::RPAREN() {
  return getToken(InfixParser::RPAREN, 0);
}


size_t InfixParser::PrimaryContext::getRuleIndex() const {
  return InfixParser::RulePrimary;
}

void InfixParser::PrimaryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InfixListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimary(this);
}

void InfixParser::PrimaryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InfixListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimary(this);
}

InfixParser::PrimaryContext* InfixParser::primary() {
  PrimaryContext *_localctx = _tracker.createInstance<PrimaryContext>(_ctx, getState());
  enterRule(_localctx, 16, InfixParser::RulePrimary);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(117);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(109);
      func();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(110);
      histref();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(111);
      variable();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(112);
      constant();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(113);
      match(InfixParser::LPAREN);
      setState(114);
      expression(0);
      setState(115);
      match(InfixParser::RPAREN);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableContext ------------------------------------------------------------------

InfixParser::VariableContext::VariableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* InfixParser::VariableContext::ID() {
  return getToken(InfixParser::ID, 0);
}


size_t InfixParser::VariableContext::getRuleIndex() const {
  return InfixParser::RuleVariable;
}

void InfixParser::VariableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InfixListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariable(this);
}

void InfixParser::VariableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InfixListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariable(this);
}

InfixParser::VariableContext* InfixParser::variable() {
  VariableContext *_localctx = _tracker.createInstance<VariableContext>(_ctx, getState());
  enterRule(_localctx, 18, InfixParser::RuleVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(119);
    match(InfixParser::ID);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- HistrefContext ------------------------------------------------------------------

InfixParser::HistrefContext::HistrefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* InfixParser::HistrefContext::LBRACK() {
  return getToken(InfixParser::LBRACK, 0);
}

tree::TerminalNode* InfixParser::HistrefContext::INTEGER() {
  return getToken(InfixParser::INTEGER, 0);
}

tree::TerminalNode* InfixParser::HistrefContext::RBRACK() {
  return getToken(InfixParser::RBRACK, 0);
}


size_t InfixParser::HistrefContext::getRuleIndex() const {
  return InfixParser::RuleHistref;
}

void InfixParser::HistrefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InfixListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterHistref(this);
}

void InfixParser::HistrefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InfixListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitHistref(this);
}

InfixParser::HistrefContext* InfixParser::histref() {
  HistrefContext *_localctx = _tracker.createInstance<HistrefContext>(_ctx, getState());
  enterRule(_localctx, 20, InfixParser::RuleHistref);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(121);
    match(InfixParser::LBRACK);
    setState(122);
    match(InfixParser::INTEGER);
    setState(123);
    match(InfixParser::RBRACK);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstantContext ------------------------------------------------------------------

InfixParser::ConstantContext::ConstantContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* InfixParser::ConstantContext::NUMBER() {
  return getToken(InfixParser::NUMBER, 0);
}

tree::TerminalNode* InfixParser::ConstantContext::INTEGER() {
  return getToken(InfixParser::INTEGER, 0);
}

tree::TerminalNode* InfixParser::ConstantContext::INUMBER() {
  return getToken(InfixParser::INUMBER, 0);
}

tree::TerminalNode* InfixParser::ConstantContext::IINTEGER() {
  return getToken(InfixParser::IINTEGER, 0);
}


size_t InfixParser::ConstantContext::getRuleIndex() const {
  return InfixParser::RuleConstant;
}

void InfixParser::ConstantContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InfixListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstant(this);
}

void InfixParser::ConstantContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InfixListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstant(this);
}

InfixParser::ConstantContext* InfixParser::constant() {
  ConstantContext *_localctx = _tracker.createInstance<ConstantContext>(_ctx, getState());
  enterRule(_localctx, 22, InfixParser::RuleConstant);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(125);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << InfixParser::INTEGER)
      | (1ULL << InfixParser::NUMBER)
      | (1ULL << InfixParser::IINTEGER)
      | (1ULL << InfixParser::INUMBER))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncContext ------------------------------------------------------------------

InfixParser::FuncContext::FuncContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* InfixParser::FuncContext::ID() {
  return getToken(InfixParser::ID, 0);
}

InfixParser::ParamsContext* InfixParser::FuncContext::params() {
  return getRuleContext<InfixParser::ParamsContext>(0);
}


size_t InfixParser::FuncContext::getRuleIndex() const {
  return InfixParser::RuleFunc;
}

void InfixParser::FuncContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InfixListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunc(this);
}

void InfixParser::FuncContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InfixListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunc(this);
}

InfixParser::FuncContext* InfixParser::func() {
  FuncContext *_localctx = _tracker.createInstance<FuncContext>(_ctx, getState());
  enterRule(_localctx, 24, InfixParser::RuleFunc);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(127);
    match(InfixParser::ID);
    setState(128);
    params();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParamsContext ------------------------------------------------------------------

InfixParser::ParamsContext::ParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* InfixParser::ParamsContext::LPAREN() {
  return getToken(InfixParser::LPAREN, 0);
}

std::vector<InfixParser::ExpressionContext *> InfixParser::ParamsContext::expression() {
  return getRuleContexts<InfixParser::ExpressionContext>();
}

InfixParser::ExpressionContext* InfixParser::ParamsContext::expression(size_t i) {
  return getRuleContext<InfixParser::ExpressionContext>(i);
}

tree::TerminalNode* InfixParser::ParamsContext::RPAREN() {
  return getToken(InfixParser::RPAREN, 0);
}

std::vector<tree::TerminalNode *> InfixParser::ParamsContext::COMMA() {
  return getTokens(InfixParser::COMMA);
}

tree::TerminalNode* InfixParser::ParamsContext::COMMA(size_t i) {
  return getToken(InfixParser::COMMA, i);
}


size_t InfixParser::ParamsContext::getRuleIndex() const {
  return InfixParser::RuleParams;
}

void InfixParser::ParamsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InfixListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParams(this);
}

void InfixParser::ParamsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<InfixListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParams(this);
}

InfixParser::ParamsContext* InfixParser::params() {
  ParamsContext *_localctx = _tracker.createInstance<ParamsContext>(_ctx, getState());
  enterRule(_localctx, 26, InfixParser::RuleParams);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    setState(145);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(130);
      match(InfixParser::LPAREN);
      setState(131);
      expression(0);
      setState(132);
      match(InfixParser::RPAREN);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(134);
      match(InfixParser::LPAREN);
      setState(138); 
      _errHandler->sync(this);
      alt = 1;
      do {
        switch (alt) {
          case 1: {
                setState(135);
                expression(0);
                setState(136);
                match(InfixParser::COMMA);
                break;
              }

        default:
          throw NoViableAltException(this);
        }
        setState(140); 
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
      } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
      setState(142);
      expression(0);
      setState(143);
      match(InfixParser::RPAREN);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool InfixParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 4: return expressionSempred(dynamic_cast<ExpressionContext *>(context), predicateIndex);
    case 5: return termSempred(dynamic_cast<TermContext *>(context), predicateIndex);
    case 7: return secondarySempred(dynamic_cast<SecondaryContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool InfixParser::expressionSempred(ExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 2);
    case 1: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool InfixParser::termSempred(TermContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 3);
    case 3: return precpred(_ctx, 2);
    case 4: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool InfixParser::secondarySempred(SecondaryContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 5: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> InfixParser::_decisionToDFA;
atn::PredictionContextCache InfixParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN InfixParser::_atn;
std::vector<uint16_t> InfixParser::_serializedATN;

std::vector<std::string> InfixParser::_ruleNames = {
  "eval", "assignment", "functionDef", "funcWVars", "expression", "term", 
  "factor", "secondary", "primary", "variable", "histref", "constant", "func", 
  "params"
};

std::vector<std::string> InfixParser::_literalNames = {
  "", "'*'", "'/'", "'%'", "'+'", "'-'", "'.'", "'^'", "','", "'='", "'('", 
  "')'", "'['", "']'"
};

std::vector<std::string> InfixParser::_symbolicNames = {
  "", "MULT", "DIV", "MOD", "PLUS", "MINUS", "DOT", "POW", "COMMA", "EQUALS", 
  "LPAREN", "RPAREN", "LBRACK", "RBRACK", "INTEGER", "NUMBER", "IINTEGER", 
  "INUMBER", "ID", "COMMENT", "WS"
};

dfa::Vocabulary InfixParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> InfixParser::_tokenNames;

InfixParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  static const uint16_t serializedATNSegment0[] = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
       0x3, 0x16, 0x96, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
       0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 
       0x7, 0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 
       0x4, 0xb, 0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 
       0xe, 0x9, 0xe, 0x4, 0xf, 0x9, 0xf, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 
       0x5, 0x2, 0x22, 0xa, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
       0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 
       0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 
       0x3, 0x5, 0x6, 0x5, 0x36, 0xa, 0x5, 0xd, 0x5, 0xe, 0x5, 0x37, 0x3, 
       0x5, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x3d, 0xa, 0x5, 0x3, 0x6, 0x3, 
       0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 
       0x3, 0x6, 0x7, 0x6, 0x48, 0xa, 0x6, 0xc, 0x6, 0xe, 0x6, 0x4b, 0xb, 
       0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
       0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x7, 
       0x7, 0x59, 0xa, 0x7, 0xc, 0x7, 0xe, 0x7, 0x5c, 0xb, 0x7, 0x3, 0x8, 
       0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0x63, 0xa, 0x8, 
       0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x7, 
       0x9, 0x6b, 0xa, 0x9, 0xc, 0x9, 0xe, 0x9, 0x6e, 0xb, 0x9, 0x3, 0xa, 
       0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
       0xa, 0x5, 0xa, 0x78, 0xa, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 
       0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 
       0x3, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 
       0xf, 0x3, 0xf, 0x3, 0xf, 0x6, 0xf, 0x8d, 0xa, 0xf, 0xd, 0xf, 0xe, 
       0xf, 0x8e, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x5, 0xf, 0x94, 0xa, 0xf, 
       0x3, 0xf, 0x2, 0x5, 0xa, 0xc, 0x10, 0x10, 0x2, 0x4, 0x6, 0x8, 0xa, 
       0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x2, 0x3, 0x3, 
       0x2, 0x10, 0x13, 0x2, 0x99, 0x2, 0x21, 0x3, 0x2, 0x2, 0x2, 0x4, 0x23, 
       0x3, 0x2, 0x2, 0x2, 0x6, 0x27, 0x3, 0x2, 0x2, 0x2, 0x8, 0x3c, 0x3, 
       0x2, 0x2, 0x2, 0xa, 0x3e, 0x3, 0x2, 0x2, 0x2, 0xc, 0x4c, 0x3, 0x2, 
       0x2, 0x2, 0xe, 0x62, 0x3, 0x2, 0x2, 0x2, 0x10, 0x64, 0x3, 0x2, 0x2, 
       0x2, 0x12, 0x77, 0x3, 0x2, 0x2, 0x2, 0x14, 0x79, 0x3, 0x2, 0x2, 0x2, 
       0x16, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x18, 0x7f, 0x3, 0x2, 0x2, 0x2, 0x1a, 
       0x81, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x93, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x22, 
       0x5, 0xa, 0x6, 0x2, 0x1f, 0x22, 0x5, 0x4, 0x3, 0x2, 0x20, 0x22, 0x5, 
       0x6, 0x4, 0x2, 0x21, 0x1e, 0x3, 0x2, 0x2, 0x2, 0x21, 0x1f, 0x3, 0x2, 
       0x2, 0x2, 0x21, 0x20, 0x3, 0x2, 0x2, 0x2, 0x22, 0x3, 0x3, 0x2, 0x2, 
       0x2, 0x23, 0x24, 0x5, 0x14, 0xb, 0x2, 0x24, 0x25, 0x7, 0xb, 0x2, 
       0x2, 0x25, 0x26, 0x5, 0xa, 0x6, 0x2, 0x26, 0x5, 0x3, 0x2, 0x2, 0x2, 
       0x27, 0x28, 0x5, 0x8, 0x5, 0x2, 0x28, 0x29, 0x7, 0xb, 0x2, 0x2, 0x29, 
       0x2a, 0x5, 0xa, 0x6, 0x2, 0x2a, 0x7, 0x3, 0x2, 0x2, 0x2, 0x2b, 0x2c, 
       0x7, 0x14, 0x2, 0x2, 0x2c, 0x2d, 0x7, 0xc, 0x2, 0x2, 0x2d, 0x2e, 
       0x5, 0x14, 0xb, 0x2, 0x2e, 0x2f, 0x7, 0xd, 0x2, 0x2, 0x2f, 0x3d, 
       0x3, 0x2, 0x2, 0x2, 0x30, 0x31, 0x7, 0x14, 0x2, 0x2, 0x31, 0x35, 
       0x7, 0xc, 0x2, 0x2, 0x32, 0x33, 0x5, 0x14, 0xb, 0x2, 0x33, 0x34, 
       0x7, 0xa, 0x2, 0x2, 0x34, 0x36, 0x3, 0x2, 0x2, 0x2, 0x35, 0x32, 0x3, 
       0x2, 0x2, 0x2, 0x36, 0x37, 0x3, 0x2, 0x2, 0x2, 0x37, 0x35, 0x3, 0x2, 
       0x2, 0x2, 0x37, 0x38, 0x3, 0x2, 0x2, 0x2, 0x38, 0x39, 0x3, 0x2, 0x2, 
       0x2, 0x39, 0x3a, 0x5, 0x14, 0xb, 0x2, 0x3a, 0x3b, 0x7, 0xd, 0x2, 
       0x2, 0x3b, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x2b, 0x3, 0x2, 0x2, 0x2, 
       0x3c, 0x30, 0x3, 0x2, 0x2, 0x2, 0x3d, 0x9, 0x3, 0x2, 0x2, 0x2, 0x3e, 
       0x3f, 0x8, 0x6, 0x1, 0x2, 0x3f, 0x40, 0x5, 0xc, 0x7, 0x2, 0x40, 0x49, 
       0x3, 0x2, 0x2, 0x2, 0x41, 0x42, 0xc, 0x4, 0x2, 0x2, 0x42, 0x43, 0x7, 
       0x6, 0x2, 0x2, 0x43, 0x48, 0x5, 0xc, 0x7, 0x2, 0x44, 0x45, 0xc, 0x3, 
       0x2, 0x2, 0x45, 0x46, 0x7, 0x7, 0x2, 0x2, 0x46, 0x48, 0x5, 0xc, 0x7, 
       0x2, 0x47, 0x41, 0x3, 0x2, 0x2, 0x2, 0x47, 0x44, 0x3, 0x2, 0x2, 0x2, 
       0x48, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x49, 0x47, 0x3, 0x2, 0x2, 0x2, 0x49, 
       0x4a, 0x3, 0x2, 0x2, 0x2, 0x4a, 0xb, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x49, 
       0x3, 0x2, 0x2, 0x2, 0x4c, 0x4d, 0x8, 0x7, 0x1, 0x2, 0x4d, 0x4e, 0x5, 
       0xe, 0x8, 0x2, 0x4e, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x50, 0xc, 0x5, 
       0x2, 0x2, 0x50, 0x51, 0x7, 0x3, 0x2, 0x2, 0x51, 0x59, 0x5, 0xe, 0x8, 
       0x2, 0x52, 0x53, 0xc, 0x4, 0x2, 0x2, 0x53, 0x54, 0x7, 0x4, 0x2, 0x2, 
       0x54, 0x59, 0x5, 0xe, 0x8, 0x2, 0x55, 0x56, 0xc, 0x3, 0x2, 0x2, 0x56, 
       0x57, 0x7, 0x5, 0x2, 0x2, 0x57, 0x59, 0x5, 0xe, 0x8, 0x2, 0x58, 0x4f, 
       0x3, 0x2, 0x2, 0x2, 0x58, 0x52, 0x3, 0x2, 0x2, 0x2, 0x58, 0x55, 0x3, 
       0x2, 0x2, 0x2, 0x59, 0x5c, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x58, 0x3, 0x2, 
       0x2, 0x2, 0x5a, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x5b, 0xd, 0x3, 0x2, 0x2, 
       0x2, 0x5c, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x5d, 0x63, 0x5, 0x10, 0x9, 
       0x2, 0x5e, 0x5f, 0x7, 0x7, 0x2, 0x2, 0x5f, 0x63, 0x5, 0xe, 0x8, 0x2, 
       0x60, 0x61, 0x7, 0x6, 0x2, 0x2, 0x61, 0x63, 0x5, 0xe, 0x8, 0x2, 0x62, 
       0x5d, 0x3, 0x2, 0x2, 0x2, 0x62, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x62, 0x60, 
       0x3, 0x2, 0x2, 0x2, 0x63, 0xf, 0x3, 0x2, 0x2, 0x2, 0x64, 0x65, 0x8, 
       0x9, 0x1, 0x2, 0x65, 0x66, 0x5, 0x12, 0xa, 0x2, 0x66, 0x6c, 0x3, 
       0x2, 0x2, 0x2, 0x67, 0x68, 0xc, 0x3, 0x2, 0x2, 0x68, 0x69, 0x7, 0x9, 
       0x2, 0x2, 0x69, 0x6b, 0x5, 0xe, 0x8, 0x2, 0x6a, 0x67, 0x3, 0x2, 0x2, 
       0x2, 0x6b, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x6a, 0x3, 0x2, 0x2, 0x2, 
       0x6c, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x11, 0x3, 0x2, 0x2, 0x2, 0x6e, 
       0x6c, 0x3, 0x2, 0x2, 0x2, 0x6f, 0x78, 0x5, 0x1a, 0xe, 0x2, 0x70, 
       0x78, 0x5, 0x16, 0xc, 0x2, 0x71, 0x78, 0x5, 0x14, 0xb, 0x2, 0x72, 
       0x78, 0x5, 0x18, 0xd, 0x2, 0x73, 0x74, 0x7, 0xc, 0x2, 0x2, 0x74, 
       0x75, 0x5, 0xa, 0x6, 0x2, 0x75, 0x76, 0x7, 0xd, 0x2, 0x2, 0x76, 0x78, 
       0x3, 0x2, 0x2, 0x2, 0x77, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x77, 0x70, 0x3, 
       0x2, 0x2, 0x2, 0x77, 0x71, 0x3, 0x2, 0x2, 0x2, 0x77, 0x72, 0x3, 0x2, 
       0x2, 0x2, 0x77, 0x73, 0x3, 0x2, 0x2, 0x2, 0x78, 0x13, 0x3, 0x2, 0x2, 
       0x2, 0x79, 0x7a, 0x7, 0x14, 0x2, 0x2, 0x7a, 0x15, 0x3, 0x2, 0x2, 
       0x2, 0x7b, 0x7c, 0x7, 0xe, 0x2, 0x2, 0x7c, 0x7d, 0x7, 0x10, 0x2, 
       0x2, 0x7d, 0x7e, 0x7, 0xf, 0x2, 0x2, 0x7e, 0x17, 0x3, 0x2, 0x2, 0x2, 
       0x7f, 0x80, 0x9, 0x2, 0x2, 0x2, 0x80, 0x19, 0x3, 0x2, 0x2, 0x2, 0x81, 
       0x82, 0x7, 0x14, 0x2, 0x2, 0x82, 0x83, 0x5, 0x1c, 0xf, 0x2, 0x83, 
       0x1b, 0x3, 0x2, 0x2, 0x2, 0x84, 0x85, 0x7, 0xc, 0x2, 0x2, 0x85, 0x86, 
       0x5, 0xa, 0x6, 0x2, 0x86, 0x87, 0x7, 0xd, 0x2, 0x2, 0x87, 0x94, 0x3, 
       0x2, 0x2, 0x2, 0x88, 0x8c, 0x7, 0xc, 0x2, 0x2, 0x89, 0x8a, 0x5, 0xa, 
       0x6, 0x2, 0x8a, 0x8b, 0x7, 0xa, 0x2, 0x2, 0x8b, 0x8d, 0x3, 0x2, 0x2, 
       0x2, 0x8c, 0x89, 0x3, 0x2, 0x2, 0x2, 0x8d, 0x8e, 0x3, 0x2, 0x2, 0x2, 
       0x8e, 0x8c, 0x3, 0x2, 0x2, 0x2, 0x8e, 0x8f, 0x3, 0x2, 0x2, 0x2, 0x8f, 
       0x90, 0x3, 0x2, 0x2, 0x2, 0x90, 0x91, 0x5, 0xa, 0x6, 0x2, 0x91, 0x92, 
       0x7, 0xd, 0x2, 0x2, 0x92, 0x94, 0x3, 0x2, 0x2, 0x2, 0x93, 0x84, 0x3, 
       0x2, 0x2, 0x2, 0x93, 0x88, 0x3, 0x2, 0x2, 0x2, 0x94, 0x1d, 0x3, 0x2, 
       0x2, 0x2, 0xe, 0x21, 0x37, 0x3c, 0x47, 0x49, 0x58, 0x5a, 0x62, 0x6c, 
       0x77, 0x8e, 0x93, 
  };

  _serializedATN.insert(_serializedATN.end(), serializedATNSegment0,
    serializedATNSegment0 + sizeof(serializedATNSegment0) / sizeof(serializedATNSegment0[0]));


  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

InfixParser::Initializer InfixParser::_init;
