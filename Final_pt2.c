//Name:
//Date:
//Course:
//Description:        

 //Objective 2:

//Write a program which communicates with the USART terminal using a baud rate of 56,000. 
//When the user interacts with the Joystick, the MCU will write to the terminal the 
//ASCII characters “UP Pressed”, “DN Pressed”, “LT Pressed”, “RT Pressed ”, or “CK Pressed”, 
//depending on which direction was pressed


//******************************************************************************
//Global Varibles                                      //stole the variables from Pt1 //
                 RCC_APB2ENR |= 1 << 2;  //enables clock for PortA
     RCC_APB2ENR |= 1 << 3;  //enables clock for PortB
     RCC_APB2ENR |= 1 << 4;  //enables clock for PortC
     RCC_APB2ENR |= 1 << 5;  //enables clock for PortD
     RCC_APB2ENR |= 1 << 6;  //enables clock for PortE

     GPIOA_CRL = 0x44444444; //Sets PortA/L as an input
     GPIOB_CRL = 0x44444444; //sets PortB/L as an input
     GPIOC_CRH = 0x44444444; //sets PortC/H as an input
     GPIOD_CRL = 0x44444444; //Sets PortD/L as an input *as an FYI we
          //may have to change this later to be wihtin the function as for
          //obj 3 all of portD needs to be an ouput.
     GPIOE_CRH = 0x33333333; //Set PortE/H as an output for LEDS
     
     
//****USART CODE
     unsigned int rcvrd;
     void USART1(); // Sub function which initializes the registers to enable USART1
//****

//******************************************************************************
//Functions
void initUART();

//******************************************************************************
//Main Fucntion
void main() {

         for(;;){
          switch(joyRead()){
               case 0 : //no press
               case 1 : //up turn on PE11 and PE15
               case 2 : //right turn on PE9 and PE10
               case 3 : //down turn on PE8 and PE12
               case 4 : //left turn on PE13 and 14
               case 5 : //click turn on all
          }
     }
}

void initUART(){

}
int joyRead(){      //need to change to a ASCII output to mikroC terminal from the USART connection?
     if(GPIOD_IDR.B4 == 1){
     //joystick up return a 1
     }else if(GPIOA_IDR.B4 == 1){
     //joystick right return 2
     }else if(GPIOB_IDR.B5 == 1){
     //joystick down return 3
     }else if(GPIOD_IDR.B2 == 1){
     //joystick left return 4
     }else if(GPIOC_IDR.B13 == 1){
     //joystick clicked return 5
     }else //nothing pressed return 0
}
//VARIABLE DECLARATIONS
for(;;) {
// The peripheral registers can be accessed by half-words (16-bit) or words (32-bit).
// Per data sheet (pg. 1007) USART1_SR consists of the following:
// 9 8 7 6 5 4 3 2 1 0
//CTS LBD TXE TC RXNE IDLE ORE NE FE PE
while (!((USART1_SR & (1<<5))== 0x20)){} // Check RXNE in USART1 StatusRegister.
// while receiver data register is empty, wait
// You can also check RXNE directly
// while (!USART1_SR.RXNE = 1) {} //while receiver data register is empty wait
// When data becomes available, we can store it on the CPU in a variable. Data is put into
// the USART data register USART1_DR (pg. 1010)
rcvrd = USART1_DR; //read data from receiver data register
//while transmitter data register is not empty wait
while (! (USART1_SR & (1<<7)) == 0x80) {}
// If we want to send data out via USART, we use the same data   register
USART1_DR = rcvrd; // transmit the received data
}
}
//
***********************************************************************************
***************
//SUB FUNCTIONS
void InitializeUSART1(){ // Sub function which initializes the registers to enable USART1
RCC_APB2ENR |= 1; // Enable clock for Alt. Function. USART1 uses AF for PA9/PA10
AFIO_MAPR=0X0F000000; // Do not mask PA9 and PA10 (becaue we are using for USART)
RCC_APB2ENR |= 1<<2; // Enable clock for GPIOA
GPIOA_CRH &= ~(0xFF << 4); // Clear PA9, PA10
GPIOA_CRH |= (0x0B << 4); // USART1 Tx (PA9) output push-pull
GPIOA_CRH |= (0x04 << 8); // USART1 Rx (PA10) input floating
RCC_APB2ENR |= 1<<14; // enable clock for USART1
USART1_BRR=0X00000506; // Set baud rate to 56000
// Per data sheet (pg. 1010) USART1_CR1 consists of the following:
//13 12 11 10 9 8 7 6 5 4 3 2 1 0
//UE M WAKE PCE PS PEIE TXEIE TCIE RXNEIE IDLEIE TE RE RWU SBK
//rw rw rw rw rw rw rw rw rw rw rw rw rw rw
USART1_CR1 &= ~(1<<12); // Force 8 data bits. M bit is set to 0.
USART1_CR2 &= ~(3<<12); // Force 1 stop bit
USART1_CR3 &= ~(3<<8); // Force no flow control and no DMA for
USART1
USART1_CR1 &= ~(3<<9); // Force no parity and no parity control
USART1_CR1 |= 3<<2; // RX, TX enable
//The following two instructions can also be used to enable RX and TX manually
//USART1_CR1.TE=1; //TX enable
//USART1_CR1.RE=1; //RX enable
USART1_CR1 |= 1<<13; // USART1 enable. This is done after configuration is complete
Delay_ms(100);

}