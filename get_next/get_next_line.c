#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>


int find_newline(const char *line) {
    if (!line)
        return -1;
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '\n')
            return i;
    }
    return -1;
}

char *extract_line(char **line) {
    int newline_index = find_newline(*line);
    char *output;

    if (newline_index == -1) {
        output = *line; // Return the entire remaining line
        *line = NULL;   // No leftover
        return output;
    }

    output = malloc(newline_index + 2);
    if (!output)
        return NULL;

    for (int i = 0; i <= newline_index; i++)
        output[i] = (*line)[i];
    output[newline_index + 1] = '\0';

    char *leftover = malloc(ft_strlen(*line) - newline_index);
    if (!leftover)
        return NULL;

    for (size_t i = 0; (*line)[newline_index + 1 + i] != '\0'; i++)
        leftover[i] = (*line)[newline_index + 1 + i];
    leftover[ft_strlen(*line) - newline_index - 1] = '\0';

    free(*line);
    *line = leftover;
    return output;
}

char *read_into_line(int fd, char *line) {
    char buffer[BUFFER_SIZE + 1];
    int bytes_read;

    while (find_newline(line) == -1) {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read < 0)
            return NULL; // Read error
        if (bytes_read == 0) // EOF
            return line;

        buffer[bytes_read] = '\0';
        line = ft_strjoin(line, buffer);
        if (!line)
            return NULL; // Allocation error
    }

    return line;
}

char *get_next_line(int fd) {
    static char *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    line = read_into_line(fd, line);
    if (!line)
        return NULL;

    return extract_line(&line);
}
