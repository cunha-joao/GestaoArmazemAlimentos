#include "stdio.h"
#include "string.h"
#include "time.h"
#include "conio.h"
#include "stdlib.h"

typedef struct produto{
    int codigo;
    char nome[50];
    char categoria[50];
    int dia, mes, ano;
    int quantidade;
    float preco_compra;
    float preco_venda;
}PRODUTO;

typedef struct cliente{
    char nome[50];
    char morada[50];
    char nif[9];
    char telefone[9];
    char email[50];
    int codigo;
}CLIENTE;

typedef struct venda{
    PRODUTO produto;
    CLIENTE cliente;
    int quantidade;
    int dia, mes, ano;
}VENDA;

typedef struct elem{
    PRODUTO produto;
    struct elem *anterior;
    struct elem *seguinte;
}ELEM;


void clear_menu() {
    int i;
    for(i = 0; i < 5; i++) {
        printf("\n\n\n\n\n");
    }
}

void any_key() {
    printf("\nPress enter to continue...");
    getch();
}

void listar_produto(ELEM *aux){
    printf("\nCodigo: %i\n", aux->produto.codigo);
    printf("Nome: %s\n", aux->produto.nome);
    printf("Categoria: %s\n", aux->produto.categoria);
    printf("Data de validade: %i/%i/%i\n", aux->produto.dia, aux->produto.mes, aux->produto.ano);
    printf("Quantidade: %i\n", aux->produto.quantidade);
    printf("Preco de compra: %.2f\n", aux->produto.preco_compra);
    printf("Preco de venda: %.2f\n", aux->produto.preco_venda);
}

void listar_produto_codigo(ELEM *iniLista){
    ELEM *aux = NULL;
    int pesquisa;

    clear_menu();

    printf("Selecione o codigo do produto que deseja ver:\n");
    scanf("%i", &pesquisa);

    if(iniLista == NULL){
        printf("Lista vazia!\n");
        return;
    }
    printf("Produto com codigo %i:\n", pesquisa);
    for(aux = iniLista; aux != NULL; aux = aux->seguinte){
        if(aux->produto.codigo == pesquisa) {
            listar_produto(aux);
        }
    }
}

void listar_produto_alfabetica(ELEM *iniLista){
    ELEM *aux1 = NULL;
    ELEM *aux2 = NULL;
    ELEM *min = NULL;

    clear_menu();

    if(iniLista == NULL){
        printf("lista vazia!\n");
        return;
    }

    //Algoritmo selection sort
    for (aux1 = iniLista; aux1->seguinte != NULL; aux1 = aux1->seguinte) {
        min = aux1;
        for (aux2 = aux1->seguinte; aux2 != NULL; aux2 = aux2->seguinte) {
            if (strcmp(aux2->produto.nome, min->produto.nome) < 0) {
                min = aux2;
            }
        }
    }

    printf("Produtos com o nome organizador por ordem alfabetica:\n");
    for(aux1 = iniLista; aux1 != NULL; aux1 = aux1->seguinte){
        listar_produto(aux1);
    }
}

void listar_produto_categoria(ELEM *iniLista){
    ELEM *aux = NULL;
    char pesquisa[50];

    clear_menu();

    printf("Selecione a categoria dos produtos que deseja ver:\n");
    scanf("%s", pesquisa);

    if(iniLista == NULL){
        printf("Lista vazia!\n");
        return;
    }

    printf("Produtos com categoria %s\n", pesquisa);
    for(aux = iniLista; aux != NULL; aux = aux->seguinte){
        if(strcmp(aux->produto.categoria, pesquisa) == 0) {
            listar_produto(aux);
        }
    }
}

void listar_produto_validade(ELEM *iniLista){
    ELEM *aux = NULL;

    time_t data_atual;
    data_atual = time(NULL);
    struct tm tm = *localtime(&data_atual);

    clear_menu();

    if(iniLista == NULL){
        printf("Lista vazia!\n");
        return;
    }

    printf("Produtos fora de validade:\n");
    for(aux = iniLista; aux != NULL; aux = aux->seguinte){
        if(aux->produto.ano < tm.tm_year + 1900){
            listar_produto(aux);
        } else if(aux->produto.ano == tm.tm_year + 1900 && aux->produto.mes < tm.tm_mon + 1){
            listar_produto(aux);
        } else if(aux->produto.ano == tm.tm_year + 1900 && aux->produto.mes == tm.tm_mon + 1 &&
        aux->produto.dia < tm.tm_mday){
            listar_produto(aux);
        }
    }
}

void adicionar_produto(ELEM **iniLista, ELEM **fimLista){
    ELEM *novo = NULL;
    novo=(ELEM *)calloc(1, sizeof(ELEM));

    clear_menu();

    if(novo==NULL){
        printf("Out of memory!\n");
        return;
    }

    printf("Codigo:\n");
    scanf("%i", &novo->produto.codigo);

    printf("Nome:\n");
    scanf("%s", novo->produto.nome);

    printf("Categoria:\n");
    scanf("%s", novo->produto.categoria);

    printf("Dia de expiracao da validade:\n");
    scanf("%i", &novo->produto.dia);

    printf("Mes de expiracao da validade:\n");
    scanf("%i", &novo->produto.mes);

    printf("Ano de expiracao da validade:\n");
    scanf("%i", &novo->produto.ano);

    printf("Quantidade:\n");
    scanf("%i", &novo->produto.quantidade);

    printf("Preco de compra:\n");
    scanf("%f", &novo->produto.preco_compra);

    printf("Preco de venda:\n");
    scanf("%f", &novo->produto.preco_venda);

    novo->seguinte = NULL;
    novo->anterior = NULL;
    if(*fimLista == NULL){
        *iniLista = novo;
        *fimLista = novo;
    }
    else{
        novo->anterior = *fimLista;
        (*fimLista)->seguinte = novo;
        *fimLista = novo;
    }
}

