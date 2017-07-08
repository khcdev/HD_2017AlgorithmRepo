package p_2606;

import java.util.*;

public class p_2606 {

	public static void main(String[] args) {
		int vCount;
		int eCount;
		int count =0;		
		Scanner scan = new Scanner(System.in);		
				
		vCount = scan.nextInt();
		eCount = scan.nextInt();
		
		
		// 그래프 생성
		
		Vertex[] vertex= new Vertex[vCount+1];
		for(int i=1;i<vertex.length; i++) {
			vertex[i] = new Vertex();
			vertex[i].data = i;
		}
		

		for(int i =1; i<=eCount; i++){
			int t1, t2;
			t1 = scan.nextInt();
			t2 = scan.nextInt();
			
			vertex[t1].linked.add(t2);
			vertex[t2].linked.add(t1);		
		}
		
		// find
		Queue<Vertex> queue = new LinkedList<Vertex>();
		queue.offer(vertex[1]);
		vertex[1].visited = true;
		
		while(!queue.isEmpty())
		{
			Vertex temp = queue.poll();
			count++;
			
			if(temp.visited == true) 
			{
				for(int i =0; i<temp.linked.size(); i++) {
					if(vertex[temp.linked.get(i)].visited == false)
					{
						queue.offer(vertex[temp.linked.get(i)]);
						vertex[temp.linked.get(i)].visited = true;
					}
				}
		
			}
		
			
		}
		
		System.out.println(count-1);

	}
}

class Vertex{
	int data;
	boolean visited = false;
	ArrayList<Integer> linked = new ArrayList();
	
}




