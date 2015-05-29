#ifndef __FINDERBM_H
#define __FINDERBM_H

static const int AOFFSET  = 32; // offset of the alphabet in ascii table
static const int ASIZE = 127-32+1; // size of the alpabet

int findBM(const char* text,const char* pattern, int text_length, int pattern_length);

#endif
