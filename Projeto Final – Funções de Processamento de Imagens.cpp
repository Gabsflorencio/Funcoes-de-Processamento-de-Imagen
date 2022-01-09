//MADSON GARCIA DA SILVA
//GABRIEL FLORENCIO DE ALMEIDA

#include<iostream>
#include<fstream>
#include<cstring>

using namespace std;

const int MAX = 512;
const int RGB = 3;

struct img
{

    int linha;
    int coluna;
    int mat[RGB][MAX][MAX];

};

bool abre_img(char nome[], img& imagem);
void salva_img(char nome[], img img);

void converte_para_cinza(img img_in, img& img_out);
void filt_dilatacao(img img_in, img& img_out);
void reflete(img img_in, img& img_out);
void equaliza_histograma(img img_in, img& img_out);


int main()
{
    char nome[MAX], novo_nome[MAX];
    img imagem, saida;
    int filtro = -1;

    cout << "1. Tons de cinza\n";
    cout << "2. Filtrar por dilatacao\n";
    cout << "3. Reflexao horizontal\n";
    cout << "4. Histograma\n\n";
    cout << "0. Sair\n";
    cout << endl;

    while(filtro != 0)
    {

        cout << "Escolha o filtro:\n";
        cin >> filtro;
        cout << endl;



        while(filtro > 4)
        {
            cout << "Opcao invalida, escolha novamente:\n";
            cin >> filtro;
        }

        if(filtro == 1)
        {
            cout << "Tons de cinza\n";
            cout << "Insira o nome do arquivo:\n";
            cin >> nome;
            cout << endl;

            while(!abre_img(nome, imagem))
            {
                cout << "O arquivo de imagem nao eh compativel ou nao existe\n";
                cout << "Insira novamente o nome do arquivo:\n";
                cin >> nome;
                cout << endl;
            }

            converte_para_cinza(imagem, saida);

            cout << "Insira o novo nome:\n";
            cin >> novo_nome;

            salva_img(novo_nome, saida);


        }

        if(filtro == 2)
        {
            cout << "Filtrar por dilatacao\n";
            cout << "Insira o nome da imagem:\n";
            cin >> nome;
            cout << endl;

            while(!abre_img(nome, imagem))
            {
                cout << "O arquivo de imagem nao eh compativel ou nao existe\n";
                cout << "Insira novamente o nome do arquivo:\n";
                cin >> nome;
                cout << endl;
            }

            filt_dilatacao(imagem, saida);

            cout << "Insira o novo nome:\n";
            cin >> novo_nome;

            salva_img(novo_nome, saida);


        }

        if(filtro == 3)
        {
            cout << "Reflexao horizontal\n";
            cout << "Insira o nome da imagem:\n";
            cin >> nome;
            cout << endl;

            while(!abre_img(nome, imagem))
            {
                cout << "O arquivo de imagem nao eh compativel ou nao existe\n";
                cout << "Insira novamente o nome do arquivo:\n";
                cin >> nome;
                cout << endl;
            }

            reflete(imagem, saida);

            cout << "Insira o novo nome:\n";
            cin >> novo_nome;

            salva_img(novo_nome, saida);

        }

        if(filtro == 4)
        {
            cout << "Histograma\n";
        cout << "Insira o nome da imagem:\n";
        cin >> nome;
            cout << endl;

            while(!abre_img(nome, imagem))
            {
                cout << "O arquivo de imagem nao eh compativel ou nao existe\n";
                cout << "Insira novamente o nome do arquivo:\n";
                cin >> nome;
                cout << endl;
            }

            equaliza_histograma(imagem, saida);

            cout << "Insira o novo nome:\n";
            cin >> novo_nome;

            salva_img(novo_nome, saida);

        }
    }



    cout << "Até logo!";
    return 0;

}

bool abre_img(char nome[], img& imagem)
{
    fstream arq;

    char tipo_arq[3];
    int pixel;

    arq.open(strcat(nome, ".ppm"));

    arq.getline(tipo_arq, 3);
    arq >> imagem.coluna >> imagem.linha >> pixel;




    if(!strcmp(tipo_arq, "P3") && imagem.coluna <= 512 && imagem.linha <= 512)
    {
        cout << "Arquivo aberto com sucesso\n\n";

        for(int i=0 ; i<imagem.linha ; i++)
        {
            for(int j=0; j<imagem.coluna; j++)
            {
                for(int cor=0 ; cor<RGB ; cor++)
                {
                    arq >> imagem.mat[cor][i][j];
                }
            }
        }

        return true;

    }
    else
    {
        return false;
    }


}

