//���ߣ� 
//ʱ�䣺
#include "saomiao.h"
#include "common.h"
#include "include.h"
#include "math.h"
int qianzhan=29;
int kp=200,kd=0,my_piancha,my_lastzhongjian=40,currentzhongjianzhi=40,rightheixian_flag=0,leftheixian_flag=0,xielv;
int jiao, x,y,linshi_x,linshi_right_heixian,linshi_y,ruyuanhuan_flag=0;
extern u8 imgyiwei[60][80];
extern int currentzhongjian[60],right_heixian[60],left_heixian[60],zhidao_flag;
int lastpiancha_1,lastpiancha_2,lastpiancha_3,lastpiancha_4,duojijiaodu,flag_l=0,flag_r=0,linshi_left_heixian,B,shaobudaozuo_flag[60],shaobudaoyou_flag[60];
int shizidiyidian,shangshizidiyidian,S_Z;
int shizishu,chazhi,yy1,yy2,rushizi;
int duandian,duandianshu,duandianshu1,currentzhongjian_lk;
int xielv_flag;
int qulv_point=0,zhangai_right=0,zhangai_left=0;
int dian1,youshi_kuan_flag=0;
extern int star_lineflag,zhangaijishiright_flag,zhangaijishileft_flag;
char s_wan_flag,shizi_flag,yuanhuan_flag=0,guai_flag=0;
int qvlv_quanju,qulv_jinduan,qulv_yuandaun;
int qulv_jinduan_right=0,qulv_jinduan_left=0,qulv_yuandaun_right=0,qulv_yuandaun_left=0,qvlv_quanju_right=0,qvlv_quanju_left=0;
int half_zhi[60];
int yy1_pinjun,yy2_pinjun;
extern char S;
int kp1;

char jiji=0;

static int half_width_group[60]=
{
14,16,16,17,17,18,18,18,19,19,
20,20,21,21,22,22,23,23,23,25,
25,25,25,26,26,26,27,27,28,28,
28,29,29,30,30,30,31,31,32,33,
33,33,33,33,34,34,34,35,35,35,
36,36,36,36,37,37,38,38,38,38      
};

int regression(int startline,int endline)   //���Իع鷽�̼���б��      
{
  	if(endline>56)
    endline=56;
  	int i;
  	int sumX=0,sumY=0,avrX=0,avrY=0 ;
 	int num=0,B_up1=0,B_up2=0,B_up,B_down;
	for(i=startline;i<=endline;i++)
   	{
		num++;
		sumX+=i;
		sumY+=currentzhongjian[i];
   	}
   
    avrX=sumX/num;
    avrY=sumY/num;
    B_up=0;
    B_down=0;
    for(i=startline;i<=endline;i++)
   {
         
       	B_up1=(int)(currentzhongjian[i]-avrY);
    	B_up2=i-avrX;
        B_up+=(int)(10*(B_up1*B_up2));
        B_up=B_up/100*100;
    	B_down+=(int)(10*((i-avrX)*(i-avrX)));
    }
   if(B_down==0) 
   B=0;
   else 
   B=B_up*16/B_down;//16
   return B;
}


int hy;
void huaxian(int x1,int y1,int x2,int y2)//��������֮������һ���߶�
{
	int i,max,a1,a2;
	a1=x1;
	a2=x2;
	if(a1>a2)
	{
		max=a1;
		a1=a2;
		a2=max;
	}
    for(i=x1;i>0;i--)
    {
		if((x2-x1)!=0)
		{
			hy=(i-x1)*(y2-y1)/(x2-x1)+y1;
			currentzhongjian[i]=hy;
			if(hy<=1||hy>=79)	break;
		}
    }
}

void huaxian2(int xxx1,int yyy1,int xxx2,int yyy2)//����֮����߶�
{
      int i2,max2,a12,a22;
      a12=xxx1;
      a22=xxx2;
      if(a12>a22)
      {
        max2=a12;
      a12=a22;
      a22=max2;}
    for(i2=xxx1;i2<59;i2++)
    {
      if((xxx2-xxx1)!=0)
      {
        hy=(i2-xxx1)*(yyy2-yyy1)/(xxx2-xxx1)+yyy1;
       currentzhongjian[i2]=hy;
      }
    }
}

void huaxian3(int xxx1,int yyy1,int xxx2,int yyy2)//����֮����߶�
{
      int i2,max2,a12,a22;
      a12=xxx1;
      a22=xxx2;
      if(a12>a22)
      {
        max2=a12;
      a12=a22;
      a22=max2;}
    for(i2=xxx1;i2<xxx2;i2++)
    {
      if((xxx2-xxx1)!=0)
      {
        hy=(i2-xxx1)*(yyy2-yyy1)/(xxx2-xxx1)+yyy1;
      currentzhongjian[i2]=hy;
      }
    }
}

