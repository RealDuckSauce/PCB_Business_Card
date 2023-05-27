// PCB Business Card Program ver. 3.4.
// Will Vestergaard
// https://github.com/WILL-VESTERGAARD
// willvestergaard@gmail.com
// Prepared: 27.05.2023
//
// Preface:
// Hello, thank you taking the time to download this code, even if just for a look.
// While I have annotated some of this code, it is far from perfect. This is a largely 
// personal project, but encourage you to use any of this to aid you own similar 
// project(s). Feel free to reach out if you have any questions.
// Thanks again!
// Will.

//Required libraries
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

//Declare the size of the simulation bounds, also the dimensions of the matrix.
const float xBound = 7; //incl zero, 8 across
const float yBound = 7; //incl zero, 8 down

float accXPin = A2; //ADXL335 Accelerometer pins
float accYPin = A1;

float rawX = 0; // Raw data from the adc 
float rawY = 0;

float sX = 0; //Chnge in position after each iteration. s in SUVATS
float sY = 0;

float pX = 4; //The current position, this declaration doubles as the initial position of the pixel
float pY = 4;

int cX = 0; //The coordinates of the pixel, as interpreted by the matrix
int cY = 0;

float uX = 0; //Inital velocity at the start of each iteration, equal to the calculated velocity at the end of each iteration. u in SUVATS
float uY = 0;

float vX = 0; //Velocity of particle. v in SUVATS
float vY = 0;

float aX = 0; //Acceleration inn each axis, calculated from the product of the accelerometer value and the acceleration multiplier.
float aY = 0;


//Simulation Modifiers
const float aMult = 230; //Acceleration multiplier

const float elast = 0.7; //Elastcity of ball. Between 0-1. For % of velocity lost when colliding with wall.

const float t = 0.01; //Time taken to complete one simulation iteration (seconds) t used with SUVAT equation(s) - this is a poor estimate and can remain relatively constant.


Adafruit_8x8matrix matrix = Adafruit_8x8matrix();



void setup() {
  
  analogReference(EXTERNAL);
  
  Serial.begin(9600);
  Serial.println("Starting.. 8x8 Sim");
  
  matrix.begin(0x70);  // pass in the address
  
}


 //the main simulation loop
void loop()
{
  
  rawX = analogRead(accXPin); //read the acceleometer value(s)
  rawY = analogRead(accYPin); //read the acceleometer value(s)

  aX = calX + map(rawX, 0, 1023, -40, 40); //Map the raw acceleromter values
  aX = aX*aMult;
  aY = calY + map(rawY, 0, 1023, 40, -40);
  aY = aY*aMult;

  vX = uX+aX*t;
  vY = uY+aY*t;
  
  sX = (uX*t)+(0.5*aX*sq(t)); //find the displacement
  sY = (uY*t)+(0.5*aY*sq(t));


  pX = pX+sX;
  pY = pY+sY;



  //stop the particle from slipping away
  if (pX >= xBound)
    {
      vX = vX*-1*elast;
      pX = xBound-0.05;
    }
  if (pX <= 0)
    {
      vX = vX*-1*elast;
      pX = 0.05;
    }

  if (pY >= yBound)
    {
      vY = vY*-1*elast;
      pY = yBound-0.05;
    }
  if (pY <= 0)
    {
      vY = vY*-1*elast;
      pY = 0.05;
    }
  
  uX = vX;// update the initial velocity for the next iteration
  uY = vY;
  
  cX = round(pX);
  cY = round(pY);

  matrix.clear();      // clear display
  matrix.drawPixel(cX, cY, LED_ON);  
  matrix.writeDisplay();  // write the changes we just made to the display  
}

// ;)
