/*****************************************************************************
 *
 * Program for writing to Newhaven Display's 2x16 Character COG with the ST7032 Controller.
 * This code is written for the Arduino Uno R3 using Serial Interface
 *
 * Newhaven Display invests time and resources providing this open source code,
 * Please support Newhaven Display by purchasing products from Newhaven Display!
 *
 * Copyright (c) 2018, Newhaven Display International
 *
 * This code is provided as an example only and is not guaranteed by Newhaven Display.
 * Newhaven Display accepts no responsibility for any issues resulting from its use.
 * The developer of the final application incorporating any parts of this
 * sample code is responsible for ensuring its safe and correct operation
 * and for any consequences resulting from its use.
 *
 *****************************************************************************/

unsigned char text1[] = {"NEWHAVEN Display"};
unsigned char text2[] = {"2x16 COG Module "};

#define SI 8
#define SCL 9
#define CS 10
#define RS 11
#define RST 12

/**
 * @brief Send a data byte to the display.
 * 
 * @param d Data byte to send to display.
 * @return none
 */
void data(unsigned char d)
{
  digitalWrite(CS, LOW);
  for (int i = 0; i < 8; i++)
  {
    if ((d & 0x80) == 0x80) // Send MSB first
      digitalWrite(SI, HIGH);
    else
      digitalWrite(SI, LOW);
    d = (d << 1);
    digitalWrite(SCL, LOW);
    digitalWrite(SCL, HIGH);
    digitalWrite(SCL, LOW);
  }
  digitalWrite(CS, HIGH);
}

/**
 * @brief Send a command byte to the display.
 * 
 * @param c Command byte to send to display.
 * @return none
 */
void command(unsigned char c)
{
  digitalWrite(CS, LOW);
  digitalWrite(RS, LOW);
  for (int i = 0; i < 8; i++)
  {
    if ((c & 0x80) == 0x80) // Send MSB first
      digitalWrite(SI, HIGH);
    else
      digitalWrite(SI, LOW);
    c = (c << 1);
    digitalWrite(SCL, LOW);
    digitalWrite(SCL, HIGH);
    digitalWrite(SCL, LOW);
  }
  digitalWrite(CS, HIGH);
  digitalWrite(RS, HIGH);
}

/**
 * @brief Initalize the connected NHD-C0216CZ display.
 * 
 * @return none
 */
void init1()
{
  digitalWrite(RST, LOW); // RST = 0; //RESET
  delay(2);
  digitalWrite(RST, HIGH); // RST = 1; //end reset
  delay(20);
  command(0x30); // wake up
  delay(2);
  command(0x30); // wake up
  command(0x30); // wake up
  command(0x39); // function set
  command(0x14); // internal osc frequency
  command(0x56); // power control
  command(0x6D); // follower control

  command(0x70); // contrast
  command(0x0C); // display on
  command(0x06); // entry mode
  command(0x01); // clear
  delay(10);
}

/**
 * @brief Write customer character data to CGRAM.
 * 
 * @return none
 */
void cgram()
{
  command(0x38); // set CGRAM address
  command(0x40); // set DDRAM address

  data(0x00); // 1st
  data(0xFF);
  data(0x00);
  data(0x00);
  data(0x00);
  data(0x00);
  data(0x00);
  data(0x00);
  data(0x00);

  data(0x00); // 2nd
  data(0xFF);
  data(0x00);
  data(0x00);
  data(0x00);
  data(0x00);
  data(0x00);
  data(0x00);

  data(0x00); // 3th
  data(0x00);
  data(0xFF);
  data(0x00);
  data(0x00);
  data(0x00);
  data(0x00);
  data(0x00);

  data(0x00); // 4th
  data(0x00);
  data(0x00);
  data(0xFF);
  data(0x00);
  data(0x00);
  data(0x00);
  data(0x00);

  data(0x00); // 5th
  data(0x00);
  data(0x00);
  data(0x00);
  data(0xFF);
  data(0x00);
  data(0x00);
  data(0x00);

  data(0x00); // 6th
  data(0x00);
  data(0x00);
  data(0x00);
  data(0x00);
  data(0xFF);
  data(0x00);
  data(0x00);

  data(0x00); // 7th
  data(0x00);
  data(0x00);
  data(0x00);
  data(0x00);
  data(0x00);
  data(0xFF);
  data(0x00);

  data(0xFF); // 8th
  data(0x00);
  data(0xFF);
  data(0x00);
  data(0xFF);
  data(0x00);
  data(0x00);
  data(0x00);

  command(0x38); // set CGRAM address
}

/**
 * @brief Print "NEWHAVEN Display 2x16 COG Module" to
 * the screen.
 * 
 * @return none
 */
void disp1()
{
  int a;
  command(0x80);
  for (a = 0; a < 16; a++)
  {
    data(text1[a]);
  }
  command(0xC0);
  for (a = 0; a < 16; a++)
  {
    data(text2[a]);
  }
}

void setup()
{
  DDRB = 0xFF; // PortB = Control + Data Lines
  init1();
  delay(50);
  disp1();
  delay(50);
  cgram();
  delay(1000);
}

void loop()
{
  command(0x01);
  delay(2);
  command(0x02);
  delay(5);

  // Following code to display custom character
  data(0x00);
  data(0x01);
  data(0x02);
  data(0x03);
  data(0x04);
  data(0x05);
  data(0x06);
  data(0x07);
  // End of code to display custom character

  while (1);
}
