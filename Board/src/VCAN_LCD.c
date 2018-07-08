/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       VCAN_LCD.c
 * @brief      LCD ������
 * @author     ɽ��Ƽ�
 * @version    v5.0
 * @date       2013-06-26
 */


#include "common.h"
#include "VCAN_LCD.h"
extern int kp1,kd,S_speed,DJ_mid,currentzhongjian[60];
Site_t site = {3,5};
char    enter_flag=0,lcd_show_enable1=1;
 int  site_flag=0;
 int BCOLOUR_NEW[8]={BCOLOUR,BCOLOUR,BCOLOUR,BCOLOUR,BCOLOUR,BCOLOUR,BCOLOUR,BCOLOUR};
 extern uint8 imgbuff[60*80];
 extern uint8 imgyiwei[60][80]; 
 extern void lkcongzhongjiansaomiao();
/*!
 *  @brief      LCD��ʼ��
 *  @since      v5.0
 */
void LCD_init(void)
{
    Site_t site = {0, 0};
    Size_t size ;

    LCD_INIT();                             //��ʼ��LCD

    //LCD_SET_DIR(LCD_DIR+1);

    //���ڳ�ʼ����ʱ����� ��Ļ���� ѡ�������ʼ����ɺ󣬲Ż�ȡ���
    size.W = LCD_W;
    size.H = LCD_H;

    LCD_rectangle(site, size, BCOLOUR);     //��ʼ������
}

/*!
 *  @brief      ��ʾʵ�ľ���
 *  @param      site    ���Ͻ�����
 *  @param      size    ���δ�С
 *  @param      rgb565  ��ɫ
 *  @since      v5.0
*  Sample usage:        Site_t site = {10,20};   //x = 10 ,y = 20
                        Size_t size = {50,60};  // W = 50 ,H = 60
                        LCD_rectangle(site, size, RED);
 */
void LCD_rectangle(Site_t site, Size_t size, uint16 rgb565)
{
    uint32 n, temp;

    LCD_PTLON(site, size);              //����

    temp = (uint32)size.W * size.H;
    LCD_RAMWR();                        //д�ڴ�
    for(n = 0; n < temp; n++)
    {
        LCD_WR_DATA( rgb565 );          //д����
    }
}

void LCD_clear(uint16 rgb565)     //����
{
    Site_t site = {0,0};
    Size_t size;
    size.H = LCD_H;
    size.W = LCD_W;

    LCD_rectangle(site, size, rgb565);

}

//��ʮ����
void LCD_cross(Site_t site,uint16 len,uint16 Color)
{
    //������ֱ��
    Site_t sitetmp;
    Size_t size;
    int16  stmp,etmp;
    uint16 w = LCD_W,h = LCD_H;

    ASSERT((site.x<LCD_W) && (site.y<LCD_H));       //ʮ���ߵ����Ĳ��ܳ���Һ����Χ

    stmp = site.x - len/2;                          //����ˮƽ�ߵ�x�����ͽ����㣬���Ʋ�����Һ����Χ
    if(stmp < 0)stmp = 0;
    etmp = site.x + len/2;
    if(etmp >= w)etmp= w-1;

    sitetmp.x = stmp;
    sitetmp.y = site.y;
    size.W = etmp - stmp +1;
    size.H = 1;
    LCD_rectangle(sitetmp,size, Color);

    stmp = site.y - len/2;                          //����ˮƽ�ߵ�x�����ͽ����㣬���Ʋ�����Һ����Χ
    if(stmp < 0)stmp = 0;
    etmp = site.y + len/2;
    if(etmp >= h)etmp= h-1;

    sitetmp.x = site.x;
    sitetmp.y = stmp;
    size.W = 1;
    size.H = etmp - stmp +1;
    LCD_rectangle(sitetmp,size, Color);



}

/*!
 *  @brief      ����
 *  @param      site    ���Ͻ�����
 *  @param      rgb565  ��ɫ
 *  @since      v5.0
*  Sample usage:        Site_t site = {10,20};   //x = 10 ,y = 20
                        LCD_point(site, RED);
 */
void LCD_point(Site_t site, uint16 rgb565)
{
    Size_t size = {1, 1};
    LCD_PTLON(site, size);
    LCD_RAMWR();                        //д�ڴ�
    LCD_WR_DATA(rgb565);                //д����
}

