#include "Operator.h"
#include "Tokenizer.h"
#include "TokenData.h"
#include "TDOP.h"
#include "Token.h"

Token *nudInt (Token *thisToken, Tokenizer *expression) {
  return thisToken;
}

Token *nudFloat(Token *thisToken, Tokenizer *expression) {
  return thisToken;
}

Token *nudPlus(Token *thisToken, Tokenizer *expression) {
  return evaluate(expression, UNARY_PLUS_BP);
}

Token *ledPlus(Token *leftToken, Tokenizer *expression){
  Token *intToken;

    ((IntegerToken *)intToken)->value = ((IntegerToken *)leftToken)->value + ((IntegerToken *)evaluate(expression, ADDITION_BP))->value;

  return intToken;
}

Token *nudMinus(Token *thisToken, Tokenizer *expression) {
  Token *negtoken;

    negtoken = evaluate(expression, UNARY_MINUS_BP);
    ((IntegerToken *)negtoken)->value = -(((IntegerToken *)negtoken)->value);

    return negtoken;
}

Token *ledMinus(Token *leftToken, Tokenizer *expression) {
  Token *intToken;

    ((IntegerToken *)intToken)->value = ((IntegerToken *)leftToken)->value - ((IntegerToken *)evaluate(expression, SUBTRACTION_BP))->value;

  return intToken;
}

Token *nudAsterisk(Token *thisToken, Tokenizer *expression) {
  //return evaluate(expression, UNARY_PLUS_BP);
}

Token *ledAsterisk(Token *leftToken, Tokenizer *expression) {
  Token *intToken;

    ((IntegerToken *)intToken)->value = ((IntegerToken *)leftToken)->value * ((IntegerToken *)evaluate(expression, MULTIPLICATION_BP))->value;

  return intToken;
}

Token *ledSlash(Token *leftToken, Tokenizer *expression) {
  Token *intToken;

    ((IntegerToken *)intToken)->value = ((IntegerToken *)leftToken)->value / ((IntegerToken *)evaluate(expression, DIVISION_BP))->value;

  return intToken;
}

Token *ledPercent(Token *leftToken, Tokenizer *expression) {
  Token *intToken;

    ((IntegerToken *)intToken)->value = ((IntegerToken *)leftToken)->value % ((IntegerToken *)evaluate(expression, MULTIPLICATION_BP))->value;

  return intToken;
}

Token *nudExclamation(Token *thisToken, Tokenizer *expression) {
  Token *token;

  token = evaluate(expression, LOGICAL_NOT_BP);
  if(((IntegerToken *)token)->value > 0)
    ((IntegerToken *)thisToken)->value = 0;

  else
    ((IntegerToken *)thisToken)->value = 1;
}
