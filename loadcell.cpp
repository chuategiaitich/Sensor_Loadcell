#include <loadcell.h>

Loadcell::Loadcell(int SCK_PIN, int DOUT_PIN, int SCALE_FACTOR)
{
    this->SCK_PIN = SCK_PIN;
    this->DOUT_PIN = DOUT_PIN;
    this->SCALE_FACTOR = SCALE_FACTOR;
}

void Loadcell::init(int SCK_PIN, int DOUT_PIN, int SCALE_FACTOR)
{
    this->SCK_PIN = SCK_PIN;
    this->DOUT_PIN = DOUT_PIN;
    this->SCALE_FACTOR = SCALE_FACTOR;
    pinMode(SCK_PIN, OUTPUT);
    pinMode(DOUT_PIN, INPUT);
    digitalWrite(SCK_PIN, LOW);
}

void Loadcell::init()
{
    pinMode(SCK_PIN, OUTPUT);
    pinMode(DOUT_PIN, INPUT);
    digitalWrite(SCK_PIN, LOW);
}

void Loadcell::set_SCK_PIN(int SCK_PIN)
{
    this->SCK_PIN = SCK_PIN;
}

void Loadcell::set_DOUT_PIN(int DOUT_PIN)
{
    this->DOUT_PIN = DOUT_PIN;
}

void Loadcell::set_SCALE_FACTOR(int SCALE_FACTOR)
{
    this->SCALE_FACTOR = SCALE_FACTOR;
}

void Loadcell::reset_zero_offset()
{
    delay(500);
    zero_value = read_raw_value();
}

long Loadcell::read_raw_value()
{
    // long value = 0;
    // while (digitalRead(DOUT_PIN) == HIGH) {}

    // for (int i = 0; i < 24; i++) // 24 bits
    // {
    //     digitalWrite(SCK_PIN, HIGH);
    //     // delayMicroseconds(1); 
    //     digitalWrite(SCK_PIN, LOW);
    //     value = value << 1; 
    //     if (digitalRead(DOUT_PIN) == HIGH)
    //         {
    //             value |= 1;
    //         }
    // }

    // digitalWrite(SCK_PIN, HIGH); //chanel A & gain = 128 (default)
    // // delayMicroseconds(1);
    // digitalWrite(SCK_PIN, LOW);

    // if (value & 0x800000)
    //     { 
    //     value = value - 0x1000000; 
    //     }
    // return value;
    long value = 0;
    unsigned long timeout = millis() + 100;
    while (digitalRead(DOUT_PIN) == HIGH && millis() < timeout) {}

    if (millis() >= timeout) {
        return 0; // Timeout, return 0 or an error value
    }

    for (int i = 0; i < 24; i++) {
        digitalWrite(SCK_PIN, HIGH);
        value = (value << 1) | digitalRead(DOUT_PIN);
        digitalWrite(SCK_PIN, LOW);
    }

    digitalWrite(SCK_PIN, HIGH);
    digitalWrite(SCK_PIN, LOW);

    if (value & 0x800000) {
        value -= 0x1000000;
    }
    return value;
}

long Loadcell::read_value()
{
    return (read_raw_value()-zero_value)/SCALE_FACTOR;
}

void Loadcell::auto_calib(float calib)
{
    // int SCALE_FACTOR_calib = SCALE_FACTOR;
    long current_value = read_value();
    if(current_value<0) current_value=-current_value;
    if(current_value>calib) SCALE_FACTOR++;
    else if(current_value<calib) SCALE_FACTOR--;
    Serial.print("Current value = ");Serial.print(current_value);Serial.print("  |   Current scale factor value = ");Serial.println(SCALE_FACTOR);
}