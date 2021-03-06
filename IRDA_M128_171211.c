#include "ASA_Lib.h"

//SPI
#define SPI_PORT	PORTB
#define SPI_PIN		PINB
#define SPI_DDR		DDRB
#define SPI_MISO	PB3
#define SPI_MOSI	PB2
#define SPI_SCK		PB1
#define SPI_SS      PB0

//ASA_ID
#define ADDR_PORT	PORTB
#define ADDR_PIN	PINB
#define ADDR_DDR	DDRB
#define ADDR0       PB5
#define ADDR1       PB6
#define ADDR2       PB7

char flag;

// /*****SPI*****/
// void SPI_Init(void)
// {
// 	//set miso as inputs
// 	SPI_DDR =(0<<SPI_MISO)|(1<<SPI_MOSI)|(1<<SPI_SCK)|(1<<SPI_SS)|(1<<ADDR0)|(1<<ADDR1)|(1<<ADDR2);
// 	//set mosi, sck, /ss, Addr0, Addr1, Addr2 as outputs
// 	SPCR =(1<<SPE)|(0<<DORD)|(0<<CPOL)|(0<<CPHA)|(1<<MSTR)|(1<<SPR1)|(1<<SPR0);
// 	//SPI enable, master, f/128
// 	_delay_ms(10);
// }
//
// char SPI_MasterTransmit(char cData)
// {
// 	/* Start transmission */
// 	SPDR = cData;
// 	/* Wait for transmission complete */
// 	while(!(SPSR & (1<<SPIF)));
//
// 	return SPDR;
// }
// void SPI_MasterRecieve(void){
// 	DDRB = (0<<SPI_SCK)|(1<<SPI_MISO)|(0<<SPI_MOSI)|(0<<SPI_SS);
// 	SPCR = (1<<SPIE)|(1<<SPE)|(0<<DORD)|(0<<MSTR)|(0<<CPOL)|(0<<CPHA);
// }
#define FOSC 11059200// Clock Speed
#define BAUD 4800
#define MYUBRR FOSC/16/BAUD-1

void PWM1_init(void){
  TCCR1A=(1<<COM1A1)|(0<<COM1A0)|(0<<COM1B1)|(0<<COM1B0)|(1<<WGM11)|(0<<WGM10);
  ///// COM1A1,COM1A0 /////
  //  control output compare pins (OC1A and OC1B respectively) behavior
  //  ->  Clear OC1A/OC1B on compare match when up-counting.Set OC1A/OC1B on compare match when downcounting
  TCCR1B=(1<<WGM13)|(1<<WGM12)|(0<<CS12)|(0<<CS11)|(1<<CS10);
  //  WGM13,WGM12,WGM11,WGM10 -> set Timer/Counter Mode of Operation (PWM, phase correct)
	ICR1=290;
  // freq=38k ->  mode of face constance-> f_clock/2/N/TOP  -> 8*10^5/2/1/105;
  //  N->  (Clock Select Bit Description) , TOP -> ICR1dddd
	//OCR1A=52;
}
void USART_Init( unsigned int ubrr )
{
/* Set baud rate */
UBRR1H = (unsigned char)(ubrr>>8);
UBRR1L = (unsigned char)ubrr;
/* Enable receiver and transmitter */
UCSR1B = (1<<RXEN1)|(1<<TXEN1);
/* Set frame format: 8data, 2stop bit */
UCSR1C = (0<<USBS1)|(3<<UCSZ10);
}

void USART_Transmit( unsigned char data ){
	/* Wait for empty transmit buffer */
	while ( !( UCSR1A & (1<<UDRE1)) );
	/* Put data into buffer, sends the data */
	UDR1 = data;
}

unsigned char USART_Receive( void ){
	/* Wait for data to be received */
	while ( !( UCSR1A & (1<<RXC1)) );
	/* Get and return received data from buffer */
	return UDR1;
}

int main(void)
{
  DDRB|=0x10;
  printf("start");
	char Tr,data1;
	ASA_M128_set();
	PWM1_init();
  USART_Init(MYUBRR);
	printf("start\n");
	DDRD=0x04;
	while(1)
	{

		scanf("%x",&Tr);
		ASA_ID_set(2);
		USART_Transmit(Tr);

		 printf("TX = %x\n",Tr);
		// _delay_ms(20);
		// data1=USART_Receive();
    //
		// printf("RX = %x\n",data1);


	}
}
// struct Data_Check{
//   char HeadCheck;
//   char EndCheck;
//   char Data;
// };
// int HeadCheck(char data){
//  struct  Data_Check Datacheck;
//   Datacheck.HeadCheck
//
// }
