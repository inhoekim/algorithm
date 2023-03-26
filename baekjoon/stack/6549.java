import java.util.*;
import java.io.*;

public class Anything {
	public static void main(String[] argv) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n;
		long pop_cnt, ret;
		while (true) {
			//입출력 Part
			StringTokenizer st = new StringTokenizer(br.readLine(), " ");
			n = Integer.parseInt(st.nextToken());
			if (n == 0)
				break ;
			//본로직 Part
			Stack<Rectangle> stack = new Stack<>();
			ret = 0;
			while (st.hasMoreTokens()){
				Rectangle current_rtg = new Rectangle(Integer.parseInt(st.nextToken()), 1);
				pop_cnt = 0;
				//현재 사각형의 앞에 있는 사각형의 높이가 현재 사각형과 같다 -> 하나의 사각형으로 압축
				//현재 사각형의 앞에 있는 사각형의 높이가 현재 사각형보다 높다 -> 더이상 앞의 사각형은 뒤에 나오는 사각형들을 최대값 계산 시에 포함시킬 수 없음. 따라서 그냥 pop시킴.
				while (!stack.isEmpty() && stack.peek().height >= current_rtg.height){
					Rectangle front_rtg = stack.pop();
					pop_cnt += front_rtg.width;
					ret = Math.max(ret, pop_cnt * front_rtg.height);
				}
				current_rtg.setWidth(pop_cnt + current_rtg.width);
				stack.add(current_rtg);
			}
			//현재 스택에 남아있는 상자는 높이 별 오름차순이므로 하나씩 팝해보면서 가장 큰 직사각형이 있는 지 경우의 수 계산
			pop_cnt = 0;
			while (!stack.isEmpty()){
				Rectangle rtg = stack.pop();
				pop_cnt += rtg.width;
				ret = Math.max(ret, pop_cnt * rtg.height);
			}
			System.out.println(ret);
		}
	}
}

class Rectangle{
	long height, width;

	public Rectangle(long height, long width){
		this.height = height;
		this.width = width;
	}

	public void setWidth(long width) {
		this.width = width;
	}
}
