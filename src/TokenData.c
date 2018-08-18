#include "TokenData.h"
#include "TDOP.h"
#include "Token.h"
#include "Operator.h"
#include <stdint.h>
#include <string.h>
#include <malloc.h>
#include "Exception.h"
#include "Error.h"

TokenInfo symbolMapTable[256] = {
  [ADD_SYMBOL] = {.bindingPower = ADDITION_BP, .nud = nudPlus, .led = ledPlus},
  [SUB_SYMBOL] = {.bindingPower = SUBTRACTION_BP, .nud = nudNegative, .led = ledMinus},
  [NEGATIVE_SYMBOL] = {.bindingPower = UNARY_MINUS_BP, .nud = NULL, .led = NULL},
  [MUL_SYMBOL] = {.bindingPower = MULTIPLICATION_BP, .nud = nudAsterisk, .led = ledAsterisk},
  [DIV_SYMBOL] = {.bindingPower = DIVISION_BP, .nud = nudSlash, .led = ledSlash},
  [MODULO_SYMBOL] = {.bindingPower = REMAINDER_BP, .nud = nudPercent, .led = ledPercent},
  [LOGICAL_NOT_SYMBOL] = {.bindingPower = LOGICAL_NOT_BP, .nud = nudExclamation, .led = ledExclamation},
  [BITWISE_NOT_SYMBOL] = {.bindingPower = BITWISE_NOT_BP, .nud = nudTilde, .led = ledTilde},
  [LOGICAL_AND_SYMBOL] = {.bindingPower = LOGICAL_AND_BP, .nud = nudDoubleAmpersand, .led = ledDoubleAmpersand},
  [BITWISE_AND_SYMBOL] = {.bindingPower = BITWISE_AND_BP, .nud = nudAmpersand, .led = ledAmpersand},
  [LOGICAL_OR_SYMBOL] = {.bindingPower = LOGICAL_OR_BP, .nud = nudDoubleVerticalBar, .led = ledDoubleVerticalBar},
  [BITWISE_OR_SYMBOL] = {.bindingPower = BITWISE_OR_BP, .nud = nudVerticalBar, .led = ledVerticalBar},
  [BITWISE_XOR_SYMBOL] = {.bindingPower = BITWISE_XOR_BP, .nud = nudCaret, .led =ledCaret},
  [BITWISE_LEFT_SHIFTER_SYMBOL] = {.bindingPower = BITWISE_LEFT_SHIFTER_BP, .nud = nudDoubleLeftArrows, .led = ledDoubleLeftArrows},
  [BITWISE_RIGHT_SHIFTER_SYMBOL] = {.bindingPower = BITWISE_RIGHT_SHIFTER_BP, .nud = nudDoubleRightArrows, .led = ledDoubleRightArrows},
  [GREATER_SYMBOL] = {.bindingPower = GREATER_BP, .nud = nudRightArrow, .led = ledRightArrow},
  [LESSER_SYMBOL] = {.bindingPower = LESSER_BP, .nud = nudLeftArrow, .led = ledLeftArrow},
  [GREATER_EQUALS_SYMBOL] = {.bindingPower = GREATER_EQUALS_BP, .nud = nudRightArrowEqual, .led = ledRightArrowEqual},
  [LESSER_EQUALS_SYMBOL] = {.bindingPower = LESSER_EQUALS_BP, .nud = nudLeftArrowEqual, .led = ledLeftArrowEqual},
  [EQUALS_TO_SYMBOL] = {.bindingPower = EQUALS_TO_BP, .nud = nudDoubleEquals, .led = ledDoubleEquals},
  [EQUAL_SYMBOL] = {.bindingPower = EQUAL_BP, .nud = nudEqual, .led = ledEqual},
  [NOT_EQUALS_TO_SYMBOL] = {.bindingPower = NOT_EQUALS_TO_BP, .nud = nudExclamationEqual, .led = ledExclamationEqual},
  [OPENING_BRACKET_SYMBOL] = {.bindingPower = OPENING_BRACKET_BP, .nud = nudLeftBracket, .led = ledLeftBracket},
  [CLOSING_BRACKET_SYMBOL] = {.bindingPower = CLOSING_BRACKET_BP, .nud = nudRightBracket},
  [INTEGER_SYMBOL] = {.nud = nudInt, .led = ledInt},
  [FLOAT_SYMBOL] = {.nud = nudFloat, .led = ledFloat},
  [NULL_SYMBOL] = {.bindingPower = WEAKEST_BP, .nud = nudNULL},
};

