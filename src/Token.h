#ifndef Token_H
#define Token_H

#include <stdint.h>
#include "Common.h"
#include "CException.h"
#include "Exception.h"

typedef struct OperatorIsotope OperatorIsotope;
struct OperatorIsotope {
  int symbolTable[3];
};

typedef enum {
  NULL_SYMBOL,
  ADD_SYMBOL, INCREMENT_SYMBOL, ADD_ASSIGN_SYMBOL,
  SUB_SYMBOL, DECREMENT_SYMBOL, SUB_ASSIGN_SYMBOL,
  MUL_SYMBOL, MUL_ASSIGN_SYMBOL,
  DIV_SYMBOL, DIV_ASSIGN_SYMBOL,
  MODULO_SYMBOL, MODULO_ASSIGN_SYMBOL,
  NEGATIVE_SYMBOL,
  LOGICAL_NOT_SYMBOL, BITWISE_NOT_SYMBOL, NOT_EQUALS_TO_SYMBOL,
  LOGICAL_AND_SYMBOL, BITWISE_AND_SYMBOL, BITWISE_AND_ASSIGN_SYMBOL,
  LOGICAL_OR_SYMBOL, BITWISE_OR_SYMBOL, BITWISE_OR_ASSIGN_SYMBOL,
  BITWISE_XOR_SYMBOL, BITWISE_XOR_ASSIGN_SYMBOL,
  LESSER_SYMBOL, BITWISE_LEFT_SHIFTER_SYMBOL, LESSER_EQUALS_SYMBOL,
  GREATER_SYMBOL, BITWISE_RIGHT_SHIFTER_SYMBOL, GREATER_EQUALS_SYMBOL,
  EQUAL_SYMBOL, EQUALS_TO_SYMBOL,
  OPENING_BRACKET_SYMBOL,
  CLOSING_BRACKET_SYMBOL,
  FLOAT_SYMBOL,
  IDENTIFIER_SYMBOL,
  INTEGER_SYMBOL,
  UNDEFINED_SYMBOL,
} Symbols;

typedef enum {
  TOKEN_UNKNOWN_TYPE,
  TOKEN_NULL_TYPE,
  TOKEN_INVALID_TYPE,
  TOKEN_INTEGER_TYPE,
  TOKEN_OPERATOR_TYPE,
  TOKEN_FLOAT_TYPE,
  TOKEN_STRING_TYPE,
  TOKEN_IDENTIFIER_TYPE,
} TokenType;

typedef enum {
  NO_AFFIX,
  PREFIX,
  INFIX,
  POSTFIX,
} Affix;

typedef enum {
  BITWISE_NOT_BP = 15,
  LOGICAL_NOT_BP = 15,
  UNARY_MINUS_BP = 15,
  MULTIPLICATION_BP =14,
  DIVISION_BP = 14,
  REMAINDER_BP = 14,
  ADDITION_BP = 13,
  SUBTRACTION_BP = 13,
  BITWISE_RIGHT_SHIFTER_BP = 12,
  BITWISE_LEFT_SHIFTER_BP = 12,
  GREATER_BP = 11,
  LESSER_BP = 11,
  GREATER_EQUALS_BP = 11,
  LESSER_EQUALS_BP = 11,
  EQUALS_TO_BP = 10,
  NOT_EQUALS_TO_BP = 10,
  BITWISE_AND_BP = 9,
  BITWISE_XOR_BP = 8,
  BITWISE_OR_BP = 7,
  LOGICAL_AND_BP = 5,
  LOGICAL_OR_BP = 4,
  EQUAL_BP = 3,
  OPENING_BRACKET_BP = 2,
  CLOSING_BRACKET_BP = 1,
  WEAKEST_BP = 0,
} BindingPower;

typedef enum {
  NO_ASSOCIATIVITY,
  LEFT_TO_RIGHT,
  RIGHT_TO_LEFT,
} Associativity;

typedef struct {
  TokenType type:16;
  Symbols symbol:16;
  uint32_t startColumn;
  uint32_t length;
  char *originalStr;         ///
  char *str;
} Token;

typedef struct {
  TokenType type;
  uint32_t startColumn;
  uint32_t length;
  char *originalStr;         ///
  char *str;
  int value;
} IntegerToken;

typedef struct {
  TokenType type;
  uint32_t startColumn;
  uint32_t length;
  char *originalStr;         ///
  char *str;
  double value;
} FloatToken;

typedef struct {
  TokenType type;
  uint32_t startColumn;
  uint32_t length;
  char *originalStr;         ///
  char *str;
} IdentifierToken, StringToken, CharConstToken;

typedef struct {
  TokenType type;
  uint32_t startColumn;
  uint32_t length;
  char *originalStr;         ///
  char *str;
  Token *token[0];
} OperatorToken;

OperatorIsotope *getOperatorIsotopeInfo(Token *token);
Token *createNullToken();
Token *createInvalidToken(char *originalString, int start, int len);
Token *createIntegerToken(int value, char *originalString);
Token *createFloatToken(double value, char *originalString);
Token *createIdentifierToken(char *str, char *originalString);
Token *createStringToken(char *str, char *originalString);
Token *createOperatorToken(char *str, char *originalString);
void freeToken(void *token);
void dumpTokenErrorMessage(CEXCEPTION_T ex, int lineNo);

#endif // Token_H
