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
    char c = getchar();

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

void loop(void) {
  printf("> ");
  char *buffer = read_line();
  printf("Buffer: %s\n", buffer);

  char *args[100];
  int arg_idx = 0;
  char arg_buffer[100];
  int start_arg_idx = 0;

  for (int i = 0; i < 100; i++) {
    if (buffer[i] != ' ' && buffer[i] != '\0')
      continue;

    int bytes = (i - start_arg_idx) * sizeof(char);
    args[arg_idx] = malloc(bytes);
    memcpy(args[arg_idx], &buffer[start_arg_idx], bytes);
    start_arg_idx = i + 1;
    arg_idx++;

    if (buffer[i] == '\0')
      break;
  }

  for (int i = 0; i < arg_idx; i++) {
    printf("arg[%i]: %s\n", i, args[i]);
  }
}

int main(int argc, char **argv) {
  loop();
  return 0;
}
