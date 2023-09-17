#include "/home/ytian/MLP_ADC_DAC/Rev2/IP/Layer5_2x5/Layer5_2x5.h"

void activation(float din, float *dout) {
	if(din <= -10) *dout = -10.0;
	else if(din >= 10) *dout = 10.0;
	else *dout = din;
}

void v5xv5(float *sum, float a1,float a2,float a3,float a4,float a5,
					 float b1,float b2,float b3,float b4,float b5, float bias)
{
float t1=a1*b1;
float t2=a2*b2;
float t3=a3*b3;
float t4=a4*b4;
float t5=a5*b5;
float t12,t34;
float t1234,t1_5;
t12=t1+t2;
t34=t3+t4;
t1234=t12+t34;
t1_5=t1234+t5;
activation((t1_5+bias), sum);
return;
}

void Layer5_2x5(float *sum1, float a1,float a2,float a3,float a4,float a5,  float b1,float b2,float b3,float b4,float b5,
		        float *sum2, float a6,float a7,float a8,float a9,float a10, float b6,float b7,float b8,float b9,float b10,
				float bias1, float bias2
				) {

	v5xv5(sum1,a1,a2,a3,a4,a5, b1,b2,b3,b4,b5,bias1);
	v5xv5(sum2,a6,a7,a8,a9,a10,b6,b7,b8,b9,b10,bias2);
	return;
}
