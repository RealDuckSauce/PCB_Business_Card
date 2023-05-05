# PCB Business Card Particle Simulation

This is a personal project, creating a coin-cell powered PCB business card with a simple particle simulation.

## Design
The design utilises an 8x8 square led matrix, run by the HT16K33 LED driver. 

The pitch and roll of the card are determined by an ADXL335 accelerometer. 

All is controlled by an Atemga328p.

The scope of the stimulation includes just one particle in 2D space; for simplicity.

## Assembly

## Programming

Ensure you have the Arduino IDE with the following libraries installed:

- Adafruit GFX
- Adafruit LED Backpack

The PCB cannot be programmed without an ISP programmer, as there is no serial interface on board.

- Connect an ISP programmer to the ISP header
- Flash the Atmega328p
 

## Tuning the Behaviour of the Simulation

``` arduino
void setup() {
  
  Serial.begin(9600);
  Serial.println("Starting.. 8x8 Sim");
  
  matrix.begin(0x70);  // pass in the address
}
```

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.