//*****************************************************������ƺ���**********************************************************//
int DJ_mid=4200;//dj��mid�����ֵ������û�аڽ�
void servo()//������ƺ���
{
    jiao=(int)(kp1*duojijiaodu/10-kd*(lastpiancha_4-duojijiaodu));//�����pid�㷨��ʽ��û��С��������kp1Ҫд�����ٳ���10��ʵ��С��
    if(jiao>=1000)  //�ȴ�����
    jiao=1000;
    if(jiao<=-1000)
    jiao=-1000;
    ftm_pwm_duty(FTM0,FTM_CH6,DJ_mid+jiao); //633��
} 
//***************************************************ɨ�躯��***************************************************************//
void lkcongzhongjiansaomiao()
{
  
	int zhangai_flag=0,qulv_s_y=0,qulv_s_l=0;
	int kuan_flag=0,lo=0,s_point=0,S_COUNT=0,fuduandian=0,chushizi_flag=0,qulv_yuanhuan=0;
	shangshizidiyidian=0;
	left_heixian[59]=0;
	right_heixian[59]=79; 
	shizishu=0;
	rushizi=0;
	xielv_flag=0;
	shizi_flag=0;
	my_lastzhongjian=39;
	memset(shaobudaozuo_flag,0,sizeof(shaobudaozuo_flag));//���㺯��
	memset(shaobudaoyou_flag,0,sizeof(shaobudaoyou_flag));

	if(currentzhongjian[58])
		currentzhongjian[59]=my_lastzhongjian=currentzhongjian[58];
	else
		currentzhongjian[59]=39;
	for(y=58;y>=0;y--)//ɨ����58������ͼ�������
	{
		for(x=my_lastzhongjian;x<=79;x++)//���м�����ɨ��
		{
			if(imgyiwei[y][x]==0)
			{
				right_heixian[y]=x;
				shaobudaoyou_flag[y]=1;    //�������ұ߶��ߣ�1��ʾɨ����
				break;
			}
		}

		for(x=my_lastzhongjian;x>=0;x--)//����ɨ��
		{ 
			if(imgyiwei[y][x]==0)
			{
				left_heixian[y]=x;   //��¼�ڼ����Ҳ�����
				shaobudaozuo_flag[y]=1;//ȷ��ĳһ��ɨ�����ı�־����1��ʾ����ɨ����������߶���
				break;
			}  
		}

        if(fuduandian==0)
        {
			if(y>48)//���߲��ߣ���������������
			{
				if(shaobudaoyou_flag[y]==0&&shaobudaozuo_flag[y]==1)//ɨ������
				{ 
					right_heixian[y]=left_heixian[y]+2*half_width_group[y];
				}
				else if(shaobudaoyou_flag[y]==1&&shaobudaozuo_flag[y]==0)//ɨ������
				{
					left_heixian[y]=right_heixian[y]-2*half_width_group[y];
				}
				else if(shaobudaoyou_flag[y]==0&&shaobudaozuo_flag[y]==0)//��ɨ����
				{
					left_heixian[y]=0;//������߶�ɨ������ֱ�Ӵ��м���ȡ����
					right_heixian[y]=79;
				}
			}
			else if(y<=48)//��Զ�Ĳ��ߣ�
			{
				if(shaobudaoyou_flag[y]==0&&shaobudaozuo_flag[y]==1)//ɨ������
				{ 
					right_heixian[y]=right_heixian[y+1]+(abs)(left_heixian[y]-left_heixian[y+1])-1;//���������һ������һ�㣬
																								//��y+1��Ϊ��������һ�ε�x���꣬
																	//left_heixian[y]-left_heixian[y+1]�����ƫ��������һΪ���ڲ���
				}
				else if(shaobudaoyou_flag[y]==1&&shaobudaozuo_flag[y]==0)//ɨ������
				{
				
					left_heixian[y]=left_heixian[y+1]-(abs)(right_heixian[y+1]-right_heixian[y])+1;//absΪȡ����ֵ
				}
				
				else if(shaobudaoyou_flag[y]==0&&shaobudaozuo_flag[y]==0)//��ɨ����
				{
					left_heixian[y]=0;
					right_heixian[y]=79;
				}
			}  

			//*************************************���ߴ���*********************************************************//
			currentzhongjian[y]=(int)((right_heixian[y]+left_heixian[y])/2);  //��ȡ�м��ߣ���߼��ұ߱�2��
				
			half_zhi[y]=(int)((right_heixian[y]-left_heixian[y])/2);  //һ������ֵ��û�ã����ģ�
				
			//*******************************************************�����˲���ֹ���߳���ë��**************************************************/
				
			if(currentzhongjian[y]-currentzhongjian[y+1]>4&&y<42&&B<0)
				currentzhongjian[y]=currentzhongjian[y+1]+1;
			if(currentzhongjian[y]-currentzhongjian[y+1]<-4&&y<42&&B>0)
				currentzhongjian[y]=currentzhongjian[y+1]-1;  


			/******************************************************************���ʼ���**************************************************************/
			if(y>30)//���ʽ����ж�  �õ�����qulv_jinduan
			{
				if((currentzhongjian[y]-currentzhongjian[y+1])>0)
					qulv_jinduan_right++;			//���˵�б��
				else
				if((currentzhongjian[y]-currentzhongjian[y+1])<0)
					qulv_jinduan_left++;
			} 


			if(y<25&&y>=7)//����Զ���жϣ�Զ����һ��Ͳ�Ҫ�� �õ�����qulv_yuanduan
			{
				if((currentzhongjian[y]-currentzhongjian[y+1])>0)
					qulv_yuandaun_right++;			//Զ�˵�б��
				else 
				if((currentzhongjian[y]-currentzhongjian[y+1])<0)
					qulv_yuandaun_left++;
			}
			if(y<=55&&y>10)//����ȫ���ж�   �õ�����qulv_quanju����
			{
				if((currentzhongjian[y]-currentzhongjian[y+1])>0)
					qvlv_quanju_right++;
				else
				if((currentzhongjian[y]-currentzhongjian[y+1])<0)
					qvlv_quanju_left++;
			}   

			if(currentzhongjian[y]>79) //���ߵ����Ʒ��� x����������y��������
				currentzhongjian[y]=79;
			if(currentzhongjian[y]<0)  //����������ͼ��Χ��0-79
				currentzhongjian[y]=0;

			my_lastzhongjian=currentzhongjian[y];//�����м������
			
			if(0<56)//Сsλ���жϣ�Сs�����ֱ�߳��
			{
				if((currentzhongjian[y]-currentzhongjian[y+2])>0)
					qulv_s_y++;
				else 
				if((currentzhongjian[y]-currentzhongjian[y+2])<0)
					qulv_s_l++;
				if(y>36&&abs(currentzhongjian[y]-currentzhongjian[y+2])>0)
				{
					qulv_yuanhuan++;
				}
				//printf("y:%d\n",qulv_s_y);
				//printf("l:%d\n",qulv_s_l);
			}
			if(y<58&&y>=10)
				S_COUNT+=currentzhongjian[y];
			// *******************************************СS�ϵ�����*********************************************//
			if(y>8&&(abs)(right_heixian[y]-currentzhongjian[y])<5||(abs)(left_heixian[y]-currentzhongjian[y])<5)//СS�ϵ��ж�
				s_point=y;//
			else
				s_point=0;

			//****************************************************�ϰ��ж�****************************************************************//
			if(y<52&&y>5&&qvlv_quanju<11&&duandian<5&&qulv_jinduan<=4&&dian1<9)
			{
				if(kuan_flag<=21&&zhangai_flag<2&&2*half_zhi[y]>2*half_width_group[y]-5)//������
				{
					kuan_flag++;
				//pl+=currentzhongjian[y];
				}
				else
				if(2*half_width_group[y]-2*half_zhi[y]>8&&kuan_flag>17)//������խ
				{
					zhangai_flag++;
					if(zhangai_flag==6)
					lo=(currentzhongjian[y]+currentzhongjian[y+1])/2-(currentzhongjian[55]+currentzhongjian[54])/2;
				}
				if(zhangai_flag>7&&kuan_flag>17&&2*half_zhi[y]>2*half_width_group[y]-8)//������
				{
					youshi_kuan_flag++;
				}
				if(youshi_kuan_flag>=4)
				{
					if(lo>2)
					{
					zhangai_left=1;
					zhangai_right=0;
					}
					else
					if(lo<-2)
					{
						
					zhangai_right=1;
					zhangai_left=0;
					}
					youshi_kuan_flag=0;
				}
				
			}
                  // *******************************************��ֹɨ���ܵ���*********************************************//
                  if(y<36&&((abs)(right_heixian[y]-currentzhongjian[y])<1||(abs)(left_heixian[y]-currentzhongjian[y])<1))//��ֹɨ���ܵ�����
                {
                      duandian=y;
                      fuduandian=y;
                      if(y>15)
                      {
                        duandianshu=y-15;
                        if(duandianshu>35)
                          duandianshu=35;
                      }
                        ///////// *********************************************************** ////////////////
                        ///////// *********************************************************** //////////////// 
                    if(y>qianzhan)
                      {
                        duandianshu1=y-qianzhan;
                        if(duandianshu1>25)
                          duandianshu1=25;
                      }
                    // if(DSYJ_y==28)
                      //  DSYJ_currentzhongjian[DSYJ_y]=79;
                    //break;
                }
                else 
                {
                  duandian=0;
                  duandianshu=0;
                  duandianshu1=0; 
                }
         }
    }
    /*if(right_heixian[y]-left_heixian[y]<half_width_group[y]&&right_heixian[y+1]-left_heixian[y+1]<half_width_group[y+1])//��ֹɨ���ܵ�����
          break;*/
    //}
    //********************************************************y�н�����־*******************************************************

    S_Z=S_COUNT/(48);

    //********************************************************************���ʼ���*******************************************************************
      qvlv_quanju=abs(qvlv_quanju_right-qvlv_quanju_left);//����ȫ��
      qulv_jinduan=abs(qulv_jinduan_right-qulv_jinduan_left);//���ʽ���
      qulv_yuandaun=abs(qulv_yuandaun_right-qulv_yuandaun_left);//����Զ��
      qvlv_quanju_right=qvlv_quanju_left=qulv_jinduan_right=qulv_jinduan_left=qulv_yuandaun_right=qulv_yuandaun_left=0;
      //�˴������������㣬�õ�ȫ������

    // *******************************************************ʮ�ִ���*********************************************************//

      if(duandian<16) // *****************************ʮ��
      {
          for(int i=58;i>7;i--)
          { 
            if(i>45&&(shaobudaozuo_flag[i]==1||shaobudaoyou_flag[i]==1))    //45�����ɨ�������ұ�ɨ������Ϊʮ��++
            rushizi++;
            if((i>9&&i<=40)&&shaobudaozuo_flag[i]==0&&shaobudaoyou_flag[i]==0)  //
              shizishu++;
            if(i<45&&(shaobudaozuo_flag[i]==1||shaobudaoyou_flag[i]==1)&&shangshizidiyidian==0)
              shangshizidiyidian=i;
          }
          if(shizishu>2&&rushizi>10)//����ʮ��
          {
              shizi_flag=1;
              //gpio_set(PTE1,1);
              xielv_flag=1;
              for(int i=49;i>0;i--)
              {      
              if(shaobudaozuo_flag[i]==0&&shaobudaoyou_flag[i]==0)
                {
                  shizidiyidian=i;
                  break;
                }     
              }
              if(shizidiyidian<34)
                {
                yy1=shizidiyidian+19;
                yy2=shizidiyidian+24;
              }
              else 
              if(shizidiyidian<40)
                {
                yy1=shizidiyidian+13;
                yy2=shizidiyidian+18;
              }
              else if(shizidiyidian<45)
              {
                yy1=shizidiyidian+9;
                yy2=shizidiyidian+13;
              }
              else if(shizidiyidian<49)
              {
                yy1=shizidiyidian+6;
                yy2=shizidiyidian+10;
              }else
                if(shizidiyidian<55)
              {
                yy1=shizidiyidian+2;
                yy2=shizidiyidian+4;
              }
              yy1_pinjun=(currentzhongjian[yy1]+currentzhongjian[yy1+1]+currentzhongjian[yy1-1])/3;
              yy2_pinjun=(currentzhongjian[yy2]+currentzhongjian[yy2+1]+currentzhongjian[yy2-1])/3;
              if(!ruyuanhuan_flag)
              huaxian(yy1,yy1_pinjun,yy2,yy2_pinjun); 
                
              //huaxian(yy1,currentzhongjian[yy1],yy2,currentzhongjian[yy2]); 
            }
        else if(shizishu>4&&rushizi<=10&&shangshizidiyidian>=20)//��ʮ��
          {
            chushizi_flag=1;
          // gpio_set(PTE1,1);
            xielv_flag=1;
            shizi_flag=0;
        if(!ruyuanhuan_flag)
          huaxian2(shangshizidiyidian-6,currentzhongjian[shangshizidiyidian-6],58,currentzhongjian[58]);

          }
              //  gpio_set(PTE1,0);

      } 
      //********************************************************Բ�����*******************************************************
   if(shizi_flag&&qulv_yuanhuan<=10&&qulv_jinduan<7&&!chushizi_flag)
    {
      
      signed char kkk=0,black_num=0;
      for( kkk=(int)(currentzhongjian[58]+currentzhongjian[57]+currentzhongjian[56])/3;kkk<=79;kkk++)//����ɨ��ڿ����
      {
        if(!imgyiwei[8][kkk]||!imgyiwei[10][kkk])
        {
           black_num++;
      
        }
        else
          break;
        
      }
      for( kkk=(int)(currentzhongjian[58]+currentzhongjian[57]+currentzhongjian[56])/3;kkk>=0;kkk--)//����ɨ��ڿ����
      {
          if(!imgyiwei[8][kkk]||!imgyiwei[10][kkk])
        {
        black_num++;
      
        }
        else
          break;
      }
      
      if(black_num>36)//��⵽Բ��
      {
        yuanhuan_flag++;
        //gpio_set(PTC18,0);//����led��ʾ
      }
      else
      {
        yuanhuan_flag=0;
        //gpio_set(PTC18,1);////�ر�led��ʾ
      }
    
    }
    else
    {
    yuanhuan_flag=0;
    //gpio_set(PTC18,1);//�ر�led��ʾ
    }
      
    if(yuanhuan_flag>3)//������⵽Բ����������
    {
    guai_flag=1;
    jiji++;
    //gpio_set(PTA14,1);
    }

    if(guai_flag&&guai_flag<=30)//������ٷ�ת��ʱ��
    {
    guai_flag++;
    if(guai_flag&&guai_flag<=30)//���ӹ��䱣�ֵ�ʱ��
    {
    //huaxian3(9,75,shizidiyidian,currentzhongjian[shizidiyidian+4]);
    ruyuanhuan_flag=1;
    }
    }
    else
    guai_flag=0;
    
    
    // ***********************************************************СS���ж�*СS���ж�*****************************************************//
        if(s_point==0&&qulv_s_y>6&&qulv_s_l>6&&zhidao_flag<20&&!shizi_flag)
        {
          s_wan_flag=1;
          //led(LED0, LED_ON);
        }
        else
        {
          s_wan_flag=0;
          //led(LED0, LED_OFF);
        }
        
        
        
}
    //************************************************ͼ�������,������ƫ���************************************************/



