#include <stdio.h>
#include <iostream>
#define MAX 100
#define INF 2000000
int grafo[MAX][MAX]; // representação matricial dos grafos
bool grafobool[MAX][MAX];
bool visdfs[MAX];

struct no{
	int vertice;
	no* proximo;
};
typedef no* noptr;
noptr grafoLA[MAX];

// Funcao para ler a matriz
void leGrafo (int g[][MAX], int ordem, int tamanho)
{
	for (int i=0; i < ordem; i++)
	{
		for (int j=0; j < tamanho; j++)
		{
			scanf("%d", &g[i][j]);
		}
	}
}

// Funções desenvolvidas no trabalho

// Caso 2
bool k_regularMI(int ordem, int tamanho, int k)
{
	int cont;
	for (int i = 0; i < ordem; i++)
	{
		cont = 0;
		for (int j = 0; j < tamanho; j++)
		{
			if(grafo[i][j] != 0)
			{
				cont++;
			}
		}
		if (cont != k) return false;
	}
	return true;
}

// Caso 3
bool eulerianoMA(int ordem)
{
	int cont = 0;

	for (int i=0; i < ordem; i++)
	{
		cont = 0;
		for (int j=0; j < ordem; j++)
		{
			if(grafo[i][j] != 0)
			{
				cont++;
			}
		}
		if ((cont % 2) != 0) return false;
	}
	return true;
}

// Caso 4
bool eulerianoMI(int ordem, int tamanho)
{
	int cont = 0;

	for (int i=0; i < ordem; i++)
	{
		cont = 0;
		for (int j=0; j < tamanho; j++)
		{
			if(grafo[i][j] != 0)
			{
				cont++;
			}
		}
		if ((cont % 2) != 0) return false;
	}
	return true;
}

// Caso 5
void dfs(int ordem, int x)
{
	visdfs[x] = true;
	for(int i = 0; i < ordem; i++)
	{
		if(!visdfs[i] && grafo[x][i])
			dfs(ordem, i);
	}
}

void conexoMA(int ordem)
{
	int aux = 0;
	for(int i = 0; i < ordem; i++) visdfs[i] = false;
	for(int i = 0; i < ordem; i++)
	{
		if(visdfs[i] == 0)
		{
			aux++;
			dfs(ordem, i);
		}
	}
	printf("%d\n", aux);
}

// Caso 6
bool completoMI(int ordem, int tamanho)
{
	int aux;
	aux = ordem*(ordem-1)/2;
	if(aux== tamanho) return true;
	else return false;
}

// Caso 7
void legrafoLA(int ordem)
{
	int num;
	for(int i = 0; i < ordem; i++)
	{
		grafoLA[i] = (noptr)malloc(sizeof(noptr));
	}
	noptr atual = NULL;

	for(int i = 0; i < ordem; i++)
	{
		atual = grafoLA[i];
		scanf("%d", &num);
		while (num != -1)
		{
			atual->vertice = num;
			atual->proximo = (noptr)malloc(sizeof(noptr));
			atual = atual->proximo;

			scanf("%d", &num);
		}

	}
}

bool completoLA(int ordem)
{
	noptr atual = NULL;
	int cont;
	for(int i = 0; i < ordem; i++)
	{
		cont = 0;
		atual = grafoLA[i];
		while (atual->proximo != NULL)
		{
			if(atual->vertice)cont++;
			atual = atual->proximo;

		}
		if(cont != ordem) return false;
	}
	return true;
}


// Caso 8
void complementoMA(int ordem)
{
	for (int i=0; i < ordem; i++)
		for (int j=0; j < ordem; j++)
			if(i != j)
			{
				if(grafo[i][j])grafo[i][j]--;
				else grafo[i][j]++;
			}
	for (int i = 0; i < ordem; i++)
	{
		for (int j = 0; j < ordem; j++)
		{
			if(j != ordem-1)
				printf("%d ", grafo[i][j]);
			else printf("%d\n", grafo[i][j]);
		}
	}
}

