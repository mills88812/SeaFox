
const char Motor =  "M";
bool NOTLIVE = true;
int motor2pin1 = 30;
int  motor2pin2 = 31;
//speaker = up/down
// orange = bottom left
//brown = bottom right
//green = top right
//blue = top left
void setup() {
Serial.begin(9600);
//pwm pins
  //top left
   // pinMode(4, OUTPUT);
//motor groupe
  //top left
    pinMode(30, OUTPUT);
    pinMode(31, OUTPUT);
        pinMode(4, OUTPUT);

    //debug
      pinMode(LED_BUILTIN, OUTPUT);
      Serial.println("registered");
}

void loop() {
    ReadSerial();
      // Serial.write("waiting \r\n");
 // digitalWrite(motor2pin1, HIGH);
 // digitalWrite(motor2pin2, LOW);
  //analogWrite(4, 255); //ENA pin
  //digitalWrite(LED_BUILTIN, HIGH);
    //    Serial.println("cw");


   // analogWrite(4, 255);
   // delay(30000);
  //              digitalWrite(motor2pin1, LOW);
   // digitalWrite(motor2pin2, HIGH);
   //   digitalWrite(LED_BUILTIN, LOW);
        //    Serial.println("ccw");


}
void ReadSerial()
{//&& NOTLIVE
                 digitalWrite(LED_BUILTIN, HIGH);
 
String input;
  if(Serial.available() )
  {

    


    input = Serial.readString();
    command(input); 
  }
}

void command(String Output)
{
          int speed;
          bool CW;
          char MotorID = Output.charAt(3);
          Serial.println(MotorID);
               //   Serial.print(MotorID);

      //input = "";
      //, Output.length() >= 10
    //  Serial.print(Output.charAt(0));



       
        //  Serial.print("Read M");


          if(Output.charAt(5) == '1')
          {
            CW = true;

            
          }
          else{
            CW = false;
                  //      digitalWrite(LED_BUILTIN, HIGH);

          }
          // speed is char 7, 8 ,9
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
        Serial.println(speed);
         // speed = 200;
          MotorControl(MotorID, speed, CW);
         //+ MotorID
    //           Serial.print("finished 2 with: speed: " + speed);
    //   Serial.println("finished 3 with: CW/CRW: " + CW );


  //      Serial.print("finished 1 \r\n");


      
      NOTLIVE = true;
      
} 

void MotorControl(int MotorID, int speed, bool CW)
{
                  digitalWrite(LED_BUILTIN, LOW);
//delay(20);
  //motor on/direction
 // if(MotorID == 1)
  //{
    if(CW){
    digitalWrite(motor2pin2, HIGH);
    digitalWrite(motor2pin1, LOW);
    }
    else{
    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);
    }
    if(speed == 0)
    {
          digitalWrite(motor2pin2, LOW);
    digitalWrite(motor2pin1, LOW);
    }
    analogWrite(4, speed);
  //}
    //      Serial.print("running motor \r\n");

}
      
      

void SpeedControl(int Pin, int speed)
{
  if(speed > 0)
  {
    analogWrite(Pin, speed);
  }
}


void outputAndErrors(int ID, String Text)
{
  if(ID == 0)
  {
    //Serial.write("general error");
  }
}