#ifndef Token_H
#define Token_H

#include <stdint.h>
#include "Common.h"
#include "CException.h"
#include "Exception.h"
typedef enum {
  NULL_SYMBOL,
  ADD_SYMBOL,
  SUB_SYMBOL,
  MUL_SYMBOL,
  DIV_SYMBOL,
  MODULO_SYMBOL,
  NEGATIVE_SYMBOL,
  LOGICAL_NOT_SYMBOL,
  BITWISE_NOT_SYMBOL,
  LOGICAL_AND_SYMBOL,
  BITWISE_AND_SYMBOL,
  LOGICAL_OR_SYMBOL,
  BITWISE_OR_SYMBOL,
  BITWISE_XOR_SYMBOL,
  BITWISE_LEFT_SHIFTER_SYMBOL,
  BITWISE_RIGHT_SHIFTER_SYMBOL,
  EQUAL_SYMBOL,
  EQUALS_TO_SYMBOL,
  NOT_EQUALS_TO_SYMBOL,
  GREATER_SYMBOL,
  LESSER_SYMBOL,
  GREATER_EQUALS_SYMBOL,
  LESSER_EQUALS_SYMBOL,
  OPENING_BRACKET_SYMBOL,
  CLOSING_BRACKET_SYMBOL,
  FLOAT_SYMBOL,
  IDENTIFIER_SYMBOL,
  INTEGER_SYMBOL,
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
  BITWISE_NOT_BP = 14,
  LOGICAL_NOT_BP = 14,
  UNARY_MINUS_BP = 14,
  MULTIPLICATION_BP =13,
  DIVISION_BP = 13,
  REMAINDER_BP = 13,
  ADDITION_BP = 12,
  SUBTRACTION_BP = 12,
  BITWISE_RIGHT_SHIFTER_BP = 11,
  BITWISE_LEFT_SHIFTER_BP = 11,
  GREATER_BP = 10,
  LESSER_BP = 10,
  GREATER_EQUALS_BP = 10,
  LESSER_EQUALS_BP = 10,
  EQUALS_TO_BP = 9,
  NOT_EQUALS_TO_BP = 9,
  BITWISE_AND_BP = 8,
  BITWISE_XOR_BP = 7,
  BITWISE_OR_BP = 6,
  LOGICAL_AND_BP = 5,
  LOGICAL_OR_BP = 4,
  EQUAL_BP = 2,
  OPENING_BRACKET_BP = 1,
  CLOSING_BRACKET_BP = 0,
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
