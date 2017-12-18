const int motor_B_direction_PIN = 13;
const int motor_A_direction_PIN = 12;
const int motor_A_PWM = 10;
const int motor_B_PWM = 11;
const int switch_A_links = 2;
const int switch_A_rechts = 3;
boolean motor_A_direction  = HIGH;
boolean motor_B_direction  = HIGH;
boolean test = false;
#include <MIDI.h>
int basenote[] = {48,54,60,66,72};

#if defined(USBCON)
#include <midi_UsbTransport.h>

static const unsigned sUsbTransportBufferSize = 16;
typedef midi::UsbTransport<sUsbTransportBufferSize> UsbTransport;

UsbTransport sUsbTransport;

MIDI_CREATE_INSTANCE(UsbTransport, sUsbTransport, MIDI);

#else // No USB available, fallback to Serial
MIDI_CREATE_DEFAULT_INSTANCE();
#endif


////// --
/////////////////////////////////////
////////////////////////////////////////
/////////////////////////////////////
////// --

void handleNoteOn(byte inChannel, byte inNumber, byte inVelocity)
{ 
  if ((inNumber >= basenote[0]) && (inNumber <= (basenote[0]+6))) // Zwischen C2 und F2 --> MOTOR A // LINKS
    {
      int speed2 = map(inNumber, basenote[0], (basenote[0]+6), 50, 255);
      analogWrite(motor_A_PWM,speed2 );
      digitalWrite(motor_A_direction_PIN, HIGH);motor_A_direction = HIGH;    
    }

if ((inNumber > basenote[1]) && (inNumber <= (basenote[1]+6))) // Zwischen X und XX --> MOTOR A // RECHTS
    {
      int speed2 = map(inNumber, (basenote[1] + 1), (basenote[1]+6), 50, 255);
      digitalWrite(motor_A_direction_PIN, LOW);motor_A_direction = LOW; 
      analogWrite(motor_A_PWM,speed2 ); 
    }
  if ((inNumber > basenote[2]) && (inNumber <= (basenote[2]+6))) // Zwischen C2 und F2 --> MOTOR A // LINKS
    {
      int speed2 = map(inNumber, basenote[2], (basenote[2]+6), 50, 255);
      analogWrite(motor_B_PWM,speed2 ); 
      digitalWrite(motor_B_direction_PIN, HIGH);motor_B_direction = HIGH;
    }

if ((inNumber > basenote[3]) && (inNumber <= (basenote[3]+6))) // Zwischen X und XX --> MOTOR A // RECHTS
    {
      int speed2 = map(inNumber, (basenote[3] + 1), (basenote[3]+6), 50, 255);
      digitalWrite(motor_B_direction_PIN, LOW); motor_B_direction = LOW;
      analogWrite(motor_B_PWM,speed2 ); 
    }
} 
    

void handleNoteOff(byte inChannel, byte inNumber, byte inVelocity)
{

 if ((inNumber >= basenote[0]) && (inNumber <= (basenote[1]+6))) // Zwischen C2 und F2 --> MOTOR A // LINKS
    {
  analogWrite(motor_A_PWM, 0);
    }

if ((inNumber > basenote[2]) && (inNumber <= (basenote[3]+6))) // Zwischen C2 und F2 --> MOTOR A // LINKS
    {
  analogWrite(motor_B_PWM, 0);
    }
}


void setup() 
{  
  

   //Serial.begin(115200);
    // while (!Serial);
    MIDI.begin(); // Alle Kanäle
    MIDI.setHandleNoteOn(handleNoteOn);
    MIDI.setHandleNoteOff(handleNoteOff);
    pinMode(A0,INPUT_PULLUP); 
    pinMode(A1,INPUT_PULLUP); 
    pinMode(A2,INPUT_PULLUP); 
    pinMode(A3,INPUT_PULLUP); 
    pinMode(8,INPUT_PULLUP); 
    pinMode(motor_B_direction_PIN, OUTPUT);   
    pinMode(motor_A_direction_PIN, OUTPUT); 
    pinMode(switch_A_links, INPUT_PULLUP);
    pinMode(switch_A_rechts, INPUT_PULLUP);
} 

void loop() 
{ 
    if(   (digitalRead(switch_A_links)  == LOW)   && (motor_A_direction == LOW ))   {analogWrite(motor_A_PWM, 0);} // Auschalten
    if(   (digitalRead(switch_A_rechts) == LOW)   && (motor_A_direction == HIGH)) {analogWrite(motor_A_PWM, 0);} // Auschalten
    MIDI.read();
 
 
 while( digitalRead(8) == LOW)
    {
    if(   (analogRead(A0) < 1000))   {digitalWrite(motor_A_direction_PIN, LOW);analogWrite(motor_A_PWM, 100);delay(2);} else { analogWrite(motor_A_PWM, 0); }
    if(   (analogRead(A1) < 1000 )   ){digitalWrite(motor_A_direction_PIN, HIGH);analogWrite(motor_A_PWM, 100);delay(2);}else { analogWrite(motor_A_PWM, 0); }
    if(   (analogRead(A2) < 1000 )   ){digitalWrite(motor_B_direction_PIN, LOW);analogWrite(motor_B_PWM, 100);delay(2);} else { analogWrite(motor_B_PWM, 0); }
    if(   (analogRead(A3) < 1000 )   ){digitalWrite(motor_B_direction_PIN, HIGH);analogWrite(motor_B_PWM, 100);delay(2);}   else { analogWrite(motor_B_PWM, 0); }

}
}


