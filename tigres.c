#include <stdio.h>
#include <string.h>
#include "mpi.h"
void concatenar(char c,char *cadena){
  char cadenaT[2];
  cadenaT[0]=c;
  cadenaT[1]='\0';
  strcat(cadena,cadenaT);
}
int main(int argc, char *argv[]){
int procesador,nprocesador,i,suma;
int nenvio=0,vrecepcion;
char frase[]="tres tristes tigres trigaban trigo por culpa del bolivar";
int n=strlen(frase);
char a[50]="";
char b[50]="";
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&procesador);
MPI_Comm_size(MPI_COMM_WORLD,&nprocesador);
int f=n/(nprocesador);
if(procesador==0){
  for(i=(procesador)f;i<f(procesador+1);i++){
	if((frase[i]==' ')){
	  if(nenvio%2==0){
	     concatenar(' ',a);
	  }
	  else{
	     concatenar(' ',b);
	  }
	  nenvio+=1;
	}
	else{
	  if(nenvio%2==0){
	     concatenar(frase[i],a);
	  }
	  else{
	     concatenar(frase[i],b);
	  }
	}
   }
   MPI_Send(&nenvio,1,MPI_INT,1,0,MPI_COMM_WORLD);
   MPI_Send(&a,f,MPI_CHAR,1,0,MPI_COMM_WORLD);
   MPI_Send(&b,f,MPI_CHAR,1,0,MPI_COMM_WORLD);
}
else{
 if(procesador==nprocesador-1){
  MPI_Recv(&nenvio,1,MPI_INT,procesador-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
  MPI_Recv(&a,f,MPI_INT,procesador-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
  MPI_Recv(&b,f,MPI_INT,procesador-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
  for(i=(procesador)*f;i<n;i++){
	if((frase[i]==' ')){
          if(nenvio%2==0){
	     concatenar(' ',a);
	  }
	  else{
	     concatenar(' ',b);
	  }
	  nenvio+=1;
	}
	else{
	  if(nenvio%2==0){
	     concatenar(frase[i],a);
	  }
	  else{
	     concatenar(frase[i],b);
	  }
	}
       
   }
  printf("%s\n",a);
  printf("%s\n",b);
 }
 else{
  MPI_Recv(&nenvio,f,MPI_INT,procesador-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
  MPI_Recv(&a,f,MPI_INT,procesador-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
  MPI_Recv(&b,f,MPI_INT,procesador-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
  for(i=(procesador)f;i<f(procesador+1);i++){
	if((frase[i]==' ')){
	  if(nenvio%2==0){
	     concatenar(' ',a);
	  }
	  else{
	     concatenar(' ',b);
	  }
	  nenvio+=1;
	}
	else{
	  if(nenvio%2==0){
	     concatenar(frase[i],a);
	  }
	  else{
	     concatenar(frase[i],b);
	  }
	}
   }
  MPI_Send(&nenvio,1,MPI_INT,procesador+1,0,MPI_COMM_WORLD);
  MPI_Send(&a,f,MPI_INT,procesador+1,0,MPI_COMM_WORLD);
  MPI_Send(&b,f,MPI_INT,procesador+1,0,MPI_COMM_WORLD);	
}
}
MPI_Finalize();
}