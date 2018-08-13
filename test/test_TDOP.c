#include "unity.h"
#include "TDOP.h"
#include "Tokenizer.h"
#include "Token.h"
#include "TokenData.h"
//#include "IndirectTDOP.h"
#include "Operator.h"
#include "Exception.h"
#include "CException.h"
#include "Error.h"

CEXCEPTION_T e;

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
  token = getAdvanceToken(tokenizer);
  tokenInfo = getTokenInfo(token);

  TEST_ASSERT_EQUAL (ADDITION_BP, tokenInfo->bindingPower);
}

void test_nudInt_given_1_should_return_1(void) {
  Tokenizer *expression;
  Token *token, *token1, *token2;

  expression = createTokenizer("1");
  token1 = getAdvanceToken(expression);
  token2 = getAdvanceToken(expression);
  token = nudInt(token1, token2, expression, 0);

  TEST_ASSERT_EQUAL (1,((IntegerToken *)token1)->value);
  TEST_ASSERT_EQUAL (INTEGER_SYMBOL, token1->symbol);
}

void test_getAdvanceToken_given_expression_1_should_return_token_with_symbol_1(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer(" 1 ");
  token = getAdvanceToken(expression);

  TEST_ASSERT_EQUAL (TOKEN_INTEGER_TYPE, token->type);
  TEST_ASSERT_EQUAL (1,((IntegerToken *)token)->value);
  TEST_ASSERT_EQUAL (INTEGER_SYMBOL, token->symbol);
}