/*!
 *  @brief      ��һ�ѵ�
 *  @param      site        ����������
 *  @param      point_num   �������
 *  @param      rgb565      ��ɫ
 *  @since      v5.0
*  Sample usage:        Site_t site[3] = {{10,20},{11,21},{12,22}};   //3���㣬����ֱ���  {10,20},{11,21},{12,22}
                        LCD_points(site,3, RED);
 */
void LCD_points          (Site_t *site,uint32 point_num, uint16 rgb565)                 //��һ�ѵ�
{
    while(point_num--)
    {
        LCD_point(site[point_num],rgb565);                 //����
    }
}

/*!
 *  @brief      ��ʾ�ַ�
 *  @param      site    ���Ͻ�����
 *  @param      ascii   �ַ�
 *  @param      Color   ������ɫ
 *  @param      bkColor ������ɫ
 *  @since      v5.0
*  Sample usage:        Site_t site = {10,20};   //x = 10 ,y = 20
                        LCD_char(site,'0', BLUE,RED);
 */
void LCD_char(Site_t site, uint8 ascii, uint16 Color, uint16 bkColor)
{
#define MAX_CHAR_POSX (LCD_W-8)
#define MAX_CHAR_POSY (LCD_H-16)

    uint8 temp, t, pos;
    Size_t size = {8, 16};

    if(site.x > MAX_CHAR_POSX || site.y > MAX_CHAR_POSY)
    {
        return;
    }

    LCD_PTLON(site, size);

    LCD_RAMWR();                    //д�ڴ�

    for (pos = 0; pos < 16; pos++)
    {
        temp = ascii_8x16[((ascii-0x20)*16)+pos];

        for(t = 0; t < 8; t++)
        {

            if(temp & 0x80)
            {
                LCD_WR_DATA(Color);
            }
            else
            {
                LCD_WR_DATA(bkColor);
            }
            temp <<= 1;
        }
    }
    return;
#undef MAX_CHAR_POSX
#undef MAX_CHAR_POSY
}

/*!
 *  @brief      ��ʾ�ַ���
 *  @param      site    ���Ͻ�����
 *  @param      Str     �ַ�����ַ
 *  @param      Color   ������ɫ
 *  @param      bkColor ������ɫ
 *  @since      v5.0
*  Sample usage:        Site_t site = {10,20};   //x = 10 ,y = 20
                        LCD_str(site,"www.vcan123.com", BLUE,RED);
 */
void LCD_str(Site_t site, uint8 *Str, uint16 Color, uint16 bkColor)
{
#define MAX_CHAR_POSX (LCD_W-8)
#define MAX_CHAR_POSY (LCD_H-16)
    while(*Str != '\0')
    {
        if(site.x > MAX_CHAR_POSX )
        {
            //����
            site.x = 0;
            site.y += 16;
        }
        if(site.y > MAX_CHAR_POSY )
        {
            //һ��
            site.y = 0;
            site.x = 0;
        }

        LCD_char(site, *Str, Color, bkColor);
        site.x += 8;
        Str ++ ;
    }
#undef MAX_CHAR_POSX
#undef MAX_CHAR_POSY
}

/*!
 *  @brief      ��ʾ����
 *  @param      site    ���Ͻ�����
 *  @param      num     ����
 *  @param      Color   ������ɫ
 *  @param      bkColor ������ɫ
 *  @since      v5.0
*  Sample usage:        Site_t site = {10,20};   //x = 10 ,y = 20
                        LCD_num(site,123, BLUE,RED);
 */
void LCD_num(Site_t site, uint32 num, uint16 Color, uint16 bkColor)
{
    uint32 res = num;
    uint8 t = 0;
    Site_t sitetemp;
    sitetemp.y = site.y;

    if( num == 0 )
    {
        LCD_char(site, '0', Color, bkColor);
        return;
    }
    while( res )  /*�õ����ֳ���t*/
    {
        res /= 10;
        t++;
    }

    while(num)
    {
        sitetemp.x = site.x + (8 * (t--) - 8);
        LCD_char(sitetemp, (num % 10) + '0', Color, bkColor);
        num /= 10 ;
    }
}

