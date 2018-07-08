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


void get_maichong(void)//获取速度
{
    speed_a=-FTM1_CNT;
    FTM1_CNT=0;

}
  /*******************************************************12届电机正反转及差速子函数*****************************************************/  

void DSYJ_dianji_fanzhuan(int zhankongbi)//zhankongbi 0-10000反转
{
    ftm_pwm_duty(FTM2,FTM_CH0,0);  //电机
    ftm_pwm_duty(FTM2,FTM_CH1,zhankongbi);   

}

void DSYJ_dianji_zhengzhuan(int zhankongbi )//zhankongbi 0-10000正转
{
    ftm_pwm_duty(FTM2,FTM_CH0,zhankongbi); // 电机
    ftm_pwm_duty(FTM2,FTM_CH1,0);   


}


  /*******************************************************速度控制*****************************************************/  

int MC_piancha,d_MC_piancha,last_MC,NOW_SPEED=0;
int dianji_kp,dianji_kd;
int dianji_zhankongbi,last_dianji_zhankongbi,CS=11;
extern char pof,shizi_flag;
void dianji_canshu_init(void)//电机参数初始化
{
      MC_piancha=0;
      d_MC_piancha=0;
      last_MC=0;
      dianji_kp=40;
      dianji_kd=25;
      dianji_zhankongbi=0;
      last_dianji_zhankongbi=0;
}

void DSYJ_dianji_PID(int QWMC)//速度PID控制
{
 
            NOW_SPEED=speed_a;//
        
        //********************设置反转力度**************//

        int dut,men;
       if(guai_flag)//圆环开始拐弯了
       {
          dut=4500;//反转力度为45%
          men=0;//目标速度-实际速度
        }
        else
        
          if(zhangaijishileft_flag||zhangaijishiright_flag)//障碍
         {
               dut=1000;//反转力度为10%
                men=-6;//目标速度-实际速度
          }else
          if(LK_yanshi>30&&NOW_SPEED>6)//检测到起跑线后延时150ms后且当前速度大于6
          {
                  dut=2000;//反转力度20%，反转最多为30%占空比，用于停车距离控制
                  men=-4;
          }
          else
          if(pof)//坡道
           {
                dut=1000;
                men=-5;
          }
          else
          if(zhidao_flag>20)//长直道
          {
              zhidao_ruwan_flag=0;
              dut=0;//3000
              men=-10;
          }
          else
          if(zhidao_ruwan_flag)//直道入弯
          {
              dut=0;//最大3000
                men=0;
          }
          else//其他弯道
          {
            dut=0;//1000
            men=-10;
           }
        
        if(yunsu_flag&&!star_lineflag)//匀速
        {
              dut= 0;//1000
              men=-10;
        }
        
        
        //***************电机控制pid公式****************************//
        MC_piancha=QWMC-NOW_SPEED;//脉冲偏差=期望脉冲-实际脉冲
        d_MC_piancha=MC_piancha-last_MC;
        last_MC=MC_piancha;
        dianji_zhankongbi=last_dianji_zhankongbi+dianji_kp*MC_piancha+dianji_kd*d_MC_piancha;
        if(dianji_zhankongbi>7000)
          dianji_zhankongbi=7000; 
        if(dianji_zhankongbi<0)
          dianji_zhankongbi=0; 
        last_dianji_zhankongbi=dianji_zhankongbi;
        
        
        if(MC_piancha<men)//实际速度和期望速度差值小于设定的门槛
        DSYJ_dianji_fanzhuan(dut);//安照设定的占空比反转
          else 
            if(MC_piancha>6)//如果期望速度比实际速度大6以上，就直接控制电机猛转加速
              DSYJ_dianji_zhengzhuan(5500);//bangbang控制算法
          else
        DSYJ_dianji_zhengzhuan(last_dianji_zhankongbi);//否则通过pid调节

}


void lukuangudge()//路况判断
{
   if(zhangaijishileft_flag||zhangaijishiright_flag)//障碍
   {
     mubiao_speed=dawan_speed;//减速
     dawan_flag=0;
   }
   else
    if(pof)//坡道
{
 // gpio_set(PTE1,1);
    zhidao_flag=0;
    mubiao_speed=60;
}
else
if(S>25)//小s弯
 {
      mubiao_speed=S_speed;
 }else
  if(zhidao_flag>13)//长直道
  {
      mubiao_speed=long_speed;      
      dawan_flag=0;
    // gpio_set(PTE1,1);
  }
  else
   
if(qvlv_quanju>12&&qvlv_quanju<=25&&abs(my_piancha)<=21&&abs(my_piancha)>=13)//小弯
{ 
  //gpio_set(PTE1,1);
    mubiao_speed=dawan_speed;
    dawan_flag=0;
}
else
 if(qvlv_quanju>25||abs(my_piancha)>21||duandian>10)//大弯
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
 if(NOW_SPEED>dawan_speed+10&&qulv_yuandaun>13&&qulv_jinduan<6)//高速直道入大弯
 {
   zhidao_flag=0;
  // led(LED0, LED_OFF);//提示关闭
   dawan_flag=0;
   zhidao_ruwan_flag=1;
   mubiao_speed=dawan_speed;//目标速度直接等于大弯速度
 }
}