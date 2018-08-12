#include "TokenData.h"
#include "TDOP.h"
#include "Token.h"
#include "Operator.h"
#include <stdint.h>
#include <string.h>
#include <malloc.h>
#include "Exception.h"
#include "Error.h"

TokenInfo symbolMapTable[256] = {
  [ADD_SYMBOL] = {.bindingPower = ADDITION_BP, .nud = nudPlus, .led = ledPlus},
  [SUB_SYMBOL] = {.bindingPower = SUBTRACTION_BP, .nud = nudMinus, .led = ledMinus},
  [NEGATIVE_SYMBOL] = {.bindingPower = UNARY_MINUS_BP, .nud = nudNegative, .led = ledNegative},
  [MUL_SYMBOL] = {.bindingPower = MULTIPLICATION_BP, .nud = nudAsterisk, .led = ledAsterisk},
  [DIV_SYMBOL] = {.bindingPower = DIVISION_BP, .nud = nudSlash, .led = ledSlash},
  [MODULO_SYMBOL] = {.bindingPower = REMAINDER_BP, .nud = nudPercent, .led = ledPercent},
  [LOGICAL_NOT_SYMBOL] = {.bindingPower = LOGICAL_NOT_BP, .nud = nudExclamation, .led = ledExclamation},
  [BITWISE_NOT_SYMBOL] = {.bindingPower = BITWISE_NOT_BP, .nud = nudTilde, .led = ledTilde},
  [LOGICAL_AND_SYMBOL] = {.bindingPower = LOGICAL_AND_BP, .nud = nudDoubleAmpersand, .led = ledDoubleAmpersand},
  [BITWISE_AND_SYMBOL] = {.bindingPower = BITWISE_AND_BP, .nud = nudAmpersand, .led = ledAmpersand},
  [LOGICAL_OR_SYMBOL] = {.bindingPower = LOGICAL_OR_BP, .nud = nudDoubleVerticalBar, .led = ledDoubleVerticalBar},
  [BITWISE_OR_SYMBOL] = {.bindingPower = BITWISE_OR_BP, .nud = nudVerticalBar, .led = ledVerticalBar},
  [BITWISE_XOR_SYMBOL] = {.bindingPower = BITWISE_XOR_BP, .nud = nudCaret, .led =ledCaret},
  [BITWISE_LEFT_SHIFTER_SYMBOL] = {.bindingPower = BITWISE_LEFT_SHIFTER_BP, .nud = nudDoubleLeftArrows, .led = ledDoubleLeftArrows},
  [BITWISE_RIGHT_SHIFTER_SYMBOL] = {.bindingPower = BITWISE_RIGHT_SHIFTER_BP, .nud = nudDoubleRightArrows, .led = ledDoubleRightArrows},
  [GREATER_SYMBOL] = {.bindingPower = GREATER_BP, .nud = nudRightArrow, .led = ledRightArrow},
  [LESSER_SYMBOL] = {.bindingPower = LESSER_BP, .nud = nudLeftArrow, .led = ledLeftArrow},
  [GREATER_EQUALS_SYMBOL] = {.bindingPower = GREATER_EQUALS_BP, .nud = nudRightArrowEqual, .led = ledRightArrowEqual},
  [LESSER_EQUALS_SYMBOL] = {.bindingPower = LESSER_EQUALS_BP, .nud = nudLeftArrowEqual, .led = ledLeftArrowEqual},
  [EQUALS_TO_SYMBOL] = {.bindingPower = EQUALS_TO_BP, .nud = nudDoubleEquals, .led = ledDoubleEquals},
  [EQUAL_SYMBOL] = {.bindingPower = EQUAL_BP, .nud = nudEqual, .led = ledEqual},
  [NOT_EQUALS_TO_SYMBOL] = {.bindingPower = NOT_EQUALS_TO_BP, .nud = nudExclamationEqual, .led = ledExclamationEqual},
  [OPENING_BRACKET_SYMBOL] = {.bindingPower = OPENING_BRACKET_BP, .nud = nudLeftBracket, .led = ledLeftBracket},
  [CLOSING_BRACKET_SYMBOL] = {.bindingPower = CLOSING_BRACKET_BP},
  [INTEGER_SYMBOL] = {.nud = nudInt, .led = ledInt},
  [FLOAT_SYMBOL] = {.nud = nudFloat, .led = ledFloat},
  [NULL_SYMBOL] = {.bindingPower = WEAKEST_BP},
};

TokenInfo *getTokenInfo(Token *token) {

  if(token->type == TOKEN_INTEGER_TYPE)
    return &symbolMapTable[INTEGER_SYMBOL];

  else if(token->type == TOKEN_FLOAT_TYPE)
    return &symbolMapTable[FLOAT_SYMBOL];

  else if(token->type == TOKEN_OPERATOR_TYPE)
    return &symbolMapTable[token->symbol];

  else if(token->type == TOKEN_NULL_TYPE)
    return &symbolMapTable[NULL_SYMBOL];

}

