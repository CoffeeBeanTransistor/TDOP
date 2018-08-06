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
  token = nudInt(token, expression, 0);

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

void test_TDOP_given_2_plus_9_should_return_11(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer(" 2 + 9 ");

  token = TDOP(expression);
  TEST_ASSERT_EQUAL (11,((IntegerToken *)token)->value);
}

void test_TDOP_given_1_plus_2_multiply_3_minus_neg_4_remainder_5_should_return_6(void) {
  Token *token;
  Tokenizer *expression;

  expression = createTokenizer(" 1 + 2 * 3 - -4 % 5 ");
  token = TDOP(expression);

  TEST_ASSERT_EQUAL (1 + 2 * 3 - -4 % 5, ((IntegerToken *)token)->value);
}

void test_TDOP_given_logical_not_23_expect_false (void) {
  Token *token;
  Tokenizer *expression;

  expression = createTokenizer(" !23 ");
  token = TDOP(expression);

  TEST_ASSERT_FALSE (((IntegerToken *)token)->value);
}

void test_TDOP_given_logical_not_negative_23_expect_true (void) {
  Token *token;
  Tokenizer *expression;

  expression = createTokenizer(" !-23 ");
  token = TDOP(expression);

  TEST_ASSERT_TRUE (((IntegerToken *)token)->value);
}

void test_TDOP_given_logical_not_0_expect_true (void) {
  Token *token;
  Tokenizer *expression;

  expression = createTokenizer(" !0 ");
  token = TDOP(expression);

  TEST_ASSERT_TRUE (((IntegerToken *)token)->value);
}

void test_TDOP_given_5_times_bracket_23_minus_8_bracket_plus_9_should_return_84(void) {
  Token *token;
  Tokenizer *expression;

  expression = createTokenizer(" 5 * ( 23 - 8 ) + 9 ");
  token = TDOP(expression);

  TEST_ASSERT_EQUAL (5 * ( 23 - 8 ) + 9,((IntegerToken *)token)->value);
}

void test_TDOP_given_complicated_expression_with_brackets_should_solve_correctly(void) {
  Token *token;
  Tokenizer *expression;

  expression = createTokenizer(" -(7+--9)*(-1+-2*---6) ");
  token = TDOP(expression);

  TEST_ASSERT_EQUAL (-176,((IntegerToken *)token)->value);
}

void test_TDOP_given_3_and_4_minuses_2_expression_should_return_value_5(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer(" 3----2 ");
  token = TDOP(expression);

  TEST_ASSERT_EQUAL (5, ((IntegerToken *)token)->value);
}

void test_TDOP_testing_nudTilde_given_tilde_35_should_return_negative_36(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( "~35" );
  token = TDOP(expression);

  TEST_ASSERT_EQUAL (-36, ((IntegerToken *)token)->value);
}

void test_TDOP_given_tilde_containing_expression_should_solve_correctly(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( " ~(35 + 74) * 92 " );
  token = TDOP(expression);

  TEST_ASSERT_EQUAL (~(35 + 74) * 92, ((IntegerToken *)token)->value);
}

void test_TDOP_testing_logical_AND_given_2_true_statements_with_double_ampersand_in_between_should_return_true(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( "(23 - 54) && (1-2) " );
  token = TDOP(expression);

  TEST_ASSERT_TRUE (((IntegerToken *)token)->value);
}

void test_TDOP_testing_logical_AND_given_1_true_statement_and_1_zero_valued_statement_with_double_ampersand_should_return_false(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( "2*5 && 23 - 23 " );
  token = TDOP(expression);

  TEST_ASSERT_FALSE (((IntegerToken *)token)->value);
}

void test_TDOP_testing_bitwise_AND_given_7_ampersand_in_between_12_should_return_4(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( "7&4" );
  token = TDOP(expression);

  TEST_ASSERT_EQUAL (7&4, ((IntegerToken *)token)->value);
}

void test_TDOP_testing_bitwise_AND_given_2_statements_with_aan_ampersand_in_between_shuould_solve_correctly(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( "(29- 48) & (7*8)" );
  token = TDOP(expression);

  TEST_ASSERT_EQUAL ((29- 48) & (7*8), ((IntegerToken *)token)->value);
}

