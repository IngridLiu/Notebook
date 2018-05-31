package GeneticTSP;

import java.util.Random;

/**
 * 个体类
 * 包含：
 * 		1.createByRandomGenes 初始个体基因(随机) 基因直接用城市序列编码
 * 		2.calFitness 计算个体适应度
 * 		3.printRate 打印路径
 */

public class SpeciesIndividual {
	
	String[] genes;//基因序列
	float distance;//路程
	float fitness;//适应度
	SpeciesIndividual next; //next指针
	float rate;
	
	SpeciesIndividual()
	{
		//初始化
		this.genes=new String[TSPData.CITY_NUM];
		this.fitness=0.0f;
		this.distance=0.0f;
		this.next=null;
		rate=0.0f;
	}
	
	//初始个体基因(随机)
	void createByRandomGenes()
	{
		//初始化基因为1-CITY_NUM序列
		for(int i = 0;i < genes.length;i++)
		{
			genes[i]=Integer.toString(i+1);
		}
		
		//获取随机种子
		Random rand=new Random();

		for(int j=0;j<genes.length;j++)
		{
			int num= j + rand.nextInt(genes.length-j); //nextInt(n)将返回一个大于等于0小于n的随机数，即：0 <= nextInt(n) < n。 
			
			//交换
			String tmp;
			tmp=genes[num];
			genes[num]=genes[j];
			genes[j]=tmp;
		}
	}
	
	
	//计算个体适应度
	void calFitness()
	{
		float totalDis=0.0f;
		for(int i = 0;i < TSPData.CITY_NUM;i++)
		{
			int curCity=Integer.parseInt(this.genes[i])-1;
			int nextCity=Integer.parseInt(this.genes[(i+1) % TSPData.CITY_NUM])-1;

			totalDis += TSPData.disMap[curCity][nextCity];
		}
		
		this.distance=totalDis;
		this.fitness=1.0f/totalDis;
	}
	
	//深拷贝
	public SpeciesIndividual clone()
	{	
		SpeciesIndividual species=new SpeciesIndividual();
		
		//复制值
		for(int i=0;i<this.genes.length;i++)
			species.genes[i]=this.genes[i];
		species.distance=this.distance;
		species.fitness=this.fitness;
	
		return species;	
	}
	
	//打印路径
	void printRate()
	{
		System.out.print("最短路线：");
		for(int i=0;i<genes.length;i++)
			System.out.print(genes[i]+"->");
		System.out.print(genes[0]+"\n");
		System.out.print("最短长度：" + distance);
	}

}
