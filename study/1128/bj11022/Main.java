package bj11022;

import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		for(int i = 0; i < n; i++) {
			int num1 = sc.nextInt();
			int num2 = sc.nextInt();
			System.out.printf("Case #%d: %d + %d = %d\n", i+1, num1, num2, (num1+num2));
		}
		sc.close();
	}

}
