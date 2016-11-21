#ifndef UTIL_H
#define UTIL_H
#ifdef __cplusplus
extern "C" {
#endif

unsigned inportb(unsigned);
void outportb(unsigned, unsigned);
void stopints();
void startints();

#ifdef __cplusplus
}
#endif

#endif