void test_getAdvanceToken_given_expression_23_plus_98_should_return_3_tokens_23_plus_98(void) {
  Tokenizer *expression;
  Token *v1Token, *v2Token, *opToken;

  expression = createTokenizer(" 23 + 98 ");
  v1Token = getAdvanceToken(expression);
  opToken = getAdvanceToken(expression);
  v2Token = getAdvanceToken(expression);

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

void test_getAdvanceToken_given_NOT_EQUAL_expression_should_return_token_str_NOT_EQUAL(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer(" != ");
  token = getAdvanceToken(expression);

  TEST_ASSERT_EQUAL_STRING ("!=", token->str);
  TEST_ASSERT_EQUAL(NOT_EQUALS_TO_SYMBOL, token->symbol);
}

void test_getAdvanceToken_given_separated_AND_expression_should_return_token_str_BITWISE_OR(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer(" &   & ");
  token = getAdvanceToken(expression);

  TEST_ASSERT_EQUAL_STRING ("&", token->str);
  TEST_ASSERT_EQUAL(BITWISE_AND_SYMBOL, token->symbol);
}

void test_getAdvanceToken_given_negative_2_expression_should_return_token_with_negative_symbol(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer(" -2 ");
  token = getAdvanceToken(expression);

  TEST_ASSERT_EQUAL (NEGATIVE_SYMBOL, token->symbol);
}

void test_getAdvanceToken_given_subtract_54_expression_should_return_token_with_sub_symbol(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer(" - 54 ");
  token = getAdvanceToken(expression);

  TEST_ASSERT_EQUAL (SUB_SYMBOL, token->symbol);
}

void test_TDOP_given_2_plus_9_should_return_11(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer(" 2 + 9 ");

  token = TDOP(expression);
  TEST_ASSERT_EQUAL_FLOAT (11,((FloatToken *)token)->value);
}

void test_TDOP_given_1_plus_2_multiply_3_minus_neg_4_remainder_5_should_return_6(void) {
  Token *token;
  Tokenizer *expression;

  expression = createTokenizer(" 1 + 2 * 3 - -4 % 5 ");
  token = TDOP(expression);

  TEST_ASSERT_EQUAL_FLOAT (1 + 2 * 3 - -4 % 5, ((FloatToken *)token)->value);
}

void test_TDOP_given_logical_not_23_expect_false (void) {
  Token *token;
  Tokenizer *expression;

  expression = createTokenizer(" !23 ");
  token = TDOP(expression);

  TEST_ASSERT_FALSE (((FloatToken *)token)->value);
}

void test_TDOP_given_logical_not_negative_23_expect_false (void) {
  Token *token;
  Tokenizer *expression;

  expression = createTokenizer(" !-23 ");
  token = TDOP(expression);

  TEST_ASSERT_FALSE (((FloatToken *)token)->value);
}

void test_TDOP_given_logical_not_0_expect_true (void) {
  Token *token;
  Tokenizer *expression;

  expression = createTokenizer(" !0 ");
  token = TDOP(expression);

  TEST_ASSERT_TRUE (((FloatToken *)token)->value);
}

void test_getTokenIntegerValue_given_a_token_with_float_value_with_no_fractional_part_expect_an_integer_number_will_return(void) {
  Token *token;
  int value;

  token = newFloatToken(8.0000,token,NULL,NULL);
  value = getTokenIntegerValue(token);

  TEST_ASSERT_EQUAL (8,value);
}

void test_getTokenIntegerValue_given_a_token_with_float_value_fractional_part_expect_return_false(void) {
  Token *token;
  token = newFloatToken(8.832, token, NULL,NULL);

  TEST_ASSERT_EQUAL_FLOAT (8.832,((FloatToken *)token)->value);
  TEST_ASSERT_EQUAL (TOKEN_FLOAT_TYPE, token->type);
}

void test_TDOP_given_5_times_bracket_23_minus_8_bracket_plus_9_should_return_84(void) {
  Token *token;
  Tokenizer *expression;

  expression = createTokenizer(" 5 * ( 23 - 8 ) + 9 ");
  token = TDOP(expression);

  TEST_ASSERT_EQUAL (5 * ( 23 - 8 ) + 9,((FloatToken *)token)->value);
}

void test_TDOP_given_complicated_expression_with_brackets_should_solve_correctly(void) {
  Token *token;
  Tokenizer *expression;

  expression = createTokenizer(" -(7+--9)*(-1+-2*---6) ");
  token = TDOP(expression);

  TEST_ASSERT_EQUAL_FLOAT (-176,((FloatToken *)token)->value);
}

void test_TDOP_given_3_and_4_minuses_2_expression_should_return_value_5(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer(" 3----2 ");
  token = TDOP(expression);

  TEST_ASSERT_EQUAL (5, ((FloatToken *)token)->value);
}

void test_TDOP_testing_nudTilde_given_tilde_35_should_return_negative_36(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( "~35" );
  token = TDOP(expression);

  TEST_ASSERT_EQUAL (-36, ((FloatToken *)token)->value);
}

void test_TDOP_given_tilde_containing_expression_should_solve_correctly(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( " ~(35 + 74) * 92 " );
  token = TDOP(expression);

  TEST_ASSERT_EQUAL (~(35 + 74) * 92, ((FloatToken *)token)->value);
}

void test_TDOP_testing_logical_AND_given_2_true_statements_with_double_ampersand_in_between_should_return_true(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( "(23 - 54) && (1-2) " );
  token = TDOP(expression);

  TEST_ASSERT_TRUE (((FloatToken *)token)->value);
}

void test_TDOP_testing_logical_AND_given_1_true_statement_and_1_zero_valued_statement_with_double_ampersand_should_return_false(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( "2*5 && 23 - 23 " );
  token = TDOP(expression);

  TEST_ASSERT_FALSE (((FloatToken *)token)->value);
}

void test_TDOP_testing_bitwise_AND_given_7_ampersand_in_between_12_should_return_4(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( "7&4" );
  token = TDOP(expression);

  TEST_ASSERT_EQUAL (7&4, ((FloatToken *)token)->value);
}

void test_TDOP_testing_bitwise_AND_given_2_statements_with_aan_ampersand_in_between_shuould_solve_correctly(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( "(29- 48) & (7*8)" );
  token = TDOP(expression);

  TEST_ASSERT_EQUAL ((29- 48) & (7*8), ((FloatToken *)token)->value);
}

void test_TDOP_testing_logical_OR_given_1_true_statement_and_1_false_statement_with_double_vertical_lines_in_between_should_return_true(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( "(23 *(23-12)) || (0 / 62) " );
  token = TDOP(expression);

  TEST_ASSERT_TRUE (((FloatToken *)token)->value);
}

void test_TDOP_testing_bitwise_OR_given_2_statements_with_1_vertical_line_in_between_should_solve_correctly(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( " (2&19) | (4* 9)" );
  token = TDOP(expression);

  TEST_ASSERT_EQUAL ((2&19) | (4* 9), ((FloatToken *)token)->value);
}

void test_TDOP_testing_bitwise_XOR_given_31_and_19_with_1_caret_in_between_should_return_value_12(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( "31^19" );
  token = TDOP(expression);

  TEST_ASSERT_EQUAL (12, ((FloatToken *)token)->value);
}

void test_TDOP_testing_left_shift_given_98_shifting_to_left_2_times_should_return_392(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( " 98 << 2 " );
  token = TDOP(expression);

  TEST_ASSERT_EQUAL (392, ((FloatToken *)token)->value);
}

void test_TDOP_testing_left_shift_given_complicated_expression_with_left_shift_involved_should_solve_correctly(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( " (21 ^12) | (41 << 8) " );
  token = TDOP(expression);

  TEST_ASSERT_EQUAL ((21 ^12) | (41 << 8), ((FloatToken *)token)->value);
}

void test_TDOP_testing_right_shift_given_63_shifting_to_right_8_times_should_return_0(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( " 63 >> 8 " );
  token = TDOP(expression);

  TEST_ASSERT_EQUAL (0, ((FloatToken *)token)->value);
}

void test_TDOP_testing_left_shift_given_complicated_expression_with_right_shift_involved_should_solve_correctly(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( " (59>>2)*92^32 " );
  token = TDOP(expression);

  TEST_ASSERT_EQUAL ((59>>2)*92^32, ((FloatToken *)token)->value);
}

void test_TDOP_testing_less_than_given_57_lesser_than_23_should_return_false(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( " 57 < 23 " );
  token = TDOP(expression);

  TEST_ASSERT_FALSE (((FloatToken *)token)->value);
}

void test_TDOP_testing_less_than_given_expression_involving_lesser_than_should_solve_correctly(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( " (74 <(63-2)) + 23%6 " );
  token = TDOP(expression);

  TEST_ASSERT_EQUAL ((74 <(63-2)) + 23%6, ((FloatToken *)token)->value);
}

void test_TDOP_testing_greater_than_given_238_greater_than_78_should_return_true(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( "238>78" );
  token = TDOP(expression);

  TEST_ASSERT_TRUE (((FloatToken *)token)->value);
}

void test_TDOP_testing_greater_than_given_expression_involving_greater_than_should_solve_correctly(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( " 23>9+-9|6^23-(12*54) " );
  token = TDOP(expression);

  TEST_ASSERT_EQUAL (23>9+-9|6^23-(12*54), ((FloatToken *)token)->value);
}

void test_TDOP_testing_less_than_equal_to_given_922_less_than_equal_to_922_should_return_true(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( " 922<=922 " );
  token = TDOP(expression);

  TEST_ASSERT_EQUAL (1, ((FloatToken *)token)->value);
}

void test_TDOP_testing_less_than_equal_to_given_expression_involving_lesser_than_equal_to_should_solve_correctly(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( " 37 <= 2 + 1 " );
  token = TDOP(expression);

  TEST_ASSERT_EQUAL (37 <= 2 + 1, ((FloatToken *)token)->value);
}

void test_TDOP_testing_greater_than_equal_to_given_43_greater_than_equal_to_44_should_return_false(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( "43>=78" );
  token = TDOP(expression);

  TEST_ASSERT_FALSE (((FloatToken *)token)->value);
}

void test_TDOP_testing_greater_than_equal_to_given_expression_involving_greater_than_equal_to_should_solve_correctly(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( " (8&9*73)<<(12>=6)" );
  token = TDOP(expression);

  TEST_ASSERT_EQUAL ((8&9*73)<<(12>=6), ((FloatToken *)token)->value);
}

void test_TDOP_testing_equal_to_given_777_equals_to_777_should_return_true(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( "777 == 777" );
  token = TDOP(expression);

  TEST_ASSERT_TRUE (((FloatToken *)token)->value);
}

void test_TDOP_testing_equal_to_given_expression_involving_equal_to_should_solve_correctly(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( " 23==9 * 7|2" );
  token = TDOP(expression);

  TEST_ASSERT_EQUAL (23==9 * 7|2, ((FloatToken *)token)->value);
}

void test_TDOP_testing_not_equal_to_given_157_not_equals_to_157_should_return_false(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( "157 != 157" );
  token = TDOP(expression);

  TEST_ASSERT_FALSE (((FloatToken *)token)->value);
}

void test_nudInt_given_8_point_64_should_return_8_point_64_token(void) {
  Tokenizer *expression;
  Token *token, *token1, *token2;

  expression = createTokenizer("8.64");
  token1 = getAdvanceToken(expression);
  token2 = getAdvanceToken(expression);
  token = nudFloat(token1, token2, expression, 0);

  TEST_ASSERT_EQUAL_FLOAT(8.64,((FloatToken *)token1)->value);
  TEST_ASSERT_EQUAL(FLOAT_SYMBOL, token1->symbol);
}

void test_getTokenType_given_a_floating_number_should_return_true(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer("8.3");
  token = getAdvanceToken(expression);

  TEST_ASSERT_FALSE(getTokenType(token));
  TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, token->type);
}

