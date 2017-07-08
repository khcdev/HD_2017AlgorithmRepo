package p_7576;

import java.util.*;

public class Main {

	public static void main(String[] args) {
		int row, col;
		Scanner scan = new Scanner(System.in);
		int rt=0,nt=0, ut=0; // ���� �丶�� , �丶�� ����, �������� �丶��
		Queue<Vertex> queue = new LinkedList<Vertex>();
		
		
		// �丶Ʈ �ڽ��� �ֱ�
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
		
		
		if(rt+nt == row*col) // ���� �丶�䰡 �������ִ� ���
		{
			System.out.println(0);
			return;
		}else if(nt+ut == row*col) // ���� �丶�䰡 �ϳ��� ���� ��� & �丶�䰡 �Ѱ��� ���� ���
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
				if(temp.Ctemp > 0) // ��
				{
					if(box[temp.Ctemp-1][temp.Rtemp] == 0) {
					rt++;
					box[temp.Ctemp-1][temp.Rtemp] = 1;
					queue.offer(new Vertex(temp.Rtemp,temp.Ctemp-1));
					addRt++;
					}
				}
				if(temp.Rtemp < row-1 ) // ������
				{
					if(box[temp.Ctemp][temp.Rtemp+1] == 0) {
					rt++;
					box[temp.Ctemp] [temp.Rtemp+1]= 1;
					queue.offer(new Vertex(temp.Rtemp+1,temp.Ctemp));
					addRt++;
					}
				}
				if(temp.Ctemp < col-1 ) //�Ʒ�
				{
					if(box[temp.Ctemp+1][temp.Rtemp] == 0)
					{
					rt++;
					box[temp.Ctemp+1] [temp.Rtemp]= 1;
					queue.offer(new Vertex(temp.Rtemp,temp.Ctemp+1));
					addRt++;
					}
				}
				if(temp.Rtemp > 0 ) // ����
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
