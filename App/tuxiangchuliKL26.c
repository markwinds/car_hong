//#include "include.h"
#include "common.h"
//��ͼ��ת���ɶ�ά����
s16 current_deviation;
int er,Der,last_err;
int DST_SXT_duoji_kp=36;//30;//25����30..31
int DST_SXT_duoji_kd=10;//31...15   8
int DST_SXT_kongzhi;
int DSJ_SXT_zhongjian_count;
float DSJ_zhongjian_ave;
float DSJ_ave_piancha;
int danbian_flag;
int zhijiao_guaidian_flag;

int zhijiao_queren_zuo_flag,zhijiao_queren_you_flag;

///uint8 img[CAMERA_W*CAMERA_H];                           //����ӥ������ͷ��һ�ֽ�8�����أ������Ҫ��ѹΪ 1�ֽ�1�����أ����㴦��
//extern uint8 imgyiwei[CAMERA_W][CAMERA_H]; 
//uint8 imgyiwei[60][80]; 


int zhongjianheidian;

int yihangheidian_count;

int last_diyihang,last_dierhang,last_disanhang;

int danxian_chushizhongdian;
int SXT_danxian_zuosaomiao_flag,SXT_danxian_yousaomiao_flag;

int quanbai_flag;
int guaidian_flag;

int danjinshuangguaidianquanbai_count;

float DSJ_XL;
int DSJ_YXH;
int DSJ_piancha;

int SXT_chundan_flag,SXT_chunshuang_flag,SXT_dan_shuang_flag,SXT_shuang_dan_flag;
int SXT_chundan_flag_count,SXT_chunshuang_flag_count,SXT_dan_shuang_flag_count,SXT_shuang_dan_flag_count;

int zhongxiantingzhihang;
int youxiaohangxiayihang_zhongxian;
int youxiaohangxiayihang_zuobian,youxiaohangxiayihang_youbian;
int zhongxiantingzhihang_flag=0;

int zuobianshuangxiantiaobian_flag,zhidaoshuangxianbiandanxian_flag,youbianshuangxiantiaobian_flag,feishizizhijiaopodao_flag;
int zuobian_52hang,youbian_52hang,last_zuobian_52hang,last_youbian_52hang,zhongjian_52hang,danxian_chixu_count;
int danxian_shaungxian_flag,shuangxian_danxian_flag,shuangxian_danxian_flag,shuangxian_danxian_flag;
int shuangxian_danxia,danxian_shuangxian;

int danshuangxianqubieshizi;

int DSJ_shuangxianjindanxian_flag,DSJ_danxian_flag,DSJ_danxianjinshuangxian_flag,DSJ_shuangxian_flag;
int danxianjinshuangxian_diyihang;
int dierhangheidian_count;

int diyitiao_tiaobianhang,shuangxianbiandanxian;

int Zhijiao_zuoguai_flag,Zhijiao_youguai_flag,Zhijiao_guai_count;

