#include "Operator.h"
#include "Tokenizer.h"
#include "TokenData.h"
#include "TDOP.h"
#include "Token.h"


Token *nudInt (Token *thisToken, Tokenizer *expression, uint32_t leftBindingPower) {
  return thisToken;
}

Token *nudFloat(Token *thisToken, Tokenizer *expression, uint32_t leftBindingPower) {
  return thisToken;
}

Token *nudPlus(Token *thisToken, Tokenizer *expression, uint32_t leftBindingPower) {
  return evaluate(expression, UNARY_PLUS_BP);
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

Token *nudMinus(Token *thisToken, Tokenizer *expression, uint32_t leftBindingPower) {
  Token *token;
  int value;

    token = evaluate(expression, UNARY_MINUS_BP);
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

Token *nudAsterisk(Token *thisToken, Tokenizer *expression, uint32_t leftBindingPower) {
  //return evaluate(expression, UNARY_PLUS_BP);
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

Token *nudExclamation(Token *thisToken, Tokenizer *expression, uint32_t leftBindingPower) {
  Token *token;

  token = evaluate(expression, LOGICAL_NOT_BP);
  if(((IntegerToken *)token)->value > 0)
    ((IntegerToken *)thisToken)->value = 0;

  else
    ((IntegerToken *)thisToken)->value = 1;
}

Token *nudLeftBracket(Token *thisToken, Tokenizer *expression, uint32_t leftBindingPower) {
    /*Token *expr = evaluate(expression, WEAKEST);

    if(matchBracket(expr, ')'));
    return 1;*/
}

int *matchBracket(Token *thisToken, char closing) {
  /*Token *expr;
  expr = thisToken;
  return 1;*/
}
