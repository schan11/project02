#ifndef CUSTOMER_H
#define CUSTOMER_H

struct customer {
	char first_name[100];
	char last_name[100];
	long credit_card;
	int dining; // 1: delivery, 2: dine in, 3: pick up
};

struct customer *new_customer(char *, char *, long, int);
struct customer *modify_first_name(struct customer *, char *);
struct customer *modify_last_name(struct customer *, char *);
struct customer *modify_card(struct customer *, long);
struct customer *modify_dining(struct customer *, int);
char* get_first_name(struct customer *);
char* get_last_name(struct customer *);
long get_card(struct customer *);
char* get_dining(struct customer *);
struct customer *checkout(struct customer *);
void print_customer(struct customer *);

#endif