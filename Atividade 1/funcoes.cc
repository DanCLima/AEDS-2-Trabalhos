#include <iostream>
#include <fstream>

using namespace std;

/* Matriz que irá auxiliar na função de rotacionar para a esquerda*/
int esq[600][404];

/* Matriz que irá auxiliar na função de inverter a imagem*/
int mat2[600][600];

int *m, *q, *r;

/*Auxiliar para controlar a estrutura de repetição 
 da função escurecer bordas */
int aux;

/* Imagem Negativa */
void negativo (string nomearq, string cabecalho, int lin, int col, int tonalidade, int mat[600][600]){
    m = &mat[0][0];
    ofstream myfile2;
    myfile2.open (nomearq);
        if (myfile2.is_open()){
            myfile2 << cabecalho << endl;
            myfile2 << col << " " << lin << endl;
            myfile2 << tonalidade << endl;
            for (int i = 0; i< lin; i++){
                for (int j = 0; j < col; j++){
                    myfile2 << (255 - *m) << " ";
                    m++;         
                }
                myfile2 << endl;
            }
            cout << endl;
            myfile2.close();
        }
        else
            cout << "Unable to open file";

}

/* Clarear a Imagem */
void clarear(string nomearq, string cabecalho, int lin, int col, int tonalidade, int mat[600][600]){
    m = &mat[0][0];
    ofstream myfile3;
    myfile3.open (nomearq);
    if (myfile3.is_open()){
        myfile3 << cabecalho << endl;
        myfile3 << col << " " << lin << endl;
        myfile3 << tonalidade << endl;
        for (int i = 0; i< lin; i++){
            for (int j = 0; j < col; j++){
                /*Ao multiplicar por 70 estaremos deixando os valores da imagem 
                 mais próximo da tonalidade branca, logo, estaremos clareando a imagem*/
                if ( (70 + *m) > 255){
                    /*Caso a multiplicação resulte em um número maior que 255 que
                     é a tonalidade máxima, colocaremos 255 no lugar do resultado
                     da multiplicação*/
                    myfile3 << 255 << " ";
                }
                else{
                    myfile3 << (70 + *m) << " ";   
                }
                m++;         
            }
            myfile3 << endl;
        }
        cout << endl;
        myfile3.close();
    }
    else
        cout << "Unable to open file";
}

/* Rotação para a Esquerda */
void esquerda(string nomearq, string cabecalho, int lin, int col, int tonalidade, int mat[600][600]){
    m = &mat[0][0];
    ofstream myfile4;
    myfile4.open (nomearq);
    if (myfile4.is_open()){
        myfile4 << cabecalho << endl;
        myfile4 << lin << " " << col << endl;
        myfile4 << tonalidade << endl;
        /*O ponteiro r irá servir para a mudança de coluna, enquanto o ponteiro q
         servirá para percorrer a coluna*/
        for(r = &esq[col-1][0]; r <= &esq[col-1][lin-1]; r++){
            for(q = r; q >= &esq[0][0]; q = q - lin){ 
                *q = *m;
                m++;
            }           
        }
        /*Colocando os Valores no Arquivo*/
        for (int i = 0; i< lin; i++){
            for (int j = 0; j < col; j++){
                myfile4 << *q << endl;
                q++;         
            }
            myfile4 << endl;
        }

        cout << endl;
        myfile4.close();
    }
    else
        cout << "Unable to open file";
}


