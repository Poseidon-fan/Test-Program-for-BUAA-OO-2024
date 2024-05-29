#include "Factor.h"
#include "Term.h"




std::string Factor::getContent()
{
    return content;
}

std::string Factor::getFactor()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 3);
    int random_number = dis(gen) % 3;
    
    if (random_number == 1) {
        NumberFactor *n = new NumberFactor();
        n->generate();
        return n->getContent();
    }
    else if (random_number == 2) {
        VariableFactor* v = new VariableFactor();
        v->generate();
        return v->getContent();
    }
    else {
        ExprFactor *e = new ExprFactor();
        e->generate();
        return e->getContent();
    }
    return "";
    // TODO: �ڴ˴����� return ���
}



void NumberFactor::generate()
{
    std::string res = "";

    // ʹ�õ�ǰʱ����Ϊ����������������ӣ������������������  
    srand(time(nullptr));
    // ����һ��0��2֮����������  
    int random_number = rand() % 3;
    // ���������
    if (random_number == 0) res += "+";
    else if (random_number == 1) res += "-";

    res += std::to_string(getRandomLong());
    content = res;
}

void VariableFactor::generate()
{
    std::string res = "x";

    if (getRandomBool()) {
        content = res;
        return;
    }
    else {       
        res += "^";
        res += std::to_string(abs(getRandomLong()));
    }    
    content = res;
}

void ExprFactor::generate()
{
    std::string res = "(";
    Term* t = new Term();
    t->generate();
    res += t->toString();
    res += ")";
    content = res;
}
