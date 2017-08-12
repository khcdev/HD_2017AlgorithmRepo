package test;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

public class TestSe {

	static HashMap<Integer, DataSet> graphMap;
	static ArrayList<Sleep> arrayList;
	static int TestCase;
	static int buildingCount;
	static int edge;
	static int Target;
	static int sum[];

	public static void main(String[] args) {

		Scanner scan = new Scanner(System.in);
		TestCase = scan.nextInt();
		sum = new int[TestCase];

		for (int l = 0; l < TestCase; l++) {
			init();// 초기화

			buildingCount = scan.nextInt();
			edge = scan.nextInt();

			// 건물의 실행 시간을 저장한다.
			for (int i = 0; i < buildingCount; i++) {
				DataSet dataSet = new DataSet();
				graphMap.put(i, dataSet);
				graphMap.get(i).Time = scan.nextInt();
			}

			for (int i = 0; i < edge; i++) {

				int xTemp = scan.nextInt() - 1;
				int yTemp = scan.nextInt() - 1;

				graphMap.get(xTemp).arrayList.add(new Vertax(xTemp, yTemp));
			}

			// 진입 차수를 계산한다.

			findEdgeList();

			Target = scan.nextInt() - 1;

			while (graphMap.get(Target).insertion != 0) {

				ArrayList<Integer> node = new ArrayList<>();
				for (int i = 0; i < graphMap.size(); i++) {
					if (graphMap.get(i).flag != 0 && graphMap.get(i).insertion == 0) {
						node.add(i);
					}
				}
				int temp = 0;
				for (int i = 0; i < node.size(); i++) {
					temp = (temp > graphMap.get(node.get(i)).Time) ? temp : graphMap.get(node.get(i)).Time;
				}

				for (int i = 0; i < node.size(); i++) {
					graphMap.get(node.get(i)).flag = 0;
				}
				arrayList.add(new Sleep(node, temp));

				findEdgeList();

			}
			int tempSum = 0;
			for (int i = 0; i < arrayList.size(); i++) {
				tempSum += arrayList.get(i).Time;
			}
			tempSum += graphMap.get(Target).Time;
			sum[l] = tempSum;
		}

		for (int i = 0; i < TestCase; i++) {
			System.out.println(sum[i]);
		}
	}

	private static void findEdgeList() {

		for (int i = 0; i < graphMap.size(); i++) {
			for (int j = 0; j < graphMap.get(i).arrayList.size(); j++) {
				graphMap.get(graphMap.get(i).arrayList.get(j).to).insertion = 0;
			}
		}

		for (int i = 0; i < graphMap.size(); i++) {
			if (graphMap.get(i).flag != 0)
				for (int j = 0; j < graphMap.get(i).arrayList.size(); j++) {
					graphMap.get(graphMap.get(i).arrayList.get(j).to).insertion++;
				}
		}
		
		System.out.println("-----------------");
		for (int i = 0; i < graphMap.size(); i++) {
			System.out.print(graphMap.get(i).insertion);
		}
		System.out.println("=================");

	}

	private static void init() {
		graphMap = new HashMap<>();
		arrayList = new ArrayList<>();
		buildingCount = 0;
		edge = 0;
		Target = 0;
	}

}

class DataSet {
	ArrayList<Vertax> arrayList = new ArrayList<>();
	int insertion;
	int Time;
	int flag = 1;

	DataSet() {

	}

	public DataSet(ArrayList<Vertax> arrayList, int time) {
		super();
		this.arrayList = arrayList;
		Time = time;
	}

	@Override
	public String toString() {
		return "DataSet [arrayList=" + arrayList + ", insertion=" + insertion + ", Time=" + Time + "]";
	}

}

class Vertax {

	int from;
	int to;

	public Vertax(int from, int to) {
		this.from = from;
		this.to = to;
	}

	@Override
	public String toString() {
		return "Vertax [from=" + from + ", to=" + to + "]";
	}

}

class Sleep {
	ArrayList<Integer> arrayList = new ArrayList<>();
	int Time;

	public Sleep(ArrayList<Integer> arrayList, int time) {
		super();
		this.arrayList = arrayList;
		Time = time;
	}
}
