#include "Operator.h"
#include "Tokenizer.h"
#include "TokenData.h"
#include "TDOP.h"
#include "Token.h"
#include "Exception.h"
#include "Error.h"


Token *thisToken;

Token *nudInt (Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  return thisToken;
}

Token *ledInt (Token *leftToken, Tokenizer *expression) {
    throwException(INVALID_SYMBOL_PLACEMENT, leftToken, "''%s'' should not appear at here.", leftToken->str);
}

Token *nudFloat(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  return thisToken;
}

Token *ledFloat (Token *leftToken, Tokenizer *expression) {
    throwException(INVALID_SYMBOL_PLACEMENT, leftToken, "''%s'' should not appear at here.", leftToken->str);
}

Token *nudPlus(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  return evaluate(expression, ADDITION_BP);
}

Token *ledPlus(Token *leftToken, Tokenizer *expression){
  Token  *rightToken, *token;
  double v1, v2, ans;

    rightToken = evaluate(expression, ADDITION_BP);
    v1 = getTokenValue(leftToken);
    v2 = getTokenValue(rightToken);
    ans =  v1 + v2;
    token = newFloatToken(ans, token, leftToken, rightToken);

  return token;
}

Token *nudNegative(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  double value;
  Token *token;

    token = evaluate(expression, UNARY_MINUS_BP);
    value = getTokenValue(token);
    value = -value;
    token = newFloatToken(value,token,thisToken,token);
    return token;
}

Token *ledNegative (Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  double v1, v2, ans;

    rightToken = evaluate(expression, SUBTRACTION_BP);
    v1 = getTokenValue(leftToken);
    v2 = getTokenValue(rightToken);
    ans =  v1 - v2;
    token = newFloatToken(ans, token, leftToken, rightToken);
    return token;
}

Token *nudMinus(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  double value;
  Token *token;

    token = evaluate(expression, SUBTRACTION_BP);
    value = getTokenValue(token);
    value = -value;
    token = newFloatToken(value,token,thisToken,token);
    return token;
}

Token *ledMinus(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  double v1, v2, ans;

    rightToken = evaluate(expression, SUBTRACTION_BP);
    v1 = getTokenValue(leftToken);
    v2 = getTokenValue(rightToken);
    ans =  v1 - v2;
    token = newFloatToken(ans, token, leftToken, rightToken);
    return token;
}

Token *nudAsterisk (Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  throwException(INVALID_SYMBOL_PLACEMENT, thisToken, "'%s' should not appear at here.", thisToken->str);
}

Token *ledAsterisk(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  double v1, v2, ans;

    rightToken = evaluate(expression, MULTIPLICATION_BP);
    v1 = getTokenValue(leftToken);
    v2 = getTokenValue(rightToken);
    ans =  v1 * v2;
    token = newFloatToken(ans, token, leftToken, rightToken);
    return token;
}

Token *nudSlash (Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  throwException(INVALID_SYMBOL_PLACEMENT, thisToken, "'%s' should not appear at here.", thisToken->str);
}

Token *ledSlash(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  double v1, v2, ans;

    rightToken = evaluate(expression, DIVISION_BP);
    v1 = getTokenValue(leftToken);
    v2 = getTokenValue(rightToken);
    ans =  v1 / v2;
    token = newFloatToken(ans, token, leftToken, rightToken);
    return token;
}

Token *nudPercent (Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  throwException(INVALID_SYMBOL_PLACEMENT, thisToken, "'%s' should not appear at here.", thisToken->str);
}

Token *ledPercent(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, REMAINDER_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 % v2;
    token = newFloatToken(ans, NULL, leftToken, rightToken);

    return token;
}

Token *nudExclamation(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  Token *token;

  token = evaluate(expression, LOGICAL_NOT_BP);

  if(getTokenIntegerValue(token) != 0)
    token = newFloatToken(0, NULL, thisToken, token);

  else
    token = newFloatToken(1, NULL, thisToken, token);

  return token;
}

Token *ledExclamation(Token *leftToken, Tokenizer *expression) {
  throwException(INVALID_SYMBOL_PLACEMENT, leftToken, "'%s' should not appear at here.", leftToken->str);
}

Token *nudTilde(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  Token *token;
  int value;

  token = evaluate(expression, BITWISE_NOT_BP);

  value = getTokenIntegerValue(token);
  value = ~value;
  token = newFloatToken(value, NULL, thisToken, token);
  return token;

}

Token *ledTilde(Token *leftToken, Tokenizer *expression) {
  throwException(INVALID_SYMBOL_PLACEMENT, leftToken, "'%s' should not appear at here.", leftToken->str);
}

Token *nudDoubleAmpersand(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  throwException(INVALID_SYMBOL_PLACEMENT, thisToken, "'%s' should not appear at here.", thisToken->str);
}

Token *ledDoubleAmpersand(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, LOGICAL_AND_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 && v2;
    token = newFloatToken(ans, NULL, leftToken, rightToken);

  return token;
}