Token *getAdvanceToken(Tokenizer *expression) {
  Token *token1;

    token1 = getToken(expression);
    token1 = getTokenSymbol(token1,expression);
    return token1;
}

Token *getTokenSymbol(Token *token1, Tokenizer *expression) {
  Token *token2;

  if(token1->type == TOKEN_OPERATOR_TYPE) {
    token2 = getToken(expression);
      switch (*(token1)->str) {
        case '+'  : modifyToken(token1,ADD_SYMBOL);
                    pushBackToken(expression,token2);
                    break;

        case '-'  : switch (token2->type) {
                      case  TOKEN_INTEGER_TYPE  :
                        if(verifyTokensBackToBack(token1,token2)) {
                          modifyToken(token1,NEGATIVE_SYMBOL);
                          pushBackToken(expression,token2);
                        }
                        else  {
                          modifyToken(token1,SUB_SYMBOL);
                          pushBackToken(expression,token2);
                        }
                        break;

                      default :
                        modifyToken(token1,SUB_SYMBOL);
                        pushBackToken(expression,token2);
                    }
                    break;

        case '*'  :   modifyToken(token1,MUL_SYMBOL);
                      pushBackToken(expression,token2);
                      break;

        case '/'  :   modifyToken(token1,DIV_SYMBOL);
                      pushBackToken(expression,token2);
                      break;

        case '%'  :   modifyToken(token1,MODULO_SYMBOL);
                      pushBackToken(expression,token2);
                      break;

        case '&'  : switch(*(token2)->str) {
                      case '&'  :
                        if(verifyTokensBackToBack(token1,token2)) {
                          modifyToken(token1,LOGICAL_AND_SYMBOL);
                          freeToken(token2);
                        }
                        else {
                         modifyToken(token1,BITWISE_AND_SYMBOL);
                         pushBackToken(expression,token2);
                       }
                       break;

                      default  :
                        modifyToken(token1,BITWISE_AND_SYMBOL);
                        pushBackToken(expression,token2);
                    }
                    break;

        case '|'  : switch(*(token2)->str) {
                      case '|'  :
                        if(verifyTokensBackToBack(token1,token2)) {
                          modifyToken(token1,LOGICAL_OR_SYMBOL);
                          freeToken(token2);
                        }
                        else {
                          modifyToken(token1,BITWISE_OR_SYMBOL);
                          pushBackToken(expression,token2);
                        }
                        break;

                      default :
                          modifyToken(token1,BITWISE_OR_SYMBOL);
                          pushBackToken(expression,token2);
                    }
                    break;

        case '!'  : switch(*(token2)->str) {
                      case '='  :
                        if(verifyTokensBackToBack(token1,token2)) {
                          modifyToken(token1,NOT_EQUALS_TO_SYMBOL);
                          freeToken(token2);
                        }
                        else {
                          modifyToken(token1,LOGICAL_NOT_SYMBOL);
                          pushBackToken(expression,token2);
                        }
                        break;

                      default :
                          modifyToken(token1,LOGICAL_NOT_SYMBOL);
                          pushBackToken(expression,token2);
                    }
                    break;

        case '>'  : switch(*(token2)->str) {
                      case  '>' :
                        if(verifyTokensBackToBack(token1,token2)) {
                          modifyToken(token1,BITWISE_RIGHT_SHIFTER_SYMBOL);
                          freeToken(token2);
                        }
                        else {
                          modifyToken(token1,GREATER_SYMBOL);
                          pushBackToken(expression,token2);
                        }
                        break;

                      case  '=' :
                        if(verifyTokensBackToBack(token1,token2)) {
                          modifyToken(token1,GREATER_EQUALS_SYMBOL);
                          freeToken(token2);
                          }
                        else {
                          modifyToken(token1,GREATER_SYMBOL);
                          pushBackToken(expression,token2);
                        }
                        break;

                      default :
                        modifyToken(token1,GREATER_SYMBOL);
                        pushBackToken(expression,token2);
                    }
                    break;

        case '<'  : switch(*(token2)->str) {
                      case  '<' :
                        if(verifyTokensBackToBack(token1,token2)) {
                          modifyToken(token1,BITWISE_LEFT_SHIFTER_SYMBOL);
                          freeToken(token2);
                        }
                        else {
                          modifyToken(token1,LESSER_SYMBOL);
                          pushBackToken(expression,token2);
                        }
                        break;

                      case  '=' :
                        if(verifyTokensBackToBack(token1,token2)) {
                          modifyToken(token1,LESSER_EQUALS_SYMBOL);
                          freeToken(token2);
                          }
                        else {
                          modifyToken(token1,LESSER_SYMBOL);
                          pushBackToken(expression,token2);
                        }
                        break;

                      default :
                        modifyToken(token1,LESSER_SYMBOL);
                        pushBackToken(expression,token2);
                    }
                    break;

          case '='  : switch(*(token2)->str) {
                        case '='  :
                          if(verifyTokensBackToBack(token1,token2)) {
                            modifyToken(token1,EQUALS_TO_SYMBOL);
                            freeToken(token2);
                          }
                          else {
                            modifyToken(token1,EQUAL_SYMBOL);
                            pushBackToken(expression,token2);
                          }
                          break;

                        default :
                            modifyToken(token1,EQUAL_SYMBOL);
                            pushBackToken(expression,token2);
                      }
                      break;

          case '~'  :   modifyToken(token1,BITWISE_NOT_SYMBOL);
                        pushBackToken(expression,token2);
                        break;

          case '^'  :   modifyToken(token1,BITWISE_XOR_SYMBOL);
                        pushBackToken(expression,token2);
                        break;

          case '('  :   modifyToken(token1,OPENING_BRACKET_SYMBOL);
                        pushBackToken(expression,token2);
                        break;

          case ')'  :   modifyToken(token1,CLOSING_BRACKET_SYMBOL);
                        pushBackToken(expression,token2);
                        break;

          default   :   throwException(ERR_INVALID_SYMBOL, token1, "Unknown character, '%s'",token1->str);
      }
      return token1;
  }

  else if(token1->type == TOKEN_INTEGER_TYPE)
    return modifyToken(token1,INTEGER_SYMBOL);

  else if(token1->type == TOKEN_FLOAT_TYPE)
    return modifyToken(token1,FLOAT_SYMBOL);

  else if(token1->type == TOKEN_NULL_TYPE)
    return modifyToken(token1,NULL_SYMBOL);

}

