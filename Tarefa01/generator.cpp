#include "generator.h"

int main(void) {
        formula f;
        f.number_of_variables = 3;
        vector<int> c = {1, 2, 3};
        f.clauses.push_back(c);
        generateSMT(f, "nqueens.txt");

}

void generateSMT(formula &f, string file_path) {
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