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


#ifndef _FLASH_H_
#define _FLASH_H_

//k60N512����512K�ĳ���Flash
//512K�ĳ���Flash��Ϊ256��������ÿ������2K��С
//K60X256����256K�ĳ���Flash
//512K�ĳ���Flash��Ϊ128��������ÿ������2K��С
//    sector��2K��Ϊ������С��λ
//    ���֣�32b��Ϊд����С��λ

#include "common.h"
#include "include.h"

#define MEMORIES_ADDRESS0 253
#define MEMORIES_ADDRESS1 254
#define MEMORIES_ADDRESS2 255


__RAMFUN	void 	flash_init();													//����ָ��flash����

__RAMFUN 	uint8 	flash_erase_sector	(uint16 sectorNo);									//����ָ��flash����
__RAMFUN 	uint8 	flash_write		(uint16 sectorNo,uint16 offset,uint32 data);					        //д��flash����
__RAMFUN 	uint8 	flash_write_buf		(uint16 sectorNo,uint16 offset,uint16 cnt,uint8 buf[]);					//�ӻ�����д��flash����



__RAMFUN        uint8   Flash_read(uint16 sectNo,uint16 offset,uint16 cnt,uint8*bBuf);
extern int speed_level;
extern USHORT16 User_parameter[12];
void write_speed_gear1(void);
void write_speed_gear2(void);
void write_speed_gear3(void);
void write_speed_gear4(void);
void write_speed_gear5(void);
void BFX_LED(void);

#define		flash_read(sectorNo,offset,type)		(*(type *)((uint32)(((sectorNo)<<11) + (offset))))			//��ȡ����
#endif //_FLASH_H_ 