void test_TDOP_given_2_point_32_minus_9_point_94_should_return_11(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer(" 2.2 - -9 ");
  token = TDOP(expression);

  TEST_ASSERT_EQUAL_FLOAT (2.20 - -9, ((FloatToken *)token)->value);
}

void test_TDOP_testingw_bitwise_OR_given_2_statements_with_1_vertical_line_in_between_should_solve_correctly(void) {
  Tokenizer *expression;
  Token *token;

  expression = createTokenizer( " (((2+4)*3)-3) %10" );
  token = TDOP(expression);

  TEST_ASSERT_EQUAL ((((2+4)*3)-3) %10, ((FloatToken *)token)->value);
}

void test_newFloatToken_given_a_float_number_should_display_correctly(void) {
  Tokenizer *expression;
  Token *leftToken, *rightToken, *token;

  expression = createTokenizer(" 7.4  5.6 ");
  leftToken = getAdvanceToken(expression);
  rightToken = getAdvanceToken(expression);
  token = newFloatToken(13,token,leftToken, rightToken);

  TEST_ASSERT_EQUAL(TOKEN_FLOAT_TYPE, token->type);
  TEST_ASSERT_EQUAL(FLOAT_SYMBOL, token->symbol);
  TEST_ASSERT_EQUAL_STRING(" 7.4  5.6 ", token->originalStr);
  TEST_ASSERT_EQUAL(1, token->startColumn);
  TEST_ASSERT_EQUAL(8, token->length);
  TEST_ASSERT_EQUAL_STRING("7.4  5.6", token->str);

}

