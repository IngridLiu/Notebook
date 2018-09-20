#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <utility>
#include <algorithm>
using namespace std;

// Change any of these parameters to match your needs

const int POP_SIZE = 10;            // population size(��Ⱥ��С)
const int MAXN = 751 + 2;           // no. of problem variables(�����ģ���������)
const int MAX_DIMENSION = 100009;   // max. dimension(���ά�ȼ������ģ)
const int MAX_OUTER_ITER = 50;      // max. iteration(����������)
const int MAX_INNER_ITER = 15;      // max. no. of no update(�޸Ľ�����������)
const int INF = 0x3f3f3f3f;         // max. integer



char instance[109];                        // the name of the data instance
int size;                                  // no. of the cities (excluding the depot)(���г���)
pair <int, int> points[MAX_DIMENSION];     // the coordinates of the cities(pick_up���delivery��һһ��Ӧ)
pair <int, int> node[MAXN / 2 + 1];        // the tree nodes (including a pikeup point and a delivery point)(����pick_up���delivery��һһ��Ӧ)
int nodeSize;                              // the size of the tree(���Ĵ�С)
int nodeID[MAXN];                          // the tree id of the point(���е��id)
int adj[MAXN / 2 + 1][MAXN / 2 + 1];       // linked list of the tree(���е��������ӹ�ϵ)
int deg[MAXN / 2 + 1];                     // the degree of the tree node(���е�ĳ����)
int dis[MAXN][MAXN];                       // the distance matrix(��������Ӧ�㵽��ľ���)
int other[MAXN];                           // the id of the other point in a tree node(����delivery��pick_up��Ķ�Ӧ��ϵ)
int vertexP[MAXN];                         // to record all the pickup points(��¼���е�pick_up��)
int nVertexP;                              // the no. of the pickup points(pick_up�������)
bool isVertexP[MAXN];                      // to record whether a point is a pickup point(��¼�Ƿ�Ϊpick_up��)
int startingTourCost;                      // the cost of the starting tour(��ʼ���Ŀ�꺯��ֵ)


// genotype(GT), a member of the population//
//�ṹ��genotype�洢·���滮�Ͷ�Ӧ��Ŀ�꺯��ֵ
struct Genotype {
	//·���滮
	int gene[MAXN + 2];
	//Ŀ�꺯��ֵ
	int fitness;
	
	Genotype() {}
	
	//���캯��
	Genotype(const Genotype &b) {
		memcpy(gene, b.gene, size * sizeof(int));
		fitness = b.fitness;
	}
	
	//�ض���
	void operator =(const Genotype &b) {
		memcpy(gene, b.gene, size * sizeof(int));
		fitness = b.fitness;
	}
};

Genotype population[POP_SIZE + 2];      // the current population(��ǰ�⼴��ǰ��Ⱥ)
Genotype newPopulation[POP_SIZE + 2];   // the new population(�µõ��Ľ⼴����Ⱥ)
Genotype src;                           // the starting solution(��ʼ�⼴��ʼ��Ⱥ)



// Declaration of procesdures used by this genetic algorithm

void initialize(void);
void evaluate(void);
void keepTheBest(void);
void elitist(void);
void coupleExchange(Genotype&);
void blockExchange(Genotype&);
void relocateBlock(Genotype&);
void relocateCouple(Genotype&, int, int);
void relocateCouple(Genotype&);
int calcFitness(const Genotype&);
bool check(const Genotype &);
void ATSP(Genotype &);
void RAI(Genotype &);
void localSearch(Genotype &);
Genotype crossOver(const Genotype &gt, const Genotype &gt2);

// to localSearch the current genotype.
//ʹ���������Ӷ�����genotype���оֲ�����
void localSearch(Genotype &gt) {
    coupleExchange(gt);
    relocateCouple(gt);
    blockExchange(gt);
    relocateBlock(gt);
}


// to initialize the values of all the genes.
//������gene���г�ʼ��
void initialize() {
	localSearch(src);
	ATSP(src);
	int mem, k;
	for (mem = 0; mem < POP_SIZE; ++mem) {
		population[mem] = src;
		RAI(population[mem]);
		localSearch(population[mem]);
		ATSP(population[mem]);
		newPopulation[mem] = population[mem];
	}
	for (mem = 0; mem < POP_SIZE; ++mem) {
		Genotype bestOne = population[mem], t;
		for (k = 0; k < POP_SIZE; ++k) 
			if (k != mem) {
				t = crossOver(newPopulation[mem], newPopulation[k]);
				if (t.fitness > bestOne.fitness)
					bestOne = t;
			}
			population[mem] = bestOne;
	}
}


// to compute the fitness of the genotype.
//����·���滮genotype��Ŀ�꺯��ֵ
int calcFitness(const Genotype &gt) {
	int i, fitness = 0;
	for (i = 1; i < size; ++i)
		fitness += dis[gt.gene[i - 1]][gt.gene[i]];
	fitness += dis[0][gt.gene[0]] + dis[gt.gene[size - 1]][0];
	return -fitness;
}


