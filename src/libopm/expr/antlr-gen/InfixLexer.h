
// Generated from Infix.g4 by ANTLR 4.9.2

#pragma once


#include "antlr4-runtime.h"




class  InfixLexer : public antlr4::Lexer {
public:
  enum {
    MULT = 1, DIV = 2, MOD = 3, PLUS = 4, MINUS = 5, DOT = 6, POW = 7, COMMA = 8, 
    EQUALS = 9, LPAREN = 10, RPAREN = 11, LBRACK = 12, RBRACK = 13, INTEGER = 14, 
    NUMBER = 15, IINTEGER = 16, INUMBER = 17, ID = 18, COMMENT = 19, WS = 20
  };

  explicit InfixLexer(antlr4::CharStream *input);
  ~InfixLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

