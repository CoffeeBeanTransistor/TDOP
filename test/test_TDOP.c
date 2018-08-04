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
  token = getNextToken(tokenizer);
  tokenInfo = getTokenInfo(token);

  TEST_ASSERT_EQUAL (ADDITION_BP, tokenInfo->bindingPower);
}

void test_nudInt_given_1_should_return_1(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer("1");
  token = getNextToken(expression);
  token = nudInt(token, expression,0);

  TEST_ASSERT_EQUAL (1,((IntegerToken *)token)->value);
  TEST_ASSERT_EQUAL (INTEGER_SYMBOL, token->symbol);
}

void test_getNextToken_given_expression_1_should_return_token_with_symbol_1(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer(" 1 ");
  token = getNextToken(expression);

  TEST_ASSERT_EQUAL (1,((IntegerToken *)token)->value);
  TEST_ASSERT_EQUAL (INTEGER_SYMBOL, token->symbol);
}

void test_getNextToken_given_expression_23_plus_98_should_return_3_tokens_23_plus_98(void) {
  Tokenizer *expression;
  Token *v1Token, *v2Token, *opToken;

  expression = createTokenizer(" 23 + 98 ");
  v1Token = getNextToken(expression);
  opToken = getNextToken(expression);
  v2Token = getNextToken(expression);

  TEST_ASSERT_EQUAL (23,((IntegerToken *)v1Token)->value);
  TEST_ASSERT_EQUAL (INTEGER_SYMBOL, v1Token->symbol);
  TEST_ASSERT_EQUAL (ADD_SYMBOL,opToken->symbol);
  TEST_ASSERT_EQUAL_STRING  ("+", opToken->str);
  TEST_ASSERT_EQUAL (98,((IntegerToken *)v2Token)->value);
  TEST_ASSERT_EQUAL (INTEGER_SYMBOL, v2Token->symbol);

}

void test_verifyTokenBackToBack_given_double_closed_AND_should_return_true(void) {
  Tokenizer *expression;
  Token *token1, *token2;

  expression = createTokenizer(" && ");
  token1 =getToken(expression);
  token2 = getToken(expression);

  TEST_ASSERT_TRUE (verifyTokensBackToBack(token1,token2));
}

void test_verifyTokenBackToBack_given_double_separated_EQUALS_should_return_false(void) {
  Tokenizer *expression;
  Token *token1, *token2;

  expression = createTokenizer(" =    = ");
  token1 =getToken(expression);
  token2 = getToken(expression);

  TEST_ASSERT_FALSE (verifyTokensBackToBack(token1,token2));
}

void test_modifyToken_given_logical_AND_symbol_should_return_double_AND_str_in_token(void) {
  Tokenizer *expression;
  Token *token, *token1;

  expression = createTokenizer(" & ");
  token1 =getToken(expression);
  token = modifyToken(token1, LOGICAL_AND_SYMBOL);

  TEST_ASSERT_EQUAL_STRING ("&&", token->str);
  TEST_ASSERT_EQUAL(LOGICAL_AND_SYMBOL, token->symbol);
}

void test_getNextToken_given_NOT_EQUAL_expression_should_return_token_str_NOT_EQUAL(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer(" != ");
  token = getNextToken(expression);

  TEST_ASSERT_EQUAL_STRING ("!=", token->str);
  TEST_ASSERT_EQUAL(NOT_EQUALS_TO_SYMBOL, token->symbol);
}

void test_getNextToken_given_separated_AND_expression_should_return_token_str_BITWISE_OR(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer(" &   & ");
  token = getNextToken(expression);

  TEST_ASSERT_EQUAL_STRING ("&", token->str);
  TEST_ASSERT_EQUAL(BITWISE_AND_SYMBOL, token->symbol);
}

void test_getNextToken_given_negative_2_expression_should_return_token_with_negative_symbol(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer(" -2 ");
  token = getNextToken(expression);

  TEST_ASSERT_EQUAL (NEGATIVE_SYMBOL, token->symbol);
}

void test_getNextToken_given_subtract_54_expression_should_return_token_with_sub_symbol(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer(" - 54 ");
  token = getNextToken(expression);

  TEST_ASSERT_EQUAL (SUB_SYMBOL, token->symbol);
}

/*void test_nudInt_given_8_point_64_should_return_8_point_64_token(void) {
  Tokenizer *expression;
  Token *token;
  FloatToken *floatToken;

  expression = createTokenizer("8.64");
  token = getToken(expression);
  floatToken = (FloatToken *)nudFloat(token, expression);

  TEST_ASSERT_EQUAL (8.64,floatToken->value);
}*/

void test_TDOP_given_2_plus_9_should_return_11(void) {
  Tokenizer *expression;
  Token *token;
  IntegerToken *intToken;

  expression = createTokenizer(" 2 + 9 ");

  token = TDOP(expression);
  intToken = (IntegerToken *)token;
  TEST_ASSERT_EQUAL (11,intToken->value);
}

void test_TDOP_given_1_plus_2_multiply_3_minus_neg_4_remainder_5_should_return_6(void) {
  Token *token;
  Tokenizer *expression;
  IntegerToken *intToken;

  expression = createTokenizer(" 1 + 2 * 3 - -4 % 5 ");
  token = TDOP(expression);
  intToken = (IntegerToken *)token;

  TEST_ASSERT_EQUAL (1 + 2 * 3 - -4 % 5, intToken->value);
}

/*void test_TDOP_given_logical_not_23_expect_0 (void) {
  Token *token;
  Tokenizer *expression;
  IntegerToken *intToken;

  expression = createTokenizer(" !23 ");
  token = TDOP(expression);
  intToken = (IntegerToken *)token;

  TEST_ASSERT_EQUAL (!23, intToken->value);
}

void test_TDOP_given_logical_not_0_expect_1 (void) {
  Token *token;
  Tokenizer *expression;
  IntegerToken *intToken;

  expression = createTokenizer(" !0 ");
  token = TDOP(expression);
  intToken = (IntegerToken *)token;

  TEST_ASSERT_EQUAL (!0, intToken->value);
}*/

/*void test_TDOP_given_5_times_bracket_23_minus_8_bracket_plus_9_should_return_(void) {
  Token *token;
  Tokenizer *expression;
  IntegerToken *intToken;

  expression = createTokenizer(" 5 * ( 23 - 8 ) + 9 ");
  token = TDOP(expression);
  intToken = (IntegerToken *)token;

  TEST_ASSERT_EQUAL (5 * ( 23 - 8 ) + 9 , intToken->value);
}*/

/*void test_matchBracket_given_2_left_3_right_brackets_expect_return_0(void) {
  Token *token1, *token2, *token3, *token4, *ans;
  Tokenizer *expression;

  expression = createTokenizer(" (() ");
  ans = TDOP(expression);

  TEST_ASSERT_EQUAL (')',ans->str[0]);
}*/
