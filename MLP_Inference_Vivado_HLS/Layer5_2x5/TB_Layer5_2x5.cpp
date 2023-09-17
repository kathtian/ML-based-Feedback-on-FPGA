#include <stdio.h>
#include <stdlib.h>

#include "/home/ytian/MLP_ADC_DAC/Rev2/IP/Layer5_2x5/Layer5_2x5.h"

int main(void) {

  float a=1;
  float b=1;

  float bias1=1.1;
  float bias2=1.1;

  float a2=2;
  float b2=1;
  float *c1;
  float *c2;

  float arr1[1];
  float arr2[2];
  c1=arr1;
  c2=arr2;

  Layer5_2x5(c1,a,a,a,a,a,b,b,b,b,b,
		     c2,a2,a2,a2,a2,a2,b2,b2,b2,b2,b2,bias1,bias2);

  printf("Test successful\n, %f %f", *c1, *c2);
}
