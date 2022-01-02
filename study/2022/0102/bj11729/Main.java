import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.math.BigInteger;
import java.util.Scanner;

public class Main {
	private static StringBuilder sb = new StringBuilder();
	private static BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	private static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	//private static int cnt = 0; (시간초과..)
	
	public static void main(String[] args) throws IOException {
		int N = Integer.parseInt(br.readLine());
		//bw.write(Integer.toString(cnt) + "\n");
		BigInteger cnt = new BigInteger("2");
		cnt = cnt.pow(N);
		cnt = cnt.subtract(new BigInteger("1"));
		bw.write(cnt.toString() + "\n");
		if(N <= 20) {
			recurse(N,1,3);
			bw.write(sb.toString());
		}
		bw.flush();
		bw.close();
	}
	
	public static void recurse(int block, int from, int to) {
		if(block == 1) {
			//cnt++;
			sb.append(from + " " + to + "\n");
			return;
		}
		
		int middle = 6 - from - to;
				
		recurse(block - 1, from, middle); 
		recurse(1,from,to);
		recurse(block-1,middle,to);
	}
}
