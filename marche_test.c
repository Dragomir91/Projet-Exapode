#include "lpc17xx.h"
#include "type.h"
#include "can.h"
#include "uart.h"




CAN_MSG MsgBuf_TX1, MsgBuf_TX2; /* TX and RX Buffers for CAN message */
CAN_MSG MsgBuf_RX1, MsgBuf_RX2; /* TX and RX Buffers for CAN message */

//********************************************************************//
// Detail de la connexion bluetooth 																		
//
// Nom du module : Hexapode 
// Mot de passe : 0
// Baud rate : 9600
// Stop bite : 1
// Parity : None 
// H/W flow cotrol : Don't use
//
//********************************************************************//

volatile uint32_t CAN1RxDone = FALSE, CAN2RxDone = FALSE;


void Init_CAN(void);
void Send_CAN(int ID, int DataA, int DataB);
void marche_case(void);
void marche_avant(void);
void stand_position(void);
void send_position(int ID, int positionA, int positionB, int positionC);
void marche_test1(void);
void marche_test2(void);

void danse(void);
void maintenance(void);
void marche_rapide(void);
 
void init_UART(void);
void Init_GPIO(void); // Initialise sortie LED
void Allumer_LED(int Num_LED);
void Eteindre_LED(int Num_LED);
void init_baudratetest(void);
void UART1_IRQHandler (void);


#define DELAY 1000000

void SysTick_Handler(void)  {                               /* SysTick interrupt Handler.*/
  static int a;
	
	if (a==1){
	Allumer_LED(2);
	a=0;
	}
	else{
	Eteindre_LED(2);
	a=1;
}
}
//DataA : paquet le plus lourd. Initialisation du Baudarate à 125kBps

int main( void )
{
	int long i; 
	
	SystemClockUpdate();
	//Eteindre_LED(2);
	
	
	Init_GPIO();
	Init_CAN();
	//init_UART();
	//UARTInit(1,9600);
	//init_baudratetest();
	//LPC_UART1 -> ACR |= 0x01;
	LPC_UART1->FCR |= 0x03;  //active le FIFO étape 4
	
	
	
	SysTick_Config(1445000);
	send_position(7, 100, 100, 100);
	/*
	while(1){
	//Send_CAN(3,120, 15);

	send_position(7, 100, 100, 100);
	for(i=0;i<2*DELAY;i++){};

			
	
	//stand_position();
		//marche_avant();
		//stand_position();
		
	
		//danse();
	}
	//marche_avant();
	*/
}

/******************************************************************************************
**                                                                                       **
*******************************************************************************************/
void stand_position(void)
{
	int long i;
	send_position(1,150,150,150);
	for(i=1;i<10000;i++);
	send_position(3,150,150,150);
	for(i=1;i<10000;i++);
	send_position(5,150,150,150);
	for(i=1;i<10000;i++);
	send_position(7,150,150,150);
	for(i=1;i<10000;i++);
	send_position(9,150,150,150);
	for(i=1;i<10000;i++);
	send_position(11,150,150,150);
}

void marche_avant(void)
{
	int i=0;
	
	send_position(3,150,70,210);
	send_position(7,150,70,250);            //lève les pattes A
	send_position(11,150,70,210);
	for(i=0;i<2*DELAY;i++){}
		
	send_position(1,150,150,150);
	send_position(5,150,150,150);            //place les pattes B
	send_position(9,150,150,150);
	for(i=0;i<3*DELAY;i++){}
		
	send_position(3,170,90,160);
	send_position(7,150,100,240);            //avance les pattes A
	send_position(11,130,90,160);
	for(i=0;i<2*DELAY;i++){}

	send_position(3,165,150,130);
	send_position(7,150,160,200);            //pose (1) les pattes A
	send_position(11,135,150,130);
	for(i=0;i<2*DELAY;i++){}
		
	send_position(3,165,150,130);
	send_position(7,150,160,160);            //pose les pattes A
	send_position(11,135,150,130);
	for(i=0;i<2*DELAY;i++){}
			
	send_position(1,150,70,210);
	send_position(5,150,70,210);            //lève les pattes B
	send_position(9,150,70,210);
	for(i=0;i<DELAY;i++){}
		
	send_position(3,150,150,150);
	send_position(7,150,150,150);            //place les pattes A
	send_position(11,150,150,150);
	for(i=0;i<DELAY;i++){}
	
	send_position(1,150,90,140);
	send_position(5,180,70,140);            //avance les pattes B
	send_position(9,120,70,140);
	for(i=0;i<DELAY;i++){}
		
	send_position(1,150,155,125);
	send_position(5,180,155,145);            //pose les pattes B
	send_position(9,120,155,145);
	for(i=0;i<2*DELAY;i++){}
		
}

