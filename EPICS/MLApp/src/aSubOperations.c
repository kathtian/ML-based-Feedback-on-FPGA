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

/* ADC data process: little-big indian change, high-low word change */
static long subADCWfProc(aSubRecord *pasub)
{
	double *aPtr;
	long *bPtr, *cPtr;
	float *aOutPtr;
	long i,wfLength,wfReadLength;
	short tempS1,tempS2;
	float tempF;
	aPtr = (double *)pasub->a;
	bPtr = (short *)pasub->b;
	cPtr = (short *)pasub->c;
	aOutPtr = (float *)pasub->vala;	
	wfReadLength = *bPtr;
	wfLength= *cPtr; 	
	for(i=0;i<wfLength;i++) {
		if(i< wfReadLength) {
		//read waveform	
	   		if( ((int)(i/2)) == ((int)((i+1)/2)))  { 
			//even word: 
			tempS1 = (short)(*aPtr);
			tempS2 = (tempS1&0x00FF)*256+((tempS1&0xFF00)>>8);		
			tempF = tempS2/3276.6;
			aPtr++;
			} else {
			tempS1 = (short)(*aPtr);
			tempS2 = (tempS1&0x00FF)*256+((tempS1&0xFF00)>>8);		
			*aOutPtr = (float)(tempS2/3276.6);
			aOutPtr++;
			*aOutPtr= tempF;
			aOutPtr++;
			aPtr++;	}		
			} 
		else {
			//Since can't dynamics change the waveform length, for the remaining waveform,
			//just copy the last points for a better display
			*aOutPtr= tempF;
			aOutPtr++;
			aPtr++;	 }	
	}		
	return 0;
}	
	

epicsRegisterFunction(subADCWfProc);
