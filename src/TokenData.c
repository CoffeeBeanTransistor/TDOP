#include "TokenData.h"
#include "TDOP.h"

#define INTEGER_SYMBOL 256
#define FLOAT_SYMBOL 257
#define NULL_SYMBOL 258

TokenInfo symbolMapTable[500] = {
  ['+'] = {.bindingPower = ADDITION_BP, .nud = nudPlus, .led = ledPlus},
  ['-'] = {.bindingPower = SUBTRACTION_BP, .nud = nudMinus, .led = ledMinus},
  /*['*'] = {.bindingPower = MULTIPLICATION_BP, .nud = nudAsterisk, .led = ledAsterisk},
  ['/'] = {.bindingPower = DIVISION_BP, .nud = NULL, .led = ledSlash},
  ['%'] = {.bindingPower = REMAINDER_BP, .nud = NULL, .led = ledPercent},
  ['!'] = {.bindingPower = LOGICAL_NOT_BP, .nud = nudExclamation, .led = NULL},*/
  [INTEGER_SYMBOL] = {.nud = nudInt},
  [FLOAT_SYMBOL] = {.nud = nudFloat},
  [NULL_SYMBOL] = {.bindingPower = WEAKEST},
};

TokenInfo *getTokenInfo(Token *token) {

  if(token->type == TOKEN_INTEGER_TYPE)
    return &symbolMapTable[INTEGER_SYMBOL];

  /*else if(token->type == TOKEN_FLOAT_TYPE)
    return &symbolMapTable[FLOAT_SYMBOL];*/

  else if(token->type == TOKEN_OPERATOR_TYPE)
    return &symbolMapTable[token->str[0]];

  else if(token->type == TOKEN_NULL_TYPE)
    return &symbolMapTable[NULL_SYMBOL];
}


Token *nudInt (Token *thisToken, Tokenizer *expression) {
  return thisToken;
}

Token *nudFloat (Token *thisToken, Tokenizer *expression) {
  return thisToken;
}

Token *nudPlus(Token *thisToken, Tokenizer *expression) {
  return evaluate(expression, UNARY_PLUS_BP);
}

Token *ledPlus (Token *leftToken, Tokenizer *expression){
  Token *intToken;
  FloatToken *floatToken;

  if(leftToken->type == TOKEN_INTEGER_TYPE)
    ((IntegerToken *)intToken)->value = ((IntegerToken *)leftToken)->value + ((IntegerToken *)evaluate(expression, ADDITION_BP))->value;

  return intToken;
}

Token *nudMinus(Token *thisToken, Tokenizer *expression) {
  Token *negToken;

  negToken = evaluate(expression, UNARY_MINUS_BP);
  ((IntegerToken *)negToken)->value = -(((IntegerToken *)negToken)->value);

  return negToken;
}

Token *ledMinus (Token *leftToken, Tokenizer *expression) {

}
