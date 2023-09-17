#include <stdio.h>
#include <stdlib.h>

#include "Layer2_10x20.h"

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
  float bias6=1.1;
  float bias7=1.1;
  float bias8=1.1;
  float bias9=1.1;
  float bias10=1.1;


  float *c1;
  float *c2;
  float *c3;
  float *c4;
  float *c5;
  float *c6;
    float *c7;
    float *c8;
    float *c9;
    float *c10;

  float arr1[1];
  float arr2[2];
  float arr3[3];
  float arr4[4];
  float arr5[5];

  float arr6[1];
    float arr7[1];
    float arr8[1];
    float arr9[1];
    float arr10[1];

  c1=arr1;
  c2=arr2;
  c3=arr3;
  c4=arr4;
  c5=arr5;

  c6=arr6;
  c7=arr7;
  c8=arr8;
  c9=arr9;
  c10=arr10;

  Layer2_10x20(c1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,
		  b1,b1,b1,b1,b1,b1,b1,b1,b1,b1,b1,b1,b1,b1,b1,b1,b1,b1,b1,b1,
		      c2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,
			  c3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,
			  c4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,
			  c5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,
		      c6,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,
			  c7,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,
			  c8,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,
			  c9,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,
			  c10,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,
			  bias1,bias2,bias3,bias4,bias5,bias6,bias7,bias8,bias9,bias10);




  printf("Test successful\n, %f %f %f %f %f %f %f %f %f %f", *c1, *c2,*c3,*c4,*c5,*c6, *c7,*c8,*c9,*c10);
}