// to evalute the fitness of the genotype.
//���㵱ǰpopulation������genotype��Ŀ�꺯��ֵ
void evaluate() {
	for (int mem = 0; mem < POP_SIZE; ++mem)
		population[mem].fitness = calcFitness(population[mem]);
}


// to keep the best solution.
//��¼��ǰpopulation�е���ý�
void keepTheBest() {
	int mem, best = 0; // stores the index of the best individual
	
	for (mem = 1; mem < POP_SIZE; ++mem)
		if (population[mem].fitness > population[best].fitness)
			best = mem;
		population[POP_SIZE] = population[best];
}


// The best member of the previous generation
// is stored as the last in the array. If the best member of
// the current generation is worse then the best member of the
// previous generation, the latter one would replace the worst
// member of the current population.
//��һ���е���ø���洢������ĩ�ˡ�����ǰ����ø������һ���Ĳ��ǰ�������屻�����
void elitist() {
	int best, worst;
	int i, bestMem, worstMem;
	
	best = population[0].fitness;
	worst = population[0].fitness;
	bestMem = worstMem  = 0;

	//�����õ���ǰ��Ⱥ����ø����������
	for (i = 0; i < POP_SIZE - 1; ++i) {
		if (population[i].fitness > population[i + 1].fitness) {
			if (population[i].fitness >= best) {
				best = population[i].fitness;
				bestMem = i;
			}
			if (population[i + 1].fitness <= worst) {
				worst = population[i + 1].fitness;
				worstMem = i + 1;
			}
		} else {
			if (population[i].fitness <= worst) {
				worst = population[i].fitness;
				worstMem = i;
			}
			if (population[i + 1].fitness >= best) {
				best = population[i + 1].fitness;
				bestMem = i + 1;
			}
		}
	}
	
	if (best >= population[POP_SIZE].fitness) {
		population[POP_SIZE] = population[bestMem];
	} else {
		population[worstMem] = population[POP_SIZE];
	}
}


// to get the position of x+ and x-.
//�����õ�pickup��x+��delivery��x-��λ��
void getPosition(const Genotype &gt, int x, int &xl, int &xr) {
	for (int i = 0; i < size; ++i) {
		if (gt.gene[i] == x) {
			xl = i;
		} else if (gt.gene[i] == other[x]) {
			xr = i;
			//return;
		}
	}
}


// dfs to rebuild the solution.
//�����������x��λ��
void dfs(int x, int arr[], int &n) {
	int i;
	if (x != 0) arr[n++] = node[x].first;
	for (i = 0; i < deg[x]; ++i)
		dfs(adj[x][i], arr, n);
	if (x != 0) arr[n++] = node[x].second;
}


// calculate TSP according to the distance matrix dis[][]
int calcTSP(int dis[][MAXN / 2 + 1], int n, int id[], int T) {
    const int INF = 0x3f3f3f3f;
	int i, j, k, l, m, t, cur, min, pos, q[MAXN], nq, mid[MAXN], ans = INF, seq[MAXN];
	
    while (T--) {
		for (i = 0; i < n; ++i) q[i] = i;
		random_shuffle(q, q + n);
		m = 0;  nq = n;
		id[m++] = q[--nq];
		while (nq) {
			cur = q[--nq];
			for (min = INF, id[m] = id[0], i = 0; i < m; ++i) {
				t = dis[id[i]][cur] + dis[cur][id[i + 1]] - dis[id[i]][id[i + 1]];
				if (t < min) {
					min = t;
					pos = i;
				}
			}
			memmove(id + pos + 2, id + pos + 1, (m - (pos + 1) + 1) * sizeof(int));
			id[pos + 1] = cur;
			m++;
		}
        int cnt = 0;
		for (l = 0; l < n * 30; ++l) {
			i = rand() % n;
			j = rand() % n;
			if (i > j) swap(i, j);
			for (k = 0; k < n; ++k) mid[k] = id[k];
			for (nq = m = k = 0; k < n; ++k)
                if (i <= k && k <= j) q[nq++] = id[k];
                else id[m++] = id[k];
				random_shuffle(q, q + nq);
				if (m == 0) id[m++] = q[--nq];
				while (nq) {
					cur = q[--nq];
					for (min = INF, id[m] = id[0], i = 0; i < m; ++i) {
						t = dis[id[i]][cur] + dis[cur][id[i + 1]] - dis[id[i]][id[i + 1]];
						if (t < min) {
							min = t;
							pos = i;
						}
					}
					memmove(id + pos + 2, id + pos + 1, (m - (pos + 1) + 1) * sizeof(int));
					id[pos + 1] = cur;
					m++;
				}
				for (id[n] = id[0], cur = 0, i = 0; i < n; ++i)
					cur += dis[id[i]][id[i + 1]];
				if (cur < ans) {
					ans = cur;
					for (i = 0; i < n; ++i) seq[i] = id[i];
					cnt = 1;
				} else {
					++cnt;
					for (i = 0; i < n; ++i) id[i] = mid[i];
				}
				if (cnt > n * 5) break;
		}
    }
    for (i = 0; i < n; ++i)
        if (seq[i] == 0) break;
		for (pos = i, j = 0; i < n; ++i) id[j++] = seq[i];
		for (i = 0; i < pos; ++i) id[j++] = seq[i];
		return ans;
}


