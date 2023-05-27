/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*
 |           UNIFAL − Universidade Federal de Alfenas.        |
 |             BACHARELADO EM CIENCIA DA COMPUTACAO.          |
 | Trabalho...: Processamento de Imagens com Ponteiros        |
 | Componentes:                                               |
 | 1) Daniel da Costa Lima - R.A.: 2021.1.08.026              |
 | 2) Renan Magalhães Lage - R.A.: 2021.1.08.020              |
 | 3) Vinícius Eduardo de Souza Honório - R.A.: 2021.1.08.024 |
 *−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/
#include <iostream>
#include <fstream>
#include "funcoes.h"

using namespace std;


int main (void){
    
    int lin, col, i, j, tonalidade, *p, *q, *r;
    
    /*Variável para receber a primeira informação do arquivo: */
    string cabecalho;
    
    /*Variável que recebe o nome do arquivo que o usuario quer abrir: */
    string nomeimagem;   
    int mat[600][600];
    
    /*Matriz que servira de reserva para guardar os valores da matriz original
     será usada na função bordas */
    int reserv[600][600];
    
    /*variavel para formar o novo do arquivo
    irá adicionar um adjetivo que represente
    a função no inicio do nome do arquivo*/
    string nomearq; 
    
    /*Variável para receber o número da opção da função 
     desejada pelo usuario*/
    int num; 

    /*Mensagem inicial exibida para a leitura do nome do arquivo que deseja ser aberto*/
    cout << "+-------------------------------------------+" << endl;
    cout << "| Digite o nome da imagem que deseja abrir: |" <<endl;
    cout << "| EX: imagem.pgm                            |"<<endl;
    cout << "+-------------------------------------------+" << endl;
    /*O nome da imagem deverá conter o formato da imagem como indicado no exemplo*/
    cin >> nomeimagem ;

    ifstream myfile1 (nomeimagem);
    if (myfile1.is_open()){
        while (!myfile1.eof() ){
            myfile1 >> cabecalho;
            myfile1 >> col;
            myfile1 >> lin;
            myfile1 >> tonalidade;
            if (lin < 1 or col < 1){
                cout << "Erro: dimensões não formam matriz" <<endl;
                return -1;
            }
            p = &mat[0][0];
            q = &reserv[0][0];
            for (int i = 0; i < lin; i++){
                for (int j = 0; j < col; j++){
                    myfile1 >> *p;
                    /*Atribuição feita para a atribuição de valor da matriz reserva*/
                    *q = *p;
                    q++;                            
                    p++;
                }
                cout << endl;
            }
        }
    }

    /*Menu de opções das funções*/
    cout << "+--------------------------------------+" << endl;
    cout << "|                MENU                  |" << endl;
    cout << "|          ESCOLHA UMA OPÇÃO           |" << endl;
    cout << "+--------------------------------------+" << endl;
    cout << "| 1 - Imagem Negativa                  |" << endl;
    cout << "| 2 - Rotacionar Imagem Para Esquerda  |" << endl;
    cout << "| 3 - Rotacionar Imagem Para Direita   |" << endl;
    cout << "| 4 - Inverter Verticalmente           |" << endl;
    cout << "| 5 - Inverter Horizontalmente         |" << endl;
    cout << "| 6 - Escurecer Bordas                 |" << endl;
    cout << "| 7 - Clarear a Imagem                 |" << endl;
    cout << "| 8 - Escurecer a Imagem               |" << endl;
    cout << "| 0 - Sair                             |" << endl;
    cout << "+--------------------------------------+" << endl;

    do{
        cout << "Digite a opção desejada : " << endl;
        scanf("%d", &num);

        /*Caso o usuario digitar algum número que esta fora das 
        opções exibe a seguinte mensagem:*/
        if ( num < 0 || num > 8){
            cout << "ATENÇÃO - Digite um número que esteja entre as opções: " << endl;
            scanf("%d", &num);
        }

        /*Caso digitar ZERO o programa ira ser 
        fechado e exibira a seguinte mensagem:*/ 
        if ( num == 0){
            cout << "+------------------+" << endl;
            cout << "|       EXIT       |" << endl;
            cout << "+------------------+" << endl;
        }

        //1 - Imagem Negativa
        if ( num == 1){
            cout <<"Opção 1 selecionada - Função Negativa"<<endl;
            nomearq = "Negativo" + nomeimagem;
            negativo(nomearq, cabecalho, lin, col, tonalidade, mat);
        }

        //2 - Rotacionar Imagem Para Esquerda
        if ( num == 2){
            cout<<"Opção 2 selecionada - Função Rotacionar para a Esquerda"<<endl;
            nomearq = "Esquerda" + nomeimagem;
            esquerda(nomearq, cabecalho, lin, col, tonalidade, mat);
        }

        //3 - Rotacionar Imagem Para Direita
        if ( num == 3){
            cout<<"Opção 3 selecionada- Função Rotacionar para a Direita"<<endl;
            nomearq = "Direita" + nomeimagem;
            direita(nomearq, cabecalho, lin, col, tonalidade, mat);
        }

        //4 - Inverter Verticalmente
        if ( num == 4){
            cout<< "Opção 4 selecionada - Função Inverter Verticalmente"<<endl;
            nomearq = "Vertical" + nomeimagem;
            inversaov(nomearq, cabecalho, lin, col, tonalidade, mat);
        }

        //5 - Inverter Horizontalmente
        if ( num == 5){
            cout<<"Opção 5 selecionada- Função Inverter Horizontalmente"<<endl;
            nomearq = "Horizontal" + nomeimagem;
            inversaoh(nomearq, cabecalho, lin, col, tonalidade, mat);
        }

        //6 - Escurecer Bordas
        if ( num == 6){
            cout<< "Opção 6 selecionada - Função Escurecer Bordas"<<endl;
            nomearq = "Bordas" + nomeimagem;
            bordas(nomearq, cabecalho, lin, col, tonalidade, reserv);
        }

        //7 - Clarear a Imagem
        if ( num == 7){
            cout<<"Opção 7 selecionada - Função Clarear Imagem"<<endl;
            nomearq = "Clarear" + nomeimagem;
            clarear(nomearq, cabecalho, lin, col, tonalidade, mat);
        }

        //8 - Escurecer a Imagem
        if( num == 8){
            cout<<"Opção 8 selecionada - Função Escurecer Imagem"<<endl;
            nomearq = "Escurecer" + nomeimagem;
            escurecer(nomearq, cabecalho, lin, col, tonalidade, mat);
        }

    }while (num != 0);
    

    return 0;
}