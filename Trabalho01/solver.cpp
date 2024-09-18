#include "solver.h"

int main(void) {
        formula f;
        fromFileGenerate3SAT(f, "sat.cnf");
        cout << f.clauses.size() << endl;

        for(int i = 0; i < f.clauses.size(); i++) {
                cout << "(";
                for(int x_i : f.clauses[i]) {
                        if(x_i >= 0) cout << x_i << " ";
                        else cout << "¬" << abs(x_i) << " ";
                }
                cout << ")" << endl;
        }
        return 0;
}

void fromFileGenerate3SAT(formula &f, string file_path) {
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
}