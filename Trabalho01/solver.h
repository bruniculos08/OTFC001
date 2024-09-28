// Implementação do algoritmo DPLL
// Alunos: Bruno R. dos Santos e Helena Vargas

#include <bits/stdc++.h>

using namespace std;

typedef struct Formula
{
        int number_of_variables;
        vector<vector<int>> clauses;
} formula;

// Função para ler arquivo no formato CNF:
void fromFileGenerateSAT(formula &f , string file_path);
// Função DPLL:
bool DPLL(formula f, vector<int> atoms);
// Função de simplificação:
formula simplify(formula f, vector<int> &atoms); 
// Função para imprimir fórmula:
void printFormula(formula &f);
// Função para imprimir valoração dos átomos:
void printFormula(formula &f);