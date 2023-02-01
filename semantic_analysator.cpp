#include "semantic_analysator.h"

std::string get_lexeme(std::string s) {
	std::string temp = "";
	for (auto elem : s) {
		if (elem == ' ')
			return temp;
		temp += elem;
	}
	return temp;
}

bool semantic_analysator::Function() {
	//node root1 = synt_analysator::tree.root;
	if (!Begin())
		return 0;
	if (!Descriptions())
		return 0;
	if (!Operators(tree.root->net_nichego_vajnee_semji[2]))
		return 0;
	if (!End())
		return 0;
	tree.root->polska += tree.root->net_nichego_vajnee_semji[0]->polska +
		tree.root->net_nichego_vajnee_semji[1]->polska +
		tree.root->net_nichego_vajnee_semji[2]->polska +
		tree.root->net_nichego_vajnee_semji[3]->polska;
	fout << tree.root->polska;
	return 1;
}

bool semantic_analysator::Begin() {
	auto begin = tree.root->net_nichego_vajnee_semji[0];
	begin->polska += get_lexeme(begin->net_nichego_vajnee_semji[0]->field) + " ";
	begin->polska += get_lexeme(begin->net_nichego_vajnee_semji[1]->field);
	begin->polska += " 2 FUNCTION\n";
	//помечаем, что мейн интовый
	table.set_atribute(get_lexeme(begin->net_nichego_vajnee_semji[1]->field),
		get_lexeme(begin->net_nichego_vajnee_semji[0]->field));
	return 1;
}

bool semantic_analysator::Descriptions() {
	auto descriptions = tree.root->net_nichego_vajnee_semji[1];
	//идЄм по дескрам
	for (auto &elem : descriptions->net_nichego_vajnee_semji) {
		if (!Varlist(elem->net_nichego_vajnee_semji[1], "int"))
			return 0;
		int number_of_variables = (elem->net_nichego_vajnee_semji[1]->get_childs().size() + 1) / 2;
		descriptions->polska += elem->net_nichego_vajnee_semji[1]->polska;
		descriptions->polska += "int ";
		descriptions->polska += std::to_string(number_of_variables) + " " + "DECLARATION\n";
	}
	return 1;
}

bool semantic_analysator::Varlist(std::shared_ptr<node_tree> n_t, std::string s) {
	auto varlist = n_t;
	for (int i = 0; i < n_t->get_childs().size(); i += 2) {
		auto temp1 = n_t->net_nichego_vajnee_semji[i];
		info infa(temp1->field);
		if (table.find(infa).atribute == "int") {
			std::cout << "\nѕеременна€ ранее объ€вл€лась!\n";
			return 0;
		}
		varlist->polska = infa.lexem + " " + varlist->polska;
		table.set_atribute(get_lexeme(temp1->field), s);
	}
	return 1;
}

bool semantic_analysator::Operators(std::shared_ptr<node_tree> n_t) {
	auto operators = n_t;
	//идЄм по ќѕјћ
	for (auto& elem : operators->net_nichego_vajnee_semji) {
		info infa(elem->net_nichego_vajnee_semji[0]->field);
		if (infa.type == "FOR") {
			info infa2(elem->net_nichego_vajnee_semji[2]->field);
			if (table.find(infa2).atribute != "int") {
				std::cout << "\nѕеременна€ не была объ€влена, дурила!\n";
				return 0;
			}
			std::string buff = "";
			std::string znak = "=";
			buff = infa2.lexem + " " + znak + " ";
			if (!Expr(elem->net_nichego_vajnee_semji[4], "int"))
				return 0;
			buff += "m1 DECLARATION ";
			buff = elem->net_nichego_vajnee_semji[4]->polska + buff;
			if (!Condition(elem->net_nichego_vajnee_semji[6], "int"))
				return 0;
			buff += elem->net_nichego_vajnee_semji[6]->polska + " " + "m2 BF ";
			if (!Expr(elem->net_nichego_vajnee_semji[8], "int"))
				return 0;
			buff += elem->net_nichego_vajnee_semji[8]->polska  + "m1 BRL m2 DEFL\n";
			if (!Operators(elem->net_nichego_vajnee_semji[11]))
				return 0;
			buff += elem->net_nichego_vajnee_semji[11]->polska;
			operators->polska += buff;
		}
		else {
			std::string znak = "=";
			if (table.find(infa).atribute != "int") {
				std::cout << "\nѕеременна€ не была объ€влена, дурила!\n";
				return 0;
			}
			if (!Expr(elem->net_nichego_vajnee_semji[2], "int"))
				return 0;
			operators->polska += elem->net_nichego_vajnee_semji[2]->polska
				 + infa.lexem + " " + znak + "\n";
			
		}
	}
	return 1;
}

