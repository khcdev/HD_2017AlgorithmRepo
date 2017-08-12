package test;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Scanner;

class Test {

	//����
	static int count;
	//�� ���� hash�� hash���� ���� arraylist�� �����Ѵ�.
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
		
		///hash�ȿ� ����� ���� �Էµƴ��� Ȯ��
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
		// ����Ѵ�.
		System.out.println(hashMap.get(0).get(0).value);
	}

	// ������ ���� ������ ����� ��ü�Ѵ�.
	private static void findMax(int i, int j) {

		hashMap.get(i).get(j).value = hashMap.get(i + 1).get(j).value > hashMap.get(i + 1).get(j + 1).value
				? hashMap.get(i).get(j).value + hashMap.get(i + 1).get(j).value
				: hashMap.get(i).get(j).value + hashMap.get(i + 1).get(j + 1).value;

	}
}

// ����� ����Ʈ�� �����ϱ� ���� Ŭ�����̴�.
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