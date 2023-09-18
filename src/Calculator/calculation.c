#include "calc.h"

int is_binary(int id) {
  return id == ADD_ID || id == SUB_ID || id == MUL_ID || id == DIV_ID ||
         id == MOD_ID || id == POW_ID;
}

double un_minus(double x) { return x *= -1; }
double add(double a, double b) { return a + b; }
double sub(double a, double b) { return a - b; }
double mul(double a, double b) { return a * b; }
double percent(double x) { return x / 100; };
double div_custom(double a, double b) { return a / b; }
double mod(double a, double b) { return fmod(a, b); }
double ctg(double x) { return 1 / tan(x); }
double ln(double x) { return log(x); }
double log(double x) { return log10(x); }

double process_unary(int id, double x) {
  double (*operations_unary[12])(double) = {
      sin, cos, tan, ctg, asin, acos, atan, sqrt, ln, log, un_minus, percent};
  return (operations_unary[id - SIN_ID](x));
}

double process_binary(int id, double a, double b) {
  double (*operations_binary[6])(double, double) = {add,        sub, mul,
                                                    div_custom, pow, mod};
  return (operations_binary[id - ADD_ID](a, b));
}

void postfix_to_answer_step(const queue_node *node, stack *tmp_st, double x) {
  int id = node->id;
  double val = node->val;
  if (id == X_ID) {
    id = NUM_ID;
    val = x;
  }
  if (id == NUM_ID)
    push(tmp_st, id, val);
  else {
    double tmp, b = tmp_st->end_node->val;
    if (is_binary(id)) {
      double a = tmp_st->end_node->prev_node->val;
      tmp = process_binary(id, a, b);
      pop(tmp_st);
    } else
      tmp = process_unary(id, b);
    pop(tmp_st);
    push(tmp_st, NUM_ID, tmp);
  }
}

double postfix_to_answer(queue *que, double x) {
  stack *tmp_st = init_stack();
  while (que->head) {
    postfix_to_answer_step(que->head, tmp_st, x);
    dequeue(que);
  }
  double val = tmp_st->end_node->val;
  destroy_stack(tmp_st);

  return val;
}

double calculation(char *str, double x, int *fl) {
  queue *que = parse(str);
  double result = -1;
  if (que)
    result = postfix_to_answer(que, x);
  else
    *fl = 1;

  destroy_queue(que);
  return result;
}

// double calc(char *str, double x) {
//   int fl = 0;
//   double res;
//   if ((fl = validation(str)) == 0) {
//     res = calculation(str, x, &fl);
//     if (fl) res = -1;
//   } else {
//     res = -1;
//   }
//   return res;
// }