TokenInfo *getTokenInfo(Token *token) {

  if(token->type == TOKEN_INTEGER_TYPE)
    return &symbolMapTable[INTEGER_SYMBOL];

  else if(token->type == TOKEN_FLOAT_TYPE)
    return &symbolMapTable[FLOAT_SYMBOL];

  else if(token->type == TOKEN_OPERATOR_TYPE)
    return &symbolMapTable[token->symbol];

  else if(token->type == TOKEN_NULL_TYPE)
    return &symbolMapTable[NULL_SYMBOL];

}

Token *getAdvanceToken(Tokenizer *expression) {
  Token *token1;

    token1 = getToken(expression);

    if(token1->type == TOKEN_OPERATOR_TYPE)
      token1 = handleSignEqualAndRepeat(expression, token1);

    else if (token1->type == TOKEN_INTEGER_TYPE) {
      checkIfNextTokenIsInteger(expression);
      token1->symbol = INTEGER_SYMBOL;
    }

    else if (token1->type == TOKEN_FLOAT_TYPE)
      token1->symbol = FLOAT_SYMBOL;

    else if (token1->type == TOKEN_NULL_TYPE)
      token1->symbol = NULL_SYMBOL;

    return token1;
}


Token *handleSignEqualAndRepeat(Tokenizer *expression, Token *token1) {

    Token *token2 = getToken(expression);
    OperatorIsotope *token1IsoInfo;

    token1IsoInfo = getOperatorIsotopeInfo(token1);

    if (token2->type == TOKEN_NULL_TYPE) {
      token1->symbol =  token1IsoInfo->symbolTable[0];
      pushBackToken(expression, token2);
      return token1;
    }

    if(verifyTokensBackToBack(token1,token2)) {
      if(verifyTokensRepeated(token1, token2)) {
        if(checkIfUndefined(token1IsoInfo, 1))
          throwException(ERR_UNDEFINED_SYMBOL, token1, "Undefined operator, '%s'",token1->str);
        else {
          token1->symbol =  token1IsoInfo->symbolTable[1];
          free(token1->str);
          token1->str = createString(&token1->originalStr[token1->startColumn], 2);
          freeToken(token2);
        }
      } else if(verifyTokenIsEqualSign(token2)) {
        if(checkIfUndefined(token1IsoInfo, 2))
          throwException(ERR_UNDEFINED_SYMBOL, token1, "Undefined operator, '%s'",token1->str);
        else {
          token1->symbol =  token1IsoInfo->symbolTable[2];
          free(token1->str);
          token1->str = createString(&token1->originalStr[token1->startColumn], 2);
          freeToken(token2);
        }
      } else {
          if(checkIfUndefined(token1IsoInfo, 0))
            throwException(ERR_UNDEFINED_SYMBOL, token1, "Undefined operator, '%s'",token1->str);
          else {
            token1->symbol =  token1IsoInfo->symbolTable[0];
            pushBackToken(expression, token2);
          }
      }
    }

    else {
      if(checkIfUndefined(token1IsoInfo, 0))
        throwException(ERR_UNDEFINED_SYMBOL, token1, "Undefined operator, '%s'",token1->str);
      else {
        token1->symbol =  token1IsoInfo->symbolTable[0];
        pushBackToken(expression, token2);
      }
    }
    return token1;
 }

Token *newFloatToken(double value, Token *token, Token *leftToken, Token *rightToken) {

  if(leftToken == NULL || rightToken == NULL) {
    token = createFloatToken(value, NULL);
    token->symbol = FLOAT_SYMBOL;
    return token;
  } else {
    token = createFloatToken(value, NULL);
    token->symbol = FLOAT_SYMBOL;
    token->originalStr = leftToken->originalStr;
    token->startColumn = leftToken->startColumn;
    token->length = (rightToken->startColumn + rightToken->length) - leftToken->startColumn;
    token->str = malloc(token->length);
    strncpy(token->str,leftToken->originalStr+token->startColumn,token->length + 1);
    token->str[token->length] = '\0';
    return token;
  }
}

