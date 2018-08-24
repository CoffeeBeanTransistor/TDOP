#include "Operator.h"
#include "Tokenizer.h"
#include "TokenData.h"
#include "Evaluate.h"
#include "Token.h"
#include "Exception.h"
#include "Error.h"



Token *nudInt (Token *thisToken, Tokenizer *expression) {
      return thisToken;
}

Token *ledInt (Token *intToken, Token *thisToken, Tokenizer *expression) {
    throwException(INVALID_SYMBOL_PLACEMENT, intToken, "''%s'' should not appear at here.", intToken->str);
}

Token *nudFloat(Token *floatToken, Tokenizer *expression) {
  return floatToken;
}

Token *ledFloat (Token *leftToken, Token *thisToken, Tokenizer *expression) {
    throwException(INVALID_SYMBOL_PLACEMENT, leftToken, "''%s'' should not appear at here.", leftToken->str);
}

Token *nudPlus(Token *plusToken, Tokenizer *expression) {
  return _evaluate(expression, ADDITION_BP);
}

Token *ledPlus(Token *leftToken, Token *thisToken, Tokenizer *expression){
  Token  *rightToken, *token;
  double v1, v2, ans;

    rightToken = _evaluate(expression, ADDITION_BP);
    v1 = getTokenValue(leftToken);
    v2 = getTokenValue(rightToken);
    ans =  v1 + v2;
    token = newFloatToken(ans, leftToken, rightToken);

  return token;
}

Token *nudNegative(Token *minusToken, Tokenizer *expression) {
  double value;
  Token *token;


    token = _evaluate(expression, UNARY_MINUS_BP);
    value = getTokenValue(token);
    value = -value;
    token = newFloatToken(value,minusToken,token);
    token->symbol = NEGATIVE_SYMBOL;
    freeToken(minusToken);
    return token;
}

Token *ledMinus(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  double v1, v2, ans;

    rightToken = _evaluate(expression, SUBTRACTION_BP);
    v1 = getTokenValue(leftToken);
    v2 = getTokenValue(rightToken);
    ans =  v1 - v2;
    token = newFloatToken(ans, leftToken, rightToken);
    return token;
}

Token *nudAsterisk (Token *astToken, Tokenizer *expression) {
  throwException(INVALID_SYMBOL_PLACEMENT, astToken, "'%s' should not appear at here.", astToken->str);
}

Token *ledAsterisk(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  double v1, v2, ans;

    rightToken = _evaluate(expression, MULTIPLICATION_BP);
    v1 = getTokenValue(leftToken);
    v2 = getTokenValue(rightToken);
    ans =  v1 * v2;
    token = newFloatToken(ans, leftToken, rightToken);
    return token;
}

Token *nudSlash (Token *slashToken, Tokenizer *expression) {
  throwException(INVALID_SYMBOL_PLACEMENT, slashToken, "'%s' should not appear at here.", slashToken->str);
}

Token *ledSlash(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  double v1, v2, ans;

    rightToken = _evaluate(expression, DIVISION_BP);
    v1 = getTokenValue(leftToken);
    v2 = getTokenValue(rightToken);

    if(v2 == 0)
      throwException(ERR_UNDEFINED, rightToken, "The expression cannot be divided by 0!");
    else {
    ans =  v1 / v2;
    token = newFloatToken(ans, leftToken, rightToken);
    return token;
    }
}

Token *nudPercent (Token *percToken, Tokenizer *expression) {
  throwException(INVALID_SYMBOL_PLACEMENT, percToken, "'%s' should not appear at here.", percToken->str);
}

