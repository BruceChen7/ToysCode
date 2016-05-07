//
// Created by bruce on 5/7/16.
//

#include "mpc.h"
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "utils/utils.h"

long eval_op(long x, char* op, long y) {
    if(strcmp(op, "+") == 0) {
        return x + y;
    }
    if(strcmp(op, "-")== 0) {
        return x - y ;
    }

    if(strcmp(op, "*") == 0) {
        return x * y;
    }

    if(strcmp(op, "/") == 0) {
        return x / y;
    }
    return 0;
}

long eval(mpc_ast_t* t) {
    if(strstr(t->tag, "number")) {
        return atoi(t->contents);
    }

    char* op = t->children[1]->contents;
    // 计算第二个表达式的值
    long x = eval(t->children[2]);
    int i = 3;

    while(strstr(t->children[i]->tag,"exp")) {
        x = eval_op(x, op, eval(t->children[i]));
        i++;
    }
    return x;
}




int main() {
    // definition of number;
    mpc_parser_t* Number = mpc_new("number");
    mpc_parser_t* Operator = mpc_new("operator");
    mpc_parser_t* Expr = mpc_new("expr");
    mpc_parser_t* Lispy = mpc_new("lispy");

    mpca_lang(MPCA_LANG_DEFAULT,
              "                                                      \
                  number    : /-?[0-9]+/;                            \
                  operator  : '+'|'-'|'*'|'/';                       \
                  expr      : <number> | '('<operator><expr>+ ')';   \
                  lispy     : /^/<operator> <expr>+ /$/;              \
              ",
              Number, Operator, Expr, Lispy);
    puts("Lispy version 0.0.0.0.2");
    puts("Press Ctrl+c Exit\n");

    while(1) {
        char* input = readline("lispy> ");
        mpc_result_t r;
        if(mpc_parse("<stdin>", input, Lispy, &r)) {
            mpc_ast_print(r.output);
            long result = eval(r.output);
            printf("result is %li\n", result);
            mpc_ast_delete(r.output);
        } else {
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }
        free(input);
    }
    mpc_cleanup(4, Number, Operator, Expr, Lispy);
}