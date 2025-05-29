#include<iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main()
{
	
	int m,n;
	srand(time(NULL));
	FILE *f=fopen("array2.txt","wt");
	cout<<"Nhap m,n:";cin>>m>>n;
	fprintf(f,"%d %d\n",m,n);
	for (int i=1;i<=m;i++)
	{
	for (int j=1;j<=n;j++)
	fprintf(f,"%6d",rand()%100+1);
	fprintf(f,"\n");
	}
	fclose(f);	
}