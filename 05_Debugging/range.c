#include <stdio.h>
#include <stdlib.h>

void range(long start, long finish, long step) {
	if (start < finish) {
		for (long i = start; i < finish; i = i + step) {
			printf("%ld\n", i);
		}
	} else {
		for (long i = start; i > finish; i = i + step) {
			printf("%ld\n", i);
		}
	}
}

int main(int argc, char* argv[]) {
	long start = 0, finish, step = 1;

	char* pointer = NULL;
	int base = 10;

	switch (argc) {
		case 1:
			printf("Help:\n");
			printf("\t> %s\t - prints help\n", argv[0]);
			printf("\t> %s N\t - prints a sequence of the following numbers: [0, 1, ... , N - 1]\n", argv[0]);
			printf("\t> %s M N\t - prints a sequence of the following numbers: [M, M + 1, ... , N - 1]\n", argv[0]);
			printf("\t> %s M N S\t - prints a sequence of the following numbers: [M, M + S, M + 2S, ... , N - 1]\n", argv[0]);
			return 0;

		case 2:
			finish = strtol(argv[1], &pointer, base);
			break;

		case 3:
			start = strtol(argv[1], &pointer, base);
			finish = strtol(argv[2], &pointer, base);
			break;

		case 4:
			start = strtol(argv[1], &pointer, base);
			finish = strtol(argv[2], &pointer, base);
			step = strtol(argv[3], &pointer, base);

			if (step == 0) {
				printf("Error: zero step is specified!\n");
				return 1;
			}

			break;

		default:
			printf("Error: too many input parameters are specified!\n");
			return 1;
	}

	if ((start <= finish && step < 0) || (start >= finish && step > 0)) {
		printf("[ ] - empty sequence...\n");
		return 0;
	}

	range(start, finish, step);
	return 0;
}
