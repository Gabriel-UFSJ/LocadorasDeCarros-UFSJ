#include"tp.h"

int cc(float a){
  int contador = 0;
  while(a > 10){
    contador++;
    a = a / 10;
  }
  return contador+1;
}

void imprimeLinha(char caractere, int qtdx) {
	for (int i = 0; i <= qtdx; i++) {
		printf("%c", caractere);
	}
}

void imprimeAEsquerda(char str[], char caractere, int qtdx) {
  int qt = strlen(str);
  int j = qtdx - qt;
    for(int i = 0; i < qt; i++)
      printf("%c", str[i]);
    for(int i = 0; i<j;i++)
        printf("%c", caractere);
}

void imprimeADireita(char str[],char caractere,int qtdx) {
  int qt = qtdx-strlen(str);
    printf("%s", str);
    for(int i = qt; i<qtdx;i++)
        printf("%c", caractere);
}

void imprimeItemLocacao(itemlocacao item[], int i){
  imprimeAEsquerda(item[i].carro.modelo, ' ', 25);
  float valor = item[i].carro.Diaria;
  int qtd = item[i].dias;
  float q = qtd;
  float st = qtd * valor;
  for(int i = 0; i < 8 - cc(valor); i++)
    printf(" ");
  printf("%.2f", valor);
  printf(" x");
  for(int i = 0; i < 3 - cc(q); i++)
    printf(" ");
  printf("%d", qtd);
  printf(" =");
  for(int i = 0; i < 5 - cc(st); i++)
    printf(" ");
  printf("%.2f", st);
  printf("\n");
}

carro* CadastrarCarro() {
    carro *c = (carro*) malloc(sizeof(carro));
    c->modelo = (char*) malloc(sizeof(char) * 30);
    printf("\nINFORME O MODELO DO CARRO: ");
    gets(c->modelo);
    setbuf(stdin, NULL);
    printf("INFORME O VALOR DA DIARIA DO CARRO: ");
    scanf("%f", &c->Diaria);
    setbuf(stdin, NULL);
    c->d = 0;
    return c;
}

int qtdCarros(lc* carros){
    int qtd = 0;
    lc* atual = carros;
    while(atual != NULL){
        qtd++;
        atual = atual->prox;
    }
    return qtd;
}

lc* adicionarCarro(lc* carros, carro* c){
    lc* listac = (lc*) malloc(sizeof(lc));
    listac->carros = c;
    listac->prox = carros;
    carros = listac;
    return carros;
}

void gravarCarros(lc* carros){
    lc* atual = carros;
    FILE* arq = fopen("carros.txt", "w");
    while(atual != NULL){
        fprintf(arq, "Modelo: %s\nDiaria: %f\nStatus: %d\n\n",atual->carros->modelo, atual->carros->Diaria, atual->carros->d);
        atual = atual->prox;
    }
    fclose(arq);
}

lc* carregarCarros(){
    FILE* arq = fopen("carros.txt", "r");
    carro* c;
    lc* carros = NULL;
    char* strg = (char*) malloc(sizeof(char) * 10);
    while(!feof(arq)){
        c = (carro*) malloc(sizeof(carro));
        c->modelo = (char*) malloc(sizeof(char));
        if(fscanf(arq, "%s %s\n", strg, c->modelo) == EOF) break;
        fscanf(arq, "%s %f\n", strg, &c->Diaria);
        fscanf(arq, "%s %d\n\n", strg, &c->d);
        carros = adicionarCarro(carros, c);
    }
    free(strg);
    fclose(arq);
    return carros;
}

int showMenu(){
    int op;
    system("cls");
    imprimeLinha('*', 50);
    printf("\n                  MENU DE OPCOES\n");
    imprimeLinha('*', 50);
    printf("\n0 - SAIR");
    printf("\n1 - CADASTRAR NOVO CARRO");
    printf("\n2 - REALIZAR LOCACAO");
    printf("\n3 - DEVOLVER CARRO\n");
    imprimeLinha('*', 50);
    printf("\nINFORME A OPCAO: ");
    scanf("%d", &op);
    setbuf(stdin, NULL);
    return op;
}

float calcularTotal(itemlocacao item[], int qtd, float tt){
  if(qtd == 0) {
    tt += item[qtd].carro.Diaria * item[qtd].dias;
    return tt;
  } 
  tt += item[qtd].carro.Diaria * item[qtd].dias;
  return calcularTotal(item, qtd-1, tt);
}

