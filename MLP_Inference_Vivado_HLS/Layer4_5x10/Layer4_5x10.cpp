#include "Layer4_5x10.h"

void activation(float din, float *dout) {
	if(din > 0) *dout = din;
	else *dout = 0;
}

void v10xv10(float *sum, float a1,float a2,float a3,float a4,float a5,float a6,float a7,float a8,float a9,float a10,
					 float b1,float b2,float b3,float b4,float b5,float b6,float b7,float b8,float b9,float b10, float bias)
{
float t1=a1*b1;
float t2=a2*b2;
float t3=a3*b3;
float t4=a4*b4;
float t5=a5*b5;
float t6=a6*b6;
float t7=a7*b7;
float t8=a8*b8;
float t9=a9*b9;
float t10=a10*b10;

float t12=t1+t2;
float t34=t3+t4;
float t56=t5+t6;
float t78=t7+t8;
float t9_10=t9+t10;

float t1234=t12+t34;
float t5678=t56+t78;
float t1_8=t1234+t5678;
float t1_10=t1_8+t9_10;


activation((t1_10+bias), sum);
return;
}

void Layer4_5x10(float *sum1, float a1_1,float a1_2,float a1_3,float a1_4,float a1_5,float a1_6,float a1_7,float a1_8,float a1_9,float a1_10,
		                      float b1_1,float b1_2,float b1_3,float b1_4,float b1_5,float b1_6,float b1_7,float b1_8,float b1_9,float b1_10,
				float *sum2,  float a2_1,float a2_2,float a2_3,float a2_4,float a2_5,float a2_6,float a2_7,float a2_8,float a2_9,float a2_10,
				float *sum3,  float a3_1,float a3_2,float a3_3,float a3_4,float a3_5,float a3_6,float a3_7,float a3_8,float a3_9,float a3_10,
				float *sum4,  float a4_1,float a4_2,float a4_3,float a4_4,float a4_5,float a4_6,float a4_7,float a4_8,float a4_9,float a4_10,
				float *sum5,  float a5_1,float a5_2,float a5_3,float a5_4,float a5_5,float a5_6,float a5_7,float a5_8,float a5_9,float a5_10,

				float bias1,float bias2,float bias3,float bias4,float bias5
) {


	v10xv10(sum1,a1_1,a1_2,a1_3,a1_4,a1_5,a1_6,a1_7,a1_8,a1_9,a1_10,b1_1,b1_2,b1_3,b1_4,b1_5,b1_6,b1_7,b1_8,b1_9,b1_10,bias1);
	v10xv10(sum2,a2_1,a2_2,a2_3,a2_4,a2_5,a2_6,a2_7,a2_8,a2_9,a2_10,b1_1,b1_2,b1_3,b1_4,b1_5,b1_6,b1_7,b1_8,b1_9,b1_10,bias2);
	v10xv10(sum3,a3_1,a3_2,a3_3,a3_4,a3_5,a3_6,a3_7,a3_8,a3_9,a3_10,b1_1,b1_2,b1_3,b1_4,b1_5,b1_6,b1_7,b1_8,b1_9,b1_10,bias3);
	v10xv10(sum4,a4_1,a4_2,a4_3,a4_4,a4_5,a4_6,a4_7,a4_8,a4_9,a4_10,b1_1,b1_2,b1_3,b1_4,b1_5,b1_6,b1_7,b1_8,b1_9,b1_10,bias4);
	v10xv10(sum5,a5_1,a5_2,a5_3,a5_4,a5_5,a5_6,a5_7,a5_8,a5_9,a5_10,b1_1,b1_2,b1_3,b1_4,b1_5,b1_6,b1_7,b1_8,b1_9,b1_10,bias5);

	return;
}
