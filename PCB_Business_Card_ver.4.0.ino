// PCB Business Card Program ver. 4.0.
// Will Vestergaard
// https://github.com/WILL-VESTERGAARD
// willvestergaard@gmail.com
// Prepared: 03/06/2024
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

float sX[6] = {0}; //Chnge in position after each iteration. s in SUVATS
float sY[6] = {0};

float pX[6] = {3, 6, 1, 2, 4, 5}; //The current position, this declaration doubles as the initial position of the pixel
float pY[6] = {4, 3, 5, 2, 6, 1};

int cX[6] = {0}; //The coordinates of the pixel, as interpreted by the matrix
int cY[6] = {0};

float uX[6] = {0}; //Inital velocity at the start of each iteration, equal to the calculated velocity at the end of each iteration. u in SUVATS
float uY[6] = {0};

float vX[6] = {0}; //Velocity of particle. v in SUVATS
float vY[6] = {0};

float aX = 0; //Acceleration inn each axis, calculated from the product of the accelerometer value and the acceleration multiplier.
float aY = 0;


//Simulation Modifiers
const float aMult = 200; //Acceleration multiplier

const float elast[6] = {0.60, 0.62, 0.64, 0.66, 0.68, 0.70}; //Elastcity of each ball. Between 0-1. For % of velocity lost when colliding with wall.

const float t = 0.01; //Time taken to complete one simulation iteration (seconds) t used with SUVAT equation(s) - this is a poor estimate and can remain relatively constant.


Adafruit_8x8matrix matrix = Adafruit_8x8matrix();


void setup() {
  analogReference(EXTERNAL);  
  matrix.begin(0x70);  // pass in the address

  // Display each pixel one by one every 100ms
  for (int i = 0; i < 6; i++) {
    matrix.drawPixel(pX[i], pY[i], LED_ON);
    matrix.writeDisplay();
    delay(3);
  }
}


 //the main simulation loop
void loop()
{
  // Clear the display before updating particle positions
  matrix.clear();

  rawX = analogRead(accXPin); //read the acceleometer value(s)
  rawY = analogRead(accYPin); //read the acceleometer value(s)

  aX = map(rawX, 0, 1023, -50, 50); //Map the raw acceleromter values
  aX = aX*aMult;
  aY = map(rawY, 0, 1023, 50, -50);
  aY = aY*aMult;

  for (int i = 0; i < 6; i++) {
    vX[i] = uX[i]+aX*t;
    vY[i] = uY[i]+aY*t;
    
    sX[i] = (uX[i]*t)+(0.5*aX*sq(t)); //find the displacement
    sY[i] = (uY[i]*t)+(0.5*aY*sq(t));
  
    pX[i] += sX[i];
    pY[i] += sY[i];
  
    //stop the particle from slipping away
    if (pX[i] >= xBound)
      {
        vX[i] = vX[i]*-1*elast[i];
        pX[i] = xBound-0.05;
      }
    if (pX[i] <= 0)
      {
        vX[i] = vX[i]*-1*elast[i];
        pX[i] = 0.05;
      }
  
    if (pY[i] >= yBound)
      {
        vY[i] = vY[i]*-1*elast[i];
        pY[i] = yBound-0.05;
      }
    if (pY[i] <= 0)
      {
        vY[i] = vY[i]*-1*elast[i];
        pY[i] = 0.05;
      }
    
    uX[i] = vX[i];// update the initial velocity for the next iteration
    uY[i] = vY[i];
    
    cX[i] = round(pX[i]);
    cY[i] = round(pY[i]);

    matrix.drawPixel(cX[i], cY[i], LED_ON);
  }

  matrix.writeDisplay();  // write the changes we just made to the display  
}
