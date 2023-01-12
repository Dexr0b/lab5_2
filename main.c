#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 30

int main()
{
    char group[SIZE],name[SIZE],surname[SIZE];
    double x1,x2,y,delta,bin,**A;
    int steps,N;

    FILE* input=fopen("input.txt", "r");
    FILE* output=fopen("output.txt", "w");
    FILE* binary=fopen("binary.txt", "w+b");
    fscanf(input,"%lf %lf %d %lf", &x1, &x2, &steps, &delta);
    fgets(surname,SIZE, input);
    fgets(group,SIZE, input);
    fgets(name,SIZE, input);
    
    if (steps==0)
    {
        steps=((x2-x1)/delta)+1;
    }
    else if (delta==0)
    {
        delta=(x2-x1)/(steps-1);
    }
    fclose(input);

        fprintf(output,"\n******************************************");
        fprintf(output,"\n  N           X            F(X)           ");
        fprintf(output,"\n******************************************");
    fwrite(&steps, sizeof(int), 1, binary);
    
    for(int i=0; i<steps; i++)
    {
        y= -0.5*pow(x1-64,3)-3*pow(x1,2)+10;
        fprintf(output, "\n\t|%d|%.2lf\t|%.2lf\t|",i,x1,y);
        fwrite(&x1, sizeof(double), 1, binary);
        fwrite(&y, sizeof(double), 1, binary);
        x1+=delta;
    }
    
    fprintf(output,"\n%s %s %s", group, name, surname);
    fclose(output);
    fclose(binary);

    binary = fopen("binary.txt", "r+b");
    printf("\n|N|\t|X\t|\t|Y\t\t|");
    fread(&N, sizeof(int), 1, binary);

    A=(double**)malloc(3*sizeof(double*));
    for(int i=0; i<3; i++)
    {
        A[i]=(double*)malloc(N*sizeof(double));
    }

    for(int i=0; i<N; i++)
    {
        printf("\n|%d|", i);
        for(int j=1; j<3; j++)
        {
            fread(&bin, sizeof(double), 1, binary);
            A[j][i] = bin;
            printf("\t|%.2lf\t| ", A[j][i]);
        }
    }
    fclose(input);
    fclose(output);
    fclose(binary);
}
