/*---------------------------------------------------------------------+
 *          UNIFAL - Universidade Federal de Alfenas.                  *
 *            BACHARELADO EM CIÊNCIA DA COMPUTAÇÃO.                    *
 * Trabalho..: Atividade 3                                             *
 * Disciplina: AEDS 2                                                  *
 * Professor.: Paulo Alexandre Bressan                                 *
 * Aluno:....: Daniel da Costa Lima                                    *
 * Data......: 12/04/2022                                              *
+---------------------------------------------------------------------*/

#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/* Criando as estruturas base para a lista*/
typedef struct no {
    string modelo, marca, tipo, ano, km, potencia, combustivel, cambio, direcao, cor, portas, placa;
    struct no *prox;
} No;

typedef struct lista {
    no *inicio;
    int tam;
} Lista;

/* Criando as estruturas base para a ávore binária */
typedef struct info{
    string modelo, marca, tipo, ano, km, potencia, combustivel, cambio, direcao, cor, portas, placa;
} Info;

typedef struct noarv{
    info car;
    struct noarv *dir, *esq;
    int altura;
}NoArv;

/*------------------------------ Funções para a lista encadeada ------------------------------*/
/* Inserindo nó no início da lista */
void inserirInicio(Lista *lista, No *dados){
    No *novo = (No*)new(No);
    if (novo){
        novo->ano = dados->ano;
        novo->cambio = dados->cambio;
        novo->combustivel = dados->combustivel;
        novo->cor = dados->cor;
        novo->direcao = dados->direcao;
        novo->km = dados->km;
        novo->marca = dados->marca;
        novo->modelo = dados->modelo;
        novo->placa = dados->placa;
        novo->portas = dados->portas;
        novo->potencia = dados->potencia;

        novo->prox = lista->inicio;
        lista->inicio = novo;
        lista->tam++;        
    }
    else {
        cout << "+---------------------------+" << endl;
        cout << "|  Erro ao alocar memoria!  |" << endl;
        cout << "+---------------------------+" << endl;
    }
}

/* Função para remover nós da lista encadeada*/
void remover(Lista *lista, No *dados){
    No *inicio = lista->inicio;     //Criando uma variável ponteiro pra percorrer a lista sem perder a referência
    No *removendo_no;

    if (inicio != NULL && lista->inicio->placa == dados->placa){
        removendo_no = lista->inicio;
        lista->inicio = removendo_no->prox;
    }
    else{
        while (inicio != NULL && inicio->prox != NULL && inicio->prox->placa != dados->placa){
            inicio = inicio->prox;
        }  
        if (inicio != NULL && inicio->prox != NULL){
            removendo_no = inicio->prox;
            inicio->prox = removendo_no->prox;
        }
        
    }
    if (removendo_no){
        delete removendo_no;
        lista->tam--;
    }
    
}

/* Função para realizar uma busca na lista encadeada */
void buscar(Lista *lista, string dado1){
    No *aux, *no = NULL;
    int cont = 0;
    
    aux = lista->inicio;
    
    cout << "+-----------------------------------+" << endl;
    cout << "|        Resultado da busca:        |" << endl;
    while (aux){
        if (aux->ano == dado1 || aux->cambio == dado1 ||aux->combustivel == dado1 || aux->cor == dado1 || aux->direcao == dado1 || aux->km == dado1 || aux->marca == dado1 || aux->modelo == dado1 || aux->placa == dado1 || aux->portas == dado1 || aux->potencia == dado1){
            cout <<"|          Placa: " << aux->placa <<"           |"<< endl;
            cont++;
        }
        aux = aux->prox;
    } 
    if (cont == 0){
        cout << "|    Nenhum carro foi encontrado.   |" << endl;
    }
    cout << "+-----------------------------------+" << endl;
    
}

/* 
 * Função que verifica a existência do veiculo no sistema
 * pela comparação da placa do novo nó que será inserido
 * com as placas dos veículos já inseridos 
 * Retorno: 1 para veículo já cadastrado e 0 caso não esteja cadastrado 
 */
int buscar_placa(Lista *lista, No dados){
    No *aux;

    aux = lista->inicio;
    
    while (aux){
        if (aux->placa == dados.placa){
            return 1;
        }
        aux = aux->prox;
    } 
    return 0;
}

