//���ߣ�
//˵����saomiao�ļ�����һ��lkcongzhongjiansaomiao����������ͼ��������ƫ����Լ�������ƾ��ڴ��ļ���
//duoji_dianji�ļ��¶����ٶȿ��Ƶ���س��򣬺��ĳ�������������ļ�
#include "common.h"
#include "include.h"
#include "math.h"
#include "saomiao.h"
uint8 imgbuff[CAMERA_SIZE];     
 int currentzhongjian[60];
 int right_heixian[60];
 int left_heixian[60];
int quanjuCount;
int OutData[4],tuoluoyivar;
int star_lineflag=0;
int LK_jishi=0;
int LK_jishi_flag=0;
int LK_yanshi=0,zhidao_flag,yunsu_flag,yuzhi;
extern int podao_flag,zhangai_right,zhangai_left,qvlv_quanju,duandian,mubiao_speed,dawan_speed,qulv_jinduan;
extern void  lukuangudge();
char go=0,S1,S,zhichong_flag;
extern char lcd_show_enable1;
extern char jiji;

//s16 speed_a;
extern int my_piancha;
int zhangaijishiright_flag=0,zhangaijishileft_flag=0;
//int kp=22,kd=10,right_heixian[60],lastpiancha_1,duojijiaodu,left_heixian[60],my_lastzhongjian=40,currentzhongjianzhi=40,rightheixian_flag,leftheixian_flag,xielv;
//��������
void PORTA_IRQHandler();
void DMA0_IRQHandler();
void PIT0_IRQHandler();
void Priority_Set();
extern char s_wan_flag;
 char pof;
//void PIT1_IRQHandler();
/*!
 *  @brief      main����
 *  @since      v5.3
 *  @note       ɽ�� DMA �ɼ�����ͷ ʵ��
                ע�⣬������ busƵ����Ϊ100MHz(50MHz busƵ�ʻ�̫��������û����ʱ�ɼ�ͼ��)

                ������ʹ�õ���λ��Ϊ��ɽ��๦�ܵ������֡�
                ����������ο���ɽ��๦�ܵ�����������ר��
                                http://www.vcan123.com/forum.php?mod=collection&action=view&ctid=27
 */
void hecheng()//�������ߺ���
{
    unsigned int ji;
    for(ji=0;ji<=59;ji++)
          {
          imgyiwei[ji][currentzhongjian[ji]]=0 ;
          }
    }
    void sendimg(uint8 *imgaddr,uint32 imgsize)
    {
    img_extract((u8 *)imgyiwei, imgbuff,CAMERA_SIZE);      //��ѹͼ��
    lkcongzhongjiansaomiao();
    uint8 cmd[4] = {0, 255, 1, 0 };    //yy_����ͷ���ڵ��� ʹ�õ�����
    hecheng();
    uart_putbuff(VCAN_PORT, cmd, sizeof(cmd));    //�ȷ�������
    uart_putbuff(VCAN_PORT, imgaddr, imgsize); //�ٷ���ͼ��
}




void star_line_judg()//�����߼�� 
{
    int kk,bai_flag=0,hei_flag=0,heibai_flag=0,baihei_flag=0;
      for(kk=5;kk<=72;kk++)
      {
        if(imgyiwei[45][kk]>0)
          bai_flag=1;
        else
        if(bai_flag&&imgyiwei[45][kk]==0)
        {
          baihei_flag++;
          bai_flag=0;
        }
        
        if(imgyiwei[45][kk]==0)
          hei_flag=1;
        else
        if(hei_flag&&imgyiwei[45][kk]>0)
        {
          heibai_flag++;
          hei_flag=0;
        }
          
      }
      if(baihei_flag>=4&&heibai_flag>=4&&baihei_flag-heibai_flag<=2)
        star_lineflag=1;
}


