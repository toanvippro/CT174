// B2012048-Nguyenngoctran
// Bai toan Tam giac so
// Giai bai toan bang thuat toan QUY HOACH DONG

#include <stdio.h>
#define size 50

void ReadData(int a[][size], int *n){
	FILE *f;
	f=fopen("tam_giac_so.txt", "r");
	if(f==NULL){
		printf("Loi mo file!!!\n");
		return;
	}
	int i=0, j;	
	while (!feof(f)){
		for(j=0; j<=i; j++)
			fscanf(f, "%d", &a[i][j]); 
		i++;
		}
	*n=i;
	fclose(f);
}

void PrintData(int a[][size], int n){
	int i,j;
	printf("\nTAM GIAC SO da cho\n");
	for(i=0; i<n; i++){
		for(j=0; j<=i; j++)
			printf("%5d", a[i][j]);
		printf("\n");
	}
}

int CS_max(int F[][size], int i, int j){
	if (j==0)
		return (F[i-1][0]>F[i-1][1])? 0:1;
	if (j==i)
		return i-1;
	if (j==i-1)
		return (F[i-1][i-2]>F[i-1][i-1])? i-2:i-1;
	
	if (F[i-1][j-1]>F[i-1][j]&&F[i-1][j-1]>F[i-1][j+1])
		return j-1;
	if (F[i-1][j]>F[i-1][j-1]&&F[i-1][j]>F[i-1][j+1])
		return j;
	if (F[i-1][j+1]>F[i-1][j]&&F[i-1][j+1]>F[i-1][j-1])
		return j+1;
}

// Dung cong thuc truy hoi de tao bang F
void Tao_Bang(int a[][size], int n, int F[][size]){
 	int i, j;
	 // 2 dong dau tien cua bang F xac dinh cu the
 		F[0][0]= a[0][0];
 		F[1][0]= F[0][0] + a[1][0];
 		F[1][1]= F[0][0] + a[1][1];
 	// Tu dong thu 3 (i=2) tro ve sau
	// Moi phan tu cua bang F duoc xac dinh nho vao dong truoc do (truy hoi)
	 for(i=2; i<n; i++)
		 for(j=0; j<=i; j++){
			 int k=CS_max(F,i,j);
			 F[i][j] = F[i-1][k] + a[i][j];
	 }
}

void In_Bang(int n, int F[][size]){
	int i, j;
	printf("\nBang F\n");
	for(i=0; i<n; i++){
		for(j=0; j<=i; j++)
		 	printf("%5d", F[i][j]);
		printf("\n");
	}
}

int CS_max_dong_cuoi(int F[], int j){
	int somax=F[0];
	int maxindex=0;
	int k;
	
	for(k=1; k<=j; k++)
		if (F[k]>somax){
			somax=F[k];
			maxindex=k;
		}
	return maxindex;
}

// Tra bang F, nhung xac dinh phuong an tu trong tam giac so (bang a)

void Tra_Bang(int a[][size], int n, int F[][size], int PA[]){
	int i,j;
	// Xac dinh chi so j cua phan tu lon nhat o dong cuoi trong bang F
	j=CS_max_dong_cuoi(F[n-1],n-1);
	
	// Phan tu cuoi cung cua duong di tuc la PA[n-1]
	// la phan tu cua dong cuoi cung bang a, ung voi cot j vua tim thay o tren
	PA[n-1]=a[n-1][j];
	
	// Xet cac dong cua bang F, tu dong n-1 den dong 1
	// De xac dinh cac phan tu cua PA tu PA[n-2] den PA[0]
	
	for(i=n-1; i>=1; i--){
		
		// Can cu vao chi so cot j cua dong cuoi (dong i) cua bang F
		// ma xac dinh chi so cot j cua dong tren (dong i-1) cua bang F
		
		j=CS_max(F,i,j);
		
		// PA[i-1] la phan tu cua dong i-1 cua tam giac so a,
		// ung voi cot j vua tim thay o tren
		
		PA[i-1]=a[i-1][j];
	}
}

int GiaPA(int PA[], int n){
	int i;
	int sum=0;
	for(i=0; i<n; i++)	sum+=PA[i];
	return sum;
}

void PrintPA(int PA[], int n){
	int i;
	printf("\nPhuong an la duong di qua cac so : ");
	printf("\%d", PA[0]);
	for(i=1; i<n; i++)	printf(" => %d", PA[i]);
	printf("\n\nTong cac so tren duong di la %d\n", GiaPA(PA,n));
}	

int main(){
	int a[size][size]; //Luu tam giac so
	int n;
	
	printf("\nBai toan TAM GIAC SO dung thuat toan QUY HOACH DONG\n");
	ReadData(a,&n);
	PrintData(a,n);
	
	int PA[n]; 	//Phuong an toi uu: mang co n phan tu
	int F[n][size]; 	//Bang F: mang 2 chieu co n dong, n cot
	
	Tao_Bang(a,n,F);
	In_Bang(n,F);
	
	Tra_Bang(a,n,F,PA);
	PrintPA(PA,n);
	
	return 0;
}
