#include <mpc.h>
#include "utils/utils.h"

void match_all_a_b() {
    mpc_parser_t* AB = mpc_new("ab");

    mpca_lang(MPCA_LANG_DEFAULT,
              "ab : /'a'['a''b']*/ | /'b'['a''b']*/", AB);

    puts("match a b version 0.0.0.0.2");
    puts("Press Ctrl+c Exit\n");

    while(1) {
        char* input = readline("ab>");
        mpc_result_t r;

        if(mpc_parse("<stdin>", input, AB, &r)) {
            mpc_ast_print(r.output);
            mpc_ast_delete(r.output);
        } else {
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
            puts("are not all ab");
        }
        free(input);
    }
    mpc_cleanup(1, AB);
}

int main() {
    match_all_a_b();
    return 0;
}