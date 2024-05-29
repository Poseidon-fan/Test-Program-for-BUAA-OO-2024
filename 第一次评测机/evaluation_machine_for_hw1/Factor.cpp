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
    // TODO: 在此处插入 return 语句
}



void NumberFactor::generate()
{
    std::string res = "";

    // 使用当前时间作为随机数生成器的种子，这样可以增加随机性  
    srand(time(nullptr));
    // 生成一个0到2之间的随机整数  
    int random_number = rand() % 3;
    // 随机带符号
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
