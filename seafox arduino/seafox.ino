
const char Motor =  "M";
bool NOTLIVE = true;
int motor2pin1 = 30;
int  motor2pin2 = 31;
bool FULLSTOP = false;
//speaker = up/down, 30/31, pwm: 4
// orange = bottom left, 31/32, pwm: 5
//brown = bottom right, 33/34, pwm: 6
//green = top right, 35/36, pwm: 7
//blue = top left, 37/38, pwm: 8
void setup() {
Serial.begin(9600);
//pwm pins
  //top left
   // pinMode(4, OUTPUT);
//motor groupe
  //up/down speaker
    pinMode(30, OUTPUT);
    pinMode(31, OUTPUT);
        pinMode(4, OUTPUT);
  //bottom left/orange
    pinMode(32, OUTPUT);
        pinMode(33, OUTPUT);
    pinMode(5, OUTPUT);
  //bottom right/brown  
    pinMode(34, OUTPUT);
    pinMode(35, OUTPUT);
    pinMode(6, OUTPUT);
    //top right/green
    pinMode(36, OUTPUT);
    pinMode(37, OUTPUT);
    pinMode(7, OUTPUT);
    //top left/blue
        pinMode(38, OUTPUT);
    pinMode(39, OUTPUT);
    pinMode(8, OUTPUT);


    //debug
      pinMode(LED_BUILTIN, OUTPUT);
      Serial.println("registered");
}

void loop() {
  if(FULLSTOP != true)
  {
delay(59);
ReadSerial();
  }
  else{
    emergencyShutdownFullstop();
    Serial.println("Full Stop");
  }

}
void ReadSerial()
{
  digitalWrite(LED_BUILTIN, HIGH);
 
String input;
  if(Serial.available() && NOTLIVE)
  {
    input = Serial.readString();
    command(input); 
  }
}

void command(String Output)
{
  NOTLIVE = false;
  //initialize variables
          int speed;
          bool CW;
          char MotorID = Output.charAt(3);
          //debug print
          Serial.println(MotorID);
          //check for clock wise or not
          if(Output.charAt(5) == '1')
          {
            CW = true;

            
          }
          else if(Output.charAt(5) == '0'){
            CW = false;
                  //      digitalWrite(LED_BUILTIN, HIGH);

          }
          else{
            outputAndErrors(3, "invalid rotation shutting down");
          }
          // speed system
        if(Output.length() == 9){
          speed = Output.charAt(7);

        }
        else if(Output.length() == 10)
        {
          int tens =  Output.charAt(7) * 10;
          int ones = Output.charAt(8);
          speed = tens + ones;
        }
        else{
          int hunderds =  Output.charAt(7) * 100;
          int tens = Output.charAt(8) * 10;
          int ones = Output.charAt(9);
          speed = hunderds + tens + ones;
        }
        if(speed >= 0 && speed <= 255)
        {
 //speed debugging
        Serial.println(speed);
      //run motors
          MotorControl(MotorID, speed, CW);
        }
        else {
        outputAndErrors(2, "faulty speed");
        }
       
} 

void MotorControl(int MotorID, int speed, bool CW)
{
  //debug LED
   digitalWrite(LED_BUILTIN, LOW);
   //find motor and activate them based on variables
  if(MotorID == 1)
  {
    if(CW){
    digitalWrite(30, HIGH);
    digitalWrite(31, LOW);
    }
    else{
    digitalWrite(31, HIGH);
    digitalWrite(30, LOW);
    }
    if(speed == 0)
    {
          digitalWrite(31, LOW);
    digitalWrite(30, LOW);
    }
    analogWrite(4, speed);
  }
  else if(MotorID == 2)
  {
    if(CW){
    digitalWrite(32, HIGH);
    digitalWrite(33, LOW);
    }
    else{
    digitalWrite(33, HIGH);
    digitalWrite(32, LOW);
    }
        analogWrite(5, speed);

  }
    else if(MotorID == 3)
  {
        if(CW){
    digitalWrite(34, HIGH);
    digitalWrite(35, LOW);
    }
    else{
    digitalWrite(35, HIGH);
    digitalWrite(34, LOW);
    }
      analogWrite(6, speed);
  }
    else if(MotorID == 4)
  {
            if(CW){
    digitalWrite(36, HIGH);
    digitalWrite(37, LOW);
    }
    else{
    digitalWrite(37, HIGH);
    digitalWrite(36, LOW);
    }
      analogWrite(7, speed);
  }
    else if(MotorID == 5)
  {
            if(CW){
    digitalWrite(38, HIGH);
    digitalWrite(39, LOW);
    }
    else{
    digitalWrite(38, HIGH);
    digitalWrite(39, LOW);
    }
      analogWrite(8, speed);
  }
  else
  {
    outputAndErrors(1, "error invalid motor id");
  }
        NOTLIVE = true;

}

void emergencyShutdownFullstop()
{
      digitalWrite(30, LOW);
      digitalWrite(31, LOW);
      digitalWrite(32, LOW);
      digitalWrite(33, LOW);
      digitalWrite(34, LOW);
      digitalWrite(35, LOW);
      digitalWrite(36, LOW);
      digitalWrite(37, LOW);
      digitalWrite(38, LOW);
      digitalWrite(39, LOW);
      analogWrite(4, 0);
      analogWrite(5, 0);
      analogWrite(6, 0);
      analogWrite(7, 0);
      analogWrite(8, 0);
      FULLSTOP = true;

}
void outputAndErrors(int ID, String Text)
{
  //error codes
  if(ID == 0)
  {
    Serial.write("general error");
  }
  else if(ID == 1)
  {
    Serial.write("Invalid motor ID");
    emergencyShutdownFullstop();
  }
  else if(ID == 2)
  {
    Serial.write("Invalid speed val");
    emergencyShutdownFullstop();
  }
  else if(ID == 3)
  {
    Serial.write("Invalid rotation value");
    emergencyShutdownFullstop();
  }
}