package GeneticTSP;

import java.util.Random;

/**
 * 遗传算法类
 * 包含：
 * 		1.run 开始跑算法
 * 		2.createBeginningSpecies 创建种群
 * 		3.calRate 计算每一种物种被选中的概率
 *      4.select  轮盘策略 选择适应度高的物种
 *      5.crossover 染色体交叉
 *      6.mutate 染色体变异
 *      7.getBest 获得适应度最大的物种
 */

public class GeneticAlgorithm {
	
	
		
	    //开始遗传
		SpeciesIndividual run(SpeciesPopulation Population)
		{
			SpeciesIndividual bestIndividual;
			
			//创建初始种群
			createBeginningSpecies(Population);
			
			for(int i=1;i<=TSPData.DEVELOP_NUM;i++)
			{
				//选择
				select(Population);
				
				//交叉
				crossover(Population);
				
				//变异
				mutate(Population);
				
				System.out.print("\n----------第  " +i );
				System.out.print(" 代物种----------\n");
				bestIndividual = getBest(Population);
				bestIndividual.printRate();
				
			}	
			
			return getBest(Population);
		}
		
		//创建初始种群
		void createBeginningSpecies(SpeciesPopulation Population)
		{
			//100%随机
			int randomNum=(int)(TSPData.SPECIES_NUM);
			for(int i=1;i<=randomNum;i++)
			{
				SpeciesIndividual species=new SpeciesIndividual();//创建结点
				species.createByRandomGenes();//初始种群基因

				Population.add(species);//添加物种
			}
			
		}

		//计算每一物种被选中的概率
		void calRate(SpeciesPopulation Population)
		{
			//计算总适应度
			float totalFitness=0.0f;
			Population.individualNum=0;
			SpeciesIndividual point=Population.head.next;//游标
			while(point != null)//寻找表尾结点
			{
				point.calFitness();//计算适应度
				
				totalFitness += point.fitness;
				Population.individualNum++;

				point=point.next;
			}

			//计算选中概率
			point=Population.head.next;//游标
			while(point != null)//寻找表尾结点
			{
				point.rate=point.fitness/totalFitness;
				point=point.next;
			}
		}
		
		//选择优秀物种（轮盘赌）
		void select(SpeciesPopulation Population)
		{			
			//计算适应度
			calRate(Population);
			
			//找出最大适应度物种
			float talentDis=Float.MAX_VALUE;
			SpeciesIndividual talentSpecies=null;
			SpeciesIndividual point=Population.head.next;//游标

			while(point!=null)
			{
				if(talentDis > point.distance)
				{
					talentDis=point.distance;
					talentSpecies=point;
				}
				point=point.next;
			}

			//将最大适应度物种复制talentNum个
			SpeciesPopulation newSpeciesPopulation=new SpeciesPopulation();
			int talentNum=(int)(Population.individualNum/4);
			for(int i=1;i<=talentNum;i++)
			{
				//复制物种至新表
				SpeciesIndividual newSpecies=talentSpecies.clone();
				newSpeciesPopulation.add(newSpecies);
			}

			//轮盘赌Population.speciesNum-talentNum次
			int roundNum=Population.individualNum-talentNum;
			for(int i=1;i<=roundNum;i++)
			{
				//产生0-1的概率
				float rate=(float)Math.random();
				
				SpeciesIndividual oldPoint=Population.head.next;//游标
				while(oldPoint != null && oldPoint != talentSpecies)//寻找表尾结点
				{
					if(rate <= oldPoint.rate)
					{
						SpeciesIndividual newSpecies=oldPoint.clone();
						newSpeciesPopulation.add(newSpecies);
						
						break;
					}
					else
					{
						rate=rate-oldPoint.rate;
					}
					oldPoint=oldPoint.next;
				}
				if(oldPoint == null || oldPoint == talentSpecies)
				{
					//复制最后一个
					point=Population.head;//游标
					while(point.next != null)//寻找表尾结点
						point=point.next;
					SpeciesIndividual newSpecies=point.clone();
					newSpeciesPopulation.add(newSpecies);
				}
				
			}
			Population.head=newSpeciesPopulation.head;
		}
		
		//交叉操作
		void crossover(SpeciesPopulation Population)
		{
			//以概率pcl~pch进行
			float rate=(float)Math.random();
			if(rate > TSPData.pcl && rate < TSPData.pch)
			{			
				SpeciesIndividual point=Population.head.next;//游标
				Random rand=new Random();
				int find=rand.nextInt(Population.individualNum);
				while(point != null && find != 0)//寻找表尾结点
				{
					point=point.next;
					find--;
				}
			
				if(point.next != null)
				{
					int begin=rand.nextInt(TSPData.CITY_NUM);

					//取point和point.next进行交叉，形成新的两个染色体
					for(int i=begin;i<TSPData.CITY_NUM;i++)
					{
						//找出point.genes中与point.next.genes[i]相等的位置fir
						//找出point.next.genes中与point.genes[i]相等的位置sec
						int fir,sec;
						for(fir=0;!point.genes[fir].equals(point.next.genes[i]);fir++);
						for(sec=0;!point.next.genes[sec].equals(point.genes[i]);sec++);
						//两个基因互换
						String tmp;
						tmp=point.genes[i];
						point.genes[i]=point.next.genes[i];
						point.next.genes[i]=tmp;
						
						//消去互换后重复的那个基因
						point.genes[fir]=point.next.genes[i];
						point.next.genes[sec]=point.genes[i];
						
					}
				}
			}
		}
		
		//变异操作
		void mutate(SpeciesPopulation Population)
		{	
			//每一物种均有变异的机会,以概率pm进行
			SpeciesIndividual point=Population.head.next;
			while(point != null)
			{
				float rate=(float)Math.random();
				if(rate < TSPData.pm)
				{
					//寻找逆转左右端点
					Random rand=new Random();
					int left=rand.nextInt(TSPData.CITY_NUM);
					int right=rand.nextInt(TSPData.CITY_NUM);
					if(left > right)
					{
						int tmp;
						tmp=left;
						left=right;
						right=tmp;
					}
					
					//逆转left-right下标元素
					while(left < right)
					{
						String tmp;
						tmp=point.genes[left];
						point.genes[left]=point.genes[right];
						point.genes[right]=tmp;

						left++;
						right--;
					}
				}
				point=point.next;
			}
		}

		//获得适应度最大的物种
		SpeciesIndividual getBest(SpeciesPopulation list)
		{
			float distance=Float.MAX_VALUE;
			SpeciesIndividual bestSpecies=null;
			SpeciesIndividual point=list.head.next;//游标
			while(point != null)//寻找表尾结点
			{
				if(distance > point.distance)
				{
					bestSpecies=point;
					distance=point.distance;
				}

				point=point.next;
			}
			
			return bestSpecies;
		}

}
