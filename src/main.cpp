#include <Arduino.h> // Arduino 라이브러리 포함
#include <TaskScheduler.h> // TaskScheduler 라이브러리 포함
#include <PinChangeInterrupt.h>

const int redPin = 13;
const int yellowPin = 12;
const int greenPin = 11;
const int firstButton = 4;
const int secondButton = 3;
const int thirdButton = 2;

volatile bool firstButtonState = false;
volatile bool secondButtonState = false;
volatile bool thirdButtonState = false;

int bcnt=0;

Scheduler runner;

void task1();
void task2();
void task3();
void task4();
void task5();
void task6();

Task t1(2000, TASK_FOREVER, &task1, &runner, false);
Task t2(500, TASK_FOREVER, &task2, &runner, false);
Task t3(2000, TASK_FOREVER, &task3, &runner, false);
Task t4(0, TASK_FOREVER, &task4, &runner, false);
Task t5(500, TASK_FOREVER, &task5, &runner, false);
Task t6(0, TASK_FOREVER, &task6, &runner, false);

void TrafficOn() {
  t1.enable();
}

void firstint(){
  runner.disableAll();
  firstButtonState = !digitalRead(firstButton);
  if (!firstButtonState) TrafficOn();
}

void secondint(){
  runner.disableAll();
  secondButtonState = !digitalRead(secondButton);
  if (!secondButtonState) TrafficOn();
}

void thirdint(){
  runner.disableAll();
  thirdButtonState = !digitalRead(thirdButton);
  if (!thirdButtonState) TrafficOn();
}

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  pinMode(firstButton, INPUT_PULLUP);
  pinMode(secondButton, INPUT_PULLUP);
  pinMode(thirdButton, INPUT_PULLUP);

  attachPCINT(digitalPinToPCINT(firstButton), firstint, CHANGE);
  attachInterrupt(digitalPinToInterrupt(secondButton), secondint, CHANGE);
  attachInterrupt(digitalPinToInterrupt(thirdButton), thirdint, CHANGE);

  runner.addTask(t1);
  runner.addTask(t2);
  runner.addTask(t3);
  runner.addTask(t4);
  runner.addTask(t5);
  TrafficOn();
}

void task1() {
  bcnt=0;
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, HIGH);
  t1.disable();
  t2.enableDelayed(2000);
}

void task2() {
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, HIGH);
  t2.disable();
  t3.enableDelayed(500);
}

void task3() {
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, HIGH);
  t3.disable();
  t4.enableDelayed(2000);
}

void task4() {
  digitalWrite(greenPin, LOW);
  t4.disable();
  if(bcnt==3)
  {
    t6.enableDelayed(1000/6);
  }
  else
  {
    t5.enableDelayed(1000/6);
  }
}

void task5() {
  bcnt=bcnt+1;
  digitalWrite(greenPin, HIGH);
  t5.disable();
  t4.enableDelayed(1000/6);
}

void task6() {
  digitalWrite(yellowPin, HIGH);
  t6.disable();
  t1.enableDelayed(500);
}

void loop() {
  if(firstButtonState)
  {
    analogWrite(redPin, 255);
    analogWrite(yellowPin, 0);
    analogWrite(greenPin, 0);
  }
  else if(secondButtonState)
  {
    digitalWrite(redPin, HIGH);
    digitalWrite(yellowPin, HIGH);
    digitalWrite(greenPin, HIGH);
    delay(200);
    digitalWrite(redPin, LOW);
    digitalWrite(yellowPin, LOW);
    digitalWrite(greenPin, LOW);
    delay(200);
  }
  else if(thirdButtonState)
  {
    digitalWrite(redPin, LOW);
    digitalWrite(yellowPin, LOW);
    digitalWrite(greenPin, LOW);
  }
  else runner.execute();
}