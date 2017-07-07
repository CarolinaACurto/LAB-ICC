



/*Regras:
Há um tabuleiro de 5x5, ou seja, 25 fileiras. Há 3 lixos escondidos. O objetivo do jogo é descobrir onde estão estes lixos e pesca-los para retira-los do oceano.
A cada vez que é “pescado”  uma mensagem indica se você encontrou algum lixo. Caso tenha errado, é dito quantos lixos existem naquela linha e naquela coluna.
O jogo só acaba quando você descobrir e retirar os 3 lixos.

Legenda para o usuário:
~: água no bloco. Ainda não foi lançado o anzol.
*: anzol foi jogado, não há nada ali.
X: anzol foi jogado, havia um lixo ali.

Como jogar:
A cada rodada, digite dois números: o número da linha e o número da coluna onde quer pescar. Depois é só esperar para ver se acertou, ou receber a dica.*/



#include <stdio.h>
#include <stdlib.h>

void inicializaTabuleiro(int tabuleiro[][5]){
    int linha, coluna;
        for(linha=0 ; linha < 5 ; linha++ )
            for(coluna=0 ; coluna < 5 ; coluna++ )
                tabuleiro[linha][coluna]=-1;
}

void mostraTabuleiro(int tabuleiro[][5]){

    int linha, coluna;

        printf("\t1 \t2 \t3 \t4 \t5");
        printf("\n");

        for(linha=0 ; linha < 5 ; linha++ ){
            printf("%d",linha+1);
            for(coluna=0 ; coluna < 5 ; coluna++ ){
                if(tabuleiro[linha][coluna]==-1){
                    printf("\t~");
                }else if(tabuleiro[linha][coluna]==0){
                    printf("\t*");
                }else if(tabuleiro[linha][coluna]==1){
                    printf("\tX");
                }

            }
            printf("\n");
        }

    }


void iniciaLixos(int lixos[][2]){
        srand((unsigned) time(NULL));
        int lixo, anterior;

        for(lixo=0 ; lixo < 3 ; lixo++){
            lixos[lixo][0]= rand()%5;
            lixos[lixo][1]= rand()%5;

            //agora vamos checar se esse par não foi sorteado
            //se foi, so sai do do...while enquanto sortear um diferente
            for(anterior=0 ; anterior < lixo ; anterior++){
                if( (lixos[lixo][0] == lixos[anterior][0])&&(lixos[lixo][1] == lixos[anterior][1]) )
                    do{
                        lixos[lixo][0]= rand()%5;
                        lixos[lixo][1]= rand()%5;
                    }while( (lixos[lixo][0] == lixos[anterior][0])&&(lixos[lixo][1] == lixos[anterior][1]) );
            }
        }
    }

void Pescar(int pesca[2]){

        printf("Linha: ");
        scanf("%d",&pesca[0]);
        pesca[0]--;

        printf("Coluna: ");
        scanf("%d",&pesca[1]);
        pesca[1]--;

}

int acertou(int pesca[2], int lixos[][2]){
    int lixo;

        for(lixo=0 ; lixo < 3 ; lixo++){
            if( pesca[0]==lixos[lixo][0] && pesca[1]==lixos[lixo][1]){
                printf("\nVoce encontrou um lixo em (%d,%d)\n\n",pesca[0]+1,pesca[1]+1);
                return 1;
            }
        }
        return 0;
    }



void dica(int pesca[2], int lixos[][2], int tentativa){
        int linha=0,
            coluna=0,
            fila;

        //conta quantos lixos há na linha pesca[0]
        for(fila=0 ; fila < 3 ; fila++){
            if(lixos[fila][0]==pesca[0])
                linha++;
            if(lixos[fila][1]==pesca[1])
                coluna++;
        }

        printf("\nDica %d: \nlinha %d -> %d lixos\ncoluna %d -> %d lixos\n",tentativa,pesca[0]+1,linha,pesca[1]+1,coluna);
}

void alteraTabuleiro(int pesca[2], int lixos[][2], int tabuleiro[][5]){
        if(acertou(pesca,lixos))
            tabuleiro[pesca[0]][pesca[1]]=1;
        else
            tabuleiro[pesca[0]][pesca[1]]=0;
    }




int main() {
        int tabuleiro[5][5];
        int lixos[3][2];
        int pesca[2];
        int tentativas=0,
            acertos=0;

        inicializaTabuleiro(tabuleiro);
        iniciaLixos(lixos);

        printf("\n");

        do{
            mostraTabuleiro(tabuleiro);
            Pescar(pesca);
            tentativas++;

            if(acertou(pesca,lixos)){
                dica(pesca,lixos,tentativas);
                acertos++;
            }
            else
                dica(pesca,lixos,tentativas);

            alteraTabuleiro(pesca,lixos,tabuleiro);


        }while(acertos!=3);

        printf("\n\n\nJogo terminado. Voce encontrou 3 lixos no oceano em %d tentativas", tentativas);
        printf("\n\n\nVoce tornou o oceano um pouco mais limpo, as tartarugas e baleias agradecem!!!\n\n\n");
        mostraTabuleiro(tabuleiro);

        return 0;
    }