void lkzhongjian()
{
  unsigned int i;
 for(i=0;i<=59;i++)
  { 
    imgyiwei[i][currentzhongjian[i]]=0;

  }
 
 
}
/*void sendimg(uint8 *imgaddr,uint32 imgsize)
{
 
        uint8 cmd[4] = {0, 255, 1, 0 };    //yy_����ͷ���ڵ��� ʹ�õ�����
        //hecheng()��
        uart_putbuff(VCAN_PORT, cmd, sizeof(cmd));    //�ȷ�������

      uart_putbuff(VCAN_PORT, imgaddr, imgsize); //�ٷ���ͼ��
          // uart_putbuff(VCAN_PORT, currentzhongjian, 60); //�ٷ���ͼ��
    }*/
    //**************************************************************************
    /*
    *  ����˵����SCIʾ����CRCУ��
      �ڲ����ú���

    //**************************************************************************
    static unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT)
    {
        unsigned short CRC_Temp;
        unsigned char i,j;
        CRC_Temp = 0xffff;

        for (i=0;i<CRC_CNT; i++)
        {
            CRC_Temp ^= Buf[i];
            for (j=0;j<8;j++) {
                if (CRC_Temp & 0x01)
                    CRC_Temp = (CRC_Temp >>1 ) ^ 0xa001;
                else
                    CRC_Temp = CRC_Temp >> 1;
            }
        }
        return(CRC_Temp);
}

//************************************************
//
/*
*  ����˵����SCIʾ�������ͺ���
   
*/
//****************************************************
void OutPut_Data(void)
{   
    int temp[4] = {0};
    unsigned int temp1[4] = {0};
    unsigned char databuf[10] = {0};
    unsigned char i;
    unsigned short CRC16 = 0;
    for(i=0;i<4;i++)
    {
        temp[i]  = (int)OutData[i];
        temp1[i] = (unsigned int)temp[i];

    }

    for(i=0;i<4;i++)
    {
        databuf[i*2]   = (unsigned char)(temp1[i]%256);
        databuf[i*  2+1] = (unsigned char)(temp1[i]/256);
    }

    CRC16 = CRC_CHECK(databuf,8);
    databuf[8] = CRC16%256;
    databuf[9] = CRC16/256;

    for(i=0;i<10;i++)
    {
        uart_putchar (UART0,(char)databuf[i]);
    }
}


void SendHex(unsigned char hex) {
  unsigned char temp;
  temp = hex >> 4;
  if(temp < 10) {
    uart_putchar(UART0,temp + '0');
  } else {
    uart_putchar(UART0,temp - 10 + 'A');
  }
  temp = hex & 0x0F;
  if(temp < 10) {
    uart_putchar(UART0,temp + '0');
  } else {
   uart_putchar(UART0,temp - 10 + 'A');
  }
}

void SendImageData(unsigned char ImageData[][80]) 
{
  

          int lll1,lll2;
          unsigned char crc = 0;
      lkcongzhongjiansaomiao();
      lkzhongjian();
          /* Send Data */
          uart_putchar(UART0,'*');
          uart_putchar(UART0,'L');
          uart_putchar(UART0,'D');

          SendHex(0);
          SendHex(0);
          SendHex(0);
          SendHex(0);
          
        //  imgyiwei[60][80]; 

          for(lll2=0;lll2<80;lll2++)
          {
            
            for(lll1=0;lll1<60; lll1++)
              SendHex(ImageData[lll1][lll2]);
          }
          
          
        /* for(ll1=0;ll1<60;ll1++)
      {
        for(ll0=0;ll0<80;ll0++) 
        {
        if(imgyiwei[ll1][ll0]==0)
            Draw_potL(ll0,ll1,0,1);
          else
            Draw_potL(ll0,ll1,1,1);
        }
      }*/
          

          SendHex(crc);
          uart_putchar(UART0,'#');
}

