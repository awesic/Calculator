#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Calculator/calc.h"
#include "Calculator/validator.h"

#define EPSILON 1e-6
#define PI 3.1415926
#define LEN(express) (int)(sizeof(express) / sizeof(express[0]))

START_TEST(arithmetic_tests) {
  char *expressions[] = {"2 + (48.643 - 394) * 4",
                         "-4 + 9.004 - (583 * -3) / 9.05",
                         "35\% * 30485",
                         "47mod 5 / 3",
                         "-(-5.537 +89.097 - 325) * --5",
                         "757.09 * -495",
                         "93.0543 + 5^3",
                         "11^5 / 7.08",
                         "(84 - 4)) - 49",
                         "94 - 949283 --- + 3/*3",
                         "3 * - sqrt(4 + 9)",
                         "sqrt(2^2 + 7^2) * 32 - 9 /3.98"};
  double answer_list[] = {2 + (48.643 - 394) * 4,
                          (-4 + 9.004 - (583 * (-3)) / 9.05),
                          0.35 * 30485,
                          (47 % 5) / 3.0,
                          -(-5.537 + 89.097 - 325) * -(-5),
                          757.09 * -495,
                          93.0543 + pow(5, 3),
                          pow(11, 5) / 7.08,
                          -1,
                          -1,
                          3 * (-sqrt(4 + 9)),
                          sqrt(pow(2, 2) + pow(7, 2)) * 32 - 9 / 3.98};
  for (int i = 0; i < LEN(expressions); ++i) {
    char str[256];
    strcpy(str, expressions[i]);
    double res;
    int check = validation(str);
    if (check == 0) {
      res = calculation(str, 0.0, &check);
      if (check == 1) res = -1;
    } else {
      res = -1;
    }
    ck_assert_ldouble_eq_tol(res, answer_list[i], EPSILON);
  }
}
END_TEST

START_TEST(sin_tests) {
  char *expressions[] = {"sin(0)",
                         "sin(1)",
                         "sin(3.1415926) + sin(-45)",
                         "sin(3.1415926/ 2)",
                         "sin(-3.1415926 / 2)",
                         "2 * sin(3 * 3.1415926 / 2)",
                         "sin ( - 3 * 3.1415926 / 2)",
                         "sin(5.1234567890123456)",
                         "3 + -sin(9 + 9)"};
  double answer[] = {sin(0),
                     sin(1),
                     sin(PI) + sin(-45),
                     sin(PI / 2),
                     sin(-PI / 2),
                     2 * sin(3 * PI / 2),
                     sin(-3 * PI / 2),
                     sin(5.1234567890123456),
                     3 + -sin(9 + 9)};
  long double res;
  for (int i = 0; i < LEN(expressions); ++i) {
    char *str = strdup(expressions[i]);
    int check = validation(str);
    if (check == 0) {
      res = calculation(str, 0.0, &check);
      if (check == 1) res = -1;
    } else {
      res = -1;
    }
    ck_assert_ldouble_eq_tol(res, answer[i], EPSILON);
    free(str);
  }
}
END_TEST

START_TEST(cos_tests) {
  char *expressions[] = {"cos(0)",
                         "cost(1)",
                         "cos(3.1415926) + cos(-45)",
                         "cos(3.1415926/ 2)",
                         "cos(-3.1415926 / 2)",
                         "2 * cos(3 * 3.1415926 / 2)",
                         "cos ( - 3 * 3.1415926 / 2)",
                         "cos(5.1234567890123456)",
                         "3 + -cos(9 + 9)"};
  double answer[] = {cos(0),
                     -1,
                     cos(PI) + cos(-45),
                     cos(PI / 2),
                     cos(-PI / 2),
                     2 * cos(3 * PI / 2),
                     cos(-3 * PI / 2),
                     cos(5.1234567890123456),
                     3 + -cos(9 + 9)};
  double res;
  for (int i = 0; i < LEN(expressions); ++i) {
    char *str = strdup(expressions[i]);
    int check = validation(str);
    if (check == 0) {
      res = calculation(str, 0.0, &check);
      if (check == 1) res = -1;
    } else {
      res = -1;
    }
    ck_assert_ldouble_eq_tol(res, answer[i], EPSILON);
    free(str);
  }
}
END_TEST

