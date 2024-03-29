/*==============================================================================
 Project: Intro-3-Loops                 Activity: mirobo.tech/intro-3
 Date:    December 11, 2023
 
 This introductory programming activity for the mirobo.tech CHRP4 and UBMP4
 demonstrates the use of both while-loop and for-loop structures to change
 the brightness of an LED using PWM (Pulse-Width Modulation).
 
 Additional program analysis and programming activities reinforce the concepts
 of limits using conditional statements, challenge the learner's understanding
 of variables, program structure and flow, and explore nested loops to create
 different pitches of tones and audio frequency sweeps.
==============================================================================*/

#include    "xc.h"              // Microchip XC8 compiler include file
#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions

#include    "CHRP4.h"           // Include CHRP4 constants and functions

// TODO Set linker ROM ranges to 'default,-0-7FF' under "Memory model" pull-down.
// TODO Set linker code offset to '800' under "Additional options" pull-down.

// Program variable definitions
unsigned char pwmLED4 = 127;    // LED3 brightness (PWM on-time) value
unsigned char pwmPeriod;        // Counter for PWM generation loop
unsigned int period = 460;      // Sound period for program analysis activities

int main(void)
{
    OSC_config();               // Configure internal oscillator for 48 MHz
    CHRP4_config();             // Configure I/O for on-board CHRP4 devices
	
    while(1)
	{
        // Decrease brightness
        if(SW3 == 0)
        {
            pwmLED4 -= 1;
        }

        // Increase brightness
        if(SW4 == 0)
        {
            pwmLED4 += 1;
        }
        
        // PWM LED4 brightness
        pwmPeriod = 255;
        while(pwmPeriod != 0)
        {
            if(pwmLED4 == pwmPeriod)
            {
                LED4 = 1;
            }
            pwmPeriod --;
            __delay_us(20);
        }
        LED4 = 0;
        
        // Reset the microcontroller and start the bootloader if SW1 is pressed.
        if(SW1 == 0)
        {
            RESET();
        }
    }
}

