# project02

by Serena Chan, Sunny Li, Kelly Zhou

# Project Description:

We will be working on a server/client system for a customer purchasing items in a store (ie. food). 
We will display a menu of available items to purchase, then allow customers to input their item(s) of choice. 
After they are done purchasing, we will prompt the customers to enter their payment information (ie. credit card information) 
and we will keep a record of their purchases. We will try to implement this system for different types of shops. Depending on 
the shop, there could also be a return system for the products. 

# User Interface Description:

When the client process is run, it will display a menu (and some commands for the user) and the user will input a command
to access a certain service. Then, they will communicate through the command line to enter and remove items of purchase. They will
indicate when they are finished purchasing, which will prompt them to checkout. After they input their payment information, a receipt
of their purchases will display. 

# Technical Design:

  - Topics from Class:
	
		1. We will be working with files (reading, writing)
		
		2. We will use named pipes to send and receive information
		
		3. We will use signals to close the system
		
		4. We will use forking to go to different child processes
		
		5. We will use memory allocation 
  
  - Breakdown of Parts:
  		
		1. Serena - work with files and pipes to send and receive the information and keep track of the information
		
		2. Sunny - set up structs for customer account information 
		
		3. Kelly - work on forking the processes for the user interface and prompting user input
  
  - Algorithms and Data Structures:
  		
		1. Structs to hold information about the customer (ie. payment information)
  
# Timeline:

1/15: Set up user interface and allow customers to place their orders

1/20: Set up the payment account information and the structs to store them

1/22: Display the purchase history

Beyond: Set up more shops, add more services/ features

