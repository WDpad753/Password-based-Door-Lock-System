/* Declaring Libraries */
#include<stdio.h>

/* Declaring Functions */
/* To limit the PIN */
void limitPIN()
{
	/* Declaring Varaibles */
    unsigned char pass[8] = {"00000000"};                                                 // This is the Saved Pass
    unsigned char password[8];                                                            // Password input
    unsigned char PIN;                                                                    // Used to save numbers pressed
    int i;                                                                                // Used for Loop
	for(i=0;i<8;i++)                                                                      // This loop for entering 8 numbers length of password
	{   
		PIN = getch();                                                                    // Getting the password
     	password[i] = PIN;                                                                // Saving password from PIN in password[i]
     	PIN = '*' ;                                                                       // Replacing the number to *
     	printf("%c",PIN);                                                                 // Printing out * in command
	 }
}

/* Checking the PIN */
void checkingPIN()
{
	/* Declaring Varaibles */
    unsigned char pass[8] = {"00000000"};                                                // This is the Saved Pass
    unsigned char password[8];                                                           // Password input
    int i;                                                                               // Used for Loop
    int j = 1;                                                                           // Used to checking
	for (i=0;i<8;i++)                                                                    // This loop for checking if the password[i] is consistent with pass[i]
	{
		if (pass[i] != password[i]) j = 0;                                               // If the password[i] is not equal to pass[i] then equate j to 0
	}
	if (j == 1)                                                                          // If j is equal to 1 then print Correct or else display Invalid
	{
     printf("\nCorrect\n");
	}
	else
	{
     printf("\nInvalid\n");
    }
}

/* Comparing the password entered with saved password */ 
void passwordentered()
{
	/* Declaring Varaibles */
    unsigned char pass[8] = {"00000000"};                                                 // This is the Saved Pass
    unsigned char password[8];                                                            // Password input
    int i;                                                                                // Used for Loop
    printf("\nYour password is : ");                                                      // Print out the password collected
    for(i=0;i<8;i++)  
    {   
        printf("%d",password[i]); 
    } 
    printf("\nSystem password is : ");                                                    // Print out the saved pass 
    for(i=0;i<8;i++)  
    {   
        printf("%d",pass[i]); 
    }
}

/* To change the password */
void changingpassword()
{
	/* Declaring Varaibles */
    unsigned char pass[8] = {"00000000"};                                                 // This is the Saved Pass      
    unsigned char password[8];                                                            // Password input
    unsigned char PIN;                                                                    // Used to save numbers pressed
    int i;                                                                                // Used for Loop
    char change;                                                                          // Used to see if the user want to change the password
    int j;                                                                                // Used to checking
    if (j == 1)                                                                           // If j is eqaul to 1 then it gives option for users to enter new password
   {
     printf("\nDo you want to change password?: ");
     scanf("%c",&change);
     if ((change == 'y')||(change == 'Y'))                                                // If change is equal to y then it requires user to enter new password
     {
        printf("\nEnter the New Password:\n");   
        for(i=0;i<8;i++)  
        {   
            PIN = getch();                                                                // Getting the password
            password[i] = PIN;                                                            // Saving password from PIN in password[i]
            PIN = '*' ;                                                                   // Replacing the number to *
            printf("%c",PIN);                                                             // Printing out * in command
        }
        for (i=0;i<8;i++) pass[i] = password[i];
        /* Comparing the password entered with saved password */ 
        printf("\nYour password is : \n");                                                // Print out the password collected
        for(i=0;i<8;i++)  
        {   
            printf("%d",password[i]); 
        } 
        printf("\nSystem password is : \n");                                              // Print out the saved pass 
        for(i=0;i<8;i++)  
        {   
            printf("%d",pass[i]); 
        }
        /* To End the Program */ 
     }else
     {
          printf("\nEnd of Program\n");
     }
   }
}

int main()
{
	/* Declaring Varaibles */
  	unsigned char pass[8] = {"00000000"};
  	unsigned char password[8];
  	unsigned char PIN;
  	int i;
	char change;
	
	/* Enter the password */
	printf("Enter the Password\n");
	
	/* Calling the functions */
	limitPIN();
	checkingPIN();
	passwordentered();
	changingpassword();
	
	/* Pausing the Program and ending it */
	system ("pause");         
	return(0);
}
