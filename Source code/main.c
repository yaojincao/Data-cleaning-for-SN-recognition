#include <stdio.h> 
//#include <iostream.h>
#include <stdlib.h> 
#include "DataStru.h"
//#include "math.h"
#include "string.h"
#include "Process.h"


//extern char RResult[20];//��ں�ʶ����
extern int Num_i;//ʶ�����
extern int NumSim[ModNum], ComTem;//���ƶȣ����ȱ���


extern int ChMod[21][15];//��һ���ַ��洢λ��
extern int ChMod15[29][15];//��һ���ַ��洢λ��

extern float NumDoubleSim[36], ComDoubleTem;//���ƶȣ����ȱ���
extern int RealStart[10],RealEnd[10];//��߹ں���ֱ������ʼ��ֹλ��

//ǰ��λ�жϸ�������
extern int maxC1, maxC2, maxC3, maxN1, maxN2, maxN3;
extern int sim234[3][ModNum];
extern int simC1, simC2, simC3,simN1, simN2, simN3, sumC1N2N3, sumN1C2N3, sumN1N2C3;
extern float simDouble234[3][36];
extern float simDoubleC1, simDoubleC2, simDoubleC3,simDoubleN1, simDoubleN2, simDoubleN3;
extern float simDoubleC1N2N3, simDoubleN1C2N3, simDoubleN1N2C3;

extern int BinParSet;//��������

extern int SnCornrX;//�۽ǲ���
extern int SnCornrY;//�۽ǲ���

extern	char *SeriesNumRecVersion;//�汾��,15����ֺ�ȫ����棨����"SnRec_COS1000_151126.02.15";��

extern int I1JumpPar[10];// I��1��ȼ�����

//��Ϊλ�ù��ƻ�������
extern int chleft[];
extern int chright[];

extern int chleft_100_old[];
extern int chright_100_old[];

extern int chleft_51[];
extern int chright_51[];

extern int chleft_50[];
extern int chright_50[];

extern int chleft_20[];
extern int chright_20[];

extern int chleft_10[];
extern int chright_10[];

extern int chleft_5[];
extern int chright_5[];

extern int HAdd_100[10];
extern int Delta_yMin_100[10];

extern int HEvaluate_100[10];
extern int WEvaluate_100[10];

extern int HEvaluate_101[10];
extern int WEvaluate_101[10];

extern int HEvaluate_20[10];
extern int WEvaluate_20[10];

//15���±Ҳ���
extern int chleft_102[];
extern int chright_102[];
extern int HEvaluate_102[10];
extern int WEvaluate_102[10];

extern int Delta_yMin[10];//��λ��������
extern int yMin,yMin1;//��λ��������
extern int PrintPar;//��λ��������
extern int Adj;//��λ��������


//�ұ߹ںŸ��Ӳ���
extern int SnPosId;//���ҹںű�־λ��0Ϊ��1Ϊ�ҹں�
extern char RResultSnRt[20];//ʶ����
extern int NumSimSnRt[ModNum];//���ƶȸ�������
extern float NumDoubleSimSnRt[36];//���ƶȸ�������
extern int RealStartSnRt[10],RealEndSnRt[10];//ÿ���ں���ֱ�������ʼ����ֹ
extern int yMinSnRt,yMin1SnRt;//��λ��������

//�ұ߹��ֺ����������
extern int height1SnRt[SnRtRecImgHeight][10];				//��������
extern int wSnProjectionSnRt[300];									//ͶӰ��������
extern int SimIntSnRt[SnRtRecImgHeight];					//��������
extern int yMaxSnRt;											//��λ��������
extern int XStartSnRt[10],XEndSnRt[10];						//��λ��������
//ԭ������DSP����
extern int version;//�汾10����10Ԫ��20����20Ԫ��50����50Ԫ��100����100Ԫ05�棻101����100Ԫ99�棻102����100Ԫ15��
extern int ObjOrientation;//0��ʾ���棻1��ʾ���棻����15��100Ԫ��������ͬһ���㷨�������ⶨ��Ϊ3��������˫CIS��ֵֻ������Ϊ1��3��	
extern int sim23[2][ModNum];//���ֺ�23��λ���ƶ�

