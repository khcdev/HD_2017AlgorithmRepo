package p_1932;

import java.util.Scanner;

public class p_1932 {
	
	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		
		int triSize = scan.nextInt();
		int[][] arr = new int[triSize][];
		
		for(int i=0; i<triSize; i++) {
			
			arr[i] = new int[i+1];
			
			for(int j=0; j<=i; j++) {
				arr[i][j] = scan.nextInt();
				
				if(i != 0) {
					
					if(j == 0) { // list header
						arr[i][j] = arr[i][j] + arr[i-1][j];
					}
					else if(j == i){ // list tail
						arr[i][j] = arr[i][j] + arr[i-1][j-1];
					}
					else { // list middle
						arr[i][j] = arr[i][j] + arr[i-1][j-1] > arr[i][j] + arr[i-1][j]? arr[i][j] + arr[i-1][j-1]:arr[i][j] + arr[i-1][j];
					}
					
				}
			}
			
		}		
		
		
		int max = arr[triSize-1][0];
		
		for(int i=1; i<triSize; i++) {
			if(max < arr[triSize-1][i]) {
				max = arr[triSize-1][i];
			}
		}
		
		System.out.println(max);
		
	}

}
