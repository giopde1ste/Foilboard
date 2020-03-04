#include <mbed.h>

InterruptIn button(BUTTON1);
DigitalOut led(LED1);
 
void flip() {
    led = !led;
}
 
int main() {
    button.rise(&flip);  // attach the address of the flip function to the rising edge
    while(1) {           // wait around, interrupts will interrupt this!
      ;
    }
}
