/*
Reading Analog input value with grownd diferentiation.
Any consecutive "wait" reading lower than "calibration"
will trigger HIGH "ledPin"
�Antonio Scolari
antonio.scolari@scantibodies.com
*/


#include <Ethernet.h>
#include <EthernetUdp.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE };
IPAddress ip(10, 221, 21, 109);
unsigned int localPort = 5000;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE];
String datReq;
int packetSize;
EthernetUDP Udp;

//#include <Wire.h>
#include "Lib/elapsedMillis.h"
#define RackID "B01R01"
#define OFF         0
#define ON          1
#define ACKNOWLEDGE 2
elapsedMillis teA0;
elapsedMillis teA1;
elapsedMillis teA2;
elapsedMillis teA3;
elapsedMillis teA4;
elapsedMillis teA5;
elapsedMillis teA6;
elapsedMillis teA7;
elapsedMillis teA8;
elapsedMillis teA9;
elapsedMillis teA10;
elapsedMillis teA11;
elapsedMillis teA12;
elapsedMillis teA13;
elapsedMillis teA14;
elapsedMillis teA15;
elapsedMillis te_report;
int report_every = 3;
int SensorA0, SensorA1, SensorA2, SensorA3, SensorA4,
SensorA5, SensorA6, SensorA7, SensorA8, SensorA9,
SensorA10, SensorA11, SensorA12, SensorA13, SensorA14,
SensorA15 = 1023;
/*
char SensorA[] = {1023, 1023, 1023, 1023,
1023, 1023, 1023, 1023,
1023, 1023, 1023, 1023,
1023, 1023, 1023, 1023};
*/
int ledPin = 13;
const int calibration = 1010; //SENSITIVITY
unsigned int wait = 1; //SECOUNDS TO REMAIN WET
int waitExceed = 0;
int sensorValue = 0;
bool transmited = false;
bool RESET = LOW;
bool ACK = LOW;

void setup() {
    //Acknowledge & Reset Buttons
    pinMode(2, INPUT_PULLUP);
    pinMode(3, INPUT_PULLUP);
    wait *= 1000;
    pinMode(A0, INPUT_PULLUP);
    pinMode(A1, INPUT_PULLUP);
    pinMode(A2, INPUT_PULLUP);
    pinMode(A3, INPUT_PULLUP);
    pinMode(A4, INPUT_PULLUP);
    pinMode(A5, INPUT_PULLUP);
    pinMode(A6, INPUT_PULLUP);
    pinMode(A7, INPUT_PULLUP);
    pinMode(A8, INPUT_PULLUP);
    pinMode(A9, INPUT_PULLUP);
    pinMode(A10, INPUT_PULLUP);
    pinMode(A11, INPUT_PULLUP);
    pinMode(A12, INPUT_PULLUP);
    pinMode(A13, INPUT_PULLUP);
    pinMode(A14, INPUT_PULLUP);
    pinMode(A15, INPUT_PULLUP);
    pinMode(ledPin, OUTPUT);
    //Wire.begin(9);
    //Wire.onRequest(requestEvent);
    //Wire.onReceive(receiveEvent);
    Serial.begin(115200);
    Ethernet.begin(mac, ip);
    Udp.begin(localPort);
    delay(1500);
}


/////////////////////////    CONNECTION STATUS REQUESTED    ////

/*void requestEvent() {
    String data = String();
    data += RackID;
    data += ":CONNECTED";
    Wire.write(data.c_str());
    delay(100);
}*/


