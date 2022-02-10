#include "Backpack.h"
#include <iostream>
using namespace std;
Backpack::Backpack(double nVolume) {
	items = {-1337.};
	Volume = nVolume;
	//isSolved = false;
};
double Backpack::GetVolume() { 
	return Volume; 
}
void Backpack::SetVolume(double V) {
	Volume = V;
	//isSolved = false;
}
void Backpack::AddItem(double x) {
	items.push_back(x);
	//if(items[0] == -1337.){ items.erase(items.begin());} //z jakiegoœ powodu startowanie z pustego wektora wywala ca³y program
	cout << items[0] << items[1] << "\n";
	cout << "Added item of weight: " << x << " = " << items[items.size()-1] << " out of " << items.size() << " \n";
	cout << items[0] << items[1] << "\n";
	cout << items.size() << "\n";
	if(items.size() == 4){ cout << items[0] << items[1] << items[2] << items[3] << "\n"; }
	//isSolved = false;
}
void Backpack::EmptyTheBackpack() {
	items = {};
	//isSolved = false;
}
void Backpack::ChangeCombination(vector<bool> &combo) {
	combo[0] = !combo[0];
	for (int i = 1; i < combo.size(); i++) {
		combo[i] = combo[i] == combo[i - 1];
	}
}
void Backpack::SolveSelf() {
	cout << "Solving self\n";
	//if (isSolved) { cout << "You fool! It appears i am already solved!\n"; }
	vector<double> res = {};
	
	//tymczasowo niech res = najwiekszy element mniejszy od Volume
	res = { 0. };
	double it;
	cout << items[0] << items[1] << items[2] << "\n";
	for (int i = 0; i < items.size(); i++) {
		it = items[i];
		cout << "Checking if " << it << " is less than " << Volume << " and bigger than " << res[0] << "\n";
		if (it < Volume && it > res[0]) {
			res[0] = it;
			cout << "New largest is " << it << "\n";
		}
	}

	//ale powinno byæ:
	double max_weight = 0.;
	vector<bool> combination = {};
	for (int i = 0; i < items.size(); i++) {
		combination.push_back(0);
	}
	//isSolved = true;
	results = res;
}

vector<double> Backpack::GetResults() {
	//if (!isSolved) {
		SolveSelf();
	//}
	return results;
}

