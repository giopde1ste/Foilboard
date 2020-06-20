#include "pwmTransform.h"

pwmTransform::pwmTransform(PinName PWMpinIn, PinName PWMpinOut) : pwmReciever(PWMpinIn), pwmTransmitter(PWMpinOut)
{
    createPwm();
}

void pwmTransform::createPwm() //TODO: setup class for pwmTransmitter & pwmReciever called pwmTransform
{
    pwmTransmitter.pulsewidth_ms(PERIOD_LENGTH_MS);
    pwmTransmitter.pulsewidth_ms(PULSEWIDTH_LENGHT_MS_0);
}

void pwmTransform::updatePwm()
{
    _pulseWidthSec = pwmReciever.pulsewidth(); // Returns float pulsewidth in seconds
    _pulseWidthus = (int)(_pulseWidthSec * PULSEWIDTH_MODIFIER_S_TO_US);
    if (limitation)
    {
        transformPulseWidth(&_pulseWidthus);
    }
    pwmTransmitter.pulsewidth_us(_pulseWidthus);
}

void pwmTransform::transformPulseWidth(int *pulseWidth)
{
    if (*pulseWidth >= PULSEWIDTH_LENGHT_MS_MAX_LIM)
    { // simple conversion, if the pulseWidth exeeds the max lenght, set the puleWidth as the max lenght
        *pulseWidth = PULSEWIDTH_LENGHT_MS_MAX_LIM;
    }
}

void pwmTransform::attachPwmToTicker(float updatetime)
{
    pwmUpdateticker.attach(this, &pwmTransform::updatePwm, updatetime);
}

void pwmTransform::switchLimitation()
{
    limitation = !limitation;
}