/*!
 *  @brief      ��ʾ���֣���ն����λ��
 *  @param      site            ���Ͻ�����
 *  @param      num             ����
 *  @param      max_num_bit     ����λ��
 *  @param      Color           ������ɫ
 *  @param      bkColor         ������ɫ
 *  @since      v5.0
*  Sample usage:        Site_t site = {10,20};   //x = 10 ,y = 20
                        LCD_num_BC(site,123,5, BLUE,RED);
 */
void LCD_num_BC(Site_t site, uint32 num, uint8 max_num_bit, uint16 Color, uint16 bkColor)
{
    uint32 res = num;
    uint8 t = 0;
    Site_t sitetemp;
    Size_t size;

    sitetemp.y = site.y;

    if( num == 0 )
    {
        LCD_char(site, '0', Color, bkColor);

        site.x += 8;
        size.H  = 16;
        size.W  = 8 * (max_num_bit - 1);
        LCD_rectangle(site, size, bkColor);

        return;
    }
    while( res )            /*�õ����ֳ���t*/
    {
        res /= 10;
        t++;
    }
    if(t >= max_num_bit )    //������󳤶�
    {
        t = max_num_bit;
    }

    res = t;

    while( t != 0 )
    {
        sitetemp.x = site.x + (8 * (t--) - 8);
        LCD_char(sitetemp, (num % 10) + '0', Color, bkColor);
        num /= 10 ;
    }

    if(res != max_num_bit )
    {
        size.W = 8 * (max_num_bit - res);
        site.x += (8 * res);
        size.H  = 16;
        LCD_rectangle(site, size, bkColor);
    }
}

/*!
 *  @brief      �Ҷ�ͼ����ʾ
 *  @param      site            ���Ͻ�����
 *  @param      size            ��ʾͼ���С
 *  @param      img             ͼ���ַ
 *  @since      v5.0
 *  Sample usage:       Site_t site = {10,20};      //x = 10 ,y = 20
                        Size_t size = {320,240};    //W = 320,H = 240
                        LCD_Img_gray(site, size, img);
 */
void LCD_Img_gray(Site_t site, Size_t size, uint8 *img)
{
    uint32     total = (size.H * size.W);
    uint16     imgtemp;
    uint8     *pimg = (uint8 *)img;

    LCD_PTLON(site, size);                      //����
    LCD_RAMWR();                                //д�ڴ�

    while(total--)
    {
        imgtemp     = (uint16) * (pimg++);
        imgtemp = GRAY_2_RGB565(imgtemp);
        LCD_WR_DATA( imgtemp );               //дͼ������
    }
}

/*!
 *  @brief      ���ŻҶ�ͼ����ʾ
 *  @param      site            ���Ͻ�����
 *  @param      size            ��ʾͼ���С
 *  @param      img             ͼ���ַ
 *  @param      imgsize         ͼ���С
 *  @since      v5.0
 *  Sample usage:       Site_t site = {10,20};          //x = 10 ,y = 20
                        Size_t size = {80,60};          //W = 80,H = 60
                        Size_t imgsize = {320,240};     //W = 320,H = 240
                        LCD_Img_gray_Z(site, size, img,imgsize);
 */
void LCD_Img_gray_Z(Site_t site, Size_t size, uint8 *img, Size_t imgsize)
{
    uint32 temp, tempY;
    uint16 x, y;
    uint16 X, Y;
    uint8 *pimg = (uint8 *)img;
    uint16 rgb;

    LCD_PTLON(site, size);                      //����

    LCD_RAMWR();                                //д�ڴ�

    for(y = 0; y < size.H; y++)
    {
        Y = ( (  y * imgsize.H   ) / size.H) ;
        tempY = Y * imgsize.W ;

        for(x = 0; x < size.W; x++)
        {
            X = ( x * imgsize.W  ) / size.W ;
            temp = tempY + X;
            rgb = GRAY_2_RGB565(pimg[temp]);    //
            LCD_WR_DATA(rgb);
        }
    }
}



void LCD_Img_Binary(Site_t site, Size_t size, uint8 *img)
{
    uint32     total = (size.H * size.W) / 8;
    uint8     imgtemp;
    uint8       bitindex;
    uint8     *pimg = (uint8 *)img;

    LCD_PTLON(site, size);                      //����

    LCD_RAMWR();                                //д�ڴ�

    while(total--)
    {
        imgtemp     = *(pimg++);
        bitindex    = 8;
        while(bitindex--)
        {
            if( imgtemp & (0x01 << bitindex) )
            {
                LCD_WR_DATA( BINARY_COLOR );      //дͼ������
            }
            else
            {
                LCD_WR_DATA(  BINARY_BGCOLOR  );      //дͼ������
            }
        }
    }
}

