/**
 * @brief Arquivo contendo o tipo de dado Alarme_t e as
 * suas funções de CRUD e suas funções auxiliares.
 * 
 * @file Equipamento.h
 * @author Gustavo Correa
 * @date 2020-09-27
 */

typedef struct {            //Tipo de dado Alarme_t
    char Nome[128];
    int Classificacao;
    int N_Serie_Equi;
    int identificador;
    bool Ativo;
    int N_Ativacao;
    Data_t DataCadastro;
    Data_t DataEntrada;
    Data_t DataSaida;
    char Descricao[256];
    
} Alarme_t;
 
/*-----------------PROTÓTIPOS---------------------------*/
int CreateAlarme(Alarme_t A);
int ReadAlarme(int Identificador, Alarme_t *A);
int UpdateAlarme(Alarme_t A);
int DeleteAlarme(int Identificador);
void String2Alarme_t(char *linha, Alarme_t *A);
/*-----------------FUNÇÕES AUXILIARES---------------------------*/
void String2Alarme_t(char *linha, Alarme_t *A){
    int j=0,i=0;
    char bufferNome[NOME_MAX];
    char bufferDesc[DESC_MAX];

    A->identificador=GetInt(&i,linha);
    A->N_Serie_Equi=GetInt(&i,linha);
    A->Ativo=GetInt(&i,linha);
    while(linha[i]!='\t'){//Le os nomes
        bufferNome[j] =linha[i];
        i++;
        j++;
    }
    bufferNome[j]='\0';
    strcpy(A->Nome, bufferNome);
    i++;
    j=0;
    A->N_Ativacao=GetInt(&i,linha);
    A->Classificacao=GetInt(&i,linha);
    A->DataCadastro.Dia=GetInt(&i,linha);
    A->DataCadastro.Mes=GetInt(&i,linha);
    A->DataCadastro.Ano=GetInt(&i,linha);
    A->DataEntrada.Dia=GetInt(&i,linha);
    A->DataEntrada.Mes=GetInt(&i,linha);
    A->DataEntrada.Ano=GetInt(&i,linha);
    A->DataSaida.Dia=GetInt(&i,linha);
    A->DataSaida.Mes=GetInt(&i,linha);
    A->DataSaida.Ano=GetInt(&i,linha);
    while(linha[i]!='\n'){//Le as descrições
        bufferDesc[j] =linha[i];
        i++;
        j++;
    }
    bufferDesc[j]='\0';
    strcpy(A->Descricao, bufferDesc);
}
/*-----------------FUNÇÕES---------------------------*/
int CreateAlarme(Alarme_t A){
    FILE *fp;
    Alarme_t Aux;
    if(ReadAlarme(A.identificador,&Aux)==TRUE){
        printf("Número de serie já existente.");
        return FALSE;
    }
    else{    
        fp=fopen(ALARME_FILE, "a");
        fprintf(fp,"%d\t%d\t%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%s\n",  A.identificador,
                                                                                        A.N_Serie_Equi,
                                                                                        A.Ativo,
                                                                                        A.Nome,
                                                                                        A.N_Ativacao,
                                                                                        A.Classificacao,
                                                                                        A.DataCadastro.Dia,
                                                                                        A.DataCadastro.Mes,
                                                                                        A.DataCadastro.Ano,
                                                                                        A.DataEntrada.Dia,
                                                                                        A.DataEntrada.Mes,
                                                                                        A.DataEntrada.Ano,
                                                                                        A.DataSaida.Dia,
                                                                                        A.DataSaida.Mes,
                                                                                        A.DataSaida.Ano,
                                                                                        A.Descricao );
        fclose(fp);
        return TRUE;
    }
}
int ReadAlarme(int Identificador, Alarme_t *A){
    FILE *fp;
    char linha[BYTES_MAX];
    Alarme_t Aux;
    fp=fopen(ALARME_FILE, "rt");
    while (!feof(fp)){
        fgets(linha, BYTES_MAX,fp);
        String2Alarme_t(linha, &Aux);
        if(Aux.identificador==Identificador){
            strcpy(A->Nome,Aux.Nome);
            A->Ativo=Aux.Ativo;
            A->N_Ativacao=Aux.N_Ativacao;
            A->N_Serie_Equi=Aux.N_Serie_Equi;
            A->identificador=Aux.identificador;
            A->Classificacao=Aux.Classificacao;
            A->DataCadastro=Aux.DataCadastro;
            A->DataEntrada=Aux.DataCadastro;
            A->DataSaida=Aux.DataCadastro;
            strcpy(A->Descricao,Aux.Descricao);
            fclose(fp);
            return TRUE;
        }
    }
    fclose(fp);
    return FALSE;
}
int UpdateAlarme(Alarme_t A){
    Alarme_t Aux;
    if(ReadAlarme(A.identificador ,&Aux)==FALSE){
        printf("Alarme não existente.");
        return FALSE;
    }
    else{
        DeleteAlarme(A.identificador);
        CreateAlarme(A);
        return TRUE;
    }
}
int DeleteAlarme(int Identificador){
    FILE *fp;
    FILE *fpTemp;
    char linha[BYTES_MAX];
    char linhaAUX[BYTES_MAX];
    Alarme_t Aux;

    if(ReadAlarme(Identificador,&Aux)==FALSE){
        printf("Número de serie não existente.");
        return FALSE;
    }

    fp=fopen(ALARME_FILE, "rt");
    if(fp!=NULL){
        while (!feof(fp)){//Localiza linha a ser removida.
            fgets(linha, BYTES_MAX,fp);
            String2Alarme_t(linha, &Aux);
            if(Aux.identificador==Identificador){
                strcpy(linhaAUX, linha);
            }
        }
        fclose(fp);
        fp=fopen(ALARME_FILE, "rt");
        fpTemp=fopen(TEMP, "w");
        while (!feof(fp)){//Escreve em um arquivo temporario todas as linhas menos a que desejamos ser removida.
            fgets(linha, BYTES_MAX,fp);
            if((strcmp(linha, linhaAUX)!=0)&&(!feof(fp))){
                fprintf(fpTemp, "%s",linha);
            }
        }
        fclose(fp);
        fclose(fpTemp);
        rename(TEMP, ALARME_FILE);
        remove(TEMP);
        return TRUE;
    }
    return FALSE;
}