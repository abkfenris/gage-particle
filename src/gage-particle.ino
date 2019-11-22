/*
 * Project gage-particle
 * Description: 
 * Author: Alex Kerney (abk@mac.com)
 * Date: 2019-03-06
 */

void setup()
{
  Serial1.begin(9600);
  Serial.begin(9600);

  Serial.println("Setup");

  delay(1000);
}

char buf[5];
int value;

void loop()
{
  Serial.println("Reading data from sensor");

  while (Serial1.available())
  {
    // Serial.println("Reading a byte");
    if (Serial1.peek() == 'R')
    {
      // Serial.println("New reading");
      Serial1.read(); // pop the R off
      for (int i = 0; i < 4; i++)
      {
        char data = Serial1.read();
        buf[i] = data;
        // Serial.write(data);
      }
      Serial.print("From buf: ");
      Serial.write(buf);
      value = atoi(buf);
      Serial.print(", from value: ");
      Serial.print(value);
      Serial.println("");
    }
    else
    {
      Serial1.read();
    }
    // char data = Serial1.read();
    // Serial.print("Data: ");
    // Serial.write(data);
    // Serial.println("");

    // int avaliable = Serial1.avaliable();

    // if (avaliable > 0)
    // {
    //   Serial.print("Data avaliable from sensor: ");
    //   Serial.write(avaliable);
    //   Serial.println("");
    // }

    // if (Serial1.peek() == 'R')
    // {
    //   if (Serial1.avaliable() >= 5)
    //   {
    //     Serial1.readBytes(buf, 6);
    //     // Serial.write(buf);
    //   }
    //   else
    //   {
    //     Serial1.read();
    //   }
    // }
  }

  Serial.println("---");
  delay(3000);
}