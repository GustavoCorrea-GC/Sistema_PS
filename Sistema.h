/**
 * @file Sistema.h
 * @author Gustavo Correa (gustavocorrea@alunos.utfpr.edu.br)
 * @brief Arquivo contendo as definições e tipos de dados utilizados no sistema.
 * @version 0.1
 * @date 2020-09-26
 * 
 * @copyright Copyright (c) 2020
 */

/**
 * @brief Define o tamanho maximo dos buffers
 * 
 */
#define BYTES_MAX 512   
/**
 * @brief Define o tamanho do buffer que armazena inteiros.
 * 
 */
#define INT_MAX 10     
/**
 * @brief Define o tamanho da string de nome.
 * 
 */
#define NOME_MAX 128    
/**
 * @brief Define o tamanho da string de descrição.
 * 
 */
#define DESC_MAX 256    
#define TRUE 0
#define FALSE 1
/**
 * @brief Define o caminho e o nome do arquivo que contém a lista de equipamentos cadastrados no sistema.
 * 
 */
#define EQUIP_FILE "Equipamentos.tsv"
/**
 * @brief Define o caminho e o nome do arquivo que contém a lista de alarmes cadastrados no sistema.
 * 
 */
#define ALARME_FILE "Alarmes.tsv"
/**
 * @brief Define o caminho e o nome do arquivo temporário que é utilizado no sistema.
 * 
 */
#define TEMP "Temporario.temp"

typedef int bool;
/**
 * @brief Estrutura de dados que contém um identificador de alarme e uma string, utilizado para ordenação de strings.
 * @see SortString()
 */
typedef struct StrAlarm_t{
    int Id;                 /**< Inteiro contendo o identificador do alarme. */
    char Desc[DESC_MAX];    /**< String contendo a descrição do alarme a ser comparado. */
}StrAlarm_t;
/**
 * @brief Estrutura de dados que contém um identificador de alarme e um inteiro, utilizada para a ordenação dos alarmes.
 * @see SortInt()
 */
typedef struct IntAlarm_t{
    int Id;     /**< Inteiro contendo o identificador do alarme. */
    int Val;    /**< Inteiro contendo o valor a ser comparado. */
}IntAlarm_t;

/**
 * @brief Enum contendo a definição das classificações dos alarmes.
 * 
 */
enum{           
    ALTA = 1,   /**< Classificação alta para o alarme. */
    MEDIA,      /**< Classificaçao média para o alarme. */
    BAIXA       /**< Classificação baixa para o alarme. */
};
/**
 * @brief Enum contendo a definição dos tipos de equipamentos.
 * 
 */
enum{           
    TENSAO = 1, /**< Equipamento do tipo tensão. */
    CORRENTE,   /**< Equipamento do tipo corrente. */
    OLEO        /**< Equipamento do tipo óleo. */
};
/**
 * @brief Tipo de dados para datas.
 * 
 * @todo Utilizar a time.h para definir datas.
 * 
 */
typedef struct Data_t
{
    int Dia;
    int Mes;
    int Ano;
}Data_t;