void pianchachuli()//ƫ���
{
        if(xielv_flag==0)
        regression(15+duandianshu,43+duandianshu);///б�ʼ���
        
        dian1=abs((currentzhongjian[52]+currentzhongjian[53]+currentzhongjian[54])/3-39);
        //lins=currentzhongjian[30];
        currentzhongjian_lk=(currentzhongjian[qianzhan+duandianshu1]-39);//��

    if(zhangaijishiright_flag)//�ϰ���ƫ���
    {
      currentzhongjian_lk-=5;
      B=0;
    }
    else if(zhangaijishileft_flag)
    {
      currentzhongjian_lk+=5;
      B=0;
    }
    if(B>19)
    B=19;
    if(B<-19)
    B=-19;

    my_piancha=(int)(1.1*currentzhongjian_lk-0.9*B);//0.95,0.32//ƫ��ϳɣ�����ת�䣬1.1���ĵ�+0,9����б�ʹ����ܵ�ƫ��
    
    if(0<ruyuanhuan_flag<10)//��50ms
    {
    ruyuanhuan_flag++;
    if(my_piancha<-4&&shizi_flag)//�ұ߽���Բ��
    my_piancha+=13;
    else
    if(my_piancha>4&&shizi_flag)//��߽���Բ��
    my_piancha-=13;
    }
    else
    ruyuanhuan_flag=0;
    

    if(S>30)//S��
    {
        kp1=400;
        //B=0;
        my_piancha=currentzhongjian[16]-39;
    }
    else
    if(abs(my_piancha)<5)//ֱ���ϣ�ƫ�����ֵС��5
    {
      kp1=kp-20;//ֱ���ϵ�P��Сһ�㣬��ֱֹ������
    }
    else
      kp1=kp;//����ֱ��P��Ҫ��һ�㡣������������ȣ��������ڲࡣ 



    B=0;
    if(star_lineflag)//��⵽������
      kp1=80;
    lastpiancha_4=lastpiancha_3;
    lastpiancha_3=lastpiancha_2;
    lastpiancha_2=lastpiancha_1;
    lastpiancha_1=duojijiaodu;
    duojijiaodu=my_piancha; 
    servo();//������ƺ���
}