/* Inversão horizontal */
void inversaoh (string nomearq, string cabecalho, int lin, int col, int tonalidade, int mat[600][600]){
    /*O ponteiro "m" aponta para o endereço do primeiro elemento da matriz principal*/
    m = &mat[0][0];                 
    ofstream myfile5;
    myfile5.open (nomearq);
    if (myfile5.is_open()){                 
        myfile5 << cabecalho << endl;           
        myfile5 << col << " " << lin << endl;
        myfile5 << tonalidade << endl;
        /*O ponteiro "m" aponta para o endereço do último elemento da primeira 
        linha da matriz que contém a imagem. 
        O "(col-1)" retira a casa em excesso obtida na adição da posição inicial 
        mais a quantidade de colunas total (devido ao primeiro índice mat[0][0])*/
        m = m + (col-1);
        /*O ponteiro "q" aponta para o endereço do primeiro elemento da matriz 2*/
        q = &mat2[0][0];            
        for (int i = 0; i < lin; i++){
            for (int j = 0; j < col; j++){
                /*A cada passo na matriz principal, o conteúdo de "q" receberá o conteúdo de "m". 
                Assim, cada linha da matriz principal será reescrita de trás para frente na matriz 2*/
                *q = *m;            
                myfile5 << *q << " ";
                /*O ponteiro "q" será incrementado a cada repetição, pois percorre a matriz 2 de forma continua*/
                q++;
                /*O ponteiro "m" precisa ser decrementado a cada repetição, 
                 pois percorre as linhas da matriz principal de trás para frente.*/
                m--;                
            }
            myfile5 << endl;
            /*Ao percorrer todos os elementos de uma linha, o ponteiro "m" 
              será redirecionado para o endereço do último elemento da próxima 
              linha na matriz principal*/
            m = m + (2 * col);      
        }
        cout << endl;
        myfile5.close();
    } 
    else {
        cout << "Nao foi possivel gerar o arquivo";
    }        
}

/* Inversão vertical */
void inversaov (string nomearq, string cabecalho, int lin, int col, int tonalidade, int mat[600][600]){
    m = &mat[0][0];
    ofstream myfile6;
    myfile6.open (nomearq);
    if (myfile6.is_open()){                 
        myfile6 << cabecalho << endl;           
        myfile6 << col << " " << lin << endl;
        myfile6 << tonalidade << endl;
        /*O ponteiro "m" está apontando para o endereço do 
        primeiro elemento da última linha da matriz principal*/
        m = m + (lin * col) - col;          
        q = &mat2[0][0]; 
        for (int i = 0; i < lin; i++){
            for (int j = 0; j < col; j++){
                /*A cada iteração, o conteúdo de "q" receberá o conteúdo de "m". 
                Dessa forma, as linhas da matriz principal 
                serão reescritas na ordem contrária na matriz 
                2, ou seja, de baixo para cima*/
                *q = *m;                    
                myfile6 << *q << " ";    
                q++;                        
                /*O ponteiro "q" será incrementado a cada repetição, 
                pois percorre cada linha da matriz 2 de forma continua*/
                m++;                        
                /*O ponteiro "m" também será incrementado a cada repetição, 
                pois percorre a matriz principal de forma continua*/
            }
            myfile6 << endl;
            m = m - (2 * col);              
            /*Ao percorrer todos os elementos de cada linha, 
            o ponteiro "m" precisa ser redirecionado ao endereço do 
            primeiro elemento da linha anterior na matriz principal*/
        }
        cout << endl;
        myfile6.close();
    } 
    else { 
        cout << "Nao foi possivel gerar o arquivo";
    }        
}

/* Escurecer a imagem */
void escurecer (string nomearq, string cabecalho, int lin, int col, int tonalidade, int mat[600][600]){
    m = &mat[0][0];
    ofstream myfile7;
    myfile7.open (nomearq);
    if (myfile7.is_open()){
        myfile7 << cabecalho << endl;
        myfile7 << col << " " << lin << endl;
        myfile7 << tonalidade << endl;
        for (int i = 0; i< lin; i++){
            for (int j = 0; j < col; j++){
                /*Condicional que verifica se a tonalidade do conteúdo apontado por "m", 
                decrementado em 80 tons, é menor ou igual a zero*/
                if ((*m - 80) <= 0){
                    /*Caso a condição seja verdadeira, o conteúdo do arquivo, 
                    nesse instante, receberá o valor "0", que representa a 
                    tonalidade mais escura*/
                    myfile7 << 0 << " ";    
                }
                else{
                    /*Se a condição for falsa, o conteúdo apontado por "m" 
                    será decrementado em 80 tons, tornanando-se mais escuro*/
                    myfile7 << (*m - 80) << " ";    
                }
                m++;         
            }
            myfile7 << endl;
        }
        cout << endl;
        myfile7.close();
    }
    else{
        cout << "Nao foi possivel gerar o arquivo";
    }
}

