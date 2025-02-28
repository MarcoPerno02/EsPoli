extern void __attribute__((naked)) call_svc(void);

int main(void){

	call_svc();
	
	while(1);
}