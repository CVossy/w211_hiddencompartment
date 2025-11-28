int PIN_W211_MICRO_OUT = 5;
int PIN_W211_MICRO_IN = 6;
int PIN_IBT_RPWM_Output = 3; 
int PIN_IBT_LPWM_Output = 4; 
int PIN_INPUT = 7;

int STATE = 0; // 0 is closed and 1 is open

int max_stopp_time = 8000;
void setup()
{
  pinMode(PIN_IBT_RPWM_Output, OUTPUT);
  pinMode(PIN_IBT_LPWM_Output, OUTPUT);
  pinMode(PIN_W211_MICRO_OUT, OUTPUT);
  pinMode(PIN_W211_MICRO_IN, INPUT);
  pinMode(PIN_INPUT, INPUT);
  digitalWrite(PIN_W211_MICRO_OUT,HIGH);
}
 
void loop()
{
  int micro_value = digitalRead(PIN_W211_MICRO_IN);
  int input_value = digitalRead(PIN_INPUT);
  
  // if button is pressed, try to move the motor for 8s - if that isnt sufficient, there is some other problem! but we can't let the motor run forever
  if (input_value == 1 && STATE == 0)
  {
    int stopp = 0;
    while(stopp < max_stopp_time)
    {
      digitalWrite(PIN_IBT_RPWM_Output, 1);
      digitalWrite(PIN_IBT_LPWM_Output, 0);
      delay(100);
      stopp += 100;
      micro_value = digitalRead(PIN_W211_MICRO_IN);
      if (micro_value == 1)
        stopp = max_stopp_time;
      
    }
  }
  else if (input_value == 1 && STATE == 1)
  {
    int stopp = 0;
    while(stopp < max_stopp_time)
    {
      digitalWrite(PIN_IBT_RPWM_Output, 0);
      digitalWrite(PIN_IBT_LPWM_Output, 1);
      delay(100);
      stopp += 100;
      micro_value = digitalRead(PIN_W211_MICRO_IN);
      if (micro_value == 1)
        stopp = max_stopp_time;
      
    }
  }
}
