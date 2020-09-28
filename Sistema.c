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
#include "Sistema.h"
#include "Equipamento.h"
#include "Alarmes.h"
#include "Interface.h"

int main(){
    //printf("\n%ld\n",sizeof(Alarme_t));
    /*--Inicia a lista de equipamentos--*/
    Equipamento_t InicioEquipamentos;
    Alarme_t Alarme;

    ReadAlarme(51, &Alarme);
    //ImprimirTudoAlarmes();
    //ImprimirAlarme(&Alarme);
    //ReadEquipamento(563,&InicioEquipamentos);
    //ImprimirEquipamento(&InicioEquipamentos);
    //ImprimirTudoEquipamentos();
    
    //ImprimirAtivos(&Alarme);
    ImprimirTodosAtivos();
    //int chave=1;
    /*while (Menu()!=0){
        /*
        scanf("%d",&chave);
        if (ReadEquipamento(chave,&InicioEquipamentos)==TRUE){
            UpdateEquipamento(InicioEquipamentos);
        }
        /*if(ReadAlarme(chave,&Alarme)==TRUE){
            UpdateAlarme(Alarme);
            //CreateAlarme(Alarme);
            //DeleteAlarme(chave);
        }
    }*/


        


}