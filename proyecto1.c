#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void triangular(double* x, double* y);
void stfTriangular(double* x, double* y,int n);

double T = 5; //Periodo de la funcion
double ciclos = 10; //ciclos totales de la función
double puntos = 1000; //puntos de la función

double PI = 3.14159265;

int main(int argc, char* argv[]){

	double abscisas[(int)puntos];
	double ordenadas[(int)puntos];

	double stfx[(int)puntos]; //abscisas de la STF
	double stfy[(int)puntos]; //ordenadas de la STF

	int i;


	FILE* archivo=NULL;

	triangular(abscisas,ordenadas);
	stfTriangular(stfx,stfy,1000);

	if((archivo=fopen("plotear.txt","w")) == NULL){
		printf("Error abriendo el archivo");
		exit(0);
	}

	for(i=0;i<puntos;i++){
		fprintf(archivo,"%lf\t%lf\n",stfx[i],stfy[i]);
	}

	fclose(archivo);
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

	//Llenamos al arreglo de abscisas de puntos
        for(i=0;i<puntos;i++){
                *(x+i) = (i*ciclos*T)/puntos; // ciclos*periodo/puntos
        }

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
