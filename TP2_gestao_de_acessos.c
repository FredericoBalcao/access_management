/*
 *  ESTGP/IPPortalegre
 *  Engenharia Informática
 *  Introdução à Programação 2013/2014 - Trabalho 2 - Gestão de Acessos
 *
 *  Aluno: 15307 - Frederico Balcão
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXREC 30 /*maximo de recursos*/
#define MAXPESSOAS 250 /*maximo de pessoas*/
#define MAXGRUPOS 20 /*maximo de grupos*/
#define MAXAUT 20 /*maximo de autorizacoes*/
#define MAXDES 1000 /*maximo da descrição*/
#define MAXNOME 50 /*maximo de nomes*/
#define MAXASSOCIADOS 20 /*maximo de associados*/
#define MAXPERMISSOES 40 /*maximo de permissoes*/


/*Estruturas do programa*/
struct recursos{
  char nome[MAXNOME];
  float id;
  int lotacao;
  char observacoes[MAXDES];
  int responsavel;
};

struct pessoal{
  int id;
  char nome[MAXNOME];
  int tipo;    // 1 - Aluno, 2 - docente e 3 - funcionario
};

struct grupos_acesso{
  int id;
  char nome[MAXNOME];
  int nr_associados;
  int associados[MAXASSOCIADOS]; // ids do pessoal associado ao grupo
};

struct disciplinas{
  char nome[MAXNOME];
  char curso[MAXNOME];
  int ano_curricular, semestre, ano_lectivo, nr_associados;
  int alunos[MAXASSOCIADOS]; // ids dos alunos associado ao grupo
};

struct grupos_discp{
  char nome[MAXNOME];
  int nr_associados;
  int docentes[MAXASSOCIADOS]; // ids dos docentes associado ao grupo
};

struct areas_trab{
  char nome[MAXNOME];
  int nr_associados;
  int funcionarios[MAXASSOCIADOS]; // ids dos funcionarios associado ao grupo
};

struct data{
    int dia, mes, ano; //variaveis para a estrutura da data validada
};

struct autorizacao{
  int id;                          // ID da autorizacao
  float id_recurso;                  // ID do recurso a que se refere a autorização
  char descricao[MAXDES];          // texto com descricao
  int id_responsavel;              // ID do responsavel
  int nr_associados;
  int associados_pessoas[MAXASSOCIADOS];   // IDS do pessoal autorizado
  int associados_grupos[MAXASSOCIADOS]; //IDS dos grupos autorizados
  struct data data_inicio, data_fim; //data de inicio e fim para listar autorizacoes entre datas
};

/*coloquei typedef para simplificar as variaveis das estruturas, onde as letras maiusculas são os novos nomes dos tipos de estruturas*/
typedef struct recursos R;
typedef struct pessoal P;
typedef struct grupos_acesso G_A;
typedef struct disciplinas D;
typedef struct grupos_discp G_D;
typedef struct areas_trab A_T;
typedef struct autorizacao A;

R recursos[MAXREC];
P pessoal[MAXPESSOAS];
G_A grupos[MAXGRUPOS];
D discp[MAXGRUPOS];
G_D grp_discp[MAXGRUPOS];
A_T area_trab[MAXGRUPOS];
A aut[MAXAUT];

//variaveis globais
int nr_recursos=0,nr_pessoal=0,nr_grupos=0,nr_discp=0,nr_grp_discp=0,nr_area_trab=0,nr_aut=0, nr_associados=0;
int i,existe=0, existe2=0, id, j, aux, n, k, w, valor=0, dia=0, mes=0, ano=0, dia_f=0, mes_f=0, ano_f=0;
float id_recurso_info; //variavel a ser procurada no array dos recursos para ver se existe algum igual
int opcao=0,opcao2=0,opcao3=0;
char nome[MAXNOME];
char grupo[MAXNOME];

/*Funções para pessoas*/
void inserir_pessoas(){
     if(nr_pessoal == MAXPESSOAS){ // A estrutura ja atingiu maximo de pessoas
        printf("Ja nao pode inserir mais pessoas!!\n\n");
    }else{

        do{
            printf("\nNome da pessoa: ");
            scanf(" ");
            gets(pessoal[nr_pessoal].nome);

            for(i=0; i<nr_pessoal; i++){ // ver se o id ja esta a ser usado...
                if(strcmp(pessoal[nr_pessoal].nome, pessoal[i].nome) == 0){// se ja for usado
                    existe=1;
                    printf("Nome ja usado!! Tente outro nome!!\n\n");
                }else{
                    existe=0;
                }
            }
        }while(existe==1);

        do{
            printf("\nNumero de Identificacao (ID): ");
            scanf("%d", &(pessoal[nr_pessoal].id));// id

            for(i=0; i<nr_pessoal; i++){ // ver se o id ja esta a ser usado...
                if(pessoal[nr_pessoal].id == pessoal[i].id){// se ja for usado
                    existe=1;
                    printf("Numero ja usado!! Tente outro!!\n\n");
                }else{
                    existe=0;
                }
            }
        }while(existe==1);


        printf("\nTipo de Pessoa: \n");
        printf("1-> Aluno\n");
        printf("2-> Docente\n");
        printf("3-> Funcionario\n");
        printf("Tipo: ");
        scanf("%d", &(pessoal[nr_pessoal].tipo));// tipo (1 - Aluno, 2 - docente e 3 - funcioinario)

       while(pessoal[nr_pessoal].tipo>3 || pessoal[nr_pessoal].tipo<1){ // ver se tipo e valido
            printf("\nTipo invalido!!\n");
            printf("\nTipo de Pessoa: ");
            scanf("%d", &(pessoal[nr_pessoal].tipo));// tipo (1 - Aluno, 2 - docente e 3 - funcioinario)
        }

        printf("\n\n--------- PESSOA INSERIDA COM SUCESSO!!! ---------\n\n");
        nr_pessoal++; //incrementa mais uma pessoa inserida
}
system("pause");
system("cls");
}

void listar_pessoas_tipo(){
        if(nr_pessoal==0){
            printf("\nNao existem pessoas inseridas!!\n\n");
        }else{
            printf("Listagem de Pessoas por tipo: \n");
            printf("1-> Alunos\n");
            printf("2-> Docentes\n");
            printf("3-> Funcionarios\n\n");
            printf("Tipo de pessoa que deseja listar: "); //verifica a pessoa a ser listada pelo id
            scanf("%d", &id);

        while(id>3 || id<1){ // ver se tipo e valido
            printf("\nTipo invalido!! Tente novamente!!\n");
            printf("\nTipo de pessoa que deseja listar: ");
            scanf("%d", &id);// tipo (1 - Aluno, 2 - docente e 3 - funcioinario)
        }
        existe=0;
        for(i=0; i<nr_pessoal; i++){
            if(pessoal[i].tipo == id){
                existe=1;
                printf("\n------------ LISTAGEM DE PESSOAS INSERIDAS PELO TIPO %d -----------\n", id);
                printf("\nNome: %s\n\n", pessoal[i].nome);
                printf("\nNumero de Identificacao (ID): %d\n", pessoal[i].id);
                printf("\n-------------------------------------------------------------------\n");
            }
        }
        if(existe==0){
                system("cls");
                printf("\nNao existe ninguem inserido pelo tipo %d \n\n", id);
        }
        }
system("pause");
system("cls");
}

void listar_todas_pessoas(){
    if(nr_pessoal == 0){
        printf("Nao ha pessoas inseridas!!!\n");
    }else{
        printf("\n------------ LISTAGEM DE PESSOAS INSERIDAS -----------\n");
        for(i=0; i<nr_pessoal; i++){ // imprimir um a um
            printf("\nNome: %s\n\n",pessoal[i].nome);
            printf("\nNumero de Identificacao (ID): %d\n",pessoal[i].id);
            printf("\nTipo de Pessoa: %d\n", pessoal[i].tipo);
            printf("\n--------------------------------------------------\n");
        }
    }
    system("pause");
    system("cls");
}

void apagar_pessoas(){
        if(nr_pessoal==0){
            printf("\nNao existem pessoas inseridas!!\n\n");
        }else {
        printf("Numero de identificacao (ID) da pessoa que quer apagar: ");
        scanf("%d", &id);
        existe=0;
        for(i=0; i<nr_pessoal; i++){
            if(pessoal[i].id == id){ // Quando for igual, todos os elementos seguintes vai andar uma casa
                existe=1;
                nr_pessoal--;
                pessoal[i].id=pessoal[nr_pessoal].id;
                pessoal[i].tipo=pessoal[nr_pessoal].tipo;
                strcpy(pessoal[i].nome,pessoal[nr_pessoal].nome);
                printf("\n\n--------- PESSOA COM O ID %d APAGADA COM SUCESSO!!! ---------\n\n", id);
            }
        }
        if(existe==0){
            system("cls");
            printf("\nNao existe nenhuma pessoa com esse ID!!!");
        }
        }
system("pause");
system("cls");
}

/*Funções para grupos*/
void inserir_grupos(){
    printf("Inserir grupos:\n\n");
    printf("1-> Grupos de acesso\n");
    printf("2-> Disciplinas\n");
    printf("3-> Grupos disciplinares\n");
    printf("4-> Areas de trabalho\n\n");
    printf("Opcao: ");
    scanf("%d", &opcao3);

    while(opcao3>4||opcao3<1){
        printf("\nOpcao Invalida!!\n");
        printf("\nOpcao: ");
        scanf("%d", &opcao3);
    }
    system("cls");

    switch(opcao3){
        case 1: // Grupos de acesso
        if(nr_grupos == MAXGRUPOS){ // A estrutura ja atingiu maximo de grupos
            printf("Ja nao pode inserir mais grupos!!\n\n");
        }else{

        do{
            printf("\nNome do Grupo: ");
            scanf(" ");
            gets(grupos[nr_grupos].nome);

            for(i=0; i<nr_grupos; i++){ // ver se o nome ja esta a ser usado...
                    if(strcmp(grupos[nr_grupos].nome, grupos[i].nome) == 0){// se ja for usado
                        existe=1;
                        printf("\nNome de grupo ja usado!!!\n\n");
                    }else{
                        existe=0;
                    }
            }
        }while(existe==1);

        do{
            printf("\nNumero de Identificacao (ID) do grupo: ");
            scanf("%d", &(grupos[nr_grupos].id));// id

            for(i=0; i<nr_grupos; i++){ // ver se o id ja esta a ser usado...
                    if(grupos[nr_grupos].id == grupos[i].id){// se ja for usado
                        existe=1;
                        printf("\nNumero de identificao de grupo ja usado!!\n\n");
                    }else{
                        existe=0;
                    }
            }
        }while(existe==1);

        grupos[nr_grupos].nr_associados=0;
        nr_grupos++;
        printf("\n\n--------- GRUPO DE ACESSO INSERIDO COM SUCESSO!!! ---------\n\n");
        }
        system("pause");
        system("cls");
        break;

        case 2: // Disciplinas
            if(nr_discp == MAXGRUPOS){ // A estrutura ja atingiu maximo de disciplinas
                printf("Ja nao pode inserir mais disciplinas!!\n");
            }else{
                existe=0;
                do{
                    printf("\nDesignacao da Disciplina: ");
                    scanf(" ");
                    gets(discp[nr_discp].nome);

                    for(i=0; i<nr_discp; i++){ // ver se a disciplina ja esta a ser usada...
                        if(strcmp(discp[nr_discp].nome, discp[i].nome) == 0){// se ja for usada
                            existe=1;
                            printf("\nNome de disciplina ja usado!!\n\n");
                        }else{
                            existe=0;
                        }
                    }
                }while(existe==1);

        printf("\nCurso: ");
        scanf(" ");
        gets(discp[nr_discp].curso);

        printf("\nAno Curricular: ");
        scanf("%d", &(discp[nr_discp].ano_curricular));

        printf("\nSemestre (1 ou 2): ");
        scanf("%d", &(discp[nr_discp].semestre));

         while(discp[nr_discp].semestre>2 || discp[nr_discp].semestre<1){
            printf("\nSemestre Invalido!! So existem 2 semestres!!\n");
            printf("\nTem que indicar 1 ou 2!!\n\n");
            printf("\nSemestre (1 ou 2): ");
            scanf("%d", &(discp[nr_discp].semestre));
        }

        printf("\nAno Lectivo: ");
        scanf("%d", &(discp[nr_discp].ano_lectivo));

        discp[nr_discp].nr_associados=0;
        nr_discp++;
        printf("\n\n--------- DISCIPLINA INSERIDA COM SUCESSO!!! ---------\n\n");
        }
        system("pause");
        system("cls");
        break;

        case 3: // Grupos disciplinares
                if(nr_grp_discp == MAXGRUPOS){ // A estrutura ja atingiu maximo de grupos
                    printf("Ja nao pode inserir mais grupos disciplinares!!\n");
                }else{
                    existe=0;
                    do{
                        printf("\nNome do Grupo Disciplinar: ");
                        scanf(" ");
                        gets(grp_discp[nr_grp_discp].nome);

                        for(i=0; i<nr_grp_discp; i++){ // ver se ja esta a ser usado...
                            if(strcmp(grp_discp[nr_grp_discp].nome, grp_discp[i].nome) == 0){ // se ja for usado
                                existe=1;
                                printf("Nome de grupo disciplinar ja usado!!\n");
                            }else{
                                existe=0;
                            }
                        }
                    }while(existe==1);
                grp_discp[nr_grp_discp].nr_associados=0;
                nr_grp_discp++;
                printf("\n\n--------- GRUPO DISCIPLINAR INSERIDO COM SUCESSO!!! ---------\n\n");
                }
                system("pause");
                system("cls");
                break;
                case 4: // áreas de trabalho
                   if(nr_area_trab == MAXGRUPOS){ // A estrutura ja atingiu maximo de grupos
                    printf("Ja nao pode inserir mais areas de trabalho!!\n");
                    }else{
                        existe=0;
                        do{
                        printf("\nNome da Area de Trabalho: ");
                        scanf(" ");
                        gets(area_trab[nr_area_trab].nome);

                        for(i=0; i<nr_area_trab; i++){ // ver se ja esta a ser usado...
                            if(strcmp(area_trab[nr_area_trab].nome, area_trab[i].nome) == 0){ // se ja for usado
                                existe=1;
                                printf("Nome da area de trabalho ja usado!!\n");
                            }else{
                                existe=0;
                            }
                        }
                        }while(existe==1);
                        area_trab[nr_area_trab].nr_associados=0;
                        nr_area_trab++;
                        printf("\n\n--------- AREA DE TRABALHO INSERIDA COM SUCESSO!!! ---------\n\n");
                        }
                        system("pause");
                        system("cls");
                        break;
    }
}

