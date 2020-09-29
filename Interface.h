/**
 * @brief Arquivo contendo as funções de interface e suas funções auxiliares.
 * 
 * @file Equipamento.h
 * @author Gustavo Correa
 * @date 2020-09-27
 */
/*------------------Prototipos--------------------------*/
/**
 * @brief GetSize Obter tamanho.
 * Função que obtem a quantidade de elementos de um arquivo.
 * @param A Caminho para o arquivo que se deseja saber o tamanho.
 * @return int 
 */
int GetSize(char *A);
/**
 * @brief 
 * 
 * @param vetor 
 * @param inicio 
 * @param fim 
 */
void SortString(StrAlarm_t vetor[], int inicio, int fim);
/**
 * @brief 
 * 
 * @param vetor 
 * @param inicio 
 * @param fim 
 */
void SortInt(IntAlarm_t vetor[],int inicio, int fim);
/**
 * @brief 
 * 
 * @param Eq 
 */
void ImprimirEquipamento(Equipamento_t *Eq);
/**
 * @brief 
 * 
 */
void ImprimirTudoEquipamentos();
/**
 * @brief 
 * 
 */
void Atualiza_Equipamento();
/**
 * @brief 
 * 
 */
void Criar_Equipamento();
/**
 * @brief 
 * 
 */
void Remover_Equipamento();
/**
 * @brief 
 * 
 */
void Pesquisa_Equipamento();
/**
 * @brief 
 * 
 * @param A 
 */
void ImprimirAlarme(Alarme_t *A);
/**
 * @brief 
 * 
 */
void ImprimirTudoAlarmes();
/**
 * @brief 
 * 
 */
void Atualiza_Alarme();
/**
 * @brief 
 * 
 */
void Criar_Alarme();
/**
 * @brief 
 * 
 */
void Remover_Alarme();
/**
 * @brief 
 * 
 */
void Pesquisar_Alarme();
/**
 * @brief 
 * 
 * @param A 
 */
void ImprimirAtuado(Alarme_t *A);
/**
 * @brief 
 * 
 */
void ImprimirTodosAtuados();
/**
 * @brief 
 * 
 */
void Ativar_Alarmes();
/**
 * @brief 
 * 
 */
void Desativar_Alarmes();
/**
 * @brief 
 * 
 */
void OrdenarClassificacao();
/**
 * @brief 
 * 
 */
void Ordenar_Desc();
/**
 * @brief 
 * 
 */
void OrdenarAtuacao();
/**
 * @brief 
 * 
 */
void Filtrar();
/**
 * @brief 
 * 
 */
