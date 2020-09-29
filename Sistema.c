/**
 * @brief 
 * 
 * @file Sistema.c
 * @author Gustavo Correa
 * @date 2020-09-26
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include "Sistema.h"
#include "Equipamento.h"
#include "Alarmes.h"
#include "Interface.h"

int main(){
    int i=15;
    while(i>0){
      ImprimirTudoEquipamentos();
      ImprimirTudoAlarmes();
      ImprimirTodosAtuados();
      i--;
    }
    //ImprimirTudoEquipamentos();
    //ImprimirTudoAlarmes();
    //ImprimirTodosAtuados();
    //OrdenarClassificacao();
    printf("\n\nTestar\n\n");
    OrdenarAtuacao();
    printf("\n\nTestar1\n\n");
    Filtrar();
    printf("\n\nTestar2\n\n");
    Ordenar_Desc();

}