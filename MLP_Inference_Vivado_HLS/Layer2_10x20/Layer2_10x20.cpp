#include "Layer2_10x20.h"

void activation(float din, float *dout) {
	if(din > 0) *dout = din;
	else *dout = 0;
}

void v20xv20(float *sum, float a1,float a2,float a3,float a4,float a5,float a6,float a7,float a8,float a9,float a10,
						 float a11,float a12,float a13,float a14,float a15,float a16,float a17,float a18,float a19,float a20,
					 float b1,float b2,float b3,float b4,float b5,float b6,float b7,float b8,float b9,float b10,
					 float b11,float b12,float b13,float b14,float b15,float b16,float b17,float b18,float b19,float b20,float bias)
{
float temp=0;
float tableA[20];
float tableB[20];

for(int i=0;i<20;i++) {
	if(i==0) {tableA[0]=a1;tableB[0]=b1;}
	else if(i==1) {tableA[1]=a2;tableB[1]=b2;}
	else if(i==2) {tableA[2]=a3;tableB[2]=b3;}
	else if(i==3) {tableA[3]=a4;tableB[3]=b4;}
	else if(i==4) {tableA[4]=a5;tableB[4]=b5;}
	else if(i==5) {tableA[5]=a6;tableB[5]=b6;}
	else if(i==6) {tableA[6]=a7;tableB[6]=b7;}
	else if(i==7) {tableA[7]=a8;tableB[7]=b8;}
	else if(i==8) {tableA[8]=a9;tableB[8]=b9;}
	else if(i==9) {tableA[9]=a10;tableB[9]=b10;}
	else if(i==10) {tableA[10]=a11;tableB[10]=b11;}
	else if(i==11) {tableA[11]=a12;tableB[11]=b12;}
	else if(i==12) {tableA[12]=a13;tableB[12]=b13;}
	else if(i==13) {tableA[13]=a14;tableB[13]=b14;}
	else if(i==14) {tableA[14]=a15;tableB[14]=b15;}
	else if(i==15) {tableA[15]=a16;tableB[15]=b16;}
	else if(i==16) {tableA[16]=a17;tableB[16]=b17;}
	else if(i==17) {tableA[17]=a18;tableB[17]=b18;}
	else if(i==18) {tableA[18]=a19;tableB[18]=b19;}
	else {tableA[19]=a20;tableB[19]=b20;}
}

for(int i=0;i<20;i++) temp += tableA[i]*tableB[i];

activation((temp+bias), sum);
return;
}