extern int iNew;//��������

//Buf33[SnRecImgHeight][SnRecImgWidth]; //chΪ���������� Buf33��ں����ݴ洢Buf

extern int height1[SnRecImgHeight][10];//��������
extern int wSnProjection[300];//���ͶӰ����


extern unsigned char Thr;//��ֵ��������
extern int DetectStepHeight;//��⸨������

extern int SimInt[SnRecImgHeight];//��λ��������
extern int yMax;//��λ��������
extern int XStart[10],XEnd[10];//��λ��������
extern int ANSim_num;//���ƶȸ�������
extern int ANSim[10];//���ƶȸ�������

//˫CIS����
extern int DetectStepForHeight;//��⸨������
extern float simDouble23[2][36];//���ƶȸ�������
extern float ANDoubleSim_num;//���ƶȸ�������
extern float ANDoubleSim[10];//���ƶȸ�������

extern int FlagHeightError[10];//����λ���쳣���λ
extern int FLagWidthError[10];//����λ���쳣���λ

extern int TotalSim;//��Ⱦ����
extern int DiffMag;//��Ⱦ����

extern int FoldFlag;//�۽Ǳ�־λ��1��ʾ���۽�	

//�����ֲ�������λ��������
extern int CenterEvo[10];
extern int CenterMovment;
extern int I1_CenterDetect[10];
extern int FlagReSeg;
extern int ThrForReSeg[15];

extern int yMinMag;//���Բ���
extern pSnRecDataL Buf33;
extern pSnRecDataR Buf39;

//���������ʵ�֣���װʱ����Ķ��ò���
SN_IMAGE *SnImageInfo;
//���Դ���
unsigned char SnBinTest[276*128];
//����ؽ������ʼ��



//�򻯰��bmpͼ����

unsigned char imread( long m1, long n1, long Exch_W1, FILE*in1)
{
	unsigned char Ch1;
	fseek(in1,1078+m1*Exch_W1+n1,SEEK_SET);
	if (fread(&Ch1, sizeof(char), 1, in1) == 1) return Ch1;
	else {printf("Error imread() != 1 "); return 0;}
}