Token *nudAmpersand(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  throwException(INVALID_SYMBOL_PLACEMENT, thisToken, "'%s' should not appear at here.", thisToken->str);
}

Token *ledAmpersand(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, BITWISE_AND_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 & v2;
    token = newFloatToken(ans, NULL, leftToken, rightToken);

    return token;
}

Token *nudDoubleVerticalBar(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
    throwException(INVALID_SYMBOL_PLACEMENT, thisToken, "'%s' should not appear at here.", thisToken->str);
}

Token *ledDoubleVerticalBar(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, LOGICAL_OR_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 || v2;
    token = newFloatToken(ans, NULL, leftToken, rightToken);
    return token;
}

Token *nudVerticalBar(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
    throwException(INVALID_SYMBOL_PLACEMENT, thisToken, "'%s' should not appear at here.", thisToken->str);
}

Token *ledVerticalBar(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, BITWISE_OR_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 | v2;
    token = newFloatToken(ans, NULL, leftToken, rightToken);
    return token;
}

Token *nudCaret(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  throwException(INVALID_SYMBOL_PLACEMENT, thisToken, "'%s' should not appear at here.", thisToken->str);
}

Token *ledCaret(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, BITWISE_XOR_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 ^ v2;
    token = newFloatToken(ans, NULL, leftToken, rightToken);
    return token;
}

Token *nudDoubleLeftArrows(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  throwException(INVALID_SYMBOL_PLACEMENT, thisToken, "'%s' should not appear at here.", thisToken->str);
}

Token *ledDoubleLeftArrows(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, BITWISE_LEFT_SHIFTER_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 << v2;
    token = newFloatToken(ans, NULL, leftToken, rightToken);
    return token;
}

Token *nudDoubleRightArrows(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  throwException(INVALID_SYMBOL_PLACEMENT, thisToken, "'%s' should not appear at here.", thisToken->str);
}

Token *ledDoubleRightArrows(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, BITWISE_RIGHT_SHIFTER_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 >> v2;
    token = newFloatToken(ans, NULL, leftToken, rightToken);
    return token;
}

Token *nudLeftArrow(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  throwException(INVALID_SYMBOL_PLACEMENT, thisToken, "'%s' should not appear at here.", thisToken->str);
}

Token *ledLeftArrow(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, LESSER_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 < v2;
    token = newFloatToken(ans, NULL, leftToken, rightToken);
    return token;
}

Token *nudRightArrow(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  throwException(INVALID_SYMBOL_PLACEMENT, thisToken, "'%s' should not appear at here.", thisToken->str);
}

Token *ledRightArrow(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, GREATER_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 > v2;
    token = newFloatToken(ans, NULL, leftToken, rightToken);
    return token;
}

Token *nudLeftArrowEqual(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  throwException(INVALID_SYMBOL_PLACEMENT, thisToken, "'%s' should not appear at here.", thisToken->str);
}

Token *ledLeftArrowEqual(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, LESSER_EQUALS_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 <= v2;
    token = newFloatToken(ans, NULL, leftToken, rightToken);
    return token;
}

Token *nudRightArrowEqual(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  throwException(INVALID_SYMBOL_PLACEMENT, thisToken, "'%s' should not appear at here.", thisToken->str);
}

Token *ledRightArrowEqual(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, GREATER_EQUALS_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 >= v2;
    token = newFloatToken(ans, NULL, leftToken, rightToken);
    return token;
}

Token *nudEqual(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  throwException(UNSUPPORTED_SYMBOL, thisToken, "'%s' is not supported.", thisToken->str);
}

Token *ledEqual(Token *leftToken, Tokenizer *expression) {
  throwException(UNSUPPORTED_SYMBOL, thisToken, "'%s' is not supported.", thisToken->str);
}

Token *nudDoubleEquals(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  throwException(INVALID_SYMBOL_PLACEMENT, thisToken, "'%s' should not appear at here.", thisToken->str);
}

Token *ledDoubleEquals(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, EQUALS_TO_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 == v2;
    token = newFloatToken(ans, NULL, leftToken, rightToken);
    return token;
}

Token *nudExclamationEqual(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  throwException(INVALID_SYMBOL_PLACEMENT, thisToken, "'%s' should not appear at here.", thisToken->str);
}

Token *ledExclamationEqual(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, NOT_EQUALS_TO_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 != v2;
    token = newFloatToken(ans, NULL, leftToken, rightToken);
    return token;
}

Token *nudLeftBracket(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
    Token *expr, *token;
    TokenInfo *thisTokenInfo;

    expr = evaluate(expression, WEAKEST_BP);

    if(matchBracket(expression, leftBindingPower))
      return expr;
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
    return 1;
  }
  else
    throwException(ERR_MISSING_BRACKET, thisToken, "Expected ')', but ''%s'' is met.", thisToken->str);//Throw exception
}
