// Aluno: Bruno R. dos Santos

#include <bits/stdc++.h>

using namespace std;

typedef struct Formula
{
        int number_of_variables;
        vector<vector<int>> clauses;
} formula;

// Função para gerar arquivo SMT:
void nqueensSMT(int n, string file_path);
void formulaSMT(formula &f , string file_path);