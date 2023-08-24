#pragma once

#ifndef _INC_STDIO
  #include <stdio.h>
#endif

#ifndef _INC_STDLIB
  #include <stdlib.h>
#endif

#ifndef _INC_STRING
  #include <string.h>
#endif

#ifndef assert
  #include <assert.h>
#endif

enum TokenType {
  TOKEN_LPAREN,
  TOKEN_RPAREN,
  TOKEN_LBRACE,
  TOKEN_RBRACE,
  TOKEN_LBRACKET,
  TOKEN_RBRACKET,
  TOKEN_EQUALS,
  TOKEN_PLUS,
  TOKEN_NAME,
  TOKEN_UNDEFINED,
};

const char* token_type_to_string(enum TokenType t) {
  switch (t) {
    case TOKEN_LPAREN:
      return "TOKEN_LPAREN";
    case TOKEN_RPAREN:
      return "TOKEN_RPAREN";
    case TOKEN_LBRACE:
      return "TOKEN_LBRACE";
    case TOKEN_RBRACE:
      return "TOKEN_RBRACE";
    case TOKEN_LBRACKET:
      return "TOKEN_LBRACKET";
    case TOKEN_RBRACKET:
      return "TOKEN_RBRACKET";
    case TOKEN_EQUALS:
      return "TOKEN_EQUALS";
    case TOKEN_PLUS:
      return "TOKEN_PLUS";
    case TOKEN_NAME:
      return "TOKEN_NAME";
    default:
      return "TOKEN_UNDEFINED";
  }
}

enum TokenType token_type_from(char *x) {
  if (!strcmp(x, "(")) return TOKEN_LPAREN;
  if (!strcmp(x, ")")) return TOKEN_RPAREN;
  if (!strcmp(x, "{")) return TOKEN_LBRACE;
  if (!strcmp(x, "}")) return TOKEN_RBRACE;
  if (!strcmp(x, "[")) return TOKEN_LBRACKET;
  if (!strcmp(x, "]")) return TOKEN_RBRACKET;
  if (!strcmp(x, "=")) return TOKEN_EQUALS;
  if (!strcmp(x, "+")) return TOKEN_PLUS;
  return TOKEN_NAME;
}

struct Token {
  enum TokenType type;
  char *value;
};

int token_to_string(struct Token *t, char *buf) {
  return sprintf(
    buf,
    "Token { %s => `%s` }",
    token_type_to_string(t->type),
    t->value
  );
}

int token_print(struct Token *t) {
  char buf[1024] = {0};
  token_to_string(t, buf);
  return fprintf(stderr, "%s\n", buf);
}

struct Token token_from(char *value) {
  struct Token t;
  t.value = (char*) calloc(strlen(value) + 1, sizeof(char));
  strcpy(t.value, value);
  t.type = token_type_from(t.value);
  return t;
}

void token_update_value(struct Token *t, char *new_value) {
  t->value = (char*) calloc(strlen(new_value) + 1, sizeof(char));
  strcpy(t->value, new_value);
  t->type = token_type_from(t->value);
}

struct TokenList {
  struct Token *items;
  unsigned int length;
  unsigned int capacity;
};

void token_list_to_string(struct TokenList *list, char *buf) {
  strcat(buf, "[");
  for (int i = 0; i < list->length; i++) {
    char my_buf[4096] = {0};
    token_to_string(&(list->items[i]), my_buf);
    strcat(buf, " ");
    strcat(buf, my_buf);
  }
  strcat(buf, " ]");
}

int token_list_print(struct TokenList *list) {
  char buf[4096] = {0};
  token_list_to_string(list, buf);
  return fprintf(stderr, "%s\n", buf);
}

struct TokenList token_list_init(unsigned char capacity) {
  struct TokenList x;
  x.items = NULL;
  x.length = 0;
  x.capacity = capacity;
  return x;
}

void token_list_resize(struct TokenList *list, unsigned char new_capacity) {
  list->capacity = new_capacity;
  list->items = (struct Token*) realloc(list->items, sizeof(struct Token) * new_capacity);
  assert(list->items != NULL);
}

void token_list_add(struct TokenList *list, struct Token token) {
  if (list->items == NULL) {
    list->items = (struct Token*) malloc(sizeof(struct Token) * list->capacity);
    assert(list->items != NULL);
  }
  if (list->length >= list->capacity) {
    token_list_resize(list, list->capacity * 2);
  }
  list->items[list->length++] = token;
}

void token_list_free(struct TokenList *list) {
  free(list->items);
}
