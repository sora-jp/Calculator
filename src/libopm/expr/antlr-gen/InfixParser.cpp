
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
    enterOuterAlt(_localctx, 1);
    setState(20);
    expression(0);
   
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
  size_t startState = 2;
  enterRecursionRule(_localctx, 2, InfixParser::RuleExpression, precedence);

    

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
    setState(23);
    term(0);
    _ctx->stop = _input->LT(-1);
    setState(33);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(31);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(25);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(26);
          match(InfixParser::PLUS);
          setState(27);
          term(0);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(28);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(29);
          match(InfixParser::MINUS);
          setState(30);
          term(0);
          break;
        }

        default:
          break;
        } 
      }
      setState(35);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
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
  size_t startState = 4;
  enterRecursionRule(_localctx, 4, InfixParser::RuleTerm, precedence);

    

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
    setState(37);
    factor();
    _ctx->stop = _input->LT(-1);
    setState(50);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(48);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<TermContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTerm);
          setState(39);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(40);
          match(InfixParser::MULT);
          setState(41);
          factor();
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<TermContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTerm);
          setState(42);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(43);
          match(InfixParser::DIV);
          setState(44);
          factor();
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<TermContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleTerm);
          setState(45);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(46);
          match(InfixParser::MOD);
          setState(47);
          factor();
          break;
        }

        default:
          break;
        } 
      }
      setState(52);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
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
  enterRule(_localctx, 6, InfixParser::RuleFactor);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(58);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case InfixParser::LPAREN:
      case InfixParser::NUMBER:
      case InfixParser::ID: {
        enterOuterAlt(_localctx, 1);
        setState(53);
        secondary(0);
        break;
      }

      case InfixParser::MINUS: {
        enterOuterAlt(_localctx, 2);
        setState(54);
        match(InfixParser::MINUS);
        setState(55);
        factor();
        break;
      }

      case InfixParser::PLUS: {
        enterOuterAlt(_localctx, 3);
        setState(56);
        match(InfixParser::PLUS);
        setState(57);
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
  size_t startState = 8;
  enterRecursionRule(_localctx, 8, InfixParser::RuleSecondary, precedence);

    

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
    primary();
    _ctx->stop = _input->LT(-1);
    setState(68);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<SecondaryContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleSecondary);
        setState(63);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(64);
        match(InfixParser::POW);
        setState(65);
        factor(); 
      }
      setState(70);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
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
  enterRule(_localctx, 10, InfixParser::RulePrimary);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(78);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(71);
      func();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(72);
      variable();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(73);
      constant();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(74);
      match(InfixParser::LPAREN);
      setState(75);
      expression(0);
      setState(76);
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
  enterRule(_localctx, 12, InfixParser::RuleVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(80);
    match(InfixParser::ID);
   
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
  enterRule(_localctx, 14, InfixParser::RuleConstant);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(82);
    match(InfixParser::NUMBER);
   
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
  enterRule(_localctx, 16, InfixParser::RuleFunc);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(84);
    match(InfixParser::ID);
    setState(85);
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
  enterRule(_localctx, 18, InfixParser::RuleParams);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    setState(102);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(87);
      match(InfixParser::LPAREN);
      setState(88);
      expression(0);
      setState(89);
      match(InfixParser::RPAREN);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(91);
      match(InfixParser::LPAREN);
      setState(95); 
      _errHandler->sync(this);
      alt = 1;
      do {
        switch (alt) {
          case 1: {
                setState(92);
                expression(0);
                setState(93);
                match(InfixParser::COMMA);
                break;
              }

        default:
          throw NoViableAltException(this);
        }
        setState(97); 
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
      } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
      setState(99);
      expression(0);
      setState(100);
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
    case 1: return expressionSempred(dynamic_cast<ExpressionContext *>(context), predicateIndex);
    case 2: return termSempred(dynamic_cast<TermContext *>(context), predicateIndex);
    case 4: return secondarySempred(dynamic_cast<SecondaryContext *>(context), predicateIndex);

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
  "eval", "expression", "term", "factor", "secondary", "primary", "variable", 
  "constant", "func", "params"
};

std::vector<std::string> InfixParser::_literalNames = {
  "", "'*'", "'/'", "'%'", "'+'", "'-'", "'.'", "'^'", "','", "'('", "')'"
};