uint8 imgErwei[CAMERA_W][CAMERA_H]; 
char last_SXTzhongjian[61],SXTzhongjian[61];//���һ���м����ο�ֵ
int SXTzuobian[60],SXTyoubian[60];
unsigned char flag_zuobianjie[60],flag_youbianjie[60];
int SXTbaixiankuandu[60]={
11,11,12,12,13,13,14,14,15,15,
16,16,17,17,18,18,19,19,20,20,
21,21,22,22,23,23,24,24,25,25,
26,26,27,27,28,28,29,29,30,30,
31,31,32,32,33,33,34,34,35,35,
36,36,37,37,38,38,39,39,40,40,
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



int shuangxian_danxianpanduan(void)
{
 zuobian_52hang=SXTzuobian[33];
 youbian_52hang=SXTyoubian[33];
/*********************�����������˫�߱䵥��***************************/
if(((abs(zuobian_52hang-last_zuobian_52hang))>15)&&(abs((zuobian_52hang-last_zuobian_52hang))<36)&&((abs(youbian_52hang-last_youbian_52hang))<2))
zuobianshuangxiantiaobian_flag=1;
/**********************����ֱ����˫�߱䵥�����*******************************************/
if((zuobian_52hang==youbian_52hang)&&(zuobian_52hang>32)&&(zuobian_52hang<48))      
//zhidaoshuangxianbiandanxian_flag=1;      
/*********************�ұ���������˫�߱䵥��***************************/      
if(((abs(zuobian_52hang-last_zuobian_52hang))<2)&&((abs(youbian_52hang-last_youbian_52hang))>15)&&((abs(youbian_52hang-last_youbian_52hang))<36))      
youbianshuangxiantiaobian_flag=1;
   /*********************�����ϴ������ߵķ�Χ������ʮ�����µ�(ֱ�ǻ�Ҫ����)****************************/      
if(((last_youbian_52hang-last_zuobian_52hang)>65)||((last_youbian_52hang-last_zuobian_52hang)<20))
feishizizhijiaopodao_flag=1;



if((zuobianshuangxiantiaobian_flag&&feishizizhijiaopodao_flag==0)||(zhidaoshuangxianbiandanxian_flag&&feishizizhijiaopodao_flag==0)||(youbianshuangxiantiaobian_flag&&feishizizhijiaopodao_flag==0))
{
danxian_chushizhongdian=(last_zuobian_52hang+last_youbian_52hang)/2;
SXTzhongjian[60]=danxian_chushizhongdian;
shuangxian_danxian_flag=1;
danxian_chixu_count=40;

}



flag_clr();
return shuangxian_danxian_flag;
}

     
int danxian_shuangxianpanduan(void)
{

if(((abs(SXTzhongjian[33]-zhongjian_52hang))>10)&&(danxian_chixu_count==0))
  {
  shuangxian_danxian_flag=0;
  danxian_shaungxian_flag=1;
  SXTzhongjian[60]=zhongjian_52hang;
  
  }
  zhongjian_52hang=SXTzhongjian[33];
last_zuobian_52hang=zuobian_52hang;
last_youbian_52hang=youbian_52hang;
return danxian_shaungxian_flag;
}

void flag_clr(void)
{
zuobianshuangxiantiaobian_flag=0;
zhidaoshuangxianbiandanxian_flag=0;
youbianshuangxiantiaobian_flag=0;
feishizizhijiaopodao_flag=0;
}

void dan_shaung_chuli(void)
{
    int iii0,iii1;
    SXTzhongjian[danxianjinshuangxian_diyihang]= SXTzhongjian[danxianjinshuangxian_diyihang+2];//�������˫��˫�ߴ������ֵ������ǰ�����е���ֵ������ֹ�ӵ���š�
  for(iii0=danxianjinshuangxian_diyihang;iii0>0;iii0--)//�ӵ��߽�˫����������
    {
       for(iii1=SXTzhongjian[iii0+1];iii1>0;iii1--)//
       {
          if(imgyiwei[iii0][iii1]==0)//0�Ǻ�ɫ
              {
                 SXTzuobian[iii0]=iii1;
              //   flag_zuobianjie[jjj]=1;//�Ѿ��ҵ���Ч�߽�
                 break;
              }
         
       }
       for(iii1=SXTzhongjian[iii0+1];iii1<79;iii1++)  
       {
         if(imgyiwei[iii0][iii1]==0)//0�Ǻ�ɫ
              {
                 SXTyoubian[iii0]=iii1;
              //   flag_youbianjie[jjj]=1;//�Ѿ��ҵ���Ч�߽�
                 break;
              }
         
       }
  //    if((SXTyoubian[iii0]-SXTzuobian[iii0])>45) //����ǵ��߽�˫�߽��Ӵ����ӵ㣬��ô�����ϴεĵ����м䡣  
  //           SXTzhongjian[iii0]=SXTzhongjian[danxianjinshuangxian_diyihang];
  //    else
             SXTzhongjian[iii0]=(int)((SXTzuobian[iii0]+SXTyoubian[iii0])/2);//��������ӵ㣬��ô��ֱ�Ӽ������ߡ�
      
      
      
      
      
      
    }
  
  


}

void dan_shuang_guaidianpanduan(void)
{
  int iii0;
  /*if((SXT_chundan_flag==1)&&(SXT_chundan_flag_count==0))
  {
   for(iii0=38;iii0>0;iii0--)//�ж�����
   {
    //��׼���ܼ�ʱ���
     if(abs(SXTzhongjian[iii0]-SXTzhongjian[iii0-2])>10)//�����߷������У���������м��֮ǰ���߼������������������10����ô���浥�߽�˫�ߵ�λ�á�
     {
       danxianjinshuangxian_diyihang=iii0;
       break;
     }
    }
  }
  if(SXT_dan_shuang_flag==1&&SXT_dan_shuang_flag_count==0)
  {
  for(iii0=59;iii0>39;iii0--)//�ж�����
   {
    //��׼���ܼ�ʱ���
     if(abs(SXTzhongjian[iii0]-SXTzhongjian[iii0-2])>10)//�����߷������У���������м��֮ǰ���߼������������������10����ô���浥�߽�˫�ߵ�λ�á�
     {
       danxianjinshuangxian_diyihang=iii0;
       break;
     }
    }
  
  
  }*/
}

void danxianchuli(void)//��������� ���ߴ��� �� ���߽�˫�ߴ��� 
{
 
  
  int iii0,iii1;
  int xundaodanbian_flag,zuoyoukuandu;
  zuoyoukuandu=15;
 xundaodanbian_flag=0;
  //zhongjian_52hang=SXTzhongjian[52];
 // if(danxian_chixu_count>0)
 //     danxian_chixu_count--;
  SXTzhongjian[60]=last_SXTzhongjian[59];
  for(iii0=59;iii0>10;iii0--)//�����һ�п�ʼ���ϼ���
  {
   SXT_danxian_yousaomiao_flag=0;
   SXT_danxian_zuosaomiao_flag=0;
   
    for(iii1=SXTzhongjian[iii0+1];iii1>(SXTzhongjian[iii0+1]-zuoyoukuandu);iii1--)//���м俪ʼ���������
    {
      if((imgyiwei[iii0][iii1]==0))//����һ�ε��м俪ʼ�������������߲�����С��ȡ�  ������ܻ���һЩ�������⣬ע�⣡������
      {
        SXTzuobian[iii0]=iii1;
        SXT_danxian_zuosaomiao_flag=1;
        break;
      
      }
    }
    for(iii1=SXTzhongjian[iii0+1];iii1<(SXTzhongjian[iii0+1]+zuoyoukuandu);iii1++)
    {
      if((imgyiwei[iii0][iii1]==0))
      {
        SXTyoubian[iii0]=iii1;
        SXT_danxian_yousaomiao_flag=1;
        break;
      
      }
    }
    
    if(SXT_danxian_zuosaomiao_flag==1&&SXT_danxian_yousaomiao_flag==1)
    {
      danjinshuangguaidianquanbai_count=0;
      SXTzhongjian[iii0]=(SXTzuobian[iii0]+SXTyoubian[iii0])/2;
    }
    else if(SXT_danxian_zuosaomiao_flag==1&&SXT_danxian_yousaomiao_flag==0)
    {
      danjinshuangguaidianquanbai_count=0;
      SXTzhongjian[iii0]=SXTzuobian[iii0];
    }
    else if(SXT_danxian_zuosaomiao_flag==0&&SXT_danxian_yousaomiao_flag==1)
    {
      danjinshuangguaidianquanbai_count=0;
      SXTzhongjian[iii0]=SXTyoubian[iii0];
    }
    else if((danjinshuangguaidianquanbai_count<6))
    {
      
      if(SXT_dan_shuang_flag)
      {
     // SXTzhongjian[iii0]=SXTzhongjian[iii0+1];
      SXTzhongjian[iii0]=last_SXTzhongjian[iii0];
      danjinshuangguaidianquanbai_count++;
      if(danjinshuangguaidianquanbai_count>=5)
        danxianjinshuangxian_diyihang=iii0+5;
      }
      else if((SXT_chundan_flag==1)&&(iii0<45))
      {  SXTzhongjian[iii0]=last_SXTzhongjian[iii0];
         danjinshuangguaidianquanbai_count++;
         if(danjinshuangguaidianquanbai_count>=5)
           danxianjinshuangxian_diyihang=iii0+5;
      
      }
    }
    
    
    if(SXTzhongjian[iii0]-SXTzhongjian[iii0+1]!=0&&xundaodanbian_flag==0)
    {
       xundaodanbian_flag=1;
       zuoyoukuandu=5;
    }
    
  //  if(abs(SXTzhongjian[iii0]-last_SXTzhongjian[iii0])>20)
  //    SXTzhongjian[iii0]=last_SXTzhongjian[iii0];
    
    
    
    
    
    
    
    
    
    
  //  if(SXT_danxian_zuosaomiao_flag==0&&SXT_danxian_yousaomiao_flag==0)
  //  {
     // SXTzhongjian[iii0]=20;//����Ҳ����ߣ��Ͱ��ձ�����
       //SXTzhongjian[iii0]=40; //Ϊ0�Ļ�������˫���� ����Ĵ���  ˫���������ԡ�
  //  }
    
  /*  if(abs(SXTzhongjian[39]-last_diyihang)>10)
    {
    SXTzhongjian[39]=last_diyihang;
    
    }*/
    //last_dierhang=SXTzhongjian[59];
    //last_disanhang=SXTzhongjian[52];
  //  if(abs(SXTzhongjian[59]-last_dierhang)>15)
  //  {
  //  SXTzhongjian[59]=last_dierhang;
    
  //  }
 /*     if(abs(SXTzhongjian[52]-last_disanhang)>10)
    {
    SXTzhongjian[52]=last_disanhang;
    
    }*/
    
    
     
  }
  
  /*for(iii0=59;iii0>10;iii0--)//�ж�����
  {
     if(abs(SXTzhongjian[iii0]-SXTzhongjian[iii0-2])>10)//�����߷������У���������м��֮ǰ���߼������������������10����ô���浥�߽�˫�ߵ�λ�á�
     {
       danxianjinshuangxian_diyihang=iii0;
       break;
     }
  }*/
  
 /* if((danxianjinshuangxian_diyihang>30)||SXT_dan_shuang_flag)//������߽�˫�������߽������ʮ���ˣ��򡣽����˵��߽�˫�ߵ�ģʽ��
  {
    SXT_dan_shuang_flag=1;
    dan_shaung_chuli();
  }*/
  

    //current_deviation=(int)(0.8*(SXTzhongjian[30]-SXTzhongjian[45])/15+1.2*(SXTzhongjian[39]-40));

}


void shuangxianchuli(void)
{ 
 int iii0,iii1,jjj;
 zhongxiantingzhihang_flag=0;//����ֹͣ�У�flag ��1.ÿ�����㣬ȷ��ÿ�ζ����Է����µĶ�̬����ֹͣ�С�
 //SXTzhongjian[60]=40;
  for(jjj=59;jjj>0;jjj--) //����ԽС����ԽԶ��Խ��������Խ��
   {  //flag_youbianjie[jjj]=0; //����ұ߱�־λ �ұ�
      //flag_zuobianjie[jjj]=0; //����ұ߱�־λ ��� 
      for(iii0=SXTzhongjian[jjj+1];iii0<80;iii0++)//��һ�ΰ�������м�SXTzhongjian[59]
       {
            if(imgyiwei[jjj][iii0]==0)//0�Ǻ�ɫ
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
        /* else
             {
                flag_youbianjie[jjj]=0;
             }*/
       
      
      for(iii1=SXTzhongjian[jjj+1];iii1>=0;iii1--)
      {
             if(imgyiwei[jjj][iii1]==0)
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
     /* else
            {
              flag_zuobianjie[jjj]=0;
             }*/
      
      
        if((flag_youbianjie[jjj]==1)&&(flag_zuobianjie[jjj]==1))
           {
               
             
             if((zhongxiantingzhihang_flag==0)&&(SXTyoubian[jjj]==SXTzuobian[jjj]))//&&((SXTzhongjian[jjj+1])>35)&&((SXTzhongjian[jjj+1])<45))
             {
                zhongxiantingzhihang_flag=1;//����ֹͣ�б�־��1
                zhongxiantingzhihang=jjj+1; //����ֹͣ�о�Ϊȫ�ڵ�ǰһ��
                youxiaohangxiayihang_zhongxian=SXTzhongjian[jjj+1];//ȫ��ǰһ�е��м�
                youxiaohangxiayihang_zuobian=SXTzuobian[jjj+1];//ȫ��ǰһ�е���߱���
                youxiaohangxiayihang_youbian=SXTyoubian[jjj+1];//ȫ��ǰһ�е��ұ߱���
             if(zhongxiantingzhihang>20)//40  ������ֹͣ����С��Խ��Խ��ʱ��������ʮ�ֺ�ֱ��
               {
                 //��һ���Ѿ��Ҳ����ڱߣ��ұ߼�ȥ��ߵİ��߿�ȴ�����ͨ�İ��߿���ֲ���ȫ��ʱ
                if((SXTzuobian[jjj+1]==0)&&(SXTyoubian[jjj+1]-SXTzuobian[jjj+1]>40)&&(SXTyoubian[jjj+1]-SXTzuobian[jjj+1]<78))//  40  60
                {
                  
                  Zhijiao_zuoguai_flag=1;//�жϳ�ֱ��
                  Zhijiao_guai_count=32;//30
                }
               
               else if((SXTyoubian[jjj+1]==79)&&(SXTyoubian[jjj+1]-SXTzuobian[jjj+1]>40)&&(SXTyoubian[jjj+1]-SXTzuobian[jjj+1]<78))
                {
                  Zhijiao_youguai_flag=1;
                  Zhijiao_guai_count=32;//30
                }
               else
             {//led (LED1,LED_OFF);
            // led (LED2,LED_OFF);
             }
           
             }
             
             }
             
             
           }
       if((flag_youbianjie[jjj]==0)&&(flag_zuobianjie[jjj]==1))//�����ұ߽߱�Ļ�
           {
             // SXTyoubian[jjj]=(SXTzuobian[jjj]+SXTbaixiankuandu[jjj]);
           
           }
       else if((flag_youbianjie[jjj]==1)&&(flag_zuobianjie[jjj]==0))//������߽߱�Ļ�
          {
            
            // SXTzuobian[jjj]=(SXTyoubian[jjj]-SXTbaixiankuandu[jjj]);
          }
       else if((flag_youbianjie[jjj]==0)&&(flag_zuobianjie[jjj]==0))//�����߶����� ������ʮ�����������һ�֣����п�����бʮ��,jjj>15��ʾ�ų�̫Զ�Ĳ�ȷ������
         {
           
         //quanbai_flag=1;
         }
      flag_youbianjie[jjj]=0;
      flag_zuobianjie[jjj]=0;
      SXTzhongjian[jjj]=(int)((SXTzuobian[jjj]+SXTyoubian[jjj])/2);
      
   

   }

}


void guaidianpanduan(void)
{
int zzz;

guaidian_flag=0;    //�յ�flag���� ȷ��ÿ�� �����µ�flag�յ��ʶ
zhijiao_guaidian_flag=0;//ֱ�ǹյ�flag��ʶ����
for(zzz=59;zzz>10;zzz--)  //��59��ɨ���һ��
{
//if(zzz>10)//ǰ10��Ӧ�ò��ж�
 // {
     if(abs(SXTzuobian[zzz]-SXTzuobian[zzz-2])>5)//����ߺͼ�����е���� �������15�Ļ�   //��׼���ܽ����ߣ���4-----12
     {
       diyitiao_tiaobianhang=zzz;   //����ĵ�һ�� Ŀǰ����˫�ߵ��ߵ� ����ж�
      
       guaidian_flag=1;             //�յ�ı�ʶ��1
       if(SXTyoubian[zzz-1]>5&&SXTyoubian[zzz-1]<75)//���������ʱ���ұߵ�ǰһ��������һ����Χ�ڣ�����ֱ���ı�׼��Χ�Ļ�  10   69
          zhijiao_guaidian_flag=1;   //ֱ�ǹյ�flag��1
       
        break;
          
     }
     if(abs(SXTyoubian[zzz]-SXTyoubian[zzz-2])>5)//���ұߺͼ�����е��ұߣ��������15�Ļ�
     {
       diyitiao_tiaobianhang=zzz;   //����ĵ�һ��  Ŀǰ����˫�߽����ߵĿ�ʼ�ж�
       
       guaidian_flag=1;//�յ�ı�ʶ��1
        if(SXTzuobian[zzz-1]>5&&SXTzuobian[zzz-1]<75)//���ұ������ʱ�� ��ߴ�������һ����Χ�ڣ���ô����ֱ�ǵı�ʶ
           zhijiao_guaidian_flag=1; //ֱ�ǹյ�flag��1
        
        break;
     }
       
  //}
}

yihangheidian_count=0;
dierhangheidian_count=0;
zhongjianheidian=0;
//for(zzz=SXTzuobian[diyitiao_tiaobianhang+1];zzz<SXTyoubian[diyitiao_tiaobianhang+1];zzz++)
for(zzz=15;zzz<65;zzz++)
{
  if(imgyiwei[diyitiao_tiaobianhang-8][zzz]==0)
  {
    yihangheidian_count++;
   }
  if(imgyiwei[diyitiao_tiaobianhang-11][zzz]==0)
  {
    dierhangheidian_count++;
   }
  
}
for(zzz=25;zzz<55;zzz++)
{
   if(imgyiwei[diyitiao_tiaobianhang-11][zzz]==0)
  {
    zhongjianheidian=1;
    break;
    }
}


}


//void danshuangxianchuli(void)


//int SXT_chundan_flag_count,SXT_chunshuang_flag_count,SXT_dan_shuang_flag_count,SXT_shuang_dan_flag_count;
void bianxiantiqu(void)
{
 int i,j;
 SXTzhongjian[60]=40;//Ĭ���������м俪ʼ����ɨ��
if(SXT_chunshuang_flag||SXT_chunshuang_flag_count)
{
  if(SXT_chunshuang_flag_count>0)
       SXT_chunshuang_flag_count--; 
//led (LED1,LED_ON);
//led (LED2,LED_OFF);
//led (LED3,LED_OFF);
  
   shuangxianchuli();//��˫�ߴ��� ����Ҳ��ֱ�ǵ��жϣ�������˫�ߵİ취����������
   guaidianpanduan();//�յ�Ѱ�����ж�
   if(diyitiao_tiaobianhang>32&&diyitiao_tiaobianhang<59)//����յ����30
   {
      if(yihangheidian_count<1&&dierhangheidian_count<1)//�׵Ķ�ʮ���ж�
   {
   ;
   }
   else if((yihangheidian_count>=1&&yihangheidian_count<=10)&&(dierhangheidian_count>=1&&dierhangheidian_count<=10)&&zhongjianheidian==1)//��˫���ж�
   {
    SXT_chunshuang_flag=0;
    SXT_shuang_dan_flag=1;
    SXT_shuang_dan_flag_count=5;
    
    SXTzhongjian[33]=last_diyihang;
    SXTzhongjian[59]=last_dierhang;
    SXTzhongjian[52]=last_disanhang;
   }
   else if((yihangheidian_count>15&&yihangheidian_count<79)&&(dierhangheidian_count>15&&dierhangheidian_count<79))//����
   {
     ;
   }
 }

}

else if(SXT_shuang_dan_flag||SXT_shuang_dan_flag_count)
{
  if(SXT_shuang_dan_flag_count>0)
  SXT_shuang_dan_flag_count--;

//led (LED2,LED_ON);
//led (LED1,LED_OFF);
//led (LED3,LED_OFF);
  shuangxianchuli();//��˫�ߴ��� ����Ҳ��ֱ�ǵ��жϣ�������˫�ߵİ취����������  
  guaidianpanduan();//�յ�Ѱ�����ж�
  shuang_dan_chuli();//���滹������˫�ߴ��������˫�����ϵ��ߵ��������¶������
  if(diyitiao_tiaobianhang>58)
  {
   diyitiao_tiaobianhang=0;
   SXT_chundan_flag=1;
   SXT_chundan_flag_count=5;
   SXT_shuang_dan_flag=0;
   
   SXTzhongjian[33]=last_diyihang;
   SXTzhongjian[59]=last_dierhang;
   SXTzhongjian[52]=last_disanhang;
  }
 }
  else if(SXT_chundan_flag||SXT_chundan_flag_count)
  {
       if(SXT_chundan_flag_count>0)
           SXT_chundan_flag_count--;  
  
//led (LED3,LED_ON);
//led (LED1,LED_OFF);
//led (LED2,LED_OFF);
       danxianchuli();// ���߽��д��������˴���������µ����ߡ�
       dan_shuang_guaidianpanduan();

       if(danxianjinshuangxian_diyihang>32)
   {
   SXT_chundan_flag=0;
   SXT_dan_shuang_flag=1;
   SXT_dan_shuang_flag_count=5;
   
   SXTzhongjian[33]=last_diyihang;
   SXTzhongjian[59]=last_dierhang;
   SXTzhongjian[52]=last_disanhang;
}

}
else if(SXT_dan_shuang_flag||SXT_dan_shuang_flag_count)
{
if(SXT_dan_shuang_flag_count>0)
SXT_dan_shuang_flag_count--; 

//led (LED3,LED_ON);
//led (LED1,LED_ON);
//led (LED2,LED_ON);
danxianchuli();// ���߽��д��������˴���������µ����ߡ�
dan_shuang_guaidianpanduan();
dan_shaung_chuli();//�����������ж�
if(danxianjinshuangxian_diyihang>58)
 {
   danxianjinshuangxian_diyihang=0;
   SXT_chunshuang_flag_count=200;
   SXT_dan_shuang_flag=0;
   SXT_chunshuang_flag=1;
   
   SXTzhongjian[33]=last_diyihang;
   SXTzhongjian[59]=last_dierhang;
   SXTzhongjian[52]=last_disanhang;
 }
}


for(i=0;i<61;i++)
{
  last_SXTzhongjian[i]=SXTzhongjian[i];}

last_diyihang=SXTzhongjian[33];
last_dierhang=SXTzhongjian[59];
last_disanhang=SXTzhongjian[52];












/*if(danxianjinshuangxian_diyihang>59||DSJ_shuangxian_flag)//�����߽�˫�ߵ������ߴ���55��ʱ������˫��flagΪ1ʱ�����˫��
{
SXT_chunshuang_flag=1;
SXT_dan_shuang_flag=0;
shuangxianchuli();//��˫�ߴ���
DSJ_shuangxian_flag=1;//˫��flag��1
DSJ_danxian_flag=0;//����flag��0
}

if(!DSJ_danxian_flag){//�������flagΪ0���ǵ��������

shuangxianchuli();//˫�ߴ���




//for(zzz=59;zzz>zhongxiantingzhihang;zzz--)
for(zzz=59;zzz>0;zzz--)  //��59��ɨ���һ��
{
if(zzz>10)//ǰ10��Ӧ�ò��ж�
  {
     if(SXTzuobian[zzz]-SXTzuobian[zzz-3]>15||SXTzuobian[zzz]-SXTzuobian[zzz-3]<-15)//����ߺͼ�����е���� �������15�Ļ�
     {
       diyitiao_tiaobianhang=zzz;   //����ĵ�һ�� Ŀǰ����˫�ߵ��ߵ� ����ж�
      
       guaidian_flag=1;             //�յ�ı�ʶ��1
       if(SXTyoubian[zzz-1]>10&&SXTyoubian[zzz-1]<69)//���������ʱ���ұߵ�ǰһ��������һ����Χ�ڣ�����ֱ���ı�׼��Χ�Ļ�
          zhijiao_guaidian_flag=1;   //ֱ�ǹյ�flag��1
       
        break;
          
     }
     if(SXTyoubian[zzz]-SXTyoubian[zzz-3]>15||SXTyoubian[zzz]-SXTyoubian[zzz-3]<-15)//���ұߺͼ�����е��ұߣ��������15�Ļ�
     {
       diyitiao_tiaobianhang=zzz;   //����ĵ�һ��  Ŀǰ����˫�߽����ߵĿ�ʼ�ж�
       
       guaidian_flag=1;//�յ�ı�ʶ��1
        if(SXTzuobian[zzz-1]>10&&SXTzuobian[zzz-1]<69)//���ұ������ʱ�� ��ߴ�������һ����Χ�ڣ���ô����ֱ�ǵı�ʶ
           zhijiao_guaidian_flag=1; //ֱ�ǹյ�flag��1
        
        break;
     }
       
  }
}


}

//int SXT_chundan_flag,SXT_chunshuang_flag,SXT_dan_shuang_flag,SXT_shuang_dan_flag;
 if((diyitiao_tiaobianhang>=59||DSJ_danxian_flag)&&SXT_dan_shuang_flag)//�����һ�������б���˵�59�У���ô���봿����ģʽ
   {
     DSJ_shuangxian_flag=0;//˫�ߵ�flag��1
      DSJ_danxian_flag=1;//���ߵ�flag��1
      danxianchuli();// ���߽��д���
      
      SXT_dan_shuang_flag=0;
      SXT_chundan_flag=1;
   }
 else if(SXT_chundan_flag==0)
  {
      shuang_dan_chuli();
  }*/
}

void shuang_dan_chuli(void)
{
int iii0,iii1;
  int xundaodanbian_flag,zuoyoukuandu;
  zuoyoukuandu=15;
 xundaodanbian_flag=0;
 

for(iii0=diyitiao_tiaobianhang-1;iii0>10;iii0--)
{
  
   SXT_danxian_yousaomiao_flag=0;
   SXT_danxian_zuosaomiao_flag=0;
   
    for(iii1=SXTzhongjian[iii0+1];iii1>(SXTzhongjian[iii0+1]-zuoyoukuandu);iii1--)//���м俪ʼ���������
    {
      if((imgyiwei[iii0][iii1]==0))//����һ�ε��м俪ʼ�������������߲�����С��ȡ�  ������ܻ���һЩ�������⣬ע�⣡������
      {
        SXTzuobian[iii0]=iii1;
        SXT_danxian_zuosaomiao_flag=1;
        break;
      
      }
    }
    for(iii1=SXTzhongjian[iii0+1];iii1<(SXTzhongjian[iii0+1]+zuoyoukuandu);iii1++)
    {
      if((imgyiwei[iii0][iii1]==0))
      {
        SXTyoubian[iii0]=iii1;
        SXT_danxian_yousaomiao_flag=1;
        break;
      
      }
    }
    
    if(SXT_danxian_zuosaomiao_flag==1&&SXT_danxian_yousaomiao_flag==1)
    {
      SXTzhongjian[iii0]=(SXTzuobian[iii0]+SXTyoubian[iii0])/2;
    }
    else if(SXT_danxian_zuosaomiao_flag==1&&SXT_danxian_yousaomiao_flag==0)
    {
      SXTzhongjian[iii0]=SXTzuobian[iii0];
    }
    else if(SXT_danxian_zuosaomiao_flag==0&&SXT_danxian_yousaomiao_flag==1)
    {
      SXTzhongjian[iii0]=SXTyoubian[iii0];
    }
    else
    {
       /// SXTzhongjian[iii0]=SXTzhongjian[iii0+1];
      SXTzhongjian[iii0]=last_SXTzhongjian[iii0];
    }
   
    
    
    
    if(SXTzhongjian[iii0]-SXTzhongjian[iii0+1]!=0&&xundaodanbian_flag==0)
    {
       xundaodanbian_flag=1;
       zuoyoukuandu=6;
    }
    


  /* for(zzz=diyitiao_tiaobianhang+1;zzz>10;zzz--)//˫�߽�����ģʽ,�������һ�п�ʼ������
      {
           if(SXTyoubian[zzz]-SXTzuobian[zzz]>(SXTyoubian[diyitiao_tiaobianhang]-SXTzuobian[diyitiao_tiaobianhang])+5)//���������ְ��߿�ȽϿ��򱣳���һ�ε�����
                SXTzhongjian[zzz]=SXTzhongjian[zzz-1];//������һ������
           if(SXTzuobian[zzz]==SXTyoubian[zzz])//�����ߵ����ұ������ߵ���һ��
           {
                //SXTzhongjian[zzz]=SXTzhongjian[diyitiao_tiaobianhang];
                SXTzhongjian[zzz]=SXTyoubian[zzz];//���ߵ�������һ�ߣ���ʵ����������߱���͵�������һ��
            }
            if((SXTzhongjian[zzz]-SXTzhongjian[diyitiao_tiaobianhang]>12||SXTzhongjian[zzz]-SXTzhongjian[diyitiao_tiaobianhang]<-12))//��������м�ֵ�������5��ô�жϵ��߲���
            {
                //���߲��֣����߰���һ������ϡ� 
                if(abs(SXTzuobian[zzz]-SXTzhongjian[diyitiao_tiaobianhang+2])<12)//����м�����߽�����ô���߰����������ϡ�+2�Ƿ�ֹ�����в���׼ȷ�ж�����
                 {
                      SXTzhongjian[zzz]=SXTzuobian[zzz];
                 }
                if(abs(SXTyoubian[zzz]-SXTzhongjian[diyitiao_tiaobianhang+2])<12)//����м����ұ߽�����ô���߰����ұ������
                 {
                      SXTzhongjian[zzz]=SXTyoubian[zzz];
                 }
            }
           if(abs(SXTzhongjian[zzz]-SXTzhongjian[zzz+1])>5)
           {SXTzhongjian[zzz]=last_SXTzhongjian[zzz];}
      }*/

}



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
{int xxx;
  
   //led (LED3,LED_OFF);
  
   Zhijiao_guai_count=0;
   DSJ_SXT_zhongjian_count=0;
  for(xxx=25;xxx<60;xxx++)
  {
     DSJ_SXT_zhongjian_count+=SXTzhongjian[xxx];
     }
  DSJ_zhongjian_ave=DSJ_SXT_zhongjian_count/35;
  DSJ_ave_piancha=DSJ_zhongjian_ave-39;
    //
  
DSJ_XL=(float)(SXTzhongjian[33]-SXTzhongjian[59])/20.0;
DSJ_YXH=(SXTzhongjian[52]-39);//��ʮ����Ч��

current_deviation=(int)(12*DSJ_XL+0.8*DSJ_YXH);//14  0.5 32
//11 0.9 23-24  
  //}
  //current_deviation=(int)(0.8*(SXTzhongjian[30]-SXTzhongjian[45])/15+1.2*(SXTzhongjian[52]-40));
 }

 




void DST_SXT_duojizhuanxiang(int err)
{
er=err;
Der=last_err-er;
DST_SXT_kongzhi=(int)(steer_mid-(DST_SXT_duoji_kp*er/10)+DST_SXT_duoji_kd*Der);
if(DST_SXT_kongzhi>steer_max)
DST_SXT_kongzhi=steer_max;
if(DST_SXT_kongzhi<steer_min)
DST_SXT_kongzhi=steer_min;
last_err=er;
ftm_pwm_duty(FTM1, FTM_CH0,DST_SXT_kongzhi);
  
}






