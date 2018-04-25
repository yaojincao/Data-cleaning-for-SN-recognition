// 0 -9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36
// 0 -9  A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z

#include "DataStru.h"

//extern char RResult[20];//识别结果
extern int NumSim[ModNum];//相似度，过度变量
extern int iNew;
int jNew;

int maxC1, maxC2, maxC3, maxN1, maxN2, maxN3;

int sim234[3][ModNum];
int simC1, simC2, simC3,simN1, simN2, simN3, sumC1N2N3, sumN1C2N3, sumN1N2C3;

float simDouble234[3][36];
float simDoubleC1, simDoubleC2, simDoubleC3,simDoubleN1, simDoubleN2, simDoubleN3, simDoubleC1N2N3, simDoubleN1C2N3, simDoubleN1N2C3;


void AlpEvo4ForSingle()
{
	//20120221用于23两位补判------

		if(
			(RResult[1]>=10&&RResult[2]<10&&RResult[3]<10)
			||
			(RResult[1]<10&&RResult[2]>=10&&RResult[3]<10)
			||
			(RResult[1]<10&&RResult[2]<10&&RResult[3]>=10)			
			)

		{
		}

		else
		{
			//find max C1;
			maxC1=10;
			simC1=sim234[0][10];
			for(jNew=10;jNew<35;jNew++)
			{
				if(sim234[0][jNew+1]>simC1) 
				{
					simC1=sim234[0][jNew+1]; maxC1=jNew+1;
				}
			}
			
			//find max C2;
			maxC2=10;
			simC2=sim234[1][10];
			for(jNew=10;jNew<35;jNew++)
			{
				if(sim234[1][jNew+1]>simC2) 
				{
					simC2=sim234[1][jNew+1]; maxC2=jNew+1;
				}
			}
			//find max C3;
			maxC3=10;
			simC3=sim234[2][10];
			for(jNew=10;jNew<35;jNew++)
			{
				if(sim234[2][jNew+1]>simC3) 
				{
					simC3=sim234[2][jNew+1]; maxC3=jNew+1;
				}
			}

			//find max N1;
			maxN1=0;
			simN1=sim234[0][0];
			for(jNew=0;jNew<9;jNew++)
			{
				if(sim234[0][jNew+1]>simN1) 
				{
					simN1=sim234[0][jNew+1]; maxN1=jNew+1;
				}
			}			
			
			//	find max N2;
			maxN2=0;
			simN2=sim234[1][0];
			for(jNew=0;jNew<9;jNew++)
			{
				if(sim234[1][jNew+1]>simN2) 
				{
					simN2=sim234[1][jNew+1]; maxN2=jNew+1;
				}
			}
			//	find max N3;
			maxN3=0;
			simN3=sim234[2][0];
			for(jNew=0;jNew<9;jNew++)
			{
				if(sim234[2][jNew+1]>simN3) 
				{
					simN3=sim234[2][jNew+1]; maxN3=jNew+1;
				}
			}
			//			get  N1+C2;get  C1+N2;
			sumC1N2N3=simC1+simN2+simN3;
			sumN1C2N3=simN1+simC2+simN3;
			sumN1N2C3=simN1+simN2+simC3;
			//			compare C1+N2 and N1+C2;make a decision (C1+N2 prior);
			if ( sumN1N2C3>sumN1C2N3 && sumN1N2C3>sumC1N2N3 )
			{
				RResult[1]=maxN1;RResult[2]=maxN2;RResult[3]=maxC3;
			}
			else 
			{
				if(sumN1C2N3>sumC1N2N3 && sumN1C2N3>sumN1N2C3)
				{
					RResult[1]=maxN1;RResult[2]=maxC2;RResult[3]=maxN3;
				}
				else
				{
					RResult[1]=maxC1;RResult[2]=maxN2;RResult[3]=maxN3;
				}
			}

			
		}

	
	
	
}
void AlpEvo4ForDouble()
{
	//20120221ÓÃÓÚ23Á½Î»²¹ÅÐ------

		if(
			(RResult[1]>=10&&RResult[2]<10&&RResult[3]<10)
			||
			(RResult[1]<10&&RResult[2]>=10&&RResult[3]<10)
			||
			(RResult[1]<10&&RResult[2]<10&&RResult[3]>=10)			
			
			) {}		
		else
		{
			//find max C1;
			maxC1=10;
			simDoubleC1=simDouble234[0][10];
			for(jNew=10;jNew<35;jNew++)
			{
				if(simDouble234[0][jNew+1]>simDoubleC1) 
				{
					simDoubleC1=simDouble234[0][jNew+1]; maxC1=jNew+1;
				}
			}			
			//find max C2;
			maxC2=10;
			simDoubleC2=simDouble234[1][10];
			for(jNew=10;jNew<35;jNew++)
			{
				if(simDouble234[1][jNew+1]>simDoubleC2) 
				{
					simDoubleC2=simDouble234[1][jNew+1]; maxC2=jNew+1;
				}
			}
			//find max C3;
			maxC3=10;
			simDoubleC3=simDouble234[2][10];
			for(jNew=10;jNew<35;jNew++)
			{
				if(simDouble234[2][jNew+1]>simDoubleC3) 
				{
					simDoubleC3=simDouble234[2][jNew+1]; maxC3=jNew+1;
				}
			}
			//find max N1;
			maxN1=0;
			simDoubleN1=simDouble234[0][0];
			for(jNew=0;jNew<9;jNew++)
			{
				if(simDouble234[0][jNew+1]>simDoubleN1) 
				{
					simDoubleN1=simDouble234[0][jNew+1]; maxN1=jNew+1;
				}
			}			
			//	find max N2;
			maxN2=0;
			simDoubleN2=simDouble234[1][0];
			for(jNew=0;jNew<9;jNew++)
			{
				if(simDouble234[1][jNew+1]>simDoubleN2) 
				{
					simDoubleN2=simDouble234[1][jNew+1]; maxN2=jNew+1;
				}
			}
			//	find max N3;
			maxN3=0;
			simDoubleN3=simDouble234[2][0];
			for(jNew=0;jNew<9;jNew++)
			{
				if(simDouble234[2][jNew+1]>simDoubleN3) 
				{
					simDoubleN3=simDouble234[2][jNew+1]; maxN3=jNew+1;
				}
			}
			//			get  N1+C2;get  C1+N2;
			simDoubleC1N2N3=simDoubleC1+simDoubleN2+simDoubleN3;
			simDoubleN1C2N3=simDoubleN1+simDoubleC2+simDoubleN3;
			simDoubleN1N2C3=simDoubleN1+simDoubleN2+simDoubleC3;
			//			compare C1+N2 and N1+C2;make a decision (C1+N2 prior);
			if ( simDoubleN1N2C3>simDoubleN1C2N3 && simDoubleN1N2C3>simDoubleC1N2N3 )
			{
				RResult[1]=maxN1;RResult[2]=maxN2;RResult[3]=maxC3;
			}
			else 
			{
				if(simDoubleN1C2N3>simDoubleC1N2N3 && simDoubleN1C2N3>simDoubleN1N2C3)
				{
					RResult[1]=maxN1;RResult[2]=maxC2;RResult[3]=maxN3;
				}
				else
				{
					RResult[1]=maxC1;RResult[2]=maxN2;RResult[3]=maxN3;
				}
			}			
		}	
}


