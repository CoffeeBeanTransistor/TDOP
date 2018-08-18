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
void test_evaluate_given_complicated_expression_with_brackets_should_solve_correctly(void) {
  Token *token;
  Tokenizer *expression;

  expression = createTokenizer(" -(7+--9)*(-1+-2*---6) ");
  token = evaluate(expression,0);

  TEST_ASSERT_EQUAL_FLOAT (-176,((FloatToken *)token)->value);
  freeTokenizer(expression);
}
