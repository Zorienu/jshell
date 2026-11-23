#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char read_line(void) {

}

void loop(void) {
  char buffer[100];

  printf("> ");
  if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
    printf("You entered: %s\n", buffer);
  }

  char *args[100];
  int arg_idx = 0;
  char arg_buffer[100];
  int start_arg_idx = 0;

  for (int i = 0; i < 100; i++) {
    if (buffer[i] != ' ' && buffer[i] != '\n')
      continue;

    int bytes = (i - start_arg_idx) * sizeof(char);
    args[arg_idx] = malloc(bytes);
    memcpy(args[arg_idx], &buffer[start_arg_idx], bytes);
    start_arg_idx = i + 1;
    arg_idx++;

    if (buffer[i] == '\n')
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
