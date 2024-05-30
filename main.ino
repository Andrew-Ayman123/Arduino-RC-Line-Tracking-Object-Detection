#define lMotorForward 4
#define lMotorSpeed 5
#define lMotorBackward 2

#define rMotorForward 7
#define rMotorSpeed 6
#define rMotorBackward 3

#define irRight 8
#define irCenter 9
#define irLeft 10

#define ultraEcho 12
#define ultraTrig 11

// 50 means 0.2m/s
int fwdSpeed = 64;
int rotatingSpeed = 70;
double rightFactor = 1.18;
bool isRightOn() {
    return digitalRead(irRight);

}
bool isLeftOn() {
    return digitalRead(irLeft);
}
bool isCenterOn() {
    return digitalRead(irCenter);

}

void carSetup() {
    pinMode(lMotorForward, OUTPUT);
    pinMode(lMotorSpeed, OUTPUT);
    pinMode(lMotorBackward, OUTPUT);
    pinMode(rMotorForward, OUTPUT);
    pinMode(rMotorSpeed, OUTPUT);
    pinMode(rMotorBackward, OUTPUT);
}
void forward(int speed) {
    analogWrite(lMotorSpeed, speed);
    analogWrite(rMotorSpeed, speed * rightFactor);
    digitalWrite(lMotorForward, HIGH);
    digitalWrite(lMotorBackward, LOW);
    digitalWrite(rMotorForward, HIGH);
    digitalWrite(rMotorBackward, LOW);
}
void backward(int speed) {
    digitalWrite(lMotorForward, LOW);
    digitalWrite(lMotorBackward, HIGH);
    analogWrite(lMotorSpeed, speed);
    digitalWrite(rMotorForward, LOW);
    digitalWrite(rMotorBackward, HIGH);
    analogWrite(rMotorSpeed, speed * rightFactor);
}
void rotateLeft(int speed) {
    digitalWrite(lMotorForward, LOW);
    analogWrite(lMotorSpeed, speed);
    digitalWrite(lMotorBackward, HIGH);

    digitalWrite(rMotorForward, HIGH);
    analogWrite(rMotorSpeed, min(speed * rightFactor, 255));
    digitalWrite(rMotorBackward, LOW);
}
void rotateRight(int speed) {
    digitalWrite(lMotorForward, HIGH);
    digitalWrite(lMotorBackward, LOW);
    analogWrite(lMotorSpeed, speed);
    digitalWrite(rMotorForward, LOW);
    digitalWrite(rMotorBackward, HIGH);
    analogWrite(rMotorSpeed, speed * rightFactor);
}
void turnRight(int speed) {
    digitalWrite(lMotorForward, HIGH);
    digitalWrite(lMotorBackward, LOW);
    analogWrite(lMotorSpeed, speed);
    digitalWrite(rMotorForward, LOW);
    digitalWrite(rMotorBackward, HIGH);
    analogWrite(rMotorSpeed, speed * 9/10);
}
void turnLeft(int speed) {
    digitalWrite(lMotorForward, LOW);
    analogWrite(lMotorSpeed, speed * 9/10);
    digitalWrite(lMotorBackward, HIGH);

    digitalWrite(rMotorForward, HIGH);
    analogWrite(rMotorSpeed, min(speed * rightFactor, 255));
    digitalWrite(rMotorBackward, LOW);
}
void stop() {
    digitalWrite(lMotorForward, LOW);
    digitalWrite(lMotorBackward, LOW);
    analogWrite(lMotorSpeed, 0);
    digitalWrite(rMotorForward, LOW);
    digitalWrite(rMotorBackward, LOW);
    analogWrite(rMotorSpeed, 0);
}
void setup()
{
    carSetup();
    pinMode(irRight, INPUT);
    pinMode(irLeft, INPUT);
    pinMode(irCenter, INPUT);
    pinMode(ultraTrig, OUTPUT);
    pinMode(ultraEcho, INPUT);


}
void debug() {
    Serial.println("#############################");
    Serial.print("Right:");
    Serial.println(analogRead(irRight));
    Serial.print("Center:");
    Serial.println(analogRead(irCenter));
    Serial.print("Left:");
    Serial.println(analogRead(irLeft));
    delay(500);
}

double  generateDistance() {
    digitalWrite(ultraTrig, LOW);
    delayMicroseconds(2);

    digitalWrite(ultraTrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(ultraTrig, LOW);



    // calculate the distance
    return pulseIn(ultraEcho, HIGH) * 0.0344 / 2;
}double distance;
void loop()
{

    distance = generateDistance();
    if (distance < 8 && distance>1) {
        rotateLeft(rotatingSpeed);
        delay(500);
        forward(fwdSpeed);
        delay(950);
        turnRight(rotatingSpeed);
        delay(650);
        forward(fwdSpeed);
        delay(200);
    }


    if (isRightOn() && !isLeftOn()) {
        turnRight(rotatingSpeed);

        do {
            delay(5);
        } while (!(isCenterOn() || isLeftOn()) || isRightOn());
        forward(fwdSpeed);
        delay(75);


    }
    else if (!isRightOn() && isLeftOn()) {
        turnLeft(rotatingSpeed);

        do {
            delay(5);
        } while (!(isCenterOn() || isRightOn()) || isLeftOn());
        forward(fwdSpeed);
        delay(75);
    }
    else {
        forward(fwdSpeed);
        delay(75);
    }



}
