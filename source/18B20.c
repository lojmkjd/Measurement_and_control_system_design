/*-----------------------------------------------
  ���ƣ�18B20�¶ȴ�����
  �޸ģ���
  ���ݣ�18B20�����¶ȼ���Ӧ����������
------------------------------------------------*/
#include"include/delay.h"
#include"include/18b20.h"
#include <intrins.h>
/*------------------------------------------------
                    18b20��ʼ��
------------------------------------------------*/
bit Init_DS18B20(void)
{
 bit dat=0;
 DQ = 1;    //DQ��λ
 DelayUs2x(5);   //������ʱ
 DQ = 0;         //��Ƭ����DQ����
 DelayUs2x(200); //��ȷ��ʱ ���� 480us С��960us
 DelayUs2x(200);
 DQ = 1;        //��������
 DelayUs2x(50); //15~60us �� ����60-240us�Ĵ�������
 dat=DQ;        //���x=0���ʼ���ɹ�, x=1���ʼ��ʧ��
 DelayUs2x(25); //������ʱ����
 return dat;
}

/*------------------------------------------------
                    ��ȡһ���ֽ�
------------------------------------------------*/
unsigned char ReadOneChar(void)
{
unsigned char i=0;
unsigned char dat = 0;
for (i=8;i>0;i--)
 {
  DQ = 0; // �������ź�
  dat>>=1;
  DQ = 1; // �������ź�
  if(DQ)
   dat|=0x80;
  DelayUs2x(25);
 }
 return(dat);
}
/*------------------------------------------------
                    д��һ���ֽ�
------------------------------------------------*/
void WriteOneChar(unsigned char dat)
{
 unsigned char i=0;
 for (i=8; i>0; i--)
 {
  DQ = 0;
  DQ = dat&0x01;
  DelayUs2x(25);
  DQ = 1;
  dat>>=1;
 }
DelayUs2x(25);
}

/*------------------------------------------------
                    ��ȡ�¶�
------------------------------------------------*/
unsigned int ReadTemperature(void)
{
unsigned char a=0;
unsigned int b=0;
unsigned int t=0;
Init_DS18B20();
WriteOneChar(0xCC); // ����������кŵĲ���
WriteOneChar(0x44); // �����¶�ת��
DelayMs(10);
Init_DS18B20();
WriteOneChar(0xCC); //����������кŵĲ��� 
WriteOneChar(0xBE); //��ȡ�¶ȼĴ����ȣ����ɶ�9���Ĵ����� ǰ���������¶�
a=ReadOneChar();   //��λ
b=ReadOneChar();   //��λ

b<<=8;
t=a+b;

return(t);
}
