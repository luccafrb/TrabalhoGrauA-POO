#include <iostream>
#include <fstream>
#include <string>
#include "program.h"
#include "Interface/Menus.h"
#include "Classes/Usuario.h"
#include "Classes/Figurinha.h"

using namespace std;

program::program() {}
program::~program() {}

Usuario criarUsuario() {
    string nome, senha;
    cout << "Digite o nome do novo usuário: ";
    cin >> nome;
    cout << "Digite a senha do novo usuário: ";
    cin >> senha;
    return Usuario(nome, senha);
}

void program::adicionarUsuario(Usuario usuario) {
    usuarios.push_back(usuario);
}

void program::inicializate() {
    cout << "Bem vindo ao Álbum de figurinhas!" << endl;

    // Leitor
    ifstream file("Dados\\usuarios.csv");
    if (!file) {
        cout << "Erro ao abrir arquivo de usuários." << endl;
        return;
    }

    string linha;
    while (getline(file, linha)) {
        size_t pos = linha.find(',');
        if (pos != string::npos) {
            string nome = linha.substr(0, pos);
            string senha = linha.substr(pos + 1);
            usuarios.push_back(Usuario(nome, senha));
        }
    }
    file.close();

    figurinhas = Figurinha::CarregarDeCsv("Dados\\figurinhas.csv");
}

void program::run() {
char escolha;
Menus menus;


do {
    escolha = menus.mostrarMenuInicial();

    switch (escolha) {
    case 1: {
        bool nomeUnico = true;
        Usuario novoUsuario;

        do {
            novoUsuario = criarUsuario();
            nomeUnico = true;
            for (Usuario &u : usuarios) {
                if (u.getNome() == novoUsuario.getNome()) {
                    cout << "O nome de usuário \"" << u.getNome() << "\" já existe. Escolha outro, por favor." << endl;
                    nomeUnico = false;
                    break;
                }
            }
        } while (!nomeUnico);

        novoUsuario.salvarEmCsv("Dados\\usuarios.csv");
        adicionarUsuario(novoUsuario);
        break;
    }

    case 2: { // LOGIN
        string usudigitado, senhadigitado;
        cout << "Usuário: ";
        cin >> usudigitado;
        cout << "Senha: ";
        cin >> senhadigitado;

        bool autenticado = false;
        for (Usuario &u : usuarios) {
            if (u.getNome() == usudigitado && u.getSenha() == senhadigitado) {
                cout << "\nLogin bem-sucedido! Bem-vindo, " << u.getNome() << "!" << endl;
                autenticado = true;
                
                // === MENU DO USUÁRIO LOGADO ===
                char escolha_menu2;
                char escolha_menu3;
                
                do {
                    escolha_menu2 = menus.mostrarMenu();

                    switch (escolha_menu2) {
                    case 1:
                        cout << "Adicionar figurinha (em construção)\n";
                        break;

                    case 2:
                        do {
                            escolha_menu3 = menus.mostrarMenuGerenciarAlbum();
                            switch (escolha_menu3) {
                            case 1:
                            cout << "Colar Figurinha" << endl;
                            break;
                            case 2:
                            cout << "Disponibilizar para Troca" << endl;
                            break;
                            case 3:
                            cout << "Propor Troca de Figurinhas" << endl;
                            break;
                            case 4:
                            cout << "Revisar Solicitações de Troca" << endl;
                            break;
                            case 5:
                            cout << "Voltando ao Menu Anterior..." << endl;
                            break;
                            default:
                                cout << "Opção inválida!\n";
                                break;
                            }
                        } while (escolha_menu3 != 5);
                        break;

                    case 3:{
                        cout << "Abrir Pacote de Figurinhas\n";
                        
                        vector<pair<int, string>> pacotinho = Figurinha::GerarPacotinho("Dados\\figurinhas.csv");

                        cout << "=== Pacotinho Sorteado ===" << endl;
                        for (auto &f : pacotinho) {
                            cout << "ID: " << f.first << " | Nome: " << f.second << endl;
                        }
                    }
                        break;

                    case 4:
                        cout << "Voltando ao menu inicial...\n";
                        break;

                    default:
                        cout << "Opção inválida!\n";
                        break;
                    }

                } while (escolha_menu2 != 4);
            }
        }

        if (!autenticado)
            cout << "Usuário ou senha incorretos!" << endl;

        break;
    }

    case 3:
        cout << "Saindo..." << endl;
        return;


    case 4:
        cout << "Lista de usuários:" << endl;
        for (const Usuario &u : usuarios)
            cout << u.getNome() << endl;

        cout << endl << "Lista de Figurinhas:" << endl;
        for (Figurinha f : figurinhas)
            cout << f.getNome() << endl;
        break;

    default:
        cout << "Opção inválida!" << endl;
        break;
    }

} while (escolha != 3); // só sai se digitar 3 (sair)


}
