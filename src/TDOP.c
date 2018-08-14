#include "TDOP.h"
#include "Tokenizer.h"
#include "TokenData.h"
#include "Operator.h"
#include "Error.h"

Token *thisToken;
uint32_t leftBindingPower;

Token *TDOP(Tokenizer *expression) {
  Token *token;
  thisToken = getAdvanceToken(expression);
  if(thisToken->type == TOKEN_NULL_TYPE)
    throwException(ERR_INVALID_EXPRESSION,thisToken,"The expression is empty!");
  else {
    token = evaluate(expression, WEAKEST_BP);
    return token;
  }
}

Token *evaluate(Tokenizer *expression, int rightBindingPower) {
  Token  *leftToken, *t;
  TokenInfo *thisTokenInfo, *leftTokenInfo, *tTokenInfo;

  t = thisToken;
  thisToken = getAdvanceToken(expression);
  thisTokenInfo = getTokenInfo(thisToken);
  leftBindingPower = thisTokenInfo->bindingPower;
  leftToken = getNud(t, thisToken, expression, &leftBindingPower);

  while (rightBindingPower < leftBindingPower) {
    t = thisToken;
    thisToken = getAdvanceToken(expression);
    leftToken = getLed(t, leftToken, expression);
  }
  return leftToken;
}
