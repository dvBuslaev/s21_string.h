#ifndef SRC_S21_STRERROR_H_
#define SRC_S21_STRERROR_H_

#if defined(__APPLE__) || defined(__MACH__)
#define S21_ERRLIST_SIZE 107
#elif defined(__linux__)
#define S21_ERRLIST_SIZE 134
#else
#define S21_ERRLIST_SIZE 134
#endif


#endif