///////////////////////////////////////////////    ALARM    ////
class alarm {
    int state;
    bool acknowledge;
    int ledPin;
    long OnTime;
    long OffTime;
    int ledState;
    unsigned long previousMillis;
public:
    alarm(int pin, long on, long off) {
        ledPin = pin;
        state = OFF;
        acknowledge = false;
        pinMode(ledPin, OUTPUT);
        OnTime = on;
        OffTime = off;
        ledState = LOW;
        previousMillis = 0;
    }
    void trigger() {
        state = ON;
        Serial.println("ALARM TRIGGERED");
        //transmit("ALARM TRIGGERED");
        update();
        report();
    }
    void ackw() {
        if (state == ON) {
            state = ACKNOWLEDGE;
            Serial.println("ALARM ACKNOWLEDGE");
            //transmit("ALARM ACKNOWLEDGE");
            digitalWrite(ledPin, HIGH);
            report();
        }
    }
    void reset() {
        if (state > OFF) {
            state = OFF;
            Serial.println("ALARM OFF");
            //transmit("ALARM OFF");
            digitalWrite(ledPin, LOW);
            report();
        }
    }
    void update() {
        if (state == ON) {
            unsigned long currentMillis = millis();
            if ((ledState == HIGH) && (currentMillis - previousMillis >= OnTime))
            {
                ledState = LOW;
                previousMillis = currentMillis;
                digitalWrite(ledPin, ledState);
            }
            else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime))
            {
                ledState = HIGH;
                previousMillis = currentMillis;
                digitalWrite(ledPin, ledState);
            }
        }
    }
    int status() {
        return state;
    }
};


///////////////////////////////////////////    WIRE PROTOCOL    ////
/*
void transmit(String data) {
    Wire.beginTransmission(8);
    Wire.write(RackID);
    Wire.write(":");
    Wire.write(data.c_str());
    Wire.endTransmission();
    return;
}*/


///////////////////////////////////////////////    READ INPUTS    ////
void sense() {
    SensorA0 = analogRead(A0);
    SensorA1 = analogRead(A1);
    SensorA2 = analogRead(A2);
    SensorA3 = analogRead(A3);
    SensorA4 = analogRead(A4);
    SensorA5 = analogRead(A5);
    SensorA6 = analogRead(A6);
    SensorA7 = analogRead(A7);
    SensorA8 = analogRead(A8);
    SensorA9 = analogRead(A9);
    SensorA10 = analogRead(A10);
    SensorA11 = analogRead(A11);
    SensorA12 = analogRead(A12);
    SensorA13 = analogRead(A13);
    SensorA14 = analogRead(A14);
    SensorA15 = analogRead(A15);
    ACK = digitalRead(2);
    RESET = digitalRead(3);
    return;
}

void prtsense() {
    Serial.print("sensor = ");
    Serial.println(SensorA0);
    return;
}

///////////////////////////////////////////////    ALARM DECLARE    ////
alarm alarmA0(22, 100, 200);
alarm alarmA1(23, 100, 200);
alarm alarmA2(24, 100, 200);
alarm alarmA3(25, 100, 200);
alarm alarmA4(26, 100, 200);
alarm alarmA5(27, 100, 200);
alarm alarmA6(28, 100, 200);
alarm alarmA7(29, 100, 200);
alarm alarmA8(30, 100, 200);
alarm alarmA9(31, 100, 200);
alarm alarmA10(32, 100, 200);
alarm alarmA11(33, 100, 200);
alarm alarmA12(34, 100, 200);
alarm alarmA13(35, 100, 200);
alarm alarmA14(36, 100, 200);
alarm alarmA15(37, 100, 200);

void report() {
    String dtt = String();
    dtt += "RE:";
    dtt += RackID;
    dtt += ":";
    dtt += alarmA0.status();
    dtt += alarmA1.status();
    dtt += alarmA2.status();
    dtt += alarmA3.status();
    dtt += alarmA4.status();
    dtt += alarmA5.status();
    dtt += alarmA6.status();
    dtt += alarmA7.status();
    dtt += alarmA8.status();
    dtt += alarmA9.status();
    dtt += alarmA10.status();
    dtt += alarmA11.status();
    dtt += alarmA12.status();
    dtt += alarmA13.status();
    dtt += alarmA14.status();
    dtt += alarmA15.status();
    //Wire.beginTransmission(8);
    //Wire.write("RE:");
    //Wire.write(dtt.c_str());
    //delay(15);
    //Wire.endTransmission();
    //String data = "RE:" + dtt;
    ethercomm(dtt);
    transmited = true;
    te_report = 0;
    Serial.println("REPORTED");
    return;
}


