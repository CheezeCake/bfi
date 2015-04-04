#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_INPUT_SIZE (4 * 1024 * 1024) /* 4MB */
#define MAX_NESTED_LOOPS 1024

int main(int argc, char **argv)
{
	char bf_array[30 * 1000] = {0};
	char* bf_p = bf_array;

	char program[MAX_INPUT_SIZE] = {0};
	int ip = 0;
	int loop_indexes_stack[MAX_NESTED_LOOPS] = {0};
	int li_top = -1;

	FILE* input = stdin;
	char c;

	int i = 0;
	int bracket_count = 0;

	if (argc >= 2) {
		if (!(input = fopen(argv[1], "r"))) {
			fprintf(stderr, "Could not open %s : %s\n", argv[1], strerror(errno));
			return 1;
		}
	}

	while ((c = fgetc(input)) != EOF) {
		program[i++] = c;
		if (c == '[')
			++bracket_count;
		else if (c == ']')
			--bracket_count;

		if (bracket_count < 0) {
			fprintf(stderr, "unbalanced [ ] in input\n");
			return 1;
		}
	}

	fclose(input);

	if (bracket_count != 0) {
		fprintf(stderr, "unbalanced [ ] in input\n");
		return 1;
	}

	while (program[ip]) {
		switch (program[ip]) {
			case '>':
				++bf_p;
				break;
			case '<':
				--bf_p;
				break;
			case '+':
				++(*bf_p);
				break;
			case '-':
				--(*bf_p);
				break;
			case '.':
				putchar(*bf_p);
				break;
			case ',':
				*bf_p = getchar();
				break;
			case '[':
				if (*bf_p && li_top < MAX_NESTED_LOOPS) {
					loop_indexes_stack[++li_top] = ip;
				}
				else {
					bracket_count = 0;
					do {
						if (program[ip] == '[')
							++bracket_count;
						else if (program[ip] == ']')
							--bracket_count;

						++ip;
					} while (bracket_count != 0);

					--ip;
				}
				break;
			case ']':
				if (li_top >= 0) {
					ip = loop_indexes_stack[li_top--] - 1;
				}
				else {
					printf("Error\n");
					return 1;
				}
				break;
		}

		++ip;
	}

	return 0;
}
