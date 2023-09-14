#include "smartcalc.h"

int lengthCheck(char *str) { return (strlen(str) > 255) ? 1 : 0; }

int divisionByZero(char *str) {
  int fl = 0;
  double val;
  while (*str) {
    if (*str == '/') {
      sscanf(++str, "%lf", &val);
      if (val == 0.0) fl = 1;
    }
    str++;
  }
  return fl;
}

int check_brk(char *str) {
  int fl = 0;
  char *tmp = str;
  stack *tmp_st = init_stack();
  while (*tmp) {
    if (*tmp == '(')
      push(tmp_st, BRK_OPEN_ID, 0);
    else if (*tmp == ')' && tmp_st->end_node)
      pop(tmp_st);
    else if (!(tmp_st->end_node) && *tmp == ')')
      fl = 1;
    tmp++;
  }
  if (tmp_st->end_node) fl = 1;
  destroy_stack(tmp_st);
  return fl;
}

int valid_step(char *str, stack *st, int ind, int *unary) {
  char *s = str + ind;
  int id;

  if (isdigit(*s)) {
    ind += len_num(s);
    push(st, NUM_ID, 1);
    *unary = 0;
  } else if ((id = is_function(s)) != -1) {
    if (st->end_node != NULL && st->end_node->id == BRK_CLOSE_ID)
      ind = -1;
    else
      ind += len_func(id);
    push(st, id, 0);
    *unary = 1;
  } else if ((id = is_operation(s, (*unary = unary_check(s)))) != -1) {
    if (st->end_node != NULL && id != UN_MIN_ID && id != BRK_OPEN_ID &&
        id != BRK_CLOSE_ID && (st->end_node->id >= 1 && st->end_node->id <= 6))
      ind = -1;
    else
      ind += len_operation(id);
    push(st, id, 0);
    if (id == BRK_OPEN_ID && id == UN_MIN_ID) *unary = 1;
  } else if (*s == 'x') {
    push(st, X_ID, 0);
    *unary = 0;
    ind++;
  } else {
    ind = -1;
  }
  return ind;
}

int validation(char *str) {
  int fl = 0;
  if (str) {
    remove_space(str);
    if (!lengthCheck(str) && !check_brk(str)) {
      if (!divisionByZero(str)) {
        int i = 0, unary = 1;
        stack *st = init_stack();
        while (i >= 0 && str[i] != '\0') i = valid_step(str, st, i, &unary);
        if (i == -1) fl = 1;
        destroy_stack(st);
      } else {
        fl = -1;
      }
    } else {
      fl = 1;
    }
  } else {
    fl = 1;
  }
  return fl;
}