void atualizar_produto(ELEM *iniLista){
    ELEM *aux=NULL;
    int pesquisa;

    clear_menu();

    printf("Selecione o codigo do produto a atualizar:\n");
    scanf("%i", &pesquisa);

    if(iniLista==NULL){
        printf("Lista vazia\n");
        return;
    }
    for(aux=iniLista; aux!=NULL; aux=aux->seguinte){
        if(aux->produto.codigo == pesquisa){
            printf("Codigo:\n");
            scanf("%i", &aux->produto.codigo);

            printf("Nome:\n");
            scanf("%s", aux->produto.nome);

            printf("Categoria:\n");
            scanf("%s", aux->produto.categoria);

            printf("Dia de expiracao da validade:\n");
            scanf("%i", &aux->produto.dia);

            printf("Mes de expiracao da validade:\n");
            scanf("%i", &aux->produto.mes);

            printf("Ano de expiracao da validade:\n");
            scanf("%i", &aux->produto.ano);

            printf("Quantidade:\n");
            scanf("%i", &aux->produto.quantidade);

            printf("Preco de compra:\n");
            scanf("%f", &aux->produto.preco_compra);

            printf("Preco de venda:\n");
            scanf("%f", &aux->produto.preco_venda);
        }
    }
}

void remover_produto(ELEM **iniLista, ELEM **fimLista){
    ELEM *aux = NULL;
    aux = *iniLista;
    int pesquisa;

    clear_menu();

    printf("Selecione o codigo do produto a remover:\n");
    scanf("%i", &pesquisa);

    while (aux != NULL && aux->produto.codigo != pesquisa){
        aux = aux->seguinte;
    }

    if(aux == NULL){
        printf("Codigo %i nao encontrado!\n", pesquisa);
        return;
    }

    if(aux->anterior==NULL){
        *iniLista=aux->seguinte;
        if(*iniLista!=NULL){
            (*iniLista)->anterior=NULL;
        }
    }
    else{
        aux->anterior->seguinte=aux->seguinte;
    }

    aux->seguinte = NULL;
    if(aux->seguinte){
        *fimLista=aux->anterior;
        if(*fimLista!=NULL){
            (*fimLista)->seguinte=NULL;
        }
        else{
            aux->seguinte->anterior=aux->anterior;
        }
    }
    free(aux);
}

void calcular_valor(ELEM *iniLista){
    ELEM *aux = NULL;
    float total_produto;
    float total;

    if(iniLista == NULL){
        printf("Lista vazia!\n");
        return;
    }

    for(aux = iniLista; aux != NULL; aux = aux->seguinte){
        total_produto = (float)aux->produto.quantidade * aux->produto.preco_compra;
        printf("Valor do produto com codigo %i: %.2f\n", aux->produto.codigo, total_produto);
        total = total + total_produto;
    }
    printf("\nValor total do stock: %.2f", total);
}

void criar_relatorio_produto(ELEM *iniLista){
    ELEM *aux = NULL;

    time_t data_atual;
    data_atual = time(NULL);
    struct tm tm = *localtime(&data_atual);

    clear_menu();

    if(iniLista == NULL){
        printf("Lista vazia!\n");
        return;
    }

    for(aux = iniLista; aux != NULL; aux = aux->seguinte){
        if(aux->produto.ano < tm.tm_year + 1900){

        } else if(aux->produto.ano == tm.tm_year + 1900 && aux->produto.mes < tm.tm_mon + 1){

        } else if(aux->produto.ano == tm.tm_year + 1900 && aux->produto.mes == tm.tm_mon + 1 &&
                  aux->produto.dia < tm.tm_mday){

        }
    }
}

int main() {
    int opcao;
    ELEM *iniLista = NULL;
    ELEM *fimLista = NULL;

    clear_menu();

    do{
        printf("Gestao do armazem\n");
        printf("1 - Adicionar produto\n");
        printf("2 - Atualizar informacao de um produto\n");
        printf("3 - Remover produto\n");
        printf("4 - Listar informacao de um produto\n");
        printf("5 - Listar todos os produtos por ordem alfabetica\n");
        printf("6 - Listar produtos por categoria\n");
        printf("7 - Listar produtos fora de validade\n");
        printf("8 - Calcular valor do stock atual\n");
        printf("9 - Criar relatorio de produto fora de validade (...)\n");

        printf("Selecione uma opcao:\n");
        scanf("%i", &opcao);


        switch (opcao) {
            case 1:
                adicionar_produto(&iniLista, &fimLista);
                break;

            case 2:
                atualizar_produto(iniLista);
                break;

            case 3:
                remover_produto(&iniLista, &fimLista);
                break;

            case 4:
                listar_produto_codigo(iniLista);
                any_key();
                break;

            case 5:
                listar_produto_alfabetica(iniLista);
                any_key();
                break;

            case 6:
                listar_produto_categoria(iniLista);
                any_key();
                break;

            case 7:
                listar_produto_validade(iniLista);
                any_key();
                break;

            case 8:
                calcular_valor(iniLista);
                any_key();
                break;

            case 9:
                criar_relatorio_produto(iniLista);
                any_key();
                break;
        }
    } while (opcao != 0);
    printf("Volte sempre");
}
