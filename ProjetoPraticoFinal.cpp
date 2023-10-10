

/*
Tema : Empresas

Curso - Ciência da Computação - 10A

Integrantes - Maria Eduarda Ferreira da Silva e  Mateus Mendes da Silva

*/


#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <string>
#include <cstring>

using namespace std;

struct Empresa{
	int numInscricao;
	char nome[30];
	char porte;
	char ramo[25];
	int funcionarios;
	double receita;
	float lucro;
	float avaliacao;
};

Empresa leitura(ifstream& arq){  // Le o arquivo CSV e retorna uma Struct que é adicionado a um vetor
	Empresa empresas;
		char lixo;
		string nome = "";
		getline(arq,nome,',');
		strncpy(empresas.nome, nome.c_str(), sizeof(empresas.nome) - 1);
		getline(arq,nome,',');
		strncpy(empresas.ramo, nome.c_str(), sizeof(empresas.nome) - 1);
		
		arq >> empresas.numInscricao;
		arq >> lixo;
		arq >> empresas.porte;
		arq >> lixo;
		arq >> empresas.funcionarios;
		arq >> lixo;
		arq >> empresas.receita;
		arq >> lixo;
		arq >> empresas.lucro;
		arq >> lixo;
		arq >> empresas.avaliacao;
		arq.ignore();
	
	return empresas;
	
	
	}
	
int particiona(Empresa *A, int lo, int hi) { // Quick sort Numero_inscricao
   Empresa pivo = A[lo + (hi - lo) / 2];
   int i = lo - 1;
   int j = hi + 1;
   while (true) {
      do {
         i++;
      } while (A[i].numInscricao < pivo.numInscricao);
      do {
         j--;
      } while (A[j].numInscricao > pivo.numInscricao);
      if (i >= j) return j;
      swap(A[i],A[j]);
   }
} 
	
void quicksort(Empresa *a, int pos_pivo, int fim) { // Quick sort Numero_inscricao
   int pos_novo_pivo;         
   if (pos_pivo < fim) {  
      pos_novo_pivo = particiona(a, pos_pivo, fim);
      quicksort(a, pos_pivo, pos_novo_pivo); 
      quicksort(a, pos_novo_pivo + 1, fim); 
   }
}

int particiona_nome(Empresa *A, int lo, int hi) { // Quick sort Nome
   Empresa pivo = A[lo + (hi - lo) / 2];
   int i = lo - 1;
   int j = hi + 1;
   while (true) {
      do {
         i++;
      } while (strcmp(A[i].nome,pivo.nome) < 0);
      do {
         j--;
      } while (strcmp(A[j].nome,pivo.nome) > 0);
      if (i >= j) return j;
      swap(A[i],A[j]);
   }
} 
	
void quicksort_nome(Empresa *a, int pos_pivo, int fim) { // Quick sort Nome
   int pos_novo_pivo;         
   if (pos_pivo < fim) {  
      pos_novo_pivo = particiona_nome(a, pos_pivo, fim);
      quicksort_nome(a, pos_pivo, pos_novo_pivo); 
      quicksort_nome(a, pos_novo_pivo + 1, fim); 
   }
}

void imprimir_empresa(Empresa empresas){ // Imprime uma certa empresa
		cout << fixed << setprecision(2);
		cout << empresas.numInscricao << " " << 
		empresas.nome << " " <<
		empresas.porte << " " << 
		empresas.ramo << " " << 
		empresas.funcionarios << " " <<
		empresas.receita << " " << 
		empresas.lucro << " " << 
		empresas.avaliacao << endl;
	}

void imprimir_all(fstream &arq,int num){ // Imprime todas as empresas do arquivo
	Empresa aux;
	arq.clear();

	int i=0;
	while(i<num){
		arq.seekg(sizeof(Empresa)*i, ios::beg);
		arq.read(reinterpret_cast<char*>(&aux), sizeof(Empresa));
		if(aux.numInscricao != -1){
		imprimir_empresa(aux);
	}
		i++;
		}
}

void imprimir_trecho(fstream &arq,int inicio, int fim){ // Imprime um trecho das empresas do arquivo
	Empresa aux;
	arq.clear();

	int i=inicio;
	while(i<fim){
		arq.seekg(sizeof(Empresa)*i, ios::beg);
		arq.read(reinterpret_cast<char*>(&aux), sizeof(Empresa));
		imprimir_empresa(aux);
		i++;
		}
}

