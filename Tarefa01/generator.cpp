#include "generator.h"

int main(void) {
        // formula f;
        // f.number_of_variables = 3;
        // vector<int> c = {1, 2, 3};
        // f.clauses.push_back(c);
        // f.clauses.push_back(c);
        // formulaSMT(f, "nqueens.txt");
        nqueensSMT(4, "nqueens.txt");

}

void nqueensSMT(int n, string file_path) {
        ofstream smt_file;
        smt_file.open("nqueens.txt");
        if(smt_file) {
                // Declaração dos átomos:
                for(int i = 0; i < n; i++)
                        for(int j = 0; j < n; j++)
                                smt_file << "(declare-const q" << i << j << " Bool)" << endl; 
                // Cláusulas das linhas:
                smt_file << "\n; linhas (restrição de ter pelos menos uma rainha por linha)" << endl;
                for(int y = 0; y < n; y++) { // <- linhas
                        smt_file << "(assert (or";
                        for(int x = 0; x < n; x++) { // <- colunas
                                smt_file << " q" << y << x;
                        }
                        smt_file << "))" << endl;
                }                
                smt_file << "\n; linhas (restrição de haver somente uma rainha por linha)" << endl;
                // Cláusulas das linhas:
                for(int y = 0; y < n; y++) { // <- linhas
                        smt_file << "(assert (and";
                        for(int x_i = 0; x_i < n - 1; x_i++) { // <- colunas
                                for(int x_j = x_i + 1; x_j < n; x_j++) { // <- colunas
                                        smt_file << "(not (and" << " q" << y << x_i << " q" << y << x_j << "))";
                                }
                        }
                        smt_file << "))" << endl;
                }
                smt_file << "\n; colunas (restrição de haver somente uma rainha por coluna)" << endl;
                // Cláusulas das colunas:
                for (int x = 0; x < n; x++) { // <- colunas
                        smt_file << "(assert (and";
                        for(int y_i = 0; y_i < n - 1; y_i++) { // <- linhas
                                for(int y_j = y_i + 1; y_j < n; y_j++) { // <- linhas
                                        smt_file << "(not (and" << " q" << y_i << x << " q" << y_j << x << "))";
                                }
                        }
                        smt_file << "))" << endl;
                }
                smt_file << "\n; diagonais inversas (restrição de haver somente uma rainha por diagonal)" << endl;
                // Cláusulas das diagonais:
                // Diagonais inversas começando em y = 0 (exceto em x = n - 1 em que há apenas uma célula):
                for(int x = 0; x < n - 1; x++) {
                        smt_file << "(assert (and";
                        for(int x_i = x, y_i = 0; y_i < n && x_i < n; x_i++, y_i++) {
                                for(int x_j = x_i + 1, y_j = y_i + 1; y_j < n && x_j < n; x_j++, y_j++) {
                                        smt_file << "(not (and" << " q" << y_i << x_i << " q" << y_j << x_j << "))";
                                }
                        }
                        smt_file << "))" << endl;
                }
                // Diagonais inversas começando em x = 0 (exceto em y = n - 1 em que há apenas uma célula e em
                // y = 0 pois essa diagonal já foi contada):
                for(int y = 1; y < n - 1; y++) {
                        smt_file << "(assert (and";
                        for(int x_i = 0, y_i = y; y_i < n && x_i < n; x_i++, y_i++) {
                                for(int x_j = x_i + 1, y_j = y_i + 1; y_j < n && x_j < n; x_j++, y_j++) {
                                        smt_file << "(not (and" << " q" << y_i << x_i << " q" << y_j << x_j << "))";
                                }
                        }
                        smt_file << "))" << endl;
                }
                smt_file << "\n; diagonais principais (restrição de haver somente uma rainha por diagonal)" << endl;
                // Diagonais principais começando em y = n-1 (exceto em x = n - 1 em que há apenas uma célula):
                for(int x = 0; x < n - 1; x++) {
                        smt_file << "(assert (and";
                        for(int x_i = x, y_i = n-1; (0 <= y_i) && (x_i < n); x_i++, y_i--) {
                                for(int x_j = x_i + 1, y_j = y_i - 1;  (0 <= y_j) && (x_j < n); x_j++, y_j--) {
                                        smt_file << "(not (and" << " q" << y_i << x_i << " q" << y_j << x_j << "))";
                                }
                        }
                        smt_file << "))" << endl;
                }
                // Diagonais principais começando em x = 0 (exceto em y = 0 em que há apenas uma célula
                // e em y = n - 1 pois esta diagonal já foi contada):
                for(int y = 1; y < n - 1; y++) {
                        smt_file << "(assert (and";
                        for(int x_i = 0, y_i = y; (0 <= y_i) && (x_i < n); x_i++, y_i--) {
                                for(int x_j = x_i + 1, y_j = y_i - 1; (0 <= y_j) && (x_j < n); x_j++, y_j--) {
                                        smt_file << "(not (and" << " q" << y_i << x_i << " q" << y_j << x_j << "))";
                                }
                        }
                        smt_file << "))" << endl;
                }               
                smt_file << "\n(check-sat)" << endl; 
                smt_file << "(get-model)" << endl;
        }
        smt_file.close();
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