// process the TSP
void TSPProcess(int depot, int *arr, int n) {
	int i, j, u, v;
	static int a[MAXN / 2 + 1][MAXN / 2 + 1];
	static int q[MAXN / 2 + 1];
	static bool used[MAXN / 2 + 1];
	static int id[MAXN / 2 + 1];
	static int seq[MAXN / 2 + 1];
	int t = 0, ans = 0;
	
	if (n <= 1) return;
	
	id[0] = depot;
	for (i = 0; i < n; ++i)
		id[i + 1] = arr[i];
	++n;
	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j) {
			if (i == j) a[i][j] = 0;
			else if (i == 0) {
				u = node[id[i]].first;
				v = node[id[j]].first;
				a[i][j] = dis[u][v];
			} else if (j == 0) {
				u = node[id[i]].second;
				v = node[id[j]].second;
				a[i][j] = dis[u][v];
			} else {
				u = node[id[i]].second;
				v = node[id[j]].first;
				a[i][j] = dis[u][v];
			}
		}
		if (n < 8) {
			int min = INF;
			for (i = 0; i < n; ++i) q[i] = i;
			q[n] = 0;
			do {
				int sum = 0;
				for (i = 0; i < n; ++i)
					sum += a[q[i]][q[i + 1]];
				if (sum < min) {
					min = sum;
					memcpy(seq, q, n * sizeof(int));
				}
			} while (next_permutation(q + 1, q + n));
			for (i = 0; i < n - 1; ++i)
				arr[i] = id[seq[i + 1]];
			return;
		}
		for (i = 0; i < n; ++i) {
			seq[i] = i;
			ans += a[i][(i + 1) % n];
		}
		t = calcTSP(a, n, q, 3);
		if (t < ans) {
			ans = t;
			for (i = 0; i < n; ++i) seq[i] = q[i];
		}
		int sum = 0;
		seq[n] = seq[0];
		for (i = 0; i < n; ++i)
			sum += a[seq[i]][seq[i + 1]];
		for (i = 0; i < n - 1; ++i)
			arr[i] = id[seq[i + 1]];
}


// the TSP improve operator
//ASTP�����ѡ��һ�����������ӽڵ㣬����ģ����8������̰�������β��룻����������в������
void ATSP(Genotype &gt) {
	int *a = gt.gene;
	int i, u, v;
	static int stck[MAXN];
	int top = 0;
	int oldFitness = calcFitness(gt);
	
	//�ɿ��н�aת��Ϊ��stck
	stck[top++] = 0;
	memset(deg, 0, sizeof(deg));
	for (i = 0; i < size; ++i) {
		if (!isVertexP[a[i]]) {
			--top;
		} else {
			stck[top++] = a[i];
			u = nodeID[stck[top - 2]];
			v = nodeID[stck[top - 1]];
			adj[u][deg[u]++] = v;
		}
	}
	for (i = 0; i < nodeSize; ++i)
		TSPProcess(i, adj[i], deg[i]);
	int n = 0;
	dfs(0, a, n);
	gt.fitness = calcFitness(gt);
	if (gt.fitness < oldFitness) {
		printf("ATSP is wrong!!!\n");
		exit(1);
	}
}

// cross-over operator
//cross_over���ӣ������gt��ȡ����,����gt2�еĸ��ӹ�ϵ�����²����gt
Genotype crossOver(const Genotype &gt, const Genotype &gt2) {
	const int *a;
	int i, u, v;
	static int stck[MAXN], q[MAXN], pnt[MAXN], pnt2[MAXN];
	int top;
	//Genotype oldGT = gt;
	
	memset(pnt, 0, (size + 1) * sizeof(int));
	memset(pnt2, 0, (size + 1) * sizeof(int));
	a = gt.gene;
	top = 0;
	stck[top++] = 0;
	for (i = 0; i < size; ++i) {
		if (!isVertexP[a[i]]) {
			--top;
		} else {
			stck[top++] = a[i];
			u = nodeID[stck[top - 2]];
			v = nodeID[stck[top - 1]];
			pnt[v] = u;
		}
	}
	
	a = gt2.gene;
	top = 0;
	stck[top++] = 0;
	for (i = 0; i < size; ++i) {
		if (!isVertexP[a[i]]) {
			--top;
		} else {
			stck[top++] = a[i];
			u = nodeID[stck[top - 2]];
			v = nodeID[stck[top - 1]];
			pnt2[v] = u;
		}
	}
	
	int xl, xr;
	getPosition(gt, vertexP[rand() % nVertexP], xl, xr);
    for (i = xl; i <= xr; ++i)
		if (isVertexP[gt.gene[i]]) {
			pnt[nodeID[gt.gene[i]]] = pnt2[nodeID[gt.gene[i]]];
        }
		memset(deg, 0, (nodeSize + 1) * sizeof(int));
		for (i = 1; i < nodeSize; ++i) adj[pnt[i]][deg[pnt[i]]++] = i;
		for (i = 0; i < nodeSize; ++i) TSPProcess(i, adj[i], deg[i]);
		
		int n = 0;
		Genotype ret;
		dfs(0, ret.gene, n);
		ret.fitness = calcFitness(ret);
		return ret;
}


