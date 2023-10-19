/*
Curso - Ciência da Computação - 10B

Integrantes - Henrique, Mateus Mendes da Silva, Henrique Assis Moreira

Base - lms-jun22qtr-csv

*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <string>
#include <cstring>

using namespace std;

struct exame{
    char Series_reference[50];
    char Period[50];
    // char Data_value[50];
    double Data_value;
    char STATUS[50];
    char UNITS[50];
    // char MAGNTUDE[50];
    double MAGNTUDE;
    char Subject[50];
    char Group[50];
    char Series_title_1[50];
    char Series_title_2[50];
    char Series_title_3[50];
    char Series_title_4[50];
    char Series_title_5[50];
};

void clearTerminal() {
#if defined _WIN32
  system("cls");
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
  system("clear");
#elif defined(__APPLE__)
  system("clear");
#endif
}

class Arquivo{
    private :
    fstream arquivo;
    exame aux;
    void ImprimirDados(exame Dado);
    int numReg;

    public :
    Arquivo();
    ~Arquivo();
    Arquivo(string FileName);
    void MostrarDados();
    void MostrarTodos();
    void Adicionar();
    void AlterarDado();
    void TrocarPosicao();

};

Arquivo::Arquivo(){
    arquivo = fstream("arquivo_binario.bin", ios::binary | ios::in | ios::out | ios::ate);
};

Arquivo::~Arquivo(){
    arquivo.close();
};

Arquivo::Arquivo(string FileName){
    arquivo = fstream(FileName+".bin", ios::binary | ios::in | ios::out | ios::ate);
    streampos fileSize = arquivo.tellg();
	arquivo.clear();
    numReg = fileSize / sizeof(exame);
    cout << "Número total de registros : " << numReg;
};

void Arquivo::MostrarDados(){
    int posicao1, posicao2;
    cin >> posicao1 >> posicao2;

    for(int i = posicao1; i < posicao2; i++){
        arquivo.seekg(sizeof(exame)*i, ios::beg);
        arquivo.read(reinterpret_cast<char*>(&aux), sizeof(exame));
        ImprimirDados(aux);
    }
};

void Arquivo::ImprimirDados(exame Dado){
    cout << Dado.Series_reference << " " << Dado.Period << " " << Dado.Data_value << " " << Dado.STATUS << " " << Dado.UNITS << " " << Dado.MAGNTUDE << " " << Dado.Subject << " " << Dado.Group << " " << Dado.Series_title_1 << " " << Dado.Series_title_2 << " " << Dado.Series_title_3 << " " << Dado.Series_title_4 << " " << Dado.Series_title_5 << endl;
}

void Arquivo::AlterarDado(){
    int index, option;
    cin >> index;

    arquivo.seekg(sizeof(exame)*index, ios::beg);
    arquivo.read(reinterpret_cast<char*>(&aux), sizeof(exame));
    ImprimirDados(aux);

    // cout << "Qual dado deseja alterar? : ";
    
    cout << "[1] Series_Reference" << endl;
    cout << "[2] Period" << endl;
    cout << "[3] Data_Value" << endl;
    cout << "[4] STATUS" << endl;
    cout << "[5] UNITS" << endl;
    cout << "[6] MAGNTUDE" << endl;
    cout << "[7] Subject" << endl;
    cout << "[8] Group" << endl;
    cout << "Qual dado deseja editar? : ";

    cin >> option;
    switch (option)
    {
    case 1:
        cin.ignore();
        cin.getline(aux.Series_reference,50);
        break;
    case 2:
        cin.ignore();
        cin.getline(aux.Period,50);
        break;
    case 3:
        cin.ignore();
        // cin.getline(aux.Data_value,50);
        break;
    case 4:
        cin.ignore();
        cin.getline(aux.STATUS,50);
        break;
    case 5:
        cin.ignore();
        cin.getline(aux.UNITS,50);
        break;
    case 6:
        cin.ignore();
        // cin.getline(aux.MAGNTUDE,50);
        break;
    case 7:
        cin.ignore();
        cin.getline(aux.Subject,50);
        break;
    case 8:
        cin.ignore();
        cin.getline(aux.Group,50);
        break;
    
    default:
        break;
    }

    arquivo.seekp(sizeof(exame)*index, ios::beg);
    arquivo.write(reinterpret_cast<const char*>(&aux), sizeof(exame));

    cout << "Dado alterado com sucesso!" << endl;

}

void Arquivo::TrocarPosicao(){
    int pos1, pos2;
    cin >> pos1 >> pos2;

    exame reg1;
    exame reg2;

    arquivo.seekg(sizeof(exame)*pos1);
    arquivo.read(reinterpret_cast<char*>(&reg1), sizeof(exame));

    arquivo.seekg(sizeof(exame)*pos2);
    arquivo.read(reinterpret_cast<char*>(&reg2), sizeof(exame));

    arquivo.seekp(sizeof(exame)*pos1);
    arquivo.write(reinterpret_cast<const char*>(&reg2), sizeof(exame));

    arquivo.seekp(sizeof(exame)*pos2);
    arquivo.write(reinterpret_cast<const char*>(&reg1), sizeof(exame));

}

void Arquivo::Adicionar(){
    exame aux, novoExame;
    int posicao, posFinal, cont = 1;

    cin >> posicao;
    
    cin.ignore();
    cin.getline(novoExame.Series_reference,50);

    posFinal = numReg;

    while((posFinal - cont) >= posicao){
        arquivo.seekg((posFinal - cont)*sizeof(exame));
        arquivo.read((char *) (&aux), sizeof(exame));

        arquivo.seekp((posFinal - cont + 1)*sizeof(exame));
        arquivo.write((const char *) (&aux), sizeof(exame));

        cont++;      
    }

    arquivo.seekp(posicao*sizeof(exame));
    arquivo.write(reinterpret_cast<const char*>(&novoExame), sizeof(exame));

    numReg++;
}

int main() {

    string FileName;
    int option;

    cout << "Digite o nome do arquivo \nNome : ";
    cin >> FileName;

    Arquivo arq_binario(FileName);

    do{
        cout<< "---------------------------------------------"<< endl;
        cout<< "[1] Mostrar Dados"<< endl;
        cout<< "[2] Adicionar "<< endl;
		cout<< "[3] Buscar Empresa" << endl;
		cout<< "[4] Editar Empresa" << endl;
		cout<< "[5] Remover Empresa" << endl;
		cout<< "[6] Salvar para Binario ou CSV" << endl;
		cout<< "[7] Ordernar Arquivo"<< endl;
		cout<< "[8] Imprimir Trecho"<<endl<<endl;

		cout<< "[0] Encerrar" << endl;
		cout<< "---------------------------------------------" << endl;

        cout << "Opcao : ";
        cin >> option;

        switch (option)
        {
        case 1:
            arq_binario.MostrarDados();
            break;
        case 2:
            arq_binario.TrocarPosicao();
            break;
        case 3:
            arq_binario.AlterarDado();
            break;
        case 4:
            arq_binario.Adicionar();
            break;
        
        default:
            cout << "Opção não é válida\n";
            break;
        }

    } while(option != 0);
    
    // exame aux;
    // int posicao;
	// cout << endl << "---------------------------------------------"<< endl;
	// arq.clear();
	// arq.seekg(sizeof(exame)*1263020, ios::beg);
	// arq.read(reinterpret_cast<char*>(&aux), sizeof(exame));

    // cout << aux.Data_value;

    // // cin >> posicao;

    // // arq.seekp(sizeof(exame)*1, ios::beg);
    // // arq.write(reinterpret_cast<const char*>(&aux), sizeof(exame));

    // arq.close();

    return 0;

}
