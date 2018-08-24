#include "Evaluate.h"
#include "Tokenizer.h"
#include "TokenData.h"
#include "Operator.h"
#include "Error.h"

Token *evaluate(Tokenizer *expression) {

  Token *token = _evaluate(expression, 0);
  Token *errToken = getToken(expression);

  if(errToken->type != TOKEN_NULL_TYPE) {
    throwException(ERR_EXPECTING_OPERATOR, errToken, "Expecting an operator before '%s'.", errToken->str);
  }
  else
    return token;
}

Token *_evaluate(Tokenizer *expression, int rightBindingPower) {
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