void ethercomm(String data) {
    packetSize = Udp.parsePacket();

    if (packetSize > 0) {

        Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
        String datReq(packetBuffer);

        if (datReq == "Request") {
            Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
            Udp.print(data);
            Udp.endPacket();
        }
    }
}

///////////////////////////////////////////////    MAIN LOOP    ////
void loop() {
    /*
    Wire.requestFrom(8, 9);
    String message = String();
    while (Wire.available()) { // loop through all but the last
        char c = Wire.read(); // receive byte as a character
                              //Serial.print(c);
        message += c;
    }
    if (message == "connected") {
        digitalWrite(ledPin, HIGH);
        if (!transmited) report();
    }
    else {
        digitalWrite(ledPin, LOW);
        transmited = false;
    }
    */
    if (te_report >= report_every * 1000) {
        report();
    }
    sense();
    alarmA0.update();
    alarmA1.update();
    alarmA2.update();
    alarmA3.update();
    alarmA4.update();
    alarmA5.update();
    alarmA6.update();
    alarmA7.update();
    alarmA8.update();
    alarmA9.update();
    alarmA10.update();
    alarmA11.update();
    alarmA12.update();
    alarmA13.update();
    alarmA14.update();
    alarmA15.update();

    /*
    if (SensorA0 <= calibration) {
    digitalWrite(ledPin, HIGH);
    }
    else {
    digitalWrite(ledPin, LOW);
    }
    */

    ///////////////////////////////////////////////    CONTROL A0    ////
    if (SensorA0 <= calibration && teA0 >= wait &&
        alarmA0.status() == OFF) {
        alarmA0.trigger();
    }
    else if (SensorA0 > calibration) {
        if (!RESET) alarmA0.reset();
        if (!ACK) alarmA0.ackw();
        teA0 = 0;
    }
    ///////////////////////////////////////////////    CONTROL A1    ////
    if (SensorA1 <= calibration && teA1 >= wait &&
        alarmA1.status() == OFF) {
        alarmA1.trigger();
    }
    else if (SensorA1 > calibration) {
        if (!RESET) alarmA1.reset();
        if (!ACK) alarmA1.ackw();
        teA1 = 0;
    }
    //////////////////////////////////////////////    CONTROL A2    ////
    if (SensorA2 <= calibration && teA2 >= wait &&
        alarmA2.status() == OFF) {
        alarmA2.trigger();
    }
    else if (SensorA2 > calibration) {
        if (!RESET) alarmA2.reset();
        if (!ACK) alarmA2.ackw();
        teA2 = 0;
    }
    //////////////////////////////////////////////    CONTROL A3    ////
    if (SensorA3 <= calibration && teA3 >= wait &&
        alarmA3.status() == OFF) {
        alarmA3.trigger();
    }
    else if (SensorA3 > calibration) {
        if (!RESET) alarmA3.reset();
        if (!ACK) alarmA3.ackw();
        teA3 = 0;
    }
    //////////////////////////////////////////////    CONTROL A4    ////
    if (SensorA4 <= calibration && teA4 >= wait &&
        alarmA4.status() == OFF) {
        alarmA4.trigger();
    }
    else if (SensorA4 > calibration) {
        if (!RESET) alarmA4.reset();
        if (!ACK) alarmA4.ackw();
        teA4 = 0;
    }
    //////////////////////////////////////////////    CONTROL A5    ////
    if (SensorA5 <= calibration && teA5 >= wait &&
        alarmA5.status() == OFF) {
        alarmA5.trigger();
    }
    else if (SensorA5 > calibration) {
        if (!RESET) alarmA5.reset();
        if (!ACK) alarmA5.ackw();
        teA5 = 0;
    }
    //////////////////////////////////////////////    CONTROL A6    ////
    if (SensorA6 <= calibration && teA6 >= wait &&
        alarmA6.status() == OFF) {
        alarmA6.trigger();
    }
    else if (SensorA6 > calibration) {
        if (!RESET) alarmA6.reset();
        if (!ACK) alarmA6.ackw();
        teA6 = 0;
    }
    //////////////////////////////////////////////    CONTROL A7    ////
    if (SensorA7 <= calibration && teA7 >= wait &&
        alarmA7.status() == OFF) {
        alarmA7.trigger();
    }
    else if (SensorA7 > calibration) {
        if (!RESET) alarmA7.reset();
        if (!ACK) alarmA7.ackw();
        teA7 = 0;
    }
    //////////////////////////////////////////////    CONTROL A8    ////
    if (SensorA8 <= calibration && teA8 >= wait &&
        alarmA8.status() == OFF) {
        alarmA8.trigger();
    }
    else if (SensorA8 > calibration) {
        if (!RESET) alarmA8.reset();
        if (!ACK) alarmA8.ackw();
        teA8 = 0;
    }
    //////////////////////////////////////////////    CONTROL A9    ////
    if (SensorA9 <= calibration && teA9 >= wait &&
        alarmA9.status() == OFF) {
        alarmA9.trigger();
    }
    else if (SensorA9 > calibration) {
        if (!RESET) alarmA9.reset();
        if (!ACK) alarmA9.ackw();
        teA9 = 0;
    }
    //////////////////////////////////////////////    CONTROL A10    ////
    if (SensorA10 <= calibration && teA10 >= wait &&
        alarmA10.status() == OFF) {
        alarmA10.trigger();
    }
    else if (SensorA10 > calibration) {
        if (!RESET) alarmA10.reset();
        if (!ACK) alarmA10.ackw();
        teA10 = 0;
    }
    //////////////////////////////////////////////    CONTROL A11    ////
    if (SensorA11 <= calibration && teA11 >= wait &&
        alarmA11.status() == OFF) {
        alarmA11.trigger();
    }
    else if (SensorA11 > calibration) {
        if (!RESET) alarmA11.reset();
        if (!ACK) alarmA11.ackw();
        teA11 = 0;
    }
    //////////////////////////////////////////////    CONTROL A12    ////
    if (SensorA12 <= calibration && teA12 >= wait &&
        alarmA12.status() == OFF) {
        alarmA12.trigger();
    }
    else if (SensorA12 > calibration) {
        if (!RESET) alarmA12.reset();
        if (!ACK) alarmA12.ackw();
        teA12 = 0;
    }
    //////////////////////////////////////////////    CONTROL A13    ////
    if (SensorA13 <= calibration && teA13 >= wait &&
        alarmA13.status() == OFF) {
        alarmA13.trigger();
    }
    else if (SensorA13 > calibration) {
        if (!RESET) alarmA13.reset();
        if (!ACK) alarmA13.ackw();
        teA13 = 0;
    }
    //////////////////////////////////////////////    CONTROL A14    ////
    if (SensorA14 <= calibration && teA14 >= wait &&
        alarmA14.status() == OFF) {
        alarmA14.trigger();
    }
    else if (SensorA14 > calibration) {
        if (!RESET) alarmA14.reset();
        if (!ACK) alarmA14.ackw();
        teA14 = 0;
    }
    //////////////////////////////////////////////    CONTROL A15    ////
    if (SensorA15 <= calibration && teA15 >= wait &&
        alarmA15.status() == OFF) {
        alarmA15.trigger();
    }
    else if (SensorA15 > calibration) {
        if (!RESET) alarmA15.reset();
        if (!ACK) alarmA15.ackw();
        teA15 = 0;
    }
    delay(50);
}
