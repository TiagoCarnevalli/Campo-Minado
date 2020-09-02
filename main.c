/*
Instuções de Montagem do Jogo
    1 -Contruir o Campo Minado:
        1.1Definir um campo como uma matriz 30x30 de caracteres
        1.2 - Obter do usuário:
            1.2.1 - Quantidade de linhas
            1.2.2 - Quantidade de colunas
                *Tratativa de erro (Negar uma entrada que não seja suportada)
                2<= Linhas/Colunas <=30

    2 - Lançar bombas
        2.1 - O usuário define o nível do jogo
            Fácil: 25%
            Médio: 50%
            Difícil: 75%
        2.2 - Definir posição aleatória

        2.3 - Se campo [PosAleatLinha] [PosAleatColuna] == '*', repetir processo 2.2
              Senão, marca * no campo
            (Repetir x vezes, dependendo da quantidade de bombas)
    3 - Lançar os números
        3.1 - Se bomba -> Pula célula
              Senão, segue para 3.2
        3.2 - Para cada posição deve-se contar a quantidade de bombas das células adjacentes
              (Fazer o relógio)
    4 - Jogar
        4.1 - Definir uma nova matriz 30x30 e preencher com '-' (Matriz Tela)
        4.2 - Mostrar Tela nas dimensões escolhidas com legenda de linha e coluna
        4.3 - Usuário escolhe linha e coluna
            Se linha e coluna estão nas dimensões da Tela
                Se Campo [Linha] [Coluna]=='*'
                    Game Over
                Senão
                    Se Tela [Linha] [Coluna]=='-'
                        Copio de Campo para Tela na mesma posição
                        Conta Jogadas ++
                        Se Conta Jogadas == Total de Casas([Linhas]*[Colunas])-Quantidade de Conta Bombas
                            Parabéns
                        Senão
                    Senão
                        Jogada já realizada
            Senão, indicar posição inválida
*/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <time.h>

#define TAM 25

void definirDimensoes(int *pdimL, int *pdimC)
{
    do
    {
        printf("\n Entre com a quantidade de linhas do seu campo (>=2 e <=%i): ",TAM);
        scanf("%d",pdimL);
        fflush(stdin);
        system("cls");
        if(*pdimL<2 || *pdimL>TAM)
        {
            printf("\n Quantidade de linhas inválidas! Tente novamente...");
            fflush(stdin);
            getchar();
            system("cls");
        }
    }
    while(*pdimL<2 || *pdimL>TAM);
    do
    {
        printf("\n Entre com a quantidade de colunas do seu campo (>=2 e <=%i): ",TAM);
        scanf("%d",pdimC);
        fflush(stdin);
        system("cls");
        if(*pdimC<2 || *pdimC>30)
        {
            printf("\n Quantidade de colunas inválidas! Tente novamente...");
            fflush(stdin);
            getchar();
            system("cls");
        }
    }
    while(*pdimC<2 || *pdimC>TAM);
}

void mostrarCampo(char campo[TAM][TAM], int dimL, int dimC)
{
    int l,c;
    //Imprimir legenda da coluna
    printf("\n    ");
    for(c=1; c<=dimC; c++)
    {
        printf("%2i ",c);
    }
    printf("\n");
    //Imprimir células da matriz
    for(l=0; l<dimL; l++)
    {
        printf(" ");
        printf("%2i ",l+1);
        for(c=0; c<dimC; c++)
        {
            printf(" %c ", campo[l][c]);
        }
        printf("\n");
    }
}

void limparCampo(char campo[TAM][TAM])
{
    int l,c;
    for(l=0; l<TAM; l++)
    {
        for(c=0; c<TAM; c++)
        {
            campo[l][c]='?';
        }
    }
    /*Solução 2
    int estaDentroIntervalo(int num, int min, int max)
    {
        if (num>=min && num<=max)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }*/
}

