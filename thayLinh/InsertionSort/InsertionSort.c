#include <stdio.h>
#include <malloc.h>
typedef int keytype;
typedef float othertype;
typedef struct {
	keytype key;
	othertype otherfields;
}recordtype;
void Swap(recordtype *x, recordtype *y){
	recordtype temp;
	temp = *x;
	*x = *y;
	*y = temp;
}
void InsertionSort(recordtype a[], int n){
	int i, j;
	for(i=1; i<=n-1; i++)
		for(j=i; (j>=1 && a[j].key<a[j-1].key);j--)
			Swap(&a[j],&a[j-1]);
}
void Read_Data(recordtype a[], int *n){
	FILE *f;
	f=fopen("data.txt", "r");
	int i=0;
	if(f!=NULL)
	while (!feof(f)){
			fscanf(f, "%d%f", &a[i].key, &a[i].otherfields);
			i++;
	}else printf("Loi mo file\n");
	fclose(f);
	*n=i;
}
void Print_Data(recordtype a[], int n){
	int i;
	for(i=0; i<n; i++)
		printf("%3d%5d%8.2f\n", i+1, a[i].key, a[i].otherfields);
}
int main(){
	recordtype a[100];
	int n;
	Read_Data(a,&n);
	printf("Du lieu ban dau:\n");
	Print_Data(a,n);
	InsertionSort(a,n);
	printf("Ket qua sap xep chon:\n");
	Print_Data(a,n);
	return 0;
}