void Layer2_10x20(float *sum1, float a1_1,float a1_2,float a1_3,float a1_4,float a1_5,float a1_6,float a1_7,float a1_8,float a1_9,float a1_10,
							   float a1_11,float a1_12,float a1_13,float a1_14,float a1_15,float a1_16,float a1_17,float a1_18,float a1_19,float a1_20,
		                       float b1_1,float b1_2,float b1_3,float b1_4,float b1_5,float b1_6,float b1_7,float b1_8,float b1_9,float b1_10,
							   float b1_11,float b1_12,float b1_13,float b1_14,float b1_15,float b1_16,float b1_17,float b1_18,float b1_19,float b1_20,

				float *sum2,  float a2_1,float a2_2,float a2_3,float a2_4,float a2_5,float a2_6,float a2_7,float a2_8,float a2_9,float a2_10,
							  float a2_11,float a2_12,float a2_13,float a2_14,float a2_15,float a2_16,float a2_17,float a2_18,float a2_19,float a2_20,
				float *sum3,  float a3_1,float a3_2,float a3_3,float a3_4,float a3_5,float a3_6,float a3_7,float a3_8,float a3_9,float a3_10,
							  float a3_11,float a3_12,float a3_13,float a3_14,float a3_15,float a3_16,float a3_17,float a3_18,float a3_19,float a3_20,
				float *sum4,  float a4_1,float a4_2,float a4_3,float a4_4,float a4_5,float a4_6,float a4_7,float a4_8,float a4_9,float a4_10,
				  	  	      float a4_11,float a4_12,float a4_13,float a4_14,float a4_15,float a4_16,float a4_17,float a4_18,float a4_19,float a4_20,
				float *sum5,  float a5_1,float a5_2,float a5_3,float a5_4,float a5_5,float a5_6,float a5_7,float a5_8,float a5_9,float a5_10,
				              float a5_11,float a5_12,float a5_13,float a5_14,float a5_15,float a5_16,float a5_17,float a5_18,float a5_19,float a5_20,
				float *sum6,  float a6_1,float a6_2,float a6_3,float a6_4,float a6_5,float a6_6,float a6_7,float a6_8,float a6_9,float a6_10,
				              float a6_11,float a6_12,float a6_13,float a6_14,float a6_15,float a6_16,float a6_17,float a6_18,float a6_19,float a6_20,
				float *sum7,  float a7_1,float a7_2,float a7_3,float a7_4,float a7_5,float a7_6,float a7_7,float a7_8,float a7_9,float a7_10,
				              float a7_11,float a7_12,float a7_13,float a7_14,float a7_15,float a7_16,float a7_17,float a7_18,float a7_19,float a7_20,
				float *sum8,  float a8_1,float a8_2,float a8_3,float a8_4,float a8_5,float a8_6,float a8_7,float a8_8,float a8_9,float a8_10,
							  float a8_11,float a8_12,float a8_13,float a8_14,float a8_15,float a8_16,float a8_17,float a8_18,float a8_19,float a8_20,
				float *sum9,  float a9_1,float a9_2,float a9_3,float a9_4,float a9_5,float a9_6,float a9_7,float a9_8,float a9_9,float a9_10,
							  float a9_11,float a9_12,float a9_13,float a9_14,float a9_15,float a9_16,float a9_17,float a9_18,float a9_19,float a9_20,
				float *sum10,  float a10_1,float a10_2,float a10_3,float a10_4,float a10_5,float a10_6,float a10_7,float a10_8,float a10_9,float a10_10,
						      float a10_11,float a10_12,float a10_13,float a10_14,float a10_15,float a10_16,float a10_17,float a10_18,float a10_19,float a10_20,

							  float bias1,float bias2,float bias3,float bias4,float bias5,float bias6,float bias7,float bias8,float bias9,float bias10) {


	v20xv20(sum1,a1_1,a1_2,a1_3,a1_4,a1_5,a1_6,a1_7,a1_8,a1_9,a1_10,a1_11,a1_12,a1_13,a1_14,a1_15,a1_16,a1_17,a1_18,a1_19,a1_20,
			b1_1,b1_2,b1_3,b1_4,b1_5,b1_6,b1_7,b1_8,b1_9,b1_10,b1_11,b1_12,b1_13,b1_14,b1_15,b1_16,b1_17,b1_18,b1_19,b1_20,bias1);

	v20xv20(sum2,a2_1,a2_2,a2_3,a2_4,a2_5,a2_6,a2_7,a2_8,a2_9,a2_10,a2_11,a2_12,a2_13,a2_14,a2_15,a2_16,a2_17,a2_18,a2_19,a2_20,
				b1_1,b1_2,b1_3,b1_4,b1_5,b1_6,b1_7,b1_8,b1_9,b1_10,b1_11,b1_12,b1_13,b1_14,b1_15,b1_16,b1_17,b1_18,b1_19,b1_20,bias2);

	v20xv20(sum3,a3_1,a3_2,a3_3,a3_4,a3_5,a3_6,a3_7,a3_8,a3_9,a3_10,a3_11,a3_12,a3_13,a3_14,a3_15,a3_16,a3_17,a3_18,a3_19,a3_20,
			b1_1,b1_2,b1_3,b1_4,b1_5,b1_6,b1_7,b1_8,b1_9,b1_10,b1_11,b1_12,b1_13,b1_14,b1_15,b1_16,b1_17,b1_18,b1_19,b1_20,bias3);

	v20xv20(sum4,a4_1,a4_2,a4_3,a4_4,a4_5,a4_6,a4_7,a4_8,a4_9,a4_10,a4_11,a4_12,a4_13,a4_14,a4_15,a4_16,a4_17,a4_18,a4_19,a4_20,
			b1_1,b1_2,b1_3,b1_4,b1_5,b1_6,b1_7,b1_8,b1_9,b1_10,b1_11,b1_12,b1_13,b1_14,b1_15,b1_16,b1_17,b1_18,b1_19,b1_20,bias4);

	v20xv20(sum5,a5_1,a5_2,a5_3,a5_4,a5_5,a5_6,a5_7,a5_8,a5_9,a5_10,a5_11,a5_12,a5_13,a5_14,a5_15,a5_16,a5_17,a5_18,a5_19,a5_20,
			b1_1,b1_2,b1_3,b1_4,b1_5,b1_6,b1_7,b1_8,b1_9,b1_10,b1_11,b1_12,b1_13,b1_14,b1_15,b1_16,b1_17,b1_18,b1_19,b1_20,bias5);

	v20xv20(sum6,a6_1,a6_2,a6_3,a6_4,a6_5,a6_6,a6_7,a6_8,a6_9,a6_10,a6_11,a6_12,a6_13,a6_14,a6_15,a6_16,a6_17,a6_18,a6_19,a6_20,
			b1_1,b1_2,b1_3,b1_4,b1_5,b1_6,b1_7,b1_8,b1_9,b1_10,b1_11,b1_12,b1_13,b1_14,b1_15,b1_16,b1_17,b1_18,b1_19,b1_20,bias6);

	v20xv20(sum7,a7_1,a7_2,a7_3,a7_4,a7_5,a7_6,a7_7,a7_8,a7_9,a7_10,a7_11,a7_12,a7_13,a7_14,a7_15,a7_16,a7_17,a7_18,a7_19,a7_20,
			b1_1,b1_2,b1_3,b1_4,b1_5,b1_6,b1_7,b1_8,b1_9,b1_10,b1_11,b1_12,b1_13,b1_14,b1_15,b1_16,b1_17,b1_18,b1_19,b1_20,bias7);

	v20xv20(sum8,a8_1,a8_2,a8_3,a8_4,a8_5,a8_6,a8_7,a8_8,a8_9,a8_10,a8_11,a8_12,a8_13,a8_14,a8_15,a8_16,a8_17,a8_18,a8_19,a8_20,
			b1_1,b1_2,b1_3,b1_4,b1_5,b1_6,b1_7,b1_8,b1_9,b1_10,b1_11,b1_12,b1_13,b1_14,b1_15,b1_16,b1_17,b1_18,b1_19,b1_20,bias8);

	v20xv20(sum9,a9_1,a9_2,a9_3,a9_4,a9_5,a9_6,a9_7,a9_8,a9_9,a9_10,a9_11,a9_12,a9_13,a9_14,a9_15,a9_16,a9_17,a9_18,a9_19,a9_20,
			b1_1,b1_2,b1_3,b1_4,b1_5,b1_6,b1_7,b1_8,b1_9,b1_10,b1_11,b1_12,b1_13,b1_14,b1_15,b1_16,b1_17,b1_18,b1_19,b1_20,bias9);

	v20xv20(sum10,a10_1,a10_2,a10_3,a10_4,a10_5,a10_6,a10_7,a10_8,a10_9,a10_10,a10_11,a10_12,a10_13,a10_14,a10_15,a10_16,a10_17,a10_18,a10_19,a10_20,
			b1_1,b1_2,b1_3,b1_4,b1_5,b1_6,b1_7,b1_8,b1_9,b1_10,b1_11,b1_12,b1_13,b1_14,b1_15,b1_16,b1_17,b1_18,b1_19,b1_20,bias10);


	return;
}