void test_getTokenValue_given_an_integer_number_should_return_value_correctly(void) {
  Tokenizer *expression;
  Token *token;
  double value;

  expression = createTokenizer(" 6 ");
  token = getAdvanceToken(expression);

  value = getTokenValue(token);

  TEST_ASSERT_EQUAL_FLOAT(6.000, value);
}

void test_getTokenValue_given_a_floating_point_number_should_return_its_own_value(void) {
  Tokenizer *expression;
  Token *token;
  double value;

  expression = createTokenizer(" 834.1 ");
  token = getAdvanceToken(expression);

  value = getTokenValue(token);

  TEST_ASSERT_EQUAL_FLOAT(834.1, value);
}

void test_TDOP_given_unmatched_bracket_expression_should_throw_ERR_MISSING_BRACKET(void) {
  Tokenizer *expression;
  Token *token;

  Try {
  expression = createTokenizer( "(7 + 6 ");
  token = TDOP(expression);
  TEST_FAIL_MESSAGE ("Expected ERR_MISSING_BRACKET to be thrown! But no exception is thrown.");
  } Catch(e) {
  dumpTokenErrorMessage(e,1);
  TEST_ASSERT_EQUAL (ERR_MISSING_BRACKET, e->errorCode);
  freeException(e);
  }
}

void test_TDOP_given_fractional_number_in_logical_operation_should_throw_ERR_NOT_AN_INTEGER(void) {
  Tokenizer *expression;
  Token *token;

  Try {
  expression = createTokenizer( " 8.23 << 5");
  token = TDOP(expression);
  TEST_FAIL_MESSAGE ("Expected ERR_NOT_AN_INTEGER to be thrown! But no exception is thrown.");
  } Catch(e) {
  dumpTokenErrorMessage(e,1);
  TEST_ASSERT_EQUAL (ERR_NOT_AN_INTEGER, e->errorCode);
  freeException(e);
  }
}

void test_given_unknown_character_should_throw_ERR_INVALID_SYMBOL(void) {
Tokenizer *expression;
Token *token;

  Try {
  expression = createTokenizer( " 7.24 ? 2");
  token = TDOP(expression);
  TEST_FAIL_MESSAGE ("Expected ERR_INVALID_SYMBOL to be thrown! But no exception is thrown.");
  } Catch(e) {
  dumpTokenErrorMessage(e,1);
  TEST_ASSERT_EQUAL (ERR_INVALID_SYMBOL, e->errorCode);
  freeException(e);
  }
}

void test_given_a_not_supported_operator_should_throw_ERR_UNSUPPORTED_SYMBOL(void) {
Tokenizer *expression;
Token *token;

  Try {
  expression = createTokenizer( " 3 = =2 ");
  token = TDOP(expression);
  TEST_FAIL_MESSAGE ("Expected UNSUPPORTED_SYMBOL to be thrown! But no exception is thrown.");
  } Catch(e) {
  dumpTokenErrorMessage(e,1);
  TEST_ASSERT_EQUAL (UNSUPPORTED_SYMBOL, e->errorCode);
  freeException(e);
  }
}

