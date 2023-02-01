#include <iostream>
#include <fstream>
#include "hash_table.h"
#include "lex_analys.h"
#include "syntax_analys.h"
#include "semantic_analysator.h"

int main() {
    setlocale(0, "RUS");
    hash_table table;
    lex_analysator lex;
    synt_analysator anal("input.txt");
    std::ofstream fout("result.txt");
    std::string str = "";
    if (anal.analys(anal.tree)) {
        semantic_analysator kukaji("polska.txt", anal.tree, anal.table);
        if (!kukaji.Function())
            return 0;
        std::cout << "Программа завершила работу с кодом 0.";
        anal.print_tree(fout);
    }

    fout.close();
	return 0;
}