Token *modifyToken(Token *token, int symbol) {

  switch (symbol) {
    case NULL_SYMBOL :
      token->symbol = NULL_SYMBOL;
      break;

    case INTEGER_SYMBOL :
      token->symbol = INTEGER_SYMBOL;
      break;

    case FLOAT_SYMBOL :
      token->symbol = FLOAT_SYMBOL;
      break;

    case ADD_SYMBOL :
      token->symbol = ADD_SYMBOL;
      break;

    case SUB_SYMBOL :
      token->symbol = SUB_SYMBOL;
      break;

    case NEGATIVE_SYMBOL :
      token->symbol = NEGATIVE_SYMBOL;
      break;

    case MUL_SYMBOL :
      token->symbol = MUL_SYMBOL;
      break;

    case DIV_SYMBOL :
      token->symbol = DIV_SYMBOL;
      break;

    case MODULO_SYMBOL :
      token->symbol = MODULO_SYMBOL;
      break;

    case LOGICAL_NOT_SYMBOL :
      token->symbol = LOGICAL_NOT_SYMBOL;
      break;

    case BITWISE_NOT_SYMBOL :
      token->symbol = BITWISE_NOT_SYMBOL;
      break;

    case LOGICAL_AND_SYMBOL :
      token->symbol = LOGICAL_AND_SYMBOL;
      free(token->str);
      token->str = strdup("&&");
      break;

    case BITWISE_AND_SYMBOL :
      token->symbol = BITWISE_AND_SYMBOL;
      break;

    case LOGICAL_OR_SYMBOL  :
      token->symbol = LOGICAL_OR_SYMBOL;
      free(token->str);
      token->str = strdup("||");
      break;

    case BITWISE_OR_SYMBOL :
      token->symbol = BITWISE_OR_SYMBOL;
      break;

    case GREATER_SYMBOL :
      token->symbol = GREATER_SYMBOL;
      break;

    case LESSER_SYMBOL :
      token->symbol = LESSER_SYMBOL;
      break;

    case BITWISE_XOR_SYMBOL :
      token->symbol = BITWISE_XOR_SYMBOL;
      break;

    case OPENING_BRACKET_SYMBOL :
      token->symbol = OPENING_BRACKET_SYMBOL;
      break;

    case CLOSING_BRACKET_SYMBOL :
      token->symbol = CLOSING_BRACKET_SYMBOL;
      break;

    case EQUAL_SYMBOL :
      token->symbol = EQUAL_SYMBOL;
      break;

    case BITWISE_LEFT_SHIFTER_SYMBOL  :
      token->symbol = BITWISE_LEFT_SHIFTER_SYMBOL;
      free(token->str);
      token->str = strdup("<<");
      break;

    case BITWISE_RIGHT_SHIFTER_SYMBOL  :
      token->symbol = BITWISE_RIGHT_SHIFTER_SYMBOL;
      free(token->str);
      token->str = strdup(">>");
      break;

    case GREATER_EQUALS_SYMBOL  :
      token->symbol = GREATER_EQUALS_SYMBOL;
      free(token->str);
      token->str = strdup(">=");
      break;

    case LESSER_EQUALS_SYMBOL  :
      token->symbol = LESSER_EQUALS_SYMBOL;
      free(token->str);
      token->str = strdup("<=");
      break;

    case EQUALS_TO_SYMBOL  :
      token->symbol = EQUALS_TO_SYMBOL;
      free(token->str);
      token->str = strdup("==");
      break;

    case NOT_EQUALS_TO_SYMBOL  :
      token->symbol = NOT_EQUALS_TO_SYMBOL;
      free(token->str);
      token->str = strdup("!=");
      break;
  }
  return token;
}

