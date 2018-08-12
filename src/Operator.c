#include "Operator.h"
#include "Tokenizer.h"
#include "TokenData.h"
#include "TDOP.h"
#include "Token.h"
#include "Exception.h"
#include "Error.h"


Token *thisToken;

Token *nudInt (Token *thisToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower) {
    if(nextToken->type == TOKEN_INTEGER_TYPE || nextToken->type == TOKEN_FLOAT_TYPE)
      throwException(ERR_EXPECTING_OPERATOR, nextToken, "Expecting an operator, but '%s' is met.", nextToken->str);
    else
      return thisToken;
}

Token *ledInt (Token *intToken, Token *thisToken, Tokenizer *expression) {
    throwException(INVALID_SYMBOL_PLACEMENT, intToken, "''%s'' should not appear at here.", intToken->str);
}

Token *nudFloat(Token *floatToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  return floatToken;
}

Token *ledFloat (Token *leftToken, Token *thisToken, Tokenizer *expression) {
    throwException(INVALID_SYMBOL_PLACEMENT, leftToken, "''%s'' should not appear at here.", leftToken->str);
}

Token *nudPlus(Token *plusToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  return evaluate(expression, ADDITION_BP);
}

Token *ledPlus(Token *leftToken, Token *thisToken, Tokenizer *expression){
  Token  *rightToken, *token;
  double v1, v2, ans;

    rightToken = evaluate(expression, ADDITION_BP);
    v1 = getTokenValue(leftToken);
    v2 = getTokenValue(rightToken);
    ans =  v1 + v2;
    token = newFloatToken(ans, token, leftToken, rightToken);

  return token;
}

Token *nudNegative(Token *negToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  double value;
  Token *token;

    token = evaluate(expression, UNARY_MINUS_BP);
    value = getTokenValue(token);
    value = -value;
    token = newFloatToken(value,token,negToken,token);
    return token;
}

Token *ledNegative (Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  double v1, v2, ans;

    rightToken = evaluate(expression, SUBTRACTION_BP);
    v1 = getTokenValue(leftToken);
    v2 = getTokenValue(rightToken);
    ans =  v1 - v2;
    token = newFloatToken(ans, token, leftToken, rightToken);
    return token;
}

Token *nudMinus(Token *minusToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  double value;
  Token *token;

    token = evaluate(expression, SUBTRACTION_BP);
    value = getTokenValue(token);
    value = -value;
    token = newFloatToken(value,token,minusToken,token);
    return token;
}

Token *ledMinus(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  double v1, v2, ans;

    rightToken = evaluate(expression, SUBTRACTION_BP);
    v1 = getTokenValue(leftToken);
    v2 = getTokenValue(rightToken);
    ans =  v1 - v2;
    token = newFloatToken(ans, token, leftToken, rightToken);
    return token;
}

Token *nudAsterisk (Token *astToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  throwException(INVALID_SYMBOL_PLACEMENT, astToken, "'%s' should not appear at here.", astToken->str);
}

Token *ledAsterisk(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  double v1, v2, ans;

    rightToken = evaluate(expression, MULTIPLICATION_BP);
    v1 = getTokenValue(leftToken);
    v2 = getTokenValue(rightToken);
    ans =  v1 * v2;
    token = newFloatToken(ans, token, leftToken, rightToken);
    return token;
}

Token *nudSlash (Token *slashToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  throwException(INVALID_SYMBOL_PLACEMENT, slashToken, "'%s' should not appear at here.", slashToken->str);
}

Token *ledSlash(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  double v1, v2, ans;

    rightToken = evaluate(expression, DIVISION_BP);
    v1 = getTokenValue(leftToken);
    v2 = getTokenValue(rightToken);

    if(v2 == 0)
      throwException(ERR_UNDEFINED, rightToken, "The expression cannot be divided by 0!");
    else {
    ans =  v1 / v2;
    token = newFloatToken(ans, NULL, leftToken, rightToken);
    return token;
    }
}

