#include <stdint.h>
#include <tm4c123gh6pge.h>
volatile int i;



void   main(void)
{

    SYSCTL_RCGCGPIO_R |= (1<<6);
    GPIO_PORTG_DIR_R |= (1<<5);
    GPIO_PORTG_DEN_R |= (1<<5);





    while (1){


            for( i=400000; i>0;i--);


            GPIO_PORTG_DATA_BITS_R[1<<5] = (1<<5);

            for (i=400000; i>0;i--);
            GPIO_PORTG_DATA_BITS_R[1<<5] = 0;

        }