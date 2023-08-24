#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "include/token.h"
#include "include/expr.h"

struct Expr read_prefix_expr(FILE *stream) {
  char c;
  while ((c = fgetc(stream)) != EOF) {
    switch (c) {
      case '(':
        read_prefix_expr(stream);
        break;
      case '{':
        read_infix_expr(stream);
        break;
      case '[':
        read_pipe_expr(stream);
        break;
      default:
        break;
    }
  }
}

struct Expr read_infix_expr(FILE *stream) {

}

struct Expr read_pipe_expr(FILE *stream) {

}

int read_file(const char *file_path) {
  FILE *stream = fopen(file_path, "r");
  if (stream == NULL) {
    fprintf(stderr, "Failed to open file with path: %s\n", file_path);
    return 1;
  }
  char c;
  while ((c = fgetc(stream)) != EOF) {
    switch (c) {
      case '(':
        read_prefix_expr(stream);
        break;
      case '{':
        read_infix_expr(stream);
        break;
      case '[':
        read_pipe_expr(stream);
        break;
    }
  }
  return fclose(stream);
}

int main(int argc, char **argv) {
  for (int i = 1; i < argc; i++) {
    fprintf(stderr, "### PARSE BEGIN = %s ###\n", argv[i]);
    fprintf(stderr, "### PARSE STATE = %s ###\n", read_file(argv[i]) ? "ERROR" : "OK");
  }
  return 0;
}
