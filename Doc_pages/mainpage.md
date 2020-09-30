@mainpage Sistema de cadastro e manipulação de alarmes relacionados a equipamentos

# Resumo

Sistema que tem como objetivo a manipulação e cadastro de alarmes relacionados a equipamentos, foi desenvolvido utilizando dois arquivos do tipo .tsv que podem ser abertos como tabela.
Esses dois arquivos são manipulados para a inserção/remoção/atualização/pesquisa de elementos como alarmes e equipamentos.

O sistema foi desenvolvido com essas características com o intuito de economizar memoria, para assim não ser necessário armazenar todos os dados em listas encadeadas na memória durante a execução do sistema e só armazenar os dados ao fim da execução.

O sistema possui 5 arquivos:

1. **Sistema.c**: Arquivo contendo a função main e todos os includes.
2. **Sistema.h**: Arquivo contendo as definições e tipos de dados utilizados no sistema.
3. **Interface.h**: Arquivo contendo as funções de interface e suas funções auxiliares.
4. **Equipamento.h**: Arquivo contendo o tipo de dado Equipamento_t, suas funções de CRUD as suas funções auxiliares.
5. **Alarme.h**: Arquivo contendo o tipo de dado Alarme_t, as suas funções de CRUD e suas funções auxiliares.

