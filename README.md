# CAFE C

by Serena Chan, Sunny Li, Kelly Zhou (Period 10)

## Project Description:

Welcome to the grand opening of Cafe C! We sell a wide variety of refreshing drinks, Japanese-themed appetizers, and delectable desserts. With our interactive server/client system, customers will be able to order a high-quality meal with easy to follow, step-by-step instructions. Our cafe ensures a safe transaction; we use a fail-proof system that will confirm your information after you've entered it, and even allows you to update your information if necessary.

## Library List:

- <stdio.h>
- <stdlib.h>
- <fcntl.h>
- <unistd.h>
- <signal.h>
- <string.h>
- <sys/stat.h>
- <sys/types.h>
- <errno.h>

Library Installation Instructions: N/A

## Instructions:

1. Compile and make, then type ./menu into terminal. Our main menu will be displayed, with provided instructions to choose your preferred food category.
2. After doing so, create a new tab in terminal and type ./system. This will open the pipes, allowing us to receive and keep track of your info.
3. Follow the printed instructions and input information as prompted.


## Bugs (so far):

- If the customer enters an invalid input as the first order, an error is not reported and the program has to be reset (However, an error is correctly reported for invalid inputs after the first order)
- If an invalid credit card number is inputted, the system will not allow you to input a dining option.
---

# Project Proposal (original, final updated version above)

## Project Description:

We will be working on a server/client system for a customer purchasing items in a store (ie. food).
We will display a menu of available items to purchase, then allow customers to input their item(s) of choice.
After they are done purchasing, we will prompt the customers to enter their payment information (ie. credit card information)
and we will keep a record of their purchases. We will try to implement this system for different types of shops. Depending on
the shop, there could also be a return system for the products.

## User Interface Description:

When the client process is run, it will display a menu (and some commands for the user) and the user will input a command
to access a certain service. Then, they will communicate through the command line to enter and remove items of purchase. They will
indicate when they are finished purchasing, which will prompt them to checkout. After they input their payment information, a receipt
of their purchases will display.

## Technical Design:

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

## Timeline:

1/15: Set up user interface and allow customers to place their orders

1/20: Set up the payment account information and the structs to store them

1/22: Display the purchase history

Beyond: Set up more shops, add more services/ features
