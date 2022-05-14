// NHANH CAN TSP

#include <stdio.h>
#define size 30

/*Khai bao*/
typedef struct {
	float do_dai;
	int dau, cuoi;
	int da_dung;
}canh;

void read_file(char file_name, canh a[][size], int *n){
	int i,j;
	FILE *f;
	f = fopen("TSP1.txt", "r");
	if(f==NULL){
		printf("Loi mo file!");
		return;
	}
	
	fscanf(f, "%d", n);
	
	for(i=0; i<*n; i++)
		for(j=0; j<*n; j++){
			fscanf(f, "%f", &a[i][j].do_dai);
			a[i][j].dau = i;
			a[i][j].cuoi = j;
			a[i][j].da_dung = 0;
		}
	fclose(f);
}

void in_ma_tran(canh a[][size], int n){
	int i,j;
	printf("\nMa tran TRONG SO cua do thi la:\n");
	for(i=0; i<n; i++){
		for(j=0; j<n; j++)
			printf("%c%c = %5.2f", a[i][j].dau+97, a[i][j].cuoi+97, a[i][j].do_dai);
			printf("\n");
	}
}

void in_PA(canh PA[], int n){
	int i;
	float sum = 0.0;
	printf("\nPhuong an TSP bang NC:\n");
	for(i=0; i<n; i++){
		sum += a[i].do_dai;
		printf("Canh %c%c = %5.2f\n", PA[i].dau+97, PA[i].cuoi+97, PA[i].do_dai);
	}
	printf("Chu trinh: ");
	for(i=0; i<n; i++){
		printf("%c", PA[i].dau+97);
		printf("-> ");
	}
	printf("%c", PA[0].dau+97);
	printf("Tong do dai canh = %5.2f", sum);
}

float canh_NN(canh a[][size], int n){
	float Cmin = 3.40282e+38;
	int i,j;
	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
			if(i!=j && !a[i][j].da_dung && a[i][j].do_dai < Cmin)
				Cmin = a[i][j].do_dai;
	return Cmin;
}

float can_duoi(canh a[][size], float TGT, int i, int n){
	return TGT + (n-i) * canh_NN(a, n);
}

void Cap_Nhat_PA_TNTT(canh a[][size], int n, float TGT, float *GNNTT, canh x[], canh PA[]){
	int i;
	x[n-1] = a[x[n-2].cuoi][x[0].dau];
	TGT = TGT + x[n-1].do_dai;
	if(*GNNTT > TGT){
		*GNNTT = TGT;
		for(i=0; i<n; i++)
			PA[i] = x[i];
	}
}

int co_chu_trinh(cach x[], int k, int ke_tiep){
	int i=0, co_CT=0;
	while(i<k && !co_CT)
		if(ke_tiep == x[i].dau)
			co_CT = 1;
		else
			i++;
	return co_CT;
}

void Nhanh_Can(cach a[][size], int n, int i, int dau, float *TGT, float *CD, float *GNNTT, cach x[], cach PA[]){
	int j;
	for(j=0; j<n; j++)
		if(dau!=j && !a[dau][j].da_dung && !co_chu_trinh(x, i, j)){
			*TGT = *TGT + a[dau][j].do_dai;
			*CD = can_duoi(a, *TGT, i+1, n);
			if(*CD > *GNNTT){
				x[i] = a[dau][j];
				a[dau][j].da_dung = 1;
				a[j][dau].da_dung = 1;
				
				
				if(i == n-2){
					Cap_Nhat_PA_TNTT(a, n, *TGT, GNNTT, x, PA;
				}
				else
					Nhanh_Can(a, n, i+1, j, TGT, CD, GNNTT, x, PA);
			}
			*TGT = *TGT - a[dau][j].do_dai;
			a[dau][j].da_dung = 0;
			a[j][dau].da_dung = 0;	
		}
}

void reset(canh a[][size], int n){
	int i,j;
	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
			a[i][j].da_dung = 0;
}
	
int main(){
	canh a[size][size];
	int n;
	printf("\nPhuong an TSP dung thuat toan NC:\n");
	read_file("TSP.txt", a, &n);
	canh PA[n];
	canh xx[n];
	char tpxp, yn;
	while(1){
		fflush(stdin);
		in_ma_tran(a, n);
		printf("\nNhap 1 thanh pho tu a den %c ", n-1+97);
		scanf("%c", &tpxp);
		Nhanh_Can(a, n, 0, tpxp-97, &TGT, &CD, &GNNTT, x, PA);
		in_PA(PA, n);
		fflush(stdin);
		printf("Tiep tuc Y/N?");
		scanf("%c", &yn);
		if(yn == 'N' || yn == 'n')
			break;
		reset(a, n);
	}
	return 0;
}

