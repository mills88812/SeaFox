String input;
const char Motor =  "M";
void setup() {
  Serial.begin(9600);
pinMode(LED_BUILTIN, OUTPUT);
pinMode(22, OUTPUT);
pinMode(23, OUTPUT);
pinMode(24, OUTPUT);

}

void loop() {
    
}
void ReadSerial()
{
  if(Serial.available())
  {
    input += Serial.read();
    if(Serial.read() == "]")
    {
      command(input);
    }
  }
}

void command(String Output)
{
      input = "";
      if(Output.charAt(0) == "[", Output.length() >= 10)
      {
        if(Output.charAt(1) == "M")
        {
          int speed;
          bool CW;
          in MotorID;
        }
        else if(Output.charAt(1) != "M")
        {

        }
      }
      else {
          outputAndErrors(0, "null generic error");
      }
} 

void MotoControl(int MotorID, int speed, bool CW)
{
  

}
      
      

void outputAndErrors(int ID, String Text)
{
  if(ID = 0)
  {
    Serial.write("general error");
  }
}