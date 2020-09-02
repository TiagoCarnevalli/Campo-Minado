/*
Instu��es de Montagem do Jogo
    1 -Contruir o Campo Minado:
        1.1Definir um campo como uma matriz 30x30 de caracteres
        1.2 - Obter do usu�rio:
            1.2.1 - Quantidade de linhas
            1.2.2 - Quantidade de colunas
                *Tratativa de erro (Negar uma entrada que n�o seja suportada)
                2<= Linhas/Colunas <=30

    2 - Lan�ar bombas
        2.1 - O usu�rio define o n�vel do jogo
            F�cil: 25%
            M�dio: 50%
            Dif�cil: 75%
        2.2 - Definir posi��o aleat�ria

        2.3 - Se campo [PosAleatLinha] [PosAleatColuna] == '*', repetir processo 2.2
              Sen�o, marca * no campo
            (Repetir x vezes, dependendo da quantidade de bombas)
    3 - Lan�ar os n�meros
        3.1 - Se bomba -> Pula c�lula
              Sen�o, segue para 3.2
        3.2 - Para cada posi��o deve-se contar a quantidade de bombas das c�lulas adjacentes
              (Fazer o rel�gio)
    4 - Jogar
        4.1 - Definir uma nova matriz 30x30 e preencher com '-' (Matriz Tela)
        4.2 - Mostrar Tela nas dimens�es escolhidas com legenda de linha e coluna
        4.3 - Usu�rio escolhe linha e coluna
            Se linha e coluna est�o nas dimens�es da Tela
                Se Campo [Linha] [Coluna]=='*'
                    Game Over
                Sen�o
                    Se Tela [Linha] [Coluna]=='-'
                        Copio de Campo para Tela na mesma posi��o
                        Conta Jogadas ++
                        Se Conta Jogadas == Total de Casas([Linhas]*[Colunas])-Quantidade de Conta Bombas
                            Parab�ns
                        Sen�o
                    Sen�o
                        Jogada j� realizada
            Sen�o, indicar posi��o inv�lida
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
            printf("\n Quantidade de linhas inv�lidas! Tente novamente...");
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
            printf("\n Quantidade de colunas inv�lidas! Tente novamente...");
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
    //Imprimir c�lulas da matriz
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
    /*Solu��o 2
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
        printf("\n N�veis de jogo: ");
        printf("\n 1 - F�cil");
        printf("\n 2 - M�dio");
        printf("\n 3 - Dif�cil");
        printf("\n Escolha o n�vel que deseja jogar: ");
        scanf("%d",&nivel);
        //Solu��o 1
        if(nivel<1||nivel>3)
        {
            printf("\nN�vel inv�lido. Tente novamente...");
            fflush(stdin);
            getchar();
            system("cls");
        }
    }
    return nivel;

    /*Soluc�o 2
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
    printf("\n Seu jogo ter� %.0f bombas.\n",*qtdBombas);
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
            //Fazer o "Rel�gio" (sen�o for bomba)
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
                //Preencher o n�mero
                campo[l][c]=contaBombas+48; //Convers�o de int para char usando tabela ASCII
            }
        }
    }
}

void explodir(char tela[TAM][TAM],char campo[TAM][TAM],int dimL,int dimC)
{
    //"Explodir" os n�meros 0 at� encontrar um n�mero maior
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
    //O jogador deve escolher uma posi��o no campo
    for(j=dimL*dimC-qtdBombas; j>0; j--)
    {
        do
        {
            mostrarCampo(tela,dimL,dimC);
            printf("\n Escolha a posi��o que deseja marcar ");
            printf("\n Linha:");
            scanf("%d",&lj/*,&cj*/);
            printf(" Coluna: ");
            scanf("%d",&cj);
            fflush(stdin);
            system("cls");
            if(lj<=0||lj>dimL||cj<=0||cj>dimC)
            {
                printf("\n Posi��o inv�lida. Tente novamente...");
                j++;
            }
        }
        while(lj<=0||lj>dimL||cj<=0||cj>dimC);
        lj--;
        cj--;
        //Verificar se a posi��o j� n�o foi jogada
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
            printf("\n Esta posi��o j� foi marcada. Tente novamente...");
            j--;
        }
        explodir(tela,campo,dimL,dimC);
        /*if(j==0)
        {
            mostrarCampo(tela,dimL,dimC);
            printf("\n Parab�ns! Voc� ganhou!!\n");
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
                printf("\n Parab�ns! Voc� ganhou!!\n");
                break;
            }
        }
    }
}

int main()
{
    //Configura o software para portugu�s, permitindo usar acentos.
    setlocale(LC_CTYPE,"Portuguese");
    char campo[TAM][TAM],tela[TAM][TAM];
    int dimL, dimC;
    float qtdBombas=0;
    //1� Passo: Usu�rio escolhe dimens�es.
    definirDimensoes(&dimL,&dimC);
    printf("\n Campo com dimens�es %d x %d\n\n",dimL,dimC);
    //2� Passo: Calcular quantidade de bombas
    calcularQtdBombas(dimL,dimC,&qtdBombas);
    //3� Passo: Limpar campo colocando "?"
    limparCampo(campo);
    //mostrarCampo(campo,dimL,dimC);
    //4� Passo: Posicionar as minas no campo
    posicionarBombas(campo,qtdBombas,dimL,dimC);
    //mostrarCampo(campo,dimL,dimC);
    //5� Passo: Posicionar n�meros
    posicionarNumeros(campo,dimL,dimC);
    //mostrarCampo(campo,dimL,dimC);
    //6� Passo: Limpar a matriz tela
    limparCampo(tela);
    //mostrarCampo(tela,dimL,dimC);
    //7� Passo: Jogar
    jogar(tela,campo,dimL,dimC,qtdBombas);
    return 0;
}
