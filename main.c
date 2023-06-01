//INCLUDES
#include "stdio.h"
#include "string.h"
#include "time.h"
#include "conio.h"
#include "stdlib.h"

//STRUCTS
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
    int nif;
    int telefone;
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
    CLIENTE cliente;
    VENDA venda;
    struct elem *anterior;
    struct elem *seguinte;
}ELEM;


//FUNCOES DE SUPORTE

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

void list_product(ELEM *aux){
    printf("\nCodigo: %i\n", aux->produto.codigo);
    printf("Nome: %s\n", aux->produto.nome);
    printf("Categoria: %s\n", aux->produto.categoria);
    printf("Data de validade: %i/%i/%i\n", aux->produto.dia, aux->produto.mes, aux->produto.ano);
    printf("Quantidade: %i\n", aux->produto.quantidade);
    printf("Preco de compra: %.2f\n", aux->produto.preco_compra);
    printf("Preco de venda: %.2f\n", aux->produto.preco_venda);
}

void list_client(ELEM *aux){
    printf("\nCodigo: %i\n", aux->cliente.codigo);
    printf("Nome: %s\n", aux->cliente.nome);
    printf("Morada: %s\n", aux->cliente.morada);
    printf("NIF: %i\n", aux->cliente.nif);
    printf("Telefone: %i\n", aux->cliente.telefone);
    printf("Email: %s\n", aux->cliente.email);
}

void list_sale(ELEM *nova_venda){
    printf("INFORMACAO DA VENDA:\n");
    printf("\n// Cliente //\n");
    printf("Codigo: %i\n", nova_venda->venda.cliente.codigo);
    printf("Nome: %s\n", nova_venda->venda.cliente.nome);
    printf("Morada: %s\n", nova_venda->venda.cliente.morada);
    printf("NIF: %i\n", nova_venda->venda.cliente.nif);
    printf("Telefone: %i\n", nova_venda->venda.cliente.telefone);
    printf("Email: %s\n", nova_venda->venda.cliente.email);
    printf("\n// Produto //\n");
    printf("Codigo: %i\n", nova_venda->venda.produto.codigo);
    printf("Nome: %s\n", nova_venda->venda.produto.nome);
    printf("Categoria: %s\n", nova_venda->venda.produto.categoria);
    printf("\nQuantidade da venda: %i\n", nova_venda->venda.quantidade);
    printf("Data da venda: %i/%i/%i\n", nova_venda->venda.dia, nova_venda->venda.mes, nova_venda->venda.ano);
}


//GERIR PRODUTOS

void list_product_code(ELEM *iniLista){
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
            list_product(aux);
        }
    }
}

void list_product_order(ELEM *iniLista){
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

    printf("Produtos com o nome organizado por ordem alfabetica:\n");
    for(aux1 = iniLista; aux1 != NULL; aux1 = aux1->seguinte){
        list_product(aux1);
    }
}

void list_product_category(ELEM *iniLista){
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
            list_product(aux);
        }
    }
}

void list_product_expiration(ELEM *iniLista){
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
            list_product(aux);
        } else if(aux->produto.ano == tm.tm_year + 1900 && aux->produto.mes < tm.tm_mon + 1){
            list_product(aux);
        } else if(aux->produto.ano == tm.tm_year + 1900 && aux->produto.mes == tm.tm_mon + 1 &&
        aux->produto.dia < tm.tm_mday){
            list_product(aux);
        }
    }
}

