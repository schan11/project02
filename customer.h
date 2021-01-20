#ifndef CUSTOMER_H
#define CUSTOMER_H

struct customer {
	char first_name[100];
	char last_name[100];
	int credit_card;
	int dining; // -1: delivery, 0: dine in, 1: pick up
};

struct customer *new_customer(char *, char *, int, int);
struct customer *modify_first_name(struct customer *, char *);
struct customer *modify_last_name(struct customer *, char *);
struct customer *modify_card(struct customer *, int);
struct customer *modify_dining(struct customer *, int);
char* get_first_name(struct customer *);
char* get_last_name(struct customer *);
int get_card(struct customer *);
char* get_dining(struct customer *);
struct customer *checkout(struct customer *);
void print_customer(struct customer *);

#endif