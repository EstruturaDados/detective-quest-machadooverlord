#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Sala {
    char nome[50];
    char pista[100];
    struct Sala *esquerda;
    struct Sala *direita;
};

struct PistaNode {
    char texto[100];
    struct PistaNode *esquerda;
    struct PistaNode *direita;
};

struct PistaNode *arvorePistas = NULL;

struct Sala* criarSala(char *nome, char *pista) {
    struct Sala *novaSala = (struct Sala*)malloc(sizeof(struct Sala));
    strcpy(novaSala->nome, nome);
    if(pista != NULL) {
        strcpy(novaSala->pista, pista);
    } else {
        strcpy(novaSala->pista, "");
    }
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

struct PistaNode* inserirPista(struct PistaNode *raiz, char *texto) {
    if(raiz == NULL) {
        struct PistaNode *novaPista = (struct PistaNode*)malloc(sizeof(struct PistaNode));
        strcpy(novaPista->texto, texto);
        novaPista->esquerda = NULL;
        novaPista->direita = NULL;
        return novaPista;
    }
    
    if(strcmp(texto, raiz->texto) < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, texto);
    }
    else if(strcmp(texto, raiz->texto) > 0) {
        raiz->direita = inserirPista(raiz->direita, texto);
    }
    
    return raiz;
}

void exibirPistas(struct PistaNode *raiz) {
    if(raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("- %s\n", raiz->texto);
        exibirPistas(raiz->direita);
    }
}

void explorarSalas(struct Sala *salaAtual) {
    char opcao;
    
    while(salaAtual != NULL) {
        printf("\n--!--\n");
        printf("Voce esta em: %s\n", salaAtual->nome);
        
        if(strcmp(salaAtual->pista, "") != 0) {
            printf("\n*** PISTA ENCONTRADA: %s ***\n", salaAtual->pista);
            arvorePistas = inserirPista(arvorePistas, salaAtual->pista);
        }
        
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
    printf("\nBem-vindo ao Detective Quest - Nivel Aventureiro!\n");
    printf("Explore a mansao e encontre pistas...\n");
    
    struct Sala *hallEntrada = criarSala("Hall de Entrada", NULL);
    struct Sala *biblioteca = criarSala("Biblioteca", "Livro com pagina rasgada");
    struct Sala *cozinha = criarSala("Cozinha", "Faca com manchas");
    struct Sala *saladeEstar = criarSala("Sala de Estar", "Copo quebrado no chao");
    struct Sala *sotao = criarSala("Sotao", "Carta antiga amarelada");
    struct Sala *quarto = criarSala("Quarto Principal", "Relogio parado as 3h");
    struct Sala *jardim = criarSala("Jardim", NULL);
    
    hallEntrada->esquerda = biblioteca;
    hallEntrada->direita = cozinha;
    
    biblioteca->esquerda = saladeEstar;
    biblioteca->direita = sotao;
    
    cozinha->esquerda = quarto;
    cozinha->direita = jardim;
    
    explorarSalas(hallEntrada);
    
    printf("\n==!==\n");
    printf("PISTAS COLETADAS (ordem alfabetica):\n");
    printf("==!==\n");
    
    if(arvorePistas != NULL) {
        exibirPistas(arvorePistas);
    } else {
        printf("Nenhuma pista foi coletada.\n");
    }
    
    printf("\nObrigado por jogar Detective Quest!\n");
    
    return 0;
}