/* Learn More -- Program Analysis Activities
 * 
 * 1.   The main part of the program contains the 'outer' while(1) loop. In C,
 *      brackets in a while or if structure usually contain a conditional
 *      statement, but these brackets just contain '1'. What condition does '1'
 *      represent? (Hint: Think about Boolean variables introduced in the
 *      'Intro-2-Variables activity.) How many times will this outer while loop
 *      run with '1' as its condition. Why?
 * 
 * 2.   There is a second, 'inner' while loop inside the main loop, beginning
 *      with the conditional while statement: while(pwmPeriod != 0)
 * 
 *      What condition is being evaluated inside this while statement's
 *      brackets? How many times will the contents of this inner loop run?
 * 
 * 3.   What condition is being evaluated by the 'if' statement inside the PWM
 *      loop? What happens when this if condition is true?
 * 
 * 4.   Pressing the up or down buttons (SW4 and SW3) will increase or decrease
 *      the brightness of LED D4 using PWM (Pulse-Width Modulation). How many 
 *      different brightnesses can the LED have? Try to figure out the
 *      percentage brightness change that corresponds to a one-number change in
 *      the value of the pwmLED4 variable.
 * 
 * 5.   A while loop needs three statements to perform its function:
 * 
 *      First, an assignment statement is used to set a starting condition. In
 *      this program, 'pwmPeriod = 255;' sets the pwmPeriod variable to its
 *      starting value of 255.
 * 
 *      Next, a condition statement determines whether or not the contents of
 *      the loop will repeat. The 'while(pwmPeriod != 0)' structure keeps 
 *      running the loop until pwmPeriod is equal to 0. Unlike an if statement,
 *      which runs the code inside its braces only once, a while statement keeps
 *      running the code inside its braces until its condition is false.
 * 
 *      Finally, some sort of expression is needed to modify the variable that
 *      will be checked by the condition. Without this, the loop will never end 
 *      (the program will appear to get stuck in the loop and never go any 
 *      further -- this is known as an infinite loop). The statement 
 *      'pwmPeriod --;' modifies the loop variable in this program, counting
 *      pwmPeriod down until it reaches 0.
 *
 *      A 'for' loop is an alternative to the while loop and incorporates the
 *      assignment of a loop variable, the loop conditional check, and variable
 *      modification into a single statement as shown in the example code below.
 *      Compare the structure of the 'while' loop in the program with the 'for'
 *      loop, below. What is an advantage of using a 'for' loop instead of a
 *      'while' loop? 
 *    
 *      Replace the entire while structure in the program with this 'for' loop:

        // PWM LED4 brightness
        for(unsigned char pwmPeriod = 255; pwmPeriod != 0; pwmPeriod --)
        {
            if(pwmLED4 == pwmPeriod)
            {
                LED4 = 1;
            }
            __delay_us(20);
        }
        LED4 = 0;
        
 *      Compile the program, download it into your circuit, and try it out. Does
 *      it work the same way as the program using the while loop did?
 * 
 * 6.   The 'for' loop, above, *redefines* the pwmPeriod variable in the 
 *      initialization statement: 'for(unsigned char pwmPeriod = 255; ...'
 * 
 *      Even though they share the same name, this instance of the PWMperiod
 *      variable will be 'local' to the for loop. It won't be accessible outside
 *      of the loop, nor will it alter the value of the existing pwmPeriod
 *      variable. For these reasons, it's a very bad idea to re-use variable
 *      names inside loops due to the confusion of having two variables with the
 *      same name, but different values. (It's only being done here to prove a 
 *      point!)
 * 
 *      Is this really the case? Let's prove that the global pwmPeriod variable
 *      (the one defined in the program outside of the for loop) is not affected
 *      by the local pwmPeriod variable inside the for loop. Add this line to
 *      your program above the for loop:
 
        pwmPeriod = 128;

 *      Next, add the following lines to your program below the for loop:
        
        if(pwmPeriod == 128)
        {
            LED3 = 1;
        }
        else
        {
            LED3 = 0;
        }
        
 *      When the program runs, the pwmPeriod variable inside the for loop will
 *      count down from 255 to 0, and should be 0 when the loop finishes. The 
 *      'if' structure will let us know. Compile and run the program. Is LED D3
 *      lit? If it is, what must the value of the global pwmPeriod variable be?
 * 
 * 7.   Can the global pwmPeriod variable definition at the top of now be 
 *      removed since the pwmPeriod variable is being defined in the for loop?
 *      Try it and see. Comment out the pwmPeriod variable declaration at the
 *      top of the program. If the program compiles and runs without error, the
 *      global pwmPeriod variable is no longer necessary. Unfortunately, this
 *      means that some variables will be defined at the top of the code, while
 *      other variables will be defined in the code ? potentially making it more
 *      difficult to track variables and understand a program.
 * 
 *      Instead of defining a new pwmPeriod variable local to the loop, the
 *      global pwmPeriod variable can be used in the loop. Un-comment the
 *      pwmPeriod variable definition at the top of the program, and then
 *      replace the 'for' declaration statement with the one below:
 
        for(pwmPeriod = 255; pwmPeriod != 0; pwmPeriod --)

 *      By removing the 'unsigned char' descriptors before the pwmPeriod = 255;
 *      variable assignment, the pwmPeriod variable used by the loop will be the
 *      global variable defined at the top of the program. Try it out. Does LED
 *      D3 still show pwmPeriod as having the value 128? What would happen if
 *      you tried to comment out the pwmPeriod variable declaration now?
 * 
 * 8.   Add the code below the PWM loop to generate a tone. (Comment out the 
 *      PWM loop for a better sound.)
                
        // Change pitch
        if(SW2 == 0)
        {
            period -= 1;
        }
        
        if(SW5 == 0)
        {
            period += 1;
        }
        
        // Make a tone
        for(unsigned char cycles = 50; cycles != 0; cycles--)
        {
            BEEPER = !BEEPER;
            for(unsigned int p = period; p != 0; p--);
        }

 *      This code makes tones by using two nested for loops. The outer loop
 *      (using the cycles variable) causes the BEEPER pin to toggle once before
 *      the inner loop runs. The inner loop (using the period variable) is an
 *      empty loop, shown by its trailing semicolon ';'. Empty loops contain
 *      no curly braces or code to run, but add a short delay to the program
 *      simply by having to count down a loop variable. The more loops it takes
 *      to count the variable down, the more instruction cycles it will take the
 *      microcontroller to decrement the loop counter variable to zero,
 *      increasing the time delay until outer loop ends.
 * 
 *      What numeric type is the period variable? How large a number can this
 *      period variable hold?
 * 
 * 9.   Why is the value of the period variable copied to the local variable p
 *      by the inner for loop's initiation statement? What would happen if the
 *      actual period variable was decremented instead? (Hint: practice thinking
 *      like a computer and try to follow the instructions step-by-step.)
 * 
 * Programming Activities
 * 
 * 1.   Pressing and holding SW3 or SW4 causes the brightness of LED D4 to
 *      repeatedly cycle through its entire brightness range because the pwmLED4
 *      variable is allowed to either overflow (increase above 255), or
 *      underflow (decrease below 0).
 * 
 *      Add conditional code to modify your program code to prevent overflow
 *      or underflow. That is, pressing and holding SW3 should dim the LED until
 *      t is off and keep if off, and pressing and holding SW4 should brighten
 *      the LED until it reaches its maximum brightness, and maintain that
 *      brightness without cycling through the range again.
 * 
 * 2.   Modify your program to control the brightness of two different LEDs
 *      simultaneously. Add statements to control LED D2 using SW2 and SW5 while
 *      continuing to use SW3 and SW4 to control LED D4.
 * 
 *      Hint: To ensure each LED can reach its maximum brightness -- or 100% PWM
 *      on-time -- you'll have to perform the PWM functions for both LEDs within
 *      the same loop. You can view the resulting PWM wave if you have access to
 *      an oscilloscope. If not, you can ensure your LEDs reach full brightness
 *      by lighting LED3 and LED5 at the start of your program and comparing
 *      their brightness to LED D2 and LED D4. If your PWM functions are working
 *      properly, their brightnesses will match.
 * 
 * 3.   Rather than having lights suddenly turn on at full brightness (or motors
 *      turn on at full power), create a program that uses a for loop and the 
 *      PWM code to make a 'soft-start' to slowly increases the PWM value when
 *      a button is pressed. Can you also make it turn off in a similar way?
 * 
 * 4.   Make a program that creates a repeated, visual 'pulse', by continuously
 *      brightening and dimming one or more LEDs.
 * 
 * 5.   Make a 'chirp' or 'pew-pew' sound effect by sweeping through a range of
 *      frequencies from low to high, or high to low in response to a button
 *      press.
 */
