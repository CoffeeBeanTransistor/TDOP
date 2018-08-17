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
