#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "customer.h"

struct customer *new_customer(char *first, char *last, long card, int dine) {
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

struct customer *modify_card(struct customer *cust, long card) {
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

long get_card(struct customer *cust) {
	return cust->credit_card;
}

char* get_dining(struct customer *cust) {
	if (cust->dining == 1)
		return "delivery";
	else if (cust->dining == 2)
		return "dine in";
	else if (cust->dining == 3)
		return "pick up";
	else
		return "no dining option";
}

struct customer *checkout(struct customer *cust) {
	free(cust);
	return 0;
}

void print_customer(struct customer *cust) {
	char dine[100];

	if (cust->dining == 1)
		strcpy(dine, "Delivery");
	else if (cust->dining == 2)
		strcpy(dine, "Dine in");
	else if (cust->dining == 3)
		strcpy(dine, "Pick up");
	else
		strcpy(dine, "no dining option");

	printf("First name: %s\n", cust->first_name);
	printf("Last  name: %s\n", cust->last_name);
	printf("Credit Card: %lu\n", cust->credit_card);
	printf("Dining Option: %s\n\n", dine);
}