void listar_pessoas_grupos(){
    printf("Listar pessoas de um grupo\n");
    printf("1-> Grupos de acesso\n");
    printf("2-> Disciplinas\n");
    printf("3-> Grupos disciplinares\n");
    printf("4-> Areas de trabalho\n\n");
    printf("Opcao: ");
    scanf("%d",&opcao3);

    while(opcao3>4||opcao3<1){
        printf("Digite opcao valida!!\n");
        printf("\nOpcao: ");
        scanf("%d", &opcao3);
    }
    system("cls");

    switch(opcao3){
        case 1: // Grupos de acesso
            if(nr_grupos==0){ // A estrutura esta vazia
                printf("Nao ha grupos!!\n");
            }else{
                printf("\nNumero de identificacao (ID) do grupo a listar: ");
                scanf("%d", &id);
                for(i=0; i<nr_grupos; i++){
                    if(grupos[i].id == id){
                        existe=1;
                        printf("\n------------ LISTAGEM DE GRUPOS DE ACESSO -----------\n");
                        printf("Nome             : %s\n", grupos[i].nome);
                        printf("Nr de associados : %d\n", grupos[i].nr_associados);
                        printf("\n---------------- Pessoal Associado ------------------\n");
                        for(j=0; j<grupos[i].nr_associados; j++){
                            existe=1;
                            printf("Numeros de identificacao associados: \n");
                            printf("-> %d\n", grupos[i].associados[j]);
                        }
                    }
                }
                if(existe==0){
                    system("cls");
                    printf("\nNao existe nenhum grupo de acesso com esse ID!!\n\n");
                }
            }
        system("pause");
        system("cls");
        break;
        case 2: // Disciplinas
            if(nr_discp==0){ // A estrutura esta vazia
                printf("Nao ha  disciplinas!!\n");
            }else{
                printf("Nome da disciplina: ");
                scanf(" ");
                gets(grupo);
                existe=0;
                for(i=0; i<nr_discp; i++){
                    if(strcmp(discp[i].nome, grupo) == 0){
                        existe=1;
                        printf("\n------------ LISTAGEM DE DISCIPLINAS -----------\n");
                        printf("Curso            : %s\n", discp[i].curso);
                        printf("Ano              : %d\n", discp[i].ano_curricular);
                        printf("Semestre         : %d\n", discp[i].semestre);
                        printf("Ano lectivo      : %d\n", discp[i].ano_lectivo);
                        printf("Nr de associados : %d\n", discp[i].nr_associados);
                        printf("\n---------------- Alunos Associados -------------\n");
                        for(j=0; j<grupos[i].nr_associados; j++){
                            existe=1;
                            printf("Numeros de identificacao associados: \n");
                            printf("-> %d\n", discp[i].alunos[j]);
                        }
                    }
                }
                if(existe==0){
                    system("cls");
                    printf("\nNao existe nenhuma disciplina com esse nome!!\n\n");
                }
            }
        system("pause");
        system("cls");
        break;
        case 3: // Grupos disciplinares
            if(nr_grp_discp==0){ // A estrutura esta vazia
                printf("Nao ha grupos!!\n");
            }else{
                printf("Nome do grupo disciplinar: ");
                scanf(" ");
                gets(grupo);
                existe=0;
                for(i=0; i<nr_grp_discp; i++){
                    if(strcmp(grp_discp[i].nome, grupo) == 0){
                        existe=1;
                        printf("\n------------ LISTAGEM DE GRUPOS DISCIPLINARES -----------\n");
                        printf("Nr de associados : %d\n", grp_discp[i].nr_associados);
                        printf("\n---------------- Docentes Associados --------------------\n");
                        for(j=0; j<grupos[i].nr_associados; j++){
                            existe=1;
                            printf("Numeros de identificacao associados: \n");
                            printf("-> %d\n", grp_discp[i].docentes[j]);
                        }
                    }
                }
                if(existe==0){
                    system("cls");
                    printf("\nNao existe nenhum grupo disciplinar com esse nome!!\n\n");
                }
            }
            system("pause");
            system("cls");
            break;

            case 4: // áreas de trabalho
                if(nr_area_trab==0){ // A estrutura esta vazia
                    printf("Nao ha areas de trabalho!!\n");
                }else{
                    printf("Nome da Area de Trabalho: ");
                    scanf(" ");
                    gets(grupo);
                    existe=0;
                    for(i=0; i<nr_area_trab; i++){
                        if(strcmp(area_trab[i].nome,grupo) == 0){
                            existe=1;
                            printf("\n------------ LISTAGEM DE AREAS DE TRABALHO -----------\n");
                            printf("Nr de associados : %d\n", area_trab[i].nr_associados);
                            printf("\n---------------- Funcionarios Associados -------------\n");
                            for(j=0; j<grupos[i].nr_associados; j++){
                                existe=1;
                                for(k=0; k<area_trab[i].funcionarios; k++){
                                printf("Numeros de identificacao associados: \n");
                                printf("-> %d\n", area_trab[i].funcionarios[j]);
                            }
                        }
                    }
                    }
                    if(existe==0){
                        system("cls");
                        printf("\nNao existe nenhuma area de trabalho com esse nome!!\n\n");
                    }
                }
            system("pause");
            system("cls");
    }
}


void apagar_grupos(){
    printf("Apagar grupos: \n");
    printf("1-> Grupos de acesso\n");
    printf("2-> Disciplinas\n");
    printf("3-> Grupos disciplinares\n");
    printf("4-> Areas de trabalho\n\n");
    printf("Opcao: ");
    scanf("%d",&opcao3);

    while(opcao3>4||opcao3<1){
        printf("Opcao Invalida!!!\n");
        printf("Opcao: ");
        scanf("%d", &opcao3);
    }
    system("cls");

    switch(opcao3){
        case 1: // Grupos de acesso
            if(nr_grupos==0){ // A estrutura esta vazia
                printf("Nao ha grupos!!\n");
            }else{
                existe=0;
                printf("\nNumero de identificacao (ID) do grupo a apagar: ");
                scanf("%d", &id);
                for(i=0; i<nr_grupos; i++){
                    if(grupos[i].id == id){ // Quando for igual, todos os elementos seguintes vai andar uma casa
                        existe=1;
                        for(i=0; i<nr_grupos; i++){
                            nr_grupos--;
                            strcpy(grupos[i].nome, grupos[nr_grupos].nome);
                            grupos[i].id=grupos[nr_grupos].id;
                            grupos[i].nr_associados = grupos[nr_grupos].nr_associados;
                            for(j=0; j<grupos[i].nr_associados; j++){ // preciso de um ciclo para passar todos os elementos associados...
                                existe=1;
                                grupos[i].associados[j]=grupos[nr_grupos].associados[j];
                            }
                        }
                    }
                    printf("\n\n--------- GRUPO DE ACESSO APAGADO COM SUCESSO!!! ---------\n\n");
                }
                if(existe==0){
                    system("cls");
                    printf("\nNao existe nenhum grupo com esse ID!!\n\n");
                }
            }
            system("pause");
            system("cls");
            break;

                case 2: // Disciplinas
                    if(nr_discp==0){ // A estrutura esta vazia
                        printf("\nNao ha disciplinas!!\n");
                    }else{
                        printf("\nNome da disciplina a apagar: ");
                        scanf(" ");
                        gets(grupo);
                        existe=0;
                        for(i=0; i<nr_discp; i++){
                            if(strcmp(discp[i].nome, grupo) == 0){ // Quando for igual, todos os elementos seguintes vai andar uma casa
                                existe=1;
                                for(i=0; i<nr_discp; i++){
                                    nr_discp--;
                                    strcpy(discp[i].nome,discp[nr_discp].nome);
                                    strcpy(discp[i].curso,discp[nr_discp].curso);
                                    discp[i].ano_curricular=discp[nr_discp].ano_curricular;
                                    discp[i].ano_lectivo=discp[nr_discp].ano_lectivo;
                                    discp[i].semestre=discp[nr_discp].semestre;
                                    discp[i].nr_associados=discp[nr_discp].nr_associados;
                                   for(j=0; j<discp[i].nr_associados; i++){
                                        existe=1;
                                        discp[i].alunos[j]=discp[nr_discp].alunos[j];
                                    }
                                }
                            }
                            printf("\n\n--------- DISCIPLINA APAGADA COM SUCESSO!!! ---------\n\n");
                        }
                        if(existe==0){
                            system("cls");
                            printf("\nNao existe nenhuma disciplina com esse nome!!!\n\n");
                        }
                    }
                    system("pause");
                    system("cls");
                    break;
                    case 3: // Grupos disciplinares
                        if(nr_grp_discp==0){ // A estrutura esta vazia
                            printf("Nao ha grupos disciplinares!!\n");
                        }else{
                            existe=0;
                            printf("Nome do grupo disciplinar a apagar: ");
                            scanf(" ",grupo);
                            gets(grupo);

                            for(i=0; i<nr_grp_discp; i++){
                                if(strcmp(grp_discp[i].nome, grupo) == 0){ // Quando for igual, todos os elementos seguintes vai andar uma casa
                                   existe=1;
                                   for(i=0; i<nr_grp_discp; i++){
                                        nr_grp_discp--;
                                        strcpy(grp_discp[i].nome,grp_discp[nr_grp_discp].nome);
                                        grp_discp[i].nr_associados=grp_discp[nr_grp_discp].nr_associados;
                                        for(j=0; j<grp_discp[i].nr_associados; j++){
                                            existe=1;
                                            grp_discp[i].docentes[j]=grp_discp[nr_grp_discp].docentes[j];
                                        }
                                    }
                                }
                                printf("\n\n--------- GRUPO DISCIPLINAR APAGADO COM SUCESSO!!! ---------\n\n");
                            }
                            if(existe==0){
                                system("cls");
                                printf("\nNao existe nenhum grupo disciplinar com esse nome!!!\n\n");
                            }
                        }
                        system("pause");
                        system("cls");
                        break;
                        case 4: // áreas de trabalho
                            if(nr_area_trab==0){ // A estrutura esta vazia
                                printf("Nao ha areas de trabalho!!\n");
                                }else{
                                    printf("Nome da area de trabalho a apagar: ");
                                    scanf(" ", grupo);
                                    gets(grupo);
                                    existe=0;
                                    for(i=0; i<nr_area_trab; i++){
                                        if(strcmp(area_trab[i].nome, grupo) == 0){ // Quando for igual, todos os elementos seguintes vai andar uma casa
                                            existe=1;
                                            for(i=0; i<nr_area_trab; i++){
                                                nr_area_trab--;
                                                strcpy(area_trab[i].nome,area_trab[nr_area_trab].nome);
                                                area_trab[i].nr_associados=area_trab[nr_area_trab].nr_associados;
                                                for(j=0; j<area_trab[i].nr_associados; j++){
                                                    existe=1;
                                                    area_trab[i].funcionarios[j]=area_trab[nr_area_trab].funcionarios[j];
                                                }
                                            }
                                        }
                                        printf("\n\n--------- AREA DE TRABALHO APAGADA COM SUCESSO!!! ---------\n\n");
                                    }
                                    if(existe==0){
                                        system("cls");
                                        printf("\nNao existe nenhuma area de trabalho com esse nome!!!\n\n");
                                    }
                                }
                                system("pause");
                                system("cls");
                                break;
    }
}