Token *nudPercent (Token *percToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  throwException(INVALID_SYMBOL_PLACEMENT, percToken, "'%s' should not appear at here.", percToken->str);
}

Token *ledPercent(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, REMAINDER_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    if(v2 == 0)
      throwException(ERR_UNDEFINED, NULL, "The expression cannot be divided by 0!");
    else {
    ans =  v1 % v2;
    token = newFloatToken(ans, NULL, leftToken, rightToken);
    return token;
    }
}

Token *nudExclamation(Token *exclToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  Token *token;

  token = evaluate(expression, LOGICAL_NOT_BP);

  if(getTokenIntegerValue(token) != 0)
    token = newFloatToken(0, NULL, exclToken, token);

  else
    token = newFloatToken(1, NULL, exclToken, token);

  return token;
}

Token *ledExclamation(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  throwException(INVALID_SYMBOL_PLACEMENT, leftToken, "'%s' should not appear at here.", leftToken->str);
}

Token *nudTilde(Token *tildeToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  Token *token;
  int value;

  token = evaluate(expression, BITWISE_NOT_BP);

  value = getTokenIntegerValue(token);
  value = ~value;
  token = newFloatToken(value, NULL, tildeToken, token);
  return token;

}

Token *ledTilde(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  throwException(INVALID_SYMBOL_PLACEMENT, leftToken, "'%s' should not appear at here.", leftToken->str);
}

Token *nudDoubleAmpersand(Token *doublAampToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  throwException(INVALID_SYMBOL_PLACEMENT, doublAampToken, "'%s' should not appear at here.", doublAampToken->str);
}

Token *ledDoubleAmpersand(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, LOGICAL_AND_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 && v2;
    token = newFloatToken(ans, NULL, leftToken, rightToken);

  return token;
}

Token *nudAmpersand(Token *ampToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  throwException(INVALID_SYMBOL_PLACEMENT, ampToken, "'%s' should not appear at here.", ampToken->str);
}

Token *ledAmpersand(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, BITWISE_AND_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 & v2;
    token = newFloatToken(ans, NULL, leftToken, rightToken);

    return token;
}

Token *nudDoubleVerticalBar(Token *doubleVertToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower) {
    throwException(INVALID_SYMBOL_PLACEMENT, doubleVertToken, "'%s' should not appear at here.", doubleVertToken->str);
}

Token *ledDoubleVerticalBar(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, LOGICAL_OR_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 || v2;
    token = newFloatToken(ans, NULL, leftToken, rightToken);
    return token;
}

Token *nudVerticalBar(Token *vertToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower) {
    throwException(INVALID_SYMBOL_PLACEMENT, vertToken, "'%s' should not appear at here.", vertToken->str);
}

Token *ledVerticalBar(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, BITWISE_OR_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 | v2;
    token = newFloatToken(ans, NULL, leftToken, rightToken);
    return token;
}

Token *nudCaret(Token *caretToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  throwException(INVALID_SYMBOL_PLACEMENT, caretToken, "'%s' should not appear at here.", caretToken->str);
}

Token *ledCaret(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, BITWISE_XOR_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 ^ v2;
    token = newFloatToken(ans, NULL, leftToken, rightToken);
    return token;
}

Token *nudDoubleLeftArrows(Token *doubleLeftArrToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  throwException(INVALID_SYMBOL_PLACEMENT, doubleLeftArrToken, "'%s' should not appear at here.", doubleLeftArrToken->str);
}

Token *ledDoubleLeftArrows(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, BITWISE_LEFT_SHIFTER_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 << v2;
    token = newFloatToken(ans, NULL, leftToken, rightToken);
    return token;
}

Token *nudDoubleRightArrows(Token *doubleRightArrToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  throwException(INVALID_SYMBOL_PLACEMENT, doubleRightArrToken, "'%s' should not appear at here.", doubleRightArrToken->str);
}

