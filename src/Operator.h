#ifndef _Operator_H
#define _Operator_H
#include "Operator.h"
#include "Tokenizer.h"
#include "TokenData.h"
#include "TDOP.h"
#include "Token.h"

Token *nudInt (Token *intToken, Tokenizer *expression);
Token *ledInt (Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudFloat (Token *floatToken, Tokenizer *expression);
Token *ledFloat (Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudPlus(Token *plusToken, Tokenizer *expression);
Token *ledPlus (Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudNegative(Token *minusToken, Tokenizer *expression);
Token *ledMinus (Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudAsterisk (Token *astToken, Tokenizer *expression);
Token *ledAsterisk (Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudSlash (Token *slashToken, Tokenizer *expression);
Token *ledSlash(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudPercent (Token *percToken, Tokenizer *expression);
Token *ledPercent(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudExclamation(Token *exclToken, Tokenizer *expression);
Token *ledExclamation(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudTilde(Token *tildeToken, Tokenizer *expression);
Token *ledTilde(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudDoubleAmpersand(Token *doublAampToken, Tokenizer *expression);
Token *ledDoubleAmpersand(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudAmpersand(Token *ampToken, Tokenizer *expression);
Token *ledAmpersand(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudDoubleVerticalBar(Token *doubleVertToken, Tokenizer *expression);
Token *ledDoubleVerticalBar(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudVerticalBar(Token *vertToken, Tokenizer *expression);
Token *ledVerticalBar(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudCaret(Token *caretToken, Tokenizer *expression);
Token *ledCaret(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudDoubleLeftArrows(Token *doubleLeftArrToken, Tokenizer *expression);
Token *ledDoubleLeftArrows(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudDoubleRightArrows(Token *doubleRightArrToken, Tokenizer *expression);
Token *ledDoubleRightArrows(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudLeftArrow(Token *leftArrToken, Tokenizer *expression);
Token *ledLeftArrow(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudRightArrow(Token *rightArrToken, Tokenizer *expression);
Token *ledRightArrow(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudLeftArrowEqual(Token *leftArrEquToken, Tokenizer *expression);
Token *ledLeftArrowEqual(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudRightArrowEqual(Token *rightArrEquToken, Tokenizer *expression);
Token *ledRightArrowEqual(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudEqual(Token *equToken, Tokenizer *expression);
Token *ledEqual(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudDoubleEquals(Token *doubleEquToken, Tokenizer *expression);
Token *ledDoubleEquals(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudExclamationEqual(Token *exclEquToken, Tokenizer *expression);
Token *ledExclamationEqual(Token *leftToken, Token *thisToken, Tokenizer *expression);

Token *nudLeftBracket(Token *leftBracketToken, Tokenizer *expression);
Token *ledLeftBracket(Token *leftToken, Token *leftBracketToken, Tokenizer *expression);

Token *nudRightBracket(Token *rightBracketToken, Tokenizer *expression);
Token *nudNULL(Token *nullToken, Tokenizer *expression);

int matchBracket(Tokenizer *expression);
//Token *nudRightBracket(Token *thisToken, Tokenizer *expression, uint32_t leftBindingPower);

#endif // _TDOP_H
