#include "Album.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <ctime>
#include <limits>

using namespace std;

Album::Album(vector<Figurinha> &todasFigurinhas)
{
    criarPaginas(todasFigurinhas);
}

Album::~Album() {}

bool Album::colarFigurinha()
{
    int escolha = -1;

    while (true)
    {
        if (!mostrarFigurinhasDaColecao())
        {
            cout << "Sem figurinhas na coleção." << endl;
            return false;
        }

        cout << "Digite o número da figurinha que você deseja colar (0 para sair): ";
        cin >> escolha;

        if (escolha == 0)
            break;

        bool figurinhaValida = false;

        for (Figurinha &f : figurinhas)
        {
            if (f.getNum() == escolha)
            {
                f.colar();

                for (Pagina &p : paginas)
                {
                    if (p.getTitulo() == f.getConteudo())
                    {
                        p.adicionarFigurinha(&f);
                        cout << "Colada na página " << p.getTitulo() << endl;
                        break;
                    }
                }

                figurinhaValida = true;
                break;
            }
        }

        if (!figurinhaValida)
        {
            cout << "Figurinha inválida!" << endl;
            return false;
        }
    }

    return true;
}

void Album::adicionarFigurinha(Figurinha figurinha)
{
    figurinhas.push_back(figurinha);
}

void Album::verAlbum()
{
    if (paginas.empty())
    {
        cout << "O álbum está vazio." << endl;
        return;
    }

    int paginaAtual = 0;

    while (true)
    {
        cout << "-- Página " << paginaAtual + 1 << " do Álbum --" << endl;
        paginas[paginaAtual].mostrarFigurinhas();

        cout << "---------------------" << endl;
        if (paginaAtual < paginas.size() - 1)
            cout << "1 - Próxima página" << endl;
        if (paginaAtual > 0)
            cout << "2 - Página anterior" << endl;
        cout << "0 - Sair" << endl;

        int escolha;
        cin >> escolha;

        if (escolha == 1 && paginaAtual < paginas.size() - 1)
            paginaAtual++;
        else if (escolha == 2 && paginaAtual > 0)
            paginaAtual--;
        else if (escolha == 0)
            return;
        else
            cout << "Opção inválida! Tente novamente." << endl;
    }
}

void Album::mostrarFigurinhasColadas()
{
    if (figurinhas.empty())
    {
        cout << "Sem figurinhas." << endl;
        return;
    }

    for (Figurinha &f : figurinhas)
    {
        if (f.getStatus() == 1)
        {
            cout << f.getNome() << endl;
        }
    }
}

bool Album::mostrarFigurinhasDaColecao()
{
    if (figurinhas.empty())
        return false;

    cout << "-- Figurinhas na coleção --" << endl;

    for (Figurinha &f : figurinhas)
    {
        if (f.getStatus() == 0)
        {
            cout << f.getNum() << " - " << f.getNome() << endl;
        }
    }

    return true;
}

void Album::criarPaginas(vector<Figurinha> &todasFigurinhas)
{
    vector<string> conteudosUnicos;
    vector<int> numDeFigurinhasPorConteudo;

    for (Figurinha &f : todasFigurinhas)
    {
        bool encontrado = false;

        for (int i = 0; i < conteudosUnicos.size(); i++)
        {
            if (f.getConteudo() == conteudosUnicos[i])
            {
                numDeFigurinhasPorConteudo[i]++;
                encontrado = true;
                break;
            }
        }

        if (!encontrado)
        {
            conteudosUnicos.push_back(f.getConteudo());
            numDeFigurinhasPorConteudo.push_back(1);
        }
    }

    int contador = 1;
    for (int i = 0; i < conteudosUnicos.size(); i++)
    {
        string conteudo = conteudosUnicos[i];
        int numFigurinhas = numDeFigurinhasPorConteudo[i];

        int numMin = contador;
        int numMax = contador + numFigurinhas - 1;
        contador = numMax + 1;

        Pagina novaPagina(conteudo, numMin, numMax);
        paginas.push_back(novaPagina);
    }
}

Figurinha* Album::disponibilizarFigurinhaParaTroca()
{
    if (!mostrarFigurinhasIndisponiveisParaTroca())
    {
        cout << "Sem figurinhas indisponíveis para troca." << endl;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cin.get();
        return nullptr;
    }

    int escolha;
    cout << "Digite o número da figurinha que você deseja liberar para troca: ";
    cin >> escolha;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (Figurinha &f : figurinhas)
    {
        if (f.getNum() == escolha && f.getStatus() == 0)
        {
            f.disponibilizarParaTroca(); // status = 2
            cout << "Figurinha '" << f.getNome() << "' liberada para troca!" << endl;
            return &f;
        }
    }

    cout << "Número inválido ou figurinha já colada/disponível para troca!" << endl;
    return nullptr;
}

bool Album::mostrarFigurinhasIndisponiveisParaTroca()
{
    bool existeIndisponivel = false;
    for (Figurinha &f : figurinhas)
    {
        if (f.getStatus() == 0)
        {
            existeIndisponivel = true;
            break;
        }
    }

    if (!existeIndisponivel)
        return false;

    cout << "-- Figurinhas indisponíveis para troca --" << endl;
    for (Figurinha &f : figurinhas)
    {
        if (f.getStatus() == 0)
            cout << f.getNum() << " - " << f.getNome() << endl;
    }
    cout << "---------------------------------------" << endl;
    return true;
}

void Album::abrirPacotinho(vector<Figurinha> &todasFigurinhas)
{
    vector<Figurinha> pacotinho;
    int quantidade = 3;

    if (todasFigurinhas.empty())
        return;

    srand(time(nullptr));

    vector<int> indices;
    for (size_t i = 0; i < todasFigurinhas.size(); ++i)
        indices.push_back(i);

    for (int i = 0; i < quantidade; ++i)
    {
        int randPos = rand() % indices.size();
        int idx = indices[randPos];

        pacotinho.push_back(todasFigurinhas[idx]);
        indices[randPos] = indices.back();
        indices.pop_back();
    }

    cout << "-- Novas figurinhas --" << endl;
    for (Figurinha &f : pacotinho)
    {
        cout << f.getNome() << endl;
        figurinhas.push_back(f);
    }
    cout << "---------------------" << endl;

    cout << "Pressione ENTER para continuar..." << endl;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
}

void Album::salvarFigurinhaParaTrocaCSV(Figurinha* f, const std::string &nickname)
{
    if (!f) return; // nada para salvar

    namespace fs = std::filesystem;
    if (!fs::exists("Dados"))
        fs::create_directory("Dados");

    string nomeArquivo = "Dados/" + nickname + "_trocas.csv";
    bool arquivoJaExiste = fs::exists(nomeArquivo);

    ofstream arquivo(nomeArquivo, ios::app);
    if (!arquivo.is_open())
    {
        cout << "Erro ao criar o arquivo CSV!" << endl;
        return;
    }

    // escreve cabeçalho apenas se o arquivo é novo
    if (!arquivoJaExiste)
        arquivo << "Numero,Nome,Conteudo,Status\n";

    arquivo << f->getNum() << ","
            << f->getNome() << ","
            << f->getConteudo() << ",Disponivel\n";

    arquivo.close();
    cout << "Arquivo '" << nomeArquivo << "' salvo com sucesso!" << endl;
}
