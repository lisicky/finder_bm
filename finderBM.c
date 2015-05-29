#include "finderBM.h"
#include <unistd.h>
#include <stdlib.h>

static void  pre_bm_bc(const char* pattern, int pattern_length, int* table_bc, int asize);
static void pre_bm_gs(const char* pattern, int pattern_length, int* table_gs); 
static int  is_prefix(const char* pattern, int pattern_length, int p);
static int suffix_length(const char* pattern, int pattern_length, int p);

static inline int max(int a, int b) {
	return (a>b)?a:b;
}

int findBM(const char* text,const char* pattern, int text_length, int pattern_length)
{
	int* table_bc;
	int* table_gs;
	int pos=-1;
	int index_bc;

	if(pattern_length==0)
		return 0;
	if(text_length==0)
		return -1;
	if(pattern_length>text_length)
		return -1;
	if((NULL==pattern)||(NULL==text))
		return -2;
	if((NULL==(table_bc=(int*)malloc(ASIZE*sizeof(int))))) {
		return -2;	
	}	
	if((NULL==(table_gs=(int*)malloc(pattern_length*sizeof(int))))) {
		free(table_bc);
		return -2;	
	}	
	 pre_bm_bc(pattern,pattern_length,table_bc,ASIZE);
	 pre_bm_gs(pattern,pattern_length,table_gs);

	for(int i=pattern_length-1; (i<text_length)&&(pos<0);) {
		int j = pattern_length - 1;
		while (pattern[j]==text[i]) {
			if(j==0) {
				pos=i;
				break;
			}
			j--;
			i--;	
		}
		if(text[i]<AOFFSET) {
		 	i+=pattern_length-j;
			continue;
		}
		index_bc=text[i]-AOFFSET;
		i+=max(table_gs[pattern_length-1-j], table_bc[index_bc]);
	}
	free(table_bc);
	free(table_gs);	
	return pos;
}

static void  pre_bm_bc(const char* pattern, int pattern_length, int* table_bc, int asize) {
	int index_in_table;
	for(int i=0; i<asize; i++) { 
		table_bc[i]=pattern_length;
	}
	for(int i=0; i<(pattern_length-1); i++) {
		if(0>(index_in_table=pattern[i]-AOFFSET)) {
			return;
		}
		table_bc[index_in_table]=pattern_length-i-1;
	}
}

//return non zero if true 
static int  is_prefix(const char* pattern, int pattern_length, int p) {
	int j=0;
	for(int i=p; i<pattern_length; i++) {
		if(pattern[i]!=pattern[j])
			return 0;
		j++;
	}
	return 1;
}

static int suffix_length(const char* pattern, int pattern_length, int p) {
	int len=0;
	int j=pattern_length-1;
	for(int i=p; (i>=0)&&(pattern[i]==pattern[j]); i--) {
		len++;
		j--;
	}
	return len;
}

static void pre_bm_gs(const char* pattern, int pattern_length, int* table_gs) {
	int last_prefix_pos = pattern_length;
	for(int i=pattern_length-1; i>=0; i--) {
		if(is_prefix(pattern,pattern_length,i+1))
			last_prefix_pos=i+1;
		table_gs[pattern_length-i-1]=last_prefix_pos + pattern_length - i - 1;
	
	}
	for(int i=0; i<pattern_length-1; i++) {
		int suff_len = suffix_length(pattern,pattern_length,i);
		table_gs[suff_len] = pattern_length + suff_len - i - 1;
	}
}