/*Associar Pessoas a Grupos*/
void associar_pessoas_grupos(){
    printf("Associar pessoas a grupos:\n");
    printf("1-> Associar pessoa a um grupo de acesso\n");
    printf("2-> Associar pessoa a uma disciplina\n");
    printf("3-> Associar pessoa a um grupo disciplinar\n");
    printf("4-> Associar pessoa a uma area de trabalho\n\n");
    printf("Opcao: ");
    scanf("%d",&opcao3);

    while(opcao3>4||opcao3<1){
        printf("Opcao Invalida!!\n");
        printf("Opcao: ");
        scanf("%d",&opcao3);
    }

    system("cls");

    switch(opcao3){
        case 1: // Associar pessoa a um grupo de acesso
            if(nr_grupos==0){ // A estrutura esta vazia
                printf("Nao tem grupos!!!\n");
            }else{
            // pedir grupo
            existe=0;

            while(existe != 1){
                printf("\nNome do grupo: ");
                scanf(" ");
                gets(grupo);

            for(i=0; i<nr_grupos; i++){
                if(existe == 0){
                    if(strcmp(grupos[i].nome, grupo)== 0){ // se tiver o ID no pessoal e valido
                        existe=1; // ponho a variavel existe a 1
                        printf("\nNumero de identificacao (ID) da pessoa: ");
                        scanf("%d", &(grupos[i].associados[grupos[i].nr_associados]));

                        // ver se ID e valido, e se nao for, pedir um valido
                        existe=-1;
                    while(existe == -1){

                    for(j=0; j<nr_pessoal; j++){
                        if(pessoal[i].id == grupos[i].associados[grupos[i].nr_associados])
                            existe=1;
                    }
                    if(existe == -1){
                        printf("Numero de identificacao (ID) invalido\n");
                        printf("Tente novamente!!\n\n");
                        printf("Numero de identificacao (ID) da pessoa: ");
                        scanf("%d", &(grupos[i].associados[grupos[i].nr_associados]));
                    }
                    }
                    grupos[i].nr_associados++;
                }
                }
            }
            printf("\n\n--------- PESSOA ASSOCIADA A UM GRUPO DE ACESSO COM SUCESSO!!! ---------\n\n");
            }
            if(existe==0)  // se for zero e porque o ID e invalido
                printf("\nNome de grupo invalido!!\n");
            }
            break;

            case 2: // Associar pessoa a disciplina
                if(nr_discp==MAXGRUPOS){ // A estrutura esta vazia
                    printf("Nao tem disciplinas!!\n");
                }else{
                    existe=0;

                while(existe != 1){
                    printf("\nNome da disciplina: ");
                    scanf(" ");
                    gets(grupo);

               for(i=0; i<nr_discp; i++){
                    while(existe == 0){
                        if(strcmp(discp[i].nome, grupo)== 0){ // se tiver o ID no pessoal e valido
                            existe=1; // ponho a variavel existe a 1
                            printf("\nNumero de identificacao (ID) da pessoa:");
                            scanf("%d",&(discp[i].alunos[discp[i].nr_associados]));
                            // ver se ID e valido, e se n for pedir um valido
                            existe=-1;
                    while(existe == -1){
                       for(j=0; j<nr_pessoal; j++){
                            if(pessoal[i].id == discp[i].alunos[discp[i].nr_associados])
                                existe=1;
                        }
                        if(existe == -1){
                            printf("Numero de identificacao (ID) invalido\n");
                            printf("Tente novamente!!\n\n");
                            printf("Numero de identificacao (ID) da pessoa: ");
                            scanf("%d", &(discp[i].alunos[discp[i].nr_associados]));
                        }
                    }
                    discp[i].nr_associados++;
                        }
                    }
                }
                printf("\n\n--------- PESSOA ASSOCIADA A UMA DISCIPLINA COM SUCESSO!!! ---------\n\n");
                }
                if(existe==0)  // se for zero e pk o ID e invalido
                    printf("Nome da disciplina invalida!!\n");
                }
                break;

                case 3: // Associar pessoa a um Grupo disciplinar
                    if(nr_grp_discp==0){ // A estrutura esta vazia
                        printf("Nao tem grupos!!\n");
                    }else{
                    existe=0;

                    while(existe != 1){
                        printf("\nNome do grupo disciplinar: ");
                        scanf(" ");
                        gets(grupo);

                    for(i=0; i<nr_grp_discp; i++){
                            if(existe == 0){
                                if(strcmp(grp_discp[i].nome, grupo)== 0){ // se tiver o ID no pessoal e valido
                                existe=1; // ponho a variavel existe a 1
                                printf("\nNumero de identificacao (ID) da pessoa:");
                                scanf("%d", &(grp_discp[i].docentes[grp_discp[i].nr_associados]));
                                // ver se ID e valido, e se n for pedir um valido
                                existe=-1;
                    while(existe == -1){
                        for(j=0; j<nr_pessoal; i++){
                            if(pessoal[i].id == grp_discp[i].docentes[grp_discp[i].nr_associados])
                                existe=1;
                    }
                    if(existe == -1){
                        printf("Numero de identificacao (ID) invalido\n");
                        printf("Tente novamente!!\n\n");
                        printf("Numero de identificacao (ID) da pessoa: ");
                        scanf("%d",&(grp_discp[i].docentes[grp_discp[i].nr_associados]));
                    }
                    }
                    grp_discp[i].nr_associados++;
                            }
                            }
                    }
                    printf("\n\n--------- PESSOA ASSOCIADA UM GRUPO DISCIPLINAR COM SUCESSO!!! ---------\n\n");
                    }
                    if(existe==0)  // se for zero e porque o ID e invalido
                        printf("Nome de grupo disciplinar invalido!!\n");
                    }
                    break;

                    case 4: // Associar pessoa a uma área de trabalho
                        if(nr_area_trab==0){ // A estrutura esta vazia
                            printf("Nao tem areas de trabalho!!\n");
                        }else{
                        existe=0;

                        while(existe != 1){
                            printf("\nNome dda area de trabalho: ");
                            scanf(" ");
                            gets(grupo);

                        for(i=0; i<nr_area_trab; i++){
                                if(existe == 0){
                                    if(strcmp(area_trab[i].nome,grupo)== 0){ // se tiver o ID no pessoal e valido
                                    existe=1; // ponho a variavel existe a 1
                                    printf("\nNumero de identificacao (ID) da pessoa:");
                                    scanf("%d", &(area_trab[i].funcionarios[area_trab[i].nr_associados]));
                                    // ver se ID e valido, e se n for pedir um valido
                                    existe=-1;
                                while(existe == -1){
                                 for(j=0; j<nr_pessoal; j++){
                                        if(pessoal[i].id == area_trab[i].funcionarios[area_trab[i].nr_associados])
                                            existe=1;
                                        }
                                        if(existe==-1){
                                            printf("Numero de identificacao (ID) invalido\n");
                                            printf("Tente novamente!!\n\n");
                                            printf("Numero de identificacao (ID) da pessoa: ");
                                            scanf("%d",&(area_trab[i].funcionarios[area_trab[i].nr_associados]));
                                        }
                                }
                                area_trab[i].nr_associados++;
                                }
                                }
                        }
                        printf("\n\n--------- PESSOA ASSOCIADA UMA AREA DE TRABALHO COM SUCESSO!!! ---------\n\n");
                        if(existe==0)  // se for zero e porque o ID e invalido
                            printf("Nome de area de trabalho invalido!!\n");
                        }
                        }
                        break;
                }
system("pause");
system("cls");
}

/*Funções para recursos*/
void inserir_recursos(){
   if(nr_recursos == MAXREC){ // A estrutura ja atingiu maximo de pessoas
        printf("\nJa nao pode inserir mais recursos!!\n\n");
    }else{
        existe=0;
        do{
            printf("\nNome do recurso: ");
            scanf(" ");
            gets(recursos[nr_recursos].nome);

            for(i=0; i<nr_recursos; i++){ // ver se o id ja esta a ser usado...
                if(strcmp(recursos[nr_recursos].nome, recursos[i].nome) == 0){// se ja for usado
                    existe=1;
                    printf("\nNome de recurso ja usado!! Tente outro!!\n\n");
                }else{
                    existe=0;
                }
            }
        }while(existe==1);
        existe=0;
        do{
            printf("\nNumero de Identificacao (ID) do recurso: ");
            scanf("%f", &(recursos[nr_recursos].id));// id

            for(i=0; i<nr_recursos; i++){ // ver se o id ja esta a ser usado...
                if(recursos[nr_recursos].id == recursos[i].id){// se ja for usado
                    existe=1;
                    printf("\nNumero de identificacao (ID) ja usado!! Tente outro!!\n\n");
                }else{
                    existe=0;
                }
            }
        }while(existe==1);

        printf("\nLotacao: ");
        scanf("%d", &(recursos[nr_recursos].lotacao));

        printf("\nObservacoes: ");
        scanf(" ");
        gets(recursos[nr_recursos].observacoes);

        printf("\nTem Responsavel? (1-Sim e 0-Nao)"); // Tenho de saber se tem responsavel pois e opcional
        scanf("%d", &opcao3);

        while(opcao3>1 || opcao3<0){
            printf("\nTem responsavel? (1-Sim e 0-Nao)");
            scanf("%d", &opcao3);
        }

        if(opcao3 == 1){ // se tiver responsavel
                printf("\nResponsavel (o seu ID): ");
                scanf("%d", &(recursos[nr_recursos].responsavel)); // peço o ID do responsavel
                existe = 0;
                for(i=0; i<nr_pessoal; i++){ // procuro na lista do pessoal
                    if(pessoal[i].id == recursos[nr_recursos].responsavel){ // se tiver o ID no pessoal e valido
                        existe = 1;
                        printf("\n\n--------- RECURSO INSERIDO COM SUCESSO!!! ---------\n\n");
                    }
                }
                if(existe==0){
                printf("\n\n--------- RECURSO INSERIDO COM SUCESSO SEM RESPONSAVEL!!! ---------\n\n");
                }
        }
        nr_recursos++;
    }
    system("pause");
    system("cls");
}

void listar_recursos(){
     if(nr_recursos == 0){
        printf("Nao ha recursos!!!\n");// A estrutura esta vazia
    }else{
        printf("\n------------ LISTAGEM DE RECURSOS INSERIDOS -----------\n\n");
        for(i=0; i<nr_recursos; i++){ // imprimir um a um
            printf("Nome        : %s\n", recursos[i].nome);
            printf("Lotacao     : %d\n", recursos[i].lotacao);
            printf("Numero de identificacao (ID)          : %.2f\n", recursos[i].id);
            printf("Observacoes : %s\n", recursos[i].observacoes);
            printf("Responsavel (ID): %d\n", recursos[i].responsavel);
            printf("\n-----------------------------------------------------\n");
        }
    }
    system("pause");
    system("cls");
}

void apagar_recursos(){
     if(nr_recursos == 0){
            printf("\nNao existem recursos inseridos!!\n\n");
        }else{
            printf("Numero de identificacao (ID) do recurso que quer apagar: ");
            scanf("%f", &id_recurso_info);
            existe=0;
            for(i=0; i<nr_recursos; i++){
                if(recursos[i].id == id_recurso_info){ // Quando for igual, todos os elementos seguintes vai andar uma casa
                    existe=1;
                    nr_recursos--;
                    recursos[i].id=recursos[nr_recursos].id;
                    recursos[i].lotacao=recursos[nr_recursos].lotacao;
                    strcpy(recursos[i].nome,recursos[nr_recursos].nome);
                    strcpy(recursos[i].observacoes,recursos[nr_recursos].observacoes);
                    recursos[i].responsavel=recursos[nr_recursos].responsavel;
                    printf("\n\n--------- RECURSO COM O ID %.2f APAGADO COM SUCESSO!!! ---------\n\n", id_recurso_info);
                }
            }
            if(existe==0){
                system("cls");
                printf("\nNao existe nenhum recurso com o ID %.2f !!\n\n", id_recurso_info);
            }
        }
system("pause");
system("cls");
}

void listar_info_recurso(){
      if(nr_recursos==0){
            printf("\nNao existem recursos inseridos!!\n\n");
        }else{
            printf("\nNumero de identificacao (ID) do recurso a listar: ");
            scanf("%f", &id_recurso_info);
            existe=0;
            for(i=0; i<nr_recursos; i++){
                if(recursos[i].id == id_recurso_info){
                    existe=1;
                    printf("\n------------ INFORMACACAO DO RECURSO %.2f -----------\n\n", id_recurso_info);
                    printf("Numero de identificacao (ID) do recurso : %.2f\n",recursos[i].id);
                    printf("Nome        : %s\n",recursos[i].nome);
                    printf("Lotacao     : %d\n",recursos[i].lotacao);
                    printf("Observacoes : %s\n",recursos[i].observacoes);
                    printf("Responsavel : %d\n",recursos[i].responsavel);
                    printf("\n--------------------------------------------\n");
                }
            }
            if(existe == 0){
                system("cls");
                printf("\nNao foi encontrado nenhum recurso com o ID %.2f !!\n\n", id_recurso_info);
            }
        }
system("pause");
system("cls");
}