Token *newFloatToken(double value, Token *token, Token *leftToken, Token *rightToken) {

  if(leftToken == NULL || rightToken == NULL) {
    token = createFloatToken(value, NULL);
    token = modifyToken(token, FLOAT_SYMBOL);
    return token;
  } else {
    token = createFloatToken(value, NULL);
    token = modifyToken(token, FLOAT_SYMBOL);
    token->originalStr = leftToken->originalStr;
    token->startColumn = leftToken->startColumn;
    token->length = (rightToken->startColumn + rightToken->length) - leftToken->startColumn;
    token->str = malloc(token->length);
    strncpy(token->str,leftToken->originalStr+token->startColumn,token->length + 1);
    token->str[token->length] = '\0';
    return token;
  }
}

int getTokenIntegerValue(Token *token) {
  int value, tokenvalue;

  if(getTokenType(token)) {
    if(token->type == TOKEN_FLOAT_TYPE) {
      tokenvalue = ((FloatToken *)token)->value;
      value = (int)tokenvalue;
    }
    else if (token->type == TOKEN_INTEGER_TYPE)
      return ((IntegerToken *)token)->value;
  }

  else
    throwException(ERR_NOT_AN_INTEGER, token, "Expecting an integer, but %f is met.",((FloatToken *)token)->value);//Throw exception
}

int verifyTokensBackToBack(Token *token1, Token *token2) {

    token1->startColumn = token1->startColumn + token1->length;

    if((token1)->startColumn == (token2)->startColumn) {
      token1->startColumn = token1->startColumn - token1->length;
      return 1;
    }

    else {
      token1->startColumn = token1->startColumn - token1->length;
      return 0;
    }
}

int getTokenType(Token *token) {
  double d;
  int i;

  if(token->type == TOKEN_INTEGER_TYPE)
    d = ((IntegerToken *)token)->value;

  else if(token->type == TOKEN_FLOAT_TYPE)
    d = ((FloatToken *)token)->value;

  i = (int)d;

  if(d == i)
      return 1;

  else
      return 0;
}

double getTokenValue(Token *token) {
  double value;

  switch (token->type) {
    case TOKEN_INTEGER_TYPE :
      value = ((IntegerToken *)token)->value;
      break;
    case TOKEN_FLOAT_TYPE :
      value = ((FloatToken *)token)->value;
      break;
    default :
      throwException(ERR_INVALID_OPERAND, token, "Invalid");//Throw
  }
  return value;
}

int checkTokenIfItsNULL(Token *token) {
  if(token->type == TOKEN_NULL_TYPE)
    return 1;

  else
    return 0;
}

int checkNextTokenIfItsInteger(Tokenizer *expression) {
  Token *nextTok;
  nextTok = getAdvanceToken(expression);
  if(nextTok->type == TOKEN_FLOAT_TYPE || nextTok->type == TOKEN_INTEGER_TYPE) {
    pushBackToken(expression, nextTok);
    return 1;
  }
  else {
    pushBackToken(expression, nextTok);
    return 0;
  }
}

Token *getNud(Token *thisToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower) {
  TokenInfo *thisTokenInfo;
  Token *nudToken;

  thisTokenInfo = getTokenInfo(thisToken);
  if(thisTokenInfo->nud == NULL) {
    throwException(SYSTEM_ERROR, thisToken, "nud %s is NULL.", thisToken->str);
  }
  else {
    nudToken = thisTokenInfo->nud(thisToken, nextToken, expression, leftBindingPower);
    return nudToken;
  }
}

Token *getLed(Token *thisToken, Token *leftToken, Tokenizer *expression) {
  TokenInfo *thisTokenInfo;
  Token *ledToken;

  thisTokenInfo = getTokenInfo(thisToken);
  if(thisTokenInfo->led == NULL) {
    throwException(SYSTEM_ERROR, thisToken, "led %s is NULL.", thisToken->str);
  }
  else {
    ledToken = thisTokenInfo->led(leftToken, thisToken, expression);
    return ledToken;
  }
}
