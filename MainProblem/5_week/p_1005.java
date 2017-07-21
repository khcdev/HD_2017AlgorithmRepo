package p_1005;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class p_1005 {

	public static void main(String[] args) {

		int repetTime, buildingCount, ruleCount;
		Scanner scan = new Scanner(System.in);

		repetTime = scan.nextInt();

		for (int k = 0; k < repetTime; k++) {
			buildingCount = scan.nextInt();
			ruleCount = scan.nextInt();

			int[] buildTotalTime = new int[buildingCount + 1];
			int[] buildTime = new int[buildingCount + 1];

			for (int i = 1; i <= buildingCount; i++) {
				buildTime[i] = scan.nextInt();
				buildTotalTime[i] = -1;
			}

			// 그래프 생성

			Vertex[] vertex = new Vertex[buildingCount + 1];
			for (int i = 1; i < vertex.length; i++) {
				vertex[i] = new Vertex();
				vertex[i].data = i;
			}

			for (int i = 1; i <= ruleCount; i++) {
				int t1, t2;
				t1 = scan.nextInt();
				t2 = scan.nextInt();
				vertex[t2].linked.add(t1); // 뒤집에서 넣기
			}

			int targetBuilding;
			targetBuilding = scan.nextInt();

			// 최소시간 출력하기

			Queue<Vertex> queue = new LinkedList<Vertex>();
			queue.offer(vertex[targetBuilding]);
			vertex[targetBuilding].visited = true;
			buildTotalTime[targetBuilding] = buildTime[targetBuilding];
			int biggest =0;

			while (!queue.isEmpty()) {
				Vertex temp = queue.poll();

				// 그래프의 종단점
				if (temp.linked.size() == 0) {
					biggest = buildTotalTime[temp.data];
					continue;
				}

				// 그래프의 연결점 부분
				for (int i = 0; i < temp.linked.size(); i++) {

					queue.offer(vertex[temp.linked.get(i)]);
					vertex[temp.linked.get(i)].visited = true;
					if (buildTotalTime[temp.linked.get(i)] < buildTotalTime[temp.data]
							+ buildTime[temp.linked.get(i)]) {
						buildTotalTime[temp.linked.get(i)] = buildTotalTime[temp.data] + buildTime[temp.linked.get(i)];
					}

				}

			}
			
			
			for(int i=1; i<=buildingCount;i++)
			{
				if(vertex[i].visited == true && vertex[i].linked.size() == 0)
				{
					if(biggest < buildTotalTime[i]) {
						biggest = buildTotalTime[i];
					}
				}
			}
			System.out.println(biggest);

		}
	}

}

class Vertex {
	int data;
	boolean visited = false;
	ArrayList<Integer> linked = new ArrayList();

}