// to check whether the current genotype is a valid solution.
//��鵱ǰgenotype�Ƿ����
bool check(const Genotype &gt) {
	//�洢pick_up��
	static int stck[MAXN + 2];
	//�洢ÿ����ķ���״̬
	static int vst[MAXN + 2];
	int i, top = -1;
	
	memset(vst, 0, sizeof(vst));
	for (i = 0; i < size; ++i) {
		//���gene�Ƿ񳬹���Χ
		if (!(1 <= gt.gene[i] && gt.gene[i] <= size))
			return false;
		//���ÿ�����Ƿ�ȫ��������
		if (++vst[gt.gene[i]] > 1)
			return false;
		//���pick_up���delivery���Ƿ��Ӧ
		if (!isVertexP[gt.gene[i]]) {
			if (top <= -1) return false;
			if (stck[top--] != other[gt.gene[i]]) return false;
		} else {
			stck[++top] = gt.gene[i];
		}
	}
	return top == -1;
}

// couple-exchange operator
//exchange����x��Ӧpick_up���delivery����y��Ӧ��һһ���н���
void coupleExchange(Genotype &gt) {
	int it = 0, x, y, ok = true;
	int i, xl, xr, yl, yr;
	int fitness, newL;
    static int pos[MAXN + 2];
    
    for (i = 0; i < size; ++i) pos[gt.gene[i]] = i;
	while (ok) {
		ok = false;
		for (it = 0; it < nVertexP; ++it) {
			x = vertexP[it];
			for (i = 0; i < nVertexP; ++i) {
				y = vertexP[i];
				if (y == x) continue;
				yl = pos[y];
				yr = pos[other[y]];
				xl = pos[x];
				xr = pos[other[x]];
				
                newL = -gt.fitness;
				
#define getPoint(x) (((x) < 0 || (x) >= size) ? 0 : gt.gene[(x)])

                newL -= dis[getPoint(xl - 1)][getPoint(xl)] +
					dis[getPoint(xl)][getPoint(xl + 1)] +
					dis[getPoint(xr - 1)][getPoint(xr)] +
					dis[getPoint(xr)][getPoint(xr + 1)] +
					dis[getPoint(yl - 1)][getPoint(yl)] +
					dis[getPoint(yl)][getPoint(yl + 1)] +
					dis[getPoint(yr - 1)][getPoint(yr)] +
					dis[getPoint(yr)][getPoint(yr + 1)];
				
                if (xl + 1 == xr) newL += dis[getPoint(xl)][getPoint(xr)];
                if (yl + 1 == yr) newL += dis[getPoint(yl)][getPoint(yr)];
                if (xr + 1 == yl) newL += dis[getPoint(xr)][getPoint(yl)];
                if (yr + 1 == xl) newL += dis[getPoint(yr)][getPoint(xl)];
                
				
				swap(gt.gene[xl], gt.gene[yl]);
				swap(gt.gene[xr], gt.gene[yr]);
				swap(pos[x], pos[y]);
				swap(pos[other[x]], pos[other[y]]);
				
				newL += dis[getPoint(xl - 1)][getPoint(xl)] +
					dis[getPoint(xl)][getPoint(xl + 1)] +
					dis[getPoint(xr - 1)][getPoint(xr)] +
					dis[getPoint(xr)][getPoint(xr + 1)] +
					dis[getPoint(yl - 1)][getPoint(yl)] +
					dis[getPoint(yl)][getPoint(yl + 1)] +
					dis[getPoint(yr - 1)][getPoint(yr)] +
					dis[getPoint(yr)][getPoint(yr + 1)];
				
                if (xl + 1 == xr) newL -= dis[getPoint(xl)][getPoint(xr)];
                if (yl + 1 == yr) newL -= dis[getPoint(yl)][getPoint(yr)];
                if (xr + 1 == yl) newL -= dis[getPoint(xr)][getPoint(yl)];
                if (yr + 1 == xl) newL -= dis[getPoint(yr)][getPoint(xl)];
				
				fitness = -newL;
				if (fitness > gt.fitness) {
					gt.fitness = fitness;
					ok = true;
				} else {
					swap(gt.gene[xl], gt.gene[yl]);
					swap(gt.gene[xr], gt.gene[yr]);
					swap(pos[x], pos[y]);
					swap(pos[other[x]], pos[other[y]]);
                }
			}
		}
	}
	
}

