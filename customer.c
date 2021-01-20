#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "customer.h"

struct customer *new_customer(char *first, char *last, int card, int dine) {
	struct customer *cust;

	cust = malloc(sizeof(struct customer));

	strncpy(cust->first_name, first, sizeof(cust->first_name)-1);
	strncpy(cust->last_name, last, sizeof(cust->last_name)-1);
	cust->credit_card = card;
	cust->dining = dine;

	return cust;
}

struct customer *modify_first_name(struct customer *cust, char *first) {
	strncpy(cust->first_name, first, sizeof(cust->first_name)-1);
	return cust;
}

struct customer *modify_last_name(struct customer *cust, char *last) {
	strncpy(cust->last_name, last, sizeof(cust->last_name)-1);
	return cust;
}

struct customer *modify_card(struct customer *cust, int card) {
	cust->credit_card = card;
	return cust;
}

struct customer *modify_dining(struct customer *cust, int dine) {
	cust->dining = dine;
	return cust;
}

char* get_first_name(struct customer *cust) {
	return cust->first_name;
}

char* get_last_name(struct customer *cust) {
	return cust->last_name;
}

int get_card(struct customer *cust) {
	return cust->credit_card;
}

char* get_dining(struct customer *cust) {
	char dine[100];

	if (cust->dining == -1)
		strcpy(dine, "delivery");
	else if (cust->dining == 0)
		strcpy(dine, "dine in");
	else if (cust->dining == 1)
		strcpy(dine, "pick up");
	else
		strcpy(dine, "no dining option");

	return dine;
}

struct customer *checkout(struct customer *cust) {
	free(cust);
	return 0;
}

void print_customer(struct customer *cust) {
    /*
	char dine[100];

	if (cust->dining == -1)
		strcpy(dine, "delivery");
	else if (cust->dining == 0)
		strcpy(dine, "dine in");
	else if (cust->dining == 1)
		strcpy(dine, "pick up");
	else
		strcpy(dine, "no dining option");
*/
	printf("First name: %s\n", cust->first_name);
	printf("Last  name: %s\n", cust->last_name);
	printf("Credit Card: %d\n", cust->credit_card);
	printf("Dining Option: %s\n\n", cust->dine);
}