/* Rotação para a Direita */ 
void direita (string nomearq, string cabecalho, int lin, int col, int tonalidade, int mat[600][600]){
    m = &mat[0][0];
    ofstream myfile8;
    myfile8.open (nomearq);
    if (myfile8.is_open()){
        myfile8 << cabecalho << endl;
        myfile8 << lin << " " << col << endl;
        myfile8 << tonalidade << endl;
	for(int i = 0; i < col; i++){
            /* i = Controla a iteração do deslocamento horizontal (esquerda para direita)*/
            for(q = m+(600 * (lin - 1) + i); q >= m+i; q = q - 600){
                /* q = Controla a iteração do deslocamento vertical (baixo para cima)*/
		myfile8 << *q << " ";
                /* A ordem de leitura dos píxeis foi alterada de modo a imprimir-se a imagem já rotacioanda*/
            }
        }
        cout << endl;
        myfile8.close();
    }
    else
        cout << "Unable to open file";
}

/* Escurecer bordas */
void bordas(string nomearq, string cabecalho, int lin, int col, int tonalidade, int mat[600][600]){
    m = &mat[0][0];
    ofstream myfile9;
    myfile9.open (nomearq);
    if (myfile9.is_open()){
        myfile9 << cabecalho << endl;
        myfile9 << col << " " << lin << endl;
        myfile9 << tonalidade << endl;
        for(aux = 0; aux < 16; aux++){
            /* aux = Controla a iteração de cada camada da borda
             aux adicionalmente foi usada para o cálculo do escurecimento (maior aux, menor escurecimento)
             Finalmente, aux também foi usada para auxiliar no controle das iterações na sequência*/
            for(r = m+(600 * aux + aux); r < m+(600 * aux + col-aux); r++){
                /* r = Controla a iteração da borda (esquerda para direita)*/
                /* Escurecimento do Topo */
                *r = *r - ((16-aux) * tonalidade/16);
                if(*r < 0)
                    *r = 0;
            }
            for(r = m+(600 * aux + col-aux+600-1); r < m+(600 * (lin-aux) + col-aux-1); r = r+600){
                /* r = Controla a iteração da borda (cima para baixo)*/
                /* Escurecimento da Lateral Direita */
                *r = *r - ((16-aux) * tonalidade/16);
                if(*r < 0)
                    *r = 0;
            }
            for(r = m+(600 * (lin-aux) + col-aux-1-1); r >= m+(600 * (lin-aux) + aux); r--){
                /* r = Controla a iteração da borda (direita para esquerda)*/
                /* Escurecimento da Base */
                *r = *r - ((16-aux) * tonalidade/16);
                if(*r < 0)
                    *r = 0;
            }
            for(r = m+(600 * (lin-aux-1) + aux); r > m+(600 * aux + aux); r = r - 600){
                /* r = Controla a iteração da borda (baixo para cima)*/
                /* Escurecimento da Lateral Esquerda*/
                *r = *r - ((16-aux) * tonalidade/16);
                if(*r < 0)
                    *r = 0;
            }
        }
        
        /* Escrita no Arquivo*/
        for(r = m; r < m+(600 * lin); r = r+600-col){
            /* r = Controla a iteração dos píxeis a serem escritos 
            (esquerda para direita, cima para baixo)*/
            for(q = r+col; r < q; r++)
                /* q = Auxilia no controle da iteração, limitando o 
                 incremento de 'r' até o final da linha*/
                myfile9 << *r << " ";
        }
        cout << endl;
        myfile9.close();
    }
    else
        cout << "Unable to open file";
}