// block-exchange operator
//swap:��x��Ӧpick_up��delivery֮���gene��y��Ӧ�Ľ���
void blockExchange(Genotype &gt) {
	int it = 0, x, ok = true;
	while (ok) {
		ok = false;
		for (it = 0; it < nVertexP; ++it) {
			x = vertexP[it];
			Genotype newGT = gt;
			int i, xl, xr, y, yl, yr, bestY = x, n = 0;
			int length = -gt.fitness, bestFitness = gt.fitness, fitness, newL;
			static int pos[MAXN + 2];
			
			for (i = 0; i < size; ++i) pos[newGT.gene[i]] = i;
			for (i = 0; i < nVertexP; ++i) {
				y = vertexP[i];
				if (y == x) continue;
				yl = pos[y];
				yr = pos[other[y]];
				xl = pos[x];
				xr = pos[other[x]];
				if ((xl < yl && yr < xr) ||
					(yl < xl && xr < yr)) continue;
				if (xl > yl) {
					swap(xl, yl);
					swap(xr, yr);
				}
				newL = length;
				if (xl == 0) {
					newL -= dis[0][gt.gene[xl]];
					newL += dis[0][gt.gene[yl]];
				} else {
					newL -= dis[gt.gene[xl - 1]][gt.gene[xl]];
					newL += dis[gt.gene[xl - 1]][gt.gene[yl]];
				}
				
				if (xr + 1 == yl) {
					newL -= dis[gt.gene[xr]][gt.gene[yl]];
					newL += dis[gt.gene[yr]][gt.gene[xl]];
				} else {
					newL -= dis[gt.gene[xr]][gt.gene[xr + 1]];
					newL += dis[gt.gene[yr]][gt.gene[xr + 1]];
					newL -= dis[gt.gene[yl - 1]][gt.gene[yl]];
					newL += dis[gt.gene[yl - 1]][gt.gene[xl]];
				}
				
				if (yr == size - 1) {
					newL -= dis[gt.gene[yr]][0];
					newL += dis[gt.gene[xr]][0];
				} else {
					newL -= dis[gt.gene[yr]][gt.gene[yr + 1]];
					newL += dis[gt.gene[xr]][gt.gene[yr + 1]];
				}
				
				fitness = -newL;
				if (fitness > bestFitness) {
					bestFitness = fitness;
					bestY = y;
					break;
				}
			}
			
			if (bestY == x) continue;
			if (gt.fitness > bestFitness) {
				printf("gtFitness = %d bestFitness = %d\n", gt.fitness, bestFitness);
				printf("blockExchange fails\n");
				exit(1);
			}
			//	if (fabs(gt.fitness - bestFitness) < 1e-6) return;
			if (gt.fitness == bestFitness) continue;
			xl = pos[x];
			xr = pos[other[x]];
			yl = pos[bestY];
			yr = pos[other[bestY]];
			if (xl > yl) {
				swap(xl, yl);
				swap(xr, yr);
			}
			for (i = 0; i < xl; ++i)
				gt.gene[n++] = newGT.gene[i];
			for (i = yl; i <= yr; ++i)
				gt.gene[n++] = newGT.gene[i];
			for (i = xr + 1; i < yl; ++i)
				gt.gene[n++] = newGT.gene[i];
			for (i = xl; i <= xr; ++i)
				gt.gene[n++] = newGT.gene[i];
			for (i = yr + 1; i < size; ++i)
				gt.gene[n++] = newGT.gene[i];
			gt.fitness = bestFitness;//calcFitness(bestGT);
			ok = true;
		}
	}
}


// relocate-block operator
//relocate:�ƶ�x��Ӧpick_up��delivery֮���gene
void relocateBlock(Genotype &gt) {
	int it, x, ok = true;
	
	while (ok) {
		ok = false;
		for (it = 0; it < nVertexP; ++it) {
			x = vertexP[it];
			Genotype newGT = gt, T1; // T1 = T'
			int i, xl, xr, n = 0, m = 0, bestPos;
			int fitness, bestFitness = gt.fitness, length = 0;
			
			getPosition(newGT, x, xl, xr);
			for (i = 0; i < xl; ++i)
				T1.gene[n++] = newGT.gene[i];
			for (i = xr + 1; i < size; ++i)
				T1.gene[n++] = newGT.gene[i];
			for (i = xl; i < xr; ++i)
				length += dis[newGT.gene[i]][newGT.gene[i + 1]];
			for (i = 0; i < n - 1; ++i)
				length += dis[T1.gene[i]][T1.gene[i + 1]];
			T1.gene[n] = 0;
			if (n > 0) {
				length += dis[0][T1.gene[0]] + dis[T1.gene[n - 1]][0];
			}
			for (i = -1; i < n; ++i) {
				if (i == -1) {
					fitness = -(length + dis[0][newGT.gene[xl]]
						+ dis[newGT.gene[xr]][T1.gene[0]]
						- dis[0][T1.gene[0]]);
					//bestFitness = fitness;
					//bestPos = i;
				} else {
					fitness = -(length + dis[T1.gene[i]][newGT.gene[xl]]
						+ dis[newGT.gene[xr]][T1.gene[i + 1]]
						- dis[T1.gene[i]][T1.gene[i + 1]]);
					
				}
				if (fitness > bestFitness) {
					bestFitness = fitness;
					bestPos = i;
					break;
				}
			}
			if (gt.fitness > bestFitness) {
				printf("gtFitness = %d bestFitness = %d\n", gt.fitness, bestFitness);
				printf("relocateBlock fails\n");
				exit(1);
			}
			//if (fabs(gt.fitness - bestFitness) < 1e-6) return;
			if (gt.fitness == bestFitness) continue;
			for (i = 0; i <= bestPos; ++i)
				gt.gene[m++] = T1.gene[i];
			for (i = xl; i <= xr; ++i)
				gt.gene[m++] = newGT.gene[i];
			for (i = bestPos + 1; i < n; ++i)
				gt.gene[m++] = T1.gene[i];
			gt.fitness = bestFitness;
			ok = true;
		}
	}
}