void test_given_invalid_symbol_placement_should_throw_INVALID_SYMBOL_PLACEMENT(void) {
Tokenizer *expression;
Token *token;

  Try {
  expression = createTokenizer( " <9 + 4 ");
  token = TDOP(expression);
  TEST_FAIL_MESSAGE ("Expected INVALID_SYMBOL_PLACEMENT to be thrown! But no exception is thrown.");
  } Catch(e) {
  dumpTokenErrorMessage(e,1);
  TEST_ASSERT_EQUAL (INVALID_SYMBOL_PLACEMENT, e->errorCode);
  freeException(e);
  }
}

void test_given_numbers_divided_by_zero_should_throw_ERR_UNDEFINED(void) {
Tokenizer *expression;
Token *token;

  Try {
  expression = createTokenizer( " 10/(0*9) ");
  token = TDOP(expression);
  TEST_FAIL_MESSAGE ("Expected ERR_UNDEFINED to be thrown! But no exception is thrown.");
  } Catch(e) {
  dumpTokenErrorMessage(e,1);
  TEST_ASSERT_EQUAL (ERR_UNDEFINED, e->errorCode);
  freeException(e);
  }
}

void test_given_an_empty_expression_should_throw_ERR_INVALID_EXPRESSION(void) {
Tokenizer *expression;
Token *token;

  Try {
  expression = createTokenizer( "  " );
  token = TDOP(expression);
  TEST_FAIL_MESSAGE ("Expected ERR_INVALID_EXPRESSION to be thrown! But no exception is thrown.");
  } Catch(e) {
  dumpTokenErrorMessage(e,1);
  TEST_ASSERT_EQUAL (ERR_INVALID_EXPRESSION, e->errorCode);
  freeException(e);
  }
}

void test_given_2_brackets_expression_with_no_operator_in_between_should_throw_ERR_EXPECTING_OPERATOR(void) {
Tokenizer *expression;
Token *token;

  Try {
  expression = createTokenizer( " (2*3) (5-2)  ");
  token = TDOP(expression);
  TEST_FAIL_MESSAGE ("Expected ERR_EXPECTING_OPERATOR to be thrown! But no exception is thrown.");
  } Catch(e) {
  dumpTokenErrorMessage(e,1);
  TEST_ASSERT_EQUAL (ERR_EXPECTING_OPERATOR, e->errorCode);
  freeException(e);
  }
}

void test_given_2_integers_with_no_operator_should_throw_ERR_EXPECTING_OPERATOR(void) {
Tokenizer *expression;
Token *token;

  Try {
  expression = createTokenizer( " 7 1 + 9 ");
  token = TDOP(expression);
  TEST_FAIL_MESSAGE ("Expected ERR_EXPECTING_OPERATOR to be thrown! But no exception is thrown.");
  } Catch(e) {
  dumpTokenErrorMessage(e,1);
  TEST_ASSERT_EQUAL (ERR_EXPECTING_OPERATOR, e->errorCode);
  freeException(e);
  }
}

void test_TDOP_given_a_left_number_an_operator_but_no_right_token_should_throw_ERR_EXPECTING_OPERAND(void) {
  Tokenizer *expression;
  Token *token;

  Try {
  expression = createTokenizer( " 7 <<  " );
  token = TDOP(expression);
  TEST_FAIL_MESSAGE ("Expected ERR_EXPECTING_OPERAND to be thrown! But no exception is thrown.");
  } Catch(e) {
  dumpTokenErrorMessage(e,1);
  TEST_ASSERT_EQUAL (ERR_EXPECTING_OPERAND, e->errorCode);
  freeException(e);
  }
}

/*void test_given_invalid_symbol_placement_nud_is_NULL_should_throw_SYSTEM_ERROR(void) {
Tokenizer *expression;
Token *token;

  Try {
  expression = createTokenizer( " *2 ");
  token = TDOP(expression);
  TEST_FAIL_MESSAGE ("Expected SYSTEM_ERROR to be thrown! But no exception is thrown.");
  } Catch(e) {
  dumpTokenErrorMessage(e,1);
  TEST_ASSERT_EQUAL (SYSTEM_ERROR, e->errorCode);
  freeException(e);
  }
}*/
