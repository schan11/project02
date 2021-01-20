#include <stdio.h>
#include "customer.h"

int main() {
	struct customer *bob = new_customer("bob", "smith", 123123123, -1);

	print_customer(bob);

	modify_first_name(bob, "bobby");

	print_customer(bob);

	modify_last_name(bob, "smithy");

	print_customer(bob);

	modify_card(bob, 321321321);

	print_customer(bob);

	modify_dining(bob, 0);

	print_customer(bob);

	modify_dining(bob, 1);

	print_customer(bob);

	modify_dining(bob, 2);

	print_customer(bob);

	printf("%s %s\n%d\n\n", get_first_name(bob), get_last_name(bob), get_card(bob));  //  get_dining(bob)

	checkout(bob);

	print_customer(bob);

	return 0;
}
