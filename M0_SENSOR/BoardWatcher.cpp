/*
 * Inspired by https://gist.github.com/jdneo/43be30d85080b175cb5aed3500d3f989
 *
 * Have some hardware interrupts regularly triggered even if the code is in a loop
 * and restart the board if the loop takes too long.
 *
 * How to use:
 * - Create an object with the maximum duration of the loop in <S
 *      BoardWatcher boardWatcher(30 * 1000);
 * - Make sure to create the TC3_Handler() function and make it call
 *   the boardWatcher timerCallback() method
 */

#include <Arduino.h>
#include "BoardWatcher.h"

#define CPU_HZ 48000000
#define TIMER_PRESCALER_DIV 1024

void resetBoard() {
    // https://forum.arduino.cc/t/samd21-software-reset/849635
    Serial.println("ABOUT TO RESET BOARD");

    __disable_irq();
    NVIC_SystemReset();
    while (true);
}

void setTimerFrequency(int frequencyHz) {
    Serial.print("setTimerFrequency ");
    Serial.print(frequencyHz);
    Serial.println("Hz");

    int compareValue = (CPU_HZ / (TIMER_PRESCALER_DIV * frequencyHz)) - 1;
    TcCount16* TC = (TcCount16*) TC3;
    // Make sure the count is in a proportional position to where it was
    // to prevent any jitter or disconnect when changing the compare value.
    TC->COUNT.reg = map(TC->COUNT.reg, 0, TC->CC[0].reg, 0, compareValue);
    TC->CC[0].reg = compareValue;
    while (TC->STATUS.bit.SYNCBUSY == 1);
}

void startTimer(int frequencyHz) {
    REG_GCLK_CLKCTRL = (uint16_t) (GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN_GCLK0 | GCLK_CLKCTRL_ID_TCC2_TC3) ;
    while ( GCLK->STATUS.bit.SYNCBUSY == 1 ); // wait for sync

    TcCount16* TC = (TcCount16*) TC3;

    TC->CTRLA.reg &= ~TC_CTRLA_ENABLE;
    while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync

    // Use the 16-bit timer
    TC->CTRLA.reg |= TC_CTRLA_MODE_COUNT16;
    while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync

    // Use match mode so that the timer counter resets when the count matches the compare register
    TC->CTRLA.reg |= TC_CTRLA_WAVEGEN_MFRQ;
    while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync

    // Set prescaler to 1024
    TC->CTRLA.reg |= TC_CTRLA_PRESCALER_DIV1024;
    while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync

    setTimerFrequency(frequencyHz);

    // Enable the compare interrupt
    TC->INTENSET.reg = 0;
    TC->INTENSET.bit.MC0 = 1;

    NVIC_EnableIRQ(TC3_IRQn);

    TC->CTRLA.reg |= TC_CTRLA_ENABLE;
    while (TC->STATUS.bit.SYNCBUSY == 1); // wait for sync
    Serial.println("timer started");
}


BoardWatcher::BoardWatcher(int maxLoopRunningTimeMS): maxLoopRunningTimeMS(maxLoopRunningTimeMS), lastLoopStart(0) { }

/**
 * To be called in the sketch setup() to start running the timers regularly
 */
void BoardWatcher::init() {
    startTimer(1);
}

/**
 * Keep track of the time at the beginning of each loop so that the timer callback
 * can compute if the loop lasted longer than allowed
 */
void BoardWatcher::newLoop() {
    this->lastLoopStart = millis();
}

/**
 * Callback to be executed by the TC3_Handler() (i.e. the interrupt function)
 * It's role is to check if the current interrupt must run a check, check the
 * current run time of the loop and if it's too long restart the board
 * (Should we trigger the deepsleep to make sure we dont restart in loop? Probably)
 */
void BoardWatcher::timerCallback() {
    TcCount16* TC = (TcCount16*) TC3;
    // If this interrupt is due to the compare register matching the timer count
    // we toggle the LED.
    if (TC->INTFLAG.bit.MC0 == 1) {
        TC->INTFLAG.bit.MC0 = 1;
        // Actual callback logic here
        int loopDuration = millis() - this->lastLoopStart;
        Serial.println();
        Serial.print("In interrupt. Loop duration: ");
        Serial.println(loopDuration);

        if (loopDuration > this->maxLoopRunningTimeMS) {
            Serial.println("Reset board because max running time elapsed");
            resetBoard();
        }
    }
}
