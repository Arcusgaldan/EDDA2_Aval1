#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trp.h"
#define TAMPACOTE 69

int checaFlag(Pacote pacote){
	if(pacote.inicioTermino != 0 && pacote.inicioTermino != 2 && pacote.inicioTermino != 3){
		return 0;
	}
	return 1;
}

int checaParidade(char *binario){
    int i;
    int soma = 0;
    for(i = 0; i <= TAMPACOTE; i++){
        if(binario[i] == '1')
            soma++;
    }
    if(soma%2 == 0){
        return 1;
    }else{
        return 0;
    }
}

void imprimePacote(Pacote pacote){
    printf("Identificador da mensagem: %i\n", pacote.idMensagem);
    printf("Identificador do pacote: %i\n", pacote.idPacote);
    printf("Remetente: %i\n", pacote.remetente);
    printf("Destinatario: %i\n", pacote.destinatario);
    printf("Flag de posição: %i\n", pacote.inicioTermino);
    printf("Dados: %s\n", pacote.dados);
    printf("Paridade: %i\n", pacote.paridade);
    printf("--------------------------------------------------------------------------------\n");
}

void imprimeMensagem(Fila *mensagem){
    Pacote aux;
    printf("ID da Mensagem: %i\n", mensagem->fim->pacote.idMensagem);
    printf("Remetente: %i\n", mensagem->fim->pacote.remetente);
    printf("Destinatário: %i\n", mensagem->fim->pacote.destinatario);
    printf("Mensagem: ");
    while(!filaVazia(mensagem)){
        aux = filaRemover(mensagem);
        printf("%s", aux.dados);
    }
    printf("\n");
    printf("################################################################################\n");
}

int binarioDecimal(char *binario){
    int i = strlen(binario) - 1, j = 1, aux = 0;
    for(i; i >= 0; i--){
        if(binario[i] != '0' && binario[i] != '1'){
            return -1;
        }
        aux += (binario[i] - 48) * j;
        j *= 2;
    }
    return aux;
}

Pacote binarioPacote(char *binario){
    Pacote pacote;
    if(strlen(binario) != TAMPACOTE){
        pacote.paridade = -1;
        return pacote;
    }
    int i = 0, j = 0;
    char *aux = malloc(32 * sizeof(char));
    for(i; i < 8; i++){
        aux[j] = binario[i];
        j++;
    }
    aux[j] = '\0';
    j = 0;
    pacote.idMensagem = binarioDecimal(aux);
    for(i; i < 16; i++){
        aux[j] = binario[i];
        j++;
    }
    aux[j] = '\0';
    j = 0;
    pacote.idPacote = binarioDecimal(aux);
    for(i; i < 25; i++){
        aux[j] = binario[i];
        j++;
    }
    aux[j] = '\0';
    j = 0;
    pacote.remetente = binarioDecimal(aux);
    for(i; i < 34; i++){
        aux[j] = binario[i];
        j++;
    }
    aux[j] = '\0';
    j = 0;
    pacote.destinatario = binarioDecimal(aux);
    for(i; i < 36; i++){
        aux[j] = binario[i];
        j++;
    }
    aux[j] = '\0';
    j = 0;
    pacote.inicioTermino = binarioDecimal(aux);
    for(i; i < 44; i++){
        aux[j] = binario[i];
        j++;
    }
    aux[j] = '\0';
    j = 0;
    pacote.dados[0] = binarioDecimal(aux);
    for(i; i < 52; i++){
        aux[j] = binario[i];
        j++;
    }
    aux[j] = '\0';
    j = 0;
    pacote.dados[1] = binarioDecimal(aux);
    for(i; i < 60; i++){
        aux[j] = binario[i];
        j++;
    }
    aux[j] = '\0';
    j = 0;
    pacote.dados[2] = binarioDecimal(aux);
    for(i; i < 68; i++){
        aux[j] = binario[i];
        j++;
    }
    aux[j] = '\0';
    j = 0;
    pacote.dados[3] = binarioDecimal(aux);
    pacote.dados[4] = '\0';
    pacote.paridade = binario[i] - 48;

    free(aux);
    return pacote;
}

char *intBinario(int num, int tam){
	if(num < 0){
        return NULL;
    }
	char *aux = malloc((tam+1) * sizeof(char));
	int i;
	aux[tam] = '\0';
	for(i = tam-1; num >= 2; i--){
        if(i == 0){
            return NULL;
        }
        aux[i] = (num % 2) + 48;
        num /= 2;
    }
    aux[i] = num + 48;
    i--;
    while(i >= 0){
        aux[i] = 48;
        i--;
    }
}

