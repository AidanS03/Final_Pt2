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
//******************************************************************************
//Functions
void initUART();

//******************************************************************************
//Main Fucntion
void main() {

}

void initUART(){
      for(;;){  //the switch case scenario for the joystick, I just plop them here for now
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
      
      }
}