package test;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Scanner;

class Main {

	static int dist[];
	final static int startNode = 0;
	static int nodeNum;
	static int lineNum;
	static final int MAX = 1000000;
	
	public static void main(String[] args) {
		HashMap<Integer, ArrayList<Node>> hashMap = new HashMap<>();
		Scanner scan = new Scanner(System.in);

		nodeNum = scan.nextInt();
		lineNum = scan.nextInt();

		dist = new int[nodeNum];
		Arrays.fill(dist, MAX);
		dist[startNode] = 0;

		for (int i = 0; i < lineNum; i++) {
			int from = scan.nextInt();
			int to = scan.nextInt();
			int value = scan.nextInt();

			if (!hashMap.containsKey(from - 1)) {
				hashMap.put(from - 1, new ArrayList<>());
			}

			hashMap.get(from - 1).add(new Node(from - 1, to - 1, value));
		} // for

		if(!hashMap.containsKey(0)){
			for(int i=1;i<dist.length;i++)
				System.out.println(-1);
			return;
		}
		
		for (int i = 0; i < dist.length; i++) {
			if (hashMap.containsKey(i)) {
				for (int j = 0; j < hashMap.get(i).size(); j++) {
					int value = hashMap.get(i).get(j).value;
					int to = hashMap.get(i).get(j).to;
					int from = hashMap.get(i).get(j).from;

					if (dist[from] + value < 0) {
						System.out.println(-1);
						return;
					} else if (dist[to] >= dist[from] + value) {
						dist[to] = dist[from] + value;
					}
				}
			}
		} // 2-for

		for (int i = 1; i < dist.length; i++) {
			if (dist[i] == MAX) {
				System.out.println(-1);
			} else {
				System.out.println(dist[i]);
			}
		}

	}// main
}

class Node {

	int from;
	int to;
	int value;

	Node(int from, int to, int value) {
		this.from = from;
		this.to = to;
		this.value = value;
	}

}