/* Função que verifica a data para as autorizacoes */
int validar_data(int dia,int mes, int ano){
    int valor = 1;
    if(ano >= 2013 && ano <= 2014){ //ano opcional
        switch(mes){
            case 1: /*janeiro*/
            case 3: /*março*/
            case 5: /*maio*/
            case 7: /*julho*/
            case 8: /*agosto*/
            case 10: /*outubro*/
            case 12: /*dezembro*/
                if(dia < 1 || dia > 31){
                    valor = 0;
                    printf("\nDia invalido!!\n");
                    printf("O mes que indicou so tem 31 dias!!\n");
                }
                break;
            case 4: /*abril*/
            case 6: /*junho*/
            case 9: /*setembro*/
            case 11: /*novembro*/
                if(dia < 1 || dia > 30){
                    valor = 0;
                    printf("\nDia invalido!!\n");
                    printf("O mes que indicou so tem 30 dias!!\n");
                }
                break;
            case 2:
                if(ano % 100 == 0 && ano % 400 != 0){
                    if(dia < 1 || dia > 28){
                        valor = 0;
                        printf("\nDia invalido!!\n");
                        printf("O mes de Fevereiro so tem 28 dias!!\n");
                    }
                }else if(ano % 4 == 0){
                    if(dia < 1 || dia > 29){
                        valor = 0;
                        printf("\nDia invalido!!\n");
                        printf("O mes de Fevereiro so tem 29 dias!!\n");
                    }
                }else{
                    if(dia < 1 || dia > 28){
                        valor = 0;
                        printf("O mes de Fevereiro so tem 28 dias!!\n");
                    }
                }
                break;
            default:
                valor = 0;
                printf("\nMes invalido!!\n");
        }
    }else{
        valor = 0;
        printf("\nAno invalido!!\n");
        printf("Intervalo lectivo entre 2013-2014\n");
    }
    return valor;
}

/*Funções para autorizações*/
void inserir_autorizacoes(){
    if(nr_recursos==0){ // se nao ha recursos inseridos, nao posso inserir autorizacoes
            printf("\nNao tem recursos inseridos!!\n");
    }else{
        if(nr_aut == MAXAUT){ // A estrutura ja atingiu maximo de autorizacoes
            printf("\nJa nao pode inserir mais autorizacoes!!\n");
        }else{
            // ID da autorizacao
            existe=0;
            do{
                printf("\nNumero de identificacao (ID) da Autorizacao: ");
                scanf("%d", &(aut[nr_aut].id));
                for(i=0; i<nr_aut; i++){ // ver se ja esta a ser usado...
                    if(aut[nr_aut].id == aut[i].id ){ // se ja for usado
                        existe=1;
                        printf("\nJa existe uma autorizacao com esse numero de identificacao (ID)!!\n");
                        printf("\nTente novamente!!\n\n");
                    }else{
                        existe=0;
                    }
                }
            }while(existe==1);

            // ID do recurso a que se refere a autorização
            existe=0;
            do{
                printf("\nNumero de identificacao (recurso em causa): ");
                scanf("%f", &(aut[nr_aut].id_recurso));
                for(i=0; i<nr_recursos; i++){
                    if(recursos[i].id == aut[nr_aut].id_recurso){ // se tiver o ID do recurso e valido
                        existe=1;
                    }
                    if(existe=0){  // se for zero e porque o ID e invalido
                        printf("\nNao existe nenhum recurso com esse numero de identificacao (ID)!!\n");
                        printf("\nTente novamente!!\n\n");
                    }
                }
            }while(existe==1);

                // Data de inicio da autorizacao
                do{
                    printf("\n->Indique uma data de inicio(dd/mm/aa): ");
                    scanf("%d/%d/%d",&aut[nr_aut].data_inicio.dia,&aut[nr_aut].data_inicio.mes,&aut[nr_aut].data_inicio.ano);
                    valor = validar_data(aut[nr_aut].data_inicio.dia,aut[nr_aut].data_inicio.mes,aut[nr_aut].data_inicio.ano);
                }while(valor==0);

                // Data de fim da autorizacao
                do{
                    valor=1;
                    printf("\n->Indique uma data de fim(dd/mm/aa): ");
                    scanf("%d/%d/%d",&aut[nr_aut].data_fim.dia,&aut[nr_aut].data_fim.mes,&aut[nr_aut].data_fim.ano);
                    valor = validar_data(aut[nr_aut].data_fim.dia,aut[nr_aut].data_fim.mes,aut[nr_aut].data_fim.ano);
                }while(valor==0);

                // texto com descricao
                printf("\nDescricao: ");
                scanf(" ");
                gets(aut[nr_aut].descricao);

                // ID do responsavel
                do{
                    printf("\nResponsavel por essa autorizacao (numero de identificacao (ID)): ");
                    scanf("%d",&(aut[nr_aut].id_responsavel));
                    // procuro na lista do pessoal
                        for(i=0; i<nr_pessoal; i++){
                            if(pessoal[i].id == aut[nr_aut].id_responsavel){ // se tiver o ID no pessoal e valido
                                existe=1; // ponho a variavel existe a 1
                            }
                        }
                        if(existe==0){
                                printf("\nNao existe nenhuma pessoa com esse numero de identificacao (ID)!!\n");
                                printf("\nTente novamente!!\n\n");
                            }
                }while(existe==0);

                // IDS do pessoal autorizado
                printf("\nQuem pode aceder a esta autorizacao? \nPessoas e/ou Grupos pelo (ID)\n");
                printf("\nPara autorizar: \n");
                printf("1-> Grupos\n");
                printf("2-> Pessoas\n");
                printf("Opcao: ");
                scanf("%d", &opcao);
                switch(opcao){
                    case 1:
                        printf("\nIndique os numeros de identificacao dos grupos que quer autorizar\n");
                        printf("Insira '-1' quando terminar!\n");
                        for(i=0;i<MAXAUT;i++){
                            printf("\nNumeros de Identificacao: ");
                            scanf("%d", &(aut[nr_aut].associados_grupos[i]));
                            if(aut[nr_aut].associados_grupos[i] == -1 ){
                                aut[nr_aut].nr_associados=i;    // por exemplo i=3, 4º numero pedido, se o nr recebido for -1, sao 3 associados validos!!!!
                                i=MAXAUT;   // terminar ciclo for
                            }else{
                                // ver se ID e valido, e se n for pedir um valido
                                existe=-1;
                                while(existe==-1){
                                    j=0;
                                      while(j < nr_pessoal){
                                        if(grupos[i].id == aut[nr_aut].associados_grupos[i])
                                          existe=1;
                                        j++;
                                      }
                                      if(existe==-1){
                                        printf("ID invalido!\n");
                                        printf("Id da pessoa: ");
                                        scanf("%d", &(aut[nr_aut].associados_grupos[i]));
                                      }
                                }
                            }
                        }
                        nr_aut++;
                        break;
                        case 2:
                            printf("\nIndique os numeros de identificacao das pessoas que quer autorizar\n");
                            printf("Insira '-1' quando terminar!\n");
                            for(i=0;i<MAXAUT;i++){
                                printf("\nNumeros de Identificacao: ");
                                scanf("%d",&(aut[nr_aut].associados_pessoas[i]));
                                if( aut[nr_aut].associados_pessoas[i] == -1 ){
                                    aut[nr_aut].nr_associados=i;    // por exemplo i=3, 4º numero pedido, se o nr recebido for -1, sao 3 associados validos!!!!
                                    i=MAXAUT;   // terminar ciclo for
                                }else{
                                    // ver se ID e valido, e se n for pedir um valido
                                    existe=-1;
                                    while(existe==-1){
                                      j=0;
                                      while(j < nr_pessoal){
                                        if(pessoal[i].id == aut[nr_aut].associados_pessoas[i])
                                          existe=1;
                                        j++;
                                      }
                                      if(existe==-1){
                                        printf("ID invalido!\n");
                                        printf("Id da pessoa: ");
                                        scanf("%d", &(aut[nr_aut].associados_pessoas[i]));
                                      }
                                    }
                                  }
                            }
                             printf("\n\n--------- AUTORIZACAO INSERIDA COM SUCESSO!!! ---------\n\n");
                            nr_aut++;
                            break;
                            default:
                                printf("\nOpcao invalida!!\n\n");
                }
            }
    }
system("pause");
system("cls");
}

void apagar_autorizacoes(){
     if(nr_aut==0){
            printf("\nNao ha autorizacoes inseridas!!!\n");// A estrutura esta vazia
        }else{
    printf("Indique o numero de identificacao (ID) da autorizacao que quer apagar: ");
    scanf("%d", &id);

    existe=0;

    for(i=0; i<nr_aut; i++){
        if(aut[i].id == id){
            existe=1;
            nr_aut--;
            aut[i].id=aut[nr_aut].id;
            aut[i].id_recurso=aut[nr_aut].id_recurso;
            aut[i].id_responsavel=aut[nr_aut].id_responsavel;
            aut[i].nr_associados=aut[nr_aut].nr_associados;

            for(j=0; j<aut[i].nr_associados; j++){
                aut[i].associados_pessoas[j]=aut[nr_aut].associados_pessoas[j];
                aut[i].associados_grupos[j]=aut[nr_aut].associados_grupos[j];
            }
            aut[nr_aut].data_inicio.dia = 0;
            aut[nr_aut].data_inicio.mes = 0;
            aut[nr_aut].data_inicio.ano = 0;
            aut[nr_aut].data_fim.dia = 0;
            aut[nr_aut].data_fim.mes = 0;
            aut[nr_aut].data_fim.ano = 0;
            strcpy(aut[i].descricao, aut[nr_aut].descricao);
            printf("\n\n--------- AUTORIZACAO APAGADA COM SUCESSO!!! ---------\n\n");
        }
        }
    if(existe==0){
        system("cls");
        printf("\nNao existe nenhuma autorizacao com esse ID!!\n\n");
    }
        }
system("pause");
system("cls");
}

void listar_autorizacoes_por_datas(){
    if(nr_aut==0){
            printf("\nNao ha autorizacoes inseridas!!!\n");// A estrutura esta vazia
            system("pause");
            system("cls");
        }else{
            printf("Como pretende listar as autorizacoes?\n");
            printf("1-> Listar autorizacoes de uma pessoa\n");
            printf("2-> Listar autorizacoes de um grupo\n");
            printf("3-> Listar todas as autorizacoes por uma data\n");
            printf("Opcao: ");
            scanf("%d", &opcao);

            system("cls");
            switch(opcao){
                case 1:
                    printf("\nIndique o numero de identificacao (ID) da pessoa para listar a(s) sua(s) autorizacao(oes): ");
                    scanf("%d", &id);

                    for(i=0; i<nr_aut; i++){
                        for(j=0; j<aut[i].nr_associados; j++){
                            if(aut[i].associados_pessoas[j] == id){
                                printf("\n-------------------------------------\n");
                                printf("Autorizacao %d da pessoa com o numero de identificao %d: ", i, id);
                                printf("\n-------------------------------------\n");
                                printf("ID da autorizacao: %d\n", aut[i].id);
                                printf("ID do recurso autorizado: %f\n", aut[i].id_recurso);
                                printf("Data de inicio: %d/%d/%d\n",aut[i].data_inicio.dia,aut[i].data_inicio.mes,aut[i].data_inicio.ano);
                                printf("Data de fim: %d/%d/%d\n",aut[i].data_fim.dia,aut[i].data_fim.mes, aut[i].data_fim.ano);
                                printf("Descricao da autorizacao: %s\n", aut[i].descricao);
                                printf("ID responsavel dessa autorizacao: %d\n\n", aut[i].id_responsavel);
                            }
                        }
                    }
                    system("pause");
                    system("cls");
                    break;
                    case 2:
                        printf("Indique o numero de identificacao (ID) do grupo para listar a(s) sua(s) autorizacao(oes): ");
                        scanf("%d",&id);

                        for(i=0; i<nr_aut; i++){
                            for(j=0; j<aut[i].nr_associados; j++){
                                if(aut[i].associados_grupos[j] == id){
                                    printf("\n--------------------------------------\n");
                                    printf("Autorizacao %d do grupo com o numero de identificao %d: ", i, id);
                                    printf("\n--------------------------------------\n");
                                    printf("ID da autorizacao               : %d\n", aut[i].id);
                                    printf("ID do recurso autorizado       : %f\n", aut[i].id_recurso);
                                    printf("Data de inicio: %d/%d/%d\n",aut[i].data_inicio.dia,aut[i].data_inicio.mes,aut[i].data_inicio.ano);
                                    printf("Data de fim: %d/%d/%d\n",aut[i].data_fim.dia,aut[i].data_fim.mes, aut[i].data_fim.ano);
                                    printf("Descricao da autorizacao        : %s\n", aut[i].descricao);
                                    printf("ID responsavel dessa autorizacao   : %d\n\n", aut[i].id_responsavel);
                                }
                            }
                        }
                        break;
                        system("pause");
                        system("cls");
                        case 3:
                            printf("Indique uma data para ver todas as autorizacoes existentes\n");
                            printf("Por data de inicio ou por data de fim!!\n");
                            printf("\nData: ");
                            scanf("%d/%d/%d", &dia,&mes,&ano);

                            for (i=0; i<nr_aut; i++){
                                if((aut[i].data_inicio.dia==dia && aut[i].data_inicio.mes == mes && aut[i].data_inicio.ano == ano) ||
                                    (aut[i].data_fim.dia==dia && aut[i].data_fim.mes==mes && aut[i].data_fim.ano==ano)){
                                    existe=1;
                                    printf("Listagem de todas as autorizacoes existentes pela data %d/%d/%d : \n\n");
                                    printf("\n--------------------------------------\n");
                                    printf("Autorizacao %d: \n", i);
                                    printf("\n--------------------------------------\n");
                                    printf("ID da autorizacao               : %d\n", aut[i].id);
                                    printf("ID do recurso autorizado      : %f\n", aut[i].id_recurso);
                                    printf("Data de inicio: %d/%d/%d\n",aut[i].data_inicio.dia,aut[i].data_inicio.mes,aut[i].data_inicio.ano);
                                    printf("Data de fim: %d/%d/%d\n",aut[i].data_fim.dia,aut[i].data_fim.mes, aut[i].data_fim.ano);
                                    printf("Descricao da autorizacao        : %s\n", aut[i].descricao);
                                    printf("ID responsavel dessa autorizacao   : %d\n\n", aut[i].id_responsavel);
                                    }
                            }
                        system("pause");
                        system("cls");
                        break;
                        default:
                            printf("\nOpcao Invalida\n\n");
                            system("pause");
                            system("cls");
            }
        }
}

