//Some useless code to make clang generate some wasm files.
extern int (*__main)(int argc,char**argv);
#define NULL ((void*)0)
void _start(void){
	for(int i=0;i<100;i++){
		char* argv[2];
		argv[0]="useless";
		argv[1]=NULL;
		int ret=__main(1,argv);
		i^=ret;
	}
}
