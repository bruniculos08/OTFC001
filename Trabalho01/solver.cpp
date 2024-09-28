#include "solver.h"

int main(void) {

        formula f;
        fromFileGenerateSAT(f, "sat.cnf");
        vector<int> atoms(f.number_of_variables, -1);
        printFormula(f);
        f = simplify(f, atoms);
        printFormula(f);

        cout << f.clauses.size() << endl;

        cout << "é satisfátivel? " << ((DPLL(f, atoms)) ? "sim" : "não") << endl;
        return 0;
}

void printFormula(formula &f) {
        for(int i = 0; i < f.clauses.size(); i++) {
                if(i > 0) cout << " /\\ ";
                cout << "(";
                for(int j = 0; j < f.clauses[i].size(); j++) {
                        if(f.clauses[i][j] >= 0) cout << f.clauses[i][j];
                        else cout << "¬" << abs(f.clauses[i][j]);
                        if(j < f.clauses[i].size() - 1) cout << " \\/ ";
                }
                cout << ")";
        }
        cout << endl;
}

void fromFileGenerateSAT(formula &f, string file_path) {
        ifstream my_file (file_path); 
        string line;
        char *cstr = new char[1024];
        int number_of_variables, number_of_clauses, tmp;

        assert(my_file.is_open());
        do {
                getline(my_file, line); 
        }
        while(line[0] == 'c');

        strcpy(cstr, line.c_str());
        sscanf(cstr, "p cnf %i %i\n", &number_of_variables, &number_of_clauses);

        for(int i = 0; i < number_of_clauses && getline(my_file, line); i++) {  
                if(line[0] == 'c'){
                        i--;
                        continue;
                }
                vector<int> c_i;
                while(line[0] != '0') {
                        strcpy(cstr, line.c_str());
                        sscanf(cstr, "%d %*s", &tmp);
                        line = line.substr(line.find(' ') + 1, -1);
                        c_i.push_back(tmp);
                }
                f.clauses.push_back(c_i);
        }
        f.number_of_variables = number_of_variables;
}

bool DPLL(formula f, vector<int> atoms) {
        // Vamos considerar 0 como 'true', 1 como  'false' e -1 com '*':
        formula g = simplify(f, atoms);
        if(g.clauses.size() == 0)
                return true;
        // O bottom será representado aqui por um vector<int> de tamanho 0:
        else for(vector<int> &c : g.clauses)
                if(c.size() == 0) return false;
        // Escolhendo um literal l tal que v(l) = *:
        vector<int> l_clause;
        for(vector<int> &c : f.clauses)
                for(int l : c) 
                        if(atoms[abs(l) - 1] == -1)
                        {
                                l_clause.push_back(l);
                                goto label;
                        }
        label:
        atoms[abs(l_clause[0]) - 1] = ((l_clause[0] > 0) ? 1 : 0);
        g.clauses.push_back(l_clause);
        // Tem que setar o valor dos atomos pra 1 ou 0;
        if(DPLL(g, atoms))
                return true;
        g.clauses.pop_back();
        l_clause[0] = l_clause[0] * -1;
        atoms[abs(l_clause[0]) - 1] = ((l_clause[0] > 0) ? 1 : 0);
        g.clauses.push_back(l_clause);
        return DPLL(g, atoms);
}

formula simplify(formula f, vector<int> &atoms) {
        for(int i = 0; i < f.clauses.size(); i++) {
                if(f.clauses[i].size() == 1) {
                        int l = f.clauses[i][0];
                        atoms[abs(l) - 1] = ((l > 0) ? 1 : 0);
                        // cout << "clausula unitaria: " << l << endl;
                        
                        for(int j = 0; j < f.clauses.size(); j++) {
                                for(int k = 0; k < f.clauses[j].size(); k++)
                                        if(f.clauses[j][k] == l) {
                                                f.clauses.erase(f.clauses.begin() + j);
                                                j--;
                                                break;
                                        }
                                        else if(f.clauses[j][k] == -l) {
                                                f.clauses[j].erase(f.clauses[j].begin() + k);
                                                k--;
                                        }
                        }
                        i = -1;
                }
        }
        return f;
}