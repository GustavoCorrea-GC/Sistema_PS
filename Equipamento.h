/**
 * @brief Arquivo contendo o tipo de dado Equipamento_t e as
 * suas funções de CRUD e suas funções auxiliares.
 * 
 * @file Equipamento.h
 * @author Gustavo Correa
 * @date 2020-09-27
 */

typedef struct Equipamento_t{
    char Nome[NOME_MAX];
    int N_Serie;
    int Tipo;
    Data_t Data;               //TODO: Adicionar a time.h
    char Descricao[DESC_MAX];
    
} Equipamento_t;

/*-----------------PROTÓTIPOS---------------------------*/
int CreateEquipamento(Equipamento_t E);
int ReadEquipamento(int N_Serie, Equipamento_t *E);
int UpdateEquipamento(Equipamento_t E);
int DeleteEquipamento(int N_Serie);
void Limpar_buffer(char *buf);
void String2Equipamento_t(char *linha, Equipamento_t *Equip);
/*-----------------FUNÇÕES AUXILIARES---------------------------*/
void Limpar_buffer(char *buf){
    int i;
    for (i = 0; i < INT_MAX; i++){
        buf[i]=0;
    }
}
void String2Equipamento_t(char *linha, Equipamento_t *Equip){
    int j=0,i=0;
    char bufferINT[INT_MAX];
    char bufferNome[NOME_MAX];
    char bufferDesc[DESC_MAX];

    while(linha[i]!='\t'){//Le os Numeros de Serie
        bufferINT[j] =linha[i];
        i++;
        j++;
    }
    Equip->N_Serie=atoi(bufferINT);
    Limpar_buffer(bufferINT);
    j=0;
    i++;
    while(linha[i]!='\t'){//Le os nomes
        bufferNome[j] =linha[i];
        i++;
        j++;
    }
    bufferNome[j]='\0';
    strcpy(Equip->Nome, bufferNome);
    j=0;
    i++;
    while(linha[i]!='\t'){//Le os Tipos
        bufferINT[j] =linha[i];
        i++;
        j++;
    }
    Equip->Tipo=atoi(bufferINT);
    Limpar_buffer(bufferINT);
    j=0;
    i++;
    while(linha[i]!='\t'){//Le os dias
        bufferINT[j] =linha[i];
        i++;
        j++;
    }
    Equip->Data.Dia=atoi(bufferINT);
    Limpar_buffer(bufferINT);
    j=0;
    i++;
    while(linha[i]!='\t'){//Le os Meses
        bufferINT[j] =linha[i];
        i++;
        j++;
    }
    Equip->Data.Mes=atoi(bufferINT);
    Limpar_buffer(bufferINT);
    j=0;
    i++;
    while(linha[i]!='\t'){//Le os anos
        bufferINT[j] =linha[i];
        i++;
        j++;
    }
    Equip->Data.Ano=atoi(bufferINT);
    Limpar_buffer(bufferINT);
    j=0;
    i++;
    while(linha[i]!='\n'){//Le as descrições
        bufferDesc[j] =linha[i];
        i++;
        j++;
    }
    bufferDesc[j]='\0';
    strcpy(Equip->Descricao, bufferDesc);
}
/*-----------------FUNÇÕES---------------------------*/
int CreateEquipamento(Equipamento_t E){
    FILE *fp;
    Equipamento_t Aux;
    if(ReadEquipamento(E.N_Serie,&Aux)==TRUE){
        printf("Número de serie já existente.");
        return FALSE;
    }
    else{    
        fp=fopen(EQUIP_FILE, "a");
        fprintf(fp,"%s\t%d\t%d\t%d\t%d\t%d\t%s\n",E.Nome,E.N_Serie,E.Tipo,E.Data.Dia,E.Data.Mes,E.Data.Ano,E.Descricao );
        fclose(fp);
        return TRUE;
    }
}
int ReadEquipamento(int N_Serie, Equipamento_t *E){
    FILE *fp;
    char linha[BYTES_MAX];
    Equipamento_t Aux;
    fp=fopen(EQUIP_FILE, "rt");
    while (!feof(fp)){
        fgets(linha, BYTES_MAX,fp);
        String2Equipamento_t(linha, &Aux);
        if(Aux.N_Serie==N_Serie){
            strcpy(E->Nome,Aux.Nome);
            E->N_Serie=Aux.N_Serie;
            E->Tipo=Aux.Tipo;
            E->Data=Aux.Data;
            strcpy(E->Descricao,Aux.Descricao);
            fclose(fp);
            return TRUE;
        }
    }
    fclose(fp);
    return FALSE;
}
int UpdateEquipamento(Equipamento_t E){
    if(ReadEquipamento(E.N_Serie,&E)==FALSE){
        printf("Número de serie não existente.");
        return FALSE;
    }
    else{
        DeleteEquipamento(E.N_Serie);
        CreateEquipamento(E);
        return TRUE;
    }
}
int DeleteEquipamento(int N_Serie){
    FILE *fp;
    FILE *fpTemp;
    char linha[BYTES_MAX];
    char linhaAUX[BYTES_MAX];
    Equipamento_t Aux;

    if(ReadEquipamento(N_Serie,&Aux)==FALSE){
        printf("Número de serie não existente.");
        return FALSE;
    }

    fp=fopen(EQUIP_FILE, "rt");
    if(fp!=NULL){
        while (!feof(fp)){//Localiza linha a ser removida.
            fgets(linha, BYTES_MAX,fp);
            String2Equipamento_t(linha, &Aux);
            if(Aux.N_Serie==N_Serie){
                strcpy(linhaAUX, linha);
            }
        }
        fclose(fp);
        fp=fopen(EQUIP_FILE, "rt");
        fpTemp=fopen(TEMP, "w");
        while (!feof(fp)){//Escreve em um arquivo temporario todas as linhas menos a que desejamos ser removida.
            fgets(linha, BYTES_MAX,fp);
            if(strcmp(linha, linhaAUX)!=0){
                fprintf(fpTemp, "%s",linha);
            }
        }
        fclose(fp);
        fclose(fpTemp);
        rename(TEMP, EQUIP_FILE);
        remove(TEMP);
        return TRUE;
    }
    return FALSE;

}