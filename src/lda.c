/* ========================================================
 *   Copyright (C) 2015 All rights reserved.
 *   
 *   filename : lda.c
 *   author   : ***
 *   date     : 2015-03-26
 *   info     : 
 * ======================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lda.h"

void help(char * argv[]) {
    fprintf(stderr, "Usage: \n");
    fprintf(stderr, "./%s -a <float> -b <float> -g0 <double> -g1 <double> -k <int> -n <int> -s <int> -d <string> -o <string>: \n\n", argv[0]);
    fprintf(stderr, "      -a  alpha     doc-K   paramenter  \n");
    fprintf(stderr, "      -b  beta      K-V     paramenter  \n");
    fprintf(stderr, "      -g0 gamma0    global topic param  \n");
    fprintf(stderr, "      -g1 gamma1    specil topic param  \n");
    fprintf(stderr, "      -k  topicx    tt-size             \n");
    fprintf(stderr, "      -n  niters    iteration num       \n");
    fprintf(stderr, "      -s  savestep  savestep            \n");
    fprintf(stderr, "      -d  input     input data file     \n");
    fprintf(stderr, "      -o  out_dir   output dir          \n");
}

int parse_command_line(ParamLda *p, int argc, char *argv[]) {
    int k = 50, n = 20, s = 10;
    double a = 0.05, b = 0.05, g0 = 0.5, g1 = 0.5;
    char *input = NULL;
    char *out_dir = "./";

    int i = 0;
    char * arg = NULL;

    if ((argc & 1) == 0){
        fprintf(stderr, "command line not well formatted\n");
        return -1;
    }

    while (i < argc) {
        arg = argv[i];
        if (0 == strcmp(arg,"-a")){
            a = atof(argv[++i]);
        }
        else if (0 == strcmp(arg,"-b")){
            b = atof(argv[++i]);
        }
        else if (0 == strcmp(arg,"-g0")){
            g0 = atof(argv[++i]);
        }
        else if (0 == strcmp(arg,"-g1")){
            g1 = atof(argv[++i]);
        }
        else if (0 == strcmp(arg,"-k")){
            k = atoi(argv[++i]);
        }
        else if (0 == strcmp(arg,"-n")){
            n = atoi(argv[++i]);
        }
        else if (0 == strcmp(arg,"-s")){
            s = atoi(argv[++i]);
        }
        else if (0 == strcmp(arg,"-d")){
            input = argv[++i];
        }
        else if (0 == strcmp(arg,"-o")){
            out_dir = argv[++i];
        }
        i += 1;
    }
    if (NULL == input) {
        fprintf(stderr,"no input data exit(-1)\n");
        return -1;
    }
    p->a        = a;
    p->b        = b;
    p->g0       = g0;
    p->g1       = g1;
    p->niters   = n;
    p->savestep = s;
    p->k        = k;
    p->in_file  = input;
    p->out_dir  = out_dir;

    fprintf(stderr, "alpha : %f\tbeta : %f\tniters : %d\ttopics : %d\tinput : %s\toutput : %s\n", \
            a, b, n, k, input, out_dir);

    return 0;
}

int main(int argc, char * argv[]) {
    ParamLda p;
    if (-1 == parse_command_line(&p, argc, argv)){
        help(argv);
        return -1;
    }
    fprintf(stderr,"command line parse done\n");
    Lda * lda = create_lda(p);
    srand(time(NULL));
    if (-1 == init_lda(lda)) {
        return -1;
    }
    fprintf(stderr,"load data done\n");
    fprintf(stderr,"D: %d V: %d T: %d\n", lda_d(lda), lda_v(lda), lda_t(lda));
    est_lda(lda);
    free_lda(lda);
    lda = NULL;
    return 0;
}
