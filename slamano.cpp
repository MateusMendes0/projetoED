/*
Curso - Ciência da Computação - 10B

Integrantes - Henrique, Mateus Mendes da Silva, Henrique

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
    char Data_value[50];
    char STATUS[50];
    char UNITS[50];
    char MAGNTUDE[50];
    char Subject[50];
    char Group[50];
    char Series_title_1[50];
    char Series_title_2[50];
    char Series_title_3[50];
    char Series_title_4[50];
    char Series_title_5[50];
};

class Arquivo{
    private : 
    fstream arquivo;
    exame aux;
    void ImprimirDados(exame Dado);

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
    arquivo = fstream("arquivo_binario.bin", ios::binary | ios::app | ios::in | ios::ate);
};

Arquivo::~Arquivo(){
    arquivo.close();
};

Arquivo::Arquivo(string FileName){
    arquivo = fstream(FileName+".bin", ios::binary | ios::app | ios::in | ios::ate);
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
    cout << Dado.Series_reference << " " << Dado.Period << endl; 
}

int main() {
    
    string FileName;

    Arquivo arq;

    cout << "Digite o nome do arquivo \n";
    cin >> FileName;

    Arquivo arq_binario(FileName);

    arq_binario.MostrarDados();

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
