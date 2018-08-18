#include "unity.h"
#include "TDOP.h"
#include "Tokenizer.h"
#include "Token.h"
#include "TokenData.h"
#include "Operator.h"
#include "Exception.h"
#include "CException.h"
#include "Error.h"
#include <malloc.h>
CEXCEPTION_T e;

void setUp(void)
{
}

void tearDown(void)
{
}
void test_evaluate_given_fractional_number_in_logical_operation_should_throw_ERR_NOT_AN_INTEGER(void) {
  Tokenizer *expression;
  Token *token;

  Try {
  expression = createTokenizer( " 8.23 << 5");
  token = evaluate(expression,0);
  TEST_FAIL_MESSAGE ("Expected ERR_NOT_AN_INTEGER to be thrown! But no exception is thrown.");
  } Catch(e) {
  dumpTokenErrorMessage(e,1);
  TEST_ASSERT_EQUAL (ERR_NOT_AN_INTEGER, e->errorCode);
  freeException(e);
  freeTokenizer(expression);
  }
}

void test_given_unknown_character_should_throw_ERR_UNDEFINED_SYMBOL(void) {
  Tokenizer *expression;
  Token *token;

  Try {
  expression = createTokenizer( " 7.24 ? 2");
  token = evaluate(expression,0);
  TEST_FAIL_MESSAGE ("Expected ERR_UNDEFINED_SYMBOL to be thrown! But no exception is thrown.");
  } Catch(e) {
  dumpTokenErrorMessage(e,1);
  TEST_ASSERT_EQUAL (ERR_UNDEFINED_SYMBOL, e->errorCode);
  freeException(e);
  freeTokenizer(expression);
  }
}

void test_given_a_not_supported_operator_should_throw_ERR_UNSUPPORTED_SYMBOL(void) {
  Tokenizer *expression;
  Token *token;

  Try {
  expression = createTokenizer( " 3 = =2 ");
  token = evaluate(expression,0);
  TEST_FAIL_MESSAGE ("Expected UNSUPPORTED_SYMBOL to be thrown! But no exception is thrown.");
  } Catch(e) {
  dumpTokenErrorMessage(e,1);
  TEST_ASSERT_EQUAL (UNSUPPORTED_SYMBOL, e->errorCode);
  freeException(e);
  freeTokenizer(expression);
  }
}

void test_given_invalid_symbol_placement_should_throw_INVALID_SYMBOL_PLACEMENT(void) {
  Tokenizer *expression;
  Token *token;

  Try {
  expression = createTokenizer( " <9 + 4 ");
  token = evaluate(expression,0);
  TEST_FAIL_MESSAGE ("Expected INVALID_SYMBOL_PLACEMENT to be thrown! But no exception is thrown.");
  } Catch(e) {
  dumpTokenErrorMessage(e,1);
  TEST_ASSERT_EQUAL (INVALID_SYMBOL_PLACEMENT, e->errorCode);
  freeException(e);
  freeTokenizer(expression);
  }
}

void test_given_numbers_divided_by_zero_should_throw_ERR_UNDEFINED(void) {
  Tokenizer *expression;
  Token *token;

  Try {
  expression = createTokenizer( " 10/(0*9) ");
  token = evaluate(expression,0);
  TEST_FAIL_MESSAGE ("Expected ERR_UNDEFINED to be thrown! But no exception is thrown.");
  } Catch(e) {
  dumpTokenErrorMessage(e,1);
  TEST_ASSERT_EQUAL (ERR_UNDEFINED, e->errorCode);
  freeException(e);
  freeTokenizer(expression);
  }
}

void test_given_number_modulo_by_zero_should_throw_ERR_UNDEFINED(void) {
  Tokenizer *expression;
  Token *token;

  Try {
  expression = createTokenizer( " 7 % 0");
  token = evaluate(expression,0);
  TEST_FAIL_MESSAGE ("Expected ERR_UNDEFINED to be thrown! But no exception is thrown.");
  } Catch(e) {
  dumpTokenErrorMessage(e,1);
  TEST_ASSERT_EQUAL (ERR_UNDEFINED, e->errorCode);
  freeException(e);
  freeTokenizer(expression);
  }
}

void test_given_2_brackets_expression_with_no_operator_in_between_should_throw_ERR_EXPECTING_OPERATOR(void) {
Tokenizer *expression;
Token *token;

  Try {
  expression = createTokenizer( " (2*3) (5-2)  ");
  token = evaluate(expression,0);
  TEST_FAIL_MESSAGE ("Expected ERR_EXPECTING_OPERATOR to be thrown! But no exception is thrown.");
  } Catch(e) {
  dumpTokenErrorMessage(e,1);
  TEST_ASSERT_EQUAL (ERR_EXPECTING_OPERATOR, e->errorCode);
  freeException(e);
  freeTokenizer(expression);
  }
}

void test_given_2_integers_with_no_operator_should_throw_ERR_EXPECTING_OPERATOR(void) {
Tokenizer *expression;
Token *token;

  Try {
  expression = createTokenizer( " 7 1 + 9 ");
  token = evaluate(expression,0);
  TEST_FAIL_MESSAGE ("Expected ERR_EXPECTING_OPERATOR to be thrown! But no exception is thrown.");
  } Catch(e) {
  dumpTokenErrorMessage(e,1);
  TEST_ASSERT_EQUAL (ERR_EXPECTING_OPERATOR, e->errorCode);
  freeException(e);
  freeTokenizer(expression);
  }
}

void test_evaluate_given_a_left_number_an_operator_but_no_right_token_should_throw_ERR_EXPECTING_OPERAND(void) {
  Tokenizer *expression;
  Token *token;

  Try {
  expression = createTokenizer( " 7 <<  " );
  token = evaluate(expression,0);
  TEST_FAIL_MESSAGE ("Expected ERR_EXPECTING_OPERAND to be thrown! But no exception is thrown.");
  } Catch(e) {
  dumpTokenErrorMessage(e,1);
  TEST_ASSERT_EQUAL (ERR_EXPECTING_OPERAND, e->errorCode);
  freeException(e);
  freeTokenizer(expression);
  }
}
