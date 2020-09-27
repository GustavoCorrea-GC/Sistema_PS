

#define BYTES_MAX 512
#define INT_MAX 10
#define NOME_MAX 128
#define DESC_MAX 256
#define TRUE 0
#define FALSE 1
#define EQUIP_FILE "Equipamentos.tsv"
#define TEMP "Temporario.temp"

enum{ //Enum dos Tipos.
    ALTA = 1,
    MEDIA,
    BAIXA 
};

enum{ //Enum das Classificações.
    TENSAO = 1,
    CORRENTE,
    OLEO
};

typedef struct Data_t
{
    int Dia;
    int Mes;
    int Ano;
}Data_t;




