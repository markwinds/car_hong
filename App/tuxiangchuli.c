#include "include.h"
//��ͼ��ת���ɶ�ά����
s16 current_deviation;
int er,Der,last_err;
int DST_SXT_duoji_kp=30;//25
int DST_SXT_duoji_kd=1;
int DST_SXT_kongzhi;


uint8 imgErwei[CAMERA_W][CAMERA_H]; 
char SXTzhongjian[61];//���һ���м����ο�ֵ
int SXTzuobian[60],SXTyoubian[60];
unsigned char flag_zuobianjie[60],flag_youbianjie[60];
int SXTbaixiankuandu[60]={
11,12,13,14,15,16,17,18,19,20,
21,22,23,24,25,26,27,28,29,30,
31,32,33,34,35,36,37,38,39,40,
41,42,43,44,45,46,47,48,49,50,
51,52,53,54,55,56,57,58,59,60,
61,62,63,64,65,66,67,68,69,70,
};
unsigned char diuyoubian_flag,diuzuobian_flag;
int shizishangZuoX,shizishangZuoY,shizishangYouX,shizishangYouY,shizixiaZuoX,shizixiaZuoY,shizixiaYouX,shizixiaYouY,x0_1,x1_1,y0_1,y1_1,x0_2,y0_2,x1_2,y1_2,x_0,y_0,x_1,y_1,geshu_N;
unsigned char quanbai_N,jiange_Zuo,jiange_You;
int shizitemp[]={0};
float canshu_A,canshu_B;

void tuxiangzhuanhuan(void)
{
  int x_img,y_img,ll1;
  for(ll1=0;ll1<4800;ll1++)
   {
     x_img=((ll1)%80);
     y_img=((ll1)/80);
     imgErwei[x_img][y_img]=img[ll1];
   
   }
}


void bianxiantiqu(void)
{
 int iii0,iii1,jjj;
SXTzhongjian[60]=40;
 for(jjj=59;jjj>=0;jjj--) //����ԽС����ԽԶ��Խ��������Խ��
   {  
      for(iii0=SXTzhongjian[jjj+1];iii0<80;iii0++)//��һ�ΰ�������м�SXTzhongjian[59]
       {
            if(imgErwei[iii0][jjj]==0)//0�Ǻ�ɫ
              {
                 SXTyoubian[jjj]=iii0;
                 flag_youbianjie[jjj]=1;//�Ѿ��ҵ���Ч�߽�
                 break;
              }
       }
        if(flag_youbianjie[jjj]==0)
             {
                SXTyoubian[jjj]=79;
             }
       
      
      for(iii1=SXTzhongjian[jjj+1];iii1>=0;iii1--)
      {
             if(imgErwei[iii1][jjj]==0)
                {
                  SXTzuobian[jjj]=iii1;
                  flag_zuobianjie[jjj]=1;//�Ѿ��ҵ���Ч�߽�
                  break;
                }
      }
       if(flag_zuobianjie[jjj]==0)
            {
              SXTzuobian[jjj]=0;
            }
      

       if((flag_youbianjie[jjj]==0)&&(flag_zuobianjie[jjj]==1))//�����ұ߽߱�Ļ�
           {
              SXTyoubian[jjj]=(SXTzuobian[jjj]+SXTbaixiankuandu[jjj]+6);
           }
       else if((flag_youbianjie[jjj]==1)&&(flag_zuobianjie[jjj]==0))//������߽߱�Ļ�
          {
              SXTzuobian[jjj]=(SXTyoubian[jjj]-SXTbaixiankuandu[jjj]-6);
          }
       else if((flag_youbianjie[jjj]==0)&&(flag_zuobianjie[jjj]==0)&&jjj>0)//�����߶����� ������ʮ�����������һ�֣����п�����бʮ��,jjj>15��ʾ�ų�̫Զ�Ĳ�ȷ������
         {
           
         ;
         }
      
      flag_youbianjie[jjj]=0; //����ұ߱�־λ �ұ�
      flag_zuobianjie[jjj]=0; //����ұ߱�־λ ���
      SXTzhongjian[jjj]=(SXTzuobian[jjj]+SXTyoubian[jjj])/2;
   }
 /*if(quanbai_N!=0)
 {
   if(quanbai_N>5){
  // shizishangYouY=shizishangZuoY;
  // shizixiaZuoY=shizishangYouY+quanbai_N+4;
  // shizixiaYouY=shizixiaZuoY;
   shizishangZuoY=shizishangYouY;
   shizixiaYouY=shizishangZuoY+quanbai_N+8;
   shizixiaZuoY=shizixiaYouY;
   
   
   /*SXTzuobian[shizishangZuoY]=20;
   SXTzuobian[shizixiaZuoY]=20;
   SXTyoubian[shizishangYouY]=60;
   SXTyoubian[shizixiaYouY]=60;*/
   
 /*  x0_1=SXTzuobian[shizishangZuoY];
   y0_1=shizishangZuoY;
   x1_1=SXTzuobian[shizixiaZuoY];
   y1_1=shizixiaZuoY;
   
   x0_2=SXTyoubian[shizishangYouY];
   y0_2=shizishangYouY;
   x1_2=SXTyoubian[shizixiaYouY];
   y1_2=shizixiaYouY;
   
   //x_0=(x0_1+x0_2)/2;
   //x_1=(x1_1+x1_2)/2;
   //y_0=y0_1;
   //y_1=y1_1;
   x_0=(x0_1+x0_2)/2;
   x_1=(x1_1+x1_2)/2;
   y_0=y0_1;
   y_1=y1_1;
   
   //x_0=10;///(x0_1+x0_2)/2;
   //x_1=60;//(x1_1+x1_2)/2;
  // y_0=15;//y0_1;
 //  y_1=30;//y1_1;
   
   LCD_huaxian(x_0,y_0,x_1,y_1);
   
   
   }
   //DDALine(shizishangZuoY,SXTzuobian[shizishangZuoY],shizixiaZuoY,SXTzuobian[shizixiaZuoY]);
   quanbai_N=0;
 }*/
  


}
void LCD_huaxian(int x_0,int y_0,int x_1,int y_1)
{
   int iii0;
   canshu_A=(float)(y_1-y_0)/(x_1-x_0);
   canshu_B=(float)(y_0*x_1-y_1*x_0)/(x_1-x_0);
   geshu_N=y_1-y_0;
   for(iii0=1;iii0<=geshu_N;iii0++)
    {
      // SXTzhongjian[]
      SXTzhongjian[x_0+iii0]=(char)(((float)(y_0+iii0)-canshu_B)/(canshu_A));
    }
}

