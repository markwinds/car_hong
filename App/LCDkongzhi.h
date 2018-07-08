#ifndef _LCDkongzhi_H
#define _LCDkongzhi_H
#include "include.h"
/**********************LCD���ܱ�־λ******************************/
extern uint8 flag_LCD;                         //LCD�����־
extern uint8 flag_LCD_revise;                  //resive�����޸�ѡ��
extern uint8 flag_LCD_queren;                  //ȷ�ϱ�־λ

extern uint8 flag_LCD_first;                      //first����
extern unsigned char select_tm[10]; 
extern unsigned char flag_tubiao_viewm[10];
extern unsigned int flag_gundongs[10];
extern uint8 flag_selectm;                     //Һ��ѡ���־
extern uint8 flag_gundongm;                    //Һ�����ع�����־

extern s16 piancha_lcd;
extern int DCsignal[4];

extern uint8 flag_blueteethope;                  //����Сͼ����ʾ��־
extern uint8 flag_stop;                           //ͣ��Сͼ���־������ͣ���Ƿ���Ʊ�־


extern int keyceshi;
extern uint8 img[CAMERA_W*CAMERA_H];                           //����ӥ������ͷ��һ�ֽ�8�����أ������Ҫ��ѹΪ 1�ֽ�1�����أ����㴦��
//extern uint8 imgyiwei[CAMERA_W][CAMERA_H]; 
extern uint8 imgyiwei[60][80]; 




extern int MMA7361_sj;
extern int GYRO_X;
extern int GYRO_Y;

typedef struct
{
  u16 CCD1_int;           
  char CCD1_char[4];
  u16 CCD2_int;
  char CCD2_char[4];
  u16 CCD3_int;
  char CCD3_char[4];
  u16 CCD4_int;
  char CCD4_char[4];
   u16 CCD5_int;
  char CCD5_char[4];
    u16 CCD6_int;
  char CCD6_char[4];
  
}CCDxianshi;

extern CCDxianshi CCD_LIVE_WATCH;      


/*************************END************************/
void zhujiemian(void);
void LCD_view(void);
void diyihangview(void);

void ceshi_piancha(void);
void LCD_6x8StrtoBMPL(unsigned char x,unsigned char y,signed char ch[],unsigned char z);
void xiaoche_lock(void) ;
void clear_drawpotm_k60(void);
void ceshi_stop(void);


void dijiujie_speed_tiaoshi(void);
int Backtom(int flag,int k);

void ceshi_tuxiangxianshi(void);
int Parameterset(int p);  

int Parameterset20(int p);   
//����set
void ceshi_speedlevel(void);

void dijiujie_speed_tiaoshi2(void);
void LCDcanshuchushihua();
void DMX_chengxuchushihua();
void DSYJzhilishujuxianshi();
void OLED_flash_memories();//flashд����ʾ
void OLED_flash_memories_queren();//flashд����ʾ
void OLED_starting_car();//flashд����ʾ
void OLED_start_finish();//flashд����ʾ
void OLED_speed_set();//flashд����ʾ
void VIEW_CCD_dongtai(u8 x[]);
#endif