char *pacoteBinario(Pacote pacote){
    int num, i, tam;
    char *binario = malloc(70 * sizeof(char));
    char *aux;
    binario = strcpy(binario, "");
	
	num = pacote.idMensagem;
    tam = 8;
	aux = intBinario(num, tam);
    binario = strcat(binario, aux);
    
	num = pacote.idPacote;
    aux = intBinario(num, tam);
    binario = strcat(binario, aux);
    
	num = pacote.remetente;
    tam = 9;
    aux = intBinario(num, tam);
    binario = strcat(binario, aux);
    
	num = pacote.destinatario;
    aux = intBinario(num, tam);
    binario = strcat(binario, aux);
    
	num = pacote.inicioTermino;
    tam = 2;
    aux = intBinario(num, tam);
    binario = strcat(binario, aux);
    
	num = pacote.dados[0];
    tam = 8;
    aux = intBinario(num, tam);
    binario = strcat(binario, aux);
    
	num = pacote.dados[1];
    aux = intBinario(num, tam);
    binario = strcat(binario, aux);
    
	num = pacote.dados[2];
    aux = intBinario(num, tam);
    binario = strcat(binario, aux);
    
	num = pacote.dados[3];
    aux = intBinario(num, tam);
    binario = strcat(binario, aux);

    if(pacote.paridade == 1){
        binario = strcat(binario, "1\0");
    }else{
        binario = strcat(binario, "0\0");
    }
    return binario;
}

int main(int argc, char **argv){
    char *binario = malloc(70 * sizeof(char));
    FILE *arq;
    Lista *l = ListaNovo(l);
    Pacote pacote;
    if(argc == 2){
        printf("Abrindo o arquivo %s\n", argv[1]);
        arq = fopen(argv[1], "r+");
        if(arq == NULL){
            printf("Arquivo não existente.\n");
            return 1;
        }
        while(fgets(binario, TAMPACOTE+1, arq) != NULL){
            int aux;
            pacote = binarioPacote(binario);
            if(pacote.paridade != -1){
                imprimePacote(pacote);
                if(checaParidade(binario)){
                    if(checaFlag(pacote)){
                        aux = GuardarPacote(l, pacote);
                    }else{
                        printf("Flag de inicio/termino invalido.\n");
                    }
                }else{
                    printf("Pacote acima com paridade invalida: erro de transmissao.\n");
                }
                if(aux == 2){
                    printf("Mensagem terminada!\n");
                    imprimeMensagem(RemoverMensagem(l, pacote.idMensagem));
                    getchar();
                }
            }
        }
        fclose(arq);
    }else if(argc != 1){
        printf("Uso incorreto dos argumentos do programa.\n");
        return 1;
    }

    int opc;
    do{
        printf("1 - Adicionar novo pacote em binario\n");
        printf("2 - Adicionar novo pacote em decimais e caracteres\n");
        printf("3 - Sair\n");
        printf("\nOpcao: ");
        scanf("%i", &opc);

        if(opc == 1){
            printf("Insira o código binario: ");
        	scanf(" %69s", binario);
        	fflush(stdin);
        	if(strlen(binario) < 69){//Verifica se o binario fornecido pelo usuario tem a quantidade de caracteres necessaria
        		printf("Codigo invalido.\n");
			}else{
				int aux;
	            pacote = binarioPacote(binario);
	            if(pacote.paridade != -1){
	                imprimePacote(pacote);
	                if(checaParidade(binario)){
	                	if(checaFlag(pacote)){
	                    	aux = GuardarPacote(l, pacote);
						}else{
							printf("Flag invalida no apacote acima.\n");
						}
	                }else{
	                    printf("Pacote acima com paridade invalida: erro de transmissao.\n");
	                }
	                if(aux == 2){
	                    printf("Mensagem terminada!\n");
	                    imprimeMensagem(RemoverMensagem(l, pacote.idMensagem));
	                    getchar();
	                }
	            }
			}
        }else if(opc == 2){
            printf("Insira o ID da Mensagem: ");
			scanf(" %i", &pacote.idMensagem);
			printf("Insira o ID do Pacote: ");
			scanf(" %i", &pacote.idPacote);
			printf("Insira o Remetente: ");
			scanf(" %i", &pacote.remetente);
			printf("Insira o Destinatario: ");
			scanf(" %i", &pacote.destinatario);
			printf("Insira a Flag de Posicao (0 para meio, 2 para inicio e 3 para fim): ");
			scanf(" %i", &pacote.inicioTermino);
			if(pacote.inicioTermino != 0 && pacote.inicioTermino != 2 && pacote.inicioTermino != 3){
                printf("Flag de inicio/termino invalida.\n");
                continue;
			}
			printf("Insira os 4 caracteres da mensagem: ");
			scanf( "%4s", pacote.dados);
			printf("Insira a paridade: ");
			scanf(" %i", &pacote.paridade);
			if(pacote.paridade != 1 && pacote.paridade != 0){
				printf("Paridade invalida (1 ou 2).\n");
				continue;
			}
			int aux;
			binario = pacoteBinario(pacote);
			imprimePacote(pacote);
			if(checaParidade(binario)){
                aux = GuardarPacote(l, pacote);
			}else{
                printf("Pacote com paridade invalida: erro de transmissao\n");
			}

            if(aux == 2){
                printf("Mensagem terminada!\n");
                imprimeMensagem(RemoverMensagem(l, pacote.idMensagem));
                getchar();
            }
        }
    }while(opc != 3);

    printf("IDs das mensagens faltando: ");
    NoLista *msg = l->Primeiro;
    while(msg != NULL){
        printf("%i  ", msg->fila->fim->pacote.idMensagem);
        msg = msg->Proximo;
    }
    printf("\n");
    free(msg);
    msg = NULL;

    free(l);
    free(binario);
    l = NULL;
    binario = NULL;
    return 0;
}
