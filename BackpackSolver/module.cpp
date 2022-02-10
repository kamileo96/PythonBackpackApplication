#include <Python.h>
#include <Windows.h>
#include<iostream>
#include <stdio.h>
using namespace std;

double SumCombination(bool* combo, double* items, int len) {
    //zwraca sum� item�w w danej kombinacji
    double s = 0;
    for (int i = 0; i < len; i++) {
        s += items[i] * combo[i];
    }
    return s;
}
void ChangeCombination(bool* combo, int len) {
    //bitowe dodawanie mojego, nie chwal�c si�, autorstwa
    bool carry = true;
    int i = 0;
    while (carry && i < len) {
        combo[i] = !combo[i];
        carry = !combo[i];
        i++;
    }
}
bool IsNonzero(bool* combo, int len) {
    //patrzy czy przeszli�my przez wszystkie kombinacje (dodawanie jest modulo len)
    bool res = false;
    for (int i = 0; i < len; i++) {
        res = res || combo[i];
    }
    return res;
}
static PyObject* Solve(PyObject* self, PyObject* args)
{
    //zwraca list� przedmiot�w najbardziej wype�niaj�c� plecak
    int len;
    double p = 0, sum = 0;
    PyObject* PV;
    PyObject* obj;
    PyObject* seq;
    PyObject* itm;
    //Dwa obiekty: float/int oraz lista floatow/intow, dlatego "OO"
    if (!PyArg_ParseTuple(args, "OO", &PV, &obj))
        return NULL;
    double V = PyFloat_AsDouble(PV); //dzia�a te� dla int�w
    seq = PySequence_Fast(obj, "Expected a sequence");
    len = int(PySequence_Size(obj));


    double* items = new double[len];

    PyObject* results = PyList_New(0);
    for (int i = 0; i < len; i++) {
        itm = PyList_GET_ITEM(seq, i);
        if (PyFloat_Check(itm)) {
            p = PyFloat_AsDouble(itm);
        }
        else if (PyLong_Check(itm)) {
            p = (double)PyLong_AsLong(itm);
        }
        else
        {
            //zasadniczo to sprawdzanie nie super potrzebne, bo dzia�a dla int�w, ale wtedy mo�na wy�wietli� ten b��d:
            cout << "Error: wrong type of " << i << ". variable\n";
            return results;
        }
        items[i] = p;
        sum += p;
    }
    //to oszcz�dzi (?) na niekt�rych kombinacjach
    if (sum < V) { return obj; }
    //zapewne mo�naby te� np sprawdza� czy itemy nie s� wi�ksze od V, etc, ale za��my �e biblioteka jest u�ywana rozs�dnie.
    //true oznacza �e i-ty item jest w hipotetycznej kombinacji
    bool* combo = new bool[len];
    bool* maxCombo = new bool[len];
    for (int i = 0; i < len; i++) {
        combo[i] = 0;
        maxCombo[i] = 0;
    }
    //�eby nie wywali�o w trakcie p�tli (?)
    bool keepChecking = true;
    double maxS = 0;
    double s;
    //po wszystkich kombinacjach:
    while (keepChecking) {
        s = SumCombination(combo, items, len);
        if (s <= V && s > maxS) {
            //nie wiem ile zajmuje ten krok, ale mo�liwe �e szybciej by�oby i�� od g�ry,
            //wtedy rzadziej musieliby�my zmienia� maxCombo
            //mo�liwe �e szybsze by�oby zastosowanie int SC = sum(combo), ale nie chcia�em ogranicza� ze wzgl�du na len
            for (int i = 0; i < len; i++) {
                maxCombo[i] = combo[i];
            }
            maxS = s;
        }
        ChangeCombination(combo, len);
        keepChecking = IsNonzero(combo, len);
    }
    //formu�ujemy wynik (results teraz jest pust� PyList�):
    for (int i = 0; i < len; i++) {
        p = items[i];
        if (maxCombo[i]) {
            PyList_Append(results, PyFloat_FromDouble(p));
        }
    }
    //cout << "For a volume of " << V << " the maximum volume of items is " << maxS << ".\n";
    return results;
}
//opr�cz https://docs.python.org/3/extending/extending.html
//bardzo pomocne by�o https://docs.microsoft.com/en-us/visualstudio/python/working-with-c-cpp-python-in-visual-studio?view=vs-2022



static PyMethodDef BackpackSolver_methods[] = {
    // The first property is the name exposed to Python
    // The second is the C++ function with the implementation
    // METH_VARARGS poniewa� chcemy przekaza� kilka argument�w
    { "pakuj_plecak", (PyCFunction)Solve, METH_VARARGS, nullptr },
    // Terminate the array with an object containing nulls.
    { nullptr, nullptr, 0, nullptr }
};

static PyModuleDef BackpackSolver_module = {
    PyModuleDef_HEAD_INIT,
    "BackpackSolver",                        // Module name to use with Python import statements
    "Solves Backpacks",  // Module description
    0,
    BackpackSolver_methods                   // Structure that defines the methods of the module
};

PyMODINIT_FUNC PyInit_BackpackSolver() {
    return PyModule_Create(&BackpackSolver_module);
}