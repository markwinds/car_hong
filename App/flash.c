/******************** (C) COPYRIGHT 2016 ̩����ӿƼ� ********************
 * �ļ���       ��flash.c
 * ����         ��flash��������
 *
 * ʵ��ƽ̨     �����������
 * ��汾       �����1.0��
 * Ƕ��ϵͳ     �����������ܳ�
 *
 * ����         ��DMX
 * ����֧����̳ ��http://www.taiqdz.cn
 * ��ע	       �������������޸Ķ���
**********************************************************************************/


//����ͷ�ļ�
#include "flash.h" 
#include "common.h"
#include "key.h"
//#include "gpio.h"




//Flash����궨�壬�ڲ�ʹ��
#define   RD1BLK    0x00   // ������Flash
#define   RD1SEC    0x01   // ����������
#define   PGMCHK    0x02   // д����
#define   RDRSRC    0x03   // ��Ŀ������
#define   PGM4      0x06   // д�볤��
#define   ERSBLK    0x08   // ��������Flash
#define   ERSSCR    0x09   // ����Flash����
#define   PGMSEC    0x0B   // д������
#define   RD1ALL    0x40   // �����еĿ�
#define   RDONCE    0x41   // ֻ��һ��
#define   PGMONCE   0x43   // ֻдһ��
#define   ERSALL    0x44   // �������п�
#define   VFYKEY    0x45   // ��֤���ŷ���Կ��
#define   PGMPART   0x80   // д�����
#define   SETRAM    0x81   // �趨FlexRAM����
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
USHORT16 User_parameter[12]={100,165,28,130,70,1,0x0007,0x0008,0x0009,0x0010,0x0011,0x0012};
//User_parameter[0]:speed_set



//data memories
USHORT16 read_memory0[4]= {0x0000,0x0000,0x0000,0x0000};
USHORT16 read_memory1[4]= {0x0000,0x0000,0x0000,0x0000};
USHORT16 read_memory2[4]= {0x0000,0x0000,0x0000,0x0000};
//gear memories
USHORT16 gear_memory0[4]= {0x0000,0x0000,0x0000,0x0000};
USHORT16 gear_memory1[4]= {0x0000,0x0000,0x0000,0x0000};
USHORT16 gear_memory2[4]= {0x0000,0x0000,0x0000,0x0000};
//person control
//++++++++++++++++++++++++++++++++++++�����ٶȵ�λ����++++++++++++++++++++++++++++++++++++++++++++++++++
USHORT16 ZNC_GEAR1_0[4]= {104,167,29,132};//��������
USHORT16 ZNC_GEAR1_1[4]= {80,0,0x0000,0x0000};
USHORT16 ZNC_GEAR1_2[4]= {0x0000,0x0000,0x0000,0x0000};

USHORT16 ZNC_GEAR2_0[4]= {100,185,29,130};//����//��̨96  188 29 132������100 192 29 130
USHORT16 ZNC_GEAR2_1[4]= {80,0,0x0000,0x0000};
USHORT16 ZNC_GEAR2_2[4]= {0x0000,0x0000,0x0000,0x0000};

USHORT16 ZNC_GEAR3_0[4]= {104,202,29,130};//����
USHORT16 ZNC_GEAR3_1[4]= {80,0,0x0000,0x0000};
USHORT16 ZNC_GEAR3_2[4]= {0x0000,0x0000,0x0000,0x0000};

USHORT16 ZNC_GEAR4_0[4]= {90,170,30,120};//����  �»���̥������
USHORT16 ZNC_GEAR4_1[4]= {80,1,0x0000,0x0000};
USHORT16 ZNC_GEAR4_2[4]= {0x0000,0x0000,0x0000,0x0000};

USHORT16 ZNC_GEAR5_0[4]= {90,155,31,134};//�����ٶ�   
USHORT16 ZNC_GEAR5_1[4]= {80,1,0x0000,0x0000};
USHORT16 ZNC_GEAR5_2[4]= {0x0000,0x0000,0x0000,0x0000};
//USHORT16 dangwei3_neicun[4]= {0x0000,0x0000,0x0000,0x0000};
int speed_level;
//=================�ڲ�����ʵ��=============================================

