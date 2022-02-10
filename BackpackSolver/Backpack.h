#pragma once
#include<vector>

using namespace std;
class Backpack
{
	vector<double> items;
	vector<double> results;
	double Volume;
	//bool isSolved;

	void SolveSelf();
	void ChangeCombination(vector<bool> &combo);
public:
	Backpack(double nVolume);
	double GetVolume();
	void SetVolume(double V);
	void AddItem(double x);
	void EmptyTheBackpack();
	vector<double> GetResults();
};

