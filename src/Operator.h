#ifndef _Operator_H
#define _Operator_H
#include "Operator.h"
#include "Tokenizer.h"
#include "TokenData.h"
#include "TDOP.h"
#include "Token.h"

Token *nudInt (Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledInt (Token *leftToken, Tokenizer *expression);

Token *nudFloat (Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledFloat (Token *leftToken, Tokenizer *expression);

Token *nudPlus(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledPlus (Token *leftToken, Tokenizer *expression);

Token *nudNegative(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledNegative (Token *leftToken, Tokenizer *expression);

Token *nudMinus(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledMinus (Token *leftToken, Tokenizer *expression);

Token *nudAsterisk (Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledAsterisk (Token *leftToken, Tokenizer *expression);

Token *nudSlash (Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledSlash(Token *leftToken, Tokenizer *expression);

Token *nudPercent (Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledPercent(Token *leftToken, Tokenizer *expression);

Token *nudExclamation(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledExclamation(Token *leftToken, Tokenizer *expression);

Token *nudTilde(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledTilde(Token *leftToken, Tokenizer *expression);

Token *nudDoubleAmpersand(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledDoubleAmpersand(Token *leftToken, Tokenizer *expression);

Token *nudAmpersand(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledAmpersand(Token *leftToken, Tokenizer *expression);

Token *nudDoubleVerticalBar(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledDoubleVerticalBar(Token *leftToken, Tokenizer *expression);

Token *nudVerticalBar(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledVerticalBar(Token *leftToken, Tokenizer *expression);

Token *nudCaret(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledCaret(Token *leftToken, Tokenizer *expression);

Token *nudDoubleLeftArrows(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledDoubleLeftArrows(Token *leftToken, Tokenizer *expression);

Token *nudDoubleRightArrows(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledDoubleRightArrows(Token *leftToken, Tokenizer *expression);

Token *nudLeftArrow(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledLeftArrow(Token *leftToken, Tokenizer *expression);

Token *nudRightArrow(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledRightArrow(Token *leftToken, Tokenizer *expression);

Token *nudLeftArrowEqual(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledLeftArrowEqual(Token *leftToken, Tokenizer *expression);

Token *nudRightArrowEqual(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledRightArrowEqual(Token *leftToken, Tokenizer *expression);

Token *nudDoubleEquals(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledDoubleEquals(Token *leftToken, Tokenizer *expression);

Token *nudExclamationEqual(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledExclamationEqual(Token *leftToken, Tokenizer *expression);

Token *nudLeftBracket(Token *thisToken, Tokenizer *expression, uint32_t *eftBindingPower);
int matchBracket(Tokenizer *expression, uint32_t *leftBindingPower);
//Token *nudRightBracket(Token *thisToken, Tokenizer *expression, uint32_t leftBindingPower);

#endif // _TDOP_H
