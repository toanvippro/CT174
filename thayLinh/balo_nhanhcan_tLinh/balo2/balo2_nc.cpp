#include <stdio.h>
#include <string.h>
#include <malloc.h>
typedef struct {
	char TenDV[50];
	float TL, GT, DG;
	int SL, PA;
	
}DoVat;

DoVat *readfile(float *W, int *n){
	FILE *f;
	f= fopen ("CaiTui3.TXT", "r");
	fscanf(f, "%f", W);
	DoVat *dsdv;
	dsdv=(DoVat*)malloc(sizeof(DoVat));
	int i=0;
	while (!feof(f)){
		fscanf(f," %f%f%d%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].SL,  &dsdv[i].TenDV);
		dsdv[i].DG=dsdv[i].GT/dsdv[i].TL;
		dsdv[i].PA=0;
		i++;
		dsdv=(DoVat*)realloc(dsdv, sizeof(DoVat)*(i+1));
	}
	*n=i;
	fclose(f);
	return dsdv;
}

void swap(DoVat *x, DoVat *y){
	DoVat temp;
	temp=*x;
	*x=*y;
	*y=temp;
}

void bubblesort(DoVat *dsdv, int n){
	int i, j;
	for(i=0;i<=n-2; i++){
		for(j=n-1; j>=i+1; j--){
			if(dsdv[j].DG > dsdv[j-1].DG)
				swap(&dsdv[j], &dsdv[j-1]);
			
		}
	}
}

void InDSDV(DoVat *dsdv ,int n, float W){
	int i;
	float TongTL=0.0, TongGT=0.0;
	printf("\nPhuong an Cai Ba lo 2 dung thuat toan NHANH CAN nhu sau:\n");
	printf("|---|--------------------|---------|---------|---------|---------|-----------|\n");
	printf("|STT|     Ten Do Vat     |T. Luong | Gia Tri |So luong | Don gia | Phuong an |\n");
	printf("|---|--------------------|---------|---------|---------|---------|-----------|\n");
	for(i=0;i<n;i++){
		printf("|%2d |%-20s|%9.2f|%9.2f|%5d    |%9.2f|%6d     |\n",
		i+1,dsdv[i].TenDV,dsdv[i].TL,dsdv[i].GT,dsdv[i].SL,dsdv[i].DG, dsdv[i].PA);
		TongTL=TongTL+dsdv[i].PA * dsdv[i].TL;
		TongGT=TongGT+dsdv[i].PA * dsdv[i].GT;
	}	
	printf("|---|--------------------|---------|---------|---------|---------|-----------|\n");	
	printf("Trong luong cua ba lo = %-9.2f\n",W);
	printf("Tong trong luong = %-9.2f\n",TongTL);
	printf("Tong gia tri = %-9.2f\n",TongGT);
}


void taonutgoc(float w, float *v, float *ct, float *glntt, float *tgt, float dg_max){
	*tgt=0.0;
	*v=w;
	*ct=*v *dg_max;
	*glntt=0.0;
	
}

void Cap_Nhat_GLNTT(float TGT, float *GLNTT, int x[], DoVat *dsdv, int n){
	 int i;
	 if(*GLNTT < TGT){
		 *GLNTT = TGT;
		 for(i=0;i<n;i++)
		 	dsdv[i].PA=x[i];
	 }
}


int min(int a, int b){
	return a<b ? a:b;
}


void Nhanh_Can(int i, float *TGT, float *CT, float *V, float *GLNTT, int x[], DoVat *dsdv, int n){
	 int j; 	// j la so vat duoc chon
	 int yk; 	// So do vat lon nhat co the chon
	 yk = min(dsdv[i].SL, *V/dsdv[i].TL);	
	 for(j = yk; j>=0; j--){	// Xet tat ca cac kha nang co the phan nhanh theo so luong do vat
	 		// Ung voi mot gia tri cua j la mot nut tren cay 
	 		// Tinh 3 dai luong cua mot nut trong
	 		
		 *TGT = *TGT + j*dsdv[i].GT;
		 *V = *V - j*dsdv[i].TL;
		 *CT = *TGT + *V * dsdv[i+1].DG;	// dsdv[i+1].DG la DG vat ke tiep cua vat i (i + 1)
		
		 if(*CT > *GLNTT){ 					// Truong hop Chua cat tia (Dieu kien Cat tia la khi CT <= GLNTT)
			x[i] = j;
		 	if((i==n-1)||(*V==0)) 		// Da xet het tat ca cac do vat hoac ba lo da day
		 		Cap_Nhat_GLNTT(*TGT, GLNTT, x, dsdv, n);
		 	else
		 		Nhanh_Can(i+1, TGT, CT, V, GLNTT, x, dsdv, n); //Xet nut con cua nut i
	 	}
	 // Quay lui xet nut khac
	 x[i] = 0;
	 *TGT = *TGT - j*dsdv[i].GT;	// Tra lai Tong gia tri cua nut cha
	 *V = *V + j*dsdv[i].TL;		// Tra lai Trong luong con lai cua nut cha
	 }
}


int main(){
	DoVat *dsdv;
	int n;
	 float w, CT, TGT, V, GLNTT;
	 dsdv= readfile(&w, &n);
	 int x[n];
	 bubblesort(dsdv, n);
	 taonutgoc(w, &V, &CT, &GLNTT, &TGT, dsdv[0].DG);
	 Nhanh_Can(0, &TGT, &CT, &V, &GLNTT, x, dsdv, n);
	InDSDV(dsdv,n,w);
	
	free(dsdv);
	return 0;
}















