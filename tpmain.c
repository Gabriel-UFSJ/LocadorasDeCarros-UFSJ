#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"tp.h"

int main(){
    lc* estoque = carregarCarros();
    carro* c;
    lc* listac;
    while(1){
        int op = showMenu();
        if(op == 0){
            gravarCarros(estoque);
            return 0;
        }
        else if(op == 1){
            c = CadastrarCarro();
            estoque = adicionarCarro(estoque, c);
            gravarCarros(estoque);
        }
        else if(op == 2){
            imprimirCarrosDisponiveis(estoque);
            realizarLocacao(estoque);
            gravarCarros(estoque);
        }
        else if (op == 3){
          imprimirCarrosAlugados(estoque);
          devolverCarro(estoque);
          gravarCarros(estoque);
        } 
    }
    free(c);
    free(c->modelo);
    free(listac);
}