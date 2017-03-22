#undef CENUM_START
#undef CENUM_END
#undef CENUM_ITEM
#undef CENUM_VALUE

#if defined(CENUM_PROCESS_VAR)
# define CENUM_START(E) \
switch ( CENUM_PROCESS_VAR ) {
#else
# define CENUM_START(E) \
switch (e) {
#endif

#define CENUM_END(E) \
}

#if defined(CENUM_PROCESS_PREFIX) && defined(CENUM_PROCESS_ARG)
#define CENUM_ITEM(E,S,N) \
  case E : CENUM_PROCESS_PREFIX :: N ( CENUM_PROCESS_ARG ); break;
#elif defined(CENUM_PROCESS_PREFIX)
#define CENUM_ITEM(E,S,N) \
  case E : CENUM_PROCESS_PREFIX :: N ( ); break;
#elif defined(CENUM_PROCESS_ARG)
#define CENUM_ITEM(E,S,N) \
  case E : process :: N ( CENUM_PROCESS_ARG ); break;
#else
#define CENUM_ITEM(E,S,N) \
  case E : process :: N ( ); break;
#endif

#define CENUM_VALUE(E,S,N,V) CENUM_ITEM(E,S,N)
