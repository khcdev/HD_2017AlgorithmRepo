package test;

import java.util.ArrayList;
import java.util.Scanner;

/**
 * @author kalin
 * @date Jul 5, 2017
 * @description algo study backjun 2606 virus problem
 */
public class Main {
	// matrix for graph
	static int matrix[][];
	// list for queue
	static ArrayList<Integer> q = new ArrayList<>();
	// list for stack
	static ArrayList<Integer> s = new ArrayList<>();

	public static void main(String[] args) {

		init(); // init method
		q.add(0); // inqueue frist node which computer with virus

		// if queue is not empty, loop
		while (!q.isEmpty()) {
			int temp = q.get(0);
			q.remove(0); // dequeue

			checkMatrix(temp);
			s.add(temp); // push node

		}

		System.out.print(s.size() - 1); // print computers with virus
	}

	// checking which elements has 1.
	private static void checkMatrix(int temp) {
		for (int i = 0; i < matrix.length; i++) {
			if (matrix[temp][i] == 1) {
				if (checkQueue(i) && checkStack(i)) {
					q.add(i);
				}
			}
		}
	}

	// checking, if stack has i.
	private static boolean checkStack(int i) {
		for (int j = 0; j < s.size(); j++) {
			if (s.get(j) == i) {
				return false;
			}
		}
		return true;
	}

	// checking, if queue has i.
	private static boolean checkQueue(int i) {
		for (int j = 0; j < q.size(); j++) {
			if (q.get(j) == i) {
				return false;
			}
		}
		return true;
	}
	// init, get number of computers, lines
	static void init() {
		int computerNum = 0;
		int networkNum = 0;
		int xTemp = 0, yTemp = 0;

		Scanner scanner = new Scanner(System.in);

		computerNum = scanner.nextInt();
		matrix = new int[computerNum][computerNum];
		networkNum = scanner.nextInt();

		for (int i = 0; i < networkNum; i++) {
			xTemp = scanner.nextInt();
			yTemp = scanner.nextInt();
			matrix[xTemp - 1][yTemp - 1] = 1;
			matrix[yTemp - 1][xTemp - 1] = 1;
		}
	}

}
