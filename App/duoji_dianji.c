#include "include.h"
#include "common.h"
int dawan_speed=137;
int long_speed=147;
int S_speed=147;
s16 speed_a,speed_b;
extern int LK_yanshi,zhidao_flag,duandian,qulv_yuandaun,qulv_jinduan,qvlv_quanju,my_piancha,star_lineflag,zhangaijishileft_flag,zhangaijishiright_flag;
int podao_flag,mubiao_speed;
char dawan_flag,zhidao_ruwan_flag;
extern char S,guai_flag;


void get_maichong(void)//��ȡ�ٶ�
{
    speed_a=-FTM1_CNT;
    FTM1_CNT=0;

}
  /*******************************************************12��������ת�������Ӻ���*****************************************************/  

void DSYJ_dianji_fanzhuan(int zhankongbi)//zhankongbi 0-10000��ת
{
    ftm_pwm_duty(FTM2,FTM_CH0,0);  //���
    ftm_pwm_duty(FTM2,FTM_CH1,zhankongbi);   

}

void DSYJ_dianji_zhengzhuan(int zhankongbi )//zhankongbi 0-10000��ת
{
    ftm_pwm_duty(FTM2,FTM_CH0,zhankongbi); // ���
    ftm_pwm_duty(FTM2,FTM_CH1,0);   


}


  /*******************************************************�ٶȿ���*****************************************************/  

int MC_piancha,d_MC_piancha,last_MC,NOW_SPEED=0;
int dianji_kp,dianji_kd;
int dianji_zhankongbi,last_dianji_zhankongbi,CS=11;
extern char pof,shizi_flag;
void dianji_canshu_init(void)//���������ʼ��
{
      MC_piancha=0;
      d_MC_piancha=0;
      last_MC=0;
      dianji_kp=40;
      dianji_kd=25;
      dianji_zhankongbi=0;
      last_dianji_zhankongbi=0;
}

void DSYJ_dianji_PID(int QWMC)//�ٶ�PID����
{
 
            NOW_SPEED=speed_a;//
        
        //********************���÷�ת����**************//

        int dut,men;
       if(guai_flag)//Բ����ʼ������
       {
          dut=4500;//��ת����Ϊ45%
          men=0;//Ŀ���ٶ�-ʵ���ٶ�
        }
        else
        
          if(zhangaijishileft_flag||zhangaijishiright_flag)//�ϰ�
         {
               dut=1000;//��ת����Ϊ10%
                men=-6;//Ŀ���ٶ�-ʵ���ٶ�
          }else
          if(LK_yanshi>30&&NOW_SPEED>6)//��⵽�����ߺ���ʱ150ms���ҵ�ǰ�ٶȴ���6
          {
                  dut=2000;//��ת����20%����ת���Ϊ30%ռ�ձȣ�����ͣ���������
                  men=-4;
          }
          else
          if(pof)//�µ�
           {
                dut=1000;
                men=-5;
          }
          else
          if(zhidao_flag>20)//��ֱ��
          {
              zhidao_ruwan_flag=0;
              dut=0;//3000
              men=-10;
          }
          else
          if(zhidao_ruwan_flag)//ֱ������
          {
              dut=0;//���3000
                men=0;
          }
          else//�������
          {
            dut=0;//1000
            men=-10;
           }
        
        if(yunsu_flag&&!star_lineflag)//����
        {
              dut= 0;//1000
              men=-10;
        }
        
        
        //***************�������pid��ʽ****************************//
        MC_piancha=QWMC-NOW_SPEED;//����ƫ��=��������-ʵ������
        d_MC_piancha=MC_piancha-last_MC;
        last_MC=MC_piancha;
        dianji_zhankongbi=last_dianji_zhankongbi+dianji_kp*MC_piancha+dianji_kd*d_MC_piancha;
        if(dianji_zhankongbi>7000)
          dianji_zhankongbi=7000; 
        if(dianji_zhankongbi<0)
          dianji_zhankongbi=0; 
        last_dianji_zhankongbi=dianji_zhankongbi;
        
        
        if(MC_piancha<men)//ʵ���ٶȺ������ٶȲ�ֵС���趨���ż�
        DSYJ_dianji_fanzhuan(dut);//�����趨��ռ�ձȷ�ת
          else 
            if(MC_piancha>6)//��������ٶȱ�ʵ���ٶȴ�6���ϣ���ֱ�ӿ��Ƶ����ת����
              DSYJ_dianji_zhengzhuan(5500);//bangbang�����㷨
          else
        DSYJ_dianji_zhengzhuan(last_dianji_zhankongbi);//����ͨ��pid����

}


void lukuangudge()//·���ж�
{
   if(zhangaijishileft_flag||zhangaijishiright_flag)//�ϰ�
   {
     mubiao_speed=dawan_speed;//����
     dawan_flag=0;
   }
   else
    if(pof)//�µ�
{
 // gpio_set(PTE1,1);
    zhidao_flag=0;
    mubiao_speed=60;
}
else
if(S>25)//Сs��
 {
      mubiao_speed=S_speed;
 }else
  if(zhidao_flag>13)//��ֱ��
  {
      mubiao_speed=long_speed;      
      dawan_flag=0;
    // gpio_set(PTE1,1);
  }
  else
   
if(qvlv_quanju>12&&qvlv_quanju<=25&&abs(my_piancha)<=21&&abs(my_piancha)>=13)//С��
{ 
  //gpio_set(PTE1,1);
    mubiao_speed=dawan_speed;
    dawan_flag=0;
}
else
 if(qvlv_quanju>25||abs(my_piancha)>21||duandian>10)//����
{
  
 //gpio_set(PTE1,1);
  if(NOW_SPEED==dawan_speed)
      zhidao_ruwan_flag=0;
      dawan_flag=1;
    mubiao_speed=dawan_speed;
 }
 else
 {
  //gpio_set(PTE1,0);
     dawan_flag=0;
  // zhidao_ruwan_flag=0;
    mubiao_speed=dawan_speed;
 }
 if(NOW_SPEED>dawan_speed+10&&qulv_yuandaun>13&&qulv_jinduan<6)//����ֱ�������
 {
   zhidao_flag=0;
  // led(LED0, LED_OFF);//��ʾ�ر�
   dawan_flag=0;
   zhidao_ruwan_flag=1;
   mubiao_speed=dawan_speed;//Ŀ���ٶ�ֱ�ӵ��ڴ����ٶ�
 }
}