void maintenance(void)
{
	
	send_position(1,150,60,230);
	send_position(3,150,60,230);
	send_position(5,150,60,230);
	send_position(7,150,60,230);
	send_position(9,150,60,230);
	send_position(11,150,60,230);
	
	
}



void danse (void)
{
	int i;
	
	send_position(1,150,200,180);
	send_position(5,150,200,180);
	send_position(9,150,200,180);
	send_position(3,150,200,180);
	send_position(7,150,200,180);
	send_position(11,150,200,180);
	for(i=0;i<DELAY;i++){}
		
	send_position(1,150,70,220);
	send_position(5,150,70,220);
	send_position(9,150,70,220);
	for(i=0;i<DELAY;i++){}
		
	send_position(1,150,70,200);
	send_position(5,150,70,200);
	send_position(9,150,70,200);
	for(i=0;i<DELAY;i++){}
		
	send_position(1,150,150,130);
	send_position(5,150,150,130);
	send_position(9,150,150,130);
	for(i=0;i<DELAY;i++){}
	
	send_position(3,150,70,220);
	send_position(7,150,70,220);
	send_position(11,150,70,220);
	for(i=0;i<DELAY;i++){}
		
	send_position(3,150,70,200);
	send_position(7,150,70,200);
	send_position(11,150,70,200);
	for(i=0;i<DELAY;i++){}
		
		
	
	send_position(1,150,150,130);
	send_position(3,150,150,130);
	send_position(5,150,150,130);
	send_position(7,150,150,130);
	send_position(9,150,150,130);
	send_position(11,150,150,130);
	for(i=0;i<DELAY;i++){}
	for(i=0;i<DELAY;i++){}
	
	
}


void Init_CAN(void)
{
SystemClockUpdate();
CAN_Init( BITRATE125K18MHZ );
	
//CAN_SetACCF( ACCF_OFF );
}


void Send_CAN(int ID,int DataA, int DataB)
{

  /* Even though the filter RAM is set for all type of identifiers,
  the test module tests explicit standard identifier only */
  MsgBuf_TX1.Frame = 0x00080000; /* 11-bit, no RTR, DLC is 8 bytes */
  MsgBuf_TX1.MsgID = ID; /* Explicit Standard ID */
  MsgBuf_TX1.DataA = DataA;
  MsgBuf_TX1.DataB = DataB;
	
	
	//Transmit initial message on CAN 1 
	CAN1_SendMessage( &MsgBuf_TX1 );

}


void send_position(int ID, int positionA, int positionB, int positionC)
{
	int DataA_sp = 0x00, DataB_sp = 0x00;
	int ID_sp = ID;
	DataA_sp = DataA_sp | positionA;
	DataA_sp = DataA_sp<<4;
	DataB_sp = DataB_sp | positionB;
	DataB_sp = DataB_sp<<18;
	DataB_sp = DataB_sp | positionC;
	Send_CAN(ID_sp, DataA_sp, DataB_sp);
}

void Init_GPIO (void)
{
	LPC_GPIO1->FIODIR0 = LPC_GPIO1->FIODIR0 | 0x13; // Initialisation L1, L2, L3
	LPC_GPIO1->FIODIR1 = LPC_GPIO1->FIODIR1 | 0x07; // Initialisation L4, L5, L6
	LPC_GPIO1->FIODIR3 = LPC_GPIO1->FIODIR3 | 0x38;	// Initialisation L10, L11, L12
}

void Allumer_LED(int Num_LED)
{
	switch (Num_LED)
		{
			case 1: LPC_GPIO1->FIOPIN0 = LPC_GPIO1->FIOPIN0 | 0x01;
							break;
			case 2: LPC_GPIO1->FIOPIN0 = LPC_GPIO1->FIOPIN0 | 0x02;
							break;
			case 3: LPC_GPIO1->FIOPIN0 = LPC_GPIO1->FIOPIN0 | 0x10;
							break;
			case 4: LPC_GPIO1->FIOPIN1 = LPC_GPIO1->FIOPIN1 | 0x01;
							break;
			case 5: LPC_GPIO1->FIOPIN1 = LPC_GPIO1->FIOPIN1 | 0x02;
							break;
			case 6: LPC_GPIO1->FIOPIN1 = LPC_GPIO1->FIOPIN1 | 0x04;
							break;		
			case 10: LPC_GPIO1->FIOPIN3 = LPC_GPIO1->FIOPIN3 | 0x08;
							break;	
			case 11: LPC_GPIO1->FIOPIN3 = LPC_GPIO1->FIOPIN3 | 0x10;
							break;	
			case 12: LPC_GPIO1->FIOPIN3 = LPC_GPIO1->FIOPIN3 | 0x20;
							break;	
		}
}