// randomized arbitrary insertion function.
//RAI�������ѡx��Ӧpick_up��delivery֮���gene��������������ĩ��
void RAI(Genotype &gt) {
    int i, j, n, xl, xr, nq = 0;
    static int q[MAXN];
	//  Genotype old = gt;
	
    gt.fitness = calcFitness(gt);
	//  while (true) {
	getPosition(gt, vertexP[rand() % nVertexP], xl, xr);
    //    if (xr - xl + 1 >= size / 30) break;
    //}
    for (i = xl; i <= xr; ++i)
        if (isVertexP[gt.gene[i]]) {
            q[nq++] = gt.gene[i];
        }
		random_shuffle(q, q + nq);
		for (i = xl, j = xr + 1; j < size; ++i, ++j)
			gt.gene[i] = gt.gene[j];
		n = size - (xr - xl + 1);
		for (j = 0; j < nq; ++j) {
			gt.gene[n++] = q[j];
			gt.gene[n++] = other[q[j]];
			relocateCouple(gt, q[j], n);
		}
		// if (old.fitness > gt.fitness)
		//    gt = old;
}


// relocate-couple operator with size
//relocate:��x��Ӧ��pick_up���delivery�����²���
void relocateCouple(Genotype &gt, int x, int size) {
	Genotype newGT = gt, T1;
	int i, j, lp, rp, n = 0, m = 0;
	int bestFitness = 0, fitness, newL, length = 0;
	static int pos[MAXN + 2];
	
	for (i = 0; i < size - 1; ++i)
        bestFitness += dis[gt.gene[i]][gt.gene[i + 1]];
    bestFitness += dis[0][gt.gene[0]] + dis[gt.gene[size - 1]][0];
    bestFitness = -bestFitness;
    gt.fitness = bestFitness;
	
	
	for (i = 0; i < size; ++i)
		if (newGT.gene[i] != x && newGT.gene[i] != other[x]) {
			T1.gene[n++] = newGT.gene[i];
			pos[T1.gene[n - 1]] = n - 1;
			if (n > 1) length += dis[T1.gene[n - 2]][T1.gene[n - 1]];
		}
		T1.gene[n] = 0;
		if (n > 0) length += dis[0][T1.gene[0]] + dis[T1.gene[n - 1]][0];
		for (i = -1; i < n; ++i) {
			if (i == -1) {
				newL = length + dis[0][x] + dis[x][other[x]] + dis[other[x]][T1.gene[0]]
					- dis[0][T1.gene[0]];
				fitness = -newL;
				if (fitness > bestFitness) {
					bestFitness = fitness;
					lp = -1;
					rp = -1;
				}
				for (j = 0; j < n; ++j) {
					if (isVertexP[T1.gene[j]]) { // y+ -> y-
						j = pos[other[T1.gene[j]]];
					}
					newL = length + dis[0][x] + dis[x][T1.gene[0]]
						+ dis[T1.gene[j]][other[x]]
						+ dis[other[x]][T1.gene[j + 1]]
						- dis[0][T1.gene[0]]
						- dis[T1.gene[j]][T1.gene[j + 1]];
					fitness = -newL;
					if (fitness > bestFitness) {
						bestFitness = fitness;
						lp = -1;
						rp = j;
					}
				}
			} else {
				newL = length + dis[T1.gene[i]][x] + dis[x][other[x]] + dis[other[x]][T1.gene[i + 1]]
					- dis[T1.gene[i]][T1.gene[i + 1]];
				fitness = -newL;
				if (fitness > bestFitness) {
					bestFitness = fitness;
					lp = i;
					rp = i;
					
				}
				for (j = i + 1; j < n; ++j) {
					if (isVertexP[T1.gene[j]]) {
						j = pos[other[T1.gene[j]]];
					} else if (pos[other[T1.gene[j]]] <= i) {
						break;
					}
					newL = length + dis[T1.gene[i]][x] + dis[x][T1.gene[i + 1]]
						+ dis[T1.gene[j]][other[x]]
						+ dis[other[x]][T1.gene[j + 1]]
						- dis[T1.gene[i]][T1.gene[i + 1]]
						- dis[T1.gene[j]][T1.gene[j + 1]];
					fitness = -newL;
					if (fitness > bestFitness) {
						bestFitness = fitness;
						lp = i;
						rp = j;
					}
				}
			}
		}
		if (gt.fitness > bestFitness) {
			printf("gtFitness = %d bestFitness = %d\n", gt.fitness, bestFitness);
			printf("relocateCouple fails\n");
			exit(1);
		}
		if (gt.fitness == bestFitness) return;
		for (i = 0; i <= lp; ++i)
			gt.gene[m++] = T1.gene[i];
		gt.gene[m++] = x;
		for (i = lp + 1; i <= rp; ++i)
			gt.gene[m++] = T1.gene[i];
		gt.gene[m++] = other[x];
		for (i = rp + 1; i < n; ++i)
			gt.gene[m++] = T1.gene[i];
		gt.fitness = bestFitness;
}


