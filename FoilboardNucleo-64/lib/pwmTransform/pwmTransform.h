#ifndef PWMTRANSFORM_H
#define PWMTRANSFORM_H
#include <mbed.h>
#include <PwmIn.h>

// default values, can be changed with functions in class
#define PERIOD_LENGTH_MS 20                 // can be changed in class constructor
#define PULSEWIDTH_LENGHT_MS_0 1            // can be changed in class constructor
#define PULSEWIDTH_LENGHT_US_MAX_LIM 1500   // can be changed with pwmTransform::setPulseWidthMaxLim();
#define LIMITATION_DEFAULT_ON_STARTUP false // can be changed with pwmTransform::setPulseWidthMaxLim(int pulsewidthMaxLimus);

// default values, CAN NOT be changed and should not be changed
#define PULSEWIDTH_MODIFIER_S_TO_US 1000000 // Used to convert seconds to microseconds in pwmTransform::updatePwm();

class pwmTransform
{
public:
    pwmTransform(PinName PWMpinIn, PinName PWMpinOut, int periodStartms = PERIOD_LENGTH_MS, int pulseWidthStartms = PULSEWIDTH_LENGHT_MS_0);
    void updatePwm();
    void attachPwmToTicker(float _updatetime);
    bool limitation = LIMITATION_DEFAULT_ON_STARTUP;
    bool switchLimitation();
    void setPulseWidthMaxLim(int pulsewidthMaxLimus);

private:
    void createPwm(int periodLengthms, int pulseWidthLengtms);
    void transformPulseWidth(int *_pulseWidth);
    float _pulseWidthSec;
    int _pulseWidthus, _pulsewidthMaxLimus = PULSEWIDTH_LENGHT_US_MAX_LIM;
    PwmIn pwmReciever;
    PwmOut pwmTransmitter;
    Ticker pwmUpdateticker;
};

#endif