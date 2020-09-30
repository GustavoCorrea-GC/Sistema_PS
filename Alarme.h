/**
 * @file Alarme.h
 * @author Gustavo Correa (gustavocorrea@alunos.utfpr.edu.br)
 * @brief Arquivo contendo o tipo de dado Alarme_t, as suas funções de CRUD e suas funções auxiliares.
 * @version 0.1
 * @date 2020-09-27
 * @copyright Copyright (c) 2020
 */

/**
 * @brief Estrutura de dados para o armazenamento e manipulação de alarmes.
 * 
 */
typedef struct {            
    char Nome[NOME_MAX];        /**< String contendo o nome do alarme. */
    int Classificacao;          /**< Inteiro contendo a classificação do alarme em 3 possíveis. (ALTA:1 MEDIA:2 BAIXA:3) */
    int N_Serie_Equi;           /**< Inteiro contendo o número de serie do equipamento relacionado ao alarme. */
    int identificador;          /**< Inteiro contendo o identificador do alarme. */
    bool Ativo;                 /**< Boolean que informa se o alarmes está ativo ou não. (TRUE:0 FALSE:1) */
    int N_Ativacao;             /**< Inteiro contendo o número de vezes que esse alarme já foi ativado.*/
    Data_t DataCadastro;        /**< Date_t contendo a data em que o alarme foi cadastrado. */
    Data_t DataEntrada;         /**< Date_t contendo a data em que o alarme foi ativado. */
    Data_t DataSaida;           /**< Date_t contendo a data em que o alarme será desativado. */
    char Descricao[DESC_MAX];   /**< String contendo a descrição do alarme */
    
} Alarme_t;
 
/*-----------------PROTÓTIPOS---------------------------*/
/**
 * @brief Cria/insere um Alarme object.
 * 
 * @param A Recebe um Alarme_t que será inserido a lista de alarmes.
 * @return int Retorna TRUE no caso de sucesso e FALSE em caso de falha.
 */
int CreateAlarme(Alarme_t A);
/**
 * @brief Lê um alarme a partir de um identificador e armazena em A o alarme encontrado.
 * 
 * @param Identificador Identificador que será lido.
 * @param A Ponteiro para um Alarme_t onde ficará armazenado o alarme encontrado.
 * @return int Retorna TRUE no caso de sucesso e FALSE em caso de falha.
 */
int ReadAlarme(int Identificador, Alarme_t *A);
/**
 * @brief Atualiza um alarme.
 * 
 * @param A Alarme_t que será atualizado, deve já conter todos os termos que será inseridos.
 * @return int Retorna TRUE no caso de sucesso e FALSE em caso de falha.
 */
int UpdateAlarme(Alarme_t A);
/**
 * @brief Deleta da lista de alarmes um alarme a partir de seu identificador.
 * 
 * @param Identificador Identificador do alarme a ser removido.
 * @return int Retorna TRUE no caso de sucesso e FALSE em caso de falha.
 */
int DeleteAlarme(int Identificador);
/**
 * @brief Função que converte uma string em uma estrutura de dados Alarme_t.
 * 
 * @param linha Buffer contendo a string.
 * @param A Estrutura de dados Alarme_t em que será armazenada o conteudo da string.
 * @warning A string recebida deverá ter os itens separados por tabs ('\t') e finalizados com um '\\n' na seguinte ordem: identificador, N_Serie_Equi, Ativo, Nome, N_Ativacao, Classificacao, DataCadastro(Dia, Mes, Ano),DataEntrada(Dia, Mes, Ano), DataSaida(Dia, Mes, Ano) e Descricao.
 */
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