void listar_autorizacoes_entre_datas(){
       if(nr_aut==0){
            printf("\nNao ha autorizacoes inseridas!!!\n");// A estrutura esta vazia
        }else{
            do{
                printf("\nIntroduza a data de inicio da autorizacao que deseja listar \n");
                printf("\nData de Inicio: ");
                scanf("%d/%d/%d",&dia, &mes, &ano);
                valor = validar_data(dia,mes,ano);
            }while(valor==0);

             do{
                valor=1;
                printf("\nIntroduza a data de fim da autorizacao que deseja listar \n");
                printf("\nData de Fim: ");
                scanf("%d/%d/%d",&dia_f, &mes_f, &ano_f);
                valor = validar_data(dia_f,mes_f,ano_f);
            }while(valor==0);

            for(i=0; i<nr_aut; i++){
                 if(aut[i].data_inicio.dia>=dia && aut[i].data_inicio.mes>=mes && aut[i].data_inicio.ano>=ano){
                    if(aut[i].data_fim.dia<=dia_f && aut[i].data_fim.mes<=mes_f && aut[i].data_fim.ano<=ano_f){ // tem de ter estas duas condicoes satisfeitas para imprimir
                        printf("\n-----------------------------------\n");
                        printf("Autorizacao %d: \n", i);
                        printf("\n-----------------------------------\n");
                        printf("ID da autorizacao: %d\n",aut[i].id);
                        printf("ID recurso referente a dada autorizacao: %f\n",aut[i].id_recurso);
                        printf("Data de inicio: %d/%d/%d\n",aut[i].data_inicio.dia,aut[i].data_inicio.mes,aut[i].data_inicio.ano);
                        printf("Data de fim: %d/%d/%d\n",aut[i].data_fim.dia,aut[i].data_fim.mes, aut[i].data_fim.ano);
                        printf("Descricao da autorizacao: %s\n",aut[i].descricao);
                        printf("ID responsavel dessa autorizacao: %d\n\n",aut[i].id_responsavel);
                    }
                }
            }
        }
system("pause");
system("cls");
}

void apagar_autorizacao_anterior_data(){
    if(nr_aut==0){
            printf("\nNao ha autorizacoes inseridas!!!\n");// A estrutura esta vazia
        }else{
   printf("Indique a data para apagar todas as autorizacoes anteriores a esta: \n");
   printf("Data: ");
   scanf("%d/%d/%d", &dia, &mes, &ano);

    for (i=0; i<nr_aut; i++)
        if((aut[i].data_inicio.dia<=dia && aut[i].data_inicio.mes<=mes && aut[i].data_inicio.ano<=ano) && (aut[i].data_inicio.dia>=1 && aut[i].data_inicio.mes>=1 && aut[i].data_inicio.ano>=1)){
            if((aut[i].data_fim.dia<=dia && aut[i].data_fim.mes<=mes && aut[i].data_fim.ano<=ano) && (aut[i].data_fim.dia>=1 && aut[i].data_fim.mes>=1 && aut[i].data_fim.ano>=1)){
            existe=1;
            nr_aut--;
            aut[i].id=aut[nr_aut].id;
            aut[i].id_recurso=aut[nr_aut].id_recurso;
            aut[i].id_responsavel=aut[nr_aut].id_responsavel;
            aut[i].nr_associados=aut[nr_aut].nr_associados;

            for(j=0; j<aut[i].nr_associados; j++){
                aut[i].associados_pessoas[j]=aut[nr_aut].associados_pessoas[j];
                aut[i].associados_grupos[j]=aut[nr_aut].associados_grupos[j];
            }
            aut[nr_aut].data_inicio.dia = 0;
            aut[nr_aut].data_inicio.mes = 0;
            aut[nr_aut].data_inicio.ano = 0;
            aut[nr_aut].data_fim.dia = 0;
            aut[nr_aut].data_fim.mes = 0;
            aut[nr_aut].data_fim.ano = 0;
            strcpy(aut[i].descricao, aut[nr_aut].descricao);
            printf("\n\n--------- AUTORIZACAO COM A DATA %d/%d/%d APAGADA COM SUCESSO!!! ---------\n\n", dia, mes, ano);
        }
        }
        if(existe==0){
            system("cls");
            printf("\nNao existe nenhuma autorizacao com a data %d/%d/%d que indicou!!!\n\n");
        }
}
system("pause");
system("cls");
}

void gravar_todos_ficheiros(){
            FILE* fp;
            char nome[MAXNOME];
            printf("\nQual o nome que deseja atribuir ao ficheiro: ");
            scanf(" ");
            gets(nome);
            fp = fopen (nome, "w+");  //abre o ficheiro para leitura
            if (fp == NULL) {
                printf("Erro na abertura do ficheiro!!\n");
                exit(0);
            }
            // Exportar numero total de acessos em todo o programa
            fprintf(fp,"Numero Total de Acessos: \n");
            fprintf(fp,"Pessoas: %d\n", nr_pessoal);
            fprintf(fp,"Recursos: %d\n", nr_recursos);
            fprintf(fp,"Autorizacoes: %d\n", nr_aut);
            fprintf(fp,"Grupos de Acesso: %d\n", nr_grupos);
            fprintf(fp,"Disciplinas: %d\n", nr_discp);
            fprintf(fp,"Areas de Trabalho: %d\n", nr_area_trab);
            fprintf(fp,"Grupos Disciplinares: %d\n\n", nr_grp_discp);


            // Exportar recursos fisicos
            fprintf(fp,"Recursos fisicos:  \n");
            for(i=0; i<nr_recursos; i++){
                fprintf(fp,"Numero de identificacao (ID): %.2f\n", recursos[i].id);
                fprintf(fp,"Lotacao: %d\n", recursos[i].lotacao);
                fprintf(fp,"Nome: %s\n", recursos[i].nome);
                fprintf(fp,"Responsavel: %d\n", recursos[i].responsavel);
                fprintf(fp,"Observacoes: %s\n\n", recursos[i].observacoes);
            }
            // Exportar pessoas
            fprintf(fp,"\nPessoal: \n");
            for(i=0; i<nr_pessoal; i++){
                fprintf(fp,"Numero de identificacao (ID): %d\n", pessoal[i].id);
                fprintf(fp,"Nome: %s\n", pessoal[i].nome);
                fprintf(fp,"Tipo: %d\n\n" ,pessoal[i].tipo);
            }

            // Exportar Grupos de acesso
            fprintf(fp,"\nGrupos de acesso: \n");
            for(i=0; i<nr_grupos; i++){
                fprintf(fp,"Numero de identificacao (ID): %d\n", grupos[i].id);
                fprintf(fp,"Nome: %s\n", grupos[i].nome);
                fprintf(fp,"Nr de associados: %d\n", grupos[i].nr_associados);
                fprintf(fp,"Associados: \n");
                for(j=0; j<grupos[i].nr_associados; j++){
                    fprintf(fp,"Numero de identificacao (ID): %d\n",grupos[i].associados[j]);
                }
                fprintf(fp,"\n");
            }

            // Exportar Disciplinas
            fprintf(fp,"\nDisciplinas: \n");
            for(i=0; i<nr_discp; i++){
                fprintf(fp,"Nome: %s\n", discp[i].nome);
                fprintf(fp,"Curso: %s\n", discp[i].curso);
                fprintf(fp,"Semestre: %d\n", discp[i].semestre);
                fprintf(fp,"Ano Curricular: %d\n", discp[i].ano_curricular);
                fprintf(fp,"Ano lectivo: %d\n", discp[i].ano_lectivo);
                fprintf(fp,"Nr de associados: %d\n", discp[i].nr_associados);
                fprintf(fp,"Alunos associados: \n");
            }
            for(j=0; j<discp[i].nr_associados; j++){
                fprintf(fp,"Numero de identificacao (ID): %d\n", discp[i].alunos[j]);
            }
            fprintf(fp,"\n");

            // Exportar Grupos disciplinares
            fprintf(fp,"Grupos disciplinares: \n");

            for(i=0; i<nr_grp_discp; i++){
                fprintf(fp,"Nome: %s\n", grp_discp[i].nome);
                fprintf(fp,"Nr de associados: %d\n", grp_discp[i].nr_associados);
                fprintf(fp,"Docentes associados: \n");
                for(j=0; j<grp_discp[i].nr_associados; j++){
                  fprintf(fp,"Numero de identificacao (ID): %d\n", grp_discp[i].docentes[j]);
                }
                fprintf(fp,"\n");
            }

            // Exportar áreas de trabalho
            fprintf(fp,"\nAreas de trabalho: \n");
            for(i=0; i<nr_area_trab; i++){
                fprintf(fp,"Nome: %s\n", area_trab[i].nome);
                fprintf(fp,"Nr de associados : %d\n", area_trab[i].nr_associados);
                fprintf(fp,"Funcionarios associados: \n");
                for(j=0; j<area_trab[i].nr_associados; j++){
                  fprintf(fp,"Numero de identificacao (ID): %d\n",area_trab[i].funcionarios[j]);
                }
                fprintf(fp,"\n");
            }

            //Exportar autorizações
              fprintf(fp,"\nAutorizacoes: \n");
              for(i=0; i<nr_aut; i++){
                    fprintf(fp,"Numero de identificacao (ID) da autorizacao: %d \n", aut[i].id);
                    fprintf(fp,"%d/%d/%d\n",aut[i].data_inicio.dia,aut[i].data_inicio.mes,aut[i].data_inicio.ano);
                    fprintf(fp,"%d/%d/%d\n",aut[i].data_fim.dia,aut[i].data_fim.mes,aut[i].data_fim.ano);
                    fprintf(fp,"Id responsavel: %d\n", aut[i].id_responsavel);
                    for(j=0; j<aut[i].nr_associados; j++){
                        fprintf(fp,"Associados (pelo numero de identificacao)\n");
                        fprintf(fp,"-> %d\n", aut[i].nr_associados);
                        fprintf(fp,"\n");
                    }
                    fprintf(fp,"\n");
                    }
              fclose(fp);
    printf("Ficheiro gravado com sucesso!!!\n\n");
}