int definirNivel()
{
    int nivel=0;
    while(nivel<1||nivel>3)
    {
        printf("\n Níveis de jogo: ");
        printf("\n 1 - Fácil");
        printf("\n 2 - Médio");
        printf("\n 3 - Difícil");
        printf("\n Escolha o nível que deseja jogar: ");
        scanf("%d",&nivel);
        //Solução 1
        if(nivel<1||nivel>3)
        {
            printf("\nNível inválido. Tente novamente...");
            fflush(stdin);
            getchar();
            system("cls");
        }
    }
    return nivel;

    /*Solucão 2
    int estaDentroIntervalo(int num,int min, int max)
    {
        if(num>=min&&num<=max)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }*/
}

void calcularQtdBombas(int dimL, int dimC,float *qtdBombas)
{
    float percBombas;
    switch(definirNivel())
    {
    case 1:
        percBombas=0.25;
        break;
    case 2:
        percBombas=0.5;
        break;
    case 3:
        percBombas=0.75;
        break;
    }
    *qtdBombas=roundf((dimL*dimC)*percBombas);
    printf("\n Seu jogo terá %.0f bombas.\n",*qtdBombas);
}

void posicionarBombas(char campo[TAM][TAM],float qtdBombas,int dimL,int dimC)
{
    srand(time(NULL));
    int l,c,i;
    for(i=0; i<qtdBombas; i++)
    {
        l=rand()%dimL;
        c=rand()%dimC;
        if(campo[l][c]=='*')
        {
            i--;
        }
        campo[l][c]='*';
    }
}

void posicionarNumeros(char campo[TAM][TAM],int dimL,int dimC)
{
    int l,c,contaBombas=0;
    for(l=0; l<dimL; l++)
    {
        for(c=0; c<dimC; c++)
        {
            contaBombas=0;
            //Fazer o "Relógio" (senão for bomba)
            if(campo[l][c]=='?')
            {
                if((campo[l-1][c]=='*')&&(l-1>=0))
                {
                    contaBombas++;
                }
                if((campo[l-1][c+1]=='*')&&(l-1>=0)&&(c+1<dimC))
                {
                    contaBombas++;
                }
                if((campo[l][c+1]=='*')&&(c+1<dimC))
                {
                    contaBombas++;
                }
                if((campo[l+1][c+1]=='*')&&(l+1<dimL)&&(c+1<dimC))
                {
                    contaBombas++;
                }
                if((campo[l+1][c]=='*')&&(l+1<dimL))
                {
                    contaBombas++;
                }
                if((campo[l+1][c-1]=='*')&&(l+1<dimL)&&(c-1>=0))
                {
                    contaBombas++;
                }
                if((campo[l][c-1]=='*')&&(c-1>=0))
                {
                    contaBombas++;
                }
                if((campo[l-1][c-1]=='*')&&(l-1>=0)&&(c-1>=0))
                {
                    contaBombas++;
                }
                //Preencher o número
                campo[l][c]=contaBombas+48; //Conversão de int para char usando tabela ASCII
            }
        }
    }
}

void explodir(char tela[TAM][TAM],char campo[TAM][TAM],int dimL,int dimC)
{
    //"Explodir" os números 0 até encontrar um número maior
    int l,c,i;
    for(i=0; i<dimL*dimC; i++)
    {
        for(l=0; l<dimL; l++)
        {
            for(c=0; c<dimC; c++)
            {
                if(tela[l][c]=='0')
                {
                    if(l-1>=0)
                    {
                        tela[l-1][c]=campo[l-1][c];
                    }
                    if((l-1>=0)&&(c+1<dimC))
                    {
                        tela[l-1][c+1]=campo[l-1][c+1];
                    }
                    if(c+1<dimC)
                    {
                        tela[l][c+1]=campo[l][c+1];
                    }
                    if((l+1<dimL)&&(c+1<dimC))
                    {
                        tela[l+1][c+1]=campo[l+1][c+1];
                    }
                    if(l+1<dimL)
                    {
                        tela[l+1][c]=campo[l+1][c];
                    }
                    if((l+1<dimL)&&(c-1>=0))
                    {
                        tela[l+1][c-1]=campo[l+1][c-1];
                    }
                    if(c-1>=0)
                    {
                        tela[l][c-1]=campo[l][c-1];
                    }
                    if((l-1>=0)&&(c-1>=0))
                    {
                        tela[l-1][c-1]=campo[l-1][c-1];
                    }
                }
            }
        }
    }
}

