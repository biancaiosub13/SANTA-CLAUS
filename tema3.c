// IOSUB BIANCA-ALEXANDRA 313CA  TEMA 3

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	char oras[20];
	char tip_cadou[20];
	int nr;
	char directie;
} zona;

typedef struct {
	char oras[20];
	char tip[20];
} cadou;

typedef struct {
	int nr;
	char oras[20];
	char tip[20];
} unic;

void citire(zona ***a, int *N, int *M, int *startx, int *starty, int *pasi) {

	int i, j;

	scanf("%d%d", N, M);
	scanf("%d%d", startx, starty);
	scanf("%d", pasi);

	*a = (zona **) malloc((*N) * sizeof(zona *));
	for(j = 0; j < *N; j++) {
		(*a)[j] = malloc((*M) * sizeof(zona));   //aloc fiecare linie din matrice
	}

	for(i = 0; i < *N; i++)
		for(j = 0; j < *M; j++) {
			scanf("%s", (*a)[i][j].oras);
			scanf("%s", (*a)[i][j].tip_cadou);
			scanf("%d", &(*a)[i][j].nr);
			scanf("%*c%c", &(*a)[i][j].directie);   // am folosit %*c pentru a putea sării peste null
		}
}

int cmp(const void *p1, const void *p2) {    //funcția de comparare pentru qsort

	int aux;
	cadou a, b;

	a = *((cadou*)p1);
	b = *((cadou*)p2);

	aux = strcmp(a.oras, b.oras);

	if(aux != 0) 
		return aux;
	else
		return strcmp(a.tip, b.tip);
}

int cmp_unic(const void *p1, const void *p2) {

	int aux1, aux2;
	unic a, b;

	a = *((unic*)p1);
	b = *((unic*)p2);

	aux1 = strcmp(a.oras, b.oras);

	if(aux1 != 0) 
		return aux1;

	aux2 = b.nr - a.nr;

	if(aux2 != 0)
		return aux2;
	
	return strcmp(a.tip, b.tip);
}

int main() {

	zona **a;
	cadou *sac;

	int N, M, startx, starty, pasi, nr = -1, k = -1, dim_max = 2;

	sac = malloc(dim_max * sizeof(cadou));    //inițial în sac intră doar 2 cadouri

	citire(&a, &N, &M, &startx, &starty, &pasi); 

	while(nr < pasi) {    //nr = numarul de pași făcuți deja de Moș Crăciun

		if((startx < 0) || (starty < 0) || (startx >= N) || (starty >= M))  //când a ieșit din Laponia
		{
			printf("TOO MUCH SNOW !\n");
			break;
		}

		if(a[startx][starty].nr > 0)     // dacă există cadou
		{
			k++;   //se mărește nr. de cadouri din sac 

			if(k >= dim_max)   //dacă nu mai are loc în sac, realoc dimensiunea acestuia 
			{
				dim_max = dim_max * 2;
				sac = realloc(sac, dim_max * sizeof(cadou));
			}

			if( k < dim_max)   //dacă are loc în sac, il adaug
			{
				strcpy(sac[k].oras, a[startx][starty].oras);
				strcpy(sac[k].tip, a[startx][starty].tip_cadou);
				a[startx][starty].nr--;  //scade nr. de cadouri din zonă
			}
		}

		switch(a[startx][starty].directie)
		{
			case 'U': startx--; break;
			case 'D': startx++; break;
			case 'L': starty--; break;
			case 'R': starty++; break;
		}
		nr++;  //crește nr. de pași
	}

	free(a);  //eliberez memoria alocată lui a

	printf("%d\n", nr);      //afișez nr. de pași realizați de Moș Crăciun
	printf("%d\n", k + 1);   //afișez nr. de cadouri adunate

	int dim = 0;   // dim = dimensiunea sacului auxiliar

	//cadourile din sac sunt ordonate alfabetic după oraș, și apoi alfabetic după tip
	qsort(sac, k + 1, sizeof(cadou), cmp); 

	//aux = sac auxiliar în care fiecare element (oraș, tip_cadou) apare o singură dată
	unic *aux = malloc(sizeof(unic));   

	int i = 0; 
	int j;

	while(i <= k){

		j = i + 1;

		while((j <= k) && (strcmp(sac[i].oras, sac[j].oras) == 0) && strcmp(sac[i].tip, sac[j].tip) == 0)
			j++;

		dim++;

		if(dim != 1) aux = realloc(aux, dim * sizeof(unic));  //realoc dimensiunea sacului auxiliar
		strcpy(aux[dim - 1].oras, sac[i].oras);
		strcpy(aux[dim - 1].tip, sac[i].tip);
		aux[dim - 1].nr = j - i;  //rețin nr. de orașe + tipul de cadou (cele care sunt identice)
		i = j;
	}

	free(sac);  //eliberez memoria alocată sacului

	qsort(aux, dim, sizeof(unic), cmp_unic);
	//orasele sunt ordonate lexicografic,
    //cadourile sunt ordonate descrescător după numarul de apariții
    //dacă două sau mai multe tipuri de daruri au același număr de apariții atunci se ordonează lexicografic

    i = 0;

    while(i < dim) {
    	printf("%s:\n", aux[i].oras);
    	printf("  %d %s\n", aux[i].nr, aux[i].tip);

    	j = i + 1;

    	while((j < dim) && (strcmp(aux[i].oras, aux[j].oras) == 0))
    	{
    		printf("  %d %s\n", aux[j].nr, aux[j].tip);
    		j++;
    	}
    	i = j;
    }
    free(aux);  //eliberez memoria alocată lui aux

    return 0;
}