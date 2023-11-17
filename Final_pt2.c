//Name: Aidan Stoner, Marc Santacapita, Erin Cardino, Shaunessy Reynolds
//Date: 11/20/23
//Course: ELEC-3371
//Description: Working with USART to send and recieve messages that will tell us status and data
//             about the "game". Obj2 sends a message about which direction the joystick was
//             pressed from the MCU to my computer. Obj3 takes a message, either 'p' or 'P', from 
//             my computer and returns the message 'Paused' or 'Unpaused' depending on which state
//             it is in and moves it to the opposite state. Bonus Obj4 prints out the number of
//             times each direction was pressed on the joystick in a nice display.
//******************************************************************************
//Global Varibles
int joy, i, sent, temp;
char recieved;
int paused; //set 1 when paused, 0 when unpaused
char PauseMessage[8] = {'P','a','u','s','e','d',13,10};
char UnpauseMessage[10] = {'U','n','p','a','u','s','e','d',13,10};
int pressCounts[5] = {0,0,0,0,0}; //from left to right UP, RT, DN, LT, CK
char CountMessage[38] = {'J','o','y','s','t','i','c','k',' ','P','r','e','s','s','e','s',' ','S','i','n','c','e',' ','L','a','s','t',' ','R','e','s','e','t',':',13,10,13,10};
char letter1[5] = {'U', 'R', 'D', 'L', 'C'};
char letter2[5] = {'P', 'T', 'N', 'T', 'K'};
//******************************************************************************
//Functions
void initUSART();
int joyRead();
void initGPIO();
void sendChar(char message);
void sendPressed();
void checkForMessage();
void sendPressCount(int idx);
//******************************************************************************
//Main Fucntion
void main() {
     initUSART(); //starts USART1
     initGPIO();  //Starts clocks for GPIO
     for(;;){
//Objective 2
          joy = joyRead(); //reads what direction the joystick is in and returns 0-5
          switch(joy){
               case 0: //no press do nothing
                    sent = 0; //sent variable is used to avoid the message from being sent multiple times for one press
                    break;
               case 1: //up press, send UP
                    if(sent == 0){
                         sendChar('U');
                         sendChar('P');  //sends the message, updates the sent variable and adds one to the count
                         sendPressed();  //same process for each direction
                         sent = 1;
                         pressCounts[0] = pressCounts[0] + 1;
                         break;
                    }
               case 2: //right press, send RT
                    if(sent == 0){
                         sendChar('R');
                         sendChar('T');
                         sendPressed();
                         sent = 1;
                         pressCounts[1] = pressCounts[1] + 1;
                         break;
                    }
               case 3: //down press, send DN
                    if(sent == 0){
                         sendChar('D');
                         sendChar('N');
                         sendPressed();
                         sent = 1;
                         pressCounts[2] = pressCounts[2] + 1;
                         break;
                    }
               case 4: //left press, send LT
                    if(sent == 0){
                         sendChar('L');
                         sendChar('T');
                         sendPressed();
                         sent = 1;
                         pressCounts[3] = pressCounts[3] + 1;
                         break;
                    }
               case 5: //click press, send CK
                    if(sent == 0){
                         sendChar('C');
                         sendChar('K');
                         sendPressed();
                         sent = 1;
                         pressCounts[4] = pressCounts[4] + 1;
                         break;
                    }
          }
//******************************************************************************
//Objective 3
          if(USART1_SR.B5 == 1){
               recieved = USART1_DR; //check if reciever data register is empty and update if it is
          }
          if(recieved == 'p' || recieved == 'P'){ //check to make sure we recieved a p or P
               if(paused == 0){ //checks if game is currently unpaused
                    paused = 1; //updates variable
                    for(i = 0; i < 8; i++){  //this loop sends the message through UART1 that the game has been paused
                         sendChar(PauseMessage[i]);
                    }
               }else if(paused == 1){ //checks if game in paused
                    paused = 0; //updates variable
                    for(i = 0; i < 10; i++){ //this loop sends the message through UART1 that the game has been unpaused
                         sendChar(UnpauseMessage[i]);
                    }
               }
          }
//******************************************************************************
//Bonus Objective 4
     //count variables are being updated in obj1 then all the display stuff happens here
          if(recieved == 'Q'){
               //print press count for each button to UART1
               for(i = 0; i < 38; i++){
                    sendChar(CountMessage[i]); //sends the data title
               }
               for(i = 0; i < 5; i++){
                    sendPressCount(i); //sends the label and data for each direction
               }

          }
          recieved = 0; //clears the pause/unpause variable, needed to prevent looping
     }
}
//******************************************************************************
//Function Definitions
int joyRead(){     //determines which direction joystick is being pressed and returns 0-5
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

void initUSART(){ //starts USART1
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

void initGPIO(){  //starts the clocks for GPIO
     RCC_APB2ENR |= 1 << 2;  //enables clock for PortA
     RCC_APB2ENR |= 1 << 3;  //enables clock for PortB
     RCC_APB2ENR |= 1 << 4;  //enables clock for PortC
     RCC_APB2ENR |= 1 << 5;  //enables clock for PortD
     RCC_APB2ENR |= 1 << 6;  //enables clock for PortE
}

void sendChar(char message){ //sends one character over USART
     if(USART1_SR.B7 == 1){
          USART1_DR = message;
     }
     Delay_ms(1);
}

void sendPressed(){  //sends the word 'Pressed' over USART
     sendChar(' ');
     sendChar('P');
     sendChar('r');
     sendChar('e');
     sendChar('s');
     sendChar('s');
     sendChar('e');
     sendChar('d');
     sendChar(13);
     sendChar(10);
}

void sendPressCount(int idx){    //sends the direction label and count through USART
     sendChar(letter1[idx]);
     sendChar(letter2[idx]);
     sendChar(':');
     sendChar(' ');
     sendChar((pressCounts[idx]/100) + 48);
     temp = (pressCounts[idx]/100) * 100;
     sendChar((pressCounts[idx] - temp)/10 + 48);
     temp = (pressCounts[idx]/10) * 10;
     sendChar(pressCounts[idx] - temp + 48);
     sendChar(13);
     sendChar(10);
     sendChar(13);
     sendChar(10);
}