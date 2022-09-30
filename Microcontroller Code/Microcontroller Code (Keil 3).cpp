/* Declaring Libraries */
#include <REG932.H>
#include "scan.h"
#include "lednum2.h"  
#include "count.h"
#include "keyscan.h"
#define BLANK 0
#include <COUNT.h>


// --- external variables
extern bit flg; 
extern unsigned char timerval;

 /* Function checks that two passwords match */
unsigned char pass_compare (unsigned char *pass1, unsigned char *pass2)
{
	unsigned char count;				 // Loop counter
	for (count = 0; count<8 ; count++)
	{
		if(pass1[count] != pass2[count])
			return 0;	
	}
	return 1;
}	


void main()
{  
   unsigned char dig = 0;												// Digit loop												
   unsigned char passCheck = 0;									  		// Password checking confirmation
   unsigned char attempts = 0;								  			// Number of attempts

   //Display arrays
   unsigned char shut[4] = {"SHUT"}; 		                            // Array of SHUT
   unsigned char open[4] = {"OPEN"};        		                    // Array of OPEN
   unsigned char bar[4] = {"BAR-"};                 	                // Array of BAR-
   unsigned char try1[4] = {"TRY1"};		  		                    // Array of TRY1
   unsigned char try2[4] = {"TRY2"};   	  		                        // Array of TRY2
   unsigned char init[4] = {"INIT"};                                    // Array of INIT (for setting password)
   unsigned char set[4] = {"SET "}				                        // Array of SET
   unsigned char agn[4] = {"Agn "};			                            // 
   //Passwords
   unsigned char password1[8] = {0};                                    // Array of password1
   unsigned char password2[8] = {0};                                    // Array of password for checking
   unsigned char passwordMaster[8] = {0};
   
   P2 = 0;  // blank LED
   P2M1 = 0;  
   P2M2 = 0xFF; //set port 2 to be all push-pull outputs
   
   P1 = 0xFF;	// write all port 1 to all ones
   TxD = 0;		// write p1.0 to zero
   P1M1 = 0xFF; // set port 1 only bits 0,1,6 & 7 as open-drain outputs
   P1M2 = 0xC3; // all the rest as input-only 

 
  	setup_led();   // initialises system to use 4 digit 7-segment display. 
    init_scan();   // initialises system to use 12 key keypad.


	/***************************************/
			// Set initial password 
	/***************************************/
	
	do{
	set_led(&init);										  		  // Display INIT until password set

	for(dig = 0; dig < 8; dig++)	//Resets the password array before the new password is written
	{
		passwordMaster[dig] = 0;					   			  
		password1[dig] = 0;
	}
	keystring(&passwordMaster);									  // Uses a pointer to get the array
	if(passwordMaster[0] != 0)
	  {
		set_led(agn);					    		  			  // Display AGN	  
		keystring(&password2);									  // Confirm password
		passCheck = pass_compare(&passwordMaster, &password2);	  // Check for password confirmation
	  }
	}
	while(passCheck != 1 && password2[0] == 0);
	//Remain in loop until both passwords are the same and contain ascii codes (ie. not equal to 0)

	SetTimer(2);
	while(timerval !=0 )
	{
		set_led(set);											  // When password is confirmed display SET for 2 seconds
	}


	/********************************************/
				// Main program loop//
	/********************************************/

  	while (1)  // infinite loop that never ends
	{  
	
	   set_led(shut);                             // Output to LED  
	   
	   while (keypress() == BLANK)										// Wait for a button press
	   	{		}	   
	   
	/********************************************/
				// Collect password//
	/********************************************/
	     		
	   keystring(&password1);	//uses a pointer to get the array	
	  

	 if (timerval != 0)												   // Skip the rest of the program if password entry timed out
	 {

	   passCheck = pass_compare (password1, passwordMaster);                 // Check two passwords
	   
	   //Reset both passwords to 0
	   for(dig=0; dig<8; dig++){
	   	  password1[dig] = 0;								
	   	  password2[dig] = 0;						
	   }
	   

	/********************************************/
		  // Correct Password//
	/********************************************/
	   if(passCheck == 1)
	   { 
	   	   attempts = 0;											  //Reset attempts to 0
	  		SetTimer (5);											  // Timer set for 5 seconds

		   // Turn on relay

		   passCheck = 0;											  // Reset passCheck
		   set_led(open);                     // Display OPEN

		   
		   while (timerval !=0)										  // Wait for 5 seconds to pass
		   { 

	/********************************************/
		// Change Master password //
	/********************************************/

		      if (keypress() == 0x3a)								  // check for * press
			  {	
			    set_led(init);										   
				keystring(password1);								   // Collect 1st password
				if(password1[0] != 0)
				{
					set_led(agn);								   		   // Display AGN
					keystring(password2);								   // Confirm password
					timerval = 0;										   // Reset timer to 0 seconds (so timerout counter doesn't carry over)
				
				passCheck = pass_compare(password1, password2);	   		   // Check new passwords are the same
				}

			    if(passCheck == 1)
				{	
					set_led(set);									   // Display SET for 2 seconds
					SetTimer(2);
					while(timerval != 0){}
					
					for(dig = 0; dig < 8; dig++)
					   passwordMaster[dig] = password1[dig]
// If passwords match change Master Password

					// passwordMaster to be placed in EEPROM
			    }
		       }
		    // Turn off relay
		    }
		 }


	/********************************************/
		  // Incorrect Password//
	/********************************************/

		 else
		 {
		 	attempts++; 											    // Add 1 to number of attempts

	/********************************************/
		// Bar keypad entry and lock door//
	/********************************************/

			if(attempts>2)
			{
			 SetTimer(120);
			  while(timerval !=0)
			  {
                  set_led(bar);                              			// Output to LED  
			  }
			  attempts =0;										  		//Reset attempts
			}

	/********************************************/
				// Attempts Counter//
	/********************************************/

			else
			{
				SetTimer(2); 		 // Set 2 second delay
  				 switch (attempts)
					{
				 		case 1:
				 		 set_led(try1);
						 break;							   // Output TRY1 to LED
				  		case 2:
				  		 set_led(try2);
						 break;      // Output TRY2 to LED
					}
		        while (timerval !=0)
		       	{		}
					
		    }
		  } 
	   }	 		 
  	 }
  }                          
