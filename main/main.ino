//#include <Keypad.h>
//#include <NewPing.h>

const byte ROWS = 4;
const byte COLS = 3;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3};

//Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

int enable_left = 11;
int enable_right = 10;

int direction_left1 = 6;
int direction_left2 = 7;

int direction_right1 = 2;
int direction_right2 = 3;

int leftPin = A0;

int echoPinL = 13;
int trigPinL = 12;

int echoPinF = 11;
int trigPinF = 10;
const int MAX_DISTANCE = 350;

long duration, cm, start, ending;

//NewPing sonar(trigPin, echoPin, MAX_DISTANCE);

int left_distance;
int front_distance;
int old_distance = -1;
bool deactivated = false;

void setup() {
  Serial.begin(9600);
  pinMode(direction_left1, OUTPUT);
  pinMode(direction_left2, OUTPUT);
  pinMode(direction_right1, OUTPUT);
  pinMode(direction_right2, OUTPUT);
}

void loop() {

  rbt_forward(200, 200);
//  delay(1000);
//  rbt_stop();
//  delay(1000);
//  left_distance = detect_left();
//  Serial.print(left_distance);
//  Serial.print("cm");
//  Serial.println();

  //  // Situation 3: Robot is driving towards wall.
  //  // DETECT: distance is getting closer to a MIN threshold
  //  // -> what to do?
  //  // add more power on the left side
  //  if (left_distance <= 7) {
  //    Serial.println("left_distance <= 7");
  //    rbt_stop();
  //    delay(1000);
  //    rbt_forward(255, 150);
  //  }
  //
  //  // Situation 1: Robot is following the wall.
  //  // DETECT: distances remain below a MAX threshold
  //  // -> what to do?
  //  // keep going straight
  //  if ((left_distance >= 8) && (left_distance < 10)) {
  //    Serial.println("(left_distance >= 8) && (left_distance <= 11)");
  //    rbt_forward(230, 230);
  //  }
  //  //
  //  //  // Situation 2: Robot is driving away from wall.
  //  //  // DETECT: distance are above a MAX threshold
  //  //  // -> what to do?
  //  //  // add more power on the right side
  //  if ((left_distance >= 10) && (left_distance <= 19)) {
  //    Serial.println("(left_distance >= 11) && (left_distance <= 25)");
  //    rbt_stop();
  //    delay(1000);
  //    rbt_forward(200, 255);
  //  }
  //
  //  // Situation 5: There is no more wall
  //  // DETECT: big change in distances of left sensor
  //  // -> what to do?
  //  // turn left
  //
//  if (left_distance > 22) {
//    Serial.println("turning left");
//    rbt_stop();
//    delay(1000);
//    turn_left();
//    rbt_stop();
//    delay(2000);
//  }

  // BELOW USES FRONT SENSOR

  // Situation 4: The robot is at a corner
  // DETECT: left and front sensor show short distance
  // -> what to do?
  // Turn right
  // a) if front sensor is OFF, follow wall
  // a) if front sensor is ON, turn right again

}

// Situation 6: There is an obstacle we need to pass
// DETECT:



int detect_front() {
  int cm = 0;
  for (int i = 0; i < 15; i++) {
    pinMode(trigPinF, OUTPUT);
    digitalWrite(trigPinF, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinF, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinF, LOW);
    pinMode(echoPinF, INPUT);
    duration = pulseIn(echoPinF, HIGH);
    // convert the time into a distance
    cm += microsecondsToCentimeters(duration);
  }
  delay(200);
  return cm / 15;
}

int detect_left() {

  int cm = 0;
  for (int i = 0; i < 15; i++) {
    pinMode(trigPinL, OUTPUT);
    digitalWrite(trigPinL, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPinL, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPinL, LOW);
    pinMode(echoPinL, INPUT);
    duration = pulseIn(echoPinL, HIGH);
    // convert the time into a distance
    cm += microsecondsToCentimeters(duration);
  }
  delay(200);
  return cm / 15;
}

double microsecondsToInches(double microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}

void rbt_move() {

  digitalWrite(direction_left1, LOW);
  digitalWrite(direction_left2, HIGH);
  digitalWrite(direction_right1, HIGH);
  digitalWrite(direction_right2, LOW);
}

void rbt_stop() {
  digitalWrite(direction_left1, LOW);
  digitalWrite(direction_left2, LOW);
  digitalWrite(direction_right1, LOW);
  digitalWrite(direction_right2, LOW);
  analogWrite(enable_left, 0);
  analogWrite(enable_right, 0);
}

void rbt_forward(int left_value, int right_value) {
  rbt_move();
  analogWrite(enable_left, left_value);
  analogWrite(enable_right, right_value);
}

void turn_right() {
  rbt_move();
  analogWrite(enable_left, 255);
  analogWrite(enable_right, 0);
  delay(2080);
}

void turn_left() {
  rbt_move();
  analogWrite(enable_right, 255);
  analogWrite(enable_left, 0);
  delay(2080);
}

void go_around() {

}