void Eteindre_LED(int Num_LED)
{
	switch (Num_LED)
		{
			case 1: LPC_GPIO1->FIOPIN0 = LPC_GPIO1->FIOPIN0 & ~0x01;
							break;
			case 2: LPC_GPIO1->FIOPIN0 = LPC_GPIO1->FIOPIN0 & ~0x02;
							break;
			case 3: LPC_GPIO1->FIOPIN0 = LPC_GPIO1->FIOPIN0 & ~0x10;
							break;
			case 4: LPC_GPIO1->FIOPIN1 = LPC_GPIO1->FIOPIN1 & ~0x01;
							break;
			case 5: LPC_GPIO1->FIOPIN1 = LPC_GPIO1->FIOPIN1 & ~0x02;
							break;
			case 6: LPC_GPIO1->FIOPIN1 = LPC_GPIO1->FIOPIN1 & ~0x04;
							break;		
			case 10: LPC_GPIO1->FIOPIN3 = LPC_GPIO1->FIOPIN3 & ~0x08;
							break;	
			case 11: LPC_GPIO1->FIOPIN3 = LPC_GPIO1->FIOPIN3 & ~0x10;
							break;	
			case 12: LPC_GPIO1->FIOPIN3 = LPC_GPIO1->FIOPIN3 & ~0x20;
							break;	
		}
}

void marche_rapide(void)
{
	int i=0;
	
	send_position(3,150,70,210);
	send_position(7,150,70,250);            //lève les pattes A
	send_position(11,150,70,210);
	for(i=0;i<DELAY;i++){}
		
	send_position(1,150,150,150);
	send_position(5,150,150,150);            //place les pattes B
	send_position(9,150,150,150);
	for(i=0;i<DELAY;i++){}
		
	send_position(3,170,90,160);
	send_position(7,150,100,240);            //avance les pattes A
	send_position(11,130,90,160);
	for(i=0;i<DELAY;i++){}

	send_position(3,165,150,130);
	send_position(7,150,160,160);            //pose les pattes A
	send_position(11,135,150,130);
	for(i=0;i<DELAY;i++){}
			
	send_position(1,150,70,210);
	send_position(5,150,70,210);            //lève les pattes B
	send_position(9,150,70,210);
	for(i=0;i<DELAY;i++){}
		
	send_position(3,150,150,150);
	send_position(7,150,150,150);            //place les pattes A
	send_position(11,150,150,150);
	for(i=0;i<DELAY;i++){}
	
	send_position(1,150,90,140);
	send_position(5,180,70,140);            //avance les pattes B
	send_position(9,120,70,140);
	for(i=0;i<DELAY;i++){}
		
	send_position(1,150,155,125);
	send_position(5,180,155,145);            //pose les pattes B
	send_position(9,120,155,145);
	for(i=0;i<DELAY;i++){}
		
}

void init_UART(void)
{
	LPC_SC->PCONP |= 0x10; // étape 1
	LPC_SC->PCLKSEL0 |= 0x300; // étape 2
	//LPC_PINCON->PINSEL4 &= ~0x0F;
	LPC_PINCON->PINSEL4 |= 0x0A; // Broche P2.0 pour Tx et P2.1 pour Rx 
	LPC_UART1->LCR = 0x03; // 8 bits, sans parité, 1 bit de stop
	LPC_UART1->FCR |= 0x01;  //active le FIFO étape 4
}

/*void init_baudrate2(void)
{
	LPC_UART1->DLM = 0x00;    //fhn calculated with algorithm in the datasheet
  LPC_UART1->DLL = 9;//0x4E;//0x06;
  LPC_UART1->FDR = 0x21;//0x85;calculation, but not sure to need
	LPC_UART1->LCR = 0x03;
}*/

