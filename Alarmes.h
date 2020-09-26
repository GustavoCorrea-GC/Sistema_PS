

typedef struct {            //Tipo de dado Alarme_t
    char Nome[128];
    int Classificacao;
    int N_Serie_Equi;
    int Num_Ativo;
    int Data;
    char Descricao[256];
    struct Alarmes_t *proximo;
    
} Alarme_t;




