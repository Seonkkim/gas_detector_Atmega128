#include<iom128v.h>
#include <avr\io.h>
#include <avrdef.h>
#define F_CPU 16000000

void ADC_init(void); // ADC�ʱ� ����
unsigned int ADConversion(int ch); // ADC ����
void Data(unsigned char data);
void delay_ms(unsigned int m);
void Putch(char);

int main(void){
ADC_init();
unsigned int ch_ADC;
char str1='1';
char str2='2';
char str3='3';
char *pStr1, *pStr2, *pStr3;
DDRE=0x00;
UCSR1A=0x00;
UCSR1B|=(1<<TXEN1);
UCSR1C|=(1<<UCSZ11)|(1<<UCSZ10);
UBRR1H=0;
UBRR1L=16;
SEI();

while(1){
ch_ADC = ADConversion(0);

if(500<ch_ADC)//6~4cm
 {

    Putch(str1);
}

else if((400<ch_ADC)&&(ch_ADC <500))//9~7cm
 {

    Putch(str2);
}

else if(1<ch_ADC <400)//11~9cm
 {
    Putch(str3);
}

delay_ms(100);
}
}
    void Putch(char data){

    while(!(UCSR1A&(1<<UDRE1)));
        UDR1= data;
        }
    void delay_ms(unsigned int m)
 {
 unsigned int i,j;
 for(i=0;i<m;i++)
 {
 for(j=0;j<2117;j++);
 }
 }
void ADC_init(void)
 {
 DDRF=0x00; // �������� ����
ADMUX |= (1 << REFS1) | (1 << REFS0); // ADC ���
ADCSRA |= (1 << ADEN); // ���������Ϸ� �� 64
 ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0);
 }
 unsigned int ADConversion(int ch)
 { // �� ����
ADMUX |= (ch << MUX4) | (ch << MUX3) | (ch << MUX2) | (ch << MUX1) | (ch << MUX1); // AD ��ȯ ����
ADCSRA |= (1 << ADSC); //AD ��ȯ �Ϸ� ���� Ȯ��, AD ��ȯ �Ϸ�� ������ ���, �Ϸ� Ȯ�εǸ� ���� ����
while(!(ADCSRA & (1 << ADIF))){};// AD ��ȯ �Ϸ�� ������ ��ȯ
return ADC;
}
