#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
};

struct Sala* criarSala(char *nome) {
    struct Sala *novaSala = (struct Sala*)malloc(sizeof(struct Sala));
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

void explorarSalas(struct Sala *salaAtual) {
    char opcao;
    
    while(salaAtual != NULL) {
        printf("\n--!--\n");
        printf("Voce esta em: %s\n", salaAtual->nome);
        printf("--!--\n");
        
        if(salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("Esta sala nao tem mais caminhos! Fim da exploracao.\n");
            break;
        }
        
        printf("\nEscolha seu caminho:\n");
        if(salaAtual->esquerda != NULL) {
            printf("(e) Ir para esquerda\n");
        }
        if(salaAtual->direita != NULL) {
            printf("(d) Ir para direita\n");
        }
        printf("(s) Sair da exploracao\n");
        printf("\nOpcao: ");
        scanf(" %c", &opcao);
        
        if(opcao == 'e' && salaAtual->esquerda != NULL) {
            salaAtual = salaAtual->esquerda;
        } 
        else if(opcao == 'd' && salaAtual->direita != NULL) {
            salaAtual = salaAtual->direita;
        } 
        else if(opcao == 's') {
            printf("\nVoce saiu da exploracao.\n");
            break;
        } 
        else {
            printf("\nOpcao invalida! Tente novamente.\n");
        }
    }
}

int main() {
    printf("\n=== Enigma Studios - MACHADO OVERLORD - LUCIANO ===\n");
    printf("\n=== Detective Quest ===\n");
    printf("\nBem-vindo ao Detective Quest - Nivel Novato!\n");
    printf("Explore a mansao e encontre pistas...\n");
    
    struct Sala *hallEntrada = criarSala("Hall de Entrada");
    struct Sala *biblioteca = criarSala("Biblioteca");
    struct Sala *cozinha = criarSala("Cozinha");
    struct Sala *saladeEstar = criarSala("Sala de Estar");
    struct Sala *sotao = criarSala("Sotao");
    struct Sala *quarto = criarSala("Quarto Principal");
    struct Sala *jardim = criarSala("Jardim");
    
    hallEntrada->esquerda = biblioteca;
    hallEntrada->direita = cozinha;
    
    biblioteca->esquerda = saladeEstar;
    biblioteca->direita = sotao;
    
    cozinha->esquerda = quarto;
    cozinha->direita = jardim;
    
    explorarSalas(hallEntrada);
    
    printf("\nObrigado por jogar Detective Quest!\n");
    
    return 0;
}