void notaFiscal(itemlocacao item[], int qtd){
  imprimeLinha('*', 50);
  printf("\n                   NOTA  FISCAL\n");
  imprimeLinha('*', 50);
  printf("\n");
  for(int i = 0; i < qtd; i++){
    imprimeItemLocacao(item, i);
  }
  float tt = 0;
  float total = calcularTotal(item, qtd-1, tt);
  imprimeLinha('*', 50);
  printf("\n");
  imprimeAEsquerda("TOTAL: ", ' ', 20);
  for(int i = 0; i < 28 - cc(total); i++)
    printf(" ");
  printf("%.2f\n", total);
  imprimeLinha('*', 50);
  char vm;
  printf("\n\nAPERTE ENTER PARA VOLTAR AO MENU");
  scanf("%c", &vm);
  free(item);
}

void imprimirCarrosDisponiveis(lc* carros){
    lc* atual = carros;
    printf("\nCARROS DISPONIVEIS:");
    while(atual != NULL){
      if(atual->carros->d == 0){
        printf("\n %s, R$%.2f;", atual->carros->modelo, atual->carros->Diaria);
        atual = atual->prox;
      } else {
        atual = atual->prox;
      }
    }
    printf("\n");
}

void imprimirCarrosAlugados(lc* carros){
    lc* atual = carros;
    printf("\nCARROS ALUGADOS:");
    while(atual != NULL){
      if(atual->carros->d == 1){
        printf("\n %s;", atual->carros->modelo);
        atual = atual->prox;
      } else {
        atual = atual->prox;
      }
    }
    printf("\n");
}

carro* buscarCarro(lc* carros, char* modelo){
    lc* atual = carros;
    while(atual != NULL){
        if(strcmp(atual->carros->modelo, modelo) == 0){
            if(atual->carros->d == 0){
                atual->carros->d = 1;
                return atual->carros;
            } else if (atual->carros->d == 1){
              return NULL;
            }
        } else {
            atual = atual->prox;
        }
    }
    return NULL;
}

void realizarLocacao(lc* listac){
    int qtdi = 0;
    itemlocacao* itemt = (itemlocacao*)malloc(qtdi * sizeof(itemlocacao));
    while(1){
        itemlocacao* item = (itemlocacao*)malloc(sizeof(itemlocacao));
        item->carro.modelo = (char*) malloc(sizeof(char) * 30);
        printf("\n\nINFORME O NOME DO CARRO OU TECLE ENTER PARA FINALIZAR A LOCACAO: ");
        gets(item->carro.modelo);
        setbuf(stdin, NULL);
        if(item->carro.modelo == NULL || strcmp(item->carro.modelo, "") == 0){
            if(qtdi == 0){
                free(itemt);
                free(item);
                free(item->carro.modelo);
                break;
            } else if (qtdi != 0){
                notaFiscal(itemt, qtdi);
                free(item);
                free(item->carro.modelo);
                break;
            }
        } else {
            carro* mc = buscarCarro(listac, item->carro.modelo);
            if(mc == NULL){
                printf("ERRO: ESTE CARRO JA FOI ALUGADO, OU NAO EXISTE!");
            } else {
                item->carro = *mc;
                printf("INFORME A QUANTIDADE DE DIAS: ");
                scanf("%d", &item->dias);
                setbuf(stdin, NULL);
                itemt[qtdi] = *item;
                qtdi++;
            }
        }
    }
}

void devolverCarro(lc* lista){
  lc* atual = lista;
  char* modelo = (char*) malloc(sizeof(char) * 30);
  printf("\nINFORME O NOME DO CARRO: ");
  gets(modelo);
  setbuf(stdin, NULL);
  while(atual != NULL){
    if (strcmp (modelo, atual->carros->modelo) == 0){
      if (atual->carros->d == 1){
          atual->carros->d = 0;
          printf("\n%s DEVOLVIDO", modelo);
          char vm;
          printf("\n\nAPERTE ENTER PARA VOLTAR AO MENU");
          scanf("%c", &vm);
          free(modelo);
          break;
      } else{
        printf("\nESTE CARRO NAO ESTA ALUGADO\n");
        free(modelo);
        break;
      }
    } 
    else {
      atual = atual->prox;
    }
  }
  if(atual == NULL){
    printf("\nESTE CARRO NAO EXISTE\n");
    free(modelo);
  }
}