Token *ledPercent(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = _evaluate(expression, REMAINDER_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    if(v2 == 0)
      throwException(ERR_UNDEFINED, rightToken, "The expression cannot be modulo by 0!");
    else {
    ans =  v1 % v2;
    token = newFloatToken(ans, leftToken, rightToken);
    return token;
    }
}

Token *nudExclamation(Token *exclToken, Tokenizer *expression) {
  Token *token;

  token = _evaluate(expression, LOGICAL_NOT_BP);

  if(getTokenIntegerValue(token) != 0)
    token = newFloatToken(0, exclToken, token);

  else
    token = newFloatToken(1, exclToken, token);

  return token;
}

Token *ledExclamation(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  throwException(INVALID_SYMBOL_PLACEMENT, thisToken, "'%s' should not appear at here.", thisToken->str);
}

Token *nudTilde(Token *tildeToken, Tokenizer *expression) {
  Token *token;
  int value;

  token = _evaluate(expression, BITWISE_NOT_BP);

  value = getTokenIntegerValue(token);
  value = ~value;
  token = newFloatToken(value, tildeToken, token);
  return token;

}

Token *ledTilde(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  throwException(INVALID_SYMBOL_PLACEMENT, thisToken, "'%s' should not appear at here.", thisToken->str);
}

Token *nudDoubleAmpersand(Token *doublAampToken, Tokenizer *expression) {
  throwException(INVALID_SYMBOL_PLACEMENT, doublAampToken, "'%s' should not appear at here.", doublAampToken->str);
}

Token *ledDoubleAmpersand(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = _evaluate(expression, LOGICAL_AND_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 && v2;
    token = newFloatToken(ans, leftToken, rightToken);

  return token;
}

Token *nudAmpersand(Token *ampToken, Tokenizer *expression) {
  throwException(INVALID_SYMBOL_PLACEMENT, ampToken, "'%s' should not appear at here.", ampToken->str);
}

Token *ledAmpersand(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = _evaluate(expression, BITWISE_AND_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 & v2;
    token = newFloatToken(ans, leftToken, rightToken);

    return token;
}

Token *nudDoubleVerticalBar(Token *doubleVertToken, Tokenizer *expression) {
    throwException(INVALID_SYMBOL_PLACEMENT, doubleVertToken, "'%s' should not appear at here.", doubleVertToken->str);
}

Token *ledDoubleVerticalBar(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = _evaluate(expression, LOGICAL_OR_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 || v2;
    token = newFloatToken(ans, leftToken, rightToken);
    return token;
}

Token *nudVerticalBar(Token *vertToken, Tokenizer *expression) {
    throwException(INVALID_SYMBOL_PLACEMENT, vertToken, "'%s' should not appear at here.", vertToken->str);
}

Token *ledVerticalBar(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = _evaluate(expression, BITWISE_OR_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 | v2;
    token = newFloatToken(ans, leftToken, rightToken);
    return token;
}

Token *nudCaret(Token *caretToken, Tokenizer *expression) {
  throwException(INVALID_SYMBOL_PLACEMENT, caretToken, "'%s' should not appear at here.", caretToken->str);
}

Token *ledCaret(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = _evaluate(expression, BITWISE_XOR_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 ^ v2;
    token = newFloatToken(ans, leftToken, rightToken);
    return token;
}

Token *nudDoubleLeftArrows(Token *doubleLeftArrToken, Tokenizer *expression) {
  throwException(INVALID_SYMBOL_PLACEMENT, doubleLeftArrToken, "'%s' should not appear at here.", doubleLeftArrToken->str);
}

Token *ledDoubleLeftArrows(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = _evaluate(expression, BITWISE_LEFT_SHIFTER_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 << v2;
    token = newFloatToken(ans, leftToken, rightToken);
    return token;
}

Token *nudDoubleRightArrows(Token *doubleRightArrToken, Tokenizer *expression) {
  throwException(INVALID_SYMBOL_PLACEMENT, doubleRightArrToken, "'%s' should not appear at here.", doubleRightArrToken->str);
}

Token *ledDoubleRightArrows(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = _evaluate(expression, BITWISE_RIGHT_SHIFTER_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 >> v2;
    token = newFloatToken(ans, leftToken, rightToken);
    return token;
}

Token *nudLeftArrow(Token *leftArrToken, Tokenizer *expression) {
  throwException(INVALID_SYMBOL_PLACEMENT, leftArrToken, "'%s' should not appear at here.", leftArrToken->str);
}

Token *ledLeftArrow(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = _evaluate(expression, LESSER_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 < v2;
    token = newFloatToken(ans, leftToken, rightToken);
    return token;
}

Token *nudRightArrow(Token *rightArrToken, Tokenizer *expression) {
  throwException(INVALID_SYMBOL_PLACEMENT, rightArrToken, "'%s' should not appear at here.", rightArrToken->str);
}

Token *ledRightArrow(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = _evaluate(expression, GREATER_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 > v2;
    token = newFloatToken(ans, leftToken, rightToken);
    return token;
}

Token *nudLeftArrowEqual(Token *leftArrEquToken, Tokenizer *expression) {
  throwException(INVALID_SYMBOL_PLACEMENT, leftArrEquToken, "'%s' should not appear at here.", leftArrEquToken->str);
}

Token *ledLeftArrowEqual(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = _evaluate(expression, LESSER_EQUALS_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 <= v2;
    token = newFloatToken(ans, leftToken, rightToken);
    return token;
}

Token *nudRightArrowEqual(Token *rightArrEquToken, Tokenizer *expression) {
  throwException(INVALID_SYMBOL_PLACEMENT, rightArrEquToken, "'%s' should not appear at here.", rightArrEquToken->str);
}

Token *ledRightArrowEqual(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = _evaluate(expression, GREATER_EQUALS_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 >= v2;
    token = newFloatToken(ans, leftToken, rightToken);
    return token;
}

Token *nudEqual(Token *equToken, Tokenizer *expression) {
  throwException(INVALID_SYMBOL_PLACEMENT, equToken, "'%s' should not appear at here.", equToken->str);
}

Token *ledEqual(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  throwException(UNSUPPORTED_SYMBOL, thisToken, "'%s' is not supported.", thisToken->str);
}

Token *nudDoubleEquals(Token *doubleEquToken, Tokenizer *expression) {
  throwException(INVALID_SYMBOL_PLACEMENT, doubleEquToken, "'%s' should not appear at here.", doubleEquToken->str);
}

Token *ledDoubleEquals(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = _evaluate(expression, EQUALS_TO_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 == v2;
    token = newFloatToken(ans, leftToken, rightToken);
    return token;
}

Token *nudExclamationEqual(Token *exclEquToken, Tokenizer *expression) {
  throwException(INVALID_SYMBOL_PLACEMENT, exclEquToken, "'%s' should not appear at here.", exclEquToken->str);
}

Token *ledExclamationEqual(Token *leftToken, Token *thisToken, Tokenizer *expression) {
  Token  *rightToken, *token;
  int v1, v2, ans;

    rightToken = _evaluate(expression, NOT_EQUALS_TO_BP);

    v1 = getTokenIntegerValue(leftToken);
    v2 = getTokenIntegerValue(rightToken);
    ans =  v1 != v2;
    token = newFloatToken(ans, leftToken, rightToken);
    return token;
}

Token *nudLeftBracket(Token *leftBracketToken, Tokenizer *expression) {
    Token *expr;

    expr = _evaluate(expression, OPENING_BRACKET_BP);

    if(matchBracket(expression)) {
      freeToken(leftBracketToken);
      return expr;
    }
}

Token *ledLeftBracket(Token *leftToken, Token *leftBracketToken, Tokenizer *expression) {
  throwException(ERR_EXPECTING_OPERATOR, leftBracketToken, "Expecting an operator, '%s' is invalid here.", leftBracketToken->str);
}

Token *nudRightBracket(Token *rightBracketToken, Tokenizer *expression) {
  throwException(ERR_EXPECTING_OPERAND, rightBracketToken, "Expecting an operand, but '%s' is met.", rightBracketToken->str);
}

Token *ledRightBracket(Token *leftToken, Token *rightBracketToken, Tokenizer *expression) {
  throwException(ERR_MISSING_BRACKET, rightBracketToken, "Incomplete bracket, '%s is missing a left bracket.'", rightBracketToken->str);
}

int matchBracket(Tokenizer *expression) {
  TokenInfo *thisTokenInfo;
  Token *thisToken;

  thisToken = getAdvanceToken(expression);
  if(checkTokenIfItsNULL(thisToken))
    throwException(ERR_MISSING_BRACKET, thisToken, "Expected ')', but '%s' is met.", thisToken->str);//Throw exception

  else if(*(thisToken)->str == ')') {
      freeToken(thisToken);
      return 1;
  }
  else
    throwException(ERR_MISSING_BRACKET, thisToken, "Expected ')', but ''%s'' is met.", thisToken->str);//Throw exception
}

Token *nudNULL(Token *nullToken, Tokenizer *expression) {
    throwException(ERR_EXPECTING_OPERAND, nullToken, "Expecting an operand, but '%s' is met.", nullToken->str);
}
