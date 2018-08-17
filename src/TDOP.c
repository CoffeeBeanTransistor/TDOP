#include "TDOP.h"
#include "Tokenizer.h"
#include "TokenData.h"
#include "Operator.h"
#include "Error.h"

Token *evaluate(Tokenizer *expression, int rightBindingPower) {
  Token  *leftToken, *thisToken;
  TokenInfo *thisTokenInfo;
  uint32_t leftBindingPower;

  thisToken = getAdvanceToken(expression);
  leftToken = getNud(thisToken, expression);

  thisToken = getAdvanceToken(expression);
  thisTokenInfo = getTokenInfo(thisToken);
  leftBindingPower = thisTokenInfo->bindingPower;

  while (rightBindingPower < leftBindingPower) {
    leftToken = getLed(thisToken, leftToken, expression);
    thisToken = getAdvanceToken(expression);
    thisTokenInfo = getTokenInfo(thisToken);
    leftBindingPower = thisTokenInfo->bindingPower;
  }
  pushBackToken(expression, thisToken);
  return leftToken;
}
