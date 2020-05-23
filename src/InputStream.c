#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <locale.h>
#include <string.h>
#include <wchar.h>

#include "InputStream.h"

uint32_t readUleb(InputStream in){
	uint32_t result = 0;
	uint32_t cur;
	int count = 0;
	do {
		cur = fgetc(in->file) & 0xff;
		result |= (cur & 0x7f) << (count * 7);
		count++;
	}while (((cur & 0x80) == 0x80) && count < 5);
	in->pos+=count;
	return result;
}
uint64_t readUleb64(InputStream in){
	uint64_t result = 0;
	uint64_t cur;
	int count = 0;
	do {
		cur = fgetc(in->file) & 0xff;
		result |= (cur & 0x7f) << (count * 7);
		count++;
	}while (((cur & 0x80) == 0x80) && count < 10);
	in->pos+=count;
	return result;
}
int32_t readLeb(InputStream in){
	int32_t result = 0;
	int32_t cur;
	int count = 0;
	int signBits = -1;
	do {
		cur = fgetc(in->file) & 0xff;
		result |= (cur & 0x7f) << (count * 7);
		signBits <<= 7;
		count++;
	}while (((cur & 0x80) == 0x80) && count < 5);
	in->pos+=count;
	if (((signBits >> 1) & result) != 0 ) {
		result |= signBits;
	}
	return result;
}
int64_t readLeb64(InputStream in){
	uint64_t shift = 0;
	int64_t result = 0;
	uint8_t byte;
	while (1){
		byte = getc(in->file);
		result |= ((uint64_t) (byte & 0x7f)) << shift;
		shift += 7;
		if ((byte & 0x80) == 0)
			break;
	}
	if (shift < (64) && (byte & 0x40) != 0)
		result |= -(((uint64_t) 1) << shift);
	return result;
}
float readFloatIEEE754(InputStream in){
	float f=0;
	fread(&f,4,1,in->file);
	in->pos+=4;
	return f;
}
double readDoubleIEEE754(InputStream in){
	double f=0.0;
	fread(&f,8,1,in->file);
	in->pos+=8;
	return f;
}
//No unicode support, as decoding unicode isn't supported 
//at the moment.
const wchar_t* readName(InputStream in){
	uint32_t length=readUleb(in);
	wchar_t* ret=calloc((length+1),sizeof(wchar_t));
	assert(ret!=NULL);
	for(uint32_t i=0;i<length;i++){
		uint8_t tmp=0;
		fread(&tmp,1,1,in->file);
		ret[i]=tmp;
	}
	in->pos+=length;
	return ret;
}
int readOneByte(InputStream in,uint8_t * into){
	in->pos++;
	return fread(into,1,1,in->file);
}
InputStream open(const char* name){
	InputStream ret=malloc(sizeof(struct _inputStream));
	ret->file=fopen(name,"rb");
	ret->pos=0;
	return ret;
}
InputStream openW(const wchar_t* name){
	setlocale(LC_ALL, "");
	char* tmp=calloc(wcslen(name)+1,1);
	wcstombs(tmp,name,wcslen(name));
	InputStream ret=open(tmp);
	free(tmp);
	return ret;
}
void close(InputStream in){
	if(in->file!=NULL)
		fclose(in->file);
	free(in);
}
uint8_t* readNBytes(InputStream in,uint32_t howMany){
	uint8_t * ret=calloc(1,howMany);
	assert(ret!=NULL);
	fread(ret,1,howMany,in->file);
	in->pos+=howMany;
	return ret;
}