void buscar_inscricao(int num_inscri, int num, fstream &arq){ // Busca uma empresa pela seu Numero de Inscricao
	bool found = false;
	Empresa aux;

	cout<< endl << "---------------------------------------------"<< endl;
	int i=0;
	arq.clear();
	while(i<num and found == false){
		arq.seekg(sizeof(Empresa)*i, ios::beg);
		arq.read(reinterpret_cast<char*>(&aux), sizeof(Empresa));
		if(aux.numInscricao == num_inscri){
			found = true;
			imprimir_empresa(aux);
		}
	i++;
	}
	

	if(!found)
		cout << "Nao foi encontrada nenhuma empresa \n";
	
	 cout<< "--------------------------------------------- \n\n";

}

void buscar_porte(char porte, int num, fstream &arq){  // Busca empresas dado um certo porte ( P , M , G)
	bool found = false;
	Empresa aux;
	cout<< endl << "---------------------------------------------"<< endl;
	int i=0;
	arq.clear();
	while(i<num){
		arq.seekg(sizeof(Empresa)*i, ios::beg);
		arq.read(reinterpret_cast<char*>(&aux), sizeof(Empresa));
		if(aux.porte == porte){
			found = true;
			imprimir_empresa(aux);
		}
	i++;
	}

	if(!found)
		cout << "Nao foi encontrada nenhuma Empresa \n";
	
	 cout<< "--------------------------------------------- \n\n";
}

void buscar_nome(string nome, int num, fstream &arq){  // Busca uma empresa pelo seu nome
	bool found = false;
	Empresa aux;
	cout << endl << "---------------------------------------------"<< endl;
	int i=0;
	arq.clear();
	while(i<num and found == false){
		arq.seekg(sizeof(Empresa)*i, ios::beg);
		arq.read(reinterpret_cast<char*>(&aux), sizeof(Empresa));
		if(aux.nome == nome){
			found = true;
			imprimir_empresa(aux);
		}
	i++;
	}

	if(!found)
		cout << "Nao foi encontrada nenhuma Empresa \n";
	
	 cout<< "--------------------------------------------- \n\n";
}



void buscar_ramo(string ramo,int num,fstream &arq){   // Busca empresas dado um ramo ( ex : Tecnologia )
	bool found = false;
	Empresa aux;
	cout << endl << "---------------------------------------------"<< endl;
	int i=0;
	arq.clear();
	while(i<num){
		arq.seekg(sizeof(Empresa)*i, ios::beg);
		arq.read(reinterpret_cast<char*>(&aux), sizeof(Empresa));
		if(aux.ramo == ramo){
			found = true;
			imprimir_empresa(aux);
		}
	i++;
	}

	if(!found)
		cout << "Nao foi encontrada nenhuma empresa \n";
	
	 cout<< "--------------------------------------------- \n\n";
}

Empresa *adicionar_empresa(int &tamanho, string nome_arq, Empresa *empresas){ // Adiciona uma empresa diretamente no arquivo
	Empresa temp;
	cout << "Numero de Inscricao" << endl; // Inserção dos dados da nova empresa
    cin >> temp.numInscricao;
	cin.ignore();
	cout << "Nome" << endl;
	cin.getline(temp.nome,30);
	cout << "Porte" << endl;
    cin >> temp.porte;
	cout << "Funcionarios" << endl;
    cin >> temp.funcionarios;
	cout << "Ramo" << endl;
    cin >> temp.ramo;
	cout << "Receita" << endl;
    cin >> temp.receita;
	cout << "Lucro" << endl;
    cin >> temp.lucro;
	cout << "Avaliacao" << endl;
    cin >> temp.avaliacao;

	fstream arq(nome_arq+".bin", ios::binary | ios::app | ios::in | ios::ate);
	arq.seekp(0, ios::end);
    arq.write(reinterpret_cast<const char*>(&temp), sizeof(Empresa));
	delete[] empresas;

	streampos fileSize = arq.tellg();
   	arq.clear();
   	tamanho = fileSize / sizeof(Empresa);
	Empresa *aux = new Empresa[tamanho];
   	arq.seekg(0, ios::beg);
   	arq.clear();
   	arq.read(reinterpret_cast<char*>(aux), fileSize);
   	arq.close();
   	return aux;
}


