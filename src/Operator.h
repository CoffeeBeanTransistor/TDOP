#ifndef _Operator_H
#define _Operator_H
#include "Operator.h"
#include "Tokenizer.h"
#include "TokenData.h"
#include "TDOP.h"
#include "Token.h"

Token *nudInt (Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *nudFloat (Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *nudPlus(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledPlus (Token *leftToken, Tokenizer *expression);
Token *nudNegative(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledNegative (Token *leftToken, Tokenizer *expression);
Token *nudMinus(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *ledMinus (Token *leftToken, Tokenizer *expression);
Token *ledAsterisk (Token *leftToken, Tokenizer *expression);
Token *ledSlash(Token *leftToken, Tokenizer *expression);
Token *ledPercent(Token *leftToken, Tokenizer *expression);
Token *nudExclamation(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);
Token *nudTilde(Token *thisToken, Tokenizer *expression, uint32_t *leftBindingPower);

Token *ledDoubleAmpersand(Token *leftToken, Tokenizer *expression);
Token *ledAmpersand(Token *leftToken, Tokenizer *expression);
Token *ledDoubleVerticalBar(Token *leftToken, Tokenizer *expression);
Token *ledVerticalBar(Token *leftToken, Tokenizer *expression);
Token *ledCaret(Token *leftToken, Tokenizer *expression);
Token *ledDoubleLeftArrows(Token *leftToken, Tokenizer *expression);
Token *ledDoubleRightArrows(Token *leftToken, Tokenizer *expression);
Token *ledLeftArrow(Token *leftToken, Tokenizer *expression);
Token *ledLeftArrowEqual(Token *leftToken, Tokenizer *expression);
Token *ledRightArrow(Token *leftToken, Tokenizer *expression);
Token *ledRightArrowEqual(Token *leftToken, Tokenizer *expression);
Token *ledDoubleEquals(Token *leftToken, Tokenizer *expression);
Token *ledExclamationEqual(Token *leftToken, Tokenizer *expression);

Token *nudLeftBracket(Token *thisToken, Tokenizer *expression, uint32_t *eftBindingPower);
//Token *nudRightBracket(Token *thisToken, Tokenizer *expression, uint32_t leftBindingPower);
int matchBracket(Tokenizer *expression, char closing, uint32_t *leftBindingPower);
int convertToBinary(int number, int bitLength);

#endif // _TDOP_H
