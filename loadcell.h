#ifndef LOADCELL
#define LOADCELL

#include <Arduino.h>

class Loadcell
{
public:
    int SCK_PIN;
    int DOUT_PIN;
    int SCALE_FACTOR;
    long zero_value = 0;
    // char cmd[50];

    Loadcell(int SCK_PIN, int DOUT_PIN, int SCALE_FACTOR/*, char* cmd*/);
    // {
    //     this->SCK_PIN = SCK_PIN;
    //     this->DOUT_PIN = DOUT_PIN;
    //     this->SCALE_FACTOR = SCALE_FACTOR;
    //     // strcpy_s(this->cmd, 49, cmd)
    // }
    // ~Loadcell(){}
    void set_SCK_PIN(int SCK_PIN);
    void set_DOUT_PIN(int DOUT_PIN);
    void set_SCALE_FACTOR(int SCALE_FACTOR);
    void init();
    void init(int SCK_PIN, int DOUT_PIN, int SCALE_FACTOR);
    void reset_zero_offset();
    long read_value();
    long read_raw_value();
    void auto_calib(float calib);
};

#endif
