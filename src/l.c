// http://www.sonoma.edu/users/l/luvisi/sl3.c
// http://wiki.c2.com/?ImplementingLisp
// http://www.buildyourownlisp.com/chapter2_installation#documentation
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define ERROR(X) do { fprintf( stderr, "%s\n", X ); exit(1); } while (0)

/*
 * Structured list memory
 */
enum otype { INT, SYM, CONS, PROC, PRIMOP };

typedef struct obj {
  enum otype type;
  struct obj *p[1];
} obj;
typedef obj* (*primop)(obj *);

obj *all_symbols, *top_env, *nil, *tee, *quote, *s_if, *s_lambda, *s_define,
  *s_setb;

#define cons(X, Y)              omake(CONS, 2, (X), (Y))
#define car(X)                  ((X)->p[0])
#define cdr(X)                  ((X)->p[1])
#define setcar(X, Y)            (((X)->p[0]) = (Y))
#define setcdr(X, Y)            (((X)->p[1]) = (Y))
#define mkint(X)                omake(INT, 1, (obj *)(X))
#define intval(X)               ((int)((X)->p[0]))
#define mksym(X)                omake(SYM, 1, (obj *)(X))
#define symname(X)              ((char *)((X)->p[0]))
#define mkprimop(X)             omake(PRIMOP, 1, (obj *)(X))
#define mkproc(X,Y,Z)           omake(PROC, 3, (X), (Y), (Z))
#define procargs(X)             ((X)->p[0])
#define proccode(X)             ((X)->p[1])
#define procenv(X)              ((X)->p[2])
#define isnil(X)                ((X) == nil)

obj *omake(enum otype type, int count, ...) {
  obj *res;
  va_list ap;
  int i;
  va_start(ap, count);
  res = (obj *) malloc( sizeof(obj) + (count - 1) * sizeof(obj *));
  for (i = 0; i < count; i++) res->p[i] = va_arg(ap, obj*);
  va_end(ap);
  return res;
}
