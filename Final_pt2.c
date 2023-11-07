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