void editar(int num_inscri, fstream &arq, int num){ // Edita todas ou certa informação da empresa

	bool found = false;

	Empresa aux;

	int option;
	int i = 0;

	while(i<num and found == false){
		arq.seekg(sizeof(Empresa)*i, ios::beg);
		arq.read(reinterpret_cast<char*>(&aux), sizeof(Empresa));
		if(aux.numInscricao == num_inscri){
			found = true;
			imprimir_empresa(aux);
			cout << "Qual dado deseja editar?" << endl;
			cout << "[1] Numero de Inscricao" << endl;
			cout << "[2] Nome" << endl;
			cout << "[3] Porte" << endl;
			cout << "[4] Funcionarios" << endl;
			cout << "[5] Ramo" << endl;
			cout << "[6] Receita" << endl;
			cout << "[7] Lucro" << endl;
			cout << "[8] Avaliacao" << endl;
			cout << "[9] Todos Dados" << endl;
			
			cin >> option;

			switch (option)
			{
			case 9:

				cout << "Numero de Inscricao : ";
				cin >> aux.numInscricao;
				cin.ignore();
				cout << "Nome : ";
				cin.getline(aux.nome,30);
				cout << "Porte : ";
				cin >> aux.porte;
				cout << "Funcionarios : ";
				cin >> aux.funcionarios;
				cout << "Ramo : " ;
				cin >> aux.ramo;
				cout << "Receita : ";
				cin >> aux.receita;
				cout << "Lucro : ";
				cin >> aux.lucro;
				cout << "Avaliacao : ";
    			cin >> aux.avaliacao;
				break;

			case 1:
				cout << "Numero de Inscricao : ";
				cin >> aux.numInscricao;
				break;
			case 2:
				cout << "Nome : ";
				cin.ignore();
				cin.getline(aux.nome,30);
				break;
			case 3:
				cout << "Porte : ";
				cin >> aux.porte;
				break;	
			case 4:
				cout << "Funcionarios : ";
				cin >> aux.funcionarios;
				break;
			case 5:
				cout << "Ramo : " ;
				cin >> aux.ramo;
				break;
			case 6:
				cout << "Receita : ";
				cin >> aux.receita;
				break;
			case 7:
				cout << "Lucro : ";
				cin >> aux.lucro;
				break;
			case 8:
				cout << "Avaliacao : ";
    			cin >> aux.avaliacao;
				break;

			}

		}
		else{
			i++;
		}
	}

	if(!found){
		cout << "Nao foi encontrada nenhuma empresa \n";
	}
	else{
		arq.seekg(sizeof(Empresa)*i, ios::beg);
		arq.write(reinterpret_cast<const char*>(&aux), sizeof(Empresa));
	}
	
	cout<< "--------------------------------------------- \n\n";
	
}

void remover_empresa(fstream &arq, int num_inscri){ // Remocao logica de uma empresa no arquivo
	bool found = false;
	Empresa aux;

	Empresa removido;
	removido.numInscricao = -1;
	memcpy(removido.nome, "-1",30);
	memcpy(removido.ramo, "-1",25);
	removido.porte = 'a';
	removido.receita = -1;
	removido.lucro = -1;
	removido.funcionarios = -1;
	removido.avaliacao = -1;

	int i=0;
	arq.clear();
	arq.seekp(0, ios::end);
	streampos fileSize = arq.tellg();
	arq.clear();
	int num = fileSize / sizeof(Empresa);
	while(i<num and found == false){
		arq.seekg(sizeof(Empresa)*i, ios::beg);
		arq.read(reinterpret_cast<char*>(&aux), sizeof(Empresa));
		if(aux.numInscricao == num_inscri){
			found = true;
			imprimir_empresa(aux);
		}
		else{
			i++;
		}
	}
	arq.clear();
	arq.seekp(sizeof(Empresa)*i, ios::beg);
	arq.write(reinterpret_cast<const char*>(&removido), sizeof(Empresa));

}

void adicionar_removido(int index, fstream &arq, int num){ // Caso alguma empresa seja removida, a nova é adiciona naquela posição
	Empresa aux;
			cout << "Numero de Inscricao : ";
			cin >> aux.numInscricao;
			cin.ignore();
			cout << "Nome : ";
			cin.getline(aux.nome, 30);;
			cout << "Porte : ";
			cin >> aux.porte;
			cout << "Funcionarios : ";
			cin >> aux.funcionarios;
			cout << "Ramo : " ;
			cin >> aux.ramo;
			cout << "Receita : ";
			cin >> aux.receita;
			cout << "Lucro : ";
			cin >> aux.lucro;
			cout << "Avaliacao : ";
    		cin >> aux.avaliacao;
    arq.seekp(sizeof(Empresa)*index, ios::beg);
    arq.write(reinterpret_cast<const char*>(&aux), sizeof(Empresa));
    
}

