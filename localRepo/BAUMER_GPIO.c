#include <stdint.h>
#include <tm4c123gh6pge.h>



void main(void)
{
    volatile int delay;

    
    SYSCTL_RCGCGPIO_R |= 0x22;   /* Enable clock for Port B and Port F */
    delay = SYSCTL_RCGCGPIO_R;

    
    GPIO_PORTB_DIR_R &= ~0x01;     /* PB0 as input (sensor)  */
    GPIO_PORTB_DEN_R |= 0x01;

    
    GPIO_PORTF_DIR_R |= 0x02;   /* PF1 as output (LED) */
    GPIO_PORTF_DEN_R |= 0x02;   

    while(1)
    {
        if(GPIO_PORTB_DATA_R & 0x01)
        {
            GPIO_PORTF_DATA_R |= 0x02;   // LED ON
        }
        else
        {
            GPIO_PORTF_DATA_R &= ~0x02;  // LED OFF
        }
    }
}