//==========================================================================
//�������ƣ�flash_cmd_launch
//�������أ�0-�ɹ� 1-ʧ��
//����˵������
//���ܸ�Ҫ������Flash����
//==========================================================================
__RAMFUN static uint32 flash_cmd_launch(void)
{
    
    FTFL_FSTAT = 	(0
				  	|	FTFL_FSTAT_CCIF_MASK 		// ��������
					|	FTFL_FSTAT_ACCERR_MASK 		// ������ʴ����־λ
					| 	FTFL_FSTAT_FPVIOL_MASK		// �Ƿ����ʱ�־λ
					);	
    									
    while(!(FTFL_FSTAT & FTFL_FSTAT_CCIF_MASK));	// �ȴ��������

    // �������־
    if( FTFL_FSTAT & (FTFL_FSTAT_ACCERR_MASK | FTFL_FSTAT_FPVIOL_MASK | FTFL_FSTAT_MGSTAT0_MASK))
        return 1 ; 				//ִ���������
  
    return 0; 					//ִ������ɹ�
}

//===========================================================================

//=================�ⲿ�ӿں���==============================================
//==========================================================================
//�������ƣ�flash_init
//�������أ���
//����˵������
//���ܸ�Ҫ����ʼ��flashģ��
//==========================================================================
__RAMFUN void flash_init(void)
{
	// ���FlashԤ��ȡ������
    FMC_PFB0CR |= FMC_PFB0CR_S_B_INV_MASK;
    FMC_PFB1CR |= FMC_PFB0CR_S_B_INV_MASK;
    
    while(!(FTFL_FSTAT & FTFL_FSTAT_CCIF_MASK));	// �ȴ��������
    
	FTFL_FSTAT = 	(0
					|	FTFL_FSTAT_ACCERR_MASK 		// ������ʴ����־λ
					| 	FTFL_FSTAT_FPVIOL_MASK		// �Ƿ����ʱ�־λ
					);	
}

//==========================================================================
//�������ƣ�flash_erase_sector
//�������أ�����ִ��ִ��״̬��0=��������0=�쳣��
//����˵����sectorNo�������ţ�K60N512ʵ��ʹ��0~255��
//���ܸ�Ҫ������ָ��flash����
//==========================================================================
__RAMFUN uint8 flash_erase_sector(uint16 sectorNo)
{
    Dtype	addr;	
	addr.DW = (uint32)(sectorNo<<11);	//ÿ������2KB������������ַ=������*2K �������� <<11 ��ʾ *2*1024 
    
    //dest.word    = (uint32)(sectorNo<<11);	//ÿ������2KB������������ַ=������*2K �������� <<11 ��ʾ *2*1024 

    // ���ò�������
    FTFL_FCCOB0 = ERSSCR; // ������������
    
    // ����Ŀ���ַ
    FTFL_FCCOB1 = addr.B[2];
    FTFL_FCCOB2 = addr.B[1];
    FTFL_FCCOB3 = addr.B[0];
    
    // ִ����������
    if(1 == flash_cmd_launch())    //��ִ��������ִ���
        return 1;     //�����������
   
    // ������sector0ʱ��������豸
    if(sectorNo ==0)
    {
        // д��4�ֽ�
        FTFL_FCCOB0 = PGM4; 
        // ����Ŀ���ַ
        FTFL_FCCOB1 = 0x00;
        FTFL_FCCOB2 = 0x04;
        FTFL_FCCOB3 = 0x0C;
        // ����
        FTFL_FCCOB4 = 0xFF;
        FTFL_FCCOB5 = 0xFF;
        FTFL_FCCOB6 = 0xFF;
        FTFL_FCCOB7 = 0xFE;
        // ִ����������
        if(1 == flash_cmd_launch())  //��ִ��������ִ���
            return 2;   //�����������
    }  
    
    return 0;  //�ɹ�����
}

//==========================================================================
//�������ƣ�flash_write
//�������أ�����ִ��״̬��0=��������0=�쳣��
//����˵����sectorNo��Ŀ�������� ��K60N512ʵ��ʹ��0~255��
//         offset:д�������ڲ�ƫ�Ƶ�ַ��0~2043��
//         cnt��д���ֽ���Ŀ��0~2043��
//         buf��Դ���ݻ������׵�ַ
//���ܸ�Ҫ��flashд�����
//==========================================================================
__RAMFUN uint8 flash_write(uint16 sectorNo,uint16 offset,uint32 data) 
{
	Dtype	addr;	
    Dtype	Data;
	
	ASSERT(offset%4 == 0);			//ƫ��������Ϊ4�ı���
									//�˴���ʾ���棬���ǰ�ȫ�ġ���
	ASSERT(offset <= 0x800);		//������СΪ2K����ƫ�������벻���� 0x800
									//�˴���ʾ���棬���ǰ�ȫ�ġ���
	
    addr.DW = (uint32)((sectorNo<<11) + offset);		//�����ַ
	Data.DW	= data;	
	    
    FTFL_FCCOB0 = PGM4;				// ����д������

	FTFL_FCCOB1 = addr.B[2];		// ����Ŀ���ַ
	FTFL_FCCOB2 = addr.B[1];
	FTFL_FCCOB3 = addr.B[0];


	FTFL_FCCOB4 = Data.B[3];        // ����д������
	FTFL_FCCOB5 = Data.B[2];
	FTFL_FCCOB6 = Data.B[1];
	FTFL_FCCOB7 = Data.B[0];
	
	if(1 == flash_cmd_launch()) 	return 2;  //д���������

    return 0;  //�ɹ�ִ��
}


