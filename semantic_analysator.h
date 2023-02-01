#ifndef SEMANTIC_ANALYSATOR_H
#define SEMANTIC_ANALYSATOR_H
#include "hash_table.h"
#include "syntax_analys.h"
#include "syntax_tree.h"
#include <iostream>

class semantic_analysator {
private:
	std::ofstream fout;
	syntax_tree tree;
	hash_table table;
public:
	semantic_analysator(std::string filename, syntax_tree tr, hash_table tab) :
		fout(filename),
		tree(tr),
		table(tab) {};
	~semantic_analysator() { fout.close(); }
	bool Function();
	bool Begin();
	bool Descriptions();
	bool Varlist(std::shared_ptr<node_tree> n_t, std::string);
	bool Operators(std::shared_ptr<node_tree> n_t);
	bool Expr(std::shared_ptr<node_tree> n_t, std::string s);
	bool Condition(std::shared_ptr<node_tree> n_t, std::string s);
	bool S1mpleExpr(std::shared_ptr<node_tree> n_t, std::string s);
	bool End();
};

#endif // !SEMANTIC_ANALYSATOR_H

