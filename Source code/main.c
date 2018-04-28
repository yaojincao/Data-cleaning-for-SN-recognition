#include <stdio.h> 
//#include <iostream.h>
#include <stdlib.h> 
#include "DataStru.h"
//#include "math.h"
#include "string.h"
#include "Process.h"


//extern char RResult[20];//左冠号识别结果
extern int Num_i;//识别计数
extern int NumSim[ModNum], ComTem;//相似度，过度变量


extern int ChMod[21][15];//归一化字符存储位置
extern int ChMod15[29][15];//归一化字符存储位置

extern float NumDoubleSim[36], ComDoubleTem;//相似度，过度变量
extern int RealStart[10],RealEnd[10];//左边冠号竖直方向起始终止位置

//前四位判断辅助变量
extern int maxC1, maxC2, maxC3, maxN1, maxN2, maxN3;
extern int sim234[3][ModNum];
extern int simC1, simC2, simC3,simN1, simN2, simN3, sumC1N2N3, sumN1C2N3, sumN1N2C3;
extern float simDouble234[3][36];
extern float simDoubleC1, simDoubleC2, simDoubleC3,simDoubleN1, simDoubleN2, simDoubleN3;
extern float simDoubleC1N2N3, simDoubleN1C2N3, simDoubleN1N2C3;

extern int BinParSet;//辅助参数

extern int SnCornrX;//折角参数
extern int SnCornrY;//折角参数

extern	char *SeriesNumRecVersion;//版本号,15版冠字号全字体版（基于"SnRec_COS1000_151126.02.15";）

extern int I1JumpPar[10];// I，1宽度检测参量

//下为位置估计基础变量
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

//15版新币参数
extern int chleft_102[];
extern int chright_102[];
extern int HEvaluate_102[10];
extern int WEvaluate_102[10];

extern int Delta_yMin[10];//定位辅助参数
extern int yMin,yMin1;//定位辅助参数
extern int PrintPar;//定位辅助参数
extern int Adj;//定位辅助参数


//右边冠号附加参数
extern int SnPosId;//左右冠号标志位，0为左，1为右冠号
extern char RResultSnRt[20];//识别结果
extern int NumSimSnRt[ModNum];//相似度辅助参数
extern float NumDoubleSimSnRt[36];//相似度辅助参数
extern int RealStartSnRt[10],RealEndSnRt[10];//每个冠号竖直方向的起始和终止
extern int yMinSnRt,yMin1SnRt;//定位辅助参数

//右边冠字号主程序变量
extern int height1SnRt[SnRtRecImgHeight][10];				//辅助参数
extern int wSnProjectionSnRt[300];									//投影辅助参数
extern int SimIntSnRt[SnRtRecImgHeight];					//辅助参数
extern int yMaxSnRt;											//定位辅助参数
extern int XStartSnRt[10],XEndSnRt[10];						//定位辅助参数
//原主程序DSP变量
extern int version;//版本10代表10元；20代表20元；50代表50元；100代表100元05版；101代表100元99版；102代表100元15版
extern int ObjOrientation;//0表示反面；1表示正面；其中15版100元正反两面同一种算法处理特殊定义为3；（对于双CIS此值只能设置为1或3）	
extern int sim23[2][ModNum];//冠字号23两位相似度

extern int iNew;//辅助参数

//Buf33[SnRecImgHeight][SnRecImgWidth]; //ch为辅助参数； Buf33左冠号数据存储Buf

extern int height1[SnRecImgHeight][10];//辅助参数
extern int wSnProjection[300];//宽度投影参数


extern unsigned char Thr;//阈值辅助参数
extern int DetectStepHeight;//检测辅助参数

extern int SimInt[SnRecImgHeight];//定位辅助参数
extern int yMax;//定位辅助参数
extern int XStart[10],XEnd[10];//定位辅助参数
extern int ANSim_num;//相似度辅助参数
extern int ANSim[10];//相似度辅助参数

//双CIS补充
extern int DetectStepForHeight;//检测辅助参数
extern float simDouble23[2][36];//相似度辅助参数
extern float ANDoubleSim_num;//相似度辅助参数
extern float ANDoubleSim[10];//相似度辅助参数

extern int FlagHeightError[10];//定义位置异常标记位
extern int FLagWidthError[10];//定义位置异常标记位

extern int TotalSim;//污染参数
extern int DiffMag;//污染参数

extern int FoldFlag;//折角标志位，1表示有折角	

//新增局部特征定位辅助参数
extern int CenterEvo[10];
extern int CenterMovment;
extern int I1_CenterDetect[10];
extern int FlagReSeg;
extern int ThrForReSeg[15];

extern int yMinMag;//磁性参数
extern pSnRecDataL Buf33;
extern pSnRecDataR Buf39;