/*
void LCD_line(int x1,int y1,int x2,int y2)
{
int i;
float x_length,y_length;
float abs_x_length,abs_y_length;
float temp=0.0;

x_length=(float)x2-x1;
y_length=(float)y2-y1;
abs_x_length=abs((int)x_length);
abs_y_length=abs((int)y_length);
if(abs_x_length>abs_y_length)
    {
      for(i=0;i<abs_x_length;i++)
       {
         temp=(float)y_length/abs_x_length*i;
         if(x_length<0)
   // lcd_pixel(x1-i,y1+temp)
          //  shizitemp[i]=x1-i;
          shizitemp[i]=shizitemp[i]-i; 
         else
    //  lcd_pixel(x1+i,y1+temp)
          ;//  shizitemp[i]=x1+i;
       }
    }
else
    {
      for(i=0;i<abs_y_length;i++)
      { 
        temp=(float)x_length/abs_y_length*i;
        if(y_length<0)
          ;//lcd_pixel(x1+temp,y1-i);
        else
          ;// lcd_pixel(x1+temp,y1+i);
      
      }
        
    }
}

void DDALine(int x0,int y0,int x1,int y1)
{
int x;
float dx,dy,y,k;
dx=x1-x0;
dy=y1-y0;
k=dy/dx;
y=y0;
for(x=x0;x<x1;x++)
{
shizitemp[x-x0]=(int)(y+0.5);
y=y+k;
}
}*/


void DSJ_pianchachuli(void)
{
  current_deviation=(int)(0.8*(SXTzhongjian[30]-SXTzhongjian[45])/15+1.2*(SXTzhongjian[52]-40));//ǰ0.8 ��1.2 ��2
 }


  
void DST_SXT_duojizhuanxiang(int err)
{
er=err;
Der=last_err-er;
DST_SXT_kongzhi=steer_mid-DST_SXT_duoji_kp*er+DST_SXT_duoji_kd*Der;
if(DST_SXT_kongzhi>steer_max)
DST_SXT_kongzhi=steer_max;
if(DST_SXT_kongzhi<steer_min)
DST_SXT_kongzhi=steer_min;
last_err=er;
ftm_pwm_duty(FTM1, FTM_CH0,DST_SXT_kongzhi);
  
}

