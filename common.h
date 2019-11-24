#ifdef DEBUG
#define PRINT_DEBUG(args)	fprintf args
#else
#define PRINT_DEBUG(args)	do {} while (0)
#endif

#ifndef PROGRAM_VERSION
#define PROGRAM_VERSION	"dev"
#endif
#define ARGP_PROGRAM_VERSION "version "PROGRAM_VERSION
