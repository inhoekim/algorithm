import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.Scanner;

public class Main {
	public static BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
	public static String recurStr = "\"재귀함수가 뭔가요?\"\n"
			+ "\"잘 들어보게. 옛날옛날 한 산 꼭대기에 이세상 모든 지식을 통달한 선인이 있었어.\n"
			+ "마을 사람들은 모두 그 선인에게 수많은 질문을 했고, 모두 지혜롭게 대답해 주었지.\n"
			+ "그의 답은 대부분 옳았다고 하네. 그런데 어느 날, 그 선인에게 한 선비가 찾아와서 물었어.\"\n";
	
	public static void main(String[] args) throws IOException {
		Scanner sc = new Scanner(System.in);
		int target = sc.nextInt();
		System.out.println("어느 한 컴퓨터공학과 학생이 유명한 교수님을 찾아가 물었다.");
		recursive(target, 0);
	}
	
	public static void recursive(int target, int curr) throws IOException {
		String dash = "";
		for(int i=0; i < curr; i++) dash += "____";
		bw.write(dash+"\"재귀함수가 뭔가요?\"\n");
		if(target==curr) {
			bw.write(dash+"\"재귀함수는 자기 자신을 호출하는 함수라네\"\n");
			bw.write(dash+"라고 답변하였지.\n");
			return;
		}
		else {
			bw.write(dash+"\"잘 들어보게. 옛날옛날 한 산 꼭대기에 이세상 모든 지식을 통달한 선인이 있었어.\n");
			bw.write(dash+"마을 사람들은 모두 그 선인에게 수많은 질문을 했고, 모두 지혜롭게 대답해 주었지.\n");
			bw.write(dash+"그의 답은 대부분 옳았다고 하네. 그런데 어느 날, 그 선인에게 한 선비가 찾아와서 물었어.\"\n");
		}
		recursive(target, ++curr);
		bw.write(dash+"라고 답변하였지.\n");
		bw.flush();
	}
}
