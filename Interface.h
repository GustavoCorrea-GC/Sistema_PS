/**
 * @brief Arquivo contendo as funções de interface 
 * e suas funções auxiliares.
 * 
 * @file Equipamento.h
 * @author Gustavo Correa
 * @date 2020-09-27
 */



void ImprimirEquipamento(Equipamento_t *Eq){
    printf("\nNome:\tNº Série:\tTipo:\t\tData:");
    printf("\n%s", Eq->Nome);
    printf("\t%d", Eq->N_Serie);
    switch (Eq->Tipo)
    {
        case TENSAO:
            printf("\t\tTensão\t");
            break;
        case CORRENTE:
            printf("\t\tCorrente");
            break;
        case OLEO :
            printf("\t\tÓleo\t");
            break;
        default:
            break;
    }
    printf("\t%d/", Eq->Data.Dia);
    printf("%d/", Eq->Data.Mes);
    printf("%d", Eq->Data.Ano);
    printf("\nDescrição: ");
    printf("%s\n", Eq->Descricao);
}

void ImprimirTudoEquipamentos(){
    FILE *fp;
    char linha[BYTES_MAX];
    Equipamento_t Aux;
    fp=fopen(EQUIP_FILE, "rt");
    while (!feof(fp)){
        fgets(linha, BYTES_MAX,fp);
        String2Equipamento_t(linha, &Aux);
        ImprimirEquipamento(&Aux);
    }
    fclose(fp);
}

int AtualizaEquipamento(Equipamento_t *Aux){
    printf("Digite o novo nome do equipamento");
    scanf("%s", Aux->Nome);
    printf("Digite o novo numero de serie do equipamento");
    scanf("%d", &Aux->N_Serie);
    printf("Digite o novo tipo do equipamento");
    scanf("%d", &Aux->Tipo);
    printf("Digite o novo dia de cadastro do equipamento");
    scanf("%d", &Aux->Data.Dia);
    printf("Digite o novo mes de cadastro do equipamento");
    scanf("%d", &Aux->Data.Mes);
    printf("Digite o novo ano de cadastro do equipamento");
    scanf("%d", &Aux->Data.Ano);
    printf("Digite a nova Descricao do equipamento");
    scanf("%s", Aux->Descricao);
}

int Criar_Equipamento(Equipamento_t Aux){
    printf("Digite o novo nome do equipamento");
    scanf("%s", Aux.Nome);
    printf("Digite o novo numero de serie do equipamento");
    scanf("%d", &Aux.N_Serie);
    printf("Digite o novo tipo do equipamento");
    scanf("%d", &Aux.Tipo);
    printf("Digite o novo dia de cadastro do equipamento");
    scanf("%d", &Aux.Data.Dia);
    printf("Digite o novo mes de cadastro do equipamento");
    scanf("%d", &Aux.Data.Mes);
    printf("Digite o novo ano de cadastro do equipamento");
    scanf("%d", &Aux.Data.Ano);
    printf("Digite a nova Descricao do equipamento");
    scanf("%s", Aux.Descricao);
    
}