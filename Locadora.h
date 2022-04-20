#ifndef TP_H
#define TP_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef enum {Disponivel = 0, Alugado} status;

typedef struct {
    char* modelo;
    float Diaria;
    status d;
} carro;

typedef struct{
    carro carro;
    int dias;
} itemlocacao;

struct listacarro {
    carro* carros;
    struct listacarro* prox;
};

typedef struct listacarro lc;

int cc(float a);
void imprimeLinha(char caractere, int qtdx);
void imprimeAEsquerda(char str[], char caractere, int qtdx);
void imprimeADireita(char str[],char caractere,int qtdx);
void imprimeItemLocacao(itemlocacao item[], int i);
carro* CadastrarCarro();
int qtdCarros(lc* carros);
int qtdCarros(lc* carros);
lc* adicionarCarro(lc* carros, carro* c);
void gravarCarros(lc* carros);
lc* carregarCarros();
int showMenu();
float calcularTotal(itemlocacao item[], int qtd, float tt);
void notaFiscal(itemlocacao item[], int qtd);
void imprimirCarrosDisponiveis(lc* carros);
void imprimirCarrosAlugados(lc* carros);
carro* buscarCarro(lc* carros, char* modelo);
void realizarLocacao(lc* listac);
void devolverCarro(lc* lista);

#endif