char* createString(char *ptr, int size) {

  char *newStr, *strPtr;
  newStr = malloc(size + 1);

  strPtr = newStr;
  *(strPtr)++ = *(ptr)++;
  *(strPtr)++ = *(ptr)++;
  *(strPtr) = '\0';

  return newStr;
}

int getTokenIntegerValue(Token *token) {
  int value, tokenvalue;

  if(getTokenType(token)) {
    if(token->type == TOKEN_FLOAT_TYPE) {
      tokenvalue = ((FloatToken *)token)->value;
      value = (int)tokenvalue;
    }
    else if (token->type == TOKEN_INTEGER_TYPE)
      return ((IntegerToken *)token)->value;
  }

  else
    throwException(ERR_NOT_AN_INTEGER, token, "Expecting an integer, but %f is met.",((FloatToken *)token)->value);//Throw exception
}

int verifyTokensBackToBack(Token *token1, Token *token2) {

    token1->startColumn = token1->startColumn + token1->length;

    if((token1)->startColumn == (token2)->startColumn) {
      token1->startColumn = token1->startColumn - token1->length;
      return 1;
    }

    else {
      token1->startColumn = token1->startColumn - token1->length;
      return 0;
    }
}

int checkIfUndefined(OperatorIsotope *token1IsoInfo, int indexNum) {

  if(token1IsoInfo->symbolTable[indexNum] == 0 || token1IsoInfo->symbolTable[indexNum] == UNDEFINED_SYMBOL)
    return 1;
  else
    return 0;
}

int verifyTokensRepeated(Token *token1, Token *token2) {
  if(*(token1)->str == *(token2)->str)
    return 1;
  else
    return 0;
}

int verifyTokenIsEqualSign(Token *token2) {
  if(*(token2)->str == '=')
    return 1;
  else
    return 0;
}


int getTokenType(Token *token) {
  double d;
  int i;

  if(token->type == TOKEN_INTEGER_TYPE)
    d = ((IntegerToken *)token)->value;

  else if(token->type == TOKEN_FLOAT_TYPE)
    d = ((FloatToken *)token)->value;

  i = (int)d;

  if(d == i)
      return 1;

  else
      return 0;
}

  double getTokenValue(Token *token) {
  double value;

  switch (token->type) {
    case TOKEN_INTEGER_TYPE :
      value = ((IntegerToken *)token)->value;
      break;
    case TOKEN_FLOAT_TYPE :
      value = ((FloatToken *)token)->value;
      break;
    default :
      throwException(ERR_INVALID_OPERAND, token, "Invalid operand : '%s'.", token->str);
  }
  return value;
}

int checkTokenIfItsNULL(Token *token) {
  if(token->type == TOKEN_NULL_TYPE)
    return 1;

  else
    return 0;
}

void checkIfNextTokenIsInteger(Tokenizer *expression) {
  Token *nextToken = getToken(expression);
    if(nextToken->type == TOKEN_INTEGER_TYPE)
      throwException(ERR_EXPECTING_OPERATOR, nextToken, "Expecting an operator, but '%s' is met.", nextToken->str);
    else
      pushBackToken(expression,nextToken);
}

Token *getNud(Token *thisToken, Tokenizer *expression) {
  TokenInfo *thisTokenInfo;
  Token *nudToken;

  thisTokenInfo = getTokenInfo(thisToken);
  if(thisTokenInfo->nud == NULL) {
    throwException(SYSTEM_ERROR, thisToken, "nud %s is NULL.", thisToken->str);
  }
  else {
    nudToken = thisTokenInfo->nud(thisToken, expression);
    return nudToken;
  }
}

Token *getLed(Token *thisToken, Token *leftToken, Tokenizer *expression) {
  TokenInfo *thisTokenInfo;
  Token *ledToken;

  thisTokenInfo = getTokenInfo(thisToken);
  if(thisTokenInfo->led == NULL) {
    throwException(SYSTEM_ERROR, thisToken, "led %s is NULL.", thisToken->str);
  }
  else {
    ledToken = thisTokenInfo->led(leftToken, thisToken, expression);
    return ledToken;
  }
}