#if 0
//��������ʼ��
void FTM_QUAD_init()
{
          /*�����˿�ʱ��*/
          SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;

          /*ѡ��ܽŸ��ù���*/
        // PORTA_PCR12 = PORT_PCR_MUX(7);
        // PORTA_PCR13 = PORT_PCR_MUX(7);
          PORTA_PCR10 = PORT_PCR_MUX(6);
          PORTA_PCR11 = PORT_PCR_MUX(6);

          /*ʹ��FTM1��FTM2ʱ��*/
        // SIM_SCGC6|=SIM_SCGC6_FTM1_MASK;
          SIM_SCGC3|=SIM_SCGC3_FTM2_MASK;

        //  FTM1_MOD = 65535; //�ɸ�����Ҫ����
          FTM2_MOD = 65535;

        //  FTM1_CNTIN = 0;
          FTM2_CNTIN = 0;

        //  FTM1_MODE |= FTM_MODE_WPDIS_MASK; //��ֹд����
          FTM2_MODE |= FTM_MODE_WPDIS_MASK; //��ֹд����
        //  FTM1_MODE |= FTM_MODE_FTMEN_MASK; //FTMEN=1,�ر�TPM����ģʽ������FTM���й���
          FTM2_MODE |= FTM_MODE_FTMEN_MASK; //FTMEN=1,�ر�TPM����ģʽ������FTM���й���

        //  FTM1_QDCTRL &= ~FTM_QDCTRL_QUADMODE_MASK; //ѡ������ģʽΪA����B�����ģʽ
        //  FTM1_QDCTRL |= FTM_QDCTRL_QUADEN_MASK; //ʹ����������ģʽ
        //  FTM2_QDCTRL &= ~FTM_QDCTRL_QUADMODE_MASK; //ѡ������ģʽΪA����B�����ģʽ   0x8u  0x00001000ȡ���� 0x11110111
        FTM2_QDCTRL |= 0x08;//~0x00u; 
          
          FTM2_QDCTRL |= FTM_QDCTRL_QUADEN_MASK; //ʹ����������ģʽ
      //QUADMODE=1;
      //   FTM1_SC |= FTM_SC_CLKS(3);  //ѡ���ⲿʱ��
      //   FTM1_CONF |=FTM_CONF_BDMMODE(3); //�ɸ�����Ҫѡ��
          FTM2_SC |= FTM_SC_CLKS(3);
      //   FTM2_CONF |=FTM_CONF_BDMMODE(3);

}
#endif
//**************************************************************************

/**********************************�������************************************/
void  main(void)
{
    DisableInterrupts; 
    

    dianji_canshu_init();      //���������ʼ��

    Priority_Set();           //�ж����ȼ�����
    camera_init(imgbuff);                                  //�����趨  imgbuff Ϊ�ɼ�������������������

    
    //ftm_pwm_init(FTM2,FTM_CH0,10000,0);  //�����ʼ��  FTM2
    //ftm_pwm_init(FTM2,FTM_CH1,10000,0);
    
    
    ftm_pwm_init(FTM0,FTM_CH6,300,4200);//�����ʼ��  FTM0
       
    ftm_quad_init(FTM1);//��������ʼ��    FTM1

   
    pit_init_ms(PIT0,5);//��ʱ���ж�5ms  ����ʱ����5msһ��
    
     my_lcd_init();//Һ����ʼ��
    
    set_vector_handler(PIT0_VECTORn,PIT0_IRQHandler);   // �����жϷ��������ж���������
    enable_irq(PIT0_IRQn);                             // ʹ��PIT�ж�
    set_vector_handler(PORTA_VECTORn,PORTA_IRQHandler);    //����PORTA���жϷ�����Ϊ PORTA_IRQHandler
    set_vector_handler(DMA0_VECTORn,DMA0_IRQHandler);      //����DMA0���жϷ�����Ϊ DMA0_IRQHandler

    EnableInterrupts;	 
   //  adc_init (ADC1_SE4a);
  

    Site_t site1;                           //��ʾͼ�����Ͻ�λ��
    site1.x=15;
    site1.y=15;
  
    while(1)
    { 
     LCD_num(site1,jiji,BLUE,WHITE);
      camera_get_img();

     if(LK_jishi_flag==1)
      star_line_judg();
     
     //sendimg((u8 *)imgyiwei, CAMERA_W * CAMERA_H);//�ҵ���λ������ע��Ϊ����Է���ͼ��
    }
}

/*!
 *  @brief      PORTA�жϷ�����
 *  @since      v5.0
 */
void PORTA_IRQHandler()
{
        uint8  n = 0;    //���ź�
        uint32 flag = PORTA_ISFR;
        PORTA_ISFR  = ~0;                                   //���жϱ�־λ

        n = 29;                                             //���ж�
        if(flag & (1 << n))                                 //PTA29�����ж�
        {
            camera_vsync();
        }
    #if 0             //ӥ��ֱ��ȫ�ٲɼ�������Ҫ���ж�
        n = 28;
        if(flag & (1 << n))                                 //PTA28�����ж�
        {
            camera_href();
        }
    #endif
}

/*!
 *  @brief      DMA0�жϷ�����
 *  @since      v5.0
 */
//void PIT1_IRQHandler()
//{
//shizi_count++;
//}
void DMA0_IRQHandler()
{
    camera_dma();
    img_extract((u8 *)imgyiwei, imgbuff,CAMERA_SIZE); 
          

}

