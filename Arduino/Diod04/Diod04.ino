const int LED=9;
const int BUTTON=2;
const int BLED = 9;
const int GLED = 10;
const int RLED = 11;

boolean lastButton = LOW;
boolean currentButton = LOW;
int ledMode = 0;

void setup() {
  pinMode(BLED, OUTPUT);
  pinMode(GLED, OUTPUT);
  pinMode(RLED, OUTPUT);
  pinMode(BUTTON, INPUT);

}

boolean debounce(boolean last)
{
  boolean current = digitalRead(BUTTON);
  if(last != current){
    delay(5);
    current = digitalRead(BUTTON);
    return current;
  }
}

void setMode(int mode)
{
  switch(mode){
    case 1: digitalWrite(RLED, HIGH);
            digitalWrite(GLED, LOW);
            digitalWrite(BLED, LOW); 
            break;            
    case 2: digitalWrite(RLED, LOW);
            digitalWrite(GLED, HIGH);
            digitalWrite(BLED, LOW);
            break;
    case 3: digitalWrite(RLED, LOW);
            digitalWrite(GLED, LOW);
            digitalWrite(BLED, HIGH);
            break;
    case 4: digitalWrite(RLED, 127);
            digitalWrite(GLED, 0);
            digitalWrite(BLED, 127);
            break;
    case 5: digitalWrite(RLED, 0);
            digitalWrite(GLED, 127);
            digitalWrite(BLED, 127);
            break;
    case 6: digitalWrite(RLED, 127);
            digitalWrite(GLED, 127);
            digitalWrite(BLED, 0);
            break;
    case 7: digitalWrite(RLED, 85);
            digitalWrite(GLED, 85);
            digitalWrite(BLED, 85);
            break;
    default:digitalWrite(RLED, LOW);
            digitalWrite(GLED, LOW);
            digitalWrite(BLED, LOW);
            break;
  }
}

void loop() {
  currentButton = debounce(lastButton);
  if(lastButton == LOW && currentButton == HIGH){
    ledMode++;
  }
  lastButton = currentButton;

  if(ledMode == 8)ledMode = 0;

  setMode(ledMode);
}
