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

/*--Inicia a lista de equipamentos--*/
Equipamento_t InicioEquipamentos;

/*--Insere o primeiro equipamento--*/

//ReadEquipamento(644, &InicioEquipamentos);

ImprimirTudoEquipamentos();
DeleteEquipamento(1566);

}