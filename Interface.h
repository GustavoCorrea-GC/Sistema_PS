/**
 * @brief Arquivo contendo as funções de interface 
 * e suas funções auxiliares.
 * 
 * @file Equipamento.h
 * @author Gustavo Correa
 * @date 2020-09-27
 */


/*------------------Equipamento--------------------------*/
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
    printf("\t----------------------------------------\n");
}
void ImprimirTudoEquipamentos(){
    FILE *fp;
    char linha[BYTES_MAX];
    Equipamento_t Aux;
    fp=fopen(EQUIP_FILE, "rt");
    while (!feof(fp)){
        fgets(linha, BYTES_MAX,fp);
        String2Equipamento_t(linha, &Aux);
        if(!feof(fp)){
            ImprimirEquipamento(&Aux);
        }
    }
    fclose(fp);
}

void Atualiza_Equipamento(){
    Equipamento_t Aux;
    printf("Digite o numero de serie do equipamento:\n");
    scanf("%d", &Aux.N_Serie);
    printf("Digite o novo nome do equipamento:\n");
    scanf("%s", Aux.Nome);
    printf("Digite o novo tipo do equipamento:\n");
    scanf("%d", &Aux.Tipo);
    printf("Digite o novo dia de cadastro do equipamento:\n");
    scanf("%d", &Aux.Data.Dia);
    printf("Digite o novo mes de cadastro do equipamento:\n");
    scanf("%d", &Aux.Data.Mes);
    printf("Digite o novo ano de cadastro do equipamento:\n");
    scanf("%d", &Aux.Data.Ano);
    printf("Digite a nova Descricao do equipamento:\n");
    scanf("%s", Aux.Descricao);
    if(UpdateEquipamento(Aux)==TRUE){
        printf("\nModificado com sucesso.\n");
    }
    else{
        printf("\nFalha na modificação.\n");
    }
    
}
void Criar_Equipamento(){
    Equipamento_t Aux;
    printf("\nDigite o novo nome do equipamento:\n");
    scanf("%s", Aux.Nome);
    printf("\nDigite o novo numero de serie do equipamento:\n");
    scanf("%d", &Aux.N_Serie);
    printf("\nDigite o novo tipo do equipamento:\n");
    scanf("%d", &Aux.Tipo);
    printf("\nDigite o novo dia de cadastro do equipamento:\n");
    scanf("%d", &Aux.Data.Dia);
    printf("\nDigite o novo mes de cadastro do equipamento:\n");
    scanf("%d", &Aux.Data.Mes);
    printf("\nDigite o novo ano de cadastro do equipamento:\n");
    scanf("%d", &Aux.Data.Ano);
    printf("\nDigite a nova Descricao do equipamento:\n");
    scanf("%s", Aux.Descricao);
    if(CreateEquipamento(Aux)==TRUE){
        printf("\nCriado com sucesso.\n");
    }
    else{
        printf("\nFalha na criação.\n");
    }
    
    
}
void Remover_Equipamento(){
    int Aux;
    printf("\nDigite o numero de serie do equipamento a ser removido:\n");
    scanf("%d", &Aux);
    if(DeleteEquipamento(Aux)==TRUE){
        printf("\nRemovido com sucesso.\n");
    }
    else{
        printf("\nFalha na remoção.\n");
    }
}
void Pesquisa_Equipamento(){
    int Aux;
    Equipamento_t Eq;
    printf("\nDigite o numero de serie do equipamento:\n");
    scanf("%d", &Aux);
    if(ReadEquipamento(Aux,&Eq)==TRUE){
        ImprimirEquipamento(&Eq);
    }
    else{
        printf("\nEquipamento não encontrado.\n");
    }
}

