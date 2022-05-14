// NHANH CAN

#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct {
	char TenDV[20];
	float TL, GT, DG;
	int SL, PA;
}DoVat;

DoVat * ReadFromFile(float *W, int *n) {
	FILE *f;
	f = fopen("CaiBaLo2.INP", "r");
	fscanf(f, "%f", W); // Xac dinh trong luong Ba lo
		DoVat *dsdv;
		dsdv = (DoVat*)malloc(sizeof(DoVat));
		int i=0;
		while (!feof(f)){
			fscanf(f, "%f%f%d%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].SL, &dsdv[i].TenDV);
			dsdv[i].DG = dsdv[i].GT / dsdv[i].TL;
			dsdv[i].PA = 0;
			i++;
			dsdv = (DoVat*)realloc(dsdv, sizeof(DoVat)*(i+1));
		}
		*n = i;
	fclose(f);
	return dsdv;
}

void Swap(DoVat *x, DoVat *y) {
	DoVat temp = *x;
	*x = *y;
	*y = temp;
}

void BubbleSort(DoVat *dsdv, int n) {
	int i,j;
	for(i=0; i<n-2; i++)
		for(j=n-1; j>=i+1; j--) {
			if(dsdv[j].DG > dsdv[j-1].DG)
				Swap(&dsdv[j], &dsdv[j-1]);
		}
}

void PrintDSDV(DoVat *dsdv, int n, float W) {
	int i;
	float TongTL = 0.0, TongGT = 0.0;
	printf("\nPhuong an Cai Ba Lo 2 dung thuat toan NHANH CAN nhu sau:\n");
	printf("|---|--------------------|---------|---------|---------|---------|-----------|\n");
	printf("|STT|     Ten Do Vat     |T. Luong | Gia Tri |So Luong | Don Gia | Phuong An |\n");
	printf("|---|--------------------|---------|---------|---------|---------|-----------|\n");
	for(i=0; i<n; i++) {
		printf("|%2d |%-20s|%9.2f|%9.2f|%5d    |%9.2f|%6d     |\n", i+1, dsdv[i].TenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].SL, dsdv[i].DG, dsdv[i].PA);
		TongTL = TongTL + dsdv[i].PA * dsdv[i].TL;
		TongGT = TongGT + dsdv[i].PA * dsdv[i].GT;
	}
	printf("|---|--------------------|---------|---------|---------|---------|-----------|\n");
	printf("Trong luong cua ba lo = %-9.2f\n", W);
	printf("Tong trong luong = %-9.2f\n", TongTL);
	printf("Tong gia tri = %-9.2f\n", TongGT);
}

// Tinh cac dai luong tai nut goc
void Tao_Nut_Goc(float W, float *V, float *CT, float *GLNTT, float *TGT, float DG_Max) {
	*TGT = 0.0;
	*V = W;
	*CT = *V * DG_Max;  // Can tren cua nut goc
	*GLNTT = 0.0;
}

// Ghi nhan phuong an tot nhat tam thoi
void Cap_Nhat_GLNTT(float TGT, float *GLNTT, int x[], DoVat *dsdv, int n) {
	int i;
	if(*GLNTT < TGT) {
		*GLNTT = TGT;
		for(i=0; i<n; i++)
			dsdv[i].PA = x[i];
	}
}

int Min(int a, int b) {
	return a < b? a:b;
}

void Nhanh_Can(int i, float *TGT, float *V, float *CT, float *GLNTT, int x[], DoVat *dsdv, int n) {
	int j;  // j la so vat duoc chon
	int yk; // So do vat lon nhat co the chon
	yk = Min(dsdv[i].SL, *V/dsdv[i].TL);
	for(j=yk; j>=0; j--) {
		// Xet tat ca cac kha nang co the phan nhanh theo so luong do vat
	 	// Ung voi mot gia tri cua j la mot nut tren cay 
	 	// Tinh 3 dai luong cua mot nut trong
	 	*TGT = *TGT + j * dsdv[i].GT;
	 	*V = *V - j * dsdv[i].TL;
	 	*CT = *TGT + *V * dsdv[i+1].DG;  // dsdv[i+1].DG la DG vat ke tiep cua vat i (i + 1)
	 	if(*CT > *GLNTT) {
	 		// Truong hop Chua cat tia (Dieu kien Cat tia la khi CT <= GLNTT)
	 		x[i] = j;
	 		if((i==n-1) || (*V==0))  // Da xet het tat ca cac do vat hoac ba lo da day
	 			Cap_Nhat_GLNTT(*TGT, GLNTT, x, dsdv, n);
	 		else
	 			Nhanh_Can(i+1, TGT, CT, V, GLNTT, x, dsdv, n);  // Xet nut con cua nut i
	 			
		 }
		 // Quay liu xet nut khac
		 x[i] = 0;
		 *TGT = *TGT - j * dsdv[i].GT;  // Tra lai Tong gia tri cua nut cha
		 *V = *V + j * dsdv[i].TL;	 // Tra lai Trong luong con lai cua nut cha	
	}
}

int main(int argc, char *argv[]) {
	DoVat * dsdv;
	int n;
	float W;
	
	float CT;
	float TGT;
	
	float V;
	float GLNTT;
	
	dsdv = ReadFromFile(&W, &n);
	
	int x[n];
	
	BubbleSort(dsdv, n);
	Tao_Nut_Goc(W, &V, &CT, &GLNTT, &TGT, dsdv[0].DG);
	Nhanh_Can(0, &TGT, &CT, &V, &GLNTT, x, dsdv, n);
	PrintDSDV(dsdv, n, W);
	
	free(dsdv);
	return 0;
}
