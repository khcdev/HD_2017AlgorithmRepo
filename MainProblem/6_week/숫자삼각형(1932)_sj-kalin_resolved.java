package test;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Scanner;

class Test {

	//갯수
	static int count;
	//각 행을 hash로 hash안의 값은 arraylist로 설정한다.
	static HashMap<Integer, ArrayList<Tree>> hashMap = new HashMap<>();

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		count = scan.nextInt();

		for (int i = 0; i < count; i++) {
			ArrayList<Tree> arrayList = new ArrayList<>();
			for (int j = 0; j <= i; j++) {
				int temp = scan.nextInt();
				arrayList.add(new Tree(i, j, temp));
			}
			if (!hashMap.containsKey(i)) {
				hashMap.put(i, arrayList);
			}
		}
		
		///hash안에 제대로 값이 입력됐는지 확인
		// for (int i = 0; i < hashMap.size(); i++) {
		// for (int j = 0; j < hashMap.get(i).size(); j++) {
		// System.out.println(hashMap.get(i).get(j).toString());
		// }
		// }

		for (int i = count - 2; i >= 0; i--) {
			for (int j = 0; j < hashMap.get(i).size(); j++) {
				findMax(i, j);
			}
			// System.out.println(hashMap.get(i).toString());
		}
		// 출력한다.
		System.out.println(hashMap.get(0).get(0).value);
	}

	// 각각의 최적 값으로 행렬을 교체한다.
	private static void findMax(int i, int j) {

		hashMap.get(i).get(j).value = hashMap.get(i + 1).get(j).value > hashMap.get(i + 1).get(j + 1).value
				? hashMap.get(i).get(j).value + hashMap.get(i + 1).get(j).value
				: hashMap.get(i).get(j).value + hashMap.get(i + 1).get(j + 1).value;

	}
}

// 행렬을 리스트로 구현하기 위한 클래스이다.
class Tree {
	int x;
	int y;
	int value;

	public Tree(int x, int y, int value) {
		super();
		this.x = x;
		this.y = y;
		this.value = value;
	}

	@Override
	public String toString() {
		return "Tree [x=" + x + ", y=" + y + ", value=" + value + "]";
	}

}