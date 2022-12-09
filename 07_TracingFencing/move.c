#include <stdio.h>
#include <stdlib.h>

#define SIZE 128

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("Help:\n");
		printf("\t> %s infile outfile\n", argv[0]);
		return 0;
	}

	const char* infile = argv[1];
	const char* outfile = argv[2];

	FILE* input_file = fopen(infile, "r");

	if (input_file == NULL) {
		printf("Error: can't open file '%s' for reading!\n", infile);
		exit(1);
	}

	FILE* output_file = fopen(outfile, "w");

	if (output_file == NULL) {
		printf("Error: can't open file '%s' for writing!\n", outfile);
		fclose(input_file);
		exit(2);
	}

	char buffer[SIZE];
	int read_counter;
	int write_counter;

	while (feof(input_file) == 0) {
		read_counter = fread(buffer, sizeof(char), SIZE, input_file);
		
		if ((read_counter != SIZE) && (feof(input_file) != 0)) {
			if (ferror(input_file) != 0) {
				printf("Error: can't read characters from file '%s'!\n", infile);
				fclose(input_file);
				fclose(output_file);
				remove(outfile);
				exit(3);
			}
		}

		write_counter = fwrite(buffer, sizeof(char), read_counter, output_file);

		if (write_counter != read_counter) {
			printf("Error: can't write characters to file '%s'!\n", outfile);
			fclose(input_file);
			fclose(output_file);
			remove(outfile);
			exit(4);
		}
	}

	fclose(input_file);
	fclose(output_file);
	remove(infile);

	return 0;
}
