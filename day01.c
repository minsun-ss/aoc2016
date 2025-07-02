#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char turn(char *position, char *direction) {
    if (*direction == 'R') {
        if (*position == 'N') {
            return 'E';
        } else if (*position == 'E') {
            return 'S';
        } else if (*position == 'S') {
            return 'W';
        } else {
            return 'N';
        }
    } else {
        if (*position == 'N') {
            return 'W';
        } else if (*position == 'W') {
            return 'S';
        } else if (*position == 'S') {
            return 'E';
        } else {
            return 'N';
        }
    }
}

int part1() {
    FILE *file = fopen("data/day1", "r");

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(file_size+1);
    size_t bytes_read = fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';

    // tokenizing, y u so hard in c
    int x = 0, y = 0;
    char direction = 'N';

    char* token = strtok(buffer, " ");
    while (token != NULL) {
        char lr[2];
        memcpy(lr, &token[0], 1);
        lr[1] = '\0';

        int value = atoi(token +1);

        if (*lr == 'R' || *lr == 'L') {
            direction = turn(&direction, lr);
        }

        if (direction == 'N') {
            y += value;
        } else if (direction == 'E') {
            x += value;
        } else if (direction == 'S') {
            y -= value;
        } else if (direction == 'W') {
            x -= value;
        }

        token = strtok(NULL, " ");
    }
    int blocks = abs(x) + abs(y);
    fclose(file);

    return blocks;
}

int part2() {
    FILE *file = fopen("data/day1", "r");

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(file_size+1);
    size_t bytes_read = fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';

    int coords[1000][2];
    int current_pos = 0;
    int x = 0, y = 0;
    char direction = 'N';

    char* token = strtok(buffer, " ");
    while (token != NULL) {
        char lr[2];
        memcpy(lr, &token[0], 1);
        lr[1] = '\0';

        int value = atoi(token +1);

        if (*lr == 'R' || *lr == 'L') {
            direction = turn(&direction, lr);
        }

        for (int i = 0; i < value; i++) {
            if (direction == 'N') {
                y += 1;
            } else if (direction == 'E') {
                x += 1;
            } else if (direction == 'S') {
                y -= 1;
            } else if (direction == 'W') {
                x -= 1;
            }

            // create the coordinate
            coords[current_pos][0] = x;
            coords[current_pos][1] = y;

            for (int j = 0; j < current_pos; j++) {
                if (coords[j][0] == x && coords[j][1] == y) {
                    int blocks = abs(x) + abs(y);
                    fclose(file);
                    return blocks;
                }
            }
            current_pos++;
        }

        token = strtok(NULL, " ");
    }
}

int main() {
    printf("Part 1: %d\n", part1());
    printf("Part 2: %d\n", part2());

    return 0;
}
