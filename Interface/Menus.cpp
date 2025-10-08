#include "Menus.h"
#include <iostream>

using namespace std;

Menus::Menus()
{
}

Menus::~Menus()
{
}

int Menus::mostrarMenuInicial()
{
    cout << "---------- Menu Inicial ----------" << endl;
    cout << "Escolha uma das opções:" << endl;
    cout << "1 - Novo Álbum" << endl;
    cout << "2 - Acessar Álbum" << endl;
    cout << "3 - Sair" << endl;
    cout << "4 - Mostrar dados dos CSV's (Para teste)" << endl;
    cout << "----------------------------------" << endl;

    int escolha;
    cin >> escolha;

    return escolha;
}

int Menus::mostrarMenu()
{
    cout << "---------- Menu do Álbum ----------" << endl;
    cout << "Escolha uma das opções:" << endl;
    cout << "1 - Ver Álbum" << endl;
    cout << "2 - Gerenciar a Coleção" << endl;
    cout << "3 - Abrir Pacote de Figurinhas" << endl;
    cout << "4 - Voltar ao Menu Anterior" << endl;
    cout << "-----------------------------------" << endl;
    int escolha_menu2;
    cin >> escolha_menu2;

    return escolha_menu2;
}

int Menus::mostrarMenuGerenciarAlbum()
{
    cout << "------ Menu Gerenciar Álbum ------" << endl;
    cout << "Escolha uma das opções:" << endl;
    cout << "1 - Colar Figurinha" << endl;
    cout << "2 - Disponibilizar para Troca" << endl;
    cout << "3 - Propor Troca de Figurinhas" << endl;
    cout << "4 - Revisar Solicitações de Troca" << endl;
    cout << "5 - Voltar ao Menu Anterior" << endl;
    cout << "----------------------------------" << endl;
    
    int escolha_menu3;
    cin >> escolha_menu3;
    
    return escolha_menu3;
}
