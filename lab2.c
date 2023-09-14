// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()
#include <math.h>
// user-defined header files
#include "mypcm.h"


// function prototypes
void run(asignal * inputsignal);


int main()
{
    asignal * inputsignal = (asignal *) malloc(sizeof(asignal));
    run(inputsignal);

    
    //call any other function here

    free(inputsignal);
	return 0;
}

void run(asignal * inputsignal) 
{
    int A;
    int omega;
    int sigma;
    int duration;
    int interval;
    int encoderbits;
    //scanf("%d",&A);
    scanf("%d %d %d %d %d %d",&A,&omega,&sigma,&duration,&interval,&encoderbits);
    inputsignal->A=A;
    inputsignal->duration=duration;
    inputsignal->sigma=sigma;
    inputsignal->omega=omega;

    int length= duration/interval +1 ;

    float* dynamicArray; // Declare a pointer to int
    int size = length;     // Define the size of the array

    dynamicArray = (float *)malloc(size * sizeof(float));

    int* pcmarray; // Declare a pointer to int
    int pcmarrsize = length+1;     // Define the size of the array

    pcmarray = (int*)malloc(pcmarrsize * sizeof(int));

    int* dsignal; // Declare a pointer to int
    int dsignal_size = (length)*encoderbits ;     // Define the size of the array

    dsignal= (int*)malloc(dsignal_size * sizeof(int));
    pcmarray[0]=length;

    int levels = pow(2, encoderbits);

    sampler(dynamicArray,interval,*inputsignal );
    quantizer(dynamicArray,pcmarray,levels,A);
    encoder(pcmarray,dsignal,encoderbits);
    free(dsignal);
    free(pcmarray);
}


