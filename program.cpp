#include <iostream>
#include "program.h"
#include "Interface/Menus.h"
#include "Classes/Usuario.h"

using namespace std;

program::program()
{
}

program::~program()
{
}

void program::adicionarUsuario()
{
    bool nomeUnico = false;

    string nome, senha;
    while (!nomeUnico)
    {
        cout << "Digite o nome do novo usuário: ";
        cin >> nome;

        nomeUnico = true;

        for (Usuario &u : usuarios)
        {
            if (u.getNome() == nome)
            {
                cout << "O nome de usuário \"" << u.getNome() << "\" já existe. Escolha outro, por favor." << endl;
                nomeUnico = false;
                break;
            };
        }
    }

    cout << "Digite a senha do novo usuário: ";
    cin >> senha;

    Usuario novoUsuario(nome, senha, todasFigurinhas);

    novoUsuario.salvarEmCsv("Dados\\usuarios.csv");
    usuarios.push_back(novoUsuario);
}

void program::inicializate()
{
    cout << "Bem vindo ao Álbum de figurinhas!" << endl;

    todasFigurinhas = Figurinha::CarregarDeCsv("Dados\\figurinhas.csv");
    usuarios = Usuario::CarregarDeCsv("Dados\\usuarios.csv", todasFigurinhas);
}

void program::run()
{
    menuInicial();
}

void program::menuGerenciarAlbum(Usuario &usuarioAtual, Menus &menus)
{

    int escolha = 0;

    while (true)
    {
        escolha = menus.mostrarMenuAlbum();

        switch (escolha)
        {
        case 1:
            usuarioAtual.getAlbum().verAlbum();
            break;
        case 2:
            menuGerenciarColecao(usuarioAtual, menus);
            break;
        case 3:
            usuarioAtual.getAlbum().abrirPacotinho(todasFigurinhas);
            break;
        case 4:
            return;
            break;
        default:
            cout << "Opção inválida!" << endl;
        }
    };
}

void program::menuGerenciarColecao(Usuario &usuarioAtual, Menus &menus)
{
    int escolha = 0;

    while (true)
    {
        escolha = menus.mostrarMenuGerenciarColecao();

        switch (escolha)
        {
        case 1:
            usuarioAtual.getAlbum().colarFigurinha();
            break;
        case 2:{
     Figurinha* fLiberada = usuarioAtual.getAlbum().disponibilizarFigurinhaParaTroca();

    // Se a figurinha foi liberada, salva somente ela no CSV
    if (fLiberada != nullptr)
    {
        usuarioAtual.getAlbum().salvarFigurinhaParaTrocaCSV(fLiberada, usuarioAtual.getNome());
    }
    }
            break;
        case 3:
            cout << "3 - Propor Troca de Figurinhas" << endl;
            break;
        case 4:
            cout << "4 - Revisar Solicitações de Troca" << endl;
            break;
        case 5:
            return;
        default:
            cout << "Opção inválida!" << endl;
        }
    };
}

void program::menuInicial()
{
    int escolha;
    Menus menus;

    do
    {
        escolha = menus.mostrarMenuInicial();

        switch (escolha)
        {
        case 1:
        {
            adicionarUsuario();
            break;
        }

        case 2:
        {
            Usuario &usuarioAtual = login();

            menuGerenciarAlbum(usuarioAtual, menus);
            break;
        }

        case 3:
            cout << "Saindo.." << endl;
            break;

        case 4:
        {
            cout << "Lista de usuários:" << endl;

            for (const Usuario &u : usuarios)
            {
                cout << u.getNome() << endl;
            }

            cout << endl;
            cout << "Lista de Figurinhas:" << endl;

            for (Figurinha f : todasFigurinhas)
            {
                cout << f.getNome() << endl;
            }
            break;
        }

        default:
            break;
        }
    } while (escolha != 3);
}

Usuario &program::login()
{
    string senha, nome;
    cout << "-- Lista de Usuários --" << endl;
    for (Usuario &u : usuarios)
    {
        cout << "- " << u.getNome() << endl;
    }

    bool loginValido = false;
    while (true)
    {
        cout << "Digite o nome do seu usuário: ";
        cin >> nome;

        for (Usuario &u : usuarios)
        {
            if (u.getNome() == nome)
            {
                bool senhaCorreta = false;

                while (!senhaCorreta)
                {
                    cout << "Digite a senha do seu usuário: ";
                    cin >> senha;

                    if (u.getSenha() == senha)
                    {
                        senhaCorreta = true;
                        return u;
                    }

                    cout << "Senha de usuário incorreta! Tente novamente." << endl;
                }
            }
        }
        cout << "Nome de usuário não encontrado. Tente novamente." << endl;
    }
}
