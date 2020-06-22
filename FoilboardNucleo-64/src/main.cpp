#include <mbed.h>
#include "pindef.h"
#include "pwmTransform.h"

InterruptIn button(BUTTON1);
DigitalOut led(LED1);
pwmTransform pwmTransmitter(PWM_IN, PWM_OUT);
Serial pc(SERIAL_TX, SERIAL_RX);

void fliplim()
{
    led = pwmTransmitter.switchLimitation();
    pc.printf("Limit flipped\n");
}

int main()
{
    pc.printf("Starting initializing sequence\n");
    button.rise(&fliplim);                               // attach the address of the flip function to the rising edge
    pwmTransmitter.attachPwmToTicker(UPDATE_PERIOD_PWM); // attach the PWM signal to the ticker object with the interval time as UPDATE_PERIOD_PWM
    pc.printf("end of initializing sequence\n");
    while (1)
    { // wait around, interrupts will interrupt this!
        ;
    }
}