void add_product(ELEM **iniLista, ELEM **fimLista){
    ELEM *novo = NULL;
    novo=(ELEM *)calloc(1, sizeof(ELEM));

    clear_menu();

    if(novo==NULL){
        printf("Out of memory!\n");
        return;
    }

    printf("Codigo:\n");
    scanf("%i", &novo->produto.codigo);

    //Verifica se codigo ja existe
    ELEM *current = *iniLista;
    while (current != NULL) {
        if (current->produto.codigo == novo->produto.codigo) {
            printf("Codigo ja existe!\n");
            any_key();
            free(novo);
            return;
        }
        current = current->seguinte;
    }

    printf("Nome:\n");
    getchar();
    fgets(novo->produto.nome, sizeof(novo->produto.nome), stdin);
    novo->produto.nome[strcspn(novo->produto.nome, "\n")] = '\0';

    printf("Categoria:\n");
    fgets(novo->produto.categoria, sizeof(novo->produto.categoria), stdin);
    novo->produto.categoria[strcspn(novo->produto.categoria, "\n")] = '\0';

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

void update_product(ELEM *iniLista){
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

void remove_product(ELEM **iniLista, ELEM **fimLista){
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

void calculate_value(ELEM *iniLista){
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

void create_product_report(){
    FILE *fp = NULL;
    char relatorio[200];

    clear_menu();

    printf("Escreva o relatorio:\n");
    fflush(stdin);
    fgets(relatorio, sizeof(relatorio), stdin);

    relatorio[strcspn(relatorio, "\n")] = '\0';

    fp = fopen("relatorio_produto.txt","w");

    if (fp == NULL){
        printf("Erro ao abrir o ficheiro!\n");
        return;
    }

    fwrite(relatorio, sizeof(char), strlen(relatorio),fp);

    fclose(fp);
    printf("Relatorio guardado no ficheiro!");
}


//GERIR CLIENTES

void list_client_order(ELEM *iniLista){
    ELEM *aux1 = NULL;
    ELEM *aux2 = NULL;
    ELEM *min = NULL;

    clear_menu();

    if(iniLista == NULL){
        printf("Lista vazia!\n");
        return;
    }

    //Algoritmo selection sort
    for (aux1 = iniLista; aux1->seguinte != NULL; aux1 = aux1->seguinte) {
        min = aux1;
        for (aux2 = aux1->seguinte; aux2 != NULL; aux2 = aux2->seguinte) {
            if (strcmp(aux2->cliente.nome, min->cliente.nome) < 0) {
                min = aux2;
            }
        }
    }

    printf("Cliente com o nome organizado por ordem alfabetica:\n");
    for(aux1 = iniLista; aux1 != NULL; aux1 = aux1->seguinte){
        list_client(aux1);
    }
}

void list_client_nif(ELEM *iniLista){
    ELEM *aux = NULL;
    int pesquisa;

    clear_menu();

    printf("Selecione o NIF do cliente que deseja ver:\n");
    scanf("%i", &pesquisa);

    if(iniLista == NULL){
        printf("Lista vazia!\n");
        return;
    }

    printf("Cliente com NIF %i:\n", pesquisa);
    for(aux = iniLista; aux != NULL; aux = aux->seguinte){
        if(aux->cliente.nif == pesquisa) {
            list_client(aux);
        }
    }
}

int codigo_atual = 1;
void add_client(ELEM **iniLista, ELEM **fimLista){
    ELEM *novo_cliente = NULL;
    novo_cliente=(ELEM *)calloc(1, sizeof(ELEM));

    clear_menu();

    if(novo_cliente==NULL){
        printf("Out of memory!\n");
        return;
    }

    novo_cliente->cliente.codigo = codigo_atual++;

    printf("Nome:\n");
    getchar();
    fgets(novo_cliente->cliente.nome, sizeof(novo_cliente->cliente.nome), stdin);
    novo_cliente->cliente.nome[strcspn(novo_cliente->cliente.nome, "\n")] = '\0';

    printf("Morada:\n");
    fgets(novo_cliente->cliente.morada, sizeof(novo_cliente->cliente.morada), stdin);
    novo_cliente->cliente.morada[strcspn(novo_cliente->cliente.morada, "\n")] = '\0';

    printf("NIF:\n");
    scanf("%i", &novo_cliente->cliente.nif);

    //Verifica se NIF ja existe
    ELEM *current = *iniLista;
    while (current != NULL) {
        if (current->cliente.nif == novo_cliente->cliente.nif) {
            printf("NIF ja existe!\n");
            any_key();
            free(novo_cliente);
            return;
        }
        current = current->seguinte;
    }

    printf("Telefone:\n");
    scanf("%i", &novo_cliente->cliente.telefone);

    printf("Email:\n");
    scanf("%s", novo_cliente->cliente.email);

    novo_cliente->seguinte = NULL;
    novo_cliente->anterior = NULL;
    if(*fimLista == NULL){
        *iniLista = novo_cliente;
        *fimLista = novo_cliente;
    }
    else{
        novo_cliente->anterior = *fimLista;
        (*fimLista)->seguinte = novo_cliente;
        *fimLista = novo_cliente;
    }
}

void update_client(ELEM *iniLista){
    ELEM *aux=NULL;
    int pesquisa;

    clear_menu();

    printf("Selecione o NIF do cliente a atualizar:\n");
    scanf("%i", &pesquisa);

    if(iniLista == NULL){
        printf("Lista vazia\n");
        return;
    }

    for(aux = iniLista; aux != NULL; aux = aux->seguinte){
        if(aux->cliente.nif == pesquisa){
            printf("Morada:\n");
            scanf("%s", aux->cliente.morada);

            printf("Telefone:\n");
            scanf("%i", &aux->cliente.telefone);

            printf("Email:\n");
            scanf("%s", aux->cliente.email);
        }
    }
}


//GERIR VENDAS

void register_sale(ELEM **iniLista, ELEM **fimLista){
    ELEM *aux = NULL;
    ELEM *nova_venda = NULL;
    nova_venda=(ELEM *)calloc(1, sizeof(ELEM));
    int pesquisa_cliente;
    int pesquisa_produtos;
    int quantidade_vendida;
    time_t data_atual;
    data_atual = time(NULL);
    struct tm tm = *localtime(&data_atual);

    clear_menu();

    if(*iniLista == NULL){
        printf("Lista vazia!\n");
        any_key();
        return;
    }
    if(nova_venda == NULL){
        printf("Out of memory!\n");
        any_key();
        return;
    }

    //Definir o cliente associado a esta venda
    printf("NIF do cliente:\n");
    scanf("%i", &pesquisa_cliente);

    for(aux = *iniLista; aux != NULL; aux = aux->seguinte){
        if(aux->cliente.nif == pesquisa_cliente){
            nova_venda->venda.cliente.codigo = aux->cliente.codigo;
            strcpy(nova_venda->venda.cliente.nome, aux->cliente.nome);
            strcpy(nova_venda->venda.cliente.morada, aux->cliente.morada);
            nova_venda->venda.cliente.nif = aux->cliente.nif;
            nova_venda->venda.cliente.telefone = aux->cliente.telefone;
            strcpy(nova_venda->venda.cliente.email, aux->cliente.email);
        }
    }

    //Definir o produto vendido
    printf("Codigo do produto:\n");
    scanf("%i", &pesquisa_produtos);

    for (aux = *iniLista; aux != NULL; aux = aux->seguinte){
        if(aux->produto.codigo == pesquisa_produtos){
            nova_venda->venda.produto.codigo = aux->produto.codigo;
            strcpy(nova_venda->venda.produto.nome, aux->produto.nome);
            strcpy(nova_venda->venda.produto.categoria, aux->produto.categoria);
            nova_venda->venda.produto.dia = aux->produto.dia;
            nova_venda->venda.produto.mes = aux->produto.mes;
            nova_venda->venda.produto.ano = aux->produto.ano;

            printf("Quantidade vendida:\n");
            scanf("%i", &quantidade_vendida);
            if(quantidade_vendida > aux->produto.quantidade){
                printf("Quantidade superior a quantidade em stock!");
                any_key();
                return;
            } else{
                nova_venda->venda.quantidade = quantidade_vendida;
                aux->produto.quantidade = aux->produto.quantidade - quantidade_vendida;
            }

            nova_venda->venda.produto.preco_compra = aux->produto.preco_compra;
            nova_venda->venda.produto.preco_venda = aux->produto.preco_venda;

            nova_venda->venda.dia = tm.tm_mday;
            nova_venda->venda.mes = tm.tm_mon + 1;
            nova_venda->venda.ano = tm.tm_year + 1900;
        }
    }

    nova_venda->seguinte = NULL;
    nova_venda->anterior = NULL;
    if(*fimLista == NULL){
        *iniLista = nova_venda;
        *fimLista = nova_venda;
    }
    else{
        nova_venda->anterior = *fimLista;
        (*fimLista)->seguinte = nova_venda;
        *fimLista = nova_venda;
    }

    clear_menu();
    list_sale(nova_venda);
    any_key();
}

void create_sale_report(ELEM *iniLista){
    ELEM *aux = NULL;
    FILE *fp = NULL;
    char extra[200];
    char tipo[10];
    float valor_venda;

    clear_menu();

    printf("Tipo de relatorio (diario/mensal/anual):\n");
    scanf("%s", tipo);

    printf("Tem mais alguma coisa a adicionar?\n");
    fflush(stdin);
    fgets(extra, sizeof(extra), stdin);
    extra[strcspn(extra, "\n")] = '\0';

    for(aux = iniLista; aux != NULL; aux = aux->seguinte) {
        valor_venda = (float) aux->venda.quantidade * aux->venda.produto.preco_venda;
    }

    fp = fopen("relatorio_venda.txt","w");
    if (fp == NULL){
        printf("Erro ao abrir o ficheiro!\n");
        return;
    }

    fprintf(fp, "%i %s %s %i %i %i %i %.2f %.2f %i %.2f %s %s",
            aux->venda.produto.codigo, aux->venda.produto.nome,
            aux->venda.produto.categoria, aux->venda.produto.dia,
            aux->venda.produto.mes, aux->venda.produto.ano,
            aux->venda.produto.quantidade, aux->venda.produto.preco_compra,
            aux->venda.produto.preco_venda, aux->venda.quantidade,
            valor_venda, extra, tipo);

    fclose(fp);
    printf("Relatorio guardado no ficheiro!");
}

void list_menu(ELEM *iniLista){
    int opcao;

    clear_menu();

    do{
        printf("1 - Listar informacao de um produto\n");
        printf("2 - Listar todos os produtos por ordem alfabetica\n");
        printf("3 - Listar produtos por categoria\n");
        printf("4 - Listar produtos fora de validade\n");
        printf("5 - Listar clientes por ordem alfabetica\n");
        printf("6 - Listar informacao de um cliente\n");
        printf("0 - Voltar\n");

        printf("Selecione uma opcao:\n");
        scanf("%i", &opcao);

        switch (opcao){
            case 1:
                list_product_code(iniLista);
                any_key();
                break;

            case 2:
                list_product_order(iniLista);
                any_key();
                break;

            case 3:
                list_product_category(iniLista);
                any_key();
                break;

            case 4:
                list_product_expiration(iniLista);
                any_key();
                break;

            case 5:
                list_client_order(iniLista);
                any_key();
                break;

            case 6:
                list_client_nif(iniLista);
                any_key();
                break;
        }

    } while (opcao != 0);
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
        printf("4 - Calcular valor do stock atual\n");
        printf("5 - Criar relatorio de produto fora de validade (...)\n");
        printf("6 - Adicionar cliente\n");
        printf("7 - Atualizar informacao de um cliente\n");
        printf("8 - Registar venda\n");
        printf("9 - Criar relatorio de vendas\n");
        printf("10 - Listar informacao\n");
        printf("0 - Terminar\n");

        printf("Selecione uma opcao:\n");
        scanf("%i", &opcao);


        switch (opcao) {
            case 1:
                add_product(&iniLista, &fimLista);
                break;

            case 2:
                update_product(iniLista);
                break;

            case 3:
                remove_product(&iniLista, &fimLista);
                break;

            case 4:
                calculate_value(iniLista);
                any_key();
                break;

            case 5:
                create_product_report();
                any_key();
                break;

            case 6:
                add_client(&iniLista, &fimLista);
                break;

            case 7:
                update_client(iniLista);
                break;

            case 8:
                register_sale(&iniLista, &fimLista);
                break;

            case 9:
                create_sale_report(iniLista);
                break;

            case 10:
                list_menu(iniLista);
                break;
        }
    } while (opcao != 0);
    printf("Volte sempre");
}
