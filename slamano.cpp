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

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    

    fstream arq("arquivo_binario.bin", ios::binary | ios::app | ios::in | ios::ate);

    exame aux;
    int posicao;
	cout << endl << "---------------------------------------------"<< endl;
	arq.clear();
	arq.seekg(sizeof(exame)*1263020, ios::beg);
	arq.read(reinterpret_cast<char*>(&aux), sizeof(exame));

    cout << aux.Data_value;

    // cin >> posicao;
    
    // arq.seekp(sizeof(exame)*1, ios::beg);
    // arq.write(reinterpret_cast<const char*>(&aux), sizeof(exame));


    arq.close();


    return 0;

}