void gravar_ficheiros_pessoas(){
            FILE* fp;
            char nome[MAXNOME];
            printf("\nQual o nome que deseja atribuir ao ficheiro: ");
            scanf(" ");
            gets(nome);
            fp = fopen (nome, "w+");  //abre o ficheiro para leitura
    if (fp == NULL) {
        printf("Erro na abertura do ficheiro!!\n");
        exit(0);
    }

    // Exportar numero total de acessos em todo o programa
    fprintf(fp,"Numero Total de Acessos: \n");
    fprintf(fp,"Pessoas: %d\n", nr_pessoal);
    fprintf(fp,"Recursos: %d\n", nr_recursos);
    fprintf(fp,"Autorizacoes: %d\n", nr_aut);
    fprintf(fp,"Grupos de Acesso: %d\n", nr_grupos);
    fprintf(fp,"Disciplinas: %d\n", nr_discp);
    fprintf(fp,"Areas de Trabalho: %d\n", nr_area_trab);
    fprintf(fp,"Grupos Disciplinares: %d\n\n", nr_grp_discp);

    // Exportar pessoas
    fprintf(fp,"Dados das Pessoas\n\n");
    fprintf(fp,"\nPessoal: \n");
    for(i=0; i<nr_pessoal; i++){
        fprintf(fp,"Numero de identificacao (ID): %d\n", pessoal[i].id);
        fprintf(fp,"Nome: %s\n", pessoal[i].nome);
        fprintf(fp,"Tipo: %d\n\n" ,pessoal[i].tipo);
    }
    fclose(fp);
    printf("Ficheiro gravado com sucesso!!!\n\n");
}

void gravar_ficheiros_grupos(){
            FILE* fp;
            char nome[MAXNOME];
            printf("\nQual o nome que deseja atribuir ao ficheiro: ");
            scanf(" ");
            gets(nome);
            fp = fopen (nome, "w+");  //abre o ficheiro para leitura
    if (fp == NULL) {
        printf("Erro na abertura do ficheiro!!\n");
        exit(0);
    }

    // Exportar numero total de acessos em todo o programa
    fprintf(fp,"Numero Total de Acessos: \n");
    fprintf(fp,"Pessoas: %d\n", nr_pessoal);
    fprintf(fp,"Recursos: %d\n", nr_recursos);
    fprintf(fp,"Autorizacoes: %d\n", nr_aut);
    fprintf(fp,"Grupos de Acesso: %d\n", nr_grupos);
    fprintf(fp,"Disciplinas: %d\n", nr_discp);
    fprintf(fp,"Areas de Trabalho: %d\n", nr_area_trab);
    fprintf(fp,"Grupos Disciplinares: %d\n\n", nr_grp_discp);

    // Exportar Grupos de acesso
        fprintf(fp,"Dados dos Grupos\n\n");
        fprintf(fp,"\nGrupos de acesso: \n");
        for(i=0; i<nr_grupos; i++){
            fprintf(fp,"Numero de identificacao (ID): %d\n", grupos[i].id);
            fprintf(fp,"Nome: %s\n", grupos[i].nome);
            fprintf(fp,"Nr de associados: %d\n", grupos[i].nr_associados);
            fprintf(fp,"Associados: \n");
            for(j=0; j<grupos[i].nr_associados; j++){
                fprintf(fp,"Numero de identificacao (ID): %d\n",grupos[i].associados[j]);
            }
            fprintf(fp,"\n");
        }

        // Exportar Disciplinas
        fprintf(fp,"\nDisciplinas: \n");
        for(i=0; i<nr_discp; i++){
            fprintf(fp,"Nome: %s\n", discp[i].nome);
            fprintf(fp,"Curso: %s\n", discp[i].curso);
            fprintf(fp,"Semestre: %d\n", discp[i].semestre);
            fprintf(fp,"Ano Curricular: %d\n", discp[i].ano_curricular);
            fprintf(fp,"Ano lectivo: %d\n", discp[i].ano_lectivo);
            fprintf(fp,"Nr de associados: %d\n", discp[i].nr_associados);
            fprintf(fp,"Alunos associados\n");
        }
        for(j=0; j<discp[i].nr_associados; j++){
            fprintf(fp,"Numero de identificacao (ID): %d\n", discp[i].alunos[j]);
        }
        fprintf(fp,"\n");

        // Exportar Grupos disciplinares
        fprintf(fp,"Grupos disciplinares: \n");
        for(i=0; i<nr_grp_discp; i++){
            fprintf(fp,"Nome: %s\n", grp_discp[i].nome);
            fprintf(fp,"Nr de associados: %d\n", grp_discp[i].nr_associados);
            fprintf(fp,"Docentes associados\n");
            for(j=0; j<grp_discp[i].nr_associados; j++){
                fprintf(fp,"Numero de identificacao (ID): %d\n", grp_discp[i].docentes[j]);
            }
            fprintf(fp,"\n");
        }

        // Exportar áreas de trabalho
        fprintf(fp,"\nAreas de trabalho: \n");
        for(i=0; i<nr_area_trab; i++){
            fprintf(fp,"Nome: %s\n", area_trab[i].nome);
            fprintf(fp,"Nr de associados : %d\n", area_trab[i].nr_associados);
            fprintf(fp,"Funcionarios associados\n");
            for(j=0; j<area_trab[i].nr_associados; j++){
                fprintf(fp,"Numero de identificacao (ID): %d\n",area_trab[i].funcionarios[j]);
            }
            fprintf(fp,"\n");
        }
        fclose(fp);
        printf("Ficheiro gravado com sucesso!!!\n\n");
}

void gravar_ficheiros_recursos(){
            FILE* fp;
            char nome[MAXNOME];
            printf("\nQual o nome que deseja atribuir ao ficheiro: ");
            scanf(" ");
            gets(nome);
            fp = fopen (nome, "w+");  //abre o ficheiro para leitura
    if (fp == NULL) {
        printf("Erro na abertura do ficheiro!!\n");
        exit(0);
    }

    // Exportar numero total de acessos em todo o programa
    fprintf(fp,"Numero Total de Acessos: \n");
    fprintf(fp,"Pessoas: %d\n", nr_pessoal);
    fprintf(fp,"Recursos: %d\n", nr_recursos);
    fprintf(fp,"Autorizacoes: %d\n", nr_aut);
    fprintf(fp,"Grupos de Acesso: %d\n", nr_grupos);
    fprintf(fp,"Disciplinas: %d\n", nr_discp);
    fprintf(fp,"Areas de Trabalho: %d\n", nr_area_trab);
    fprintf(fp,"Grupos Disciplinares: %d\n\n", nr_grp_discp);

    // Exportar recursos fisicos
    fprintf(fp,"Dados dos Recursos Fisicos\n\n");
    fprintf(fp,"Recursos fisicos: \n");
    for(i=0; i<nr_recursos; i++){
        fprintf(fp,"Numero de identificacao (ID): %.2f\n", recursos[i].id);
        fprintf(fp,"Lotacao: %d\n", recursos[i].lotacao);
        fprintf(fp,"Nome: %s\n", recursos[i].nome);
        fprintf(fp,"Responsavel (numero de identificacao): %d\n", recursos[i].responsavel);
        fprintf(fp,"Observacoes: %s\n\n", recursos[i].observacoes);
    }
    fclose(fp);
    printf("Ficheiro gravado com sucesso!!!\n\n");
}

void gravar_ficheiros_autorizacoes(){
            FILE* fp;
            char nome[MAXNOME];
            printf("\nQual o nome que deseja atribuir ao ficheiro: ");
            scanf(" ");
            gets(nome);
            fp = fopen (nome, "w+");  //abre o ficheiro para leitura
    if (fp == NULL) {
        printf("Erro na abertura do ficheiro!!\n");
        exit(0);
    }

    // Exportar numero total de acessos em todo o programa
    fprintf(fp,"Numero Total de Acessos: \n");
    fprintf(fp,"Pessoas: %d\n", nr_pessoal);
    fprintf(fp,"Recursos: %d\n", nr_recursos);
    fprintf(fp,"Autorizacoes: %d\n", nr_aut);
    fprintf(fp,"Grupos de Acesso: %d\n", nr_grupos);
    fprintf(fp,"Disciplinas: %d\n", nr_discp);
    fprintf(fp,"Areas de Trabalho: %d\n", nr_area_trab);
    fprintf(fp,"Grupos Disciplinares: %d\n\n", nr_grp_discp);

    //Exportar autorizações
    fprintf(fp,"Dados das Autorizacoes\n\n");
    fprintf(fp,"\nAutorizacoes: \n");
    for(i=0; i<nr_aut; i++){
        fprintf(fp,"Numero de identificacao (ID) da autorizacao: %d \n", aut[i].id);
        fprintf(fp,"Data de inicio: %d/%d/%d\n",aut[i].data_inicio.dia,aut[i].data_inicio.mes,aut[i].data_inicio.ano);
        fprintf(fp,"Data de fim: %d/%d/%d\n",aut[i].data_fim.dia,aut[i].data_fim.mes,aut[i].data_fim.ano);
        fprintf(fp,"Id responsavel: %d\n", aut[i].id_responsavel);
        for(j=0; j<aut[i].nr_associados; j++){
            fprintf(fp,"Pessoas Associadas (numero de identificacao): %d\n", aut[i].associados_pessoas);
            fprintf(fp,"Grupos Associados ((numero de identificacao): %d\n", aut[i].associados_grupos);
            fprintf(fp,"\n");
        }
    }
    fclose(fp);
    printf("Ficheiro gravado com sucesso!!!\n\n");
}

void gravar_autorizacoes_anteriores_data(){
    FILE *fp;
    char nome[MAXNOME];

    printf("Indique a data para guardar autorizacoes anteriores a esta\n");
    printf("Data: ");
    scanf("%d/%d/%d", &dia,&mes,&ano);

    printf("\nIndique o nome que deseja atribuir ao ficheiro: \n");
    scanf(" ");
    gets(nome);
    fp = fopen (nome, "w+");  //ABRE O FICHEIRO para leitura

   if (fp == NULL) {
        printf ("Houve um erro ao abrir o arquivo!!\n");

   }else{
       printf ("Ficheiro gravado com sucesso...\n");

       for(i=0; i<nr_aut; i++){
            if((aut[i].data_inicio.dia<=dia && aut[i].data_inicio.mes<=mes && aut[i].data_inicio.ano<=ano) && (aut[i].data_inicio.dia>=1 && aut[i].data_inicio.mes>=1 && aut[i].data_inicio.ano>=1)){
                if((aut[i].data_fim.dia<=dia && aut[i].data_fim.mes<=mes && aut[i].data_fim.ano<=ano) && (aut[i].data_fim.dia>=1 && aut[i].data_fim.mes>=1 && aut[i].data_fim.ano>=1)){
                    existe=1;
                    //Exportar autorizaçoes anteriores a uma data
                    fprintf(fp,"Dados das Autorizacoes Anteriores a Data\n\n");
                    fprintf(fp,"\nAutorizacoes: \n");
                    for(i=0; i<nr_aut; i++){
                        fprintf(fp,"Numero de identificacao (ID) da autorizacao: %d \n", aut[i].id);
                        fprintf(fp,"Data de inicio: %d/%d/%d\n",aut[i].data_inicio.dia,aut[i].data_inicio.mes,aut[i].data_inicio.ano);
                        fprintf(fp,"Data de fim: %d/%d/%d\n",aut[i].data_fim.dia,aut[i].data_fim.mes,aut[i].data_fim.ano);
                        fprintf(fp,"Id responsavel: %d\n", aut[i].id_responsavel);
                        for(j=0; j<aut[i].nr_associados; j++){
                            fprintf(fp,"Pessoas Associadas (numero de identificacao): %d\n", aut[i].associados_pessoas);
                            fprintf(fp,"Grupos Associados ((numero de identificacao): %d\n", aut[i].associados_grupos);
                            fprintf(fp,"\n");
                        }
                    }
                }
            }
            if(existe==0){
                system("cls");
                printf("\nNao existe nenhuma autorizacao com essa data %d/%d/%d !!\n\n", dia, mes, ano);
            }
                fclose(fp);
            }
       }
system("pause");
system("cls");
}

