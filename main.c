#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define JSHELL_RL_BUFF_SIZE 1024
char *read_line(void) {
  int buff_size = JSHELL_RL_BUFF_SIZE;
  char *buffer = malloc(buff_size * sizeof(char));
  int idx = 0;

  if (!buffer) {
    fprintf(stderr, "jshell: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (true) {
    // Declared as an int instaed of a char because EOF is an integer
    int c = getchar();

    if (c == EOF || c == '\n') {
      buffer[idx] = '\0';
      return buffer;
    }

    buffer[idx++] = c;

    if (idx >= buff_size) {
      buff_size += JSHELL_RL_BUFF_SIZE;
      buffer = realloc(buffer, buff_size);

      if (!buffer) {
        fprintf(stderr, "jshell: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

#define JSHELL_SL_BUFF_SIZE 64
char **split_line(char *line) {
  int buff_size = JSHELL_SL_BUFF_SIZE;
  char **args = malloc(sizeof(char *) * buff_size);
  int arg_idx = 0;
  int start_arg_idx = 0;

  if (args == NULL) {
    fprintf(stderr, "jshell: allocation error\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < buff_size; i++) {
    if (line[i] != ' ' && line[i] != '\0')
      continue;

    int bytes = (i - start_arg_idx) * sizeof(char);
    args[arg_idx] = malloc(bytes);
    memcpy(args[arg_idx], &line[start_arg_idx], bytes);
    start_arg_idx = i + 1;
    arg_idx++;

    if (arg_idx >= buff_size) {
      buff_size += JSHELL_SL_BUFF_SIZE;
      args = realloc(args, buff_size);

      if (args == NULL) {
        fprintf(stderr, "jshell: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    if (line[i] == '\0') {
      args[arg_idx] = NULL;
      break;
    }
  }

  return args;
}

void loop(void) {
  printf("> ");
  char *buffer = read_line();
  printf("Buffer: %s\n", buffer);

  char **args = split_line(buffer);

  for (int i = 0; i < 100; i++) {
    if (args[i] == NULL)
      break;
    printf("arg[%i]: %s\n", i, args[i]);
  }
}

int main(int argc, char **argv) {
  loop();
  return 0;
}
