#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int backtracking(vector <pair <int, int> >*, vector<int>, int, int);
void Confiable(vector <pair <int, int> >*, vector<int>, int, int);
void NoConfiable(vector <pair <int, int> >*, vector<int>, int, int);
bool VerConfiabilidad(vector <pair <int, int> >*, vector<int>*, int);
bool aux(vector <pair <int, int> >*, vector <int>, pair<int, int>); //Funcion que cheque la el pair matchee en el vector <int>*
bool EnConj(int, vector<int>); //verifica que el int este en vector<int>
bool modulo(int, int) ;//Dice si dos numeros son iguales en modulo

int res = 0; //variable global que guardara el mejor resultado

int main(){
	while(true){
		int agentes;
		int cantEncuestas;
		cin >> agentes;
		cin >> cantEncuestas;

		vector<pair <int, int> > Encuestas;
		vector<int> ConjAgentes; //Conj que ira guardando los agentes confiables

		if(agentes > 0 && cantEncuestas >= 0){
			while(cantEncuestas > 0){ //Me guardo las encuestas en el vector Encuentas
				int a;
				int b;
				cin >> a;
				cin >> b;
				Encuestas.push_back(pair <int,int>(a,b));
				cantEncuestas--;
			}
				backtracking(&Encuestas, ConjAgentes, 1, agentes);
				cout << res << endl;
				res = 0;
				//cout << res << endl;
		}else{
			break;
		}
	}
	return 0;
}

int backtracking(vector <pair <int, int> >* encuestas, vector <int> ConjAgentes, int i, int agentes){
	if(i > agentes){	
		return res;
	}
	Confiable(encuestas, ConjAgentes, i, agentes);
	NoConfiable(encuestas, ConjAgentes, i, agentes);
}

void Confiable(vector <pair <int, int> >* Encuestas, vector<int> ConjAgentes, int i, int agentes){
	int a = i;
	a++;
	if(i <= agentes){
		if((VerConfiabilidad(Encuestas, &ConjAgentes, i))){ //VerConfiabilidad agrega a i al conjAgente si es confiable
			if(ConjAgentes.size() > res){
				res = ConjAgentes.size();
			}
			backtracking(Encuestas, ConjAgentes, a, agentes);
		}else{
			backtracking(Encuestas, ConjAgentes, a, agentes);
		}
	}
	return;
}

void NoConfiable(vector <pair <int, int> >* Encuestas, vector<int> ConjAgentes, int i, int agentes){
	if(i <= agentes){
		int a = i;
		a++;
		backtracking(Encuestas, ConjAgentes, a, agentes);
	}
	return;
}



bool VerConfiabilidad(vector <pair <int, int> >* Encuestas, vector <int>* ConjAgentes, int i){
	int n = 0;
	bool guarda = true;
	while(n < Encuestas->size()){
		if((*Encuestas)[n].first == i){
			guarda = guarda && aux(Encuestas, *ConjAgentes, (*Encuestas)[n]); //Veo que la encuesta de i matchee con el conjAgente
		}
		if(EnConj((*Encuestas)[n].first, *ConjAgentes)){
			int z = (*Encuestas)[n].second;
			if(modulo(z, i)){
				guarda = guarda && ((*Encuestas)[n].second == i ); //Veo que nadie en el conjunto desconfie de i
			}	
		}
		n++;
	}
	if(guarda){
		ConjAgentes->push_back(i);
	}
	return guarda;
}

bool aux(vector<pair <int, int> >* Encuestas, vector<int> ConjAgentes, pair<int,int> Ei){
	int n = 0;
	bool guarda = true;
	if(Ei.first == (Ei.second*(-1))){
		return false;
	}
	while(n < Encuestas->	size()){
		if(EnConj((*Encuestas)[n].first, ConjAgentes)){
			//Caso donde Ei confia o desconfia en alguien, y puede que otro agente ya en el
			//conjunto de confiables opine distinto
			if(modulo((*Encuestas)[n].second, Ei.second)){ 
				guarda = guarda && ((*Encuestas)[n].second == Ei.second);
				guarda = guarda && VerConfiabilidad(Encuestas, &ConjAgentes, Ei.second);
			}
			//Caso donde Ei desconfia en alguien que ya esta en el conjunto
			if(modulo((*Encuestas)[n].first, Ei.second)){
				guarda = guarda && (Ei.second == (*Encuestas)[n].first);
			}
		}
		n++;
	}
	return guarda;
}

bool modulo(int a, int b){
	if(a <0){
		a = (a*(-1));
	}
	if(b <0){
		b = (b*(-1));
	}
	return a==b;	
}

bool EnConj(int i, vector<int> ConjAgentes){
	int n = 0;
	while(n < ConjAgentes.size()){
		if(ConjAgentes[n] == i){
			return true;
		}
		n++;
	}
	return false;
}