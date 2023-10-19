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
    float Data_value;
    char STATUS[50];
    char UNITS[50];
    // char MAGNTUDE[50];
    float MAGNTUDE;
    char Subject[50];
    char Group[50];
    char Series_title_1[50];
    char Series_title_2[50];
    char Series_title_3[50];
    char Series_title_4[50];
    char Series_title_5[50];
};

/*
Series_reference,Period,Data_value,STATUS,UNITS,MAGNTUDE,Subject,Group,Series_title_1,Series_title_2,Series_title_3,Series_title_4,Series_title5
*/

exame leitura(ifstream& arq){  // Le o arquivo CSV e retorna uma Struct que é adicionado a um vetor
	    exame exames;
		char lixo;
		string nome = "";
		getline(arq,nome,',');
		strncpy(exames.Series_reference, nome.c_str(), sizeof(exames.Series_reference) - 1);

		getline(arq,nome,',');
		strncpy(exames.Period, nome.c_str(), sizeof(exames.Period) - 1);

        // getline(arq,nome,',');
		// strncpy(exames.Data_value, nome.c_str(), sizeof(exames.Data_value) - 1);

        arq >> exames.Data_value;
        // cout << exames.Data_value << " ";
        arq >> lixo;


		getline(arq,nome,',');
		strncpy(exames.STATUS, nome.c_str(), sizeof(exames.STATUS) - 1);
        
        getline(arq,nome,',');
		strncpy(exames.UNITS, nome.c_str(), sizeof(exames.UNITS) - 1);

        // getline(arq,nome,',');
		// strncpy(exames.MAGNTUDE, nome.c_str(), sizeof(exames.MAGNTUDE) - 1);

        arq >> exames.MAGNTUDE;

        // cout << exames.MAGNTUDE << endl;
        arq >> lixo;

        getline(arq,nome,',');
		strncpy(exames.Subject, nome.c_str(), sizeof(exames.Subject) - 1);

		getline(arq,nome,',');
		strncpy(exames.Group, nome.c_str(), sizeof(exames.Group) - 1);
        
        getline(arq,nome,',');
		strncpy(exames.Series_title_1, nome.c_str(), sizeof(exames.Series_title_1) - 1);

        getline(arq,nome,',');
		strncpy(exames.Series_title_2, nome.c_str(), sizeof(exames.Series_title_2) - 1);

        getline(arq,nome,',');
		strncpy(exames.Series_title_3, nome.c_str(), sizeof(exames.Series_title_3) - 1);

        getline(arq,nome,',');
		strncpy(exames.Series_title_4, nome.c_str(), sizeof(exames.Series_title_4) - 1);

        getline(arq,nome);
		strncpy(exames.Series_title_5, nome.c_str(), sizeof(exames.Series_title_5) - 1);
	
    return exames;
	
	}


int main() {
    
    fstream arq("arquivo_binario1.bin", ios::binary | ios::app | ios::in | ios::ate);
    string campos;
    exame teste;

//while(!file.eof())
    ifstream arquivo_csv("teste.csv");
    getline(arquivo_csv,campos);

    while(!arquivo_csv.eof()){
    teste = leitura(arquivo_csv);
	arq.seekp(0, ios::end);
    arq.write(reinterpret_cast<const char*>(&teste), sizeof(exame));
    }

    return 0;

}