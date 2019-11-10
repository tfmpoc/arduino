/////////////
// 10/28/2019
//
// Simple and quick driver for my Halloween snakehead.
/////////////

// Let's blink status when we change modes
int status = 1;

/*******************Setup Loop***************************/
void setup() {                
  // The EL channels are on pins 2 through 9 on the ATMega328
  // Initialize the pins as outputs
  pinMode(2, OUTPUT);  // channel A  
  pinMode(3, OUTPUT);  // channel B - capable of analogWrite()
  pinMode(4, OUTPUT);  // channel C
  pinMode(5, OUTPUT);  // channel D - capable of analogWrite() 
  pinMode(6, OUTPUT);  // channel E - capable of analogWrite()
  pinMode(7, OUTPUT);  // channel F
  pinMode(8, OUTPUT);  // channel G
  pinMode(9, OUTPUT);  // channel H - capable of analogWrite()

//Pin 13 is the status LED on both the EL Sequencer and Arduino for use with the EL Escudo Dos. 
   pinMode(13, OUTPUT);   

   randomSeed(analogRead(0)); // Nothing on A0 so it should be noise

   Serial.begin(9600);
}

void loop() 
{
  switch (random(6))
  {
    case 0:
      all_on();
      break;
    case 1:
      iterate();
      break;
    case 2:
      iterate_down();
      break;
    case 3:
      brighten();
      break;
    case 4:
      dim();
      break;
    case 5:
      all_off();
      break;
  }
}

void all_on()
{
  Serial.println("all_on()");
  digitalWrite(13, status);
  status = !status; 

  for (int x=2; x<=9; x++)
  {
    digitalWrite(x, HIGH);    // turn the EL channel on
  }

  delay(10 * 1000); // delay for 10 seconds
}

void all_off()
{
  Serial.println("all_off()");
  digitalWrite(13, status);
  status = !status; 
  
  for (int x=2; x<=9; x++)
  {
    digitalWrite(x, LOW);    // turn the EL channel off
  }

  delay(5 * 1000); // delay for 10 seconds
}

void iterate()
{
  Serial.println("iterate()");
  digitalWrite(13, status);
  status = !status; 

  for (int i= 0; i < 10; ++i)
  {
    for (int x=2; x<=9; x++)
    {
      digitalWrite(x, HIGH);    // turn the EL channel on
      delay(100);              // wait for 1/10 second
      digitalWrite(x, LOW);    // turn the EL channel off
    }
  }
}

void iterate_down()
{
  Serial.println("iterate()");
  digitalWrite(13, status);
  status = !status; 

  for (int i= 0; i < 10; ++i)
  {
    for (int x=9; x>=2; x--)
    {
      digitalWrite(x, HIGH);    // turn the EL channel on
      delay(100);              // wait for 1/10 second
      digitalWrite(x, LOW);    // turn the EL channel off
    }
  }
}

// will only brighten pins capable of analog. See comments above.
// undefined effect on the other pins.
void brighten()
{
  Serial.println("brighten()");
  digitalWrite(13, status);
  status = !status; 
  
  for (int bright = 0; bright < 256; ++bright)
  {
    for (int x=2; x<=9; x++)
    {
      analogWrite(x, bright);   // turn the EL channel on
      delay(10);
    }
  }
  delay(1000);
}

// will only dim pins capable of analog. See comments above.
// undefined effect on the other pins.
void dim()
{
  Serial.println("dim()");
  digitalWrite(13, status);
  status = !status; 

  for (int bright = 255; bright >= 0; --bright)
  { 
    for (int x=2; x<=9; x++)
    {
      analogWrite(x, bright);   // turn the EL channel on
      delay(10);
    }
  }
  delay(1000);
}