void LCD_Img_Binary_Z(Site_t site, Size_t size, uint8 *img, Size_t imgsize)
{

    uint32 temp, tempY;
    uint16 x, y;
    uint16 X, Y;
    uint8 *pimg = (uint8 *)img;

    LCD_PTLON(site, size);                      //����

    LCD_RAMWR();                                //д�ڴ�

    for(y = 0; y < size.H; y++)
    {
        Y = ( (  y * imgsize.H  ) / size.H) ;
        tempY = Y * imgsize.W ;

        for(x = 0; x < size.W; x++)
        {
            X = (( x * imgsize.W  ) / size.W) ;
            temp = tempY + X;
            if( (pimg[temp>>3] & (1 << (7 - (temp & 0x07))) ) == 0  )
            {
                LCD_WR_DATA( BINARY_BGCOLOR );        //дͼ������
            }
            else
            {
                LCD_WR_DATA( BINARY_COLOR );      //дͼ������
            }
        }
    }
}

void LCD_wave(Site_t site,Size_t size,uint8 *img,uint8 maxval,uint16 Color ,uint16 bkColor)
{

    uint8 h;
    uint16 y = site.y + size.H - 1;

    LCD_rectangle(site, size,bkColor);
    site.x += size.W;
    img  += (size.W - 1);
    while(size.W --)
    {
        if(*img >= maxval )
        {
            h = size.H - 1;
        }
        else
        {
            h = ((*img )* size.H )/maxval;
        }
        site.y = y - h ;
        site.x--;
        img --;
        LCD_point(site, Color);
    }
}

void LCD_wave_display(Site_t site,Size_t size,uint8 *img,uint8 maxval,uint16 Color)
{

    uint8 h;
    uint16 y = site.y + size.H - 1;

    site.x += size.W;
    img  += (size.W - 1);
    while(size.W --)
    {
        if(*img >= maxval )
        {
            h = size.H - 1;
        }
        else
        {
            h = ((*img )* size.H )/maxval;
        }
        site.y = y - h ;
        site.x--;
        img --;
        LCD_point(site, Color);
    }
}

void my_lcd_init()
{
  lcd_show_enable1=1;
Site_t site = {3,5};


    LCD_init();
    LCD_str(site,"xiang zuo an",FCOLOUR,BCOLOUR);
    site.y = 20;
    LCD_str(site,"   < <     ",FCOLOUR,BCOLOUR);
    site.y = 5;
   key_Init();
    
}

void canshu_chang_init()//����������ʾ
{
  
LCD_clear(BCOLOUR);     //����
  Site_t site = {3,5};
    LCD_str(site,"kp:",FCOLOUR,BCOLOUR);   //��ʾ8*16�ַ���
    site.y += 15;
    LCD_str(site,"kd:",FCOLOUR,BCOLOUR);   //��ʾ8*16�ַ���
    site.y += 15;
    LCD_str(site,"dawansudu:",FCOLOUR,BCOLOUR);   //��ʾ8*16�ַ���
   site.y += 15;
    LCD_str(site,"zhidaosudu:",FCOLOUR,BCOLOUR);   //��ʾ8*16�ַ���
    site.y += 15;
    LCD_str(site,"qianzhan:",FCOLOUR,BCOLOUR);   //��ʾ8*16�ַ���
    site.y += 15;
    LCD_str(site,"yuzhi(show):",FCOLOUR,BCOLOUR);   //��ʾ8*16�ַ���
    site.y += 15;
    LCD_str(site,"S_speed:",FCOLOUR,BCOLOUR);   //��ʾ8*16�ַ���
    site.y += 15;
    LCD_str(site,"DJmiddle:",FCOLOUR,BCOLOUR);   //��ʾ8*16�ַ���
     
    
     BCOLOUR_NEW[0]=YELLOW;
     site_flag=4;
}

