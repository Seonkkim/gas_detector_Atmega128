#include<iom128v.h>
#include <avr\io.h>
#include <avrdef.h>
#define F_CPU 16000000

void ADC_init(void); // ADC초기 설정
unsigned int ADConversion(int ch); // ADC 실행
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
 DDRF=0x00; // 기준전압 설정
ADMUX |= (1 << REFS1) | (1 << REFS0); // ADC 허용
ADCSRA |= (1 << ADEN); // 프리스케일러 값 64
 ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0);
 }
 unsigned int ADConversion(int ch)
 { // 핀 선택
ADMUX |= (ch << MUX4) | (ch << MUX3) | (ch << MUX2) | (ch << MUX1) | (ch << MUX1); // AD 변환 시작
ADCSRA |= (1 << ADSC); //AD 변환 완료 여부 확인, AD 변환 완료될 때까지 대기, 완료 확인되면 다음 진행
while(!(ADCSRA & (1 << ADIF))){};// AD 변환 완료된 데이터 반환
return ADC;
}
