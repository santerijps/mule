#pragma once

#ifndef ITEM_LIST_INITIAL_CAPACITY
  #define ITEM_LIST_INITIAL_CAPACITY 4
#endif

struct ItemList {
  struct Item *items;
  unsigned int length, capacity;
};

enum ItemType {
  EXPR_ITEM,
  VALUE_ITEM,
};

struct Item {
  enum ItemType type;
  union {
    struct Expr *as_expr;
    struct Value *as_value;
  };
};

struct PrefixExpr {
  char *function;
  struct ItemList args;
};

struct InfixExpr {
  char *function;
  struct Item *left, *right;
};

struct PipeExpr {
  struct ItemList args;
};

enum ExprType {
  PREFIX_EXPR_TYPE,
  INFIX_EXPR_TYPE,
  PIPE_EXPR_TYPE,
};

struct Expr {
  enum ExprType type;
  union {
    struct PrefixExpr as_prefix;
    struct InfixExpr as_infix;
    struct PipeExpr as_pipe;
  };
};

enum LiteralValueType {
  LITERAL_BOOL,
  LITERAL_NUMBER,
  LITERAL_STRING,
  LITERAL_LIST,
};

struct LiteralValue {
  enum LiteralValueType type;
  union {
    unsigned char as_bool;
    double as_number;
    char *as_string;
    struct ItemList as_list;
  };
};

struct NamedValue {
  char *name;
};

enum ValueType {
  LITERAL_VALUE_TYPE,
  NAMED_VALUE_TYPE,
};

struct Value {
  enum ValueType type;
  union {
    struct LiteralValue as_literal;
    struct NamedValue as_named;
  };
};