Token *ledDoubleRightArrows(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, BITWISE_RIGHT_SHIFTER_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 >> v2;
    token = newFloatToken(ans, NULL, leftToken, rightToken);
    return token;
}

Token *nudLeftArrow(Token *leftArrToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  throwException(INVALID_SYMBOL_PLACEMENT, leftArrToken, "'%s' should not appear at here.", leftArrToken->str);
}

Token *ledLeftArrow(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, LESSER_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 < v2;
    token = newFloatToken(ans, NULL, leftToken, rightToken);
    return token;
}

Token *nudRightArrow(Token *rightArrToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  throwException(INVALID_SYMBOL_PLACEMENT, rightArrToken, "'%s' should not appear at here.", rightArrToken->str);
}

Token *ledRightArrow(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, GREATER_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 > v2;
    token = newFloatToken(ans, NULL, leftToken, rightToken);
    return token;
}

Token *nudLeftArrowEqual(Token *leftArrEquToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  throwException(INVALID_SYMBOL_PLACEMENT, leftArrEquToken, "'%s' should not appear at here.", leftArrEquToken->str);
}

Token *ledLeftArrowEqual(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, LESSER_EQUALS_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 <= v2;
    token = newFloatToken(ans, NULL, leftToken, rightToken);
    return token;
}

Token *nudRightArrowEqual(Token *rightArrEquToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  throwException(INVALID_SYMBOL_PLACEMENT, rightArrEquToken, "'%s' should not appear at here.", rightArrEquToken->str);
}

Token *ledRightArrowEqual(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, GREATER_EQUALS_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 >= v2;
    token = newFloatToken(ans, NULL, leftToken, rightToken);
    return token;
}

Token *nudEqual(Token *equToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  throwException(UNSUPPORTED_SYMBOL, equToken, "'%s' is not supported.", equToken->str);
}

Token *ledEqual(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  throwException(UNSUPPORTED_SYMBOL, thisToken, "'%s' is not supported.", thisToken->str);
}

Token *nudDoubleEquals(Token *doubleEquToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  throwException(INVALID_SYMBOL_PLACEMENT, doubleEquToken, "'%s' should not appear at here.", doubleEquToken->str);
}

Token *ledDoubleEquals(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, EQUALS_TO_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 == v2;
    token = newFloatToken(ans, NULL, leftToken, rightToken);
    return token;
}

Token *nudExclamationEqual(Token *exclEquToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  throwException(INVALID_SYMBOL_PLACEMENT, exclEquToken, "'%s' should not appear at here.", exclEquToken->str);
}

Token *ledExclamationEqual(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, NOT_EQUALS_TO_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 != v2;
    token = newFloatToken(ans, NULL, leftToken, rightToken);
    return token;
}

Token *nudLeftBracket(Token *thisToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower) {
    Token *expr;

    expr = evaluate(expression, WEAKEST_BP);

    if(matchBracket(expression, leftBindingPower)) {
      freeToken(thisToken);
      return expr;
    }
}

Token *ledLeftBracket(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  throwException(ERR_EXPECTING_OPERATOR, thisToken, "Expecting an operator, '%s' is invalid here.", thisToken->str);
}

int matchBracket(Tokenizer *expression, uint32_t *leftBindingPower) {
  TokenInfo *thisTokenInfo;

  if(checkTokenIfItsNULL(thisToken))
    throwException(ERR_MISSING_BRACKET, thisToken, "Expected ')', but '%s' is met.", thisToken->str);//Throw exception

  else if(*(thisToken)->str == ')') {
      freeToken(thisToken);
      thisToken = getAdvanceToken(expression);
      thisTokenInfo = getTokenInfo(thisToken);
      *leftBindingPower = thisTokenInfo->bindingPower;
      //pushBackToken(expression,thisToken);
      return 1;
  }
  else
    throwException(ERR_MISSING_BRACKET, thisToken, "Expected ')', but ''%s'' is met.", thisToken->str);//Throw exception
}