std::vector<std::string> InfixParser::_symbolicNames = {
  "", "MULT", "DIV", "MOD", "PLUS", "MINUS", "DOT", "POW", "COMMA", "LPAREN", 
  "RPAREN", "NUMBER", "ID", "COMMENT", "WS"
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
       0x3, 0x10, 0x6b, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
       0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 
       0x7, 0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 
       0x4, 0xb, 0x9, 0xb, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 
       0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
       0x7, 0x3, 0x22, 0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0x25, 0xb, 0x3, 0x3, 
       0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
       0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x7, 0x4, 0x33, 
       0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x36, 0xb, 0x4, 0x3, 0x5, 0x3, 0x5, 
       0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x3d, 0xa, 0x5, 0x3, 0x6, 
       0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x7, 0x6, 0x45, 
       0xa, 0x6, 0xc, 0x6, 0xe, 0x6, 0x48, 0xb, 0x6, 0x3, 0x7, 0x3, 0x7, 
       0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x5, 0x7, 0x51, 
       0xa, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 
       0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 
       0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x6, 0xb, 0x62, 0xa, 0xb, 0xd, 0xb, 
       0xe, 0xb, 0x63, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0x69, 0xa, 
       0xb, 0x3, 0xb, 0x2, 0x5, 0x4, 0x6, 0xa, 0xc, 0x2, 0x4, 0x6, 0x8, 
       0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x2, 0x2, 0x2, 0x6d, 0x2, 0x16, 
       0x3, 0x2, 0x2, 0x2, 0x4, 0x18, 0x3, 0x2, 0x2, 0x2, 0x6, 0x26, 0x3, 
       0x2, 0x2, 0x2, 0x8, 0x3c, 0x3, 0x2, 0x2, 0x2, 0xa, 0x3e, 0x3, 0x2, 
       0x2, 0x2, 0xc, 0x50, 0x3, 0x2, 0x2, 0x2, 0xe, 0x52, 0x3, 0x2, 0x2, 
       0x2, 0x10, 0x54, 0x3, 0x2, 0x2, 0x2, 0x12, 0x56, 0x3, 0x2, 0x2, 0x2, 
       0x14, 0x68, 0x3, 0x2, 0x2, 0x2, 0x16, 0x17, 0x5, 0x4, 0x3, 0x2, 0x17, 
       0x3, 0x3, 0x2, 0x2, 0x2, 0x18, 0x19, 0x8, 0x3, 0x1, 0x2, 0x19, 0x1a, 
       0x5, 0x6, 0x4, 0x2, 0x1a, 0x23, 0x3, 0x2, 0x2, 0x2, 0x1b, 0x1c, 0xc, 
       0x4, 0x2, 0x2, 0x1c, 0x1d, 0x7, 0x6, 0x2, 0x2, 0x1d, 0x22, 0x5, 0x6, 
       0x4, 0x2, 0x1e, 0x1f, 0xc, 0x3, 0x2, 0x2, 0x1f, 0x20, 0x7, 0x7, 0x2, 
       0x2, 0x20, 0x22, 0x5, 0x6, 0x4, 0x2, 0x21, 0x1b, 0x3, 0x2, 0x2, 0x2, 
       0x21, 0x1e, 0x3, 0x2, 0x2, 0x2, 0x22, 0x25, 0x3, 0x2, 0x2, 0x2, 0x23, 
       0x21, 0x3, 0x2, 0x2, 0x2, 0x23, 0x24, 0x3, 0x2, 0x2, 0x2, 0x24, 0x5, 
       0x3, 0x2, 0x2, 0x2, 0x25, 0x23, 0x3, 0x2, 0x2, 0x2, 0x26, 0x27, 0x8, 
       0x4, 0x1, 0x2, 0x27, 0x28, 0x5, 0x8, 0x5, 0x2, 0x28, 0x34, 0x3, 0x2, 
       0x2, 0x2, 0x29, 0x2a, 0xc, 0x5, 0x2, 0x2, 0x2a, 0x2b, 0x7, 0x3, 0x2, 
       0x2, 0x2b, 0x33, 0x5, 0x8, 0x5, 0x2, 0x2c, 0x2d, 0xc, 0x4, 0x2, 0x2, 
       0x2d, 0x2e, 0x7, 0x4, 0x2, 0x2, 0x2e, 0x33, 0x5, 0x8, 0x5, 0x2, 0x2f, 
       0x30, 0xc, 0x3, 0x2, 0x2, 0x30, 0x31, 0x7, 0x5, 0x2, 0x2, 0x31, 0x33, 
       0x5, 0x8, 0x5, 0x2, 0x32, 0x29, 0x3, 0x2, 0x2, 0x2, 0x32, 0x2c, 0x3, 
       0x2, 0x2, 0x2, 0x32, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x33, 0x36, 0x3, 0x2, 
       0x2, 0x2, 0x34, 0x32, 0x3, 0x2, 0x2, 0x2, 0x34, 0x35, 0x3, 0x2, 0x2, 
       0x2, 0x35, 0x7, 0x3, 0x2, 0x2, 0x2, 0x36, 0x34, 0x3, 0x2, 0x2, 0x2, 
       0x37, 0x3d, 0x5, 0xa, 0x6, 0x2, 0x38, 0x39, 0x7, 0x7, 0x2, 0x2, 0x39, 
       0x3d, 0x5, 0x8, 0x5, 0x2, 0x3a, 0x3b, 0x7, 0x6, 0x2, 0x2, 0x3b, 0x3d, 
       0x5, 0x8, 0x5, 0x2, 0x3c, 0x37, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x38, 0x3, 
       0x2, 0x2, 0x2, 0x3c, 0x3a, 0x3, 0x2, 0x2, 0x2, 0x3d, 0x9, 0x3, 0x2, 
       0x2, 0x2, 0x3e, 0x3f, 0x8, 0x6, 0x1, 0x2, 0x3f, 0x40, 0x5, 0xc, 0x7, 
       0x2, 0x40, 0x46, 0x3, 0x2, 0x2, 0x2, 0x41, 0x42, 0xc, 0x3, 0x2, 0x2, 
       0x42, 0x43, 0x7, 0x9, 0x2, 0x2, 0x43, 0x45, 0x5, 0x8, 0x5, 0x2, 0x44, 
       0x41, 0x3, 0x2, 0x2, 0x2, 0x45, 0x48, 0x3, 0x2, 0x2, 0x2, 0x46, 0x44, 
       0x3, 0x2, 0x2, 0x2, 0x46, 0x47, 0x3, 0x2, 0x2, 0x2, 0x47, 0xb, 0x3, 
       0x2, 0x2, 0x2, 0x48, 0x46, 0x3, 0x2, 0x2, 0x2, 0x49, 0x51, 0x5, 0x12, 
       0xa, 0x2, 0x4a, 0x51, 0x5, 0xe, 0x8, 0x2, 0x4b, 0x51, 0x5, 0x10, 
       0x9, 0x2, 0x4c, 0x4d, 0x7, 0xb, 0x2, 0x2, 0x4d, 0x4e, 0x5, 0x4, 0x3, 
       0x2, 0x4e, 0x4f, 0x7, 0xc, 0x2, 0x2, 0x4f, 0x51, 0x3, 0x2, 0x2, 0x2, 
       0x50, 0x49, 0x3, 0x2, 0x2, 0x2, 0x50, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x50, 
       0x4b, 0x3, 0x2, 0x2, 0x2, 0x50, 0x4c, 0x3, 0x2, 0x2, 0x2, 0x51, 0xd, 
       0x3, 0x2, 0x2, 0x2, 0x52, 0x53, 0x7, 0xe, 0x2, 0x2, 0x53, 0xf, 0x3, 
       0x2, 0x2, 0x2, 0x54, 0x55, 0x7, 0xd, 0x2, 0x2, 0x55, 0x11, 0x3, 0x2, 
       0x2, 0x2, 0x56, 0x57, 0x7, 0xe, 0x2, 0x2, 0x57, 0x58, 0x5, 0x14, 
       0xb, 0x2, 0x58, 0x13, 0x3, 0x2, 0x2, 0x2, 0x59, 0x5a, 0x7, 0xb, 0x2, 
       0x2, 0x5a, 0x5b, 0x5, 0x4, 0x3, 0x2, 0x5b, 0x5c, 0x7, 0xc, 0x2, 0x2, 
       0x5c, 0x69, 0x3, 0x2, 0x2, 0x2, 0x5d, 0x61, 0x7, 0xb, 0x2, 0x2, 0x5e, 
       0x5f, 0x5, 0x4, 0x3, 0x2, 0x5f, 0x60, 0x7, 0xa, 0x2, 0x2, 0x60, 0x62, 
       0x3, 0x2, 0x2, 0x2, 0x61, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x62, 0x63, 0x3, 
       0x2, 0x2, 0x2, 0x63, 0x61, 0x3, 0x2, 0x2, 0x2, 0x63, 0x64, 0x3, 0x2, 
       0x2, 0x2, 0x64, 0x65, 0x3, 0x2, 0x2, 0x2, 0x65, 0x66, 0x5, 0x4, 0x3, 
       0x2, 0x66, 0x67, 0x7, 0xc, 0x2, 0x2, 0x67, 0x69, 0x3, 0x2, 0x2, 0x2, 
       0x68, 0x59, 0x3, 0x2, 0x2, 0x2, 0x68, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x69, 
       0x15, 0x3, 0x2, 0x2, 0x2, 0xb, 0x21, 0x23, 0x32, 0x34, 0x3c, 0x46, 
       0x50, 0x63, 0x68, 
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
