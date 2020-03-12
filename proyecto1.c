#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void triangular(double* x, double* y);
void stfTriangular(double* x, double* y,int n);
void reducirError(double* x,double* yreal, double* yserie);

double T = 15; //Periodo de la funcion
double ciclos = 10; //ciclos totales de la función
double puntos = 1000; //puntos de la función

double PI = 3.14159265;

float ecm = 0.01; //Error cuadratico medio

int main(int argc, char* argv[]){

	double abscisas[(int)puntos]; //abscisas de la funcion
	double ordenadas[(int)puntos]; //ordenadas de la funcion

	//no se crean abscisas para la STF ya que son las mismas
	double stfy[(int)puntos]; //ordenadas de la STF

	int i;


	FILE* funcion = NULL; // Archivo para la funcion definida
	FILE* stf = NULL; //Archivo para la funcion por STF

	//Se calculan los valores REALES de la funcion
	triangular(abscisas,ordenadas);

	reducirError(abscisas,ordenadas,stfy);

	if((stf=fopen("stf.txt","w")) == NULL){
		printf("Error abriendo el archivo");
		exit(0);
	}

	if((funcion=fopen("normal.txt","w")) == NULL){
                printf("Error abriendo el archivo");
                exit(0);
        }

	for(i=0;i<puntos;i++){
		fprintf(funcion,"%lf\t%lf\n",abscisas[i],ordenadas[i]);
		fprintf(stf,"%lf\t%lf\n",abscisas[i],stfy[i]);
	}

	fclose(funcion);
	fclose(stf);

	//Se llama a GNUplot mediante system
	//*Ya se tiene un script para plotear los resultados
	system("gnuplot -p scriptGnuPlot.p");
	return(0);
}

void triangular(double* x,double* y){

	int i;
	int k;

	//Llenamos al arreglo de abscisas de puntos
	for(i=0;i<puntos;i++){
		*(x+i) = (i*ciclos*T)/puntos; // ciclos*periodo/puntos
	}

	//Llenamos el arreglo de ordenadas de puntos
	for(i=0;i<puntos;i++){

		for(k=0;k<ciclos;k++){
			if(*(x+i) >= 0+(k*T) && *(x+i) < (T/2)+(k*T)){
				*(y+i) = ((2/T)*(*(x+i)-(k*T)))-1;
			}
			else if(*(x+i) >= (T/2)+(k*T) && *(x+i) < T+(k*T)){
				*(y+i) = ((-2/T)*(*(x+i)-(k*T)))+1;
			}
		}
	}

}

void stfTriangular(double* x, double* y, int n){

	int i;
	double j;
	double aux = 0; //acumular resultado de la STF

	double an=0; // An de la STF
	double p=0; //parametro de coseno

	for(i=0; i<puntos; i++){
		for(j=1;j<= n;j++){
			if((int)j % 2 == 0){
				an = 0;
			}else{
				an = -4/(j*j*PI*PI);
			}

			p = (*(x+i)*2*PI*j)/T;
			aux += an*( cos(p));

		}
		*(y+i) = aux-0.5;
		aux = 0;
	}

}


void reducirError(double* x,double* yreal, double* yserie){

	double error = 0;
	int n =1; //'n' para la sumatoria de la STF
	int i = 0;

	do{
		stfTriangular(x,yserie,n);
		error = 0;
		for(i = 1; i <= puntos ; i++){
			error += (*(yserie+i)-*(yreal+i))*(*(yserie+i)-*(yreal+i));
		}
		error = error/puntos;
		n++; //Si no baja de 0.01 se calculan mas terminos para STF

	}while(error >=  ecm);

	printf("\nSe obtuvo un ECM de %lf con %d armonicos:\n",error,n);
	//printf("\nn = %d armonicos\n",n);
}
