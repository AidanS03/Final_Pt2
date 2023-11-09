//Name:
//Date:
//Course:
//Description:
//******************************************************************************
//Global Varibles
int joy;
char a, b;
//******************************************************************************
//Functions
void initUSART();
int joyRead();
void initGPIO();
void sendChar(char message);
void sendPressed();
//******************************************************************************
//Main Fucntion
void main() {
     for(;;){
          initGPIO();
//Objective 2
          initUSART();
          joy = joyRead();
          a = 'a';
          b = 'b';
          switch(joy){
               case 0: //no press do nothing
                    break;
               case 1: //up press, send UP
                    sendChar(' ');
                    sendChar('U');
                    sendChar('P');
                    sendPressed();
                    break;
               case 2: //right press, send RT
                    sendChar(' ');
                    sendChar('R');
                    sendChar('T');
                    sendPressed();
                    break;
               case 3: //down press, send DN
                    sendChar(' ');
                    sendChar('D');
                    sendChar('N');
                    sendPressed();
                    break;
               case 4: //left press, send LT
                    sendChar(' ');
                    sendChar('L');
                    sendChar('T');
                    sendPressed();
                    break;
               case 5: //click press, send CK
                    sendChar(' ');
                    sendChar('C');
                    sendChar('K');
                    sendPressed();
                    break;
          }
     }
}
//******************************************************************************
//Function Definitions
int joyRead(){
     GPIOA_CRL |= 1 << 26; //Sets PA6 as an input
     GPIOB_CRL |= 1 << 22; //sets PB5 as an input
     GPIOC_CRH |= 1 << 22; //sets PC13 as an input
     GPIOE_CRH = 0x33333333; //Set PortE/H as an output for LEDS
     GPIOD_CRL |= 0x40400; //Sets PD2 and PD4 as an input


     if(GPIOD_IDR.B4 == 0){
          return 1; //joystick up return a 1
     }else if(GPIOA_IDR.B6 == 0){
          return 2; //joystick right return 2
     }else if(GPIOB_IDR.B5 == 0){
          return 3; //joystick down return 3
     }else if(GPIOD_IDR.B2 == 0){
          return 4; //joystick left return 4
     }else if(GPIOC_IDR.B13 == 0){
          return 5; //joystick clicked return 5
     }else return 0; //nothing pressed return 0
}

void initUSART(){
     RCC_APB2ENR |= 1; //start clock to PA9 and PA10 can use alternate function
     AFIO_MAPR = 0xF000000; //do no want to remap PA9 and PA10 in bit 2
     RCC_APB2ENR |= 1 << 2; //enable clock for PA9 and PA10
     GPIOA_CRH = 0; //clear PA9 and PA10
     GPIOA_CRH |= 0x4B << 4; //sets PA9 (Tx) as a push-pull output and PA10 (Rx) as an input
     RCC_APB2ENR |= 1<<14; //enable clock for USART1
     USART1_BRR=0X506; //set baud rate to 56000
     USART1_CR1.B12 = 0; //forces M as 0 so 8 data bits
     USART1_CR2.B12 = 0; //forces bits 13 and 12 to 00 so there is one stop bit
     USART1_CR2.B13 = 0;
     USART1_CR3.B8 = 0; //forces bit 8 to 0 so no RTS hardware flow
     USART1_CR3.B9 = 0; //forces bit 9 to 0 so no CTS hardware flow
     USART1_CR1.B9 = 0; //forces even parity but we will turn it off
     USART1_CR1.B10 = 0;//forces no parity
     USART1_CR1.B2 = 1; //Rx enabled
     USART1_CR1.B3 = 1; //Tx enabled
     USART1_CR1.B13 = 1; //Enables UART and needs to be enabled after all the configuration above
     Delay_ms(100);
}

void initGPIO(){
     RCC_APB2ENR |= 1 << 2;  //enables clock for PortA
     RCC_APB2ENR |= 1 << 3;  //enables clock for PortB
     RCC_APB2ENR |= 1 << 4;  //enables clock for PortC
     RCC_APB2ENR |= 1 << 5;  //enables clock for PortD
     RCC_APB2ENR |= 1 << 6;  //enables clock for PortE
}

void sendChar(char message){
     if(USART1_SR.B7 == 1){
          USART1_DR = message;
     }
     Delay_ms(5);
}

void sendPressed(){
     sendChar(' ');
     sendChar('P');
     sendChar('r');
     sendChar('e');
     sendChar('s');
     sendChar('s');
     sendChar('e');
     sendChar('d');
}