START_TEST(tan_tests) {
  char *expressions[] = {"tan(0)",
                         "ctg(1)",
                         "tan(3.1415926) + tan(-45)",
                         "tan(3.1415926/ 2)",
                         "tan(-3.1415926 / 2)",
                         "2 * tan(3 * 3.1415926 / 2)",
                         "tan ( - 3 * 3.1415926 / 2)",
                         "tan(5.1234567890123456)",
                         "3 + -tan(9 + 9)"};
  double answer[] = {tan(0),
                     ctg(1),
                     tan(PI) + tan(-45),
                     tan(PI / 2),
                     tan(-PI / 2),
                     2 * tan(3 * PI / 2),
                     tan(-3 * PI / 2),
                     tan(5.1234567890123456),
                     3 + -tan(9 + 9)};
  double res;
  for (int i = 0; i < LEN(expressions); ++i) {
    char *str = strdup(expressions[i]);
    int check = validation(str);
    if (check == 0) {
      res = calculation(str, 0.0, &check);
      if (check == 1) res = -1;
    } else {
      res = -1;
    }
    ck_assert_ldouble_eq_tol(res, answer[i], EPSILON);
    free(str);
  }
}
END_TEST

START_TEST(asin_tests) {
  char *expressions[] = {"asin(0)",
                         "asin(1)",
                         "asin(-1)",
                         "asin(-0.7) + 94 * 4",
                         "9 * asin(0.0001) - 2.987",
                         "2 * asin(1 / 2)",
                         "asin ( - 0.8 / 2)",
                         "asin(0.1234567890123456)",
                         "3 + -asin(-0.007)"};
  double answer[] = {asin(0),
                     asin(1),
                     asin(-1),
                     asin(-0.7) + 94 * 4,
                     9 * asin(0.0001) - 2.987,
                     1.0471976,
                     asin(-0.8 / 2),
                     asin(0.1234567890123456),
                     3 + -asin(-0.007)};
  double res;
  for (int i = 0; i < LEN(expressions); ++i) {
    char *str = strdup(expressions[i]);
    int check = validation(str);
    if (check == 0) {
      res = calculation(str, 0.0, &check);
      if (check == 1) res = -1;
    } else {
      res = -1;
    }
    ck_assert_ldouble_eq_tol(res, answer[i], EPSILON);
    free(str);
  }
}
END_TEST

START_TEST(acos_tests) {
  char *expressions[] = {"acos(0)",
                         "acos(1)",
                         "acos(-1)",
                         "acos(-0.7) + 94 * 4",
                         "9 * acos(0.0001) - 2.987",
                         "2 * acos(1 / 2)",
                         "acos ( - 0.8 / 2)",
                         "acos(0.1234567890123456)",
                         "3 + -acos(-0.007)"};
  double answer[] = {acos(0),
                     acos(1),
                     acos(-1),
                     acos(-0.7) + 94 * 4,
                     9 * acos(0.0001) - 2.987,
                     2 * 1.04719755,
                     acos(-0.8 / 2),
                     acos(0.1234567890123456),
                     3 + -acos(-0.007)};
  double res;
  for (int i = 0; i < LEN(expressions); ++i) {
    char *str = strdup(expressions[i]);
    int check = validation(str);
    if (check == 0) {
      res = calculation(str, 0.0, &check);
      if (check == 1) res = -1;
    } else {
      res = -1;
    }
    ck_assert_ldouble_eq_tol(res, answer[i], EPSILON);
    free(str);
  }
}
END_TEST

