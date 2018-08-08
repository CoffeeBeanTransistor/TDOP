#include "Operator.h"
#include "Tokenizer.h"
#include "TokenData.h"
#include "TDOP.h"
#include "Token.h"

Token *thisToken;

Token *nudInt (Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  return thisToken;
}

Token *nudFloat(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  return thisToken;
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
    token = newFloatToken(ans,token);

  return token;
}

Token *nudNegative(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  double value;
  Token *token;

    token = evaluate(expression, UNARY_MINUS_BP);
    value = getTokenValue(token);
    value = -value;
    token = newFloatToken(value,token);
    return token;
}

Token *ledNegative (Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  double v1, v2, ans;

    rightToken = evaluate(expression, SUBTRACTION_BP);
    v1 = getTokenValue(leftToken);
    v2 = getTokenValue(rightToken);
    ans =  v1 - v2;
    token = newFloatToken(ans,token);
    return token;
}

Token *nudMinus(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  double value;
  Token *token;

    token = evaluate(expression, SUBTRACTION_BP);
    value = getTokenValue(token);
    value = -value;
    token = newFloatToken(value,token);
    return token;
}

Token *ledMinus(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  double v1, v2, ans;

    rightToken = evaluate(expression, SUBTRACTION_BP);
    v1 = getTokenValue(leftToken);
    v2 = getTokenValue(rightToken);
    ans =  v1 - v2;
    token = newFloatToken(ans,token);
    return token;
}

Token *ledAsterisk(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  double v1, v2, ans;

    rightToken = evaluate(expression, MULTIPLICATION_BP);
    v1 = getTokenValue(leftToken);
    v2 = getTokenValue(rightToken);
    ans =  v1 * v2;
    token = newFloatToken(ans,token);
    return token;
}

Token *ledSlash(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  double v1, v2, ans;

    rightToken = evaluate(expression, DIVISION_BP);
    v1 = getTokenValue(leftToken);
    v2 = getTokenValue(rightToken);
    ans =  v1 / v2;
    token = newFloatToken(ans,token);
    return token;
}

Token *ledPercent(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, REMAINDER_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 % v2;
    token = newFloatToken(ans, NULL);

    return token;
}

Token *nudExclamation(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  Token *token;

  token = evaluate(expression, LOGICAL_NOT_BP);

  if(getTokenIntegerValue(token) != 0)
    token = newFloatToken(0, NULL);

  else
    token = newFloatToken(1, NULL);

  return token;
}

Token *nudTilde(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  Token *token;
  int value;

  token = evaluate(expression, BITWISE_NOT_BP);

  value = getTokenIntegerValue(token);
  value = ~value;
  token = newFloatToken(value,NULL);
  return token;

}

Token *ledDoubleAmpersand(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, LOGICAL_AND_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 && v2;
    token = newFloatToken(ans, NULL);

  return token;
}

Token *ledAmpersand(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, BITWISE_AND_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 & v2;
    token = newFloatToken(ans, NULL);

    return token;
}

Token *ledDoubleVerticalBar(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, LOGICAL_OR_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 || v2;
    token = newFloatToken(ans, NULL);
    return token;
}

Token *ledVerticalBar(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, BITWISE_OR_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 | v2;
    token = newFloatToken(ans, NULL);
    return token;
}

Token *ledCaret(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, BITWISE_XOR_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 ^ v2;
    token = newFloatToken(ans, NULL);
    return token;
}

Token *ledDoubleLeftArrows(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, BITWISE_LEFT_SHIFTER_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 << v2;
    token = newFloatToken(ans, NULL);
    return token;
}

Token *ledDoubleRightArrows(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, BITWISE_RIGHT_SHIFTER_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 >> v2;
    token = newFloatToken(ans, NULL);
    return token;
}

Token *ledLeftArrow(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, LESSER_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 < v2;
    token = newFloatToken(ans, NULL);
    return token;
}

Token *ledRightArrow(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, GREATER_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 > v2;
    token = newFloatToken(ans, NULL);
    return token;
}


Token *ledLeftArrowEqual(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, LESSER_EQUALS_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 <= v2;
    token = newFloatToken(ans, NULL);
    return token;
}

Token *ledRightArrowEqual(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, GREATER_EQUALS_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 >= v2;
    token = newFloatToken(ans, NULL);
    return token;
}

Token *ledDoubleEquals(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, EQUALS_TO_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 == v2;
    token = newFloatToken(ans, NULL);
    return token;
}

Token *ledExclamationEqual(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = evaluate(expression, NOT_EQUALS_TO_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 != v2;
    token = newFloatToken(ans, NULL);
    return token;
}

Token *nudLeftBracket(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
    Token *expr, *token;
    TokenInfo *thisTokenInfo;

    expr = evaluate(expression, WEAKEST_BP);
    if(matchBracket(expression, ')', leftBindingPower)) {
      return expr;
    }
    else
      return expr; //Throw exception
}

int matchBracket(Tokenizer *expression, char closing, uint32_t *leftBindingPower) {
  TokenInfo *thisTokenInfo;

  if(*(thisToken)->str == closing) {
    freeToken(thisToken);
    thisToken = getNextToken(expression);
    thisTokenInfo = getTokenInfo(thisToken);
    *leftBindingPower = thisTokenInfo->bindingPower;
    return 1;
  }
  else
    return 0;
}