//==========================================================================
//�������ƣ�flash_write
//�������أ�����ִ��״̬��0=��������0=�쳣��
//����˵����sectorNo��Ŀ�������� ��K60N512ʵ��ʹ��0~255��
//         offset:д�������ڲ�ƫ�Ƶ�ַ��0~2043��
//         cnt��д���ֽ���Ŀ��0~2043��
//         buf��Դ���ݻ������׵�ַ
//���ܸ�Ҫ��flashд�����
//==========================================================================
__RAMFUN uint8 flash_write_buf(uint16 sectorNo,uint16 offset,uint16 cnt,uint8 buf[])//�����ţ�����ƫ�Ƶ�ַ i*4  
{
    uint32 size;
 
	Dtype	addr;	
    
	ASSERT(offset%4 == 0);			//ƫ��������Ϊ4�ı���
									//�˴���ʾ���棬���ǰ�ȫ�ġ���
	ASSERT(offset <= 0x800);		//������СΪ2K����ƫ�������벻���� 0x800
									//�˴���ʾ���棬���ǰ�ȫ�ġ���
	
    addr.DW = (uint32)((sectorNo<<11) + offset);		//�����ַ
	
    // ����д������
    FTFL_FCCOB0 = PGM4;

    for(size=0; size<cnt; size+=4, addr.DW+=4, buf+=4)
    {
        
        FTFL_FCCOB1 = addr.B[2];						// ����Ŀ���ַ
        FTFL_FCCOB2 = addr.B[1];
        FTFL_FCCOB3 = addr.B[0];
 
        FTFL_FCCOB4 = buf[3];							// ��������
        FTFL_FCCOB5 = buf[2];
        FTFL_FCCOB6 = buf[1];
        FTFL_FCCOB7 = buf[0];
        
        if(1 == flash_cmd_launch()) 
            return 2;  									//д���������
    }
    
    return 0;  //�ɹ�ִ��
}






__RAMFUN uint8 Flash_read(uint16 sectNo,uint16 offset,uint16 cnt,uint8*bBuf)
{
    uint32 wAddr = 0;
    wAddr = sectNo<<11 + offset;
    while (cnt--)
        *bBuf++=*(uint8*)wAddr++;
   return TRUE;
}


void flash_erase_memories(void)
  {
   flash_erase_sector(MEMORIES_ADDRESS0);       
   flash_erase_sector(MEMORIES_ADDRESS1);       
   flash_erase_sector(MEMORIES_ADDRESS2);       
  }
  void flash_write_memories(void)
 {
   int flash_i;
   for(flash_i=0;flash_i<4;flash_i++)
  {
     flash_write(MEMORIES_ADDRESS0,flash_i*4,gear_memory0[flash_i]);  
     flash_write(MEMORIES_ADDRESS1,flash_i*4,gear_memory1[flash_i]); 
     flash_write(MEMORIES_ADDRESS2,flash_i*4,gear_memory2[flash_i]); 
   }
 }
