#include <mbed.h>
#include <PwmIn.h>

InterruptIn button(BUTTON1);
DigitalOut led(LED1);

PwmOut testReciever(PWM_OUT); //PB_3
PwmIn pwmReciever(PB_2);

Serial pc(SERIAL_TX, SERIAL_RX);
Ticker serialSyntax;

float _period = 0.0, _pulse = 0.0;

void flip()
{
    led = !led;
}

void _log()
{
    _period = pwmReciever.period();
    _pulse = pwmReciever.pulsewidth();
    pc.printf("The period is = %f Seconds\nThe pulsewidth is = %f Seconds\n\n", _period, _pulse);
    //testReciever.pulsewidth_ms(_pulse); //TODO does not work //iets
}

int main()
{
    testReciever.period_ms(20);
    testReciever.pulsewidth_ms(2);
    //testReciever.pulsewidth_us(2000);
    button.rise(&flip); // attach the address of the flip function to the rising edge
    serialSyntax.attach(&_log, 1);

    while (1)
    { // wait around, interrupts will interrupt this!
        ;
    }
}