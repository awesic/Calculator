#include "smartcalc.h"

int parsing_char(char *str, queue *que, stack *st, int place, int *is_unary) {
  char *token = str + place;
  int id;

  if (isdigit(*token)) {
    double val = get_digit(token);
    enqueue(que, NUM_ID, val);
    place += len_num(token);
    *is_unary = 0;
  } else if ((id = is_function(token)) != -1) {
    place += len_func(id);
    push(st, id, 0);
    *is_unary = 1;
  } else if ((id = is_operation(token, (*is_unary = unary_check(token)))) !=
                 -1 &&
             is_operation(token, *is_unary) != BRK_CLOSE_ID) {
    if (id != BRK_OPEN_ID) process_prior(que, st, id);
    push(st, id, 0);
    place += len_operation(id);
  } else if (is_operation(token, *is_unary) == BRK_CLOSE_ID) {
    if (close_bracket(que, st))
      place = -1;
    else
      place++;
  } else if (*token == 'x') {
    enqueue(que, X_ID, 0);
    place++;
  }
  // else
  //   place = -1;

  return place;
}

queue *parse(char *str) {
  queue *que = init_queue();
  stack *st = init_stack();
  int i = 0, unary = 1;
  while (i > -1 && str[i] != '\0') {
    i = parsing_char(str, que, st, i, &unary);
  }
  while (i != -1 && st->end_node) {
    if (st->end_node->id == BRK_OPEN_ID || st->end_node->id == BRK_CLOSE_ID)
      i = -1;
    enqueue(que, st->end_node->id, st->end_node->val);
    pop(st);
  }
  destroy_stack(st);
  if (i == -1) que = NULL;
  return que;
}

void remove_space(char *str_func) {
  char *tmp = str_func;
  do {
    while (isspace(*tmp)) ++tmp;
    *str_func++ = *tmp++;
  } while (*tmp);
  *str_func = '\0';
}

int is_function(char *str) {
  int fl = -1;
  if (!(strncmp(str, "sin(", SIN_LEN + 1))) fl = SIN_ID;
  if (!(strncmp(str, "cos(", COS_LEN + 1))) fl = COS_ID;
  if (!(strncmp(str, "tan(", TAN_LEN + 1))) fl = TAN_ID;
  if (!(strncmp(str, "ctg(", CTG_LEN + 1))) fl = CTG_ID;
  if (!(strncmp(str, "asin(", ASIN_LEN + 1))) fl = ASIN_ID;
  if (!(strncmp(str, "acos(", ACOS_LEN + 1))) fl = ACOS_ID;
  if (!(strncmp(str, "atan(", ATAN_LEN + 1))) fl = ATAN_ID;
  if (!(strncmp(str, "sqrt(", SQRT_LEN + 1))) fl = SQRT_ID;
  if (!(strncmp(str, "ln(", LN_LEN + 1))) fl = LN_ID;
  if (!(strncmp(str, "log(", LOG_LEN + 1))) fl = LOG_ID;
  //  if (!(strncmp(str, "mod", MOD_LEN))) fl = MOD_ID;

  return fl;
}

int len_func(int id) {
  int len = 0;
  if (id == SIN_ID)
    len = SIN_LEN;
  else if (id == COS_ID)
    len = COS_LEN;
  else if (id == TAN_ID)
    len = TAN_LEN;
  else if (id == CTG_ID)
    len = CTG_LEN;
  else if (id == ASIN_ID)
    len = ASIN_LEN;
  else if (id == ACOS_ID)
    len = ACOS_LEN;
  else if (id == ATAN_ID)
    len = ATAN_LEN;
  else if (id == SQRT_ID)
    len = SQRT_LEN;
  else if (id == LN_ID)
    len = LN_LEN;
  else if (id == LOG_ID)
    len = LOG_LEN;
  // else if (id == MOD_ID)
  //   len = MOD_LEN;

  return len;
}

int is_digit(char c) {
  int flag = 0;
  if (c >= '0' && c <= '9') flag = 1;
  return flag;
}

int len_num(const char *str) {
  int i = 0, point_flag = 0;
  while (is_digit(str[i]) || (str[i] == '.' && point_flag < 1)) {
    if (str[i] == '.') point_flag++;
    i++;
  }
  return i;
}

int len_operation(int id) {
  int len = 1;
  if (id == MOD_ID) len = MOD_LEN;
  return len;
}

int is_operation(const char *str, int is_unary) {
  int flag = -1;
  if (*str == '+' && !is_unary)
    flag = ADD_ID;
  else if (*str == '+' && is_unary)
    flag = UN_PLUS_ID;
  else if (*str == '-' && !is_unary)
    flag = SUB_ID;
  else if (*str == '-' && is_unary)
    flag = UN_MIN_ID;
  else if (*str == '/')
    flag = DIV_ID;
  else if (*str == '*')
    flag = MUL_ID;
  else if (*str == '(')
    flag = BRK_OPEN_ID;
  else if (*str == ')')
    flag = BRK_CLOSE_ID;
  else if (*str == '^')
    flag = POW_ID;
  else if (!(strncmp(str, "mod", MOD_LEN)))
    flag = MOD_ID;
  else if (*str == '%')
    flag = PERC_ID;

  return flag;
}

int unary_check(const char *str) {
  const char *c = str - 1;
  return !isdigit(*c) && *c != ')' && *c != '%' && *c != 'x';
}

double get_digit(char *str) {
  double val;
  sscanf(str, "%lf", &val);
  return val;
}

int prior(int id) {
  int pr = -1;
  if (id == ADD_ID || id == SUB_ID) {
    pr = ADD_SUB_PR;
  } else if (id == MUL_ID || id == DIV_ID || id == MOD_ID) {
    pr = MUL_DIV_MOD_PR;
  } else if (id == UN_MIN_ID || id == UN_PLUS_ID || id == PERC_ID) {
    pr = UN_MINPLUS_PR;
  } else if (id >= 9 && id <= 18) {
    pr = FUNC_PR;
  } else if (id == POW_ID)
    pr = POW_PR;
  return pr;
}

int close_bracket(queue *res_que, stack *tmp_st) {
  int fl = 0;
  while (tmp_st->end_node->id != BRK_OPEN_ID) {
    if (!tmp_st->end_node->prev_node) fl = 1;
    enqueue(res_que, tmp_st->end_node->id, tmp_st->end_node->val);
    pop(tmp_st);
  }
  pop(tmp_st);
  return fl;
}

void process_prior(queue *res_que, stack *tmp_st, int id) {
  int self_prior = prior(id);
  while (tmp_st->end_node && tmp_st->end_node->id != BRK_OPEN_ID &&
         self_prior <= prior(tmp_st->end_node->id)) {
    enqueue(res_que, tmp_st->end_node->id, tmp_st->end_node->val);
    pop(tmp_st);
  }
}

// queue *copy_queue(queue *que) {
//   queue *new_que = init_queue();
//   queue_node *tmp_node = que->head;
//   while (tmp_node) {
//     enqueue(new_que, tmp_node->id, tmp_node->val);
//     tmp_node = tmp_node->next_node;
//   }
//   return new_que;
// }

// double result_answer_for_one_x(queue *res_que, double x) {
//   queue *copy_que = copy_queue(res_que);
//   double x_res = postfix_to_answer(copy_que, x);
//   destroy_queue(copy_que);
//   return x_res;
// }