void test_TDOP_testing_logical_OR_given_1_true_statement_and_1_false_statement_with_double_vertical_lines_in_between_should_return_true(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( "(23 *(23-12)) || (0 / 62) " );
  token = TDOP(expression);

  TEST_ASSERT_TRUE (((IntegerToken *)token)->value);
}

void test_TDOP_testing_bitwise_OR_given_2_statements_with_1_vertical_line_in_between_should_solve_correctly(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( " (2&19) | (4* 9)" );
  token = TDOP(expression);

  TEST_ASSERT_EQUAL ((2&19) | (4* 9), ((IntegerToken *)token)->value);
}

void test_TDOP_testing_bitwise_XOR_given_31_and_19_with_1_caret_in_between_should_return_value_12(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( "31^19" );
  token = TDOP(expression);

  TEST_ASSERT_EQUAL (12, ((IntegerToken *)token)->value);
}

void test_TDOP_testing_left_shift_given_98_shifting_to_left_2_times_should_return_392(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( " 98 << 2 " );
  token = TDOP(expression);

  TEST_ASSERT_EQUAL (392, ((IntegerToken *)token)->value);
}

void test_TDOP_testing_left_shift_given_complicated_expression_with_left_shift_involved_should_solve_correctly(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( " (21 ^12) | (41 << 8) " );
  token = TDOP(expression);

  TEST_ASSERT_EQUAL ((21 ^12) | (41 << 8), ((IntegerToken *)token)->value);
}

void test_TDOP_testing_right_shift_given_63_shifting_to_right_8_times_should_return_0(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( " 63 >> 8 " );
  token = TDOP(expression);

  TEST_ASSERT_EQUAL (0, ((IntegerToken *)token)->value);
}

void test_TDOP_testing_left_shift_given_complicated_expression_with_right_shift_involved_should_solve_correctly(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( " (59>>2)*92^32 " );
  token = TDOP(expression);

  TEST_ASSERT_EQUAL ((59>>2)*92^32, ((IntegerToken *)token)->value);
}

void test_TDOP_testing_lesser_than_given_57_lesser_than_23_should_return_false(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( " 57 < 23 " );
  token = TDOP(expression);

  TEST_ASSERT_FALSE (((IntegerToken *)token)->value);
}

void test_TDOP_testing_lesser_than_given_expression_involving_lesser_than_should_solve_correctly(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( " (74 <(63-2)) + 23%6 " );
  token = TDOP(expression);

  TEST_ASSERT_EQUAL ((74 <(63-2)) + 23%6, ((IntegerToken *)token)->value);
}

void test_TDOP_testing_greater_than_given_238_greater_than_78_should_return_true(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( "238>78" );
  token = TDOP(expression);

  TEST_ASSERT_FALSE (((IntegerToken *)token)->value);
}

void test_TDOP_testing_greater_than_given_expression_involving_greater_than_should_solve_correctly(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( " 23>9+-9|6^23-(12*54) " );
  token = TDOP(expression);

  TEST_ASSERT_EQUAL (23>9+-9|6^23-(12*54), ((IntegerToken *)token)->value);
}


/*void test_nudInt_given_8_point_64_should_return_8_point_64_token(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer("8.64");
  token = getNextToken(expression);
  token = nudFloat(token, expression, 0);

  TEST_ASSERT_EQUAL (8.64,((FloatToken *)token)->value);
  TEST_ASSERT_EQUAL (FLOAT_SYMBOL, token->symbol);
}

void test_TDOP_given_2_point_32_minus_9_point_94_should_return_11(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer(" 2.32 - 9.94 ");
  token = TDOP(expression);

  TEST_ASSERT_EQUAL (2.32 - 9.94,((FloatToken *)token)->value);
}

void test_convertToBinary_given_42_expect_return_101010(void) {
  int num = 42, binaryNum;

  binaryNum = convertToBinary(num);

  TEST_ASSERT_EQUAL(101010,binaryNum);
}

void test_convertToBinary_given_negative_octal_025_expect_return_negative_10101(void) {
  int num = -025, binaryNum;

  binaryNum = convertToBinary(num);

  TEST_ASSERT_EQUAL(-10101,binaryNum);
}*/