Empresa *atualizar_vetor(Empresa *empresas, fstream &arq, int &num){ // Atualiza o vetor para que funcoes sejam executadas corretamente
	int new_size=0;
	Empresa temp;

	delete[] empresas;
	arq.clear();
	arq.seekg(0, ios::end);
	streampos fileSize = arq.tellg();
	arq.clear();
	int registros = fileSize / sizeof(Empresa);

	for(int i=0; i<registros; i++){
		arq.seekg(sizeof(Empresa)*i, ios::beg);
		arq.read(reinterpret_cast<char*>(&temp), sizeof(Empresa));
		if(temp.numInscricao != -1){
			new_size++;
		}
	}
	Empresa *aux = new Empresa[new_size];
	arq.clear();

	for(int i=0; i<registros; i++){
		arq.seekg(sizeof(Empresa)*i, ios::beg);
		arq.read(reinterpret_cast<char*>(&temp), sizeof(Empresa));
		if(temp.numInscricao != -1){
			aux[i] = temp;
		}
	}
	num = new_size;
	return aux;

}

void salvar(Empresa empresas[],int num,string campos){ // Salva os dados alterados ou adicionados a um novo arquivo CSV
	string nome_arquivo;

	cout << "Digite o nome que deseja para salvar o arquivo (sem extensao) : ";
	cin >> nome_arquivo;

	ofstream arq_save(nome_arquivo+".csv");
	cout << "ABRIU ";
	arq_save << campos << endl << num << endl;


	for (int index=0;index < num;index++){
		if(empresas[index].numInscricao != -1){
		arq_save << fixed << setprecision(2);
		arq_save <<
		empresas[index].nome << "," <<
		empresas[index].ramo << "," << 
		empresas[index].numInscricao << "," << 
		empresas[index].porte << "," << 
		empresas[index].funcionarios << "," <<
		empresas[index].receita << "," << 
		empresas[index].lucro << "," << 
		empresas[index].avaliacao << endl;
	}

	}
	arq_save.close();
	cout << endl << "Arquivo " << nome_arquivo <<".csv salvo com sucesso" << endl;

}

void criar_binario(Empresa *vetor,string nome,int tamanho){ // Cria um arquivo binario e adiciona a ele o conteudo de um vetor
	ofstream arq(nome+".bin",ios::binary);
	if (!arq){
		cout << "ERRO";
	}
	arq.write((const char *)(vetor), tamanho*sizeof(Empresa));
	arq.close();
	}

void salvar_binario(Empresa *vetor,fstream &arquivo, int tamanho){ //Salva o arquivo binario
	arquivo.clear();
	arquivo.seekp(0,ios::beg);
	arquivo.write((const char *)(vetor), tamanho*sizeof(Empresa));
	}


fstream arquivo_binario(string nome_arq){ // Retorna um arquivo binario
	fstream arq(nome_arq+".bin", ios::binary|ios::in|ios::out|ios::ate);
	return arq;
}
	