void init_baudratetest(void)
{
LPC_UART1->LCR |= 0x80; // Forçage bit DLAB=1 (Demande autorisation de modification)
LPC_UART1->DLM = 0; // Pas de sur-division de PCLK
LPC_UART1->DLL = 78; // Division principale par 9 de PCLK 52
LPC_UART1->FDR = 0x10; // Division fractionnaire par 1,5 (DIVADDVAL=1 et MULVAL=2) 21
LPC_UART1->LCR &= 0x7F; // Forçage bit DLAB=0 (Fin d'autorisation de modification)
}

void marche_test1(void)
{
	int i=0;
	
	send_position(1,195,70,150);
	send_position(9,105,70,150);
	send_position(5,195,70,150);	//lève les 1 9 5
	for(i=0;i<8*DELAY;i++){}
	send_position(1,195,150,150);
	send_position(9,105,150,150);//pose 1 9 5
	send_position(5,195,150,150);
	for(i=0;i<8*DELAY;i++){}
	send_position(1,150,150,150);
	send_position(9,150,150,150); // recule 1 9 5 et 3 7 11
	send_position(5,150,150,150);
	send_position(3,105,150,150);
	send_position(7,195,150,150);
	send_position(11,195,150,150);
	for(i=0;i<8*DELAY;i++){}
		send_position(3,195,70,150);
	send_position(7,105,70,150);	//lève et avance les 3 7 11
	send_position(11,105,70,150);
	for(i=0;i<8*DELAY;i++){}
		send_position(3,195,150,150);
	send_position(7,105,150,150);	//pose 3 7 11
	send_position(11,105,150,150);
	for(i=0;i<8*DELAY;i++){}
		send_position(1,105,150,150);
	send_position(9,195,150,150); // recule 1 9 5 et 3 7 11
	send_position(5,105,150,150);
	send_position(3,150,150,150);
	send_position(7,150,150,150);
	send_position(11,150,150,150);
	for(i=0;i<8*DELAY;i++){}
}

void marche_test2(void)
{
	int i=0;
	
	send_position(11,150,150,150);
	for(i=0;i<8*DELAY;i++){}
	send_position(11,150,150,150);
	for(i=0;i<8*DELAY;i++){}
	send_position(11,150,150,150);
	for(i=0;i<8*DELAY;i++){}
	send_position(11,150,150,150);
	for(i=0;i<8*DELAY;i++){}
	send_position(11,150,150,150);
	for(i=0;i<8*DELAY;i++){}
	send_position(11,150,150,150);
	for(i=0;i<8*DELAY;i++){}
	send_position(11,150,150,150);
	for(i=0;i<8*DELAY;i++){}
	send_position(11,150,150,150);
	for(i=0;i<8*DELAY;i++){}
	send_position(11,150,150,150);
	send_position(11,150,150,150);
	send_position(11,150,150,150);
}


void marche_case(void)
{
	int etat,i;
	etat=0;
	
	switch(etat)
	{
		case 0:
		{
	send_position(1,180,70,150);
	send_position(9,120,70,150);
	send_position(5,180,70,150);
for(i=0;i<8*DELAY;i++){}	//lève et avance les 1 9 5
			etat=1;
			break;
		}
		case 1:
		{
	send_position(1,180,150,150);
	send_position(9,120,150,150);	//pose 1 9 5
	send_position(5,180,150,150);
	for(i=0;i<8*DELAY;i++){}
	etat=2;
	break;}
		case 2:
		{
	send_position(1,150,150,150);
	send_position(9,150,150,150); // recule 1 9 5 et 3 7 11
	send_position(5,150,150,150);
	send_position(3,120,150,150);
	send_position(7,180,150,150);
	send_position(11,180,150,150);
	for(i=0;i<8*DELAY;i++){}
	etat=3;
	break;
		}
		case 3:
		{
			send_position(3,180,70,150);
	send_position(7,120,70,150);	//lève et avance les 3 7 11
	send_position(11,120,70,150);
	for(i=0;i<8*DELAY;i++){}
	etat=4;
	break;
		}
		case 4:
		{
	send_position(3,180,150,150);
	send_position(7,120,150,150);	//pose 3 7 11
	send_position(11,120,150,150);
	for(i=0;i<8*DELAY;i++){}
	etat=5;
	break;
		}
		case 5:
		{
	send_position(1,120,150,150);
	send_position(9,180,150,150); // recule 1 9 5 et 3 7 11
	send_position(5,120,150,150);
	send_position(3,150,150,150);
	send_position(7,150,150,150);
	send_position(11,150,150,150);
	for(i=0;i<8*DELAY;i++){}
	etat=0;
	break;
		}
		
			
			
			
	}
}

