#include <ctype.h>
#include <regex.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define MATCH_NUMBER 8
#define MESSAGE_LENGTH 256

int main(int argc, char* argv[]) {
	if (argc != 4) {
		printf("Help:\n");
		printf("\t> %s regexp substitution string\n", argv[0]);
		return 0;
	}

	char* regexp = argv[1];
	char* substitution = argv[2];
	char* string = argv[3];

	regex_t regex;
	regmatch_t pmatch[MATCH_NUMBER];

	int return_value;
	char error_message[MESSAGE_LENGTH];

	return_value = regcomp(&regex, regexp, REG_EXTENDED);

	if (return_value) {
		regerror(return_value, &regex, error_message, MESSAGE_LENGTH);
		printf("%s\n", error_message);
		regfree(&regex);
		return 1;
	}

	return_value = regexec(&regex, string, MATCH_NUMBER, pmatch, 0);

	if (!return_value) {
		bool group_flag = false;

		for (char* c = substitution; *c != '\0'; c++) {
			if (*c == '\\') {
				group_flag = !group_flag;
			} else if (group_flag) {
				if (!isdigit(*c)) {
					printf("Error - invalid group number (it should be a number)!\n");
					regfree(&regex);
					return 1;
				}

				int number = atoi(c);

				if (number >= MATCH_NUMBER || pmatch[number].rm_so < 0) {
					printf("Error - invalid group number (too large value)!\n");
					regfree(&regex);
					return 1;
				}

				group_flag = false;
			}
		}

		if (group_flag) {
			printf("Error - incorrect substitution expression (it cannot end with a single '\\' character)!\n");
			regfree(&regex);
			return 1;
		}

		printf("%.*s", pmatch[0].rm_so, string);

		for (char* c = substitution; *c != '\0'; c++) {
			if (*c == '\\') {
				if (group_flag) {
					printf("%c", *c);
				}

				group_flag = !group_flag;
			} else if (group_flag) {
				int number = atoi(c);
				printf("%.*s", pmatch[number].rm_eo - pmatch[number].rm_so, string + pmatch[number].rm_so);
				group_flag = false;
			} else {
				printf("%c", *c);
			}
		}

		printf("%s\n", string + pmatch[0].rm_eo);
		regfree(&regex);
		return 0;
	} else if (return_value == REG_NOMATCH) {
		printf("No match!\n");
		regfree(&regex);
		return 0;
	} else {
		regerror(return_value, &regex, error_message, MESSAGE_LENGTH);
		printf("%s\n", error_message);
		regfree(&regex);
		return 1;
	}
}
