#include "include.h"
#include "common.h"
//extern uint8 img[CAMERA_W*CAMERA_H];                           //����ӥ������ͷ��һ�ֽ�8�����أ������Ҫ��ѹΪ 1�ֽ�1�����أ����㴦��
//extern uint8 imgyiwei[CAMERA_W][CAMERA_H]; 
//extern uint8 imgyiwei[60][80];
extern int flag_stop_time,flag_stop_miaoshu;
extern int FCDC_flag_zhidao,FCDC_flag_querenzhidao,FCDC_time_querenzhidao,FCDC_flag_zhidao;
extern int flag_stopx,piancha,FCDC_flag_wandao,FCDC_podao_flag,FCDC_podao_speed,FCDC_zhidao_speed;
extern int FCDC_xiaowan,FCDC_huanwan_speed,FCDC_jiwan_speed,FCDC_xiaowan,FCDC_huanwan_speed,FCDC_huanwan_chasu,FCDC_jiwan_chasu;
void speedcontrol(void);
void DSJ_speed_canshu(void);