int vaul_change(int vaul)//�����Ķ�����ֵ����
{
if(key_status()==4)//��
    {
      systick_delay_ms(5);//����
    vaul--;
  
    while(key_status()==4);
    systick_delay_ms(5);//����
    }
    else
      if(key_status()==3)//��
      {
        systick_delay_ms(5);//����
        vaul++;
    while(key_status()==3);
    systick_delay_ms(5);//����
      }
return vaul;
}
void canshu_chang()//�Ĳ������溯��
{
   yuzhi=0x55;
  while(enter_flag)
  {
        site.y = 4;
        site.x = 90;
       
        LCD_num_C (site, kp, FCOLOUR , BCOLOUR_NEW[0]);
        site.y += 15;
        LCD_num_C (site, kd, FCOLOUR , BCOLOUR_NEW[1]);
        site.y += 15;
        LCD_num_C (site, dawan_speed , FCOLOUR , BCOLOUR_NEW[2]);
        site.y += 15;
        LCD_num_C (site, long_speed , FCOLOUR , BCOLOUR_NEW[3]);
        site.y += 15;
        LCD_num_C (site, qianzhan , FCOLOUR , BCOLOUR_NEW[4]);
        site.y += 15;
        LCD_num_C (site, yuzhi, FCOLOUR , BCOLOUR_NEW[5]);
        site.y += 15;
        LCD_num_C (site, S_speed , FCOLOUR , BCOLOUR_NEW[6]);
        site.y += 15;
        LCD_num_C (site, DJ_mid , FCOLOUR , BCOLOUR_NEW[7]);
        
         switch((site_flag-4)/15)
      {
      case 0:kp=vaul_change(kp);break;
      case 1:kd=vaul_change(kd);break;
      case 2:dawan_speed=vaul_change(dawan_speed);break;
      case 3:long_speed=vaul_change(long_speed);break;
      case 4:qianzhan=vaul_change(qianzhan);break;
      case 5:yuzhi=vaul_change(yuzhi);break;
      case 6:S_speed=vaul_change(S_speed);break;
      case 7:DJ_mid=vaul_change(DJ_mid);break;
      }
      if(key_status()==2)//ȷ��
      {
        systick_delay_ms(5);//����
        while(key_status()==2);
        systick_delay_ms(5);//����
        enter_flag=0;
      
      }
  }
        site.y = 4;
        site.x = 90;
       
        LCD_num_C (site, kp, FCOLOUR , BCOLOUR_NEW[0]);
        site.y += 15;
        LCD_num_C (site, kd, FCOLOUR , BCOLOUR_NEW[1]);
        site.y += 15;
        LCD_num_C (site, dawan_speed , FCOLOUR , BCOLOUR_NEW[2]);
        site.y += 15;
        LCD_num_C (site, long_speed , FCOLOUR , BCOLOUR_NEW[3]);
        site.y += 15;
        LCD_num_C (site, qianzhan , FCOLOUR , BCOLOUR_NEW[4]);
        site.y += 15;
        LCD_num_C (site, yuzhi, FCOLOUR , BCOLOUR_NEW[5]);
        site.y += 15;
        LCD_num_C (site, S_speed , FCOLOUR , BCOLOUR_NEW[6]);
        site.y += 15;
        LCD_num_C (site, DJ_mid , FCOLOUR , BCOLOUR_NEW[7]);
/************************************************�����Ĳ���**************************************************/     
      site.y=site_flag;
        if(key_status()==4)//��
    {
      systick_delay_ms(4);//����
     
     site.y=15+site_flag;
     site_flag=site.y;
     if(site_flag>=19)
   BCOLOUR_NEW[(site.y-19)/15]=BCOLOUR;
    if(site_flag>109)
      site_flag=4;
      if(site_flag==4)
   BCOLOUR_NEW[(site_flag-4)/15]=BCOLOUR;
    BCOLOUR_NEW[(site_flag-4)/15]=RED;
    while(key_status()==4);
    systick_delay_ms(5);//����
    }
    else
      if(key_status()==3)//��
      {
        systick_delay_ms(4);//����
     
     site.y=site_flag-15;
     site_flag=site.y;
     if(site_flag<=109)
   BCOLOUR_NEW[(site.y+19)/15]=BCOLOUR;
    if(site_flag>1000)
    {
 BCOLOUR_NEW[0]=BCOLOUR;
      site_flag=109;
      site.y=109;
    }
  
   
    BCOLOUR_NEW[(site_flag-4)/15]=RED;
    while(key_status()==3);
    systick_delay_ms(5);//����
      }
      if(key_status()==2)//ȷ��
      {
        systick_delay_ms(5);//����
        while(key_status()==2);
        systick_delay_ms(5);//����
        enter_flag=1;
      
      }
     
}
int caidan()//�˵�������
{
  LCD_clear(BCOLOUR);     //����
  BCOLOUR_NEW[0]=BCOLOUR_NEW[1]=BCOLOUR_NEW[2]=BCOLOUR_NEW[3]=BCOLOUR_NEW[4]=BCOLOUR_NEW[5]=BCOLOUR_NEW[6]=BCOLOUR_NEW[7]=BCOLOUR;
  site.y = 5;
  site.x = 30;
 LCD_str(site,"tu xiang",FCOLOUR,BCOLOUR);   //��ͼ��
    site.y += 30;
    LCD_str(site,"set canshu",FCOLOUR,BCOLOUR);   //������
    site.y += 30;
    LCD_str(site,"suo ping",FCOLOUR,BCOLOUR);   //����
    site.y = 5;
      site.x = 0;
    LCD_str(site,"__",FCOLOUR,BLUE);//����
    while(1)
    {
       
  site.x = 0;
      
    if(key_status()==4)//��
    {
      systick_delay_ms(5);//����
      LCD_str(site,"  ",FCOLOUR,BCOLOUR);//��������
    site.y+=30;
    if(site.y>65)
      site.y=5;
    LCD_str(site,"__",FCOLOUR,BLUE);//����
    while(key_status()==4);
    systick_delay_ms(5);//����
    }
    else
      if(key_status()==3)//��
      {
        systick_delay_ms(5);//����
        LCD_str(site,"  ",FCOLOUR,BCOLOUR);//��������
        if(site.y>=10)
      site.y-=30;
      else
    if(site.y<10)
      site.y=65;
    LCD_str(site,"__",FCOLOUR,BLUE);//����
    while(key_status()==3);
    systick_delay_ms(5);//����
      }
    else
      if(key_status()==2)//ȷ��
      {
        systick_delay_ms(5);//����
        while(key_status()==2);
        systick_delay_ms(5);//����
      switch(site.y)
      {
      case 5:return 1;break;//��ͼ��
      case 35:canshu_chang_init();return 2;break;//������
      case 65:return 3;break;//����
      }
      }
    }
}
void show_img()
{ 
  int iiii=0;
 Site_t site     = {0, 0};                           //��ʾͼ�����Ͻ�λ��
    Size_t imgsize  = {CAMERA_W, CAMERA_H};             //ͼ���С
    Size_t size;                   //��ʾ����ͼ���С
    // LCD_init();

   size.H = CAMERA_H;
    size.W = CAMERA_W;
   // img_extract((u8 *)imgyiwei, imgbuff,CAMERA_SIZE);      //��ѹͼ��
    lkcongzhongjiansaomiao();
    LCD_Img_Binary_Z(site, size, imgbuff, imgsize);
    for(iiii=59;iiii>=0;iiii--)
    {
      Site_t site[3] = {{currentzhongjian[iiii],iiii},{currentzhongjian[iiii]+1,iiii},{currentzhongjian[iiii]-1,iiii}};   //3���㣬����ֱ���  {10,20},{11,21},{12,22}
    LCD_points(site,3, GREEN);
    }
   
}
 unsigned char caidan_answer=0;
void show_go()
{
    LCD_clear(BCOLOUR);     //����
  site.y = 60;
  site.x = 20;
LCD_str(site,"KAI CHE",FCOLOUR,BCOLOUR);   //��ʾ8*16�ַ���
lcd_show_enable1=0;
}
void my_lcd_show()
{
  lcd_show_enable1=1;
  //**********************************************��������***************************************************//
       
        if(key_status()==1)//���
        {
          
           systick_delay_ms(5);//����
           while(key_status()==1);
           systick_delay_ms(5);//����
         caidan_answer=caidan();
         
        }
        else;
          switch(caidan_answer)
          {
          case 1:show_img();break;//��ͼ
          case 2:canshu_chang();break;//������
          case 3:show_go();break;//����
          }
}