void Menu();
/*------------------Auxiliares--------------------------*/
int GetSize(char *A){
    FILE *Aux;
    int i=0;
    char linha[BYTES_MAX];
    Aux=fopen(ALARME_FILE, "rt");
    if(Aux==NULL){
        printf("Oh dear, something went wrong with read()! %s\n", strerror(errno));
        //printf("Cagoaqui1");
        return 0;
    }
    while (!feof(Aux)){
        fgets(linha, BYTES_MAX,Aux);
        if(!feof(Aux)){
            i++;
        }
    }
    fclose(Aux);
    return i;
}
void SortString(StrAlarm_t vetor[], int inicio, int fim){
    StrAlarm_t pivo,aux;
    int i, j, meio;
    i = inicio;
    j = fim;
    meio = (int) ((i + j) / 2);
    pivo = vetor[meio];
    do{
        while(strcmp(vetor[i].Desc,pivo.Desc)<0){
            i++;
        }
        
        while(strcmp(vetor[j].Desc,pivo.Desc)>0){
            j--;
        }
        if(i <= j){
        aux = vetor[i];
        vetor[i] = vetor[j];
        vetor[j] = aux;
        i = i + 1;
        j = j - 1;
    }
    }while(j > i);
    if(inicio < j) 
        SortString(vetor, inicio, j);
    if(i < fim) 
        SortString(vetor, i, fim);

}
void SortInt(IntAlarm_t vetor[],int inicio, int fim){
    IntAlarm_t aux;
    int pivo, i, j, meio;
   
    i = inicio;
    j = fim;
    
    meio = (int) ((i + j) / 2);
    pivo = vetor[meio].Val;
    
    do{
        while (vetor[i].Val < pivo) i = i + 1;
        while (vetor[j].Val > pivo) j = j - 1;
        
        if(i <= j){
            aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;
            i = i + 1;
            j = j - 1;
        }
    }while(j > i);
    
    if(inicio < j) 
        SortInt(vetor, inicio, j);
    if(i < fim)
        SortInt(vetor, i, fim); 
}
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
    getchar();
    fgets(Aux.Nome,NOME_MAX,stdin);
    Aux.Nome[strlen(Aux.Nome)-1]='\0';
    printf("Digite o novo tipo do equipamento (Tensão:1 Corrente:2 Óleo:3):\n");
    scanf("%d", &Aux.Tipo);
    printf("Digite o novo dia de cadastro do equipamento:\n");
    scanf("%d", &Aux.Data.Dia);
    printf("Digite o novo mes de cadastro do equipamento:\n");
    scanf("%d", &Aux.Data.Mes);
    printf("Digite o novo ano de cadastro do equipamento:\n");
    scanf("%d", &Aux.Data.Ano);
    printf("Digite a nova Descricao do equipamento:\n");
    getchar();
    fgets(Aux.Descricao, DESC_MAX,stdin);
    Aux.Descricao[strlen(Aux.Descricao)-1]='\0';
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
    getchar();
    fgets(Aux.Nome,NOME_MAX,stdin);
    Aux.Nome[strlen(Aux.Nome)-1]='\0';
    printf("\nDigite o novo numero de serie do equipamento:\n");
    scanf("%d", &Aux.N_Serie);
    printf("\nDigite o novo tipo do equipamento (Tensão:1 Corrente:2 Óleo:3):\n");
    scanf("%d", &Aux.Tipo);
    printf("\nDigite o novo dia de cadastro do equipamento:\n");
    scanf("%d", &Aux.Data.Dia);
    printf("\nDigite o novo mes de cadastro do equipamento:\n");
    scanf("%d", &Aux.Data.Mes);
    printf("\nDigite o novo ano de cadastro do equipamento:\n");
    scanf("%d", &Aux.Data.Ano);
    printf("\nDigite a nova Descricao do equipamento:\n");
    getchar();
    fgets(Aux.Descricao,DESC_MAX,stdin);
    Aux.Descricao[strlen(Aux.Descricao)-1]='\0';
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

