#include <stdint.h>
#include <tm4c123gh6pge.h>
volatile int switch_state;
volatile int led_state=0;
volatile int already_pressed=0;
volatile int i;





void   main(void)
{

    SYSCTL_RCGCGPIO_R |= (1<<6); // enabling clock of gpio port g
    GPIO_PORTG_DIR_R |= (1<<5);// pin5 as output
GPIO_PORTG_DIR_R &= ~(1<<4);// pin 4 as input
    GPIO_PORTG_DEN_R |= (1<<5);// pin5 digitally enable
    GPIO_PORTG_DEN_R |= (1<<4);// pin4 digitally enable
    GPIO_PORTG_PDR_R |= (1<<4); // pin4 pulled down






    while (1){
switch_state = GPIO_PORTG_DATA_BITS_R[1<<4];
    if(switch_state  && already_pressed==0){
        led_state=!led_state;
        for( i=400000; i>0;i--);
    }



if(led_state){

    GPIO_PORTG_DATA_BITS_R[1<<5] = (1<<5);
}

else{
    GPIO_PORTG_DATA_BITS_R[1<<5] = 0;
}


}


}