//这句在这里实现，封装时这里的都用不到
SN_IMAGE *SnImageInfo;
//调试代码
unsigned char SnBinTest[276*128];
//处理截角问题初始化



//简化版读bmp图像函数

unsigned char imread( long m1, long n1, long Exch_W1, FILE*in1)
{
	unsigned char Ch1;
	fseek(in1,1078+m1*Exch_W1+n1,SEEK_SET);
	if (fread(&Ch1, sizeof(char), 1, in1) == 1) return Ch1;
	else {printf("Error imread() != 1 "); return 0;}
}

int main()
{


	//文件指针
	FILE* in;//输入图像文件指针

	FILE* out2;//输出图像左边
	FILE* out5;//输出图像右边
	FILE* out3;//文本txt左边
	FILE* out6;//文本txt右边

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

	//---------------------------------------------------------DSP算法变量---------------------------------------------------------
	//---------------------------------------------------------DSP算法变量---------------------------------------------------------
	//---------------------------------------------------------DSP算法变量---------------------------------------------------------
	int flag,xx,yy;//辅助参数
	unsigned char ch;
	int i,j,z,y;//辅助参数
	unsigned char SnDifNumMain=0;




	//--------------------------------------------------------	DSP算法变量结束
	//int fTest[276*128];
	//unsigned char (*pTest)[276];




	SnImageInfo = (SN_IMAGE *) malloc (sizeof(SN_IMAGE)*2);
	SnImageInfo[0].SnImageValid=1;
	SnImageInfo[1].SnImageValid=1;

	//程序参数初始化
	strcpy(path1, "D:\\sn_1\\SnNumber_Left.txt");	
	out3 = fopen(path1, "w");	

	strcpy(path1, "D:\\sn_1\\SnNumber_Right.txt");	
	out6 = fopen(path1, "w");


	//PC调试初始化，移植时要注释	
	SnTruncationPar.Interc1=10;		//大图左边截距(须赋值)
	SnTruncationPar.Interc2=10;		//大图下边边截距(须计算)
	SnTruncationPar.Interc3=0;			//大图右边截距(须赋值)
	SnTruncationPar.MattingX=0;		//抠图左下角x坐标(须赋值)
	SnTruncationPar.MattingY=0;		//抠图左下角y坐标(须赋值)
	SnTruncationPar.yTemp0=0;			//计算出的截线上的点的y高度坐标
	SnTruncationPar.yInit=0;			//计算出的小图左边截距

	//PC和机器调试公用初始化，移植也不能注释
	SnTruncationPar.InfoChose=0;	//选择哪个面的CashInfo
	SnTruncationPar.kTemp=0;		//从唐老师处获得的斜率
	SnTruncationPar.AvePlug=0;	//初始化填充值



	
	//----------------------------------------------------- 程序总体循环开始 ------------------------------------------------------------	

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

			//---------------------------------------------------图像参数读取及文件头拷贝---------------------------------------------------			
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
			//拷贝文件头
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
			//----------------------------------          图像参数读取文件头拷贝结束              ----------------------------------//



			//拷贝图像到数组

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
				//输出图像左边
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

		

		//--------------------------------------------------------------------     DSP 算法主程序开始     --------------------------------------------------------------------

		//SnCornerX = cacheinfo.cornerX[0] - pProcessConfig->SnR1[gPattern].StartX;
		//SnCornerY = cacheinfo.cornerY[0] - pProcessConfig->SnR1[gPattern].StartY;

		//初始化识别结果





		//-------------------------------------------------------------DSP算法结束-------------------------------------------------------------


		// 输出号码 










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
		//	//看定位临时代码

		//	for(xx=0;xx<SnRecImgWidth;xx++)
		//	{
		//		Buf33[yMin][xx]=0;
		//	}

		//	//看定位临时代码//
		//	//20110531写图像--------

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
		//	//看定位临时代码

		//	for(xx=0;xx<SnRtRecImgWidth;xx++)
		//	{
		//		Buf39[yMinSnRt][xx]=0;
		//	}

		//	//看定位临时代码//
		//	//20110531写图像--------

		//	fseek(out5,1078,SEEK_SET);
		//	for (xx=0;xx<SnRtRecImgHeight;xx++)
		//		for(yy=0;yy<SnRtRecImgWidth;yy++)
		//		{
		//			ch=Buf39[xx][yy];
		//			putc(ch, out5);
		//		}
		//}
		////--------20110531写图像


		//fclose(out2);

		printf("SnDifNumMain = %d \n", SnDifNumMain);
	}//对应 for (TestLoop=1;TestLoop<=10000;TestLoop++)
	fclose(out3);
	fclose(out6);
	//getchar();

	free(SnImageInfo);//释放内存
	getchar();
	return 0;
}