bool semantic_analysator::Expr(std::shared_ptr<node_tree> n_t, std::string s) {
	auto expr = n_t;
	//иду по симпл экспрам
	for (int i = 0; i < n_t->get_childs().size(); i+=2) {
		std::string znak = "";
		if (!S1mpleExpr(n_t->net_nichego_vajnee_semji[i], s))
			return 0;
		expr->polska = n_t->net_nichego_vajnee_semji[i]->polska + " " + expr->polska;
		if (i + 1 < n_t->get_childs().size()) {
			znak = get_lexeme(n_t->net_nichego_vajnee_semji[i + 1]->field);
			expr->polska += znak + " ";
		}
	}
	return 1;
}

bool semantic_analysator::Condition(std::shared_ptr<node_tree> n_t, std::string s){
	auto condition = n_t;
	if (!Expr(n_t->net_nichego_vajnee_semji[0], s))
		return 0;
	condition->polska += n_t->net_nichego_vajnee_semji[0]->polska;
	std::string znak = "";
	znak = get_lexeme(n_t->net_nichego_vajnee_semji[1]->field);
	if (!Expr(n_t->net_nichego_vajnee_semji[2], s))
		return 0;
	condition->polska += n_t->net_nichego_vajnee_semji[2]->polska;
	condition->polska += znak;
	return 1;
}

bool semantic_analysator::S1mpleExpr(std::shared_ptr<node_tree> n_t, std::string s) {
	auto simplexpr = n_t;
	info infa(n_t->net_nichego_vajnee_semji[0]->field);
	if (infa.type == "NUMBER") {
		simplexpr->polska += infa.lexem;
		return 1;
	}
	else if (infa.type == "IDENTIF") {
		if (table.find(infa).atribute != "int") {
			std::cout << "\nѕеременна€ не была объ€влена, дурила!\n";
			return 0;
		}
		simplexpr->polska += infa.lexem;
		return 1;
	}
	else
		if (!Expr(n_t->net_nichego_vajnee_semji[1], s))
			return 0;
	simplexpr->polska += n_t->net_nichego_vajnee_semji[1]->polska;
	return 1;
}

bool semantic_analysator::End() {
	auto end = tree.root->net_nichego_vajnee_semji[3];
	//развернули токен (тупо очень тупо....)
	info temp(end->net_nichego_vajnee_semji[1]->field); //лежит переменна€ ретурна
	auto begin = tree.root->net_nichego_vajnee_semji[0];
	info temp1(begin->net_nichego_vajnee_semji[1]->field); //лежит функци€ из бегина
	if (table.find(temp).atribute != table.find(temp1).atribute) {
		std::cout << "\n“ип функции не соответствует типу возвращаемого аргумента!\n";
		return 0;
	}
	end->polska += temp.lexem + " RETURN\n";
	return 1;
}

/*
int main(){
int a,b;
int d, i, j;
a = (a + (5 + 10) + 32 + 98);
b = b - 2 + a;
for (i = 0; i <= 100; i + 1){
	for (j = i; j <= 20; j + 2){
	d = a + b;
	}
	a = a - 1;
}
return d;
}
*/