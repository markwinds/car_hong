//作者： 
//时间：
#include "saomiao.h"
#include "common.h"
#include "include.h"
#include "math.h"
int qianzhan=29;
int kp=200,kd=0,my_piancha,my_lastzhongjian=40,currentzhongjianzhi=40,rightheixian_flag=0,leftheixian_flag=0,xielv;
int jiao, x,y,linshi_x,linshi_right_heixian,linshi_y,mm=0,nn=0;
int ruyuanhuan_flag=0,chuhuanyou_flag=0,chuhuanzuo_flag=0;
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
char s_wan_flag,shizi_flag=0,yuanhuan_flag=0,guai_flag=0;
int qvlv_quanju,qulv_jinduan,qulv_yuandaun;
int qulv_jinduan_right=0,qulv_jinduan_left=0,qulv_yuandaun_right=0,qulv_yuandaun_left=0,qvlv_quanju_right=0,qvlv_quanju_left=0;
int half_zhi[60];
int yy1_pinjun,yy2_pinjun;
extern char S;
int kp1;

char jiji=0,papa=0,chuhuan_you=0,chuhuan_zuo=0;

int yuan_diu=0,jieduan=0,qishihang=0;
int dierge=0;
extern char jieduan1_right=0,jieduan2_right=0,jieduan3_right=0,jieduan4_right=0,jieduan3_right_count=0;
char street_width=0;
char street_len=0;
char cur_L_ready_flag=0;         //左圆环预判断初始识别标志
char cur_L_ready_delay_flag=0;   //左圆环预判断弛懈标志
uint16 cur_L_ready_time_flag=0;   //左圆环预判断计时变量
char cur_L_ready_rest_flag=0;    //左圆环预判断复位变量
char cur_R_ready_flag=0;         //右圆环预判断初始识别标志
char cur_R_ready_delay_flag=0;   //右圆环预判断弛懈标志



char cur_R_diyi_flag=0; 
char cur_L_diyi_flag=0; 
char cur_R_nei_flag=0; 
char cur_L_nei_flag=0; 
uint16 cur_R_diyi_time_flag=0;
uint16 cur_R_nei_time_flag=0;
uint16 cur_L_diyi_time_flag=0;
uint16 cur_L_nei_time_flag=0;

uint16 cur_R_ready_time_flag=0;   //右圆环预判断计时变量
char cur_R_ready_rest_flag=0;    //右圆环预判断复位变量

/*圆环准确识别*/
char cur_L_real_flag=0;          //左圆环准确判断识别标志
char cur_L_real_delay_flag=0;    //左圆环准确弛懈识别标志
char cur_L_real_rest_flag=0;     //左圆环准确复位识别标志
uint16 cur_L_real_time_flag=0;    //左圆环准确弛懈识别标志
uint16 cur_L_real_time_flag1=0;   //左圆环准确弛懈识别标志1

char cur_R_real_flag=0;          //右圆环准确判断识别标志
char cur_R_real_delay_flag=0;    //右圆环准确弛懈识别标志
char cur_R_real_rest_flag=0;     //右圆环准确复位识别标志

char cur_R_real_into_flag=0;     //右圆环准确入环识别标志
char cur_L_real_into_flag=0;     //右圆环准确入环识别标志

char cur_R_real_CH_flag=0;
char cur_L_real_CH_flag=0;

uint16 cur_R_real_time_flag=0;    //右圆环准确弛懈识别标志
uint16 cur_R_real_time_flag1=0;   //右圆环准确弛懈识别标志1


static int half_width_group[60]=
{
14,16,16,17,17,18,18,18,19,19,
20,20,21,21,22,22,23,23,23,25,
25,25,25,26,26,26,27,27,28,28,
28,29,29,30,30,30,31,31,32,33,
33,33,33,33,34,34,34,35,35,35,
36,36,36,36,37,37,38,38,38,38      
};                                                      //权值不一样，越远越模糊
int regression(int startline,int endline)   //线性回归方程计算斜率      
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
void huaxian(int x1,int y1,int x2,int y2)//将两个点之间连成一条线段
{
      int i,max,a1,a2;
      a1=x1;
      a2=x2;
      if(a1>a2)
      {max=a1;
      a1=a2;
      a2=max;}
    for(i=x1;i>0;i--)
    {
      if((x2-x1)!=0)
      {
         hy=(i-x1)*(y2-y1)/(x2-x1)+y1;
         currentzhongjian[i]=hy;
      if(hy<=1||hy>=79)
        break;
      }
    }
}

