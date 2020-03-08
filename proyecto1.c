#include <stdio.h>
#include <stdlib.h>

void triangular(float* x, float* y);

float T = 5; //Periodo de la funcion
float ciclos = 10; //ciclos totales de la función
float puntos = 1000; //puntos de la función

int main(float argc, float* argv[]){

	float abscisas[(int)puntos];
	float ordenadas[(int)puntos];

	int i;

	FILE* archivo=NULL;

	triangular(abscisas,ordenadas);

	if((archivo=fopen("plotear.txt","w")) == NULL){
		printf("Error abriendo el archivo");
		exit(0);
	}

	for(i=0;i<puntos;i++){
		fprintf(archivo,"%.2f\t%.2f\n",abscisas[i],ordenadas[i]);
	}

	fclose(archivo);
	return(0);
}

void triangular(float* x,float* y){

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
