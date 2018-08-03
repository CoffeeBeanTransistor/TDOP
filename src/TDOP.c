#include "TDOP.h"
#include "Tokenizer.h"
#include "TokenData.h"
#include "Operator.h"

Token *thisToken;
uint32_t leftBindingPower = 0;

Token *TDOP(Tokenizer *expression) {
  thisToken = getNextToken(expression);
  return evaluate(expression, 0);
}

Token *evaluate(Tokenizer *expression, int rightBindingPower) {
  Token  *leftToken, *t;
  TokenInfo *thisTokenInfo, *leftTokenInfo, *tTokenInfo;

  t = thisToken;
  thisToken = getNextToken(expression);
  thisTokenInfo = getTokenInfo(thisToken);
  leftBindingPower = thisTokenInfo->bindingPower;

  tTokenInfo = getTokenInfo(t);
  leftToken = tTokenInfo->nud(t, expression, leftBindingPower);

  while (rightBindingPower < leftBindingPower) {
    t = thisToken;
    tTokenInfo = getTokenInfo(t);
    thisToken = getNextToken(expression);
    leftToken = tTokenInfo->led(leftToken, expression);
  }

  return leftToken;

}