void PIT0_IRQHandler(void)//��ʱ���жϷ�����
{
      //lcd_show_enable1=0;//ע�͵��ǵ���Һ��
         PIT_Flag_Clear(PIT0);
        if(lcd_show_enable1)//Ϊ0����Һ��
        {
            my_lcd_show();
        }
        else
        {
                    /*****************************************************������ȡ*************************************************************/     
                  get_maichong();//��ȡ���ת�� 
                  
                    if(LK_jishi_flag==0)
                      LK_jishi++;
                    if(LK_jishi==300)//����ʱ1.5��
                          go=1;//С��ǰ��

                    
                    if(LK_jishi>=2000)    //�ӳ�2000*5ms��10s�����������
                        {
                          LK_jishi_flag=1;
                          LK_jishi=2000;
                        }

                /*****************************************************������ȡ*************************************************************/  

                lkcongzhongjiansaomiao();//ͼ�����м�ɨ��

                  if(star_lineflag==1)
                        LK_yanshi++;    //��������ͣ��ʱ����� 30*5ms
                  
                  if(!star_lineflag&&go) 
                    {
                      if(yunsu_flag==1)
                      mubiao_speed=dawan_speed;
                      else
                        lukuangudge();//·���ж�       
                    }
                    else
                      if(LK_yanshi>30)//��⵽������
                        mubiao_speed=0;   //��ʼͣ��
                      //if(pof)
                        //mubiao_speed=0;
                    DSYJ_dianji_PID(mubiao_speed); //���Ƶ��ת��
                  
                /************************************************************************S���ж�****************************************************/  
                if(s_wan_flag)
                {
                    S1=1;
                    //s_wan_flag=0;
                }
                else
                {
                   S=0;
                   S1=0;
                }
                    
                if(S1&&S<=25)    //ͨ��Сs���жϴ�s��
                      S++;

                if(S>=30)
                {
                    zhichong_flag=1;
                    //gpio_set(PTE1,1);
                }
                else
                {
                    zhichong_flag=0;
                    //gpio_set(PTE1,0);
                }
                  /*******************************************************�µ�����*****************************************************/  
                  // if(abs(my_piancha)<=16&&qvlv_quanju<=10&&duandian<12&&qulv_jinduan<12)
                    // tuoluoyivar=adc_once(ADC1_SE4a,ADC_8bit);
                  // else
                    // tuoluoyivar=104;
                    
                  /*  if(abs(tuoluoyivar-104)>40&&!podao_flag)
                    {
                      podao_flag=1;
                    // gpio_set(PTE1,1);
                    }
                    if(podao_flag&&podao_flag<800)
                    {
                podao_flag++;

                    }
                else
                {
                podao_flag=0;
                //gpio_set(PTE1,0);
                }

                if(podao_flag>0&&podao_flag<130)
                pof=1;
                else
                pof=0;*/
                /*******************************************************�ϰ�����*****************************************************/  

                if(zhangai_right==1) 
                {
                      zhangaijishiright_flag=1;
                      zhangai_right=0;
                }
                else if(zhangai_left==1)
                {
                    zhangaijishileft_flag=1;
                    zhangai_left=0;
                } 
                
                  
                if(zhangaijishileft_flag&&zhangaijishileft_flag<35)
                {
                    zhangaijishileft_flag++;
                  // led(LED0, LED_ON);
                }
                else
                if(zhangaijishiright_flag&&zhangaijishiright_flag<35)
                 {
                    zhangaijishiright_flag++;
                  }
                  else 
                    zhangaijishiright_flag=zhangaijishileft_flag=0;
                /************************************************************************ֱ���ж�*ֱ���ж�*****************************************************/  

                    if(abs(my_piancha)<=13&&qvlv_quanju<=13&&duandian<10)
                    {
                      zhidao_flag++;      
                    }
                    else
                    {
                      zhidao_flag=0;
                    }
                    //gpio_turn(PTA17);
                /*****************************************************ƫ���*************************************************************/  

                  pianchachuli();
                    
        }

          
}

void Priority_Set(void)
{
 // NVIC_SetPriorityGrouping(4);            //�������ȼ�����,4bit ��ռ���ȼ�,û�������ȼ�

  NVIC_SetPriority(PORTA_IRQn,0);         //�������ȼ�
  NVIC_SetPriority(DMA0_IRQn,1);          //�������ȼ�
  NVIC_SetPriority(PIT0_IRQn,2);          //�������ȼ�

}