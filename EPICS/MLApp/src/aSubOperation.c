#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <dbAccess.h>
#include <dbDefs.h>
#include <dbFldTypes.h>
#include <registryFunction.h>
#include <aSubRecord.h>
#include <waveformRecord.h>
#include <epicsExport.h>
#include <epicsTime.h>


static long ADCSnapShotParse(aSubRecord *pasub) 
{
	char *aptr;	
	int RAW_DATASIZE_BYTE=104000000;	 
	int SnapShot_POINTS=  13000000;
	float tempF;      
	float *fPtr;
	float *fPtrA;
	float *fPtrB;
	float *fPtrC;
	float *fPtrD;
	char *cPraw;
	unsigned char c1,c2;
	
	int i;
	int adcIndex;
	
	printf("--- Received all ADC data. --- \n");

	fPtrA=pasub->vala;
	fPtrB=pasub->valb;
	fPtrC=pasub->valc;
	fPtrD=pasub->vald;

	for(adcIndex==0;adcIndex<4;adcIndex++) {
		cPraw = pasub->a;
		cPraw=cPraw + (2*adcIndex);
		for(i=0;i<SnapShot_POINTS;i++) { 
			c1 = (unsigned char)(*cPraw);
			cPraw++;
			c2= (unsigned char)(*cPraw);
			tempF = (float)(c1*256+c2);
			if(tempF >= 8192.0) tempF = (16383.0-tempF)*(-3.0/16383.0);
			else tempF = tempF*(3.0/16383.0);	
			switch(adcIndex) {
				case 0: {*fPtrA = tempF; fPtrA++; break; }
				case 1: {*fPtrB = tempF; fPtrB++; break; }
				case 2: {*fPtrC = tempF; fPtrC++; break; }
				case 3: {*fPtrD = tempF; fPtrD++; break; }
			}
			cPraw=cPraw+7;
		}
	}
}
epicsRegisterFunction(ADCSnapShotParse);