// Caso 9
bool bipartidoMA(int ordem)
{
	int i = 0, j = 0;
	int aux[MAX], k;
	bool flag = false;
	for(i = 0; i < MAX; i++)
	{
		aux[i] = -1;
	}
	for (i = 0; i < ordem; i++)
	{
		for (j = i+1; j < ordem; j++)
		{
			if(grafo[i][j])
			{
				if(aux[i] != -1)
				{
					k = !aux[i];
					if(aux[j] != -1)
					{
						if(aux[j] == aux[i]) return false;
					} else aux[j] = k;
				}
				else if(aux[j] != -1)
				{
					k = !aux[j];
					aux[i] = k;
				} else
				{
					aux[i] = 0;
					aux[j] = 1;
				}
			}
		}
	}
	for(int i = 0; i < ordem; i++)
		if (!aux[i])
		{
			if(flag) printf(" %d", i);
			else{
				printf("%d", i);
				flag = true;
			}
		}
	printf("\n");
	flag = false;
	for(int i = 0; i < ordem; i++)
		if (aux[i])
		{
			if(flag) printf(" %d", i);
			else{
				printf("%d", i);
				flag = true;
			}
		}
	printf("\n");
	return true;
}

// Caso 10
void alcancabilidade(int ordem)
{
	for (int k=0; k < ordem; k++)
		for (int i=0; i < ordem; i++)
			for (int j=0; j < ordem; j++)
				grafobool[i][j] = grafobool[i][j] || (grafobool[i][k] && grafobool[k][j]);
	for (int i = 0; i < ordem; i++)
	{
		for (int j = 0; j < ordem; j++)
		{
			if(j != ordem-1)
				printf("%d ", grafobool[i][j]);
			else printf("%d\n", grafobool[i][j]);
		}
	}

}
void converte(int ordem, int tamanho)
{
	int aux[2];
	for (int j = 0; j <= tamanho; j++)
	{
		aux[0]=-1;
		aux[1]=-1;
		for (int i = 0; i <= ordem; i++)
		{
			if(grafo[i][j])
			{
				if(aux[0]==-1) aux[0] = i;
				else aux[1] = i;
			}
		}
		grafobool[aux[0]][aux[1]] = 1;
		grafobool[aux[1]][aux[0]] = 1;
	}
}

// Verifica se grafo é regular com Matriz de Adjacências
// Caso 1
bool regular(int ordem)
{
	int grau=0, grau_aux;
	for (int i = 0; i < ordem; i++)
		grau += (grafo[0][i] != 0 ? 1 : 0);
	for (int i = 1; i < ordem; i++)
	{
		grau_aux=0;
		for (int j=0; j < ordem; j++)
		{
			grau_aux += (grafo[i][j] != 0 ? 1 : 0);
		}
		if (grau != grau_aux)
			return false;
	}
	return true;
}


int main()
{
	int operacao, ordem, tamanho;


	int n, m;
	int i, j, k;
	int Soma;

	while (true)
	{
		scanf("%d", &operacao);
		if (!operacao)
			break;
		switch (operacao)
		{
			case 1: // Caso exemplo ­ Verificar se o Grafo é regular
				scanf("%d", &ordem);
				leGrafo(grafo, ordem, ordem);
				if (regular(ordem))
					printf("Grafo regular\n");
				else
					printf("Grafo nao regular\n");
				break;
			case 2:
				scanf("%d %d %d", &n, &m, &k);
				leGrafo(grafo, n, m);
				if (k_regularMI(n, m, k))
					printf("Grafo %d-regular\n", k);
				else
					printf("Grafo nao %d-regular\n", k);
				break;
			case 3:
				scanf("%d", &n);
				leGrafo(grafo, n, n);
				if (eulerianoMA(n))
					printf("Grafo Euleriano\n");
				else
					printf("Grafo nao Euleriano\n");
				break;
			case 4:
				scanf("%d %d", &n, &m);
				leGrafo(grafo, n, m);
				if (eulerianoMI(n, m))
					printf("Grafo Euleriano\n");
				else
					printf("Grafo nao Euleriano\n");
				break;
			case 5:
				scanf("%d", &n);
				leGrafo(grafo, n, n);
				conexoMA(n);
				break;
			case 6:
				scanf("%d %d", &n, &m);
				leGrafo(grafo, n, m);
				if(completoMI(n, m))
					printf("Grafo Completo\n");
				else
					printf("Grafo nao Completo\n");
				break;
			case 7:
				scanf("%d", &n);
				legrafoLA(n);
				if(completoLA(n))
					printf("Grafo Completo\n");
				else
					printf("Grafo nao Completo\n");

				break;
			case 8:
				scanf("%d", &n);
				leGrafo(grafo, n, n);
				complementoMA(n);
				break;
			case 9:
				scanf("%d", &n);
				leGrafo(grafo, n, n);
				if(!bipartidoMA(n))
					printf("O grafo nao e bipartido\n");
				break;
			case 10:
				scanf("%d %d", &n, &m);
				leGrafo(grafo, n, m);
				converte(n, m);
				alcancabilidade(n);
				break;

		}
	}
	return (0);
}
