#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//Variavel global, definida de acordo com a função DefConstNumeroDeRegistros
int quantRegistros;

//Definição do struct usado no progama
typedef struct
{
    int id;
    char nome[30];
    double notas[3];
    double media;
}aluno;
//Função estática para impressão do menu de opções
void ImprimirMenu()
{
    printf("Escolha uma opcao:\n");
    printf("1. Imprimir todos os elementos do arranjo\n");
    printf("2. Imprimir apenas os nomes dos alunos\n");
    printf("3. Imprimir o nome dos alunos e sua respectiva nota final\n");
    printf("4. Buscar os dados de um aluno usando a busca sequencial\n");
    printf("5. Imprimir os alunos ordenados de acordo com sua matricula\n");
    printf("6. Editar as notas de um aluno\n");
    printf("7. Imprimir a matricula, nome e nota final do aluno que obteve a maior nota de todas\n");
    printf("8. Imprimir a matricula, nome e nota final do aluno que obteve a menor nota de todas\n");
    printf("9. Imprimir quantos alunos foram aprovados e quantos alunos foram reprovados, imprima ainda a media geral\n");
    printf("0. Sair do programa: ");
}
//Define o numero de registros, para facilitar a passagem de parametros
int DefConstNumeroDeRegistros(FILE *arq)
{
    int quantidade = 0;
    char letra;
    while ((letra = fgetc(arq)) != EOF)
    {
        if(letra == '\n')
        {
            quantidade++;
        }
    }
    quantRegistros = quantidade + 1;
}
//Imprime o aluno de acordo com a matricula recebida como parametro
void ImprimirAlunoNaPosicao(aluno alunos[], int matricula)
{
    for (int i = 0; i < quantRegistros; i++)
    {
        if (alunos[i].id == matricula)
        {
            printf("Id: %d, Nome: %s, Notas: %.2f, %.2f, %.2f, Nota final: %.2f\n", alunos[i].id, alunos[i].nome, alunos[i].notas[0], alunos[i].notas[1], alunos[i].notas[2], alunos[i].media);
        }
    }
}
//Atualiza as medias de todos alunos
void AtualizarMedias(aluno alunos[])
{
    for (int i = 0; i < quantRegistros; i++)
    {
        double soma = 0;
        double media =0;

        for (int c = 0; c < 3; c++)
        {
            soma += alunos[i].notas[c];
        }
        media = soma / 3.0;
        alunos[i].media = media;
    }
}
//1. Imprime todos elementos de todos alunos
void ImprimirTodosElementos (aluno alunos[])
{
    for (int i = 0; i < quantRegistros; i++)
    {
        printf("Id: %d, Nome: %s, Notas: %.2f, %.2f, %.2f, Nota final: %.2f\n", alunos[i].id, alunos[i].nome, alunos[i].notas[0], alunos[i].notas[1], alunos[i].notas[2], alunos[i].media);
    }
}
//2. Imprime apenas o nome de todos alunos
void ImprimirNomes (aluno alunos[])
{
   for (int i = 0; i < quantRegistros; i++)
    {
        printf("%s\n",alunos[i].nome);
    }
}
//3. Impre apenas nome e media de todos alunos
void ImprimirNomeAndMedia(aluno alunos[])
{
    for (int i = 0; i < quantRegistros; i++)
    {
        printf("%s: %.2f\n",alunos[i].nome, alunos[i].media);
    }
}
//4. Imprime todos elementos de um aluno especifico
void BuscarAluno(aluno alunos[])
{
    int buscaid;

    printf("Digite o id do aluno que deseja buscar: ");
    scanf("%d", &buscaid);

    for (int i = 0; i < quantRegistros; i++)
    {
        if (alunos[i].id == buscaid)
        {
            ImprimirAlunoNaPosicao(alunos, buscaid);
            return;
        }
    }
    printf("O aluno nao foi encontrado\n");
}
//5. Imprime todos elmentos de todos alunos, em ordem crescente de acordo com a matricula (Não altera a struct)
void OrdenarLista(aluno alunos[])
{
    aluno alunos2[quantRegistros];

    for (int i = 0; i < quantRegistros; i++)
    {
        alunos2[i] = alunos[i];
    }

    aluno aux;
    for (int i = 0; i < quantRegistros; i++)
    {
        for (int c = 0; c < quantRegistros-1-i; c++)
        {
            if (alunos2[c].id > alunos2[c + 1].id)
            {
                aux = alunos2[c];
                alunos2[c] = alunos2[c+1];
                alunos2[c+1] = aux;
            }
        }
    }
    ImprimirTodosElementos(alunos2);
}
//6. Altera a nota de um aluno especifico
void AlterarNota (aluno alunos[])
{
    int notaEscolhida;
    float novaNota;
    int buscaid;


    printf("Digite o id do aluno que deseja buscar: ");
    scanf("%d", &buscaid);
    bool cond = false;
    for (int i = 0; i < quantRegistros; i++)
    {
        if(alunos[i].id == buscaid)
            cond = true;
    }
    if (!cond)
    {
        printf("O Id nao foi encontrado\n");
        return;
    }

    ImprimirAlunoNaPosicao(alunos, buscaid);

    printf("\nQual nota deseja alterar? [1/2/3] ");
    scanf("%d", &notaEscolhida);
    notaEscolhida--;
    if (notaEscolhida > 2 || notaEscolhida < 0)
    {
        printf("Nota invalida\n");
        return;
    }

    printf("Qual nova nota sera atribuida? ");
    scanf("%f", &novaNota);

    for (int i = 0; i < quantRegistros; i++)
    {
        if (alunos[i].id == buscaid)
        {
            alunos[i].notas[notaEscolhida] = novaNota;
        }
    }

    AtualizarMedias(alunos);

    printf("Novas notas:\n");

    ImprimirAlunoNaPosicao(alunos, buscaid);
    printf("\n");
}
//7. Imprime todos elementos do aluno que possui a maior nota
void MaiorNota (aluno alunos[])
{
    aluno maior;
    for (int i = 0; i < quantRegistros; i++)
    {
        if (i == 0)
        {
            maior = alunos[i];
        }
        if (alunos[i].media > maior.media)
        {
            maior = alunos[i];
        }
    }
    printf("Id: %d, Nome: %s, Nota final: %.2f\n", maior.id, maior.nome, maior.media);
}
//8. Imprime todos elementos do aluno que possui a menor nota
void MenorNota (aluno alunos[])
{
    aluno menor;
    for (int i = 0; i < quantRegistros; i++)
    {
        if (i == 0)
        {
            menor = alunos[i];
        }
        if (alunos[i].media < menor.media)
        {
            menor = alunos[i];
        }
    }
    printf("Id: %d, Nome: %s, Nota final: %.2f\n", menor.id, menor.nome, menor.media);
}
//9. Imprime numero de: alunos aprovados, reprovados e media geral total
void VisaoGeral(aluno alunos[])
{
    double somaDasNotas = 0, MediaGeral = 0;
    int Aprovados = 0, Reprovados = 0;
    for (int i = 0; i < quantRegistros; i++)
    {
        if (alunos[i].media >= 6)
            Aprovados++;
        else
            Reprovados++;

        somaDasNotas += alunos[i].media;
    }
    MediaGeral = somaDasNotas / quantRegistros;

    printf("%d Aprovados\n%d Reprovados\nMedia geral: %.2f\n", Aprovados, Reprovados, MediaGeral);
}
//0. Encerra o progama e cria um novo arquivo ordenado de acordo com a matriculas + alterações feitas no progama
void SalvarInformacoesNovoArq(aluno alunos[])
{
    FILE *novoArq;
    novoArq = fopen("NovosRegistrosAlunos.txt", "w");

    aluno alunos2[quantRegistros];

    for (int i = 0; i < quantRegistros; i++)
    {
        alunos2[i] = alunos[i];
    }

    aluno aux;
    for (int i = 0; i < quantRegistros; i++)
    {
        for (int c = 0; c < quantRegistros-1-i; c++)
        {
            if (alunos2[c].id > alunos2[c + 1].id)
            {
                aux = alunos2[c];
                alunos2[c] = alunos2[c+1];
                alunos2[c+1] = aux;
            }
        }
    }
    for (int i = 0; i < quantRegistros; i++)
    {
        fprintf(novoArq, "%d %s %.2f %.2f %.2f %.2f\n",
                alunos2[i].id, alunos2[i].nome, alunos2[i].notas[0], alunos2[i].notas[1], alunos2[i].notas[2], alunos2[i].media);
    }
    printf("Progama finalizado, arquivo NovoRegistroAlunos.txt criado no diretorio\n\n");
    fclose(novoArq);
}
int main()
{
    int esc=1;
    FILE *arq;

    arq = fopen("DadosAlunos.txt", "r");
    if(arq == NULL){
        printf("Erro na abertura do arquivo");
        return 0;
    }

    DefConstNumeroDeRegistros(arq);

    rewind(arq);

    aluno *alunos;
    alunos = (aluno *) malloc(quantRegistros * sizeof(aluno));

    for(int i = 0; i < quantRegistros; i++)
    {
        fscanf(arq, "%d", &alunos[i].id);

        char nome[30];
        fscanf(arq, "%s", nome);
        strcpy(alunos[i].nome, nome);

        float notas[3];
        fscanf(arq, "%f%f%f", &notas[0], &notas[1], &notas[2]);
        for(int c = 0; c < 3; c++)
            alunos[i].notas[c] = notas[c];
    }
    fclose(arq);

    AtualizarMedias(alunos);

    while (esc != 0)
    {
        ImprimirMenu();

        scanf("%d", &esc);

        system("Cls");

        switch (esc)
        {
            case 1:
            {
                ImprimirTodosElementos(alunos);
                break;
            }
            case 2:
            {
                ImprimirNomes(alunos);
                break;
            }
            case 3:
            {
                ImprimirNomeAndMedia(alunos);
                break;
            }
            case 4:
            {
                BuscarAluno(alunos);
                break;
            }
            case 5:
            {
                OrdenarLista(alunos);
                break;
            }
            case 6:
            {
                AlterarNota(alunos);
                break;
            }
            case 7:
            {
                MaiorNota(alunos);
                break;
            }
            case 8:
            {
                MenorNota(alunos);
                break;
            }
            case 9:
                VisaoGeral(alunos);
                break;
            case 0:
            {
                SalvarInformacoesNovoArq(alunos);
                system("Pause");
                return 0;
            }
            default:
            {
                printf("Valor invalido\n");
                break;
            }
        }
        printf("\n");
        system("Pause");
        system("cls");
    }
}