// relocate-couple operator
//relocate:�������е�pick_up��x,��x��Ӧ��pick_up���delivery�����²���
void relocateCouple(Genotype &gt) {
	int it, x, ok = true;
	while (ok) {
		ok = false;
		for (it = 0; it < nVertexP; ++it) {
			x = vertexP[it];
			Genotype newGT = gt, T1;
			int i, j, lp, rp, n = 0, m = 0;
			int bestFitness = gt.fitness, fitness, newL, length = 0;
			static int pos[MAXN + 2];
			
			for (i = 0; i < size; ++i)
				if (newGT.gene[i] != x && newGT.gene[i] != other[x]) {
					T1.gene[n++] = newGT.gene[i];
					pos[T1.gene[n - 1]] = n - 1;
					if (n > 1) length += dis[T1.gene[n - 2]][T1.gene[n - 1]];
				}
				T1.gene[n] = 0;
				if (n > 0) length += dis[0][T1.gene[0]] + dis[T1.gene[n - 1]][0];
				for (i = -1; i < n; ++i) {
					if (i == -1) {
						newL = length + dis[0][x] + dis[x][other[x]] + dis[other[x]][T1.gene[0]]
							- dis[0][T1.gene[0]];
						fitness = -newL;
						if (fitness > bestFitness) {
							bestFitness = fitness;
							lp = -1;
							rp = -1;
						}
						for (j = 0; j < n; ++j) {
							if (isVertexP[T1.gene[j]]) { // y+ -> y-
								j = pos[other[T1.gene[j]]];
							}
							newL = length + dis[0][x] + dis[x][T1.gene[0]]
								+ dis[T1.gene[j]][other[x]]
								+ dis[other[x]][T1.gene[j + 1]]
								- dis[0][T1.gene[0]]
								- dis[T1.gene[j]][T1.gene[j + 1]];
							fitness = -newL;
							if (fitness > bestFitness) {
								bestFitness = fitness;
								lp = -1;
								rp = j;
							}
						}
					} else {
						newL = length + dis[T1.gene[i]][x] + dis[x][other[x]] + dis[other[x]][T1.gene[i + 1]]
							- dis[T1.gene[i]][T1.gene[i + 1]];
						fitness = -newL;
						if (fitness > bestFitness) {
							bestFitness = fitness;
							lp = i;
							rp = i;
							
						}
						for (j = i + 1; j < n; ++j) {
							if (isVertexP[T1.gene[j]]) {
								j = pos[other[T1.gene[j]]];
							} else if (pos[other[T1.gene[j]]] <= i) {
								break;
							}
							newL = length + dis[T1.gene[i]][x] + dis[x][T1.gene[i + 1]]
								+ dis[T1.gene[j]][other[x]]
								+ dis[other[x]][T1.gene[j + 1]]
								- dis[T1.gene[i]][T1.gene[i + 1]]
								- dis[T1.gene[j]][T1.gene[j + 1]];
							fitness = -newL;
							if (fitness > bestFitness) {
								bestFitness = fitness;
								lp = i;
								rp = j;
                                break;
							}
						}
					}
				}
				if (gt.fitness > bestFitness) {
					printf("gtFitness = %d bestFitness = %d\n", gt.fitness, bestFitness);
					printf("relocateCouple fails\n");
					exit(1);
				}
				//if (fabs(gt.fitness - bestFitness) < 1e-6) return;
				if (gt.fitness == bestFitness) continue;
				for (i = 0; i <= lp; ++i)
					gt.gene[m++] = T1.gene[i];
				gt.gene[m++] = x;
				for (i = lp + 1; i <= rp; ++i)
					gt.gene[m++] = T1.gene[i];
				gt.gene[m++] = other[x];
				for (i = rp + 1; i < n; ++i)
					gt.gene[m++] = T1.gene[i];
				gt.fitness = bestFitness;
				ok = true;
		}
	}
}


