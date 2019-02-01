#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <Rmath.h>
#include <R_ext/Rdynload.h>

// call Fortran
void F77_NAME(llc_f)(double *x, int n, double *l, double *a, double *ret);
void F77_NAME(add_f)(double *a, double *b, double *ret);

/*
 * called from R using .Call
 * This function communicates between R and C.
 *
 */
extern SEXP c_llc_f(SEXP x, SEXP l, SEXP a){
  const int n = LENGTH(x);
  SEXP ret;
  PROTECT(ret = allocVector(REALSXP, 1));
  F77_CALL(llc_f)(REAL(x), n, REAL(l), REAL(a), REAL(ret));
  UNPROTECT(1);
  return(ret);
}
extern SEXP c_add_f(SEXP a, SEXP b){
  SEXP ret;
  PROTECT(ret = allocVector(REALSXP, 1));
  F77_CALL(add_f)(REAL(a), REAL(b), REAL(ret));
  UNPROTECT(1);
  return(ret);
}

/*
 * Add the needed package code to C
 *
 */
static const R_CallMethodDef CallEntries[] = {
  {"c_llc_f",   (DL_FUNC) &c_llc_f,  3},
  {"c_add_f",   (DL_FUNC) &c_add_f,  2},
  {NULL,         NULL,               0}
};

void R_init_newPackage (DllInfo *dll) {
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);

}