int main()
{


	//�ļ�ָ��
	FILE* in;//����ͼ���ļ�ָ��

	FILE* out2;//���ͼ�����
	FILE* out5;//���ͼ���ұ�
	FILE* out3;//�ı�txt���
	FILE* out6;//�ı�txt�ұ�

	int exchange[8],Exch_H,Exch_W,n=0,m=0; //Exch_W1
	char path[200],path1[200],path2[200];
	char pathTemp[100];
	char NumTran[30];
	char NumTran1[30]={'P','0','6','F','0','V','3','v','1','0','0','_'};
	//char NumTran1[30]={'v','2','v','1','0','0','_'};
	int TestLoop;
	//	char NumTran1[30]={'P','0','4','F','2','V','1','V','0','5','0','_'};
	//	char NumTran1[30]={'P','1','1','F','1','V','2','V','1','0','0','_'};
	//	char NumTran1[30]={'P','0','9','F','3','V','2','V','0','2','0','_'};

	//---------------------------------------------------------DSP�㷨����---------------------------------------------------------
	//---------------------------------------------------------DSP�㷨����---------------------------------------------------------
	//---------------------------------------------------------DSP�㷨����---------------------------------------------------------
	int flag,xx,yy;//��������
	unsigned char ch;
	int i,j,z,y;//��������
	unsigned char SnDifNumMain=0;




	//--------------------------------------------------------	DSP�㷨��������
	//int fTest[276*128];
	//unsigned char (*pTest)[276];




	SnImageInfo = (SN_IMAGE *) malloc (sizeof(SN_IMAGE)*2);
	SnImageInfo[0].SnImageValid=1;
	SnImageInfo[1].SnImageValid=1;

	//���������ʼ��
	strcpy(path1, "D:\\sn_1\\SnNumber_Left.txt");	
	out3 = fopen(path1, "w");	

	strcpy(path1, "D:\\sn_1\\SnNumber_Right.txt");	
	out6 = fopen(path1, "w");


	//PC���Գ�ʼ������ֲʱҪע��	
	SnTruncationPar.Interc1=10;		//��ͼ��߽ؾ�(�븳ֵ)
	SnTruncationPar.Interc2=10;		//��ͼ�±߽߱ؾ�(�����)
	SnTruncationPar.Interc3=0;			//��ͼ�ұ߽ؾ�(�븳ֵ)
	SnTruncationPar.MattingX=0;		//��ͼ���½�x����(�븳ֵ)
	SnTruncationPar.MattingY=0;		//��ͼ���½�y����(�븳ֵ)
	SnTruncationPar.yTemp0=0;			//������Ľ����ϵĵ��y�߶�����
	SnTruncationPar.yInit=0;			//�������Сͼ��߽ؾ�

	//PC�ͻ������Թ��ó�ʼ������ֲҲ����ע��
	SnTruncationPar.InfoChose=0;	//ѡ���ĸ����CashInfo
	SnTruncationPar.kTemp=0;		//������ʦ����õ�б��
	SnTruncationPar.AvePlug=0;	//��ʼ�����ֵ



	
	//----------------------------------------------------- ��������ѭ����ʼ ------------------------------------------------------------	

	PrintPar=0; 

	for (TestLoop=1;TestLoop<=28030;TestLoop++)//1748 1825
		//-----------------------------------------------------------------------------------------------------------------
	{
		//PrintChMod15Mod();
		//PrintChMod15ModOnlyNum();

		SnPosId=0;
		if (0==SnPosId)
		{
			NumTran1[0]='P'; NumTran1[1]='0';NumTran1[2]='6';NumTran1[3]='F';NumTran1[4]='0';NumTran1[5]='V';NumTran1[6]='1';
			NumTran1[7]='V';NumTran1[8]='1';NumTran1[9]='0';NumTran1[10]='0';NumTran1[11]='_';

			z=0;y=0;n=0;m=0;xx=0;yy=0;

			//---------------------------------------------------ͼ�������ȡ���ļ�ͷ����---------------------------------------------------			
			strcpy(path2, "D:\\sn_1\\"); strcpy(path, "D:\\sn\\");

			itoa(TestLoop,NumTran,10);
			strcpy(pathTemp,NumTran1);			
			if (TestLoop>=1&&TestLoop<=1000000) strcat(pathTemp, "000");			
			strcat(pathTemp,NumTran);strcat(pathTemp,".bmp");strcat(path,pathTemp);strcat(path2,pathTemp);			

			in = fopen(path, "rb"); //Adj=20;
			if (in==0) 
			{//printf("Read image SN %d fail!\n",TestLoop);
				continue;
			}
			out2 = fopen(path2, "wb");
			printf("%s ",pathTemp);

			fseek(in,22,SEEK_SET);

			for(i=0;i<4;i++)
			{   
				if ((fread(&ch, sizeof(char), 1, in))!=1)	
				{
					printf("Error, fread!");  break; 
				}				
				else 
				{
					exchange[i]=(int)ch;
				}				
			}			
			Exch_H=exchange[0]+(exchange[1]<<8)+(exchange[2]<<16)+(exchange[3]<<24);			
			fseek(in,1078,SEEK_SET);			
			while (fread(&ch, sizeof(char), 1, in) == 1)
			{
				z++;
			}
			Exch_W=z/Exch_H;			
			if (Exch_H>=2000) 				
			{
				printf("error!  Exch_H>=2000!"); 
				return 0;
			}			
			rewind(in);			
			//�����ļ�ͷ
			for(i=0;i<1078;i++)
			{
				if ((fread(&ch, sizeof(char), 1, in))!=1)  					
				{
					printf("Error, fread!");  
					break; 
				}			
				else
				{
					putc(ch, out2);
				}
			}
			//----------------------------------          ͼ�������ȡ�ļ�ͷ��������              ----------------------------------//



			//����ͼ������

			for (xx=0;xx<SnRecImgHeight;xx++)
				for(yy=0;yy<SnRecImgWidth;yy++) 
				{
					SnImageInfo[0].pSnImageSave[xx*SnRecImgWidth+yy]=(unsigned char)imread(xx,yy,Exch_W,in); 
				}

				fclose(in);

				SnDifNumMain=SnRecognition(SnPosId);

				if (0==SnPosId)
				{
					printf("     GZ: ");
					for(i=0;i<10;i++)
						printf("%c",RResult[i]);
					printf("\n");

					RResult[10]='\0';
					fputs (RResult,out3);
					fputs("  ",out3);
					fputs (pathTemp,out3);
					fputs("\n",out3);
				}
				//���ͼ�����
				fseek(out2,1078,SEEK_SET);
				//for (xx=0;xx<SnRecImgHeight;xx++)
				//	for(yy=0;yy<SnRecImgWidth;yy++)
				//	{
				//		ch=Buf33[xx][yy];
				//		putc(ch, out2);
				//	}

				for (xx=0;xx<SnRecImgHeight;xx++)
					for(yy=0;yy<SnRecImgWidth;yy++)
					{
						//if (xx<40&&yy<240)
						//{
							ch=Buf33[xx][yy];
							putc(ch, out2);
						//}
						//else
						//{
						//	ch=255;
						//	putc(ch, out2);
						//}
					}

					fclose(out2);

		}

		

		//--------------------------------------------------------------------     DSP �㷨������ʼ     --------------------------------------------------------------------

		//SnCornerX = cacheinfo.cornerX[0] - pProcessConfig->SnR1[gPattern].StartX;
		//SnCornerY = cacheinfo.cornerY[0] - pProcessConfig->SnR1[gPattern].StartY;

		//��ʼ��ʶ����





		//-------------------------------------------------------------DSP�㷨����-------------------------------------------------------------


		// ������� 










		/*
		fputs("  ",out3);

		printf (" DiffPar=%d ", DiffMag);
		printf(" TotalSim=%d", TotalSim);

		fputs("DiffMag:",out3);
		fprintf(out3, "%d",DiffMag);

		fputs("  ",out3);

		fputs("TotalSim:",out3);
		fprintf(out3, "%d",TotalSim);
		*/





		//if (0==SnPosId)
		//{
		//	//����λ��ʱ����

		//	for(xx=0;xx<SnRecImgWidth;xx++)
		//	{
		//		Buf33[yMin][xx]=0;
		//	}

		//	//����λ��ʱ����//
		//	//20110531дͼ��--------

		//	fseek(out2,1078,SEEK_SET);
		//	for (xx=0;xx<SnRecImgHeight;xx++)
		//		for(yy=0;yy<SnRecImgWidth;yy++)
		//		{
		//			ch=Buf33[xx][yy];
		//			putc(ch, out2);
		//		}
		//}
		//SnPosId=1;
		//if (1==SnPosId)
		//{
		//	//����λ��ʱ����

		//	for(xx=0;xx<SnRtRecImgWidth;xx++)
		//	{
		//		Buf39[yMinSnRt][xx]=0;
		//	}

		//	//����λ��ʱ����//
		//	//20110531дͼ��--------

		//	fseek(out5,1078,SEEK_SET);
		//	for (xx=0;xx<SnRtRecImgHeight;xx++)
		//		for(yy=0;yy<SnRtRecImgWidth;yy++)
		//		{
		//			ch=Buf39[xx][yy];
		//			putc(ch, out5);
		//		}
		//}
		////--------20110531дͼ��


		//fclose(out2);

		printf("SnDifNumMain = %d \n", SnDifNumMain);
	}//��Ӧ for (TestLoop=1;TestLoop<=10000;TestLoop++)
	fclose(out3);
	fclose(out6);
	//getchar();

	free(SnImageInfo);//�ͷ��ڴ�
	getchar();
	return 0;
}
