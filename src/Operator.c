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
  Token  *rightToken;
  int v1, v2, ans;

    rightToken = evaluate(expression, ADDITION_BP);
    v1 = ((IntegerToken *)leftToken)->value;
    v2 = ((IntegerToken *)rightToken)->value;
    ans =  v1 + v2;
    ((IntegerToken *)leftToken)->value = ans;

  return leftToken;
}

Token *nudNegative(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  Token *token;
  int value;

    token = evaluate(expression, UNARY_MINUS_BP);
    value = ((IntegerToken *)token)->value;
    value = -value;
    ((IntegerToken *)token)->value = value;
    return token;
}

Token *ledNegative (Token *leftToken, Tokenizer *expression) {
  Token  *rightToken;
  int v1, v2, ans;

    rightToken = evaluate(expression, SUBTRACTION_BP);
    v1 = ((IntegerToken *)leftToken)->value;
    v2 = ((IntegerToken *)rightToken)->value;
    ans =  v1 - v2;
    ((IntegerToken *)leftToken)->value = ans;

    return leftToken;
}

Token *nudMinus(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  Token *token;
  int value;

    token = evaluate(expression, SUBTRACTION_BP);
    value = ((IntegerToken *)token)->value;
    value = -value;
    ((IntegerToken *)token)->value = value;
    return token;
}

Token *ledMinus(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken;
  int v1, v2, ans;

    rightToken = evaluate(expression, SUBTRACTION_BP);
    v1 = ((IntegerToken *)leftToken)->value;
    v2 = ((IntegerToken *)rightToken)->value;
    ans =  v1 - v2;
    ((IntegerToken *)leftToken)->value = ans;

    return leftToken;
}

Token *ledAsterisk(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken;
  int v1, v2, ans;

    rightToken = evaluate(expression, MULTIPLICATION_BP);
    v1 = ((IntegerToken *)leftToken)->value;
    v2 = ((IntegerToken *)rightToken)->value;
    ans =  v1 * v2;
    ((IntegerToken *)leftToken)->value = ans;

  return leftToken;
}

Token *ledSlash(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken;
  int v1, v2, ans;

    rightToken = evaluate(expression, DIVISION_BP);
    v1 = ((IntegerToken *)leftToken)->value;
    v2 = ((IntegerToken *)rightToken)->value;
    ans =  v1 / v2;
    ((IntegerToken *)leftToken)->value = ans;

  return leftToken;
}

Token *ledPercent(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken;
  int v1, v2, ans;

    rightToken = evaluate(expression, ADDITION_BP);
    v1 = ((IntegerToken *)leftToken)->value;
    v2 = ((IntegerToken *)rightToken)->value;
    ans =  v1 % v2;
    ((IntegerToken *)leftToken)->value = ans;

  return leftToken;
}

Token *nudExclamation(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  Token *token;

  token = evaluate(expression, LOGICAL_NOT_BP);

  if(((IntegerToken *)token)->value > 0)
    ((IntegerToken *)thisToken)->value = 0;

  else
    ((IntegerToken *)thisToken)->value = 1;

  return thisToken;
}

Token *nudTilde(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {

  ((IntegerToken *)thisToken)->value = ~((IntegerToken *)evaluate(expression, BITWISE_NOT_BP))->value;
  return thisToken;

}

Token *ledDoubleAmpersand(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken;
  int v1, v2, ans;

    rightToken = evaluate(expression, LOGICAL_AND_BP);
    v1 = ((IntegerToken *)leftToken)->value;
    v2 = ((IntegerToken *)rightToken)->value;
    ans =  v1 && v2;
    ((IntegerToken *)leftToken)->value = ans;

  return leftToken;
}

Token *ledAmpersand(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken;
  int v1, v2, ans;

    rightToken = evaluate(expression, BITWISE_AND_BP);
    v1 = ((IntegerToken *)leftToken)->value;
    v2 = ((IntegerToken *)rightToken)->value;
    ans =  v1 & v2;
    ((IntegerToken *)leftToken)->value = ans;

  return leftToken;
}

Token *ledDoubleVerticalBar(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken;
  int v1, v2, ans;

    rightToken = evaluate(expression, LOGICAL_OR_BP);
    v1 = ((IntegerToken *)leftToken)->value;
    v2 = ((IntegerToken *)rightToken)->value;
    ans =  v1 || v2;
    ((IntegerToken *)leftToken)->value = ans;

  return leftToken;
}

Token *ledVerticalBar(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken;
  int v1, v2, ans;

    rightToken = evaluate(expression, BITWISE_OR_BP);
    v1 = ((IntegerToken *)leftToken)->value;
    v2 = ((IntegerToken *)rightToken)->value;
    ans =  v1 | v2;
    ((IntegerToken *)leftToken)->value = ans;

  return leftToken;
}

Token *ledCaret(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken;
  int v1, v2, ans;

    rightToken = evaluate(expression, BITWISE_XOR_BP);
    v1 = ((IntegerToken *)leftToken)->value;
    v2 = ((IntegerToken *)rightToken)->value;
    ans =  v1 ^ v2;
    ((IntegerToken *)leftToken)->value = ans;

  return leftToken;
}

Token *ledDoubleLeftArrows(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken;
  int v1, v2, ans;

    rightToken = evaluate(expression, BITWISE_LEFT_SHIFTER_BP);
    v1 = ((IntegerToken *)leftToken)->value;
    v2 = ((IntegerToken *)rightToken)->value;
    ans =  v1 << v2;
    ((IntegerToken *)leftToken)->value = ans;

  return leftToken;
}

Token *ledDoubleRightArrows(Token *leftToken, Tokenizer *expression) {
  Token  *rightToken;
  int v1, v2, ans;

    rightToken = evaluate(expression, BITWISE_RIGHT_SHIFTER_BP);
    v1 = ((IntegerToken *)leftToken)->value;
    v2 = ((IntegerToken *)rightToken)->value;
    ans =  v1 >> v2;
    ((IntegerToken *)leftToken)->value = ans;

  return leftToken;
}

Token *ledLeftArrow(Token *leftToken, Tokenizer *expression) {

}

Token *ledLeftArrowEqual(Token *leftToken, Tokenizer *expression) {

}

Token *ledRightArrow(Token *leftToken, Tokenizer *expression) {

}

Token *ledRightArrowEqual(Token *leftToken, Tokenizer *expression) {

}

Token *ledDoubleEquals(Token *leftToken, Tokenizer *expression) {

}

Token *ledExclamationEqual(Token *leftToken, Tokenizer *expression) {

}

Token *nudLeftBracket(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower) {
    Token *expr, *token;
    TokenInfo *thisTokenInfo;

    expr = evaluate(expression, WEAKEST_BP);
    if(matchBracket(expression, ')', leftBindingPower)) {
      freeToken(thisToken);
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

int convertToBinary(int number, int bitLength) {

    if(number == 0)
      return 0;

    else if (bitLength != 0);
      return (number%2 + 10*convertToBinary(number/2, bitLength - 1));

}
