#ifndef SMARTCALC_H
#define SMARTCALC_H

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "queue_stack.h"
#include "validator.h"

#define PI 3.1415926

// parsing

void remove_space(char *str_func);
int is_function(char *str);
int len_func(int id);
int len_operation(int id);
int is_digit(char c);
double get_digit(char *str);
int len_num(const char *str);
int is_operation(const char *str, int is_unary);
int unary_check(const char *str);
int parsing_char(char *str, queue *que, stack *st, int place, int *is_unary);
queue *parse(char *str);
double calculation(char *str, double x, int *);

// double calc(char *str, double x);

// Dijkstra
int prior(int id);
// int is_num_or_x(int id);
int close_bracket(queue *res_que, stack *tmp_st);
void process_prior(queue *res_que, stack *tmp_st, int id);

// Polish notation
// queue *copy_queue(queue *que);
// double result_answer_for_one_x(queue *res_que, double x);

int is_binary(int id);
double un_minus(double x);
double add(double a, double b);
double sub(double a, double b);
double mul(double a, double b);
double div_custom(double a, double b);
double mod(double a, double b);
double ctg(double x);
double ln(double x);
double log(double x);
double process_unary(int id, double x);
double process_binary(int id, double a, double b);
void postfix_to_answer_step(const queue_node *node, stack *tmp_st, double x);
double postfix_to_answer(queue *que, double x);

#endif
