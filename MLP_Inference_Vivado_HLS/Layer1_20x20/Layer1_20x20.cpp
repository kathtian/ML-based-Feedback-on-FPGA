#include "Layer1_20x20.h"

void activation(float din,float *dout) {
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


void Layer1_20x20(float *sum1, float a1_1,float a1_2,float a1_3,float a1_4,float a1_5,float a1_6,float a1_7,float a1_8,float a1_9,float a1_10,
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

	float *sum11,  float a11_1,float a11_2,float a11_3,float a11_4,float a11_5,float a11_6,float a11_7,float a11_8,float a11_9,float a11_10,
				  float a11_11,float a11_12,float a11_13,float a11_14,float a11_15,float a11_16,float a11_17,float a11_18,float a11_19,float a11_20,
	float *sum12,  float a12_1,float a12_2,float a12_3,float a12_4,float a12_5,float a12_6,float a12_7,float a12_8,float a12_9,float a12_10,
				  float a12_11,float a12_12,float a12_13,float a12_14,float a12_15,float a12_16,float a12_17,float a12_18,float a12_19,float a12_20,
	float *sum13,  float a13_1,float a13_2,float a13_3,float a13_4,float a13_5,float a13_6,float a13_7,float a13_8,float a13_9,float a13_10,
				  float a13_11,float a13_12,float a13_13,float a13_14,float a13_15,float a13_16,float a13_17,float a13_18,float a13_19,float a13_20,
	float *sum14,  float a14_1,float a14_2,float a14_3,float a14_4,float a14_5,float a14_6,float a14_7,float a14_8,float a14_9,float a14_10,
	  	  	      float a14_11,float a14_12,float a14_13,float a14_14,float a14_15,float a14_16,float a14_17,float a14_18,float a14_19,float a14_20,
	float *sum15,  float a15_1,float a15_2,float a15_3,float a15_4,float a15_5,float a15_6,float a15_7,float a15_8,float a15_9,float a15_10,
	              float a15_11,float a15_12,float a15_13,float a15_14,float a15_15,float a15_16,float a15_17,float a15_18,float a15_19,float a15_20,
	float *sum16,  float a16_1,float a16_2,float a16_3,float a16_4,float a16_5,float a16_6,float a16_7,float a16_8,float a16_9,float a16_10,
	              float a16_11,float a16_12,float a16_13,float a16_14,float a16_15,float a16_16,float a16_17,float a16_18,float a16_19,float a16_20,
	float *sum17,  float a17_1,float a17_2,float a17_3,float a17_4,float a17_5,float a17_6,float a17_7,float a17_8,float a17_9,float a17_10,
	              float a17_11,float a17_12,float a17_13,float a17_14,float a17_15,float a17_16,float a17_17,float a17_18,float a17_19,float a17_20,
	float *sum18,  float a18_1,float a18_2,float a18_3,float a18_4,float a18_5,float a18_6,float a18_7,float a18_8,float a18_9,float a18_10,
				  float a18_11,float a18_12,float a18_13,float a18_14,float a18_15,float a18_16,float a18_17,float a18_18,float a18_19,float a18_20,
	float *sum19,  float a19_1,float a19_2,float a19_3,float a19_4,float a19_5,float a19_6,float a19_7,float a19_8,float a19_9,float a19_10,
				  float a19_11,float a19_12,float a19_13,float a19_14,float a19_15,float a19_16,float a19_17,float a19_18,float a19_19,float a19_20,
	float *sum20,  float a20_1,float a20_2,float a20_3,float a20_4,float a20_5,float a20_6,float a20_7,float a20_8,float a20_9,float a20_10,
			      float a20_11,float a20_12,float a20_13,float a20_14,float a20_15,float a20_16,float a20_17,float a20_18,float a20_19,float a20_20,

				  float bias1,float bias2,float bias3,float bias4,float bias5,float bias6,float bias7,float bias8,float bias9,float bias10,
				  float bias11,float bias12,float bias13,float bias14,float bias15,float bias16,float bias17,float bias18,float bias19,float bias20) {


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


	v20xv20(sum11,a11_1,a11_2,a11_3,a11_4,a11_5,a11_6,a11_7,a11_8,a11_9,a11_10,a11_11,a11_12,a11_13,a11_14,a11_15,a11_16,a11_17,a11_18,a11_19,a11_20,
			b1_1,b1_2,b1_3,b1_4,b1_5,b1_6,b1_7,b1_8,b1_9,b1_10,b1_11,b1_12,b1_13,b1_14,b1_15,b1_16,b1_17,b1_18,b1_19,b1_20,bias11);

	v20xv20(sum12,a12_1,a12_2,a12_3,a12_4,a12_5,a12_6,a12_7,a12_8,a12_9,a12_10,a12_11,a12_12,a12_13,a12_14,a12_15,a12_16,a12_17,a12_18,a12_19,a12_20,
				b1_1,b1_2,b1_3,b1_4,b1_5,b1_6,b1_7,b1_8,b1_9,b1_10,b1_11,b1_12,b1_13,b1_14,b1_15,b1_16,b1_17,b1_18,b1_19,b1_20,bias12);

	v20xv20(sum13,a13_1,a13_2,a13_3,a13_4,a13_5,a13_6,a13_7,a13_8,a13_9,a13_10,a13_11,a13_12,a13_13,a13_14,a13_15,a13_16,a13_17,a13_18,a13_19,a13_20,
			b1_1,b1_2,b1_3,b1_4,b1_5,b1_6,b1_7,b1_8,b1_9,b1_10,b1_11,b1_12,b1_13,b1_14,b1_15,b1_16,b1_17,b1_18,b1_19,b1_20,bias13);

	v20xv20(sum14,a14_1,a14_2,a14_3,a14_4,a14_5,a14_6,a14_7,a14_8,a14_9,a14_10,a14_11,a14_12,a14_13,a14_14,a14_15,a14_16,a14_17,a14_18,a14_19,a14_20,
			b1_1,b1_2,b1_3,b1_4,b1_5,b1_6,b1_7,b1_8,b1_9,b1_10,b1_11,b1_12,b1_13,b1_14,b1_15,b1_16,b1_17,b1_18,b1_19,b1_20,bias14);

	v20xv20(sum15,a15_1,a15_2,a15_3,a15_4,a15_5,a15_6,a15_7,a15_8,a15_9,a15_10,a15_11,a15_12,a15_13,a15_14,a15_15,a15_16,a15_17,a15_18,a15_19,a15_20,
			b1_1,b1_2,b1_3,b1_4,b1_5,b1_6,b1_7,b1_8,b1_9,b1_10,b1_11,b1_12,b1_13,b1_14,b1_15,b1_16,b1_17,b1_18,b1_19,b1_20,bias15);

	v20xv20(sum16,a16_1,a16_2,a16_3,a16_4,a16_5,a16_6,a16_7,a16_8,a16_9,a16_10,a16_11,a16_12,a16_13,a16_14,a16_15,a16_16,a16_17,a16_18,a16_19,a16_20,
			b1_1,b1_2,b1_3,b1_4,b1_5,b1_6,b1_7,b1_8,b1_9,b1_10,b1_11,b1_12,b1_13,b1_14,b1_15,b1_16,b1_17,b1_18,b1_19,b1_20,bias16);

	v20xv20(sum17,a17_1,a17_2,a17_3,a17_4,a17_5,a17_6,a17_7,a17_8,a17_9,a17_10,a17_11,a17_12,a17_13,a17_14,a17_15,a17_16,a17_17,a17_18,a17_19,a17_20,
			b1_1,b1_2,b1_3,b1_4,b1_5,b1_6,b1_7,b1_8,b1_9,b1_10,b1_11,b1_12,b1_13,b1_14,b1_15,b1_16,b1_17,b1_18,b1_19,b1_20,bias17);

	v20xv20(sum18,a18_1,a18_2,a18_3,a18_4,a18_5,a18_6,a18_7,a18_8,a18_9,a18_10,a18_11,a18_12,a18_13,a18_14,a18_15,a18_16,a18_17,a18_18,a18_19,a18_20,
			b1_1,b1_2,b1_3,b1_4,b1_5,b1_6,b1_7,b1_8,b1_9,b1_10,b1_11,b1_12,b1_13,b1_14,b1_15,b1_16,b1_17,b1_18,b1_19,b1_20,bias18);

	v20xv20(sum19,a19_1,a19_2,a19_3,a19_4,a19_5,a19_6,a19_7,a19_8,a19_9,a19_10,a19_11,a19_12,a19_13,a19_14,a19_15,a19_16,a19_17,a19_18,a19_19,a19_20,
			b1_1,b1_2,b1_3,b1_4,b1_5,b1_6,b1_7,b1_8,b1_9,b1_10,b1_11,b1_12,b1_13,b1_14,b1_15,b1_16,b1_17,b1_18,b1_19,b1_20,bias19);

	v20xv20(sum20,a20_1,a20_2,a20_3,a20_4,a20_5,a20_6,a20_7,a20_8,a20_9,a20_10,a20_11,a20_12,a20_13,a20_14,a20_15,a20_16,a20_17,a20_18,a20_19,a20_20,
			b1_1,b1_2,b1_3,b1_4,b1_5,b1_6,b1_7,b1_8,b1_9,b1_10,b1_11,b1_12,b1_13,b1_14,b1_15,b1_16,b1_17,b1_18,b1_19,b1_20,bias20);

	return;
}
