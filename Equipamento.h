/**
 * @file Equipamento.h
 * @author Gustavo Correa (gustavocorrea@alunos.utfpr.edu.br)
 * @brief Arquivo contendo o tipo de dado Equipamento_t, suas funções de CRUD as suas funções auxiliares.
 * @version 0.1
 * @date 2020-09-27
 * @copyright Copyright (c) 2020
 */

/**
 * @brief Estrutura de dados para o armazenamento e manipulação de equipamentos.
 * 
 */
typedef struct Equipamento_t{
    char Nome[NOME_MAX];            /**< String contendo o nome do equipamento. */
    int N_Serie;                    /**< Inteiro contendo o número de serie do equipamento.*/
    int Tipo;                       /**< Inteiro contendo o tipo do equipamento. (TENSAO:1 CORRENTE:2 OLEO:3)*/
    Data_t Data;                    /**< Date_t contendo a data em que o equipamento foi cadastrado. */
    char Descricao[DESC_MAX];       /**< String contendo a descrição do equipamento.*/
    
} Equipamento_t;

/*-----------------PROTÓTIPOS---------------------------*/
/**
 * @brief Cria/insere um Equipamento object.
 * 
 * @param A Recebe um Equipamento_t que será inserido a lista de Equipamentos.
 * @return int Retorna TRUE no caso de sucesso e FALSE em caso de falha.
 */
int CreateEquipamento(Equipamento_t E);
/**
 * @brief Lê um Equipamento a partir de um N_Serie e armazena em A o Equipamento encontrado.
 * 
 * @param N_Serie N_Serie que será lido.
 * @param A Ponteiro para um Equipamento_t onde ficará armazenado o Equipamento encontrado.
 * @return int Retorna TRUE no caso de sucesso e FALSE em caso de falha.
 */
int ReadEquipamento(int N_Serie, Equipamento_t *E);
/**
 * @brief Atualiza um Equipamento.
 * 
 * @param A Equipamento_t que será atualizado, deve já conter todos os termos que será inseridos.
 * @return int Retorna TRUE no caso de sucesso e FALSE em caso de falha.
 */
int UpdateEquipamento(Equipamento_t E);
/**
 * @brief Deleta da lista de Equipamentos um Equipamento a partir de seu N_Serie.
 * 
 * @param N_Serie N_Serie do Equipamento a ser removido.
 * @return int Retorna TRUE no caso de sucesso e FALSE em caso de falha.
 */
int DeleteEquipamento(int N_Serie);
/**
 * @brief Obtem um inteiro a partir de uma string.
 * 
 * @param i Contador que aponta a posição da string onde deverá ser lido o inteiro.
 * @param linha Buffer contendo a string onde será lido o inteiro.
 * @return int Retorna o intero lido.
 */
int GetInt(int *i, char *linha);
/**
 * @brief Limpa um buffer.
 * 
 * @param buf Buffer a ser limpo.
 */
void Limpar_buffer(char *buf);
/**
 * @brief Função que converte uma string em uma estrutura de dados Equipamento_t.
 * 
 * @param linha Buffer contendo a string
 * @param A Estrutura de dados Equipamento_t em que será armazenada o contêudo da string.
 * @warning A string recebida deverá ter os itens separados por tabs ('\t') e finalizados com um '\\n' na seguinte ordem: N_Serie, Nome, Tipo, Data(Dia, Mes e Ano) e Descrição.
 */
void String2Equipamento_t(char *linha, Equipamento_t *Equip);
/*-----------------FUNÇÕES AUXILIARES---------------------------*/
void Limpar_buffer(char *buf){
    int i;
    for (i = 0; i < INT_MAX; i++){
        buf[i]=0;
    }
}
int GetInt(int *i, char *linha){
    int j=0;
    char buffer[INT_MAX];
    Limpar_buffer(buffer);
    while(linha[*i]!='\t'){
        buffer[j] =linha[*i];
        *i=*i+1;
        j++;
    }
    *i=*i+1;
    return atoi(buffer);
}
void String2Equipamento_t(char *linha, Equipamento_t *Equip){
    int j=0,i=0;
    char bufferNome[NOME_MAX];
    char bufferDesc[DESC_MAX];

    Equip->N_Serie=GetInt(&i,linha);
    while(linha[i]!='\t'){//Le os nomes
        bufferNome[j] =linha[i];
        i++;
        j++;
    }
    bufferNome[j]='\0';
    strcpy(Equip->Nome, bufferNome);
    j=0;
    i++;
    Equip->Tipo=GetInt(&i,linha);
    Equip->Data.Dia=GetInt(&i,linha);
    Equip->Data.Mes=GetInt(&i,linha);
    Equip->Data.Ano=GetInt(&i,linha);
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
        fprintf(fp,"%d\t%s\t%d\t%d\t%d\t%d\t%s\n",E.N_Serie,E.Nome,E.Tipo,E.Data.Dia,E.Data.Mes,E.Data.Ano,E.Descricao );
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
    Equipamento_t Aux;
    if(ReadEquipamento(E.N_Serie,&Aux)==FALSE){
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
            if((strcmp(linha, linhaAUX)!=0)&&(!feof(fp))){
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