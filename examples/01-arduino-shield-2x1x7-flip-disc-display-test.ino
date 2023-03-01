/*----------------------------------------------------------------------------------*
 * Arduino Shield for 2 x 1x7 Flip-disc Display - example of display control        *
 *                                                                                  *
 * Project website: https://bit.ly/ARD-2x1x7                                        *
 * Marcin Saj 28 Feb 2023                                                           *
 * https://www.Flipo.io                                                             *
 *                                                                                  *
 * Arduino Nano Every is required                                                   *
 * 1x7 Flip-disc display is required: https://bit.ly/1x7-FD                         *
 *----------------------------------------------------------------------------------*/

#include <FlipDisc.h>   // https://github.com/marcinsaj/FlipDisc

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
  
  delay(3000);
}

void loop()
{
  /* The function is used to turn off (clear) all displays */
  Flip.Clear();
  delay(1000);
 
  /* The function is used to turn on (set) all discs of all displays */
  Flip.All();
  delay(1000);

  Flip.Clear();
  delay(1000);

  FlipDiscRoutine_1();
  FlipDiscRoutine_2();
  FlipDiscRoutine_3();
  FlipDiscRoutine_4();
  
  Flip.All();
  delay(1000);
}

/* Flip.Disc_1x7 function allows you to control a selected disc in a selected D1X7 display.
 * You can control only one disc of the selected display at a time.
 * Flip.Disc_1x7(module_number, discNumber, discStatus);
 * - module_number - relative number of the D1X7 display
 * - discNumber - display disc number counting from left to right 1-7
 * - discStatus - reset disc "0" or set disc "1" 
 * Details can be found in the description of the library https://github.com/marcinsaj/FlipDisc */

void FlipDiscRoutine_1(void)
{
  for (int i = 0; i < 5; i++)
  {
    for(int j = 1; j <= 7; j++)
    {
      Flip.Disc_1x7(1, j, 1);
      Flip.Disc_1x7(2, (7+1)-j, 1);
      delay(200);  
    }
   
    for(int j = 1; j <= 7; j++)
    {
      Flip.Disc_1x7(1, j, 0);
      Flip.Disc_1x7(2, (7+1)-j, 0);
      delay(200);  
    }
  }
  delay(1000); 
}

void FlipDiscRoutine_2(void)
{
  for(int i = 0; i < 5; i++)
  {
    for(int j = 1; j <=7; j++)
    {
      Flip.Disc_1x7(1, j, 1);
      delay(100);
      Flip.Disc_1x7(2, j, 1);  
      delay(100);
    }
    for(int j = 1; j <=7; j++)
    {
      Flip.Disc_1x7(1, j, 0);
      delay(100);
      Flip.Disc_1x7(2, j, 0);  
      delay(100);
    }
  }  
}

void FlipDiscRoutine_3(void)
{
  for(int i = 0; i < 5; i++)
  {
    for(int j = 1; j <=7; j++)
    {
      Flip.Disc_1x7(1, j, 1);
      Flip.Disc_1x7(2, j, 0);  
    }
   
    delay(1000);
   
    for(int j = 1; j <=7; j++)
    {
      Flip.Disc_1x7(1, j, 0);
      Flip.Disc_1x7(2, j, 1);  
    }

    delay(1000);
  } 
}

void FlipDiscRoutine_4(void)
{
  for(int i = 0; i < 5; i++)
  {
    for(int j = 7; j >= 1; j--)
    {
      Flip.Disc_1x7(1, j, 1);
      Flip.Disc_1x7(2, j, 1);  
      delay(50);
    }
    for(int j = 1; j <=7; j++)
    {
      Flip.Disc_1x7(1, j, 0);
      Flip.Disc_1x7(2, j, 0);  
      delay(50);
    }
  } 
}
