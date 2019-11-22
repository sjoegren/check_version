#ifdef DEBUG
#define PRINT_DEBUG(args)	fprintf args
#else
#define PRINT_DEBUG(args)	do {} while (0)
#endif
