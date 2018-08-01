#include "unity.h"
#include "TDOP.h"
#include "Tokenizer.h"
#include "Token.h"
#include "TokenData.h"
#include "IndirectTDOP.h"
#include "Operator.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_getTokenInfo_given_binary_plus_sign_token_expect_binding_power_equals_addition_bp(void) {
  Tokenizer *tokenizer;
  TokenInfo *tokenInfo;
  Token *token;

  tokenizer = createTokenizer("+");
  token = getToken(tokenizer);
  tokenInfo = getTokenInfo(token);

  TEST_ASSERT_EQUAL (ADDITION_BP, tokenInfo->bindingPower);
}

void test_nudInt_given_1_should_return_1(void) {
  Tokenizer *expression;
  Token *token;
  IntegerToken *intToken;

  expression = createTokenizer("1");
  token = getToken(expression);
  intToken = (IntegerToken *)nudInt(token, expression);

  TEST_ASSERT_EQUAL (1,intToken->value);
}

void test_nudInt_given_8_point_64_should_return_8_point_64_token(void) {
  Tokenizer *expression;
  Token *token;
  FloatToken *floatToken;

  expression = createTokenizer("8.64");
  token = getToken(expression);
  floatToken = (FloatToken *)nudFloat(token, expression);

  TEST_ASSERT_EQUAL (8.64,floatToken->value);
}

void test_TDOP_given_2_plus_9_should_return_11(void) {
  Tokenizer *expression;
  Token *token;
  IntegerToken *intToken;

  expression = createTokenizer(" 2 + 9 ");

  token = TDOP(expression);
  intToken = (IntegerToken *)token;

  TEST_ASSERT_EQUAL (11,intToken->value);
}

void test_TDOP_given_1_plus_2_multiply_3_should_return_7(void) {
  Token *token;
  Tokenizer *expression;
  IntegerToken *intToken;

  expression = createTokenizer(" 1 + 2 * 3 - -4 / 5 ");
  token = TDOP(expression);
  intToken = (IntegerToken *)token;

  TEST_ASSERT_EQUAL (1 + 2 * 3 - -4 / 5, intToken->value);
}
