//
// Created by bruce on 5/7/16.
//

#include "mpc.h"
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "utils/utils.h"



enum {
    LVAL_ERR,
    LVAL_NUM,
    LVAL_SYM,
    LVAL_SEPR,
};

// Represent a value regardless of error value or right value
typedef struct lval{
    // What the value is
    int type;
    long num;
    // For the error code string
    char*  err;
    // For the operator
    char* sym;
    // the num of pointers to lval *;
    int count;
    struct lval** cell;
} lval;

// ctor to num
lval* lval_num(long x) {
    lval* v = malloc(sizeof(lval));
    v->type = LVAL_NUM,
    v->num = x;
    return v;
}

lval* lval_err(char* m) {
    lval* v = malloc(sizeof(lval));
    v->type = LVAL_ERR;
    v->err =  malloc(strlen(m) + 1);
    strcpy(v->err, m);
    return v;

}

lval* lval_sym(char* s) {
    lval* v = malloc(sizeof(lval));
    v->type = LVAL_SYM;
    v->sym = malloc(strlen(s) + 1);
    strcpy(v->sym, s);
    return v;
}

lval* lval_sexpr(void) {
    lval* v = malloc(sizeof(lval));
    v->type = LVAL_SEPR;
    v->cell= NULL;
    v->count = 0;
    return v;
}



void lval_del(lval* v) {
    switch (v->type) {
        case LVAL_NUM: break;
        case LVAL_ERR: free(v->err); break;
        case LVAL_SYM: free(v->sym); break;
        case LVAL_SEPR:
            for(int i = 0 ; i < v->count; i++) {
                lval_del(v->cell[i]);
            }
            free(v->cell);
            break;
    }
    free(v);
}


lval* lval_add(lval* v, lval* x) {
    v->count++;
    v->cell = realloc(v->cell, sizeof(lval*) * v->count);
    v->cell[v->count-1] = x;
    return v;
}


// Delete a value
lval* lval_pop(lval* v, int i) {
    lval* x = v->cell[i];
    memmove(&(v->cell[i]), &v->cell[i+1], sizeof(lval*) * (v->count-i-1));
    v->count--;
    v->cell = realloc(v->cell, sizeof(lval*) * v->count);
    return x;
}

lval* lval_take(lval* v, int i) {
    lval* x = lval_pop(v, i);
    lval_del(v);
    return x;
}


lval* lval_read_num(mpc_ast_t* t) {
    errno = 0;
    long x = strtol(t->contents, NULL, 10);
    return errno != ERANGE ? lval_num(x): lval_err("invalid number");
}


lval* lval_read(mpc_ast_t* t) {

    // If number or symbol
    // return conversion to that type
    if(strstr(t->tag, "number")) {
        return lval_read_num(t);
    }
    // If it's just a symbol
    if(strstr(t->tag, "symbol")) {
        return lval_sym(t->contents);
    }

    // If Root(>) or sexp the create empty list
    lval* x = NULL;
    if(strcmp(t->tag, ">") == 0) {
        x = lval_sexpr();
    }
    if(strstr(t->tag, "sexpr")) {
        x = lval_sexpr();
    }

    for(int i = 0 ; i < t->children_num; i++) {
        if(strcmp(t->children[i]->contents, "(") == 0 ) {
            continue;
        }

        if(strcmp(t->children[i]->contents, ")") == 0 ) {
            continue;
        }

        if(strcmp(t->children[i]->contents, "{") == 0 ) {
            continue;
        }

        if(strcmp(t->children[i]->contents, "}") == 0 ) {
            continue;
        }
        if(strcmp(t->children[i]->tag, "regex") == 0 ) {
            continue;
        }
        x = lval_add(x, lval_read(t->children[i]));
    }
    return x;
}



void lval_print(lval* v);

