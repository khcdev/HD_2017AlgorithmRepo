package p_1753;

import java.util.*;

public class p_1753 {

	public static void main(String[] args) {
		int vCount;
		int eCount;
		int count =0;	
		int stand;
		Scanner scan = new Scanner(System.in);		
				
		vCount = scan.nextInt();
		eCount = scan.nextInt();
		stand = scan.nextInt();
		
		
		// 그래프 생성
		
		Vertex[] vertex= new Vertex[vCount+1];
		for(int i=1;i<vertex.length; i++) {
			vertex[i] = new Vertex();
			vertex[i].data = i;
		}
		

		for(int i =1; i<=eCount; i++){
			int t1, t2, v;
			t1 = scan.nextInt();
			t2 = scan.nextInt();
			v = scan.nextInt();			
			
			vertex[t1].linked.add(t2);
			vertex[t1].score.add(v);
	
		}
		
		// 다익스트라 알고리즘
		
		//기본설정
		int dist[] = new int[vCount+1];
		for(int i=1; i<=vCount; i++)
			dist[i] = 100;
		dist[stand] = 0;
		
		PriorityQueue<QueueVertex> q = new <QueueVertex> PriorityQueue();
		for(int i=1; i<=vCount; i++)
		{
			q.add(new QueueVertex(i,dist[i]));
		}
		
		//거리 변경 및 확인
		while(!q.isEmpty())
		{
			QueueVertex temp = q.poll();
			
			for(int i = 0; i< vertex[temp.data].linked.size(); i++)
			{
				if(dist[vertex[temp.data].linked.get(i)]>= (vertex[temp.data].score.get(i)+dist[temp.data]))
				{
					dist[vertex[temp.data].linked.get(i)] = vertex[temp.data].score.get(i)+dist[temp.data];
					q.add(new QueueVertex(vertex[temp.data].linked.get(i),dist[vertex[temp.data].linked.get(i)]));
				}
			}
		}
		
		
		//출력
		for(int i=1; i<=vCount; i++)
		{
			if(dist[i] == 100)
			{
				System.out.println("INF");
			}
			else
			{
				System.out.println(dist[i]);
			}
		}


	}

}

class Vertex{
	int data;
	boolean visited = false;
	ArrayList<Integer> linked = new ArrayList();
	ArrayList<Integer> score = new ArrayList();
	
}

class QueueVertex implements Comparable<QueueVertex>{	
	int distance;
	int data;

	QueueVertex(int _data, int _distance){
		data = _data;
		distance = _distance;
	}

	@Override
	public int compareTo(QueueVertex target) {
		if(this.distance >target.distance)
			return 1;
		else if(this.distance < target.distance)
			return -1;		
		return 0;
	}	
	
}