#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#define READ 10
#define WRITE 11
#define LOAD 20
#define STORE 21
#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33
#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43
int Valida(char num_str[]);
int ValidaSinal(char);
int ValidaLimite(int );
int ValidaEntrada(int);
void ErroFatal(const int [], int , int);
void dump(const int [], int , int );
int Executar();
int Criar(int memory[100]);
void Listar(void);
int Gravalog(int operacao,char *msg,char *desc[30]) {
    setlocale(LC_ALL, "Portuguese");
    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);
    FILE* arqNome;
    if(operacao==2||operacao==1){
    arqNome=fopen("LogSimpletronn.bin","ab+");
    fprintf(arqNome,"\nNome\t\t\tData de criação\t\t\tData de execução\t\t\tDescrição\n");
    fprintf(arqNome,"%s\t\t[%d/%d/%d %d:%d:%d]\t\t[%d/%d/%d %d:%d:%d]\t\t\t%s\t",msg,
            tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,tm.tm_hour, tm.tm_min, tm.tm_sec,
            tm.tm_mday, tm.tm_mon + 1,tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec,desc);
    fclose(arqNome);
    }else if((arqNome=fopen("LogSimpletronn.bin","rb"))==NULL){
        printf("\n O arquivo LogSimpletronn.bin não pode ser aberto.");
    }else{
    while(!feof(arqNome)){
     fread(&tm,sizeof(tm),1,arqNome);
     printf("%s", tm);
     }
     fclose(arqNome);
    }
}
int main (){
setlocale(LC_ALL, "Portuguese");
int con=1;
int choice;
int memory[100];
while(choice>0||choice<=4){
 printf("\nEscolha uma opção: \n");
 printf("(1)  para Carregar/Executar um código SML\n");
 printf("(2)  para Criar um novo código SML \n");
 printf("(3)  para Pesquisar códigos existentes\n");
 printf("(4)  para Sair\n");
        scanf("\n%d",&choice);
        fflush(stdin);
        switch (choice) {
        case 1:
            Executar();
            break;
        case 2:
         Criar(memory);
           break;
        case 3:
            Gravalog(choice," "," ");
           break;
        case 4:
            return 0;
            break;
        default:
            printf("Erro,digite um valor válido!\n");
            break;
        break;
     }
    }
}
int Criar(int memory[100]){

    char filename[100];
    FILE *file;
    char desc[40];
    int i = 0; int k=1;
    fflush(stdin);
    sprintf(filename, "PROG%03d.txt", k);
    while((file = fopen(filename, "r"))){
      k++;
      sprintf(filename, "PROG%03d.txt",k);/* Teste-00.txt; Teste-01.txt; ...; Teste-99.txt */
       if(!(file = fopen(filename, "r"))){
       sprintf(filename, "PROG%03d.txt",k);
       printf("\nSerá criado o %s para a criação do código SML\n",filename);
       break;
     }
}
    file = fopen(filename, "w");
    fflush(stdin);
    printf("Digite a descrição do programa tamanho max 30:");
        if(gets(desc)&&strlen(desc)>=40){
        printf("Execedeu o limite 40\n");
        return 0;
    }
        fprintf(file,"Nome do arquivo:%s\n",filename);
        fprintf(file,"Descrição do programa max 30: %s\n",desc);

  printf("*** Digite a sentinela -99999 para ***\n");
   printf("*** encerrar a entrada do seu programa. ***\n");
    char str='+';
    Gravalog(2,filename,desc);
    for(i=0;i<100;i++){
         printf("%.2d ? ", i);
         scanf("%c%d",&str,&memory[i]);
         fflush(stdin);
        if ((memory[i]==99999)&&(str=='-')) {
			memory[i] = 0;
			i=100;
			break;
		}
		if(str!='+'){
            printf("*** Instrução errada ***\n");
		    printf("*** O operando deve começar com + ***\n");
		    printf("*** Erro inesperado na linha %d ***\n", i);
		    i--;
		    continue;
		}
        if(!ValidaLimite(memory[i])||(!ValidaEntrada(memory[i]))){
        do{
            printf("*** Instrução errada ***\n");
            printf("*** A Instrução tem que ter 5 caracteres para ser válida ***\n");
            printf("*** Erro inesperado na linha %d ***\n", i);
            printf("*** Digite novamente ***\n");
            printf("%.2d ? ", i);
            scanf("%c%d",&str,&memory[i]);
            fflush(stdin);
            break;
            fflush(stdin);
            if ((memory[i]==99999)&&(str=='-')) {
			memory[i] = 0;
			i=100;
			break;
		}
        }while(!ValidaLimite(memory[i])||(!ValidaEntrada(memory[i])));
        }
		if(memory[i]<0) {
		    printf("*** Criação de arquivo Simpletron foi iniciada com número negativo ***\n");
		    printf("*** Criação do Simpletron encerrada de forma anormal. ***\n");
		    break;
		}

		fprintf(file,"%c%d\n",str, memory[i]);

	}
    fclose(file);

}
int Executar() {

    FILE *file;
    char *result;
    int memoria[100] = {0};
    char Linha[100];
    int i = 0, j = 0, valor, aux2;
    char aux[100];
    printf("Digite o nome do arquivo a ser executado.\n");
    scanf("%s", &aux);
    fflush(stdin);
    if (!(file = fopen(aux, "r"))) {
        printf("Esse arquivo não existe.");
        return 0;
    }

    while (!feof(file)) {

        result = fgets(Linha, 100, file);
        printf("%d\n", i);

        valor = atoi(Linha);

        if (i >= 2) {
            memoria[j] = valor;
            j++;
        }
        i++;
    }
    aux2 = j;
   setlocale(LC_ALL, "Portuguese");
   for (i = 0; i < aux2; i++) {
       if (i <= 9) {
        printf("0%d +%d\n", i, memoria[i]);
       }
       if (i > 9) {
        printf("%d +%d\n", i, memoria[i]);
       }
   }
   memoria[aux2] = 99999;
   int accumulator = 0, instructionCounter = 0, instructionRegister = 0, operationCode = 0, operand = 0;

	printf("*** Carga do programa concluída ***\n");
	printf("*** Iniciando execução do programa ***\n");

	for (instructionCounter = 0; instructionCounter < 100; instructionCounter++) {

        instructionRegister = memoria[instructionCounter];
        operationCode = instructionRegister / 100;
        operand = instructionRegister % 100;

        switch (operationCode) {
        case READ:
            printf("? ");
            scanf("%d", &memoria[operand]);
            fflush(stdin);
            ErroFatal(memoria, accumulator, instructionCounter);
        break;
        case WRITE:
            printf("%d\n", memoria[operand]);
             ErroFatal(memoria, accumulator, instructionCounter);
        break;
        case LOAD:
            accumulator=memoria[operand];
            ErroFatal(memoria, accumulator, instructionCounter);
        break;
        case STORE:
            memoria[operand]=accumulator;
             ErroFatal(memoria, accumulator, instructionCounter);
        break;
        case ADD:
            accumulator+=memoria[operand];
             ErroFatal(memoria, accumulator, instructionCounter);
        break;
        case SUBTRACT:
            accumulator-=memoria[operand];
             ErroFatal(memoria, accumulator, instructionCounter);
        break;
        case DIVIDE:
            if (memoria[operand] != 0){
                 accumulator /= memoria[operand];
            }else{
                printf("*** Tentativa de divisão por zero ***\n");
            }
        break;
        case MULTIPLY:
            accumulator*=memoria[operand];
            ErroFatal(memoria, accumulator, instructionCounter);
        break;
        case BRANCH:
            instructionCounter=operand-1;
             ErroFatal(memoria, accumulator, instructionCounter);
        break;
        case BRANCHNEG:
            if (accumulator < 0){
                instructionCounter = operand-1;
            }
            ErroFatal(memoria, accumulator, instructionCounter);
        break;
        case BRANCHZERO:
            if (accumulator == 0)
            instructionCounter = operand-1;
            ErroFatal(memoria, accumulator, instructionCounter);
        break;
        case 0:
            break;
        case HALT:
            printf("*** Execução do Simpletron encerrada ***\n");
            dump(memoria, accumulator, instructionCounter);
            instructionCounter=100;
            break;
        }
	}
	dump(memoria, accumulator, instructionCounter);
}
void dump(const int memoria[], int accumulator, int instructionCounter) {
	int i, j;
	printf("REGISTERS:\n");
	if(accumulator<0){
    printf("accumulator \t\t%c%.4d\n",'-',accumulator );
	}else{
	    printf("accumulator \t\t%c%.4d\n",'+',accumulator );
	}
	printf("instructionCounter \t%3c%.2d\n", ' ',instructionCounter);
	if(accumulator<0){
    printf("accumulator \t\t%c%.4d\n",'-',memoria[instructionCounter] );
	}else{
	    printf("accumulator \t\t%c%.4d\n",'+', memoria[instructionCounter]);
	}
	printf("operationCode \t\t%3c%.2d\n", ' ',memoria[instructionCounter] / 100);
	printf("operand \t\t%3c%.2d\n\n", ' ',memoria[instructionCounter] % 100);
	printf("MEMORY : \n");
   	for(i = 0;i<10;i++)
		printf("%5d ",i); printf("\n");
	for(i = 0;i <100; i += 10) {
		printf("%1.2d  ",i);
		for(j = i;j<i+10;j++){
		    if(memoria[j]<0){
            printf("%c%.4d ",'-',-memoria[j] );
	        }else{
	        printf("%c%.4d ",'+',memoria[j]);
	        }
		}
		printf("\n");
   	}
	printf("\n");
}
void ErroFatal(const int memoria[], int accumulator, int instructionCounter){
if (accumulator<-9999||accumulator>9999) {
    printf("*** Execução do Simpletron encerrada de forma anormal. ***\n");
    dump(memoria, accumulator, instructionCounter);
 }
}
int ValidaLimite(int num) {

	if (num == -99999){
		return 1;
	}else{
		return ((num >=-9999)&&(num <=9999));
	}
}
int ValidaEntrada(int num){
int aux=(num/100);
switch (aux) {
        case READ:break;
        case WRITE:break;
        case LOAD:break;
        case STORE:break;
        case ADD:break;
        case SUBTRACT:break;
        case DIVIDE:break;
        case MULTIPLY:break;
        case BRANCH:break;
        case BRANCHNEG:break;
        case BRANCHZERO:break;
        case 0:
            break;
        case HALT:
            if(aux==HALT){
            break;
            printf("*** Execução do Simpletron encerrada ***\n");
        }
             break;
        default:printf("*** Operandos inválidos ***\n");
        break;
    }
}
int ValidaEntrada2(int num) {
int aux=(num/100);
switch (aux) {
        case READ:
            return 0;
            break;
        case WRITE:
            return 0;
            break;
        case LOAD:
            return 0;
            break;
        case STORE:
            return 0;
            break;
        case ADD:
            return 0;
            break;
        case SUBTRACT:
            return 0;
            break;
        case DIVIDE:
            return 0;
            break;
        case MULTIPLY:
            return 0;
            break;
        case BRANCH:
            return 0;
            break;
        case BRANCHNEG:
            return 0;
            break;
        case BRANCHZERO:
            return 0;
            break;
        case 0:
            return 0;
            break;
        case HALT:
            if(aux==HALT){
            return 0;
            break;
            printf("*** Execução do Simpletron encerrada ***\n");
        }
            return 0;
            break;
        default:
            printf("*** Operandos inválidos ***\n");
            return 1;
            break;
    }
}
int ValidaSinal(char str){

if(str=='+'){
    }else{
     printf("*** O operando deve começar com + ***\n");
    }
}
