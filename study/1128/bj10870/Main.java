package bj10870;

import java.util.Scanner;

public class Main {

	public static int fibo(int n) {
		int result = 0;
		//base case
		if (n == 0) return 0;
		if (n == 1) return 1;
		
		result = fibo(n-1) + fibo(n-2);
		return result;
	}
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int result = fibo(n);
		System.out.println(result);
		sc.close();
	}
}
