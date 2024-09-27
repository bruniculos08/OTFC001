#include "generator.h"

int main(void) {
        formula f;
        f.number_of_variables = 3;
        vector<int> c = {1, 2, 3};
        f.clauses.push_back(c);
        f.clauses.push_back(c);
        formulaSMT(f, "nqueens.txt");

}

void nqueensSMT(int n, string file_path) {
        ofstream smt_file;
        smt_file.open("nqueens.txt");
        if(smt_file) {
                // Declaração dos átomos:
                for(int i = 1; i <= n; i++)
                        for(int j = 1; j <= n; j++)
                                smt_file << "(declare-const q" << i << j << " Bool)" << endl; 
                // Cláusulas das linhas:
                for(int i = 1; i <= n; i++) { // <- linhas
                        smt_file << "(assert (and";
                        for(int j = 1; j <= n - 1; j++) { // <- colunas
                                for(int k = j + 1; k <= n; k++) { // <- colunas
                                        smt_file << "(not (and" << " q" << (10 * i + j) << " q" << (10 * i + k) << "))";
                                }
                        smt_file << "))" << endl;
                        }
                }
                // Cláusulas das colunas:
                for (int j = 1; j <= n; j++) { // <- colunas
                        smt_file << "(assert (and";
                        for(int i = 1; i <= n; i++) { // <- linhas
                                for(int h = 1; h <= n; h++) { // <- linhas
                                        smt_file << "(not (and" << " q" << (10 * i + j) << " q" << (10 * h + j) << "))";

                                }
                        smt_file << "))" << endl;
                        }
                }
                // Cláusulas das diagonais:
                // Lembrete sobre coeficiente linear da reta (pensando no tabuleiro como um gráfico cartesiano): 
                //       (i) Para diagonais inversas tem-se a seguinte equação:
                //              1 * coluna + b = linha <-> b = linha - coluna
                //       (i) Para diagonais principais tem-se a seguinte equação:
                //              (-1) * coluna + b = linha <-> b = linha + coluna
                vector<pair<int,int>> empty;
                vector<vector<pair<int,int>>> main_diags(2 * n - 1, empty);
                vector<vector<pair<int,int>>> inv_diags(2 * n - 1, empty);
                // Note que:
                //      2 * n - 1 => quantidade de diagonais principais
                //      2 * n - 1 => quantidade de diagonais inversas
                //      2 * (2 * n - 1) => quantidade total de diagonais
                for(int y = 1; y <= n; y++) // <- linhas
                        for(int x = 1; x <= n; x++) { // <- colunas
                                pair<int, int> q = make_pair(y, x);
                                int b_main = y - x;
                                int b_inv = y + x;
                                int index_main = (b_main + (n - 1));
                                int index_inv = b_inv - 1;
                                main_diags[index_main].push_back(q);
                                inv_diags[index_inv].push_back(q);
                        }
                // Escrevendo no arquivo as cláusulas das diagonais:
                for(auto &diag : main_diags) {
                        for(auto &q : diag) {
                                int y = q.first;
                                int x = q.second;
                                
                        }        
                }
                
                                

                smt_file << "(check-sat)" << endl; 
                smt_file << "(get-model)" << endl; 
        }
}

void formulaSMT(formula &f, string file_path) {
        ofstream smt_file;

        smt_file.open("nqueens.txt");

        if(smt_file) {
                for(int i = 0; i < f.number_of_variables; i++) {
                        smt_file << "(declare-const q" << i+1 << " Bool)" << endl; 
                }
                for(auto &x : f.clauses) {
                        smt_file << "(assert (or";
                        for(int i = 0; i < x.size(); i++) {
                                smt_file << " q" << x[i]; 
                        }
                        smt_file << "))" << endl; 
                }
                smt_file << "(check-sat)" << endl; 
                smt_file << "(get-model)" << endl; 
        }
}