void jogar(char tela[TAM][TAM],char campo[TAM][TAM],int dimL,int dimC,int qtdBombas)
{
    int lj,cj,j,l,c,p,i;
    //O jogador deve escolher uma posição no campo
    for(j=dimL*dimC-qtdBombas; j>0; j--)
    {
        do
        {
            mostrarCampo(tela,dimL,dimC);
            printf("\n Escolha a posição que deseja marcar ");
            printf("\n Linha:");
            scanf("%d",&lj/*,&cj*/);
            printf(" Coluna: ");
            scanf("%d",&cj);
            fflush(stdin);
            system("cls");
            if(lj<=0||lj>dimL||cj<=0||cj>dimC)
            {
                printf("\n Posição inválida. Tente novamente...");
                j++;
            }
        }
        while(lj<=0||lj>dimL||cj<=0||cj>dimC);
        lj--;
        cj--;
        //Verificar se a posição já não foi jogada
        if(tela[lj][cj]=='?')
        {
            tela[lj][cj]=campo[lj][cj];
            if(tela[lj][cj]=='*')
            {
                mostrarCampo(tela,dimL,dimC);
                printf("\n BUUUMM!!\n");
                printf("\n GAME OVER!\n");
                break;
            }
            /*if(tela[lj][cj]=='*')
            {
                printf("\n GAME OVER!");
                return 0;
            }*/
        }
        else
        {
            printf("\n Esta posição já foi marcada. Tente novamente...");
            j--;
        }
        explodir(tela,campo,dimL,dimC);
        /*if(j==0)
        {
            mostrarCampo(tela,dimL,dimC);
            printf("\n Parabéns! Você ganhou!!\n");
        }*/
        for(i=0; i<1; i++)
        {
            p=0;
            for(l=0; l<dimL; l++)
            {
                for(c=0; c<dimC; c++)
                {
                    if(tela[l][c]=='?')
                    {
                        p++;
                    }
                }
            }
            if(p==qtdBombas)
            {
                printf("\n Parabéns! Você ganhou!!\n");
                break;
            }
        }
    }
}

int main()
{
    //Configura o software para português, permitindo usar acentos.
    setlocale(LC_CTYPE,"Portuguese");
    char campo[TAM][TAM],tela[TAM][TAM];
    int dimL, dimC;
    float qtdBombas=0;
    //1º Passo: Usuário escolhe dimensões.
    definirDimensoes(&dimL,&dimC);
    printf("\n Campo com dimensões %d x %d\n\n",dimL,dimC);
    //2º Passo: Calcular quantidade de bombas
    calcularQtdBombas(dimL,dimC,&qtdBombas);
    //3º Passo: Limpar campo colocando "?"
    limparCampo(campo);
    //mostrarCampo(campo,dimL,dimC);
    //4º Passo: Posicionar as minas no campo
    posicionarBombas(campo,qtdBombas,dimL,dimC);
    //mostrarCampo(campo,dimL,dimC);
    //5º Passo: Posicionar números
    posicionarNumeros(campo,dimL,dimC);
    //mostrarCampo(campo,dimL,dimC);
    //6º Passo: Limpar a matriz tela
    limparCampo(tela);
    //mostrarCampo(tela,dimL,dimC);
    //7º Passo: Jogar
    jogar(tela,campo,dimL,dimC,qtdBombas);
    return 0;
}