void v20xv20_old(float *sum, float a1,float a2,float a3,float a4,float a5,float a6,float a7,float a8,float a9,float a10,
						 float a11,float a12,float a13,float a14,float a15,float a16,float a17,float a18,float a19,float a20,
					 float b1,float b2,float b3,float b4,float b5,float b6,float b7,float b8,float b9,float b10,
					 float b11,float b12,float b13,float b14,float b15,float b16,float b17,float b18,float b19,float b20,float bias)
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

float t11=a11*b11;
float t12=a12*b12;
float t13=a13*b13;
float t14=a14*b14;
float t15=a15*b15;
float t16=a16*b16;
float t17=a17*b17;
float t18=a18*b18;
float t19=a19*b19;
float t20=a20*b20;


float t1_2=t1+t2;
float t3_4=t3+t4;
float t5_6=t5+t6;
float t7_8=t7+t8;
float t9_10=t9+t10;

float t1234=t1_2+t3_4;
float t5678=t5_6+t7_8;
float t1_8=t1234+t5678;
float t1_10=t1_8+t9_10;

float t1112=t11+t12;
float t1314=t13+t14;
float t1516=t15+t16;
float t1718=t17+t18;
float t19_20=t19+t20;

float t11_14=t1112+t1314;
float t15_18=t1516+t1718;
float t11_18=t11_14+t15_18;
float t11_20=t11_18+t19_20;

float t1_20=t1_10+t11_20;

activation((t1_20+bias), sum);
return;
}
