#include <EEPROM.h>

const int PIN_LIMIT_SWITCH = 6;
const int PIN_RPWM = 3;
const int PIN_LPWM = 4;
const int PIN_BUTTON = 7;

int STATE = 1; // 1 = closed, 0 = open

const int MAX_TIME = 3000;
const int INITIAL_DELAY = 800;
const int END_EXTRA_TIME = 200;
const int STEP_DELAY = 100;

void setup() 
{
  pinMode(PIN_RPWM, OUTPUT);
  pinMode(PIN_LPWM, OUTPUT);
  pinMode(PIN_LIMIT_SWITCH, INPUT_PULLUP);
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  EEPROM.get(0, STATE);
  // ensure valid value in case EEPROM contains garbage
  if (STATE != 0 && STATE != 1)
    STATE = 1;
}

void saveState(int s) 
{
  int current;
  EEPROM.get(0, current);
  if (current != s)
    EEPROM.put(0, s);
}

void moveMotor(bool direction) 
{
  int stopp = 0;

  // direction: true = closing, false = opening
  digitalWrite(PIN_RPWM, direction ? HIGH : LOW);
  digitalWrite(PIN_LPWM, direction ? LOW : HIGH);

  delay(INITIAL_DELAY);  // move out of end position
  stopp += INITIAL_DELAY;

  while (stopp < MAX_TIME) 
  {
    delay(STEP_DELAY);
    stopp += STEP_DELAY;

    int micro_value = digitalRead(PIN_LIMIT_SWITCH);

    if (micro_value == LOW) 
    {
      delay(END_EXTRA_TIME); // push fully into end position
      break;
    }
  }

  // stop motor
  digitalWrite(PIN_RPWM, LOW);
  digitalWrite(PIN_LPWM, LOW);
}

void loop() {
  int button = digitalRead(PIN_BUTTON);

  if (button == HIGH) {

    if (STATE == 0) // open -> close
    {        
      moveMotor(true);       // true = closing direction
      STATE = 1;
    }
    else // closed -> open
    {                   
      moveMotor(false);
      STATE = 0;
    }
    saveState(STATE);
  }

  delay(100);
}
