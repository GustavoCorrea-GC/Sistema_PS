/**
 * @brief Arquivo contendo as definições e tipos de dados utilizados no sistema.
 * 
 * @file Sistema.h
 * @author Gustavo Correa
 * @date 2020-09-26
 */

/**
 * @brief Define o tamanho maximo dos buffers
 * 
 */
#define BYTES_MAX 512   
#define INT_MAX 10      //Tamanho do buffer que armazena inteiros.
#define NOME_MAX 128    //Tamanho da string de nome.
#define DESC_MAX 256    //Tamanho da string de descrição.
#define TRUE 0
#define FALSE 1
#define EQUIP_FILE "Equipamentos.tsv"
#define ALARME_FILE "Alarmes.tsv"
#define TEMP "Temporario.temp"

typedef int bool;
/**
 * @brief 
 * 
 */
typedef struct StrAlarm_t{
    int Id;
    char Desc[DESC_MAX];
}StrAlarm_t;
/**
 * @brief 
 * 
 */
typedef struct IntAlarm_t{
    int Id;
    int Val;
}IntAlarm_t;

/**
 * @brief 
 * 
 */
enum{           //Enum dos Tipos.
    ALTA = 1,
    MEDIA,
    BAIXA 
};
/**
 * @brief 
 * 
 */
enum{           //Enum das Classificações.
    TENSAO = 1,
    CORRENTE,
    OLEO
};
/**
 * @brief Tipo de dados para datas.
 * 
 * TODO: Utilizar a time.h
 * 
 */
typedef struct Data_t
{
    int Dia;
    int Mes;
    int Ano;
}Data_t;