void flash_read_memories(void)
{
   int flash_i;
   for(flash_i=0;flash_i<4;flash_i++)
  {
     read_memory0[flash_i]=flash_read(MEMORIES_ADDRESS0,flash_i*4,int16);
     read_memory1[flash_i]=flash_read(MEMORIES_ADDRESS1,flash_i*4,int16);
     read_memory2[flash_i]=flash_read(MEMORIES_ADDRESS2,flash_i*4,int16);
  }
}
void read_parameter(void)
{
                    User_parameter[0]=read_memory0[0];
                    User_parameter[1]=read_memory0[1];
                    User_parameter[2]=read_memory0[2];
                    User_parameter[3]=read_memory0[3];
                    User_parameter[4]=read_memory1[0];
                    User_parameter[5]=read_memory1[1];
                    User_parameter[6]=read_memory1[2];
                    User_parameter[7]=read_memory1[3];
                    User_parameter[8]=read_memory2[0];
                    User_parameter[9]=read_memory2[1];
                    User_parameter[10]=read_memory2[2];
                    User_parameter[11]=read_memory2[3];
}
void write_parameter(void)
{
                    gear_memory0[0]=User_parameter[0];
                    gear_memory0[1]=User_parameter[1];
                    gear_memory0[2]=User_parameter[2];
                    gear_memory0[3]=User_parameter[3];
                    gear_memory1[0]=User_parameter[4];
                    gear_memory1[1]=User_parameter[5];
                    gear_memory1[2]=User_parameter[6];
                    gear_memory1[3]=User_parameter[7];
                    gear_memory2[0]=User_parameter[8];
                    gear_memory2[1]=User_parameter[9];
                    gear_memory2[2]=User_parameter[10];
                    gear_memory2[3]=User_parameter[11];
}
void write_speed_gear1(void)
{
int flash_i;
for(flash_i=0;flash_i<4;flash_i++)
      {
       gear_memory0[flash_i]=ZNC_GEAR1_0[flash_i];
       gear_memory1[flash_i]=ZNC_GEAR1_1[flash_i];
       gear_memory2[flash_i]=ZNC_GEAR1_2[flash_i];
       }
}
void write_speed_gear2(void)
{
int flash_i;
for(flash_i=0;flash_i<4;flash_i++)
      {
       gear_memory0[flash_i]=ZNC_GEAR2_0[flash_i];
       gear_memory1[flash_i]=ZNC_GEAR2_1[flash_i];
       gear_memory2[flash_i]=ZNC_GEAR2_2[flash_i];
       }
} 
void write_speed_gear3(void)
{
int flash_i;
for(flash_i=0;flash_i<4;flash_i++)
      {
       gear_memory0[flash_i]=ZNC_GEAR3_0[flash_i];
       gear_memory1[flash_i]=ZNC_GEAR3_1[flash_i];
       gear_memory2[flash_i]=ZNC_GEAR3_2[flash_i];
       }
} 
void write_speed_gear4(void)
{
int flash_i;
for(flash_i=0;flash_i<4;flash_i++)
      {
       gear_memory0[flash_i]=ZNC_GEAR4_0[flash_i];
       gear_memory1[flash_i]=ZNC_GEAR4_1[flash_i];
       gear_memory2[flash_i]=ZNC_GEAR4_2[flash_i];
       }
} 
void write_speed_gear5(void)
{
int flash_i;
for(flash_i=0;flash_i<4;flash_i++)
      {
       gear_memory0[flash_i]=ZNC_GEAR5_0[flash_i];
       gear_memory1[flash_i]=ZNC_GEAR5_1[flash_i];
       gear_memory2[flash_i]=ZNC_GEAR5_2[flash_i];
       }
}                     
                    
                    


  
void ZNC_DATA_Init(void)
{
  int flash_i;
  //OLED_flash_memories();
  OLED_starting_car();
  systick_delay_ms(500);
  
  keyright_=keyRight;
  if(!keyright_) //down  key3
             {
                systick_delay_ms(10);
                keyright_=keyRight;
                if(!keyright_)
                {   keyright_=keyRight; 
                    OLED_flash_memories();
                    systick_delay_ms(500);
                    
                    //Ĭ�ϵ�λ�ڶ���
                    /*for(flash_i=0;flash_i<4;flash_i++)
                    {
                      gear_memory0[flash_i]=ZNC_GEAR2_0[flash_i];
                      gear_memory1[flash_i]=ZNC_GEAR2_1[flash_i];
                      gear_memory2[flash_i]=ZNC_GEAR2_2[flash_i];
                    }*/
                    switch(speed_level)
                    {
                      case 1:write_speed_gear1();break;
                      case 2:write_speed_gear2();break;
                      case 3:write_speed_gear3();break;
                      case 4:write_speed_gear4();break;
                      case 5:write_speed_gear5();break;
                    }
                    flash_erase_memories();
                    flash_write_memories();
                    flash_read_memories();
                    read_parameter();
                }
                OLED_flash_memories_queren();
                systick_delay_ms(500);
             }
  else
            {
                flash_read_memories();
                read_parameter();
             }
                OLED_start_finish();
                systick_delay_ms(500);
}

void ZNC_DATA_Update(void)
{
  write_parameter();
  flash_erase_memories();
  flash_write_memories();
  flash_read_memories();
  read_parameter();
  //BFX_LED();
}

void BFX_LED(void)
{
gpio_init(PTD7,GPO,0u);
gpio_init(PTD8,GPO,0u);
gpio_init(PTC4,GPO,0u);
gpio_init(PTC5,GPO,0u);
gpio_init(PTC6,GPO,0u);
gpio_init(PTC7,GPO,0u);
gpio_init(PTC8,GPO,0u);
gpio_init(PTC9,GPO,0u);
}


//==========================================================================
