typedef struct Equipamento_t{             //Tipo de dado Equipamento_t
    char Nome[128];
    int N_Serie;
    int Tipo;
    Data_t Data;               //TODO: Adicionar a time.h
    char Descricao[256];
    struct Equipamento_t *proximo;
    
} Equipamento_t;

typedef struct Lista_Equipamentos
{
    Equipamento_t *inicio;
    int quantidade;
}Lista_Equipamentos;

/**
 * @brief 
 * 
 * @param Lista 
 */
void Definir_ListaEquipamentos (Lista_Equipamentos *Lista){
    Lista->inicio=NULL;
    Lista->quantidade=0;

}


/** 
 * @brief Insere o primeiro elemento na lista de equipamentos
 * 
 * @param inicio 
 * @param Nome 
 * @param N_serie 
 * @param Tipo 
 * @param Data 
 * @param Descricao 
 * @return int 
 */
int Inserir_Primeiro_Equipamento(Lista_Equipamentos *Lista, Equipamento_t Aux){
    
    Equipamento_t *item; 
    item = (Equipamento_t *) malloc(sizeof(Equipamento_t));

    strcpy(item->Nome,Aux.Nome);
    item->N_Serie=Aux.N_Serie;
    item->Tipo=Aux.Tipo;
    item->Data=Aux.Data;
    strcpy(item->Descricao,Aux.Descricao);
    item->proximo=NULL;
    Lista->inicio=item;
    Lista->quantidade++;
    
    return 0;
}

int inserirEquipamento(Lista_Equipamentos *Lista, Equipamento_t Equip){
    if(Lista->quantidade<1){ 
        Inserir_Primeiro_Equipamento(Lista, Equip);
        return 0;
    }
    else{
        Equipamento_t *item; 
        item = (Equipamento_t *) malloc(sizeof(Equipamento_t));
        Equipamento_t *Aux;
        Aux=Lista->inicio;
        while (Aux->proximo!=NULL) Aux=Aux->proximo;

        strcpy(item->Nome,Equip.Nome);
        item->N_Serie=Equip.N_Serie;
        item->Tipo=Equip.Tipo;
        item->Data=Equip.Data;
        strcpy(item->Descricao,Equip.Descricao);
        item->proximo=NULL;
        Aux->proximo=item;
        Lista->quantidade++;
        
        return 0;   
    }
}

/**
 * @brief 
 * 
 * @param Lista 
 * @param N_Serie 
 * @param p 
 * @return int 
 */
int Busca_N_Serie(Lista_Equipamentos *Lista, int N_Serie, Equipamento_t **p) {
    if (Lista->quantidade==0) return 1;
    else{
        *p = Lista->inicio;
        while (*p != NULL) {
            if ((*p)->N_Serie==N_Serie)
                return 1;
            else
                *p = (*p)->proximo;
        }
    }
    return 0;
}
/**
 * @brief 
 * 
 * @param Lista 
 * @param N_Serie 
 * @return int 
 */
int RemoverEquipamento(Lista_Equipamentos *Lista, int N_Serie){
    Equipamento_t *Aux, *Aux2;
    if (Lista->quantidade<2){
        if(Lista->quantidade==0){
            return 0;
        }
        else{
            Aux=Lista->inicio;
            free(Aux);
            Lista->inicio=NULL;
            return 0;
        }
    }
    else{
        Busca_N_Serie(Lista, N_Serie,&Aux);
        if(Aux->proximo!=NULL){
            Aux2=Lista->inicio;
            if(Aux2==Aux){//Caso primeiro elemento da lista precisa ser removido.
                Lista->inicio=Aux->proximo;
                free(Aux);
                return 0;
            }
            else{
                while (Aux2->proximo!=Aux)Aux2=Aux2->proximo;
                Aux2->proximo=Aux->proximo;
                free(Aux);
                return 0;
            }
        }
        else{
            while (Aux2->proximo!=Aux)Aux2=Aux2->proximo;
            Aux2->proximo=NULL;
            free(Aux);
            return 0;
            
        }   
    }
}
int AtualizaEquipamento(Lista_Equipamentos *Lista, int N_Serie){
    Equipamento_t *Aux;
    Busca_N_Serie(Lista, N_Serie, &Aux);
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

int Criar_Equipamento(Lista_Equipamentos *Lista){
    Equipamento_t Aux;
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
    inserirEquipamento(Lista, Aux);
}