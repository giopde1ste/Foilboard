#include "pwmTransform.h"

/*
 * @brief TODO: put an explanation of the function here
 * @param PinName PWMpinIn = Input Pin for PWM signal
 * @param PinName PWMpinOut = Output Pin for PWM signal
 * @param int periodStartms = Period lenght in miliseconds, default value defined as PERIOD_LENGTH_MS
 * @param int pulseWidthStartms = initial pulse width lenght in miliseconds, default value defined as PULSEWIDTH_LENGHT_MS_0
 * @return void
 */
pwmTransform::pwmTransform(PinName PWMpinIn, PinName PWMpinOut, int periodStartms = PERIOD_LENGTH_MS, int pulseWidthStartms = PULSEWIDTH_LENGHT_MS_0) : pwmReciever(PWMpinIn), pwmTransmitter(PWMpinOut)
{
    createPwm(periodStartms, pulseWidthStartms);
}

/*
 * @brief TODO: put an explanation of the function here
 * @param int periodLengthms = period length of PWM singal in mili seconds
 * @param int pulseWidthLengtms = initial pulse width length of PWM singal in milisecons
 * @return void
 */
void pwmTransform::createPwm(int periodLengthms, int pulseWidthLengtms)
{
    pwmTransmitter.period_ms(periodLengthms);
    pwmTransmitter.pulsewidth_ms(pulseWidthLengtms);
}

/*
 * @brief TODO: put an explanation of the function here
 * @return void
 */
void pwmTransform::updatePwm()
{
    _pulseWidthSec = pwmReciever.pulsewidth();                           // Returns float pulsewidth in seconds
    _pulseWidthus = (int)(_pulseWidthSec * PULSEWIDTH_MODIFIER_S_TO_US); // Converst the pulsewidth form <float>seconds to <int>microseconds
    if (limitation)                                                      // checks if the limitation is active
    {
        limitPulseWidth(&_pulseWidthus); // locks the pulsewidth to _pulsewidthMaxLimus if the pulsewidth is above _pulsewidthMaxLimus
    }
    pwmTransmitter.pulsewidth_us(_pulseWidthus); // sets the pulsewidth
}

/*
 * @brief TODO: put an explanation of the function here
 * @return void
 */
void pwmTransform::limitPulseWidth(int *pulseWidth)
{
    if (*pulseWidth >= _pulsewidthMaxLimus)
    { // simple conversion, if the pulseWidth exeeds the max lenght, set the puleWidth as the max lenght
        *pulseWidth = _pulsewidthMaxLimus;
    }
}

/*
 * @brief TODO: put an explanation of the function here
 * @param int pulseWidth = input pulsewidth
 * @return int new pulse width
 */
int pwmTransform::transformPulseWidth(int pulseWidth)
{
    // TODO: reate a function that conversts pulseWidth so that it will use the whole range of the input (1ms to 2ms duty cycle)
}

/*
 * @brief Connects the function pwmTransform::updatePwm() to an ticker where the interval time is set to updatetime
 * @param float updatetime = The interval in seconds for every updatePwm()
 * @return void
 */
void pwmTransform::attachPwmToTicker(float updatetime)
{
    pwmUpdateticker.attach(callback(this, &pwmTransform::updatePwm), updatetime);
}

/*
 * @brief Switches the state of the limitation (ON/OFF).
 * To SET the limitation, use pwmTransform::limitation = true;
 * To RESET the limitation use pwmTransform::limitation = false;
 * Default state is set in pwmTransform.h with the marco LIMITATION_DEFAULT_ON_STARTUP, default value is false.
 * @return state of the limitation
 */
bool pwmTransform::switchLimitation()
{
    limitation = !limitation;
    return limitation;
}

/*
 * @brief Set the _pulsewidthMaxLimus, default is defined as PULSEWIDTH_LENGHT_US_MAX_LIM
 * @param int pulsewidthMaxLimus = maximum pulse width in microseconds if the limit is set
 * @return void
 */
void pwmTransform::setPulseWidthMaxLim(int pulsewidthMaxLimus)
{
    _pulsewidthMaxLimus = pulsewidthMaxLimus;
}

/*
 * @brief Detach the update function form ticker and set the pulsewidth to PULSEWIDTH_LENGHT_MS_0, once reset the ticker should be reatatched with attachPwmToTicker()
 * @return void
 */
void pwmTransform::setPwmToMin()
{
    pwmUpdateticker.detach();
    pwmTransmitter.pulsewidth_ms(PULSEWIDTH_LENGHT_MS_0);
}