/*------------------Alarme--------------------------*/
void ImprimirAlarme(Alarme_t *A){
    printf("\nNome:\tAtivo:\tId:\tClassif:\tData de Cadastro:");
    printf("\n%s", A->Nome);
    switch (A->Ativo)
    {
    case TRUE:
        printf("\tSim.");
        break;
    case FALSE:
        printf("\tNão.");
        break;
    
    default:
        printf("\tErro. Lido=%d",A->Ativo);
        break;
    }
    
    printf("\t%d", A->identificador);
    switch (A->Classificacao)
    {
        case ALTA:
            printf("\tAlta\t");
            break;
        case MEDIA:
            printf("\tMédia");
            break;
        case BAIXA :
            printf("\tBaixa\t");
            break;
        default:
            printf("\tErro. Lido=%d",A->Classificacao);
            break;
    }

    printf("\t%d/", A->DataCadastro.Dia);
    printf("%d/", A->DataCadastro.Mes);
    printf("%d", A->DataCadastro.Ano);
    printf("\nN Ativaçao:\tNSerie Equip:\t\tData Entrada:");
    printf("\n%d", A->N_Ativacao);
    printf("\t\t%d", A->N_Serie_Equi);
    printf("\t\t\t%d/", A->DataEntrada.Dia);
    printf("%d/", A->DataEntrada.Mes);
    printf("%d", A->DataEntrada.Ano);
    printf("\n\t\t\t\t\tData Entrada:");
    printf("\n\t\t\t\t\t%d/", A->DataSaida.Dia);
    printf("%d/", A->DataSaida.Mes);
    printf("%d", A->DataSaida.Ano);

    printf("\nDescrição: ");
    printf("%s\n", A->Descricao);
    printf("\t----------------------------------------\n");
}
void ImprimirTudoAlarmes(){
    FILE *fp;
    char linha[BYTES_MAX];
    Alarme_t Aux;
    fp=fopen(ALARME_FILE, "rt");
    while (!feof(fp)){
        fgets(linha, BYTES_MAX,fp);
        String2Alarme_t(linha, &Aux);
        if(!feof(fp)){
            ImprimirAlarme(&Aux);
        }
    }
    fclose(fp);
}



/*------------------Alarme Atuado--------------------------*/
void ImprimirAtuado(Alarme_t *A){
    Equipamento_t E;
    ReadEquipamento(A->N_Serie_Equi, &E);

    printf("\nNome:\tAtivo:\tId:\tClassif:\tData de Cadastro:");
    printf("\n%s", A->Nome);
    switch (A->Ativo)
    {
    case TRUE:
        printf("\tSim.");
        break;
    case FALSE:
        printf("\tNão.");
        break;
    
    default:
        printf("\tErro. Lido=%d",A->Ativo);
        break;
    }
    
    printf("\t%d", A->identificador);
    switch (A->Classificacao)
    {
        case ALTA:
            printf("\tAlta\t");
            break;
        case MEDIA:
            printf("\tMédia");
            break;
        case BAIXA :
            printf("\tBaixa\t");
            break;
        default:
            printf("\tErro. Lido=%d",A->Classificacao);
            break;
    }

    printf("\t%d/", A->DataCadastro.Dia);
    printf("%d/", A->DataCadastro.Mes);
    printf("%d", A->DataCadastro.Ano);
    printf("\nN Ativaçao:\tNSerie Equip:\t\tData Entrada:");
    printf("\n%d", A->N_Ativacao);
    printf("\t\t%d", A->N_Serie_Equi);
    printf("\t\t\t%d/", A->DataEntrada.Dia);
    printf("%d/", A->DataEntrada.Mes);
    printf("%d", A->DataEntrada.Ano);
    printf("\nNome do Equipamento Relacionado:\tData Entrada:");
    printf("\n%s", E.Nome);
    printf("\t\t\t\t\t%d/", A->DataSaida.Dia);
    printf("%d/", A->DataSaida.Mes);
    printf("%d", A->DataSaida.Ano);

    printf("\nDescrição Alarme: ");
    printf("%s\n", A->Descricao);
    printf("\nDescrição Equipamento: ");
    printf("%s\n", E.Descricao);
    printf("\t----------------------------------------\n");
}
void ImprimirTodosAtuados(){
    FILE *fp;
    char linha[BYTES_MAX];
    Alarme_t Aux;
    fp=fopen(ALARME_FILE, "rt");
    while (!feof(fp)){
        fgets(linha, BYTES_MAX,fp);
        String2Alarme_t(linha, &Aux);
        if((!feof(fp))&&(Aux.Ativo==TRUE)){
            ImprimirAtuado(&Aux);
        }
    }
    fclose(fp);
}