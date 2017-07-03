int findLastComputer(int a, int b){
	int x, i;
	
	x = 1;
	for(i=0; i<b; i++){
		x *= a;
		x %= 10;
	}
	
	return (!x)*10 + x;
}
int main(){
	int T, i, a, b;
	
	scanf("%d", &T);
	for(i=0; i<T; i++){
		scanf("%d %d", &a, &b);
		printf("%d\n", findLastComputer(a, b));
	}
    
    return 0;
}