/* Imprimir a lista */
void imprimir(Lista *lista){
    No *inicio = lista->inicio;
    cout << "+-----------------------------------+" << endl;
    cout << "|             Relatorio:            |" << endl;
    cout << "|        Tamanho da Lista: " << lista->tam <<"       |"<< endl;
    while (inicio != NULL){
        cout << "|        Placa: " << inicio->placa << "             |" << endl;
        inicio = inicio->prox;
    }
    cout << "+-----------------------------------+" << endl;
    cout << endl;
}

/* Função para encerrar a lista */
void encerra_lista(Lista *lista){
    No *ant = lista->inicio->prox;
    No *pont = ant->prox;

    while (pont != NULL){
        delete(ant);
        ant = pont;
        pont = pont->prox;
    }
    delete(ant);
    delete(lista);
}

/*----------------------------------- Funções para a árvore binária ----------------------------------*/
/* Função para inserir nós na árvore */
NoArv* inserir_v1(NoArv *raiz, Info carros){

    if (raiz == NULL){
        NoArv *aux = (NoArv*)new(NoArv);
        if (aux){
            aux->car.ano = carros.ano;
            aux->car.cambio = carros.cambio;
            aux->car.combustivel = carros.combustivel;
            aux->car.cor = carros.cor;
            aux->car.direcao = carros.direcao;
            aux->car.km = carros.km;
            aux->car.marca = carros.marca;
            aux->car.modelo = carros.modelo;
            aux->car.placa = carros.placa;
            aux->car.portas = carros.portas;
            aux->car.potencia = carros.potencia;
            aux->car.tipo = carros.tipo;

            aux->esq = NULL;
            aux->dir = NULL;
            return aux;
        }
        else{
            cout << "+---------------------------+" << endl;
            cout << "|  Erro ao alocar memoria!  |" << endl;
            cout << "+---------------------------+" << endl;
        }

    }
    else{
        if (carros.placa < raiz->car.placa){
            raiz->esq = inserir_v1(raiz->esq, carros);
        }
        else{
            raiz->dir = inserir_v1(raiz->dir, carros);
        }
        return raiz;
    }
    
}

/* Função que realiza uma busca na árvore binária */
NoArv* buscar_v1(NoArv *raiz, string dado1){
    while (raiz){
        if (raiz->car.placa > dado1 ){ 
            raiz = raiz->esq;
        }
        else if(  raiz->car.placa < dado1){
            raiz = raiz->dir;
        }
        else{
            return raiz;
        }        
    }
    return NULL;
}

/*Função que imprime a ávore binária*/
void imprimir_v1(NoArv *raiz){
    if (raiz){
        cout << "|          Placa: " << raiz->car.placa << "          |" << endl;
        imprimir_v1(raiz->esq);
        imprimir_v1(raiz->dir);
    }  
}

