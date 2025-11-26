#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_HASH 10

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

struct HashNode {
    char pista[100];
    char suspeito[50];
    struct HashNode *prox;
};

struct PistaNode *arvorePistas = NULL;
struct HashNode *tabelaHash[TAM_HASH];

int funcaoHash(char *pista) {
    int soma = 0;
    int i = 0;
    while(pista[i] != '\0') {
        soma = soma + pista[i];
        i++;
    }
    return soma % TAM_HASH;
}

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

void inserirNaHash(char *pista, char *suspeito) {
    int pos = funcaoHash(pista);
    
    struct HashNode *novo = (struct HashNode*)malloc(sizeof(struct HashNode));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->prox = tabelaHash[pos];
    tabelaHash[pos] = novo;
}

char* buscarSuspeito(char *pista) {
    int pos = funcaoHash(pista);
    struct HashNode *temp = tabelaHash[pos];
    
    while(temp != NULL) {
        if(strcmp(temp->pista, pista) == 0) {
            return temp->suspeito;
        }
        temp = temp->prox;
    }
    return NULL;
}

int contarPistas(struct PistaNode *raiz, char *nomeSuspeito) {
    if(raiz == NULL) {
        return 0;
    }
    
    int total = 0;
    char *susp = buscarSuspeito(raiz->texto);
    
    if(susp != NULL && strcmp(susp, nomeSuspeito) == 0) {
        total = 1;
    }
    
    total = total + contarPistas(raiz->esquerda, nomeSuspeito);
    total = total + contarPistas(raiz->direita, nomeSuspeito);
    
    return total;
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

void verificarCulpado() {
    char acusado[50];
    
    printf("\n==!==\n");
    printf("HORA DE ACUSAR O CULPADO!\n");
    printf("==!==\n");
    
    printf("\nPistas que voce coletou:\n");
    if(arvorePistas != NULL) {
        exibirPistas(arvorePistas);
    } else {
        printf("Nenhuma pista coletada.\n");
        return;
    }
    
    printf("\nSuspeitos disponiveis:\n");
    printf("- Sr. Silva\n");
    printf("- Dra. Costa\n");
    printf("- Chef Mario\n");
    
    printf("\nDigite o nome do culpado: ");
    fgets(acusado, 50, stdin);
    
    int tam = strlen(acusado);
    if(acusado[tam-1] == '\n') {
        acusado[tam-1] = '\0';
    }
    
    int pistasContra = contarPistas(arvorePistas, acusado);
    //printf("debug: pistasContra = %d\n", pistasContra);
    
    printf("\n==!==\n");
    printf("RESULTADO\n");
    printf("==!==\n");
    printf("Pistas contra %s: %d\n", acusado, pistasContra);
    
    if(pistasContra >= 2) {
        printf("\nVOCE VENCEU!\n");
        printf("Evidencias suficientes para prender %s!\n", acusado);
        printf("Caso resolvido!\n");
    } else {
        printf("\nFALHOU!\n");
        printf("Pistas insuficientes. Precisa de pelo menos 2 pistas.\n");
        printf("O culpado fugiu!\n");
    }
}

int main() {
    printf("\n=== Enigma Studios - MACHADO OVERLORD - LUCIANO ===\n");
    printf("\n=== Detective Quest ===\n");
    printf("\nBem-vindo ao Detective Quest - Nivel Mestre!\n");
    printf("Explore a mansao e encontre pistas...\n");
    
    tabelaHash[0] = NULL;
    tabelaHash[1] = NULL;
    tabelaHash[2] = NULL;
    tabelaHash[3] = NULL;
    tabelaHash[4] = NULL;
    tabelaHash[5] = NULL;
    tabelaHash[6] = NULL;
    tabelaHash[7] = NULL;
    tabelaHash[8] = NULL;
    tabelaHash[9] = NULL;
    
    struct Sala *hallEntrada = criarSala("Hall de Entrada", NULL);
    struct Sala *biblioteca = criarSala("Biblioteca", "Livro com pagina rasgada");
    struct Sala *cozinha = criarSala("Cozinha", "Faca com manchas");
    struct Sala *saladeEstar = criarSala("Sala de Estar", "Copo quebrado no chao");
    struct Sala *sotao = criarSala("Sotao", "Carta antiga amarelada");
    struct Sala *quarto = criarSala("Quarto Principal", "Relogio parado as 3h");
    struct Sala *jardim = criarSala("Jardim", "Pegadas na terra");
    struct Sala *escritorio = criarSala("Escritorio", "Documento rasgado");
    struct Sala *porao = criarSala("Porao", "Corda ensanguentada");
    struct Sala *garagem = criarSala("Garagem", "Chave enferrujada");
    struct Sala *saladeJantar = criarSala("Sala de Jantar", "Taca de vinho vazia");
    struct Sala *banheiro = criarSala("Banheiro", "Frasco de veneno");
    struct Sala *despensa = criarSala("Despensa", NULL);
    struct Sala *corredor = criarSala("Corredor", "Mancha de sangue");
    struct Sala *varanda = criarSala("Varanda", NULL);
    
    hallEntrada->esquerda = biblioteca;
    hallEntrada->direita = cozinha;
    
    biblioteca->esquerda = saladeEstar;
    biblioteca->direita = sotao;
    
    cozinha->esquerda = quarto;
    cozinha->direita = jardim;
    
    saladeEstar->esquerda = escritorio;
    saladeEstar->direita = porao;
    
    sotao->esquerda = garagem;
    
    quarto->esquerda = saladeJantar;
    quarto->direita = banheiro;
    
    jardim->esquerda = despensa;
    jardim->direita = corredor;
    
    corredor->esquerda = varanda;
    
    inserirNaHash("Livro com pagina rasgada", "Dra. Costa");
    inserirNaHash("Faca com manchas", "Chef Mario");
    inserirNaHash("Copo quebrado no chao", "Dra. Costa");
    inserirNaHash("Carta antiga amarelada", "Sr. Silva");
    inserirNaHash("Relogio parado as 3h", "Dra. Costa");
    inserirNaHash("Pegadas na terra", "Chef Mario");
    inserirNaHash("Documento rasgado", "Dra. Costa");
    inserirNaHash("Corda ensanguentada", "Sr. Silva");
    inserirNaHash("Chave enferrujada", "Chef Mario");
    inserirNaHash("Taca de vinho vazia", "Dra. Costa");
    inserirNaHash("Frasco de veneno", "Dra. Costa");
    inserirNaHash("Mancha de sangue", "Dra. Costa");
    
    explorarSalas(hallEntrada);
    
    getchar();
    
    verificarCulpado();
    
    printf("\nObrigado por jogar Detective Quest!\n");
    
    return 0;
}