package bj2869;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

public class Main {
	static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	
	public static int func1() throws IOException {
		//입출력
		String input = br.readLine();
		String[] inputs = input.split(" ");
		int A = Integer.parseInt(inputs[0]);
		int B = Integer.parseInt(inputs[1]);
		int V = Integer.parseInt(inputs[2]);
		//로직
		int tot = 0;
		int day = 1;
		while(true) {
			tot += A;
			if(tot >= V) break; 
			tot -= B;
			day++;
		}
		return day;
	}
	
	public static int func2() throws IOException {
		//입출력
		String input = br.readLine();
		String[] inputs = input.split(" ");
		int A = Integer.parseInt(inputs[0]);
		int B = Integer.parseInt(inputs[1]);
		int V = Integer.parseInt(inputs[2]);
		//로직
		V -= A;
		int day = (int)Math.ceil((double)V / (A-B)) + 1;
		return day;
	}
	
	public static void main(String[] args) throws IOException {
		int result = func2();
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		bw.write(String.valueOf(result));
		bw.flush();
	}
}
