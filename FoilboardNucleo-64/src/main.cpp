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
    button.rise(&fliplim); // attach the address of the flip function to the rising edge
    //button.rise(callback(&pwmTransmitter, &pwmTransform::switchLimitation)); // attach the member function switchLimitationstate from the object pwmTransmitter to the rise of the button interrupt
    pwmTransmitter.attachPwmToTicker(UPDATE_PERIOD_PWM);
    pc.printf("Hello world!\n");
    while (1)
    { // wait around, interrupts will interrupt this!
        ;
    }
}