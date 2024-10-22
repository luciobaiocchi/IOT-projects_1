# IOT-projects-assignment1
## Description:
The game board includes 4 green leds L1, L2, L3, L4 and red led LS, four tactile buttons B1, B2, B3, B4 and a potentiometer Pot, and an LCD. This is the suggested  layout:

In the game, leds represent the binary digits of a number (0..15). During the game, the system repeatedly displays a number in decimal notation on the LCD and the player must turn on the proper leds defining the same number in binary notation (L1 is the most significant bit, L4 the less significant bit). So for instance: if the number 13 is displayed on the LCD, the player must turn on the leds L1, L2 and L4. To turn on the leds, the player can use the tactile buttons. Each button Bi turns on the corresponding led Li. Each game involves multiple rounds. At each round, a number (at random) is displayed and the player must compose the binary version, within some maximum time T1.  If the player does it right, a score - starting from zero - is increased and the game goes on, with another round, but  reducing the times T1 of some factor F.  If the player does not compose the correct number on time, the red led Ls is turned on for 1 second and the game ends, displaying the score on the LCD. 

### Link to the video demo: https://youtu.be/CACj1u8vGgM
