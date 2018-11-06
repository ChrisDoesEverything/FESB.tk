/*2. Napisati program koji omogu�ava rad s binarnim stablom pretra�inja. Element stabla sastoji se od godine ro�enja i
mati�nog broja studenta. Treba omogu�iti uno�enje podataka u stablo iz datoteke (vode�i ra�una da je podatak za
pretra�ivanje mati�ni broj). Tako�er, potrebno je napisati funkciju koja �e ispisati sve elemente stabla koji imaju
godinu ro�enja raniju od zadane.*/

#include<stdio.h>
#include<stdlib.h>

typedef struct stablo* cvor;
struct stablo
{
	int mbroj;
	int godina;
	cvor desno;
	cvor lijevo;
};

cvor DodajUStablo(int mbr,int god,cvor T)
{
	if(T==NULL)
	{
		T=(cvor)malloc(sizeof(struct stablo));
		T->mbroj=mbr;
		T->godina=god;
		T->desno=NULL;
		T->lijevo=NULL;
	}
	else if(mbr<T->mbroj)
		T->lijevo=DodajUStablo(mbr,god,T->lijevo);
	else if(mbr>T->mbroj)
		T->desno=DodajUStablo(mbr,god,T->desno);
	return T;
}

cvor UcitajStablo(cvor T)
{
	FILE* dat=fopen("stablo.txt","r");
	int x,y;
	if(dat==NULL)
		printf("Greska pri otvaranju!\n");
	else
	{
		while(feof(dat)==0)
		{
			fscanf(dat,"%d %d",&x,&y);
			T=DodajUStablo(x,y,T);
		}
	}
	return T;
}

void ObidjiStablo(cvor T,int x)
{
	if(T)
	{
		ObidjiStablo(T->desno,x);
		if(T->godina<x)
			printf("%d %d\n",T->mbroj,T->godina);
		ObidjiStablo(T->lijevo,x);
	}
}

void main()
{
	cvor root=NULL;
	int g;
	root=UcitajStablo(root);
	printf("Unesite godinu: ");
	scanf("%d",&g);
	ObidjiStablo(root,g);
}