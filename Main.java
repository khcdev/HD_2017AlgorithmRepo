package p_7576;

import java.util.*;

public class Main {

	public static void main(String[] args) {
		int row, col;
		Scanner scan = new Scanner(System.in);
		int rt=0,nt=0, ut=0; // 익은 토마토 , 토마토 없음, 익지않은 토마토
		Queue<Vertex> queue = new LinkedList<Vertex>();
		
		
		// 토마트 박스에 넣기
		row = scan.nextInt();
		col = scan.nextInt();

		int[][] box = new int[col][row];
		
		for(int i=0; i<col; i++)
		{
			for(int j=0; j<row; j++)
			{
				box[i][j] = scan.nextInt();
				if(box[i][j] == 1)
				{
					rt++;
					queue.offer(new Vertex(j,i));
				}else if(box[i][j] == 0)
				{
					ut++;
				}else {
					nt++;
				}
			}
		}
		
		
		if(rt+nt == row*col) // 익은 토마토가 가득차있는 경우
		{
			System.out.println(0);
			return;
		}else if(nt+ut == row*col) // 익은 토마토가 하나도 없는 경우 & 토마토가 한개도 없는 경우
		{
			System.out.println(-1);
			return;
		}
		
		
		//
		int count = -1;
		int check = rt;
		int addRt = 0;
		
		while(!queue.isEmpty())
		{
			Vertex temp = queue.poll();	
			check--;
			
			if(temp.visited == false)
			{
				if(temp.Ctemp > 0) // 위
				{
					if(box[temp.Ctemp-1][temp.Rtemp] == 0) {
					rt++;
					box[temp.Ctemp-1][temp.Rtemp] = 1;
					queue.offer(new Vertex(temp.Rtemp,temp.Ctemp-1));
					addRt++;
					}
				}
				if(temp.Rtemp < row-1 ) // 오른쪽
				{
					if(box[temp.Ctemp][temp.Rtemp+1] == 0) {
					rt++;
					box[temp.Ctemp] [temp.Rtemp+1]= 1;
					queue.offer(new Vertex(temp.Rtemp+1,temp.Ctemp));
					addRt++;
					}
				}
				if(temp.Ctemp < col-1 ) //아래
				{
					if(box[temp.Ctemp+1][temp.Rtemp] == 0)
					{
					rt++;
					box[temp.Ctemp+1] [temp.Rtemp]= 1;
					queue.offer(new Vertex(temp.Rtemp,temp.Ctemp+1));
					addRt++;
					}
				}
				if(temp.Rtemp > 0 ) // 왼쪽
				{
					if( box[temp.Ctemp][temp.Rtemp-1] == 0) 
					{
					rt++;
					box[temp.Ctemp][temp.Rtemp-1] = 1;
					queue.offer(new Vertex(temp.Rtemp-1,temp.Ctemp));
					addRt++;
					}
				}				
				
				temp.visited = true;
				
				if(check == 0)
				{
					check = addRt;
					addRt =0;
					count++;
				}
			}			
			
		}
		
		if(rt + nt < row * col)
		{
			System.out.println(-1);
			return;
		}
		
		System.out.println(count);

	}

}

class Vertex{
	int Rtemp, Ctemp;
	int data;
	boolean visited = false;
	
	Vertex(int row, int col)
	{
		Rtemp = row;
		Ctemp = col;
	}
}