// to read the coordinates of the points.
//�ļ����룬����������
void readCoordinate(char *file) {
	FILE *fp;
	int i, id;
	char s[109];
	
	if ((fp = fopen(file, "r")) == NULL) {
		printf("ERROR: Can not open input file %s!\n\n", file);
		exit(1);
	}
	while (true) {
		fscanf(fp, "%s", s);
		if (strcmp("NAME", s) == 0) {
			fscanf(fp, "%s", s); // read the character ":"
			fscanf(fp, "%s", instance);
		} else if (strcmp("DIMENSION", s) == 0) {
			fscanf(fp, "%s", s); // read the character ":"
			fscanf(fp, "%d", &size);
		} else if (strcmp("NODE_COORD_SECTION", s) == 0) {
			for (i = 0; i < size; ++i) {
				fscanf(fp, "%d", &id);
				fscanf(fp, "%d%d", &points[i].first, &points[i].second);
			}
			break;
		}
	}
	fclose(fp);
}


// to read the matching file.
//�ļ�����,���в�������
void readMatching(char *file) {
	FILE *fp;
	int i, j, x, state, y, px, py;
	
	if ((fp = fopen(file, "r")) == NULL) {
		printf("ERROR: Can not open input file %s!\n\n", file);
		exit(1);
	}
	
	nVertexP = 0;
	nodeSize = 0;
	node[nodeSize++] = make_pair(0, 0);
	nodeID[0] = 0;
	while (fscanf(fp, "%d%d%d", &x, &state, &y) != EOF) {
		if (state == 1) {
			other[x] = y;
			other[y] = x;
			vertexP[nVertexP++] = x;
			isVertexP[x] = true;
			isVertexP[y] = false;
			node[nodeSize] = make_pair(x, y);
			nodeID[x] = nodeSize++;
		}
	}
	
	// to calculate the distance matrix
	//����������
	--size;
	for (i = 0; i <= size; ++i)
		for (j = 0; j <= size; ++j) {
			px = points[i].first - points[j].first;
			py = points[i].second - points[j].second;
			dis[i][j] = (int) (sqrt(px * px + py * py) + 0.5);
		}
		fclose(fp);
}


// to get the starting tour.
//�����ʼ��
void getStartingTour() {
    int i, n = 0;
    for (i = 1; i < nodeSize; ++i) {
        src.gene[n++] = node[i].first;
        src.gene[n++] = node[i].second;
    }
    src.fitness = calcFitness(src);
    startingTourCost = -src.fitness;
}


int main(int argc, char *argv[]) {
	srand(1);
	if (argc != 3) {
		printf("\nERROR: wrong number of input parameters.\n");
		printf("USAGE: exeFile coordinateFile matchingFile resultFile\n");
		exit(1);
	}
	
	int i, j, k = 0, mem, best = INF, startTime = clock();
	readCoordinate(argv[1]);
	readMatching(argv[2]);
	getStartingTour();
	
	//if ((output = fopen(argv[3], "w")) == NULL) {
	//	printf("ERROR: Can not open output file %s!\n\n", argv[3]);
	//	exit(1);
	//}
	
	for (i = 0; i < MAX_OUTER_ITER; ++i) {
        initialize();
		evaluate();
		keepTheBest();
		j = 0;
		while (j < MAX_INNER_ITER) {
			for (mem = 0; mem < POP_SIZE; ++mem) {
				RAI(population[mem]);
                localSearch(population[mem]);
				ATSP(population[mem]);
				newPopulation[mem] = population[mem];
            }
			for (mem = 0; mem < POP_SIZE; ++mem) {
				Genotype bestOne = population[mem], t;
				for (k = 0; k < POP_SIZE; ++k) 
					if (k != mem) {
						t = crossOver(newPopulation[mem], newPopulation[k]);
						if (t.fitness > bestOne.fitness)
							bestOne = t;
					}
					population[mem] = bestOne;
			}
			evaluate();
			elitist();
			if (-population[POP_SIZE].fitness < best) {
				j = 0;
				best = -population[POP_SIZE].fitness;
			} else {
				++j;
			}
		}
		if (-population[POP_SIZE].fitness <= best) {
			best = -population[POP_SIZE].fitness;
			src = population[POP_SIZE];
		}
		//printf("current best = %d\n", best);
		if (!check(population[POP_SIZE])) {
			printf("The answer is wrong\n");
			exit(1);
		}
	}
	
	printf("Problem Name: %s 	Dimension: %d   StartingTourCost: %d", instance, size + 1, startingTourCost);
	printf("\nTime: %.2f seconds. Cost = %d\n", (clock() - startTime) * 1.0 / (CLOCKS_PER_SEC), best);
	//fprintf(output, "Problem Name: %s 	Dimension: %d   StartingTourCost: %d", instance, size + 1, startingTourCost);
	//fprintf(output, "\nTime: %.2f seconds. Cost = %d\n", (clock() - startTime) * 1.0 / (CLOCKS_PER_SEC), best);
	//fclose(output);
	return 0;
}
