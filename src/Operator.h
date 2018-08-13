#ifndef _Operator_H
#define _Operator_H
#include "Operator.h"
#include "Tokenizer.h"
#include "TokenData.h"
#include "TDOP.h"
#include "Token.h"

Token *nudInt (Token *intToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledInt (Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudFloat (Token *floatToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledFloat (Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudPlus(Token *plusToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledPlus (Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudNegative(Token *negToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledNegative (Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudMinus(Token *minusToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledMinus (Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudAsterisk (Token *astToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledAsterisk (Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudSlash (Token *slashToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledSlash(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudPercent (Token *percToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledPercent(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudExclamation(Token *exclToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledExclamation(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudTilde(Token *tildeToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledTilde(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudDoubleAmpersand(Token *doublAampToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledDoubleAmpersand(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudAmpersand(Token *ampToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledAmpersand(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudDoubleVerticalBar(Token *doubleVertToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledDoubleVerticalBar(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudVerticalBar(Token *vertToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledVerticalBar(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudCaret(Token *caretToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledCaret(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudDoubleLeftArrows(Token *doubleLeftArrToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledDoubleLeftArrows(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudDoubleRightArrows(Token *doubleRightArrToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledDoubleRightArrows(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudLeftArrow(Token *leftArrToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledLeftArrow(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudRightArrow(Token *rightArrToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledRightArrow(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudLeftArrowEqual(Token *leftArrEquToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledLeftArrowEqual(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudRightArrowEqual(Token *rightArrEquToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledRightArrowEqual(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudEqual(Token *equToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledEqual(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudDoubleEquals(Token *doubleEquToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledDoubleEquals(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudExclamationEqual(Token *exclEquToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledExclamationEqual(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudLeftBracket(Token *leftBracketToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledLeftBracket(Token *leftToken, Token *leftBracketToken, Tokenizer *expression);

Token *nudRightBracket(Token *rightBracketToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *nudNULL(Token *nullToken, Token *nextToken, Tokenizer *expression, uint32_t *leftBindingPower);

int matchBracket(Tokenizer *expression, uint32_t *leftBindingPower);
//Token *nudRightBracket(Token *thisToken, Tokenizer *expression, uint32_t leftBindingPower);

#endif // _TDOP_H
