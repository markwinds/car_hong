#include "include.h"
#include "common.h"
//uint8 img[CAMERA_W*CAMERA_H];                           //����ӥ������ͷ��һ�ֽ�8�����أ������Ҫ��ѹΪ 1�ֽ�1�����أ����㴦��
//uint8 imgyiwei[60][80];

int flag_stop_time,flag_stop_miaoshu;
int FCDC_flag_zhidao,FCDC_flag_querenzhidao,FCDC_time_querenzhidao,FCDC_flag_zhidao;
int flag_stopx,piancha,FCDC_flag_wandao,FCDC_podao_flag,FCDC_podao_speed,FCDC_zhidao_speed;
int FCDC_xiaowan,FCDC_huanwan_speed,FCDC_jiwan_speed,FCDC_xiaowan,FCDC_huanwan_speed,FCDC_huanwan_chasu,FCDC_jiwan_chasu;
              

void DSJ_speed_canshu(void)
{
FCDC_zhidao_speed=75;  //70    80 70  70  240 240 33  /90 80 75 240 240 35/
FCDC_huanwan_speed=75;//65
FCDC_jiwan_speed=75;//60
FCDC_huanwan_chasu=220;//
FCDC_jiwan_chasu=250;//
//FCDC_podao_speed=40;
DST_SXT_duoji_kp=360;
}




void speedcontrol(void)
{
  
  
             // if((GPIO_Get(PORTB,3)==0)&&(flag_stop_miaoshu>10))
       if((flag_stop_miaoshu>20))////////////////////////////////////////////////////////////////////////////////////////
              flag_stopx=1;
  
  
                flag_stop_time++;        //LED�ر� С��׼��������ʼ��ʱͣ��ʱ�䡣
              if(flag_stop_time>200)     //1S 250
                   {
                       flag_stop_miaoshu++;
                       flag_stop_time=0;
                   }  
              
              
              if(FCDC_flag_zhidao==1&&FCDC_flag_querenzhidao==0)       //ֱ����־=1  ȷ��ֱ��=0��
                  FCDC_time_querenzhidao++;                             //time++  ÿ4ms ��һ��
              else
                  FCDC_time_querenzhidao=0;
         
         
              if(FCDC_time_querenzhidao>100&&FCDC_flag_zhidao==1)                        //400msֱ��ȷ��  ֮�� ȷ����ֱ��
               {
                    FCDC_flag_querenzhidao=1;
               }
              
              
              
               piancha=danxian_piancha;
               // if(flag_stopx&&flag_stop)    
               if(flag_stopx)       //ͣ��  Һ��ͣ��+�ﵽͣ��Ҫ�󣨳���һ��ʱ����Ҽ�⵽�����ߣ�
                {
                          dianji_PID_zuo(0);    //6.28  --75     //65
                          dianji_PID_you(0);    //6.28  --64     //54
                }
               else
               {
                    if((danxian_piancha>-5)&&(danxian_piancha<5))// ֱ��  
                    {
                        FCDC_flag_zhidao=1;
                        FCDC_flag_wandao=0; //ֱ����־λΪ1�����Ϊ0
                        if(FCDC_flag_querenzhidao)//�����ĳ�ֱ��
                          {
                             if(FCDC_podao_flag)//�µ�
                             {
                                dianji_PID_zuo(FCDC_podao_speed);    //6.28  --75     //65
                                dianji_PID_you(FCDC_podao_speed);    //6.28  --64     //54
                             }
                             else//��ֱ��
                             { 
                               dianji_PID_zuo(FCDC_zhidao_speed);    //6.28  --75     //65
                               dianji_PID_you(FCDC_zhidao_speed);    //6.28  --64     //54
                           }
                          }
                        else//����ж��ݵ�����ֱ�����ٶȰ�������ٶ�����
                           {
                             if(FCDC_xiaowan)//����
                                {
                                   dianji_PID_zuo(FCDC_huanwan_speed);    //6.28  --75     //65
                                   dianji_PID_you(FCDC_huanwan_speed);    //6.28  --64     //54
                                }
                            else//����
                                {
                                   dianji_PID_zuo(FCDC_jiwan_speed);    //6.28  --75     //65
                                   dianji_PID_you(FCDC_jiwan_speed);    //6.28  --64     //54
                                }
                           }
                          
                      
                    }
                    else                   //���
                    { 
                       if(danxian_piancha>=5)     //��ת
                       {
                            FCDC_flag_zhidao=0;
                            FCDC_flag_wandao=1;    //�����־��1��ֱ����־��0
                           if(danxian_piancha<15)
                            {
                              FCDC_xiaowan=1; 
                             dianji_PID_zuo(FCDC_huanwan_speed-piancha*FCDC_huanwan_chasu/1000);    //6.28  --75     //65
                             dianji_PID_you(FCDC_huanwan_speed);  
                            }
                           else
                           {
                              FCDC_xiaowan=0; 
                               dianji_PID_zuo(FCDC_jiwan_speed-piancha*FCDC_jiwan_chasu/1000);    //6.28  --75     //65
                               dianji_PID_you(FCDC_jiwan_speed);  
                           }
                       }
                       else if(danxian_piancha<-5)  //��ת
                       {
                            FCDC_flag_zhidao=0;
                            FCDC_flag_wandao=1;
                           if(danxian_piancha>-15)
                           {
                             FCDC_xiaowan=1;
                              dianji_PID_zuo(FCDC_huanwan_speed);    //6.28  --75     //65
                             dianji_PID_you(FCDC_huanwan_speed+piancha*FCDC_huanwan_chasu/1000); 
                           }
                           else
                           {
                             FCDC_xiaowan=1;
                              dianji_PID_zuo(FCDC_jiwan_speed);    //6.28  --75     //65
                          dianji_PID_you(FCDC_jiwan_speed+piancha*FCDC_jiwan_chasu/1000); 
                           }
                           
                       }
                    
                    }
                    
    
                 }  
              
              
              
              
              
              
              
}