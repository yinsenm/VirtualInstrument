/////////////////////
//步进电机部分
/////////////////////
/*
	描述：步进电机初始化
	功能：上电或超量程，步进电机初始化到原点
*/
void Mot_Init()
{
	uint step=0;//步进电机步数初始化为0
	uchar i;//脉冲计数
	DIR=1;//确定回原点方向
	EN=0;//使能
	if(ORI==1)//原点信号高电平
	{
		delay(20);//延时5ms
		if(ORI==1)//仍为高电平，则判断触发原点
		{
			while(ORI!=0)//直到原点为低电平停止
			{
				for(i=0;i<2;i++)
				{
					PUL=~PUL;
					delay(2);
				}
				step++;
				change2(a,step);//显示步数
			}
		}
		change2(a,0);//数码管归零
	}
	Posit=0;//位置为0（原点）
	Buzz(3,2);//发三声2HZ
	EN=1;//关闭使能
}
/*
	描述：步进电机向左、向右走80mm
	功能：驱动步进电机前进或后退
*/

void Motor(uint step,uchar dir)
{
	uchar i;
	uint j=0;
	if(dir)//确定方向
	{
		DIR=0;
	}
	else
	{
		DIR=1;
	}
	EN=0;//使能
	while((step--))
	{
		if(step<400||step>STEP-400)//前后400步为低速
		{
			for(i=0;i<2;i++)
			{
				PUL=~PUL;
				delay(2);
			}
		}
		else
		{		 
			for(i=0;i<2;i++)
			{
				PUL=~PUL;
				delay(1);
			}
		}
		if(step%5==0)
		{
			
			j=j+1;
			if(dir)
			{
				change2(a,j); //前进显示
			}
			else
			{
				change2(a,STEP/5-j);//后退显示
			}
		}
		if(EXC==0)//超程处理，返回原点
		{
			delay(20);
			if(EXC==0)
			{
				Mot_Init();
				break;
			}
		}
	}
	EN=1;	
}