void ler_todos_ficheiros(){
    FILE *fp;
    char nome[MAXNOME];
    printf("\nQual o nome do ficheiro guardado?\n");
    scanf(" ");
    gets(nome);
    fp = fopen (nome, "r+");  //ABRE O FICHEIRO para leitura

   if (fp == NULL) {
      printf ("Houve um erro ao abrir o arquivo!!\n");
   }else{
        printf("Ficheiro carregado com sucesso...\n");
            //carregar numero total de acessos
            fscanf(fp,"Numero Total de Acessos: \n");
            fscanf(fp,"Pessoas: %d\n", &nr_pessoal);
            fscanf(fp,"Recursos: %d\n", &nr_recursos);
            fscanf(fp,"Autorizacoes: %d\n", &nr_aut);
            fscanf(fp,"Grupos de Acesso: %d\n", &nr_grupos);
            fscanf(fp,"Disciplinas: %d\n", &nr_discp);
            fscanf(fp,"Areas de Trabalho: %d\n", &nr_area_trab);
            fscanf(fp,"Grupos Disciplinares: %d\n\n", &nr_grp_discp);

            //carregar recursos fisicos
            fscanf(fp,"Recursos fisicos:  \n");
            for(i=0; i<nr_recursos; i++){
                fscanf(fp,"Numero de identificacao (ID): %.2f\n", &recursos[i].id);
                fscanf(fp,"Lotacao: %d\n", &recursos[i].lotacao);
                fgets(recursos[i].nome,MAXNOME,fp);
                fscanf(fp,"Responsavel: %d\n", &recursos[i].responsavel);
                fgets(recursos[i].observacoes,MAXDES,fp);
            }
            //carregar pessoas
            fscanf(fp,"\nPessoal: \n");
            for(i=0; i<nr_pessoal; i++){
                fscanf(fp,"Numero de identificacao (ID): %d\n", &pessoal[i].id);
                fgets(pessoal[i].nome,MAXNOME,fp);
                fscanf(fp,"Tipo: %d\n\n", &pessoal[i].tipo);
            }

            //carregar Grupos de acesso
            fscanf(fp,"\nGrupos de acesso: \n");
            for(i=0; i<nr_grupos; i++){
                fscanf(fp,"Numero de identificacao (ID): %d\n", &grupos[i].id);
                fgets(grupos[i].nome,MAXNOME,fp);
                fscanf(fp,"Nr de associados: %d\n", &grupos[i].nr_associados);
                fscanf(fp,"Associados: \n");
                for(j=0; j<grupos[i].nr_associados; j++){
                    fscanf(fp,"Numero de identificacao (ID): %d\n", &grupos[i].associados[j]);
                }
                fscanf(fp,"\n");
            }

            //carregar Disciplinas
            fscanf(fp,"\nDisciplinas: \n");
            for(i=0; i<nr_discp; i++){
                fgets(discp[i].nome,MAXNOME,fp);
                fgets(discp[i].curso,MAXNOME,fp);
                fscanf(fp,"Semestre: %d\n", &discp[i].semestre);
                fscanf(fp,"Ano Curricular: %d\n", &discp[i].ano_curricular);
                fscanf(fp,"Ano lectivo: %d\n", &discp[i].ano_lectivo);
                fscanf(fp,"Nr de associados: %d\n", &discp[i].nr_associados);
                fscanf(fp,"Alunos associados: \n");
            }
            for(j=0; j<discp[i].nr_associados; j++){
                fscanf(fp,"Numero de identificacao (ID): %d\n", &discp[i].alunos[j]);
            }
            fscanf(fp,"\n");

            //carregar Grupos disciplinares
            fscanf(fp,"Grupos disciplinares: \n");

            for(i=0; i<nr_grp_discp; i++){
                fgets(grp_discp[i].nome,MAXNOME,fp);
                fscanf(fp,"Nr de associados: %d\n", &grp_discp[i].nr_associados);
                fscanf(fp,"Docentes associados: \n");
                for(j=0; j<grp_discp[i].nr_associados; j++){
                  fscanf(fp,"Numero de identificacao (ID): %d\n", &grp_discp[i].docentes[j]);
                }
                fscanf(fp,"\n");
            }

            //carregar áreas de trabalho
            fscanf(fp,"\nAreas de trabalho: \n");
            for(i=0; i<nr_area_trab; i++){
                fgets(area_trab[i].nome,MAXNOME,fp);
                fscanf(fp,"Nr de associados : %d\n", &area_trab[i].nr_associados);
                fscanf(fp,"Funcionarios associados: \n");
                for(j=0; j<area_trab[i].nr_associados; j++){
                  fscanf(fp,"Numero de identificacao (ID): %d\n", &area_trab[i].funcionarios[j]);
                }
                fscanf(fp,"\n");
            }

            //carregar autorizações
              fscanf(fp,"\nAutorizacoes: \n");
              for(i=0; i<nr_aut; i++){
                fscanf(fp,"Numero de identificacao (ID) da autorizacao: %d \n", &aut[i].id);
                fscanf(fp,"%d/%d/%d\n", &aut[i].data_inicio.dia, &aut[i].data_inicio.mes, &aut[i].data_inicio.ano);
                fscanf(fp,"%d/%d/%d\n", &aut[i].data_fim.dia, &aut[i].data_fim.mes, &aut[i].data_fim.ano);
                fscanf(fp,"Id responsavel: %d\n", &aut[i].id_responsavel);
                for(j=0; j<aut[i].nr_associados; j++){
                    fscanf(fp,"Associados (pelo numero de identificacao): %d\n");
                    fscanf(fp,"Pessoas: %d\n", &aut[i].associados_pessoas);
                    fscanf(fp,"Grupos: %d\n", &aut[i].associados_grupos);
                    fscanf(fp,"\n");
                    }
                    fscanf(fp,"\n");
              }
              fclose(fp);
    }
system("pause");
system("cls");
}

void ler_ficheiros_pessoas(){
    FILE *fp;
    char nome[MAXNOME];
    printf("\nQual o nome do ficheiro guardado?\n");
    scanf(" ");
    gets(nome);
    fp = fopen (nome, "r+");  //ABRE O FICHEIRO para leitura

   if (fp == NULL) {
      printf ("Houve um erro ao abrir o arquivo!!\n");
   }else{
        printf("Ficheiro carregado com sucesso...\n");
            //Carregar numero total de acessos
            fscanf(fp,"Numero Total de Acessos: \n");
            fscanf(fp,"Pessoas: %d\n", &nr_pessoal);
            fscanf(fp,"Recursos: %d\n", &nr_recursos);
            fscanf(fp,"Autorizacoes: %d\n", &nr_aut);
            fscanf(fp,"Grupos de Acesso: %d\n", &nr_grupos);
            fscanf(fp,"Disciplinas: %d\n", &nr_discp);
            fscanf(fp,"Areas de Trabalho: %d\n", &nr_area_trab);
            fscanf(fp,"Grupos Disciplinares: %d\n\n", &nr_grp_discp);

            // carregar ficheiro pessoas
            fscanf(fp,"Dados das Pessoas\n\n");
    fscanf(fp,"\nPessoal: \n");
    for(i=0; i<nr_pessoal; i++){
        fscanf(fp,"Numero de identificacao (ID): %d\n", &pessoal[i].id);
        fgets(&pessoal[i].nome,MAXNOME,fp);
        fscanf(fp,"Tipo: %d\n\n" , &pessoal[i].tipo);
    }
    fclose(fp);
   }
system("pause");
system("cls");
}

void ler_ficheiros_recursos(){
    FILE *fp;
    char nome[MAXNOME];
    printf("\nQual o nome do ficheiro guardado?\n");
    scanf(" ");
    gets(nome);
    fp = fopen (nome, "r+");  //ABRE O FICHEIRO para leitura

   if (fp == NULL) {
      printf ("Houve um erro ao abrir o arquivo!!\n");
   }else{
        printf("Ficheiro carregado com sucesso...\n");
            //carregar numero total de acessosa
            fscanf(fp,"Numero Total de Acessos: \n");
            fscanf(fp,"Pessoas: %d\n", &nr_pessoal);
            fscanf(fp,"Recursos: %d\n", &nr_recursos);
            fscanf(fp,"Autorizacoes: %d\n", &nr_aut);
            fscanf(fp,"Grupos de Acesso: %d\n", &nr_grupos);
            fscanf(fp,"Disciplinas: %d\n", &nr_discp);
            fscanf(fp,"Areas de Trabalho: %d\n", &nr_area_trab);
            fscanf(fp,"Grupos Disciplinares: %d\n\n", &nr_grp_discp);

            //carregar recursos fisicos
            fscanf(fp,"Dados dos Recursos Fisicos\n\n");
    fscanf(fp,"Recursos fisicos: \n");
    for(i=0; i<nr_recursos; i++){
        fscanf(fp,"Numero de identificacao (ID): %.2f\n", &recursos[i].id);
        fscanf(fp,"Lotacao: %d\n", &recursos[i].lotacao);
        fgets(&recursos[i].nome,MAXNOME,fp);
        fprintf(fp,"Responsavel (numero de identificacao): %d\n", &recursos[i].responsavel);
        fgets(&recursos[i].observacoes,MAXDES,fp);
    }
    fclose(fp);
    }
system("pause");
system("cls");
}

void ler_ficheiros_grupos(){
    FILE *fp;
    char nome[MAXNOME];
    printf("\nQual o nome do ficheiro guardado?\n");
    scanf(" ");
    gets(nome);
    fp = fopen (nome, "r+");  //ABRE O FICHEIRO para leitura

   if (fp == NULL) {
      printf ("Houve um erro ao abrir o arquivo!!\n");
   }else{
        printf("Ficheiro carregado com sucesso...\n");
            //carregar numero total de acessosa
            fscanf(fp,"Numero Total de Acessos: \n");
            fscanf(fp,"Pessoas: %d\n", &nr_pessoal);
            fscanf(fp,"Recursos: %d\n", &nr_recursos);
            fscanf(fp,"Autorizacoes: %d\n", &nr_aut);
            fscanf(fp,"Grupos de Acesso: %d\n", &nr_grupos);
            fscanf(fp,"Disciplinas: %d\n", &nr_discp);
            fscanf(fp,"Areas de Trabalho: %d\n", &nr_area_trab);
            fscanf(fp,"Grupos Disciplinares: %d\n\n", &nr_grp_discp);

            //carregar Grupos de acesso
            fscanf(fp,"Dados dos Grupos\n\n");
            fscanf(fp,"\nGrupos de acesso: \n");
        for(i=0; i<nr_grupos; i++){
            fscanf(fp,"Numero de identificacao (ID): %d\n", &grupos[i].id);
            fgets(&grupos[i].nome,MAXNOME,fp);
            fscanf(fp,"Nr de associados: %d\n", &grupos[i].nr_associados);
            fscanf(fp,"Associados: \n");
            for(j=0; j<grupos[i].nr_associados; j++){
                fscanf(fp,"Numero de identificacao (ID): %d\n", &grupos[i].associados[j]);
            }
            fscanf(fp,"\n");
        }

        //carregar Disciplinas
        fscanf(fp,"\nDisciplinas: \n");
        for(i=0; i<nr_discp; i++){
            fgets(&discp[i].nome,MAXNOME,fp);
            fgets(&discp[i].curso,MAXNOME,fp);
            fscanf(fp,"Semestre: %d\n", &discp[i].semestre);
            fscanf(fp,"Ano Curricular: %d\n", &discp[i].ano_curricular);
            fscanf(fp,"Ano lectivo: %d\n", &discp[i].ano_lectivo);
            fscanf(fp,"Nr de associados: %d\n", &discp[i].nr_associados);
            fscanf(fp,"Alunos associados\n");
        }
        for(j=0; j<discp[i].nr_associados; j++){
            fscanf(fp,"Numero de identificacao (ID): %d\n", &discp[i].alunos[j]);
        }
        fscanf(fp,"\n");

        // Exportar Grupos disciplinares
        fscanf(fp,"Grupos disciplinares: \n");
        for(i=0; i<nr_grp_discp; i++){
            fgets(&grp_discp[i].nome,MAXNOME,fp);
            fscanf(fp,"Nr de associados: %d\n", &grp_discp[i].nr_associados);
            fscanf(fp,"Docentes associados\n");
            for(j=0; j<grp_discp[i].nr_associados; j++){
                fscanf(fp,"Numero de identificacao (ID): %d\n", &grp_discp[i].docentes[j]);
            }
            fscanf(fp,"\n");
        }

        //carregar áreas de trabalho
        fscanf(fp,"\nAreas de trabalho: \n");
        for(i=0; i<nr_area_trab; i++){
            fgets(&area_trab[i].nome,MAXNOME,fp);
            fscanf(fp,"Nr de associados : %d\n", &area_trab[i].nr_associados);
            fscanf(fp,"Funcionarios associados\n");
            for(j=0; j<area_trab[i].nr_associados; j++){
                fscanf(fp,"Numero de identificacao (ID): %d\n", &area_trab[i].funcionarios[j]);
            }
            fscanf(fp,"\n");
        }
        fclose(fp);
    }
system("pause");
system("cls");
}

