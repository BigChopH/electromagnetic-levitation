#include <PID_v1.h>
#define IN1 6
#define IN2 5
#define IN3 4
#define IN4 3
#define ENA 11
#define ENB 9//全体引脚初始化

double Setpoint_X, Input_X, Output_X,X_plus; //定义PID输入变量
double p_X =18,i_X =0.3,d_X = 0.08;
double Setpoint_Y, Input_Y, Output_Y,Y_plus; 
double p_Y =18,i_Y =0.3,d_Y = 0.08;
int on_put=1;

PID PID_X(&Input_X, &Output_X, &Setpoint_X,p_X,i_X,d_X, DIRECT); 
PID PID_Y(&Input_Y, &Output_Y, &Setpoint_Y,p_Y,i_Y,d_Y, DIRECT); 



void turn_X(int a)
{
  if(a>=0)
  {
    digitalWrite(IN1,0);
    digitalWrite(IN2,1); 
    analogWrite(ENA,a);
  }
  else 
  {
    a=-a;
    digitalWrite(IN1,1);
    digitalWrite(IN2,0); 
    analogWrite(ENA,a);
  }
}

void turn_Y(int a)
{
  if(a>=0)
  {
    digitalWrite(IN3,0);
    digitalWrite(IN4,1); 
    analogWrite(ENB,a);
  }
  else 
  {
    a=-a;
    digitalWrite(IN3,1);
    digitalWrite(IN4,0); 
    analogWrite(ENB,a);
  }
}

void setup() //程序开始
{
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);//定义引脚

  digitalWrite(IN1,0);
  digitalWrite(IN2,0);
  digitalWrite(IN3,0);
  digitalWrite(IN4,0);
  analogWrite(ENA,0);
  analogWrite(ENB,0); 

  Serial.begin(115200);

  Setpoint_X = 509;//560;
  Setpoint_Y = 503;//560;给定浮子悬浮稳定点
  PID_X.SetTunings(p_X,i_X,d_X);
  PID_Y.SetTunings(p_Y,i_Y,d_Y);//给定PID参数
  PID_X.SetOutputLimits(-255,255);
  PID_Y.SetOutputLimits(-255,255);//出值范围
  PID_X.SetSampleTime(5);
  PID_Y.SetSampleTime(5);//设置PID刷新率为5ms
  PID_X.SetMode(AUTOMATIC);
  PID_Y.SetMode(AUTOMATIC);//设置PID计算模式为AUTOMATIC
}

void loop()
{
  

  Input_X = analogRead(A1);
  Input_Y = analogRead(A0);


  if(on_put)
  {
    PID_X.Compute();
    PID_Y.Compute();
    turn_X(Output_X);
    turn_Y(Output_Y);

  }

Serial.println("x");
Serial.println(Input_X);
Serial.println("y");
Serial.println(Input_Y);
// Serial.print(on_put);
}

