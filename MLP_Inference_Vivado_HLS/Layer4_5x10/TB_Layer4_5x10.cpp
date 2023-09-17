#include <stdio.h>
#include <stdlib.h>

#include "Layer4_5x10.h"

int main(void) {

  float a1=1;
  float b1=1;
  float a2=2;
  float b2=2;
  float a3=3;
  float b3=3;
  float a4=4;
  float b4=4;
  float a5=5;
  float b5=5;


  float bias1=1.1;
  float bias2=1.1;
  float bias3=1.1;
  float bias4=1.1;
  float bias5=1.1;

  float *c1;
  float *c2;
  float *c3;
  float *c4;
  float *c5;

  float arr1[1];
  float arr2[2];
  float arr3[3];
  float arr4[4];
  float arr5[5];

  c1=arr1;
  c2=arr2;
  c3=arr3;
  c4=arr4;
  c5=arr5;

  Layer4_5x10(c1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,b1,b1,b1,b1,b1,b1,b1,b1,b1,b1,
		      c2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,
			  c3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,
			  c4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,
			  c5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,
			  bias1,bias2,bias3,bias4,bias5
  );



  printf("Test successful\n, %f %f %f %f %f", *c1, *c2,*c3,*c4,*c5);
}