void converte_para_cinza(img img_in, img& img_out)
{
    int cont=0;

    img_out.linha = img_in.linha;
    img_out.coluna = img_in.coluna;

    for(int i=0 ; i<img_in.linha ; i++)
    {
        for(int j=0; j<img_in.coluna; j++)
        {
            for(int cor=0 ; cor<RGB ; cor++)
            {
                cont += img_in.mat[cor][i][j];

                if(cor == 2)
                {
                    for(int k=0 ; k<3 ; k++)
                    {
                        img_out.mat[k][i][j] = (cont/3);
                    }
                    cont = 0;
                }
            }
        }
    }
}

void filt_dilatacao(img img_in, img& img_out)
{
    img_out.linha = img_in.linha;
    img_out.coluna = img_in.coluna;

    for(int i=0 ; i<(img_in.linha) ; i++)
    {
        for(int j=0; j<(img_in.coluna); j++)
        {
            for(int cor=0 ; cor<RGB ; cor++)
            {
                if(i<img_in.linha-1 && j<img_in.coluna-1)
                {
                    if(img_in.mat[cor][i][j]==255 || img_in.mat[cor][i+1][j]==255 || img_in.mat[cor][i][j+1]==255
                            || img_in.mat[cor][i+1][j+1]==255)
                    {
                        img_out.mat[cor][i][j] = 255;
                    }
                    else
                    {
                        img_out.mat[cor][i][j] = 0;
                    }
                }
                else
                {
                    img_out.mat[cor][i][j] = img_in.mat[cor][i][j];
                }

            }
        }
    }

}

void reflete(img img_in, img& img_out)
{
    img_out.linha = img_in.linha;
    img_out.coluna = img_in.coluna;

    for(int i=0 ; i<img_out.linha ; i++)
    {
        for(int j=0 ; j<(img_out.coluna/2) ; j++)
        {
            for(int cor=0 ; cor<RGB ; cor++)
            {
                img_out.mat[cor][i][j] = img_in.mat[cor][i][img_out.coluna-1-j];
            }
        }
        for(int j=(img_out.coluna/2) ; j<img_out.coluna ; j++)
        {
            for(int cor=0 ; cor<RGB ; cor++)
            {
                img_out.mat[cor][i][j] = img_in.mat[cor][i][j];
            }
        }

    }
}

void equaliza_histograma(img img_in, img& img_out)
{
    int cont=0,j,cont_cor=0,s=0;
    int hr[256];
    int hg[256];
    int hb[256];
    for(j=0; j<256; j++)
    {
        hr[j]=0;
        hg[j]=0;
        hb[j]=0;
    }

    img_out.linha = img_in.linha;
    img_out.coluna = img_in.coluna;


    for(int i=0 ; i<img_in.linha ; i++)
    {
        for(int j=0; j<img_in.coluna; j++)
        {

            hr[img_in.mat[0][i][j]]++;


            hg[img_in.mat[1][i][j]]++;


            hb[img_in.mat[2][i][j]]++;


        }
    }

    for(int i=0 ; i<img_in.linha ; i++)
    {
        for(int j=0; j<img_in.coluna; j++)
        {
            for(int cor=0 ; cor<RGB ; cor++)
            {
                if(cor==0)
                {
                    for(cont_cor = 0; cont_cor<=img_in.mat[cor][i][j]; cont_cor++)
                    {
                        s=(hr[cont_cor])+s;
                    }
                }
                if(cor==1)
                {

                    for(cont_cor = 0; cont_cor<=img_in.mat[cor][i][j]; cont_cor++)
                    {
                        s=(hg[cont_cor])+s;
                    }
                }
                if(cor==2)
                {
                    for(cont_cor = 0; cont_cor<=img_in.mat[cor][i][j]; cont_cor++)
                    {
                        s=(hb[cont_cor])+s;
                    }
                }

                img_out.mat[cor][i][j]=(s*255)/(img_in.linha*img_in.coluna);
                s=0;
            }

        }
    }
}

void salva_img(char nome[], img img)
{


    ofstream img_saida;

    img_saida.open(strcat(nome, ".ppm"));
    img_saida.is_open();


    img_saida << "P3\n" << img.coluna << " " << img.linha << "\n" << "255\n";

    for(int i=0 ; i<img.linha ; i++)
    {
        for(int j=0 ; j<img.coluna ; j++)
        {
            for(int cor=0 ; cor<RGB ; cor++)
            {
                img_saida << img.mat[cor][i][j] << " ";
            }
        }
        img_saida << "\n";
    }
    cout << "Arquivo salvo com sucesso\n\n\n";
}