void ler_ficheiros_autorizacoes(){
    FILE *fp;
    char nome[MAXNOME];
    printf("\nQual o nome do ficheiro guardado?\n");
    scanf(" ");
    gets(nome);
    fp = fopen (nome, "r+");  //ABRE O FICHEIRO para leitura

   if (fp == NULL) {
      printf ("Houve um erro ao abrir o arquivo!!\n");
   }else{
        printf("Ficheiro carregado com sucesso!!\n");
            //carregar numero total de acessosa
            fscanf(fp,"Numero Total de Acessos: \n");
            fscanf(fp,"Pessoas: %d\n", &nr_pessoal);
            fscanf(fp,"Recursos: %d\n", &nr_recursos);
            fscanf(fp,"Autorizacoes: %d\n", &nr_aut);
            fscanf(fp,"Grupos de Acesso: %d\n", &nr_grupos);
            fscanf(fp,"Disciplinas: %d\n", &nr_discp);
            fscanf(fp,"Areas de Trabalho: %d\n", &nr_area_trab);
            fscanf(fp,"Grupos Disciplinares: %d\n\n", &nr_grp_discp);

            //carregar autorizações
               fscanf(fp,"Dados das Autorizacoes\n\n");
    fscanf(fp,"\nAutorizacoes: \n");
    for(i=0; i<nr_aut; i++){
        fscanf(fp,"Numero de identificacao (ID) da autorizacao: %d \n", &aut[i].id);
        fscanf(fp,"Data de inicio: %d/%d/%d\n",&aut[i].data_inicio.dia,&aut[i].data_inicio.mes,&aut[i].data_inicio.ano);
        fscanf(fp,"Data de fim: %d/%d/%d\n",&aut[i].data_fim.dia,&aut[i].data_fim.mes,&aut[i].data_fim.ano);
        fscanf(fp,"Id responsavel: %d\n", &aut[i].id_responsavel);
        for(j=0; j<aut[i].nr_associados; j++){
            fscanf(fp,"Pessoas Associadas (numero de identificacao): %d\n", &aut[i].associados_pessoas);
            fscanf(fp,"Grupos Associados ((numero de identificacao): %d\n", &aut[i].associados_grupos);
            fscanf(fp,"\n");
        }
    }
              fclose(fp);
        }
system("pause");
system("cls");
}

/*Funções para os menus*/
void menu_pessoas(){

do{
    printf("-------------------- MENU PESSOAS ----------------\n\n");
    printf("1-> INSERIR PESSOAS\n\n");
    printf("2-> APAGAR PESSOAS\n\n");
    printf("3-> LISTAR PESSOAS PELO TIPO\n\n");
    printf("4-> LISTAR TODAS AS PESSOAS\n\n");
    printf("5-> GRAVAR DADOS\n\n");
    printf("6-> LER DADOS\n\n");
    printf("7-> VOLTAR PARA O MENU PRINCIPAL\n\n");
    printf("0-> SAIR DO PROGRAMA\n\n");
    printf("Indique a opcao que deseja: ");
    scanf("%i", &opcao);

    switch(opcao){
    case 1:
        system("cls");
        inserir_pessoas();
    break;
    case 2:
        system("cls");
        apagar_pessoas();
    break;
    case 3:
        system("cls");
        listar_pessoas_tipo();
    break;
    case 4:
        system("cls");
        listar_todas_pessoas();
    break;
    case 5:
        system("cls");
        printf("Deseja gravar os dados das pessoas? \n");
        printf("1-> Sim\n");
        printf("2-> Nao\n");
        scanf("%d", &opcao);
        switch(opcao){
        case 1:
            system("cls");
            gravar_ficheiros_pessoas();
            printf("\n---------- TODOS OS DADOS DAS PESSOAS FORAM GUARDADOS ------------\n");
            system("pause");
            system("cls");
            break;
        case 2:
            system("cls");
            break;
        }
        break;
    case 6:
        system("cls");
        ler_ficheiros_pessoas();
    break;
    case 7:
        system("cls");
        main();
    break;
    case 0:
        system("cls");
        printf("Deseja gravar os dados? \n");
        printf("1-> Sim\n");
        printf("2-> Nao\n");
        scanf("%d", &opcao);
        switch(opcao){
        case 1:
            system("cls");
            gravar_todos_ficheiros();
            printf("\n---------- TODOS OS DADOS FORAM GUARDADOS ------------\n\n");
            system("pause");
            exit(0);
            break;
        case 2:
            exit(0);
            break;
        }
        break;
    default:
        printf("Opcao Invalida\n\n");
        system("pause");
        system("cls");
}
}while(opcao != 0);
}

void menu_grupos(){

    do{
        printf("-------------------- MENU GRUPOS ----------------\n\n");
        printf("1-> INSERIR GRUPOS\n\n");
        printf("2-> APAGAR GRUPOS\n\n");
        printf("3-> LISTAR GRUPOS (INCLUSIVE PESSOAS DESSES GRUPOS)\n\n");
        printf("4-> ASSOCIAR PESSOAS A GRUPOS\n\n");
        printf("5-> GRAVAR DADOS\n\n");
        printf("6-> LER DADOS\n\n");
        printf("7-> VOLTAR PARA O MENU PRINCIPAL\n\n");
        printf("0-> SAIR DO PROGRAMA\n\n");
        printf("Indique a opcao que deseja: ");
        scanf("%i", &opcao);

        switch(opcao){
        case 1:
            system("cls");
            inserir_grupos();
            break;
        case 2:
            system("cls");
            apagar_grupos();
            break;
        case 3:
            system("cls");
            listar_pessoas_grupos();
            break;
        case 4:
            system("cls");
            associar_pessoas_grupos();
            break;
        case 5:
            system("cls");
            printf("Deseja gravar os dados dos grupos? \n");
            printf("1-> Sim\n");
            printf("2-> Nao\n");
            scanf("%d", &opcao);
            switch(opcao){
            case 1:
                system("cls");
                gravar_ficheiros_grupos();
                printf("\n---------- TODOS OS DADOS DOS GRUPOS FORAM GUARDADOS ------------\n");
                system("pause");
                system("cls");
                break;
            case 2:
                system("cls");
                exit(0);
                break;
            }
            break;
            case 6:
                system("cls");
                ler_ficheiros_grupos();
            break;
    case 7:
        system("cls");
        main();
    break;
    case 0:
        system("cls");
            printf("Deseja gravar os dados? \n");
            printf("1-> Sim\n");
            printf("2-> Nao\n");
            scanf("%d", &opcao);
            switch(opcao){
            case 1:
                system("cls");
                gravar_todos_ficheiros();
                printf("\n---------- TODOS OS DADOS FORAM GUARDADOS ------------\n");
                system("pause");
                exit(0);
                break;
            case 2:
                exit(0);
                break;
            }
            break;
        default:
            printf("Opcao Invalida\n\n");
            system("pause");
            system("cls");
        }

    }while(opcao != 0);
}

void menu_autorizacoes(){

do{
    printf("\n-------------------- MENU AUTORIZACOES ----------------\n\n");
    printf("1-> INSERIR AUTORIZACAO\n\n");
    printf("2-> LISTAR AUTORIZACAO\n\n");
    printf("3-> LISTAR AUTORIZACAO ENTRE DATAS\n\n");
    printf("4-> APAGAR AUTORIZACAO\n\n");
    printf("5-> APAGAR AUTORIZACAO ANTERIOR A UMA DATA\n\n");
    printf("6-> GRAVAR AUTORIZACAO ANTERIOR A UMA DATA\n\n");
    printf("7-> GRAVAR DADOS\n\n");
    printf("8-> LER DADOS\n\n");
    printf("9-> VOLTAR PARA O MENU PRINCIPAL\n\n");
    printf("0-> SAIR DO PROGRAMA\n\n");
    printf("Indique a opcao que deseja: ");
    scanf("%i", &opcao);

    switch(opcao){
    case 1:
        system("cls");
        inserir_autorizacoes();
    break;
    case 4:
        system("cls");
        apagar_autorizacoes();
    break;
    case 2:
        system("cls");
       listar_autorizacoes_por_datas();
    break;
    case 3:
        system("cls");
        listar_autorizacoes_entre_datas();
    break;
    case 5:
        system("cls");
        apagar_autorizacao_anterior_data();
        break;
    case 6:
        system("cls");
        gravar_autorizacoes_anteriores_data();
        break;
    case 7:
        system("cls");
        printf("Deseja gravar os dados das autorizacoes? \n");
        printf("1-> Sim\n");
        printf("2-> Nao\n");
        scanf("%d", &opcao);
        switch(opcao){
        case 1:
            system("cls");
            gravar_ficheiros_autorizacoes();
            printf("\n---------- TODOS OS DADOS DAS AUTORIZACOES FORAM GUARDADOS ------------\n");
            system("pause");
            system("cls");
            break;
        case 2:
            system("cls");
            break;
        }
        break;
        case 8:
            system("cls");
            ler_ficheiros_autorizacoes();
            break;
    case 9:
        system("cls");
        main();
    break;
    case 0:
        system("cls");
        printf("Deseja gravar os dados? \n");
        printf("1-> Sim\n");
        printf("2-> Nao\n");
        scanf("%d", &opcao);
        switch(opcao){
        case 1:
            system("cls");
            gravar_todos_ficheiros();
            printf("\n---------- TODOS OS DADOS FORAM GUARDADOS ------------\n");
            system("pause");
            exit(0);
            break;
        case 2:
            exit(0);
            break;
        }
        break;
    default:
        printf("Opcao Invalida\n\n");
        system("pause");
        system("cls");
}

}while(opcao != 0);
}

void menu_recursos(){

do{
    printf("-------------------- MENU RECURSOS ----------------\n\n");
    printf("1-> INSERIR RECURSOS\n\n");
    printf("2-> APAGAR RECURSOS\n\n");
    printf("3-> LISTAR TODOS OS RECURSOS\n\n");
    printf("4-> LISTAR INFORMACAO DE UM RESPECTIVO RECURSO\n\n");
    printf("5-> GRAVAR DADOS\n\n");
    printf("6-> LER DADOS\n\n");
    printf("7-> VOLTAR PARA O MENU PRINCIPAL\n\n");
    printf("0-> SAIR DO PROGRAMA\n\n");
    printf("Indique a opcao que deseja: ");
    scanf("%i", &opcao);

    switch(opcao){
    case 1:
        system("cls");
        inserir_recursos();
    break;
    case 2:
        system("cls");
        apagar_recursos();
    break;
    case 3:
        system("cls");
        listar_recursos();
    break;
    case 4:
        system("cls");
        listar_info_recurso();
    break;
    case 5:
        system("cls");
        printf("Deseja gravar os dados dos recursos? \n");
        printf("1-> Sim\n");
        printf("2-> Nao\n");
        scanf("%d", &opcao);
        switch(opcao){
        case 1:
            system("cls");
            gravar_ficheiros_recursos();
            printf("\n---------- TODOS OS DADOS DOS RECURSOS FORAM GUARDADOS ------------\n");
            system("pause");
            exit(0);
            break;
        case 2:
            exit(0);
            break;
        }
        break;
        case 6:
            system("cls");
            ler_ficheiros_recursos();
            break;
    case 7:
        system("cls");
        main();
    break;
    case 0:
        system("cls");
        printf("Deseja gravar os dados? \n");
        printf("1-> Sim\n");
        printf("2-> Nao\n");
        scanf("%d", &opcao);
        switch(opcao){
        case 1:
            system("cls");
            gravar_todos_ficheiros();
            printf("\n---------- TODOS OS DADOS FORAM GUARDADOS ------------\n");
            system("pause");
            exit(0);
            break;
        case 2:
            exit(0);
            break;
        }
        break;
    default:
        printf("Opcao Invalida\n\n");
        system("pause");
        system("cls");
}
}while(opcao != 0);

}

/*Menu que será redirecionado para outros menus consoante a escolha do utilizador*/
int main(){

do{
    printf("-------------GESTAO DE ACESSOS ESTGP----------\n\n");
    printf("--------------------MENU----------------\n\n");
    printf("1-> PESSOAS\n\n");
    printf("2-> GRUPOS \n\n");
    printf("3-> RECURSOS \n\n");
    printf("4-> AUTORIZACOES\n\n");
    printf("5-> GRAVAR TODOS OS FICHEIROS\n\n");
    printf("6-> LER TODOS OS FICHEIROS GUARDADOS\n\n");
    printf("0-> SAIR DO PROGRAMA\n\n");
    printf("Indique a opcao que deseja: ");
    scanf("%d", &opcao);

    switch(opcao){
        case 1:
            system("cls");
            menu_pessoas();
        break;
        case 2:
            system("cls");
            menu_grupos();
        break;
        case 3:
            system("cls");
            menu_recursos();
        break;
        case 4:
            system("cls");
            menu_autorizacoes();
        break;
        case 5:
            system("cls");
            printf("Deseja gravar todos os dados? \n");
            printf("1-> Sim\n");
            printf("2-> Nao\n");
            scanf("%d", &opcao);
            switch(opcao){
            case 1:
                system("cls");
                gravar_todos_ficheiros();
                printf("\n---------- TODOS OS DADOS FORAM GUARDADOS ------------\n");
                system("pause");
                system("cls");
                break;
            case 2:
                system("cls");
                break;
            }
        break;
        case 6:
               system("cls");
               ler_todos_ficheiros();
        break;
        case 0:
            system("cls");
            printf("Deseja gravar os dados? \n");
            printf("1-> Sim\n");
            printf("2-> Nao\n");
            scanf("%d", &opcao);
            switch(opcao){
            case 1:
                system("cls");
                gravar_todos_ficheiros();
                printf("\n---------- TODOS OS DADOS FORAM GUARDADOS ------------\n");
                system("pause");
                exit(0);
                break;
            case 2:
                exit(0);
                break;
            }
            break;
        default:
            printf("Opcao Invalida\n\n");
            system("pause");
            system("cls");
            break;
    }
}while(opcao != 0);
}
