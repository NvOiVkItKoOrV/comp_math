#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#define X_0 1

#define MF(x) my_func(x)


double a = 4.0 / 3.0;
double b = 1.0 / 3.0;
double c = 3.0 / 2.0;
double d = 3.0 / 5.0;
double e = 1.0 / 10.0;


struct ptrs2data
{
    FILE *fp1;
    FILE *fp2;
    FILE *fp3;
    FILE *fp4;
    FILE *fp5;
} ptrs;


void ctor(struct ptrs2data *ptrs)
{
    ptrs->fp1 = fopen("1data.txt", "w");
    ptrs->fp2 = fopen("2data.txt", "w");
    ptrs->fp3 = fopen("3data.txt", "w");
    ptrs->fp4 = fopen("4data.txt", "w");
    ptrs->fp5 = fopen("5data.txt", "w");
}


void dtor(struct ptrs2data *ptrs)
{   
    fclose(ptrs->fp1);
    fclose(ptrs->fp2);
    fclose(ptrs->fp3);
    fclose(ptrs->fp4);
    fclose(ptrs->fp5);
}


double my_func(double x)
{
    return pow(x + 3, 0.5);
}


void make_data(struct ptrs2data ptrs)
{
    double fx_0 = 0.5 * pow(X_0 + 3, -0.5);

    for(int x = 1; x < 22; x++)
    {
        double h     = pow(2, 1 - x);
        double der_1 = (MF(X_0 + h) - MF(X_0))     / h;
        double der_2 = (MF(X_0)     - MF(X_0 - h)) / h;
        double der_3 = (MF(X_0 + h) - MF(X_0 - h)) / (2 * h);

        double der_4 = a * ((MF(X_0 + h)     - MF(X_0 - h))     / (2 * h)) -
                       b * ((MF(X_0 + 2 * h) - MF(X_0 - 2 * h)) / (4 * h));

        double der_5 = c * ((MF(X_0 + h)     - MF(X_0 - h))     / (2 * h)) -
                       d * ((MF(X_0 + 2 * h) - MF(X_0 - 2 * h)) / (4 * h)) +
                       e * ((MF(X_0 + 3 * h) - MF(X_0 - 3 * h)) / (6 * h));

        fprintf(ptrs.fp1, "%f %.23f\n", h, fabs(der_1 - fx_0));
        fprintf(ptrs.fp2, "%f %.23f\n", h, fabs(der_2 - fx_0));
        fprintf(ptrs.fp3, "%f %.23f\n", h, fabs(der_3 - fx_0));
        fprintf(ptrs.fp4, "%f %.23f\n", h, fabs(der_4 - fx_0));
        fprintf(ptrs.fp5, "%f %.23f\n", h, fabs(der_5 - fx_0));
    }
}


int main()
{
    ctor(&ptrs);

    make_data(ptrs);

    dtor(&ptrs);

    FILE *gnuplot_pipe = popen("./plot.pgi", "w");
    fclose(gnuplot_pipe);

    return 0;
}