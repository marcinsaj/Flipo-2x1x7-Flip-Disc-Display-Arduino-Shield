/*----------------------------------------------------------------------------------*
 * #1 Example Arduino shield test code for one 1x7 flip-disc display                *
 *                                                                                  *
 * Marcin Saj 12 Feb 2023                                                           *
 * https://www.Flipo.io                                                             *
 *                                                                                  *
 * Arduino shield project website:                                          *
 * 1x7 flip-disc display project website: https://bit.ly/1x7-FD                     * 
 *----------------------------------------------------------------------------------*/

#include <FlipDisc.h>   // https://github.com/marcinsaj/FlipDisc 

// Pin declaration for Arduino Shield for 2 x 1x7 flip-disc displays
#define EN_PIN  10      // Start & End SPI transfer data
#define CH_PIN  A0      // Charging PSPS module - turn ON/OFF
#define PL_PIN  A1      // Release the current pulse - turn ON/OFF

void setup() 
{
  /* Flip.Pin(); it is the most important function and first to call before everything else. 
  The function is used to declare pin functions. Before starting the device, double check 
  that the declarations and connection are correct. If the connection of the control outputs 
  is incorrect, the display may be physically damaged. */
  Flip.Pin(EN_PIN, CH_PIN, PL_PIN);
  
  /* Flip.Init(display1, display2, ... display8) it is the second most important function. 
  Initialization function for a series of displays. Up to 8 displays can be connected in series 
  in any configuration. The function also prepares SPI. Correct initialization requires 
  code names of the serially connected displays:
  - D7SEG - 7-segment display
  - D2X1 - 2x1 display
  - D3X1 - 3x1 display
  - D1X3 - 1x3 display
  - D1X7 - 1x7 display */
  Flip.Init(D1X7);
  delay(3000);
}

void loop() 
{
  /* The function is used to turn off (clear)display */
  Flip.Clear();
  delay(1000);
  
  /* The function is used to turn on (set) all discs */
  Flip.All();
  delay(1000);

  Flip.Clear();
  delay(1000);

  /* The function allows you to control up to seven discs of the selected display. 
  Flip.Display_1x7(module_number, disc1,disc2,disc3,disc4,disc5,disc6,disc7);
  - module_number - relative number of the D1X7 display - in this case there is only one display
  - disc1, disc2, disc3, disc4, disc5, disc6, disc7 - counting from left to right 1-7 */
  
  /* Set first and second disc */
  Flip.Display_1x7(1,1,1);
  delay(2000);

  Flip.Clear();
  delay(1000);

  /* Reset 4th and 5th disc, set rest of discs */
  Flip.Display_1x7(1,1,1,1,0,0,1,1);
  delay(2000);

  Flip.All();
  delay(1000);

  /* Function allows you to control a selected disc in a selected D1X7 display.
  You can control only one disc of the selected display at a time.
  Flip.Disc_1x7(module_number, disc_number, disc_status);
  The first argument module_number is the relative number of the display 
  in the series of all displays - in this case there is only one display
  - module_number - relative number of the D1X7 display
  - disc_number - display disc number counting from left to right 1-7
  - disc_status - reset disc "0" or set disc "1" */
  
  /* Reset the 5th disc */
  Flip.Disc_1x7(1, 5, 0);
  delay(2000);

  /* Reset the 7th disc */
  Flip.Disc_1x7(1, 7, 0);
  delay(2000);
  
  Flip.Clear();
  delay(1000); 

  for (int i = 0; i < 5; i++)
  {
    for(int j = 1; j <= 7; j++)
    {
      Flip.Disc_1x7(1, j, 1);
      delay(200);  
    }
    
    for(int j = 1; j <= 7; j++)
    {
      Flip.Disc_1x7(1, j, 0);
      delay(200);  
    }
  }

  Flip.All();
  delay(3000); 
}
