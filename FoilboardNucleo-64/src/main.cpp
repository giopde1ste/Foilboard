#include <mbed.h>
#include "pindef.h"
#include "pwmTransform.h"

InterruptIn button(BUTTON1);
DigitalOut led(LED1);
pwmTransform pwmTransmitter(PWM_IN, PWM_IN);

void flip()
{
    led = !led;
}

int main()
{
    button.rise(&flip);                                            // attach the address of the flip function to the rising edge
    button.rise(&pwmTransmitter, &pwmTransform::switchLimitation); // attach the member function switchLimitationstate from the object pwmTransmitter to the rise of the button interrupt
    pwmTransmitter.attachPwmToTicker(UPDATE_PERIOD_PWM);
    while (1)
    { // wait around, interrupts will interrupt this!
        ;
    }
}