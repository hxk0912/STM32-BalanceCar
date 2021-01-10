#include "control.h"
#include "main.h"
#include "tim.h"

int count_tar = 10000;
int count_now = 0;
int count_time = 0;
float speed_now = 0;
float speed_tar = 0;

float Position_KP = 100;
float Position_KI = 0;
float Position_KD = 0.2;
float Velocity_KP = 10;
float Velocity_KI = 0.05;

void PWM_Init()
{
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,0);
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,0);
}


void Encoder_Init()
{
    HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_1);
    HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_2);
    __HAL_TIM_SET_COUNTER(&htim4,10000);
    HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_1);
    HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_2);
    __HAL_TIM_SET_COUNTER(&htim2,10000);
}

int myabs(int num)
{
	if(num<0)
	{
		num = -num;
	}
	return num;
}

int Position_PID(float Encoder,short gyro,float Target)
{ 	
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Encoder-Target;                                  
	 Integral_bias+=Bias;	                                 
	 Pwm=Position_KP*Bias+Position_KI*Integral_bias+Position_KD*(gyro); 
	 Last_Bias=Bias;                                       
	 return Pwm;                                           
}

int Incremental_PI (float Encoder_Left,float Encoder_Right,float Target)
{ 	
	 static float Bias,Pwm,Integral_bias,Bias_Least;
	 Bias=Encoder_Left + Encoder_Right - Target;  
	 Integral_bias += Bias;
	 Pwm=Velocity_KP*(Bias)+Velocity_KI*Integral_bias;                                       
	 return Pwm;                                    
}


//int Incremental_PI_Turn (float,short gyro)
//{ 	
//	 static float Bias,Pwm,Integral_bias,Bias_Least;
//	 Bias=Encoder_Left + Encoder_Right - Target;  
//	 Integral_bias += Bias;
//	 Pwm=Velocity_KP*(Bias)+Velocity_KI*Integral_bias;                                       
//	 return Pwm;                                    
//}

int ReadEncoder_Left(void)
{
	int speed;
	speed = __HAL_TIM_GET_COUNTER(&htim2)-10000;
	__HAL_TIM_SET_COUNTER(&htim2,10000);
	return speed;
}

int ReadEncoder_Right(void)
{
	int speed;
	speed = __HAL_TIM_GET_COUNTER(&htim4)-10000;
	__HAL_TIM_SET_COUNTER(&htim4,10000);
	return speed;
}

void Motor_Left(int pwm)
{   
    if (pwm>0)
    {
      HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_RESET);
	    HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_SET);
      __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,pwm);
    }else
    {
      HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_SET);
	    HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_RESET);
      __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,-pwm);
    }   
}

void Motor_Right(int pwm)
{   
    if (pwm>0)
    {
			HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_SET);
	    HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_RESET);
      __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,pwm);
    }else
    {
      HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_RESET);
	    HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_SET);
      __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,-pwm);
    }   
}

int limit_pwm(int pwm)
{
  if (pwm>=0)
  {
    if (pwm>=1000)
    {
      pwm = 1000;
    }
    
  }
  else if (pwm<=0)
  {
    if (pwm<-1000)
    {
      pwm = -1000;
    }
    
  }
  return pwm;
}