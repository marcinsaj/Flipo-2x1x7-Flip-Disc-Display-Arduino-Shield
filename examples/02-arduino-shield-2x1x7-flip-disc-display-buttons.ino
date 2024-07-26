/*----------------------------------------------------------------------------------*
 * Arduino Shield for 2 x 1x7 Flip-disc Display - example of button control         *
 *                                                                                  *
 * Project website: https://bit.ly/ARD-2x1x7                                        *
 * Marcin Saj 28 Feb 2023                                                           *
 * https://www.Flipo.io                                                             *
 *                                                                                  *
 * Arduino Nano Every is required                                                   *
 * 1x7 Flip-disc display is required: https://bit.ly/1x7-FD                         *
 *----------------------------------------------------------------------------------*/

#include <FlipDisc.h>   // https://github.com/marcinsaj/FlipDisc
#include <Bounce2.h>    // https://github.com/thomasfredericks/Bounce2

#define NUM_BUTTONS 7            // Number of buttons
#define LONG_PRESS_DURATION 1000 // Define the duration for a long press in milliseconds

const int buttonPins[NUM_BUTTONS] = {9, 8, 7, 6, 5, 4, 3}; // Define the pins for each button 
Bounce buttons[NUM_BUTTONS];     // Create an array of Bounce objects for debouncing

unsigned long pressStartTimes[NUM_BUTTONS] = {0}; // Array to store the start time of each button press
bool longPressActive[NUM_BUTTONS] = {false};      // Array to track if long press has been detected for each button
bool toggleDiscStates[14];                        // Array to store toggle state for each disc

// Pin declaration for Arduino Nano Every and PSPS module
#define EN_PIN  10      // Start & End SPI transfer data
#define CH_PIN  A0      // Charging PSPS module - turn ON/OFF
#define PL_PIN  A1      // Release the current pulse - turn ON/OFF

void setup()
{
  /* The most important function and first to call before everything else.
  Details can be found in the description of the library 
  https://github.com/marcinsaj/FlipDisc */
  Flip.Pin(EN_PIN, CH_PIN, PL_PIN);
 
  /* Initialization function of the displays */
  Flip.Init(D1X7, D1X7);

  Serial.begin(9600);

  for (int i = 0; i < NUM_BUTTONS; i++) {
    pinMode(buttonPins[i], INPUT);    // Set each button pin as input
    buttons[i].attach(buttonPins[i]); // Attach the button pin to the Bounce object
    buttons[i].interval(25);          // Set debounce interval to 25 milliseconds
  }

  for (int i = 0; i < 14; i++) 
  {
    toggleDiscStates[i] = true;       // By default all discs are ON
  }
  
  delay(1000);

  // The function is used to turn off (clear) all displays
  Flip.Clear();
  delay(1000);
 
  // The function is used to turn on (set) all discs of all displays
  Flip.All();
  delay(1000);
}

void loop() 
{
  // Loop through each button
  for (int i = 0; i < NUM_BUTTONS; i++) 
  { 
    buttons[i].update(); // Update the state of the button

    // Check if the button was pressed (went from LOW to HIGH)
    if(buttons[i].rose()) 
    {
      pressStartTimes[i] = millis(); // Record the time when the button was pressed
      longPressActive[i] = false;    // Reset the long press flag for the button
    }

    // Check if the button was released (went from HIGH to LOW)
    if(buttons[i].fell()) 
    {
      if(!longPressActive[i])        // If a long press has not been detected
      {
        toggleDiscStates[i] = !toggleDiscStates[i];

        Serial.print("Button ");     // Print the button number
        Serial.print(7-i);
        Serial.print(": short press. Toggled disc ");
        Serial.print(7-i);
        Serial.println(toggleDiscStates[i] ? ": ON" : ": OFF"); // Print the toggle state

        Flip.Disc_1x7(1, (i+1), toggleDiscStates[i]);
      }
    }

    // Check if the button is being held down longer than LONG_PRESS_DURATION
    if(buttons[i].read() == HIGH && !longPressActive[i])      // If the button is still pressed
    {
      if(millis() - pressStartTimes[i] > LONG_PRESS_DURATION) // If the press duration exceeds LONG_PRESS_DURATION
      {
        toggleDiscStates[i+7] = !toggleDiscStates[i+7];

        longPressActive[i] = true;     // Set the long press flag for the button
        Serial.print("Button ");       // Print the button number
        Serial.print(7-i);
        Serial.print(": long press, Toggled disc ");
        Serial.print(14-i);
        Serial.println(toggleDiscStates[i+7] ? ": ON" : ": OFF"); // Print the toggle state

        Flip.Disc_1x7(2, (i+1), toggleDiscStates[i+7]);
      }
    }
  }
}
