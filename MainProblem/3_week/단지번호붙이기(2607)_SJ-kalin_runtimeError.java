package test;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Scanner;
import java.util.Stack;

class Location {
	private int x;
	private int y;

	public int getX() {
		return x;
	}

	public int getY() {
		return y;
	}

	public Location() {
		this(0, 0);
	}

	Location(int x, int y) {
		this.x = x;
		this.y = y;
	}
}

public class Main {

	static int matrix[][];
	static ArrayList<Location> nodeList = new ArrayList<>();

	public static void main(String[] args) {
		System.out.println(1);
		ArrayList<Stack<Location>> stacklist = new ArrayList<>();
		Stack<Location> firstStack = new Stack<>();

		int count = 0;
		int arr[];
		Scanner scan = new Scanner(System.in);
		Scanner scanner = new Scanner(System.in);

		count = scan.nextInt();
		matrix = new int[count][count];
		for (int i = 0; i < count; i++) {
			char [] line = scanner.next().toCharArray();
			for (int j = 0; j < count; j++) {
				matrix[i][j] = Character.getNumericValue(line[j]);
				if (matrix[i][j] == 1) {
					nodeList.add(new Location(i, j));
				}
			}
		}
//		
//		for (int i = 0; i < count; i++) {
//			String temp = scanner.nextLine();
//			for (int j = 0; j < count; j++) {
//				String a = temp.substring(j, j + 1);
//				matrix[i][j] = Integer.parseInt(a);
//				if (matrix[i][j] == 1) {
//					nodeList.add(new Location(i, j));
//				}
//			}
//		}
//
		while (!nodeList.isEmpty()) {

			Location temp = nodeList.get(0);
			nodeList.remove(0);
			firstStack.push(temp);
			Stack<Location> secondStack = new Stack<>();

			while (!firstStack.isEmpty()) {

				Location temp2 = firstStack.pop();
				if (findUp(temp2)) {
					firstStack.push(new Location(temp2.getX(), temp2.getY() - 1));
					delete(temp2, 0, -1);
				}
				if (findDown(temp2)) {
					firstStack.push(new Location(temp2.getX(), temp2.getY() + 1));
					delete(temp2, 0, 1);
				}
				if (findLeft(temp2)) {
					firstStack.push(new Location(temp2.getX() - 1, temp2.getY()));
					delete(temp2, -1, 0);
				}
				if (findRight(temp2)) {
					firstStack.push(new Location(temp2.getX() + 1, temp.getY()));
					delete(temp2, 1, 0);
				}
				secondStack.push(temp2);
			}
			stacklist.add(secondStack);
			secondStack.empty();
		}

		arr = new int[stacklist.size()];
		for (int i = 0; i < stacklist.size(); i++) {
			arr[i] = stacklist.get(i).size();
		}
		Arrays.sort(arr);
		System.out.print(stacklist.size());
		for (int i = 0; i < stacklist.size(); i++) {
			System.out.println();
			System.out.print(arr[i]);
		}
		scan.close();
		scanner.close();
	}

	public static void delete(Location temp, int x, int y) {
		for (int i = 0; i < nodeList.size(); i++) {
			if (nodeList.get(i).getX() == temp.getX() + x && nodeList.get(i).getY() == temp.getY() + y) {
				nodeList.remove(i);
				break;
			}
		}
	}

	private static boolean findLeft(Location temp) {
		if (temp.getX() == 0) {
			return false;
		}

		for (int i = 0; i < nodeList.size(); i++) {
			if (temp.getX() - 1 == nodeList.get(i).getX() && temp.getY() == nodeList.get(i).getY()) {
				return true;
			}
		}

		return false;
	}

	private static boolean findDown(Location temp) {
		if (temp.getY() == matrix.length - 1) {
			return false;
		}

		for (int i = 0; i < nodeList.size(); i++) {
			if (temp.getX() == nodeList.get(i).getX() && temp.getY() + 1 == nodeList.get(i).getY()) {
				return true;
			}
		}

		return false;
	}

	private static boolean findRight(Location temp) {
		if (temp.getX() == matrix.length - 1) {
			return false;
		}

		for (int i = 0; i < nodeList.size(); i++) {
			if (temp.getX() + 1 == nodeList.get(i).getX() && temp.getY() == nodeList.get(i).getY()) {
				return true;
			}
		}

		return false;
	}

	private static boolean findUp(Location temp) {
		if (temp.getY() == 0) {
			return false;
		}

		for (int i = 0; i < nodeList.size(); i++) {
			if (temp.getX() == nodeList.get(i).getX() && temp.getY() - 1 == nodeList.get(i).getY()) {
				return true;
			}
		}

		return false;
	}

}
