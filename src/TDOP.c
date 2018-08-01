#include "TDOP.h"
#include "Tokenizer.h"
#include "TokenData.h"
#include "Operator.h"

Token *thisToken;
int leftBindingPower;

Token *TDOP(Tokenizer *expression) {
  thisToken = getToken(expression);
  return evaluate(expression, 0);
}

Token *evaluate(Tokenizer *expression, int rightBindingPower) {
  Token  *leftToken, *t;
  TokenInfo *thisTokenInfo, *leftTokenInfo, *tTokenInfo;

  t = thisToken;
  thisToken = getToken(expression);
  thisTokenInfo = getTokenInfo(thisToken);
  leftBindingPower = thisTokenInfo->bindingPower;

  tTokenInfo = getTokenInfo(t);
  leftToken = tTokenInfo->nud(t, expression);

  while (rightBindingPower < leftBindingPower) {
    t = thisToken;
    tTokenInfo = getTokenInfo(t);
    thisToken = getToken(expression);
    leftToken = tTokenInfo->led(leftToken, expression);
  }

  return leftToken;

}
