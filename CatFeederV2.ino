/*

   CAT FEEDER V2 - 2020.06.21
   Written with a lot of coffee by Jérémy Noverraz 


   This code is able to control a servo motor to open a cat feeder door based on a pre-programmed timer
*/

/* ------ INCLUDE DEPENDENCIES LIBRARIES ------- */
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <Time.h>
#include <TimeAlarms.h>

/* ---- CONSTANTES ----*/
const char *ssid     = "YOUR_SSID";
const char *password = "YOUR_WIFI_PASSWORD";

/* ---- DECLARATION ET INITIALISATION DES VARIABLES ---- */
int pos = 0;

/* ---- DECLARATION ET INITIALISATION DES FONCTIONS ---- */
Servo CatFeeder_servo;


void setup() {

  /* ---- INITIALISATION DE LA CONSOLE ---- */
  Serial.begin(115200);


  /*---- SERVO SETUP ----*/
  CatFeeder_servo.attach(2);
  CatFeeder_servo.write(pos);

  /*---- WIFI SETUP ----*/
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }



  /* ---- ALARM FOR TRIGGER FOOD SETUP ---- */
  setTime(8, 30, 0, 6, 21, 20); // set time to Saturday 8:29:10am Jun 21 2020
  // create the alarms
  Alarm.alarmRepeat(8, 30, 10, MorningAlarm); // 8:30am every day
 //Alarm.alarmRepeat(8, 30, 30, ExplicitAlarm); // Explicit alarm test @ 8:30:30am
  Alarm.alarmRepeat(17, 45, 0, EveningAlarm); // 5:45pm every day


}

void  loop() {
  SerialClockDisplay();
  Alarm.delay(1000); // wait one second between clock display
}


// functions to be called when an alarm triggers:
void MorningAlarm() {
  Serial.println("Alarm : - Time to feed the cat ! ");
  Serial.println();
  // moving servo by 180°
  CatFeeder_servo.write(180);
  Alarm.delay(2000);
  // moving servo to initial position
  CatFeeder_servo.write(pos);
}

void EveningAlarm() {
  Serial.println("Evening Alarm: - Time to feed the cat !");
  // moving servo by 180°
  CatFeeder_servo.write(180);
  Alarm.delay(2000);
  // moving servo to initial position
  CatFeeder_servo.write(pos);
}

void ExplicitAlarm() {
  Serial.println("Exlicit Alarm: - Time to feed the cat !");
  // moving servo by 180°
  CatFeeder_servo.write(180);
  Alarm.delay(2000);
  // moving servo to initial position
  CatFeeder_servo.write(pos);
}


void SerialClockDisplay()
{
  // serial monitor clock display of the time
  Serial.print(hour());
  Serial.print(" : ");
  Serial.print(minute());
  Serial.print(" : ");
  Serial.print(second());
  Serial.println();
}