/*--------------------------------------- Funções para a árvore AVL --------------------------------------*/
/* Inserindo nós */
NoArv* novo_no(Info carros){
    NoArv *novo = new(NoArv);
    if (novo){
        novo->car.ano = carros.ano;
        novo->car.cambio = carros.cambio;
        novo->car.combustivel = carros.combustivel;
        novo->car.cor = carros.cor;
        novo->car.direcao = carros.direcao;
        novo->car.km = carros.km;
        novo->car.marca = carros.marca;
        novo->car.modelo = carros.modelo;
        novo->car.placa = carros.placa;
        novo->car.portas = carros.portas;
        novo->car.potencia = carros.potencia;
        novo->car.tipo = carros.tipo;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    else{
        cout << "+---------------------------+" << endl;
        cout << "|  Erro ao alocar memoria!  |" << endl;
        cout << "+---------------------------+" << endl;
    }
    return novo;
}

/* Função que calcula a maior altura entre dois nós */
short maior(short a, short b){
    return (a > b)? a: b;
}

/* Função que retorna a altura de um nó ou -1 caso seja nulo */
short altura_no(NoArv *no){
    if (no == NULL){
        return -1;
    }
    else{
        return no->altura;
    }
    
}
/* Função que calcula o fator de balanceamento de um nó */
short fator_balanceamento(NoArv *no){
    if (no){
        return (altura_no(no->esq) - altura_no(no->dir));
    }
    else{
        return 0;
    }  
}

/* Função para rotação à esquerda */
NoArv* rotacao_esq(NoArv *r){
    NoArv *y, *f;

    y = r->dir;      //y aponta para a subarvore direita da raiz r
    f = y->esq;      // f aponta para o filho esquerdo de y

    y->esq = r;      //o filho esquerdo de y passa a ser a raiz r   
    r->dir = f;      //o filho direito de r passa a ser f
    /* Recalculando a altura dos nós que foram movimentados */
    y->altura = maior(altura_no(r->esq), altura_no(r->dir)) + 1;
    y->altura = maior(altura_no(y->esq), altura_no(y->dir)) + 1;

    return y;
}

/* Função para rotação à direita */

NoArv* rotacao_dir(NoArv *r){
    NoArv *y, *f;

    y = r->esq;
    f = y->dir;

    y->dir = r;
    r->esq = f;

    r->altura = maior(altura_no(r->esq), altura_no(r->dir)) + 1;
    y->altura = maior(altura_no(y->esq), altura_no(y->dir)) + 1;

    return y;
}

/* Função para a rotações duplas */
NoArv* rotacao_esqdir(NoArv *r){
    r->esq = rotacao_esq(r->esq);
    return rotacao_dir(r);
}

NoArv* rotacao_diresq(NoArv *r){
    r->dir = rotacao_dir(r->dir);
    return rotacao_esq(r);
}

/*
    Função para realizar o balanceamento da árvore após uma inserção ou remoção
    Recebe o nó que está desbalanceado e retorna a nova raiz após o balanceamento
*/
NoArv* balancear(NoArv *raiz){
    short fb = fator_balanceamento(raiz);

    // Rotação à esquerda
    if(fb < -1 && fator_balanceamento(raiz->dir) <= 0)
        raiz = rotacao_esq(raiz);

    // Rotação à direita
    else if(fb > 1 && fator_balanceamento(raiz->esq) >= 0)
        raiz = rotacao_dir(raiz);

    // Rotação dupla à esquerda
    else if(fb > 1 && fator_balanceamento(raiz->esq) < 0)
        raiz = rotacao_esqdir(raiz);

    // Rotação dupla à direita
    else if(fb < -1 && fator_balanceamento(raiz->dir) > 0)
        raiz = rotacao_diresq(raiz);

    return raiz;
}

/*
    Insere um novo nó na árvore
    raiz -> raiz da árvore
    carros -> nó a ser inserido
    retorna o endereço do novo nó ou nova raiz após o balanceamento
*/
NoArv* inserir(NoArv *raiz, Info carros){
    if(raiz == NULL){ // árvore vazia
        return novo_no(carros);
    }
    else{ // inserção será à esquerda ou à direita
        if(carros.placa < raiz->car.placa){
            raiz->esq = inserir(raiz->esq, carros);
        }
        else if(carros.placa > raiz->car.placa){
            raiz->dir = inserir(raiz->dir, carros);
        }
        else {
            cout << "+-----------------------------+" << endl;
            cout << "|  O veiculo ja esta existe!  |" << endl;
            cout << "+-----------------------------+" << endl;   
        }
    }

    // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
    raiz->altura = maior(altura_no(raiz->esq), altura_no(raiz->dir)) + 1;

    // verifica a necessidade de rebalancear a árvore
    raiz = balancear(raiz);

    return raiz;
}

/*
    Função para remover um nó da Árvore binária balanceada
    Pode ser necessário rebalancear a árvore e a raiz pode ser alterada
    por isso precisamos retornar a raiz
*/
NoArv* remover_avl(NoArv *raiz, string dado1) {
    if(raiz == NULL){
        cout << "+-------------------------+" << endl;
        cout << "|  Valor nao encontrado!  |" << endl;
        cout << "+-------------------------+" << endl;
        return NULL;
    } 
    else { // procura o nó a remover
        if(raiz->car.placa == dado1) {
            // remove nós folhas (nós sem filhos)
            if(raiz->esq == NULL && raiz->dir == NULL) {
                delete(raiz);               
                cout << "+----------------------------+" << endl;
                cout << "|  Elemento folha removido!  |" << endl;
                cout << "+----------------------------+" << endl;
                return NULL;
            }
            else{
                // remover nós que possuem 2 filhos
                if(raiz->esq != NULL && raiz->dir != NULL){
                    NoArv *aux = raiz->esq;
                    while(aux->dir != NULL)
                        aux = aux->dir;
                    raiz->car.placa = aux->car.placa;
                    aux->car.placa = dado1;
                    raiz->esq = remover_avl(raiz->esq, dado1);
                    return raiz;
                }
                else{
                    // remover nós que possuem apenas 1 filho
                    NoArv *aux;
                    if(raiz->esq != NULL){
                        aux = raiz->esq;
                    }
                    else{
                        aux = raiz->dir;
                    }
                    delete(raiz);
                    cout << "+---------------------------------+" << endl;
                    cout <<"|  Elemento com 1 filho removido!  |" << endl;
                    cout << "+---------------------------------+" << endl;
                    return aux;
                }
            }
        } 
        else {
            if(dado1 < raiz->car.placa){
                raiz->esq = remover_avl(raiz->esq, dado1);
            }
            else{
                raiz->dir = remover_avl(raiz->dir, dado1);
            }
        }

        // Recalcula a altura de todos os nós entre a raiz e o novo nó inserido
        raiz->altura = maior(altura_no(raiz->esq), altura_no(raiz->dir)) + 1;

        // verifica a necessidade de rebalancear a árvore
        raiz = balancear(raiz);

        return raiz;
    }
}

/* Função para imprimir a árvore AVL */
void imprimir_avl(NoArv *raiz, int nivel){
    int i;
    if(raiz){
        imprimir_avl(raiz->dir, nivel + 1);
        cout << "|        Placa: "<< raiz->car.placa << "        |" << endl;   
        imprimir_avl(raiz->esq, nivel + 1);
    }
}

int main(int argc, char** argv) {

    Lista lista;
    int opcao, opcao2;
    No dados;
    string dado1, nomearquivo;

    /* Estruturas da árvore */
    NoArv *raiz = NULL, *busca;
    info carros;

    lista.inicio = NULL;
    lista.tam = 0;

/* Abrindo o arquivo de texto */
    cout << "+------------------------------------+" << endl;
    cout << "| Digite o nome do arquivo de texto: |" << endl;
    cout << "|     (Exemplo: BD_veiculos.txt)     |" << endl;
    cout << "+------------------------------------+" << endl;
    cin >> nomearquivo;

/* Iniciando as estruturas base para inserir como nó */
    ifstream myfile1 (nomearquivo);
    if (myfile1.is_open()){
        while (!myfile1.eof()){
            myfile1 >> dados.modelo;            //Iniciando a estrutura para a lista
            carros.modelo = dados.modelo;       //Iniciando a estrutura para árvore
            myfile1 >> dados.marca;
            carros.marca = dados.marca;
            myfile1 >> dados.tipo;
            carros.tipo = dados.tipo;
            myfile1 >> dados.ano;
            carros.ano = dados.ano;
            myfile1 >> dados.km;
            carros.km = dados.km;
            myfile1 >> dados.potencia;
            carros.potencia = dados.potencia;
            myfile1 >> dados.combustivel;
            carros.combustivel = dados.combustivel;
            myfile1 >> dados.cambio;
            carros.cambio = dados.cambio;
            myfile1 >> dados.direcao;
            carros.direcao = dados.direcao;
            myfile1 >> dados.cor;
            carros.cor = dados.cor;
            myfile1 >> dados.portas;
            carros.portas = dados.portas;
            myfile1 >> dados.placa;
            carros.placa = dados.placa;
            inserirInicio(&lista, &dados);
            raiz = inserir_v1(raiz, carros);
        }
        myfile1.close();
    } else{
        cout << "+---------------------------------+" << endl;
        cout << "|  Falha na abertura do arquivo!  |" << endl;
        cout << "+---------------------------------+" << endl;
        return NULL;
    }

/* Apresentando o menu */
    do{
        cout << "+-------------------+" << endl;
        cout << "|    0 - Sair       |" << endl;
        cout << "|    1 - Inserir    |" << endl;
        cout << "|    2 - Remover    |" << endl;
        cout << "|    3 - Buscar     |" << endl;
        cout << "|    4 - Imprimir   |" << endl;
        cout << "+-------------------+" << endl;
        cin >> opcao;         
        /* Fazendo a leitura do comando */
        switch (opcao){
        /* Se o comando for 0, o programa deve ser encerrado */
        case 0:  
            cout << "+-----------------------+" << endl;        
            cout << "| A lista foi removida! |" << endl;
            cout << "|     Finalizando...    |" << endl;
            cout << "+-----------------------+" << endl;
            encerra_lista(&lista);
            break;   
        /* Se o comando for inserir, o usuário escolhe qual estrutura quer inserir */                
        case 1:
            cout << "+----------------------+" << endl;
            cout << "|  0 - Voltar          |" << endl;
            cout << "|  1 - Lista           |" << endl;
            cout << "|  2 - Arvore Binaria  |" << endl;
            cout << "|  3 - Arvore AVL      |" << endl;
            cout << "+----------------------+" << endl;
            cin >> opcao2;
            /* Nessa opcao, o usuário pode voltar ao menu anterior */  
            if (opcao2 == 0){                         
                break;
            }
            else if (opcao2 == 1 || opcao2 == 2 || opcao2 == 3){
                /* Inserindo na lista encadeada */
                cout << "+--------------------+" << endl;
                cout << "|  Digite o modelo:  |" << endl;
                cout << "+--------------------+" << endl;
                cin >> dados.modelo;
                carros.modelo = dados.modelo;
                cout << "+-------------------+" << endl;
                cout << "|  Digite a marca:  |" << endl;
                cout << "+-------------------+" << endl;
                cin >> dados.marca;
                carros.marca = dados.marca;
                cout << "+------------------+" << endl;
                cout << "|  Digite o tipo:  |" << endl;
                cout << "+------------------+" << endl;
                cin >> dados.tipo;
                carros.tipo = dados.tipo;
                cout << "+-----------------+" << endl;
                cout << "|  Digite o ano:  |" << endl;
                cout << "+-----------------+" << endl;
                cin >> dados.ano;
                carros.ano = dados.ano;
                cout << "+----------------+" << endl;
                cout << "|  Digite a km:  |" << endl;
                cout << "+----------------+" << endl;
                cin >> dados.km;
                carros.km = dados.km;
                cout << "+----------------------+" << endl;
                cout << "|  Digite a potencia:  |" << endl;
                cout << "+----------------------+" << endl;
                cin >> dados.potencia;
                carros.potencia = dados.potencia;
                cout << "+------------------------+" << endl;
                cout << "|  Digite o combustivel: |" << endl;
                cout << "+------------------------+" << endl;
                cin >> dados.combustivel;
                carros.combustivel = dados.combustivel;
                cout << "+--------------------+" << endl;
                cout << "|  Digite o cambio:  |" << endl;
                cout << "+--------------------+" << endl;
                cin >> dados.cambio;
                carros.cambio = dados.cambio;
                cout << "+---------------------+" << endl;
                cout << "|  Digite a direcao:  |" << endl;
                cout << "+---------------------+" << endl;
                cin >> dados.direcao;
                carros.direcao = dados.direcao;
                cout << "+-----------------+" << endl;
                cout << "|  Digite a cor:  |" << endl;
                cout << "+-----------------+" << endl;
                cin >> dados.cor;
                carros.cor = dados.cor;
                cout << "+---------------------+" << endl;
                cout << "|  Digite as portas:  |" << endl;
                cout << "+---------------------+" << endl;
                cin >> dados.portas;
                carros.portas = dados.portas;
                cout << "+-------------------+" << endl;
                cout << "|  Digite a placa:  |" << endl;
                cout << "+-------------------+" << endl;
                cin >> dados.placa;
                carros.placa = dados.placa;
                /* Verificando se o veículo já está na lista */
                if (buscar_placa(&lista, dados) == 0){
                    inserirInicio(&lista, &dados);
                    if (opcao2 == 2 || opcao2 == 1){
                        raiz = inserir_v1(raiz, carros);
                    }
                    else{
                        raiz = inserir(raiz, carros);
                    }
                    break;
                }
                else{
                    cout << "+------------------------+" << endl;
                    cout << "|  O veiculo ja existe!  |" << endl;
                    cout << "+------------------------+" << endl;
                    break;
                }
            }   
            else{
                cout << "+-------------------+" << endl;
                cout << "|  Opcao invalida!  |" << endl;
                cout << "+-------------------+" << endl;
                break;
            }
        /* Realizando a remoção do nó da lista e árvore */     
        case 2:
            cout << "+---------------------------------------------+" << endl;
            cout << "|  Digite a placa do veiculo a ser removido:  |" << endl;
            cout << "+---------------------------------------------+" << endl;
            cin >> dados.placa;     //lendo a placa do nó a ser removido
            dado1 = dados.placa;    
        /* Verificando a existência do veículo */           
            if (buscar_v1(raiz, dado1)){
                remover(&lista, &dados);
                raiz = remover_avl(raiz, dado1);        //Pode ser utilizado na remoção da árvore binária
            }
            else{
                cout << "+------------------------------+" << endl;
                cout << "|  Nenhum veiculo encontrado!  |" << endl;
                cout << "+------------------------------+" << endl;
            }
            break;
        /* Realizando a busca na lista ou árvore */
        case 3:
            cout << "+----------------------+" << endl;
            cout << "|  0 - Voltar          |" << endl;
            cout << "|  1 - Lista           |" << endl;
            cout << "|  2 - Arvore Binaria  |" << endl;
            cout << "|  3 - Arvore AVL      |" << endl;
            cout << "+----------------------+" << endl;   
            cin >> opcao2;     
            if (opcao2 == 0){                
                break;
            }
            /* Realizando a busca na lista */
            else if(opcao2 == 1){
                cout << "+---------------------------------------------+" << endl;
                cout << "|        Digite o dado a ser buscado:         |" << endl;
                cout << "|  (Exemplo: Manual, Hidraulica, Branco etc)  |" << endl;
                cout << "+---------------------------------------------+" << endl;
                cin >> dado1;
                buscar(&lista, dado1);
                break;  
            }
                /* Realizando a busca nas árvores */                                     
            else if (opcao2 == 2 || opcao2 == 3){
                cout << "+--------------------------------------------+" << endl;
                cout << "|  Digite a placa do veiculo a ser buscado:  |" << endl;
                cout << "+--------------------------------------------+" << endl;
                cin >> dado1;
                busca = buscar_v1(raiz, dado1);
                if (busca){
                /* Algumas informações dos veículos não foram exibidas para manter a forma do quadrinho */
                    cout << "+-----------------------------+" << endl;
                    cout << "|     Veiculo encontrado!     |" << endl;
                    cout << "|      Ano:........ " << busca->car.ano << "      |"<< endl;
                    cout << "|      Km:......... " << busca->car.km << "     |"<< endl;
                    cout << "|      Potencia:... " << busca->car.potencia << "       |"<< endl;
                    cout << "|      Portas:..... " << busca->car.portas << "         |"<< endl;
                    cout << "|      Placa:...... " << busca->car.placa << "   |"<< endl;
                    cout << "+-----------------------------+" << endl;
                }
                else{
                    cout << "+------------------------------+" << endl;
                    cout << "|  Nenhum veiculo encontrado!  |" << endl;
                    cout << "+------------------------------+" << endl;
                }
                break; 
            }                       
            else{
                cout << "+-------------------+" << endl;
                cout << "|  Opcao invalida!  |" << endl;
                cout << "+-------------------+" << endl;
                break;
            }
        case 4:
            cout << "+----------------------+" << endl;
            cout << "|  0 - Voltar          |" << endl;
            cout << "|  1 - Lista           |" << endl;
            cout << "|  2 - Arvore Binaria  |" << endl;
            cout << "|  3 - Arvore AVL      |" << endl;
            cout << "+----------------------+" << endl;  
            cin >> opcao2; 
            if (opcao2 == 0){
                /* Voltando ao menu anterior */          
                break;        
            }
            else if(opcao2 == 1){
                imprimir(&lista);
                break;
            }
            else if(opcao2 == 2){
                cout << "+----------------------------------+" << endl;
                cout << "|   Arvore binaria em pre ordem:   |" << endl;
                imprimir_v1(raiz);
                cout << "+----------------------------------+" << endl;
                cout << endl;
                break;
            }
            else if (opcao2 == 3){
                cout << "+------------------------------+" << endl;
                cout << "|   Arvore AVL em pre ordem:   |" << endl;
                imprimir_avl(raiz, 1);
                cout << "+------------------------------+" << endl;
                break;
            }
            else{
                cout << "+-------------------+" << endl;
                cout << "|  Opcao invalida!  |" << endl;
                cout << "+-------------------+" << endl;
                break;
            }
        default:
            cout << "+-------------------+" << endl;
            cout << "|  Opcao invalida!  |" << endl;
            cout << "+-------------------+" << endl;
            break;
        }       
    } while (opcao != 0);    
    
    return 0;
}