void huaxian2(int xxx1,int yyy1,int xxx2,int yyy2)//两点之间的线段
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

void huaxian3(int xxx1,int yyy1,int xxx2,int yyy2)//两点之间的线段
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

//*****************************************************舵机控制函数**********************************************************//
int DJ_mid=4220;//dj—mid舵机中值，轮子没有摆脚
void servo()//舵机控制函数
{
    jiao=(int)(kp1*duojijiaodu/10-kd*(lastpiancha_4-duojijiaodu));//舵机的pid算法公式，没有小数，所以kp1要写整数再除以10来实现小数
    if(jiao>=1000)  //舵机限幅度
    jiao=1000;
    if(jiao<=-1000)
    jiao=-1000;
    ftm_pwm_duty(FTM0,FTM_CH6,DJ_mid+jiao); //633，
} 
//***************************************************扫描函数***************************************************************//
void lkcongzhongjiansaomiao()
{
  
      int kuan_flag=0,lo=0,s_point=0,S_COUNT=0,fuduandian=0,chushizi_flag=0,qulv_yuanhuan=0;
      memset(shaobudaozuo_flag,0,sizeof(shaobudaozuo_flag));//清零函数
      memset(shaobudaoyou_flag,0,sizeof(shaobudaoyou_flag));
      int zhangai_flag=0,qulv_s_y=0,qulv_s_l=0;
      shangshizidiyidian=0;
      left_heixian[59]=0;
      right_heixian[59]=79; 
      shizishu=0;
      rushizi=0;
      xielv_flag=0;
      shizi_flag=0;
      my_lastzhongjian=39;

      if(currentzhongjian[58])
      currentzhongjian[59]=my_lastzhongjian=currentzhongjian[58];
      else
      currentzhongjian[59]=39;
      for(y=58;y>=0;y--)//扫描完58，整副图像处理完毕
      {
        
            for(x=my_lastzhongjian;x<=79;x++)//从中间向右扫描
            {
              if(imgyiwei[y][x]==0)
                {
                    
                  right_heixian[y]=x;
                  shaobudaoyou_flag[y]=1;    //这里是右边丢线
                  break;
                }
             }

                
             for(x=my_lastzhongjian;x>=0;x--)//向左扫描
             { 
                if(imgyiwei[y][x]==0)
                {
                    left_heixian[y]=x;   //记录第几列找不到线
                    shaobudaozuo_flag[y]=1;//确定某一行扫不到的标志，用1表示产生扫到，否则左边丢线
                    break;
                }  
              }
             //边线扫完 
        if(fuduandian==0)
        {
                if(y>48)//丢边补线，加整个赛道补线
                {
                     if(shaobudaoyou_flag[y]==0&&shaobudaozuo_flag[y]==1)//扫不到右
                        { 
                          right_heixian[y]=left_heixian[y]+2*half_width_group[y];
                        }
                     else if(shaobudaoyou_flag[y]==1&&shaobudaozuo_flag[y]==0)//扫不到左
                        {
                          left_heixian[y]=right_heixian[y]-2*half_width_group[y];
                        }
                    else if(shaobudaoyou_flag[y]==0&&shaobudaozuo_flag[y]==0)//都扫不到
                        {
                          left_heixian[y]=0;//如果两边都扫不到，直接从中间提取中线
                          right_heixian[y]=79;
                        }
                }
                else if(y<=48)//更远的补线，
                {
                      if(shaobudaoyou_flag[y]==0&&shaobudaozuo_flag[y]==1)//扫不到右
                        { 
                    
                          right_heixian[y]=right_heixian[y+1]+(abs)(left_heixian[y]-left_heixian[y+1])-1;//根据左边这一点与上一点，
                           //（y+1）为数组中上一次的x坐标，
                          //left_heixian[y]-left_heixian[y+1]算左边偏移量，减一为后期补偿
                        }
                      else if(shaobudaoyou_flag[y]==1&&shaobudaozuo_flag[y]==0)//扫不到左
                        {
                      
                          left_heixian[y]=left_heixian[y+1]-(abs)(right_heixian[y+1]-right_heixian[y])+1;//abs为取绝对值
                        }
                        
                      else if(shaobudaoyou_flag[y]==0&&shaobudaozuo_flag[y]==0)//都扫不到
                        {
                          left_heixian[y]=0;
                          right_heixian[y]=79;
                        }
                }  //补线完成，左右边线拟合完成
                
                    //*************************************中线处理*********************************************************//
                  
                currentzhongjian[y]=(int)((right_heixian[y]+left_heixian[y])/2);  //提取中间线（左边加右边比2）
                  
                half_zhi[y]=(int)((right_heixian[y]-left_heixian[y])/2);  //一半赛道值（没用，不改）
                    
                      //*******************************************************中线滤波防止中线出现毛刺**************************************************/
                  
                if(currentzhongjian[y]-currentzhongjian[y+1]>4&&y<42&&B<0)
                currentzhongjian[y]=currentzhongjian[y+1]+1;
                if(currentzhongjian[y]-currentzhongjian[y+1]<-4&&y<42&&B>0)
                currentzhongjian[y]=currentzhongjian[y+1]-1;  

                /*以上是对整个赛道的中线提取，下面是偏差度*/
                /******************************************************************曲率计算**************************************************************/
                if(y>30)//曲率近端判断  用到变量qulv_jinduan
                {
                    if((currentzhongjian[y]-currentzhongjian[y+1])>0)
                  qulv_jinduan_right++;
                  else
                  if((currentzhongjian[y]-currentzhongjian[y+1])<0)
                  qulv_jinduan_left++;
                } 


                if(y<25&&y>=7)//曲率远端判断，远处的一点就不要了 用到变量qulv_yuanduan
                {
                    if((currentzhongjian[y]-currentzhongjian[y+1])>0)
                  qulv_yuandaun_right++;
                  else if((currentzhongjian[y]-currentzhongjian[y+1])<0)
                  qulv_yuandaun_left++;
                }
                if(y<=55&&y>10)//曲率全局判断   用到变量qulv_quanju左右
                {
                    if((currentzhongjian[y]-currentzhongjian[y+1])>0)
                  qvlv_quanju_right++;
                  else
                  if((currentzhongjian[y]-currentzhongjian[y+1])<0)
                  qvlv_quanju_left++;
                }   

                if(currentzhongjian[y]>79) //中线的限制幅度 x代表行数，y代表列数
                  currentzhongjian[y]=79;
                if(currentzhongjian[y]<0)  //这里限制在图像范围内0-79
                  currentzhongjian[y]=0;

                my_lastzhongjian=currentzhongjian[y];//保存中间点坐标  已经产生中线点当前行数对应的列数
                
                if(0<56)//小s位置判断，小s弯道作直线冲刺
                {
                    if((currentzhongjian[y]-currentzhongjian[y+2])>0)
                    qulv_s_y++;
                    else
                    if((currentzhongjian[y]-currentzhongjian[y+2])<0)
                    qulv_s_l++;
                    
                    if(y>36&&abs(currentzhongjian[y]-currentzhongjian[y+2])>0)
                    {
                      
                    }
                    //printf("y:%d\n",qulv_s_y);
                    //printf("l:%d\n",qulv_s_l);
                }
                if(y<58&&y>=10)
                S_COUNT+=currentzhongjian[y];
                
                // *******************************************小S断点搜索*********************************************//
                if(y>8&&(abs)(right_heixian[y]-currentzhongjian[y])<5||(abs)(left_heixian[y]-currentzhongjian[y])<5)//小S断点判定
                  s_point=y;//
                else
                  s_point=0;

                //****************************************************障碍判定****************************************************************//
                if(y<52&&y>5&&qvlv_quanju<11&&duandian<5&&qulv_jinduan<=4&&dian1<9)
                {
                      if(kuan_flag<=21&&zhangai_flag<2&&2*half_zhi[y]>2*half_width_group[y]-5)//宽赛道
                      {
                          kuan_flag++;
                      //pl+=currentzhongjian[y];
                      }else
                    if(2*half_width_group[y]-2*half_zhi[y]>8&&kuan_flag>17)//赛道变窄
                    {
                      zhangai_flag++;
                      if(zhangai_flag==6)
                      lo=(currentzhongjian[y]+currentzhongjian[y+1])/2-(currentzhongjian[55]+currentzhongjian[54])/2;
                    }
                    if(zhangai_flag>7&&kuan_flag>17&&2*half_zhi[y]>2*half_width_group[y]-8)//宽赛道
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
                  // *******************************************防止扫到跑道外*********************************************//
                  if(y<36&&((abs)(right_heixian[y]-currentzhongjian[y])<1||(abs)(left_heixian[y]-currentzhongjian[y])<1))//防止扫到跑道外面
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
    /*if(right_heixian[y]-left_heixian[y]<half_width_group[y]&&right_heixian[y+1]-left_heixian[y+1]<half_width_group[y+1])//防止扫到跑道外面
          break;*/
    //}
    //********************************************************y行结束标志*******************************************************

    S_Z=S_COUNT/(48);

    //********************************************************************曲率计算*******************************************************************
      qvlv_quanju=abs(qvlv_quanju_right-qvlv_quanju_left);//曲率全局
      qulv_jinduan=abs(qulv_jinduan_right-qulv_jinduan_left);//曲率近端
      qulv_yuandaun=abs(qulv_yuandaun_right-qulv_yuandaun_left);//曲率远端
      qvlv_quanju_right=qvlv_quanju_left=qulv_jinduan_right=qulv_jinduan_left=qulv_yuandaun_right=qulv_yuandaun_left=0;
      //此处三个曲率清零，得到所有曲率

    // *******************************************************十字处理*********************************************************//

      if(duandian<16) // *****************************十字
      {
          for(int i=58;i>7;i--)
          { 
            if(i>45&&(shaobudaozuo_flag[i]==1||shaobudaoyou_flag[i]==1))    //45行左边扫bu到，右边扫不到则为十字++
            rushizi++;
            if((i>9&&i<=40)&&shaobudaozuo_flag[i]==0&&shaobudaoyou_flag[i]==0)  //
              shizishu++;
            if(i<45&&(shaobudaozuo_flag[i]==1||shaobudaoyou_flag[i]==1)&&shangshizidiyidian==0)
              shangshizidiyidian=i;
          }
          if(shizishu>2&&rushizi>10)//刚入十字
          {
              shizi_flag=1;
              //gpio_set(PTE1,1);
              xielv_flag=1;
              for(int i=49;i>0;i--)
              {      
              if(shaobudaozuo_flag[i]==0&&shaobudaoyou_flag[i]==0)
                {
                  shizidiyidian=i;   //开循环找十字第一点
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
         else if(shizishu>4&&rushizi<=10&&shangshizidiyidian>=20)//出十字
          {
               chushizi_flag=1;
               // gpio_set(PTE1,1);
               xielv_flag=1;
               shizi_flag=1;
               if(!ruyuanhuan_flag)
               huaxian2(shangshizidiyidian-6,currentzhongjian[shangshizidiyidian-6],58,currentzhongjian[58]);

          }
              //  gpio_set(PTE1,0);

      } 
      






      //********************************************************圆环检测*******************************************************
	//-------------------圆环参数初始化----------------------
	yuan_diu=1;
	jieduan=0;
	qishihang=0;
	street_len=0; //赛道长度
	street_width=0;//赛宽
	cur_R_ready_time_flag++;
	cur_R_real_time_flag++; 
	cur_L_ready_time_flag++;
	cur_L_real_time_flag++;   



	cur_R_diyi_time_flag++;
	cur_R_nei_time_flag++;
	cur_L_diyi_time_flag++;
	cur_L_nei_time_flag++;  

	/*扫赛道长度*/
	for(int i=55;i>0;i--)
	{
		if(imgyiwei[i][39]!=0)
		{
			street_len++;
		}
		else
		{
			break;
		}
	}
	for(int i=39;i<79;i++)		//扫赛道的宽度
	{
		if(imgyiwei[35][i]==0 || i==78)
		{
			street_width=i;
			break;
		}
	}
	for(int i=39;i>0;i--)
	{
		if(imgyiwei[35][i]==0 || i == 1)
		{
			street_width-=i;
			break;
		}
	}
    

	//---------------------------右圆环判断----------------------
	int i=35;
	if(yuan_diu == 1 && i == 35)    //右圆环
	{
		//在35行36行处左边不丟线,右边丟线.赛道长度大于46.宽度大于50.35行左边赛道在[5,25]范围内.
		if(shaobudaozuo_flag[i] ==1 && shaobudaozuo_flag[i+2] ==1 && shaobudaoyou_flag[i]==0 &&shaobudaoyou_flag[i+2]==0
		&& street_len >46 && street_width>50 && left_heixian[i]>5 && left_heixian[i]<25)
		{          
			cur_R_ready_flag = 1;
		}

		if(cur_R_ready_flag||cur_R_diyi_flag) //交换第一段标志
		{
			cur_R_ready_flag = 0;                //标志交换，清空第一段，多清空一次，防止bug
			cur_R_diyi_flag = 1;                 //第一段标志   
		
			//在0.4秒内,在35行36行处右边左边都不丟线,左边赛道在[5,25]范围内,赛道长度大于43.
			if(cur_R_diyi_flag && shaobudaoyou_flag[i]==1 && shaobudaoyou_flag[i+2] && shaobudaozuo_flag[i]==1
			&&shaobudaozuo_flag[i+2]==1 && street_len>43 &&left_heixian[i]>5 && left_heixian[i]<25)
			{
				cur_R_ready_rest_flag = 1;            //内圆标志
			}
			if(cur_R_diyi_time_flag > 60) 
			{     //第一段找到后0.4s后自动清空  防止第一段误判且没有找到内圆 一直保留第一段标志
				cur_R_diyi_flag = 0;
			}
		}
		else
		{
			cur_R_diyi_flag = 0;
			cur_R_diyi_time_flag = 0;
		}
		if(cur_R_ready_rest_flag||cur_R_nei_flag) //交换内圆标志 第一段和内圆准备标志全清空
		{
			
			cur_R_diyi_flag = 0;
			cur_R_ready_rest_flag = 0;
			cur_R_nei_flag = 1;         
			//在的二段后0.4秒内:在35行36行处左边不丟线,右边丟线.赛道长度大于40.宽度大于50.35行左边赛道在[10,30]范围内.
			if(1)//(cur_R_nei_flag && shaobudaozuo_flag[i]==1 && shaobudaozuo_flag[i+2]==1 && shaobudaoyou_flag[i]==0
			//&&shaobudaozuo_flag[i+2]==0 && street_len>40 && street_width>50 && left_heixian[i]>10 && left_heixian[i]<30)//
			{                             
			cur_R_real_flag = 1;  
			//jiji++;
			}            //第二段丢线标志            
			if(cur_R_nei_time_flag > 60) {     //第内圆找到后0.4s后自动清空  防止内圆误判且没有找到第二段 一直保留内圆标志
				cur_R_nei_flag = 0;}          
		}
		else 
		{
			cur_R_nei_flag = 0;
			cur_R_nei_time_flag = 0;
		}
	}
	/*右准确识别*/
	if(cur_R_real_flag||cur_R_real_delay_flag)   //交换第二段标志，即圆环总标志
	{ 
		cur_R_nei_flag = 0;
		cur_R_real_flag = 0;
		cur_R_real_CH_flag=0;        
		cur_R_real_delay_flag = 1;                 //圆环总标志  
		guai_flag=1;
        //33行大概0.4秒左右延时后,如果全是空,判断出环。

        i=33;
		//       if(imgyiwei[50][0]!=0 && imgyiwei[45][0]!=0 && imgyiwei[40][0]!=0 && imgyiwei[34][0]!=0 &&
		//          imgyiwei[28][0]==0 && imgyiwei[20][0]==0 && imgyiwei[10][0]==0 &&
		//          imgyiwei[5][79]==0 && imgyiwei[10][79]==0 && imgyiwei[50][79]==0 && imgyiwei[40][79]==0 &&
		//          imgyiwei[20][79]!=0 && imgyiwei[25][79]!=0 && imgyiwei[30][79]!=0 
		//          )
		//       {
		//           cur_R_real_rest_flag = 1;        //出圆环标志
		//           jiji++;
		//        
		//        }
        
        //if(left_heixian[15]>left_heixian[12] && left_heixian[15]>left_heixian[18] && i==33 &&cur_R_real_time_flag>40)
		if(
			imgyiwei[18][0]!=0 && imgyiwei[20][0]!=0 && imgyiwei[22][0]!=0 && imgyiwei[24][0]!=0 &&
			imgyiwei[10][0]==0 && imgyiwei[14][0]==0 && imgyiwei[34][0]==0 && imgyiwei[40][0]==0 &&
			shaobudaozuo_flag[18]==0 && shaobudaozuo_flag[20]==0 && shaobudaozuo_flag[22]==0 &&
			shaobudaozuo_flag[24]==0
			)
		{
				cur_R_real_rest_flag = 1;        //出圆环标志
				chuhuan_you=1;
		}
		//          for(int j = 0; j <= 79; j++){
		//            if(imgyiwei[i][j]){
		//              cur_R_real_CH_flag++;
		//              if(cur_R_real_CH_flag>55){
		//                cur_R_real_rest_flag = 1;        //出圆环标志
		//               
		//                  jiji++;
		//                break;}}}}
        

        if(cur_R_real_rest_flag) cur_R_real_time_flag1++;  //找到出圆环标志，开始计数
        
        i=21;
        if(cur_R_real_time_flag1>40&&shaobudaozuo_flag[i]==1 && shaobudaoyou_flag[i]==1)
		//      if(i==21&&cur_R_real_rest_flag&&cur_R_real_time_flag1>40&&!Left_Add_Flag[i]&&!Left_Add_Flag[i+2]&&Left_Add_Line[i]>50&&Left_Add_Line[i+2]<60)
        {       
          cur_R_real_delay_flag = 0;
        }         //圆环结束，总标志清空      
    }
	else
	{
		cur_R_real_delay_flag = 0;            //圆环总标志清空
		cur_R_real_time_flag = 0;             //圆环总标志找到后，开始计数，作为入环的延时
		cur_R_real_time_flag1 = 0;
		cur_R_real_rest_flag = 0;             //出圆环标志清空
    }
      












      /***********************************************************************************/ //左圆环
      i=35;
          if(yuan_diu == 1 && i == 35)
      {
        //jiji++;
        //在35行36行处左边不丟线,右边丟线.赛道长度大于46.宽度大于50.35行左边赛道在[5,25]范围内.
        if(shaobudaoyou_flag[i] ==1 && shaobudaoyou_flag[i+2] ==1 && shaobudaozuo_flag[i]==0 &&shaobudaozuo_flag[i+2]==0
        && street_len >46 && street_width>50 )
        {          
          cur_L_ready_flag = 1;
          
          //jiji++;
          
        }
        else
          ;
        
        if(cur_L_ready_flag||cur_L_diyi_flag) //交换第一段标志
        {
          cur_L_ready_flag = 0;                //标志交换，清空第一段，多清空一次，防止bug
          cur_L_diyi_flag = 1;                 //第一段标志   
          
          //在0.4秒内,在35行36行处右边左边都不丟线,左边赛道在[5,25]范围内,赛道长度大于43.
          if(cur_L_diyi_flag && shaobudaozuo_flag[i]==1 && shaobudaozuo_flag[i+2] && shaobudaoyou_flag[i]==1
          &&shaobudaoyou_flag[i+2]==1 && street_len>43)
          {
            cur_L_ready_rest_flag = 1;            //内圆标志
           // papa++;
            //jiji++;
            }
          else ;
          if(cur_L_diyi_time_flag > 60) {     //第一段找到后0.4s后自动清空  防止第一段误判且没有找到内圆 一直保留第一段标志
              cur_L_diyi_flag = 0;}
        }
        else
        {
          cur_L_diyi_flag = 0;
          cur_L_diyi_time_flag = 0;
        }
       //?
        if(cur_L_ready_rest_flag||cur_L_nei_flag) //交换内圆标志 第一段和内圆准备标志全清空
        {
          
          cur_L_diyi_flag = 0;
          cur_L_ready_rest_flag = 0;
          cur_L_nei_flag = 1;         
          //在的二段后0.4秒内:在35行36行处左边不丟线,右边丟线.赛道长度大于40.宽度大于50.35行左边赛道在[10,30]范围内.
          if(1)//(cur_L_nei_flag && shaobudaozuo_flag[i]==1 && shaobudaozuo_flag[i+2]==1 && shaobudaoyou_flag[i]==0
          //&&shaobudaozuo_flag[i+2]==0 && street_len>40 && street_width>50 && left_heixian[i]>10 && left_heixian[i]<30)//
          {                             
            cur_L_real_flag = 1;  
            //jiji++;
            }            //第二段丢线标志            
          if(cur_L_nei_time_flag > 60) {     //第内圆找到后0.4s后自动清空  防止内圆误判且没有找到第二段 一直保留内圆标志
              cur_L_nei_flag = 0;}          
        }
        else 
        {
          cur_L_nei_flag = 0;
          cur_L_nei_time_flag = 0;
        }
      }
      /*左准确识别*/
      if(cur_L_real_flag||cur_L_real_delay_flag)   //交换第二段标志，即圆环总标志
      { 
        //led(LED1, LED_ON);
        cur_L_nei_flag = 0;
        cur_L_real_flag = 0;
        cur_L_real_CH_flag=0;        
        cur_L_real_delay_flag = 1;                 //圆环总标志  
        guai_flag=1;
        //papa++;
        
        //33行大概0.4秒左右延时后,如果全是空,判断出环。
        /****************************************/ 
        i=33;
//       if(imgyiwei[50][0]!=0 && imgyiwei[45][0]!=0 && imgyiwei[40][0]!=0 && imgyiwei[34][0]!=0 &&
//          imgyiwei[28][0]==0 && imgyiwei[20][0]==0 && imgyiwei[10][0]==0 &&
//          imgyiwei[5][79]==0 && imgyiwei[10][79]==0 && imgyiwei[50][79]==0 && imgyiwei[40][79]==0 &&
//          imgyiwei[20][79]!=0 && imgyiwei[25][79]!=0 && imgyiwei[30][79]!=0 
//          )
//       {
//           cur_L_real_rest_flag = 1;        //出圆环标志
//           jiji++;
//        
//        }
        
        //if(left_heixian[15]>left_heixian[12] && left_heixian[15]>left_heixian[18] && i==33 &&cur_L_real_time_flag>40)
          if(
             imgyiwei[18][79]!=0 && imgyiwei[20][79]!=0 && imgyiwei[22][79]!=0 && imgyiwei[24][79]!=0 &&
             imgyiwei[10][79]==0 && imgyiwei[14][79]==0 && imgyiwei[34][79]==0 && imgyiwei[40][79]==0 &&
             shaobudaoyou_flag[18]==0 && shaobudaoyou_flag[20]==0 && shaobudaoyou_flag[22]==0 &&
             shaobudaoyou_flag[24]==0
               )
        {
                  cur_L_real_rest_flag = 1;        //出圆环标志
                  chuhuan_zuo=1;
                  //jiji++;
          }
//          for(int j = 0; j <= 79; j++){
//            if(imgyiwei[i][j]){
//              cur_L_real_CH_flag++;
//              if(cur_L_real_CH_flag>55){
//                cur_L_real_rest_flag = 1;        //出圆环标志
//               
//                  jiji++;
//                break;}}}}
        

        if(cur_L_real_rest_flag) cur_L_real_time_flag1++;  //找到出圆环标志，开始计数
        
        i=21;
        if(i==21&&cur_L_real_time_flag1>40&&shaobudaoyou_flag[i]==1 && shaobudaozuo_flag[i]==1)
//      if(i==21&&cur_L_real_rest_flag&&cur_L_real_time_flag1>40&&!Left_Add_Flag[i]&&!Left_Add_Flag[i+2]&&Left_Add_Line[i]>50&&Left_Add_Line[i+2]<60)
        {       
          cur_L_real_delay_flag = 0;
        }         //圆环结束，总标志清空      
      }
      else
      {
        //led(LED1, LED_OFF);
        cur_L_real_delay_flag = 0;            //圆环总标志清空
        cur_L_real_time_flag = 0;             //圆环总标志找到后，开始计数，作为入环的延时
        cur_L_real_time_flag1 = 0;
        cur_L_real_rest_flag = 0;             //出圆环标志清空
      }
  








  
/****************************圆环减速****************************/

     /***********上面是检测圆环，下面开始操作圆环************************/
  
    
    if(guai_flag && guai_flag<=15)//电机减速反转的时间 5ms*30=150ms
    {
        guai_flag++;

        if(guai_flag&&guai_flag<=15)//轮子拐弯保持的时间
        {
           //huaxian3(9,75,shizidiyidian,currentzhongjian[shizidiyidian+4]);
           ruyuanhuan_flag=1;
        }
    }
    else
    {
         guai_flag=0;  
         
    }  
    //出环右
    if(chuhuan_you &&chuhuan_you<=10)
    {
       chuhuan_you++;
       if(chuhuan_you && chuhuan_you<=10)
       {
         chuhuanyou_flag=1;
       }
    }
    else
    {
       chuhuan_you=0;
    }
    //出环左    
    if(chuhuan_zuo &&chuhuan_zuo<=20)
    {
       chuhuan_zuo++;
       if(chuhuan_zuo && chuhuan_zuo<=20)
       {
         chuhuanzuo_flag=1;
       }
    }
    else
    {
       chuhuan_zuo=0;
    }
  /*****************************操作圆环结束************/

    // ***********************************************************小S弯判定*小S弯判定*****************************************************//
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
    //************************************************图像处理结束,下面是偏差处理************************************************/



void pianchachuli()//偏差处理
{
        if(xielv_flag==0)
        regression(15+duandianshu,43+duandianshu);///斜率计算
        
        dian1=abs((currentzhongjian[52]+currentzhongjian[53]+currentzhongjian[54])/3-39);
        //lins=currentzhongjian[30];
        currentzhongjian_lk=(currentzhongjian[qianzhan+duandianshu1]-39);//点

    if(zhangaijishiright_flag)//障碍的偏差处理
    {
      currentzhongjian_lk-=5;
      B=0;
    }
    else if(zhangaijishileft_flag)
    {
      currentzhongjian_lk+=5;
      B=0;
    }
    if(B>19)     //斜率限幅
    B=19;
    if(B<-19)
    B=-19;

    my_piancha=(int)(1.1*currentzhongjian_lk-0.9*B);//0.95,0.32//偏差合成，控制转弯，1.1倍的点+0,9倍的斜率构成总的偏差
   /**********************************圆环偏差处理**************/ 
    if(ruyuanhuan_flag>0 && ruyuanhuan_flag<10)//拐50ms
    {
          //jiji++;
          ruyuanhuan_flag++;
          if(my_piancha<-4)//右边进的圆环
          my_piancha-=60;
          else
          if(my_piancha>4)//左边进的圆环
          my_piancha+=60;
    }
    else
    {
       ruyuanhuan_flag=0;
    }
    //出环右
        if(chuhuanyou_flag>0 && chuhuanyou_flag<5)//拐50ms
    {
          //jiji++;
          chuhuanyou_flag++;
          my_piancha+=60;
          cur_R_real_flag=0;          //右圆环准确判断识别标志
          cur_R_real_delay_flag=0;    //右圆环准确弛懈识别标志
          cur_R_real_rest_flag=0;     //右圆环准确复位识别标志

          cur_R_real_into_flag=0;     //右圆环准确入环识别标志
          cur_L_real_into_flag=0;     //右圆环准确入环识别标志
    }
    else
    {
       chuhuanyou_flag=0;
    }
//   //出环左
    if(chuhuanzuo_flag>0 && chuhuanzuo_flag<5)//拐50ms
    {
          //jiji++;
          chuhuanzuo_flag++;
          my_piancha-=40;
          cur_R_real_flag=0;          //右圆环准确判断识别标志
          cur_R_real_delay_flag=0;    //右圆环准确弛懈识别标志
          cur_R_real_rest_flag=0;     //右圆环准确复位识别标志

          cur_R_real_into_flag=0;     //右圆环准确入环识别标志
          cur_L_real_into_flag=0;     //右圆环准确入环识别标志
    }
    else
    {
       chuhuanzuo_flag=0;
    }
      
    /*******************圆环偏差结束***************************/
    if(S>30)//S弯
    {
        kp1=400;
        //B=0;
        my_piancha=currentzhongjian[16]-39;
    }
    else
    if(abs(my_piancha)<5)//直道上，偏差绝对值小于5
    {
      kp1=kp-20;//直道上的P，小一点，防止直道抖动
    }
    else
      kp1=kp;//不是直道P就要大一点。以增大拐弯力度，切赛道内侧。 

//    if(ruyuanhuan_flag!=0)
//    {
//       kp1=150;
//    }

    B=0;
    if(star_lineflag)//检测到起跑线
      kp1=80;
    lastpiancha_4=lastpiancha_3;
    lastpiancha_3=lastpiancha_2;
    lastpiancha_2=lastpiancha_1;
    lastpiancha_1=duojijiaodu;
    duojijiaodu=my_piancha; 
    servo();//舵机控制函数
}