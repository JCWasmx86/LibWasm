//Some useless code to make clang generate some wasm files.
volatile double d=0;
double f(int x);
void _start(void){
	for(int i=-100;i<=100;i++)
		d+=f(i);
}
double f(int x){
	return (x*x*x)*3+2.5*(x*x)+4.5*x-2.5;
}