int main(){
	string campos;
	Empresa *empresas = NULL;
	string nome_arq = "";
	int num, option=-1;
	int num_insc;
	cout << "Carregar dados CSV ou Binarios? : " << endl << "[1] CSV"<<endl<<"[2] BIN" << endl <<"Opcao : ";
	int option_arq;
	cin >> option_arq;
	cout << "Nome do arquivo (sem extensao) : ";
	cin >> nome_arq;
	if (option_arq == 1){
		ifstream arquivo_csv(nome_arq+".csv");
		if(!arquivo_csv){
			cout << "Arquivo não encontrado";
			return 0;
		}
		
		getline(arquivo_csv, campos);
		arquivo_csv >> num;
		arquivo_csv.ignore();

		cout<< "---------------------------------------------"<< endl;
		cout<<"Dados importados com sucesso!" << endl;
		cout << "Total de registros : " << num << endl;
		
		empresas = new Empresa[num];
		for(int i=0; i<num; i++){
			empresas[i] = leitura(arquivo_csv);
		}
		criar_binario(empresas,nome_arq,num);
		arquivo_csv.close();
	}

	else if(option_arq == 2){
		fstream arquivo = arquivo_binario(nome_arq);

		if (!arquivo) {
			cout << "Erro ao abrir o arquivo." << endl;
			return 0;
    	}
		cout<< "---------------------------------------------"<< endl;
    	cout<<"Dados importados com sucesso!" << endl;
		streampos fileSize = arquivo.tellg();
		arquivo.clear();
		num = fileSize / sizeof(Empresa);
		cout << "Total de registros : " << num << endl;
		empresas = new Empresa[num];
		arquivo.seekg(0, ios::beg);
		arquivo.clear();
		arquivo.read(reinterpret_cast<char*>(empresas), fileSize);
		arquivo.close();

	}

	fstream arquivo = arquivo_binario(nome_arq);

    while(option !=0){
        cout<< "---------------------------------------------"<< endl;
        cout<< "[1] Mostrar Dados"<< endl;
        cout<< "[2] Adicionar Empresa"<< endl;
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

        if(option == 1){
			cout << "N Inscricao Nome Porte Ramo Funcionarios Receita Lucro Avaliacao \n";
            imprimir_all(arquivo,num);
        }
        if(option == 2){
			Empresa aux;
			int index = -1;
			
			arquivo.clear();
			for (int i = 0; i < num; i++){ // Loop para encontrar alguma empresa removida
				arquivo.seekg(sizeof(Empresa)*i, ios::beg);
				arquivo.read(reinterpret_cast<char*>(&aux), sizeof(Empresa));
				if(aux.numInscricao == -1){
					index = i;
				}
			}
			if(index != -1){
				adicionar_removido(index,arquivo,num);
				}
			
            else if (index == -1)
				empresas = adicionar_empresa(num,nome_arq,empresas);
        }

		if(option == 3){
			int opcao;
			cout << "[1] Numero de Inscricao" << endl;
			cout << "[2] Porte" << endl;
			cout << "[3] Ramo" << endl;
			cout << "[4] Nome" << endl;

			cin >> opcao;
			switch (opcao){
			case 1:
			{	
				cout << "Digite o numero de inscricao : ";
				int num_inscri;
				cin >> num_inscri;
            	buscar_inscricao(num_inscri,num,arquivo);
				break;
			}
			case 2:
			{
				char porte;
				cout << "Qual porte? (P,M,G): ";
				cin >> porte;
            	buscar_porte(porte,num,arquivo);
				break;
			}
			case 3:
			{
				string ramo;
				cout << "Digite o ramo : ";
				cin >> ramo;
				buscar_ramo(ramo,num,arquivo);
				break;
			}
			case 4:
			{
				string nome;
				cin.ignore();
				cout << "Digite o nome : ";
				getline(cin,nome);
				buscar_nome(nome,num,arquivo);
				break;
			}	
        }
		}

		if(option == 4){

			cout << "Digite o numero de inscrição : ";
			cin >> num_insc;
			editar(num_insc,arquivo,num);
		}

		if(option == 5){

			cout << "Digite o numero de inscrição : ";
			cin >> num_insc;
			remover_empresa(arquivo, num_insc);
		}

		if (option == 6){
			cout << "Salvar para binário ou CSV? [1]Binario [2]CSV : ";
			int opt;
			cin >> opt;
			if(opt == 1){
				string nome_arquivo;
				cout << "Nome do arquivo :";
				cin >> nome_arquivo; 
				criar_binario(empresas,nome_arquivo,num);
			}
			else{
			empresas = atualizar_vetor(empresas,arquivo,num);
			salvar(empresas, num, campos);
			}
		}
		if (option == 7){
			int opt;
			cout << "Ordernar por :"<< endl <<"[1] Numero de Inscricao" << endl << "[2] Nome" << endl;
			cin >> opt;
			if(opt == 1){
				empresas = atualizar_vetor(empresas,arquivo,num);
				quicksort(empresas, 0, num-1);
				salvar_binario(empresas,arquivo,num);
				}
			else if(opt == 2){
				empresas = atualizar_vetor(empresas,arquivo,num);
				quicksort_nome(empresas,0,num-1);
				salvar_binario(empresas,arquivo,num);
				}
		}
		if (option == 8){
			int inicio,fim;
			cout << "Inicio : ";
			cin >> inicio;
			cout << "Fim : ";
			cin >> fim;
			imprimir_trecho(arquivo,inicio,fim);
			}

    }

	cout << "Deseja exportar os dados para CSV antes de sair? [1] Sim / [2] Nao : ";
	cin >> option;
	if (option == 1){
		salvar(empresas,num,campos);
	}

	cout << endl<<"Programa encerrado, obrigado por utilizar";

	arquivo.close();


    return 0;
}
