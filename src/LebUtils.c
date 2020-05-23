#include "LebUtils.h"
//TODO: Maybe there is a better O(1)-way to get the length in
//bytes
uint8_t numBytesForU64(uint64_t v){
	uint8_t cnt=0;
	do{
		uint8_t b=v&0x7f;
		v>>=7;
		if(v)
			b|=(1<<7);
		cnt++;
	}while(v);
	return cnt;
}
uint8_t numBytesForI64(int64_t v){
	int more=1;
	uint8_t cnt=0;
	while(more){
		uint8_t b=v&0x7f;
		v>>=7;
		if((v==0&&(b&0x40)==0)||(v==-1&&((b&0x40)!=0)))
			more=0;
		else
			b|=(1<<7);
		cnt++;
	}
	return cnt;
}
uint8_t numBytesForU32(uint64_t v){
	uint8_t cnt=0;
	do{
		uint8_t b=v&0x7f;
		v>>=7;
		if(v)
			b|=(1<<7);
		cnt++;
	}while(v);
	return cnt;
}
uint8_t numBytesForI32(int32_t v){
	int more=1;
	int cnt=0;
	while(more){
		uint8_t b=v&0x7f;
		v>>=7;
		if((v==0&&(b&0x40)==0)||(v==-1&&((b&0x40)!=0)))
			more=0;
		else
			b|=(1<<7);
		cnt++;
	}
	return cnt;
}
