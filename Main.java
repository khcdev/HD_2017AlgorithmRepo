package p_2667;

import java.util.*;

public class Main {

	public static void main(String[] args) {
		
		int row;
		Scanner scan = new Scanner(System.in);
		String temp = new String();
		
		//마을 만들기
		row = scan.nextInt();scan.nextLine();
		int[][] town = new  int[row][row];
		
		for(int i=0; i<row; i++)
		{
			
			temp = scan.nextLine();
			
			for(int j=0; j<row; j++)
			{
				town[i][j] = temp.charAt(j)-'0';
			}
		}
		
		ArrayList<Integer> arr = new ArrayList<Integer>();
		int count = 1;
		for(int i=0; i<row; i++)
		{
			for(int j=0; j<row; j++)
			{
				if(town[i][j] == 1)
				{
					count = 1;
					Queue<Vertex> que = new LinkedList<Vertex>();
					que.offer(new Vertex(i,j));
					town[i][j] = 2;
					
					while(!que.isEmpty())
					{
						Vertex tempV = que.poll();
						
						if(tempV.i>0)  //위
						{
							if(town[tempV.i-1][tempV.j] == 1)
							{
								que.offer(new Vertex(tempV.i-1,tempV.j));
								town[tempV.i-1][tempV.j] = 2;
								count++;
							}
						}
						
						if(tempV.j<row-1)  // 오른쪽
						{
							if(town[tempV.i][tempV.j+1] == 1)
							{
								que.offer(new Vertex(tempV.i,tempV.j+1));
								town[tempV.i][tempV.j+1] = 2;
								count++;
							}
						}
						
						if(tempV.i<row-1)  //아래
						{
							if(town[tempV.i+1][tempV.j] == 1)
							{
								que.offer(new Vertex(tempV.i+1,tempV.j));
								town[tempV.i+1][tempV.j] = 2;
								count++;
							}
						}
						
						if(tempV.j>0)  //왼쪽
						{
							if(town[tempV.i][tempV.j-1] == 1)
							{
								que.offer(new Vertex(tempV.i,tempV.j-1));
								town[tempV.i][tempV.j-1] = 2;
								count++;
							}
						}
												
					}
					arr.add(count);
				}	
				
			}
		}
		
		
		System.out.println(arr.size());
		
		Collections.sort(arr);
		
		for(int i=0; i<arr.size(); i++)
			System.out.println(arr.get(i));
		


	}

}

class Vertex{
	int i,j;
	int data;
	boolean visited = false;
	
	Vertex(int _i, int _j)
	{
		i = _i;
		j = _j;
	}
}