void Atualiza_Alarme(){
    Alarme_t Aux;
    printf("Digite o identificador do alarme:\n");
    scanf("%d", &Aux.identificador);
    printf("Digite o novo nome do alarme:\n");
    getchar();
    fgets(Aux.Nome,NOME_MAX,stdin);
    Aux.Nome[strlen(Aux.Nome)-1]='\0';
    printf("Digite o novo numero de serie do equipamento relacionado:\n");
    scanf("%d", &Aux.N_Serie_Equi);
    printf("Digita 1 para alarme ativado e 0 para alarme desativado\n");
    scanf("%d", &Aux.Ativo);
    printf("Digite o numero de vezes que esse alarme já foi ativado:\n");
    scanf("%d", &Aux.N_Ativacao);
    printf("Digite a nova classificação do alarme(Alta:1 Média:2 Baixa:3):\n");
    scanf("%d", &Aux.Classificacao);
    printf("Digite o novo dia de cadastro do Alarme:\n");
    scanf("%d", &Aux.DataCadastro.Dia);
    printf("Digite o novo mes de cadastro do alarme:\n");
    scanf("%d", &Aux.DataCadastro.Mes);
    printf("Digite o novo ano de cadastro do alarme:\n");
    scanf("%d", &Aux.DataCadastro.Ano);
    printf("Digite o novo dia de Entrada do Alarme:\n");
    scanf("%d", &Aux.DataEntrada.Dia);
    printf("Digite o novo mes de entrada do alarme:\n");
    scanf("%d", &Aux.DataEntrada.Mes);
    printf("Digite o novo ano de entrada do alarme:\n");
    scanf("%d", &Aux.DataEntrada.Ano);
    printf("Digite o novo dia de Saida do Alarme:\n");
    scanf("%d", &Aux.DataSaida.Dia);
    printf("Digite o novo mes de Saida do alarme:\n");
    scanf("%d", &Aux.DataSaida.Mes);
    printf("Digite o novo ano de Saida do alarme:\n");
    scanf("%d", &Aux.DataSaida.Ano);
    printf("Digite a nova Descricao do alarme:\n");
    getchar();
    fgets(Aux.Descricao,DESC_MAX,stdin);
    Aux.Descricao[strlen(Aux.Descricao)-1]='\0';
    if(UpdateAlarme(Aux)==TRUE){
        printf("\nModificado com sucesso.\n");
    }
    else{
        printf("\nFalha na modificação.\n");
    }
    
}
void Criar_Alarme(){
    Alarme_t Aux;
    printf("Digite o identificador do alarme:\n");
    scanf("%d", &Aux.identificador);
    printf("Digite o novo nome do alarme:\n");
    getchar();
    fgets(Aux.Nome,NOME_MAX,stdin);
    Aux.Nome[strlen(Aux.Nome)-1]='\0';
    printf("Digite o novo numero de serie do equipamento relacionado:\n");
    scanf("%d", &Aux.N_Serie_Equi);
    printf("Digita 1 para alarme ativado e 0 para alarme desativado\n");
    scanf("%d", &Aux.Ativo);
    printf("Digite o numero de vezes que esse alarme já foi ativado:\n");
    scanf("%d", &Aux.N_Ativacao);
    printf("Digite a nova classificação do alarme (Alta:1 Média:2 Baixa:3):\n");
    scanf("%d", &Aux.Classificacao);
    printf("Digite o novo dia de cadastro do Alarme:\n");
    scanf("%d", &Aux.DataCadastro.Dia);
    printf("Digite o novo mes de cadastro do alarme:\n");
    scanf("%d", &Aux.DataCadastro.Mes);
    printf("Digite o novo ano de cadastro do alarme:\n");
    scanf("%d", &Aux.DataCadastro.Ano);
    printf("Digite o novo dia de Entrada do Alarme:\n");
    scanf("%d", &Aux.DataEntrada.Dia);
    printf("Digite o novo mes de entrada do alarme:\n");
    scanf("%d", &Aux.DataEntrada.Mes);
    printf("Digite o novo ano de entrada do alarme:\n");
    scanf("%d", &Aux.DataEntrada.Ano);
    printf("Digite o novo dia de Saida do Alarme:\n");
    scanf("%d", &Aux.DataSaida.Dia);
    printf("Digite o novo mes de Saida do alarme:\n");
    scanf("%d", &Aux.DataSaida.Mes);
    printf("Digite o novo ano de Saida do alarme:\n");
    scanf("%d", &Aux.DataSaida.Ano);
    printf("Digite a nova Descricao do alarme:\n");
    getchar();
    fgets(Aux.Descricao,DESC_MAX,stdin);
    Aux.Descricao[strlen(Aux.Descricao)-1]='\0';
    if(CreateAlarme(Aux)==TRUE){
        printf("\nCriado com sucesso.\n");
    }
    else{
        printf("\nFalha na criação.\n");
    }
    
    
}
void Remover_Alarme(){
    int Aux;
    printf("\nDigite o numero de serie do Alarme a ser removido:\n");
    scanf("%d", &Aux);
    if(DeleteAlarme(Aux)==TRUE){
        printf("\nRemovido com sucesso.\n");
    }
    else{
        printf("\nFalha na remoção.\n");
    }
}
void Pesquisar_Alarme(){
    int Aux;
    Alarme_t A;
    printf("\nDigite o numero de serie do equipamento:\n");
    scanf("%d", &Aux);
    if(ReadAlarme(Aux,&A)==TRUE){
        ImprimirAlarme(&A);
    }
    else{
        printf("\nEquipamento não encontrado.\n");
    }
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

void Ativar_Alarmes(){
    int Aux;
    Alarme_t A;
    printf("Digite a Identificação do Alarme para ativa-lo.\n");
    scanf("%d", &Aux);
    if(ReadAlarme(Aux, &A)==TRUE){
        if (A.Ativo==FALSE){
            A.Ativo=TRUE;
            A.N_Ativacao++;
            printf("Digite o dia de Entrada do Alarme:\n");
            scanf("%d", &A.DataEntrada.Dia);
            printf("Digite o mes de entrada do alarme:\n");
            scanf("%d", &A.DataEntrada.Mes);
            printf("Digite o ano de entrada do alarme:\n");
            scanf("%d", &A.DataEntrada.Ano);
            printf("Digite o dia de Saida do Alarme:\n");
            scanf("%d", &A.DataSaida.Dia);
            printf("Digite o mes de Saida do alarme:\n");
            scanf("%d", &A.DataSaida.Mes);
            printf("Digite o ano de Saida do alarme:\n");
            scanf("%d", &A.DataSaida.Ano);
            UpdateAlarme(A);
        }
        else{
            printf("Alarme já ativado.");
        }
    }
}
void Desativar_Alarmes(){
    int Aux;
    Alarme_t A;
    printf("Digite a Identificação do Alarme para desativa-lo:\n");
    scanf("%d", &Aux);
    if(ReadAlarme(Aux, &A)==TRUE){
        if (A.Ativo==TRUE){
            A.Ativo=FALSE;
            UpdateAlarme(A);
        }
        else{
            printf("Alarme já desativado.\n");
        }
    }
}

/*------------------Ordenação--------------------------*/
void OrdenarClassificacao(){
    FILE *fp;
    char linha[BYTES_MAX];
    Alarme_t Aux;
    fp=fopen(ALARME_FILE, "rt");
    while (!feof(fp)){
        fgets(linha, BYTES_MAX,fp);
        String2Alarme_t(linha, &Aux);
        if((!feof(fp))&&(Aux.Classificacao==ALTA)){
            ImprimirAlarme(&Aux);
        }
    }
    fclose(fp);
    fp=fopen(ALARME_FILE, "rt");
    while (!feof(fp)){
        fgets(linha, BYTES_MAX,fp);
        String2Alarme_t(linha, &Aux);
        if((!feof(fp))&&(Aux.Classificacao==MEDIA)){
            ImprimirAlarme(&Aux);
        }
    }
    fclose(fp);
    fp=fopen(ALARME_FILE, "rt");
    while (!feof(fp)){
        fgets(linha, BYTES_MAX,fp);
        String2Alarme_t(linha, &Aux);
        if((!feof(fp))&&(Aux.Classificacao==BAIXA)){
            ImprimirAlarme(&Aux);
        }
    }
    fclose(fp);
}
void Ordenar_Desc(){
    FILE *fp;
    int i=0,j;
    int size;
    size=GetSize(ALARME_FILE);
    StrAlarm_t V[size];
    char linha[BYTES_MAX];
    Alarme_t Aux;
    fp=fopen(ALARME_FILE, "rt");
    while (!feof(fp)){
        fgets(linha, BYTES_MAX,fp);
        String2Alarme_t(linha, &Aux);
        if(!feof(fp)){
            V[i].Id=Aux.identificador;
            strcpy(V[i].Desc,Aux.Descricao);
            i++;
            
        }
    }
    fclose(fp);
    SortString(V, 0, i);
    for (j = 0; j < i; j++){
        ReadAlarme(V[j].Id,&Aux);
        ImprimirAlarme(&Aux);
    }
    
}
void OrdenarAtuacao(){
    FILE *fp;
    int i=0,j;
    char linha[BYTES_MAX];
    IntAlarm_t V[GetSize(ALARME_FILE)];
    Alarme_t Aux;
    errno=0;
    fp=fopen(ALARME_FILE, "rt");
    if(fp==NULL){
        printf("Oh dear, something went wrong with read()! %s\n", strerror(errno));
    }
    while (!feof(fp)){
        fgets(linha, BYTES_MAX,fp);
        String2Alarme_t(linha, &Aux);
        if(!feof(fp)){
            V[i].Id=Aux.identificador;
            V[i].Val=Aux.N_Ativacao;
            i++;
        }
    }
    fclose(fp);
    SortInt(V, 0, i);
    for (j = i-1; j > (i-4); j--){
        ReadAlarme(V[j].Id,&Aux);
        ImprimirAlarme(&Aux);
    }
}
void Filtrar(){
    char palavra[DESC_MAX];
    printf("\nDigite a palavra que deseja filtrar:\n");
    scanf("%s", palavra);
    FILE *fp;
    int i=0,j,k;
    int size;
    size=GetSize(ALARME_FILE);
    StrAlarm_t V[size];
    char linha[BYTES_MAX];
    Alarme_t Aux;
    fp=fopen(ALARME_FILE, "rt");
    while (!feof(fp)){
        fgets(linha, BYTES_MAX,fp);
        String2Alarme_t(linha, &Aux);
        if(!feof(fp)){
            V[i].Id=Aux.identificador;
            strcpy(V[i].Desc,Aux.Descricao);
            i++;
        }
    }
    for (j = 0; j < i; j++){
      for(k=0;k<strlen(V[j].Desc)-strlen(palavra);k++){
        if(strncmp(V[j].Desc+(k),palavra,strlen(palavra))==0){
          if(ReadAlarme(V[j].Id,&Aux)==TRUE)
            ImprimirAlarme(&Aux);
            break;
        }
      }
    }

}

void Menu(){
    int opt=0,opt2=0;
    inicio:
    printf("\n\nSelecione a opção desejada:");
    printf("\n\n\tEquipamentos e suas opções digite 1.");
    printf("\n\n\tAlarmes e suas opções digite 2.");
    printf("\n\n\tPara sair digite 0.\n");
    scanf("%d", &opt);

    if(opt==1){
        ImprimirTudoEquipamentos();
        printf("\n\nSelecione a opção desejada:");
        printf("\n\n\tAtualizar Equipamento digite 1:");
        printf("\n\n\tDeletar Equipamento digite 2:");
        printf("\n\n\tPesquisar Equipamento digite 3:");
        printf("\n\n\tCriar Equipamento digite 4:");
        printf("\n\n\tPara sair digite 0.\n");
        scanf("%d", &opt2);
        switch (opt2)
        {
        case 1:
            Atualiza_Equipamento();
            goto inicio;
            break;
        case 2:
            Remover_Equipamento();
            goto inicio;
            break;
        case 3:
            Pesquisa_Equipamento();
            goto inicio;
            break;
        case 4:
            Criar_Equipamento();
            goto inicio;
            break;
        case 0:

            goto inicio;
            break;
        default:
            break;
        }
    }
    if(opt==2){
        ImprimirTudoAlarmes();
        printf("\n\nSelecione a opção desejada:");
        printf("\n\n\tAtualizar Alarme digite 1:");
        printf("\n\n\tDeletar Alarme digite 2:");
        printf("\n\n\tPesquisar Alarme digite 3:");
        printf("\n\n\tCriar Alarme digite 4:");
        printf("\n\n\tMostrar alarmes atuados 5:");
        printf("\n\n\tAtivar Alarme 6:");
        printf("\n\n\tDesativar Alarme 7:");
        printf("\n\n\tOrdenar alarmes por descrição 8:");
        printf("\n\n\tMostrar os 3 alarmes mais atuados 9:");
        printf("\n\n\tFiltrar alarme por descrição 10:");
        printf("\n\n\tOrdenar por classificação 11:");
        printf("\n\n\tPara sair digite 0.\n");
        scanf("%d", &opt2);
        switch (opt2)
        {
        case 1:
            Atualiza_Alarme();
            goto inicio;
            break;
        case 2:
            Remover_Alarme();
            goto inicio;
            break;
        case 3:
            Pesquisar_Alarme();
            goto inicio;
            break;
        case 4:
            Criar_Alarme();
            goto inicio;
            break;
        case 5:
            ImprimirTodosAtuados();
            goto inicio;
            break;
        case 6:
            Ativar_Alarmes();
            goto inicio;
            break;
        case 7:
            Desativar_Alarmes();
            goto inicio;
            break;
        case 8:
            Ordenar_Desc();
            goto inicio;
            break;
        case 9:
            OrdenarAtuacao();
            goto inicio;
            break;
        case 10:
            Filtrar();
            goto inicio;
            break;
        case 11:
            OrdenarClassificacao();
            goto inicio;
            break;
        
        default:
            break;
        }
    }
    
    
}