void lval_expr_print(lval* v, char open, char close) {
    putchar(open);
    for (int i = 0; i < v->count; i++) {

        /* Print Value contained within */
        lval_print(v->cell[i]);

        /* Don't print trailing space if last element */
        if (i != (v->count-1)) {
            putchar(' ');
        }
    }
    putchar(close);
}

void lval_print(lval* v) {
    switch(v->type) {
        case LVAL_NUM:
            printf("%li", v->num);
            break;
        case LVAL_SYM:
            printf("%s", v->sym);
            break;
        case LVAL_ERR:
            printf("Error : %s", v->err);
        case LVAL_SEPR:
            lval_expr_print(v, '(', ')');
            break;
    }
}

void lval_println(lval* v) {
    lval_print(v);
    putchar('\n');
}

lval* buildin_op(lval* a, char* op) {
    for(int i =  0 ; i < a->count; i++) {
        if(a->cell[i]->type != LVAL_NUM) {
            lval_del(a);
            return lval_err("Can't operate on non-number");
        }
    }

    lval* x = lval_pop(a, 0);
    if((strcmp(op, "-") == 0 ) && a->count == 0) {
        x->num = -x->num;
    }

    while(a->count > 0) {
        lval* y = lval_pop(a, 0);

        if(strcmp(op, "+") == 0) {
            x->num += y->num;
        }

        if(strcmp(op, "-") == 0) {
            x->num -= y->num;
        }

        if(strcmp(op, "*") == 0) {
            x->num *= y->num;
        }

        if(strcmp(op, "/") == 0) {
            if(y->num == 0) {
                lval_del(x);
                lval_del(y);
                x = lval_err("Division by zero.");
                break;
            }
            x->num /= y->num;
        }
        lval_del(y);
    }

    lval_del(a);
    return x;
}

lval* lval_eval(lval* v);

lval* lval_eval_sexpr(lval* v) {
    for(int i = 0 ; i < v->count ; i++) {
        v->cell[i] = lval_eval(v->cell[i]);
    }

    for(int i = 0 ; i < v->count; i++) {
        if(v->cell[i]->type  == LVAL_ERR) {
            return lval_take(v, i);
        }
    }

    if(v->count == 0) {
        return lval_take(v, 0);
    }

    if(v->count == 1) {
        return lval_take(v, 0);
    }

    lval* f = lval_pop(v, 0);

    if(f->type != LVAL_SYM) {
        lval_del(f);
        lval_del(v);
        return lval_err("S-expression does not with symbol");
    }

    lval* result = buildin_op(v, f->sym);
    lval_del(f);
    return  result;
}


lval* lval_eval(lval* v) {
    if(v->type == LVAL_SEPR) {
        return lval_eval_sexpr(v);
    }
    return v;
}

int main() {
    // definition of number;
    mpc_parser_t* Number = mpc_new("number");
    mpc_parser_t* Symbol = mpc_new("symbol");
    mpc_parser_t* Expr = mpc_new("expr");
    mpc_parser_t* Sexpr = mpc_new("sexpr");
    mpc_parser_t* Lispy = mpc_new("lispy");

    mpca_lang(MPCA_LANG_DEFAULT,
              "                                                      \
                  number    : /-?[0-9]+/;                            \
                  symbol    : '+'|'-'|'*'|'/';                       \
                  sexpr     : '(' <expr>* ')';                       \
                  expr      : <number> | <symbol> | <sexpr>;         \
                  lispy     : /^/<expr>* /$/;                        \
              ",
              Number, Symbol, Sexpr, Expr, Lispy);
    puts("Lispy version 0.0.0.0.2");
    puts("Press Ctrl+c Exit\n");

    while(1) {
        char* input = readline("lispy> ");
        mpc_result_t r;
        if(mpc_parse("<stdin>", input, Lispy, &r)) {
            lval* x = lval_eval(lval_read(r.output));
            lval_println(x);
            lval_del(x);
            mpc_ast_delete(r.output);
        } else {
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }
        free(input);
    }
    mpc_cleanup(5, Number, Symbol, Sexpr, Expr, Lispy);
}