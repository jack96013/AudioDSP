/*
 * @Author       : TZU-CHIEH, HSU
 * @Mail         : j.k96013@gmail.com
 * @Department   : ECIE Lab, NTUT
 * @Date         : 2024-06-27 20:48:09
 * @LastEditTime : 2024-06-27 21:52:50
 * @Description  : ASRC + MUX
 */
#ifndef __I2SMUX_H__
#define __I2SMUX_H__


#include <Arduino.h>
#include "board.h"

enum class I2SHandlerMux
{
    BT,
    USB,
    FPGA,
};

class I2SHandler
{
    public:
    I2SHandler();
    void init();
    void loop();
    
    void setAudioInput(I2SHandlerMux mux);
    I2SHandlerMux getAudioInput(I2SHandlerMux);

    void setSampleRate(double sampleRate);
    double getSampleRate();

    private:
    I2SHandlerMux _audioInput;

};

#endif
