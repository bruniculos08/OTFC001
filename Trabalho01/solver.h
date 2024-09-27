// Implementação do algoritmo DPLL
// Alunos: Bruno R. dos Santos e Helena Vargas

#include <bits/stdc++.h>

using namespace std;

typedef struct Formula
{
        int number_of_variables;
        vector<vector<int>> clauses;
} formula;

// Função para ler arquivo no formato CNF (retorna o número de clausulas):
void fromFileGenerate3SAT(formula &f , string file_path);
// Função DPLL:
bool DPLL(formula f);
// Função de simplificação:
formula simplify(formula f); 