START_TEST(atan_tests) {
  char *expressions[] = {"atan(0)",
                         "atan(1)",
                         "atan(-1)",
                         "atan(-0.7) + 94 * 4",
                         "9 * atan(0.0001) - 2.987",
                         "2 * atan(1 / 2)",
                         "atan ( - 0.8 / 2)",
                         "atan(0.1234567890123456)",
                         "3 + -atan(-0.007)"};
  double answer[] = {atan(0),
                     atan(1),
                     atan(-1),
                     atan(-0.7) + 94 * 4,
                     9 * atan(0.0001) - 2.987,
                     2 * atan(1 / 2.0),
                     atan(-0.8 / 2),
                     atan(0.1234567890123456),
                     3 + -atan(-0.007)};
  double res;
  for (int i = 0; i < LEN(expressions); ++i) {
    char *str = strdup(expressions[i]);
    int check = validation(str);
    if (check == 0) {
      res = calculation(str, 0.0, &check);
      if (check == 1) res = -1;
    } else {
      res = -1;
    }
    ck_assert_ldouble_eq_tol(res, answer[i], EPSILON);
    free(str);
  }
}
END_TEST

START_TEST(ln_log_tests) {
  char *expressions[] = {"ln(9)",
                         "log(1)",
                         "ln(348 * 8 -293) + 93234",
                         "log(0.7) + 94 * 4",
                         "9 * ln(83 * 32) - 2.987",
                         "2 * log(1 / 2) + ln(83 - 31.8)",
                         "ln ( 0.8 / 2)",
                         "log(0.1234567890123456)",
                         "3 + -ln(0.007)"};
  double answer[] = {ln(9),
                     log(1),
                     ln(348 * 8 - 293) + 93234,
                     log(0.7) + 94 * 4,
                     9 * ln(83 * 32) - 2.987,
                     2 * log(1 / 2.0) + ln(83 - 31.8),
                     ln(0.8 / 2),
                     log(0.1234567890123456),
                     3 + -ln(0.007)};
  double res;
  for (int i = 0; i < LEN(expressions); ++i) {
    char *str = strdup(expressions[i]);
    int check = validation(str);
    if (check == 0) {
      res = calculation(str, 0.0, &check);
      if (check == 1) res = -1;
    } else {
      res = -1;
    }
    ck_assert_ldouble_eq_tol(res, answer[i], EPSILON);
    free(str);
  }
}
END_TEST

START_TEST(x_test_1) {
  char str[256] = "cos(x)";
  double res;

  for (int x = 1; x <= 5; ++x) {
    int check = validation(str);
    if (check == 0) {
      res = calculation(str, x, &check);
      if (check == 1) res = -1;
    } else {
      res = -1;
    }

    ck_assert_ldouble_eq_tol(res, cos(x), EPSILON);
  }
}
END_TEST

START_TEST(x_test_2) {
  char str[256] = "sin(2 * x) + 5.5";
  double res;

  for (int x = 1; x <= 5; ++x) {
    int check = validation(str);
    if (check == 0) {
      res = calculation(str, x, &check);
      if (check == 1) res = -1;
    } else {
      res = -1;
    }

    ck_assert_ldouble_eq_tol(res, sin(2 * x) + 5.5, EPSILON);
  }
}
END_TEST

START_TEST(x_test_3) {
  char str[256] = "x + 3 * 3.429)";
  double res, answ = -1;

  for (int x = 1; x <= 5; ++x) {
    int check = validation(str);
    if (check == 0) {
      res = calculation(str, x, &check);
      if (check == 1) {
        res = -1;
      }
    } else {
      res = -1;
    }

    ck_assert_ldouble_eq_tol(res, answ, EPSILON);
  }
}
END_TEST

