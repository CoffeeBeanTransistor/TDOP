#include "TokenData.h"
#include "TDOP.h"
#include "Token.h"
#include "Operator.h"
#include <stdint.h>
#include <string.h>
#include <malloc.h>

TokenInfo symbolMapTable[500] = {
  [ADD_SYMBOL] = {.bindingPower = ADDITION_BP, .nud = NULL, .led = ledPlus},
  [POSITIVE_SYMBOL] = {.bindingPower = UNARY_PLUS_BP, .nud = nudPlus, .led = NULL},
  [SUB_SYMBOL] = {.bindingPower = SUBTRACTION_BP, .nud = NULL, .led = ledMinus},
  [NEGATIVE_SYMBOL] = {.bindingPower = UNARY_MINUS_BP, .nud = nudMinus, .led = NULL},
  [MUL_SYMBOL] = {.bindingPower = MULTIPLICATION_BP, .nud = nudAsterisk, .led = ledAsterisk},
  [DIV_SYMBOL] = {.bindingPower = DIVISION_BP, .nud = NULL, .led = ledSlash},
  [MODULO_SYMBOL] = {.bindingPower = REMAINDER_BP, .nud = NULL, .led = ledPercent},
  [LOGICAL_NOT_BP] = {.bindingPower = LOGICAL_NOT_BP, .nud = nudExclamation, .led = NULL},
  [OPENING_BRACKET_SYMBOL] = {.bindingPower = WEAKEST, .nud = nudLeftBracket},
  [CLOSING_BRACKET_SYMBOL] = {.bindingPower = WEAKEST},
  [INTEGER_SYMBOL] = {.nud = nudInt},
  [FLOAT_SYMBOL] = {.nud = nudFloat},
  [NULL_SYMBOL] = {.bindingPower = WEAKEST},
};

Token *getTokenSymbol(Token *token1, Tokenizer *expression) {
  Token *token2;

  if(token1->type == TOKEN_OPERATOR_TYPE) {
    token2 = getToken(expression);
      switch (*(token1)->str) {
        case '+'  : switch (token2->type) {
                      case  TOKEN_INTEGER_TYPE  :
                        if(verifyTokensBackToBack(token1,token2)) {
                          modifyToken(token1,POSITIVE_SYMBOL);
                          pushBackToken(expression,token2);
                        }
                        else  {
                          modifyToken(token1,ADD_SYMBOL);
                          pushBackToken(expression,token2);
                        }
                        break;

                      default :
                        modifyToken(token1,ADD_SYMBOL);
                        pushBackToken(expression,token2);
                    }
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
                          modifyToken(token1,BITWISE_RIGHT_SHIFTER);
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
                          modifyToken(token1,BITWISE_LEFT_SHIFTER);
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
      }
      return token1;
  }

  else if(token1->type == TOKEN_INTEGER_TYPE)
    return modifyToken(token1,INTEGER_SYMBOL);

  else if(token1->type == TOKEN_NULL_TYPE)
    return modifyToken(token1,NULL_SYMBOL);

}

TokenInfo *getTokenInfo(Token *token) {

  if(token->type == TOKEN_INTEGER_TYPE)
    return &symbolMapTable[INTEGER_SYMBOL];

  /*else if(token->type == TOKEN_FLOAT_TYPE)
    return &symbolMapTable[FLOAT_SYMBOL];*/

  else if(token->type == TOKEN_OPERATOR_TYPE)
    return &symbolMapTable[token->symbol];

  else if(token->type == TOKEN_NULL_TYPE)
    return &symbolMapTable[NULL_SYMBOL];
}

Token *getNextToken(Tokenizer *expression) {
  Token *token1;

    token1 = getToken(expression);
    token1 = getTokenSymbol(token1,expression);
    return token1;
}

Token *modifyToken(Token *token, int symbol) {

  switch (symbol) {
    case INTEGER_SYMBOL :
      token->symbol = INTEGER_SYMBOL;
      break;

    case NULL_SYMBOL :
      token->symbol = NULL_SYMBOL;
      break;

    case ADD_SYMBOL :
      token->symbol = ADD_SYMBOL;
      break;

    case POSITIVE_SYMBOL :
      token->symbol = POSITIVE_SYMBOL;
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

    case BITWISE_LEFT_SHIFTER  :
      token->symbol = BITWISE_LEFT_SHIFTER;
      free(token->str);
      token->str = strdup("<<");
      break;

    case BITWISE_RIGHT_SHIFTER  :
      token->symbol = BITWISE_RIGHT_SHIFTER;
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
