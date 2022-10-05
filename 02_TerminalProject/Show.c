#include <ncurses.h>
#include <stdlib.h>

#define BORDER 3

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Specify the file to open!\n");
		return -1;
	}

	FILE* file = fopen(argv[1], "r");

	if (file == NULL) {
		printf("Could not open the file!\n");
		return -1;
	}

	fseek(file, 0, SEEK_END);
	long int file_size = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* buffer = (char*)malloc((file_size + 1) * sizeof(char));

	if (buffer == NULL) {
		printf("Memory allocation failed!\n");
		return -1;
	}

	size_t read_characters = fread(buffer, sizeof(char), file_size, file);

	if (read_characters != file_size) {
		printf("Reading process ended incorrectly!\n");
		return -1;
	}

	buffer[file_size] = '\0';
	fclose(file);

	int line_counter = 0;

	for (int i = 0; i < file_size; i++) {
		if (buffer[i] == '\n') {
			line_counter = line_counter + 1;
		}
	}

	char** text = malloc((line_counter + 1) * sizeof(char*));
	text[0] = buffer;

	for (int i = 0, j = 1; i < file_size; i++) {
		if (buffer[i] == '\n') {
			text[j] = buffer + i + 1;
			j = j + 1;
		}
	}

	initscr();
	noecho();
	cbreak();

	printw("File name = %s, lines = %d, characters = %d", argv[1], line_counter, file_size);
	refresh();

	WINDOW* win;
	win = newwin(LINES - 2 * BORDER, COLS - 2 * BORDER, BORDER, BORDER);
	keypad(win, TRUE);

	int max_x, max_y, character;
	int stop = 0, last_line = 0;

	getmaxyx(win, max_y, max_x);

	while (!stop) {
		for (int i = 0; i < max_y - 2 && i + last_line < line_counter; i++) {
			mvwprintw(win, i + 1, 1, "%4d:  %s", i + last_line + 1, text[i + last_line]);
		}

		box(win, 0, 0);
		wrefresh(win);

		switch (character = wgetch(win)) {
			case 27:
				stop = 1;
				break;
			case ' ':
				if (last_line < line_counter) {
					last_line = last_line + max_y - 2;
					werase(win);
				}
				break;
		}
	}

	endwin();
	free(buffer);
	free(text);

	return 0;
}