START_TEST(x_test_4) {
  char str[256] = "9 * ln(x * 3.2) - 2.987";
  double res;

  for (int x = 1; x <= 5; ++x) {
    int check = validation(str);
    if (check == 0) {
      res = calculation(str, x, &check);
      if (check == 1) res = -1;
    } else {
      res = -1;
    }

    ck_assert_ldouble_eq_tol(res, 9 * ln(x * 3.2) - 2.987, EPSILON);
  }
}
END_TEST

START_TEST(x_test_5) {
  char str[256] = "2 * log(x) + ln(x)";
  double res;

  for (int x = 1; x <= 5; ++x) {
    int check = validation(str);
    if (check == 0) {
      res = calculation(str, x, &check);
      if (check == 1) res = -1;
    } else {
      res = -1;
    }

    ck_assert_ldouble_eq_tol(res, 2 * log(x) + ln(x), EPSILON);
  }
}
END_TEST

START_TEST(x_test_6) {
  char str[256] = "x mod 2";
  double res;

  for (int x = 1; x <= 5; ++x) {
    int check = validation(str);
    if (check == 0) {
      res = calculation(str, x, &check);
      if (check == 1) res = -1;
    } else {
      res = -1;
    }

    ck_assert_ldouble_eq_tol(res, x % 2, EPSILON);
  }
}
END_TEST

START_TEST(x_test_7) {
  char str[256] = "x mod 2";
  double res;

  for (int x = 1; x <= 5; ++x) {
    int check = validation(str);
    if (check == 0) {
      res = calculation(str, x, &check);
      if (check == 1) res = -1;
    } else {
      res = -1;
    }

    ck_assert_ldouble_eq_tol(res, x % 2, EPSILON);
  }
}
END_TEST

START_TEST(x_test_8) {
  char str[256] = "94.0003 + x * 2";
  double res;

  for (int x = 1; x <= 5; ++x) {
    int check = validation(str);
    if (check == 0) {
      res = calculation(str, x, &check);
      if (check == 1) res = -1;
    } else {
      res = -1;
    }

    ck_assert_ldouble_eq_tol(res, (94.0003 + x * 2), EPSILON);
  }
}
END_TEST

START_TEST(x_test_9) {
  char str[256] = "x + 3+x^2 -3";
  double res;

  for (int x = 1; x <= 5; ++x) {
    int check = validation(str);
    if (check == 0) {
      res = calculation(str, (double)x, &check);
      if (check == 1) res = -1;
    } else {
      res = -1;
    }

    ck_assert_ldouble_eq_tol(res, (x + 3 + pow(x, 2) - 3), EPSILON);
  }
}
END_TEST

int main(void) {
  Suite *suite = suite_create("\033[44m-= UNIT TESTS =-\033[0m");
  TCase *tcase = tcase_create(" Test ");
  int failed = 0;

  tcase_add_test(tcase, arithmetic_tests);
  tcase_add_test(tcase, sin_tests);
  tcase_add_test(tcase, cos_tests);
  tcase_add_test(tcase, tan_tests);
  tcase_add_test(tcase, asin_tests);
  tcase_add_test(tcase, acos_tests);
  tcase_add_test(tcase, atan_tests);
  tcase_add_test(tcase, ln_log_tests);
  tcase_add_test(tcase, x_test_1);
  tcase_add_test(tcase, x_test_2);
  tcase_add_test(tcase, x_test_3);
  tcase_add_test(tcase, x_test_4);
  tcase_add_test(tcase, x_test_5);
  tcase_add_test(tcase, x_test_6);
  tcase_add_test(tcase, x_test_7);
  tcase_add_test(tcase, x_test_8);
  tcase_add_test(tcase, x_test_9);
  suite_add_tcase(suite, tcase);

  SRunner *srunner = srunner_create(suite);
  srunner_set_fork_status(srunner, CK_NOFORK);
  srunner_run_all(srunner, CK_VERBOSE);
  failed = srunner_ntests_failed(srunner);
  srunner_free(srunner);

  printf("\033[31m============== FAILED: %d ==============\033[0m\n", failed);

  return failed == 0 ? 0 : 1;
}