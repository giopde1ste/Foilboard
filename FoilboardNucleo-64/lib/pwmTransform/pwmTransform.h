#ifndef PWMTRANSFORM_H
#define PWMTRANSFORM_H
#include <mbed.h>
#include <PwmIn.h>

#define PERIOD_LENGTH_MS 20
#define PULSEWIDTH_LENGHT_MS_0 1
#define PULSEWIDTH_LENGHT_MS_MAX_LIM 1500
#define PULSEWIDTH_MODIFIER_S_TO_US 1000000
#define LIMITATION_DEFAULT_ON_STARTUP false

class pwmTransform
{
public:
    pwmTransform(PinName PWMpinIn, PinName PWMpinOut);
    void updatePwm();
    void attachPwmToTicker(float updatetime);
    bool limitation = LIMITATION_DEFAULT_ON_STARTUP;
    void switchLimitation();

private:
    void createPwm();
    void transformPulseWidth(int *pulseWidth);
    float _pulseWidthSec;
    int _pulseWidthus;
    PwmIn pwmReciever;
    PwmOut pwmTransmitter;
    Ticker pwmUpdateticker;
};

#endif