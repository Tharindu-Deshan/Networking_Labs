// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
//Add any necessary headers here
#include <math.h>

// user-defined header files
#include "mypcm.h" // do not modify this file

// put your function prototypes for additional helper functions below:

//float max_A(float *samples,asignal asignal2 ,int interval){
//    float x =INT_MIN;
//    for(int i=0; i<asignal2.duration/ interval ;i++){
//        if(x<samples[i]){
//            x=samples[i];
//        }
//    }
//    return x;
//}
//float min_A(float *samples,asignal asignal3 ,int interval){
//    float x =INT_MAX;
//    for(int i=0; i<asignal3.duration/ interval ;i++){
//        if(x>samples[i]){
//            x=samples[i];
//        }
//    }
//    return x;
//}



float analog_signal_generator(asignal signal, int t)
{
    float value ;
    if(t<0){
        return 0;
    }
    //printf("Analog Signal Gen\n");
    value = signal.A* sin(signal.omega*t +signal.sigma);
    return value;

}
void sampler(float *samples, int interval, asignal signal)
{
    int y=0;
    for(int i=0;i<=signal.duration;i=i+interval){
        samples[y] = analog_signal_generator(signal,i);
        y++;
    }
}

void quantizer(float *samples, int *pcmpulses, int levels, float A)
{
    int length=  pcmpulses[0];
    for(int i=1;i<length+1;i++){
        
        int y=floor(((samples[i-1]+A)/(2.0*A))*(levels * 1.0));
      
        pcmpulses[i]=y;
        
    }
}


void encoder(int *pcmpulses, int *dsignal, int encoderbits)
{
    int z =0;

    int x = pcmpulses[0];
    for(int i=1;i<=x;i++){
        int y = pcmpulses[i];
        int arr [encoderbits];

        for(int j=0;j<encoderbits;j++){
              arr[j]=y%2;
              y=y/2;
        }
        for(int i=encoderbits-1;i>=0;i--){
            dsignal[z]=arr[i];
            z++;
        }
    }
    for(int u=0;u<x*encoderbits;u++){
        printf("%d",dsignal[u]);
    }
}