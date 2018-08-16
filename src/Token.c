#include "Token.h"
#include "Error.h"


OperatorIsotope opIsotopeTable[256] = {
  ['+'] = {ADD_SYMBOL, INCREMENT_SYMBOL, ADD_ASSIGN_SYMBOL},
  ['-'] = {SUB_SYMBOL, DECREMENT_SYMBOL, SUB_ASSIGN_SYMBOL},
  ['*'] = {MUL_SYMBOL, UNDEFINED_SYMBOL, MUL_ASSIGN_SYMBOL},
  ['/'] = {DIV_SYMBOL, UNDEFINED_SYMBOL, DIV_ASSIGN_SYMBOL},
  ['%'] = {MODULO_SYMBOL, UNDEFINED_SYMBOL, MODULO_ASSIGN_SYMBOL},
  ['&'] = {BITWISE_AND_SYMBOL, LOGICAL_AND_SYMBOL, BITWISE_AND_ASSIGN_SYMBOL},
  ['|'] = {BITWISE_OR_SYMBOL, LOGICAL_OR_SYMBOL, BITWISE_OR_ASSIGN_SYMBOL},
  ['!'] = {LOGICAL_NOT_SYMBOL, UNDEFINED_SYMBOL, NOT_EQUALS_TO_SYMBOL},
  ['>'] = {GREATER_SYMBOL, BITWISE_RIGHT_SHIFTER_SYMBOL, GREATER_EQUALS_SYMBOL},
  ['<'] = {LESSER_SYMBOL, BITWISE_LEFT_SHIFTER_SYMBOL, LESSER_EQUALS_SYMBOL},
  ['='] = {EQUAL_SYMBOL, EQUALS_TO_SYMBOL, EQUALS_TO_SYMBOL},
  ['~'] = {BITWISE_NOT_SYMBOL, UNDEFINED_SYMBOL, UNDEFINED_SYMBOL},
  ['^'] = {BITWISE_XOR_SYMBOL, UNDEFINED_SYMBOL, BITWISE_XOR_ASSIGN_SYMBOL},
  ['('] = {OPENING_BRACKET_SYMBOL, UNDEFINED_SYMBOL, UNDEFINED_SYMBOL},
  [')'] = {CLOSING_BRACKET_SYMBOL, UNDEFINED_SYMBOL, UNDEFINED_SYMBOL},
};

OperatorIsotope *getOperatorIsotopeInfo(Token *token) {

  if(token->type == TOKEN_OPERATOR_TYPE)
    return &opIsotopeTable[token->str[0]];

  else
    throwException(ERR_INVALID_OPERATOR,token,"Invalid Operator! - '%s'", token->str);
}
