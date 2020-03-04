#include <mbed.h>

DigitalOut myled(LED1);
DigitalOut myled2(LED2);


int main() {
  while(1) {
        myled = 1;
        myled2 = 0;
        wait(1);
        myled = 0;
        myled2 = 1;
        wait(1);
  }
}