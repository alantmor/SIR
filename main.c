#include <stdio.h>
#include <stdlib.h>

#define BETA 0.005
#define GAMMA 0.025
#define N 10000
#define PERCS 0.2

#define H 0.1

/*Metodo range Kutta 4 ordem*/

float suceptivel(float s, float i);
float infectado(float s, float i);

float S[N],I[N],R[N];



int main()
{
    FILE *resultado;
    resultado=fopen("resultadoSIR.txt","w");
    if (!resultado) printf("Erro na abertura do arquivo.");

    float k1,k2,k3,k4;
    int i;
    fprintf(resultado,"%d %d %d\n",S[0],I[0],R[0]);
    S[0]=N*PERCS;
    I[0]=N*(1-PERCS);
    R[0]=0;

    for (i=1;i<N;i++)
    {
        k1=suceptivel(S[i-1],I[i-1]);
        k2=suceptivel((S[i-1]+H/2),(I[i-1]+H/2)*k1);
        k3=suceptivel((S[i-1]+H/2),(I[i-1]+H/2)*k2);
        k4=suceptivel((S[i-1]+H),(I[i-1]+H)*k1);
        S[i]=S[i-1]+((H/6)*(k1+2*k2+2*k3+k4));

        k1=infectado(S[i-1],I[0]);
        k2=infectado((S[i-1]+H/2),(I[i-1]+H/2)*k1);
        k3=infectado((S[i-1]+H/2),(I[i-1]+H/2)*k2);
        k4=infectado((S[i-1]+H),(I[i-1]+H)*k1);
        I[i]=I[i-1]+((H/6)*(k1+2*k2+2*k3+k4));

        R[i]= N - S[i] - I[i];
        fprintf(resultado,"%d %d %d\n",S[i],I[i],R[i]);
        printf("%d %d %d\n",S[i-1],I[i-1],R[i-1]);
    }

    fclose(resultado);
    return 0;
}

float suceptivel(float s, float i)
{
    float x;
    x=-BETA*s*i;

    return x;
}

float infectado(float s, float i)
{
    float x;
    x=BETA*s*i-GAMMA*i;

    return x;
}

