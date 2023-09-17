#include <stdio.h>
#include <stdlib.h>

#include "Layer1_20x20.h"

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

    float *c11;
    float *c12;
    float *c13;
    float *c14;
    float *c15;
    float *c16;
      float *c17;
      float *c18;
      float *c19;
      float *c20;

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

    float arr11[1];
      float arr12[2];
      float arr13[3];
      float arr14[4];
      float arr15[5];

      float arr16[1];
        float arr17[1];
        float arr18[1];
        float arr19[1];
        float arr20[1];

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
   float bias11=1.1;
   float bias12=1.1;
   float bias13=1.1;
   float bias14=1.1;
   float bias15=1.1;
   float bias16=1.1;
   float bias17=1.1;
   float bias18=1.1;
   float bias19=1.1;
   float bias20=1.1;




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

  c11=arr11;
  c12=arr12;
  c13=arr13;
  c14=arr14;
  c15=arr15;

  c16=arr16;
  c17=arr17;
  c18=arr18;
  c19=arr19;
  c20=arr20;

  Layer1_20x20(c1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,
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

			  c11,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,a1,
		      c12,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,
			  c13,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,
			  c14,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,
			  c15,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,
		      c16,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,a2,
			  c17,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,a3,
			  c18,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,
			  c19,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,a4,
			  c20,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,a5,
			  bias1,bias2,bias3,bias4,bias5,bias6,bias7,bias8,bias9,bias10,
			  bias11,bias12,bias13,bias14,bias15,bias16,bias17,bias18,bias19,bias20
  );





  printf("Test successful\n, %f %f %f %f %f %f %f %f %f %f", *c1, *c2,*c3,*c4,*c5,*c6, *c7,*c8,*c9,*c10);
}
