import random
import re
import sys
import sympy

# sys.setrecursionlimit(00)
max_int_length = 5
max_expr_length = 200
max_index_length = 1
max_factors = 3
max_terms = 3

max_factor_length = 50
max_expr_length = 200
max_term_length = 100

isFactor = False



def getRandomBool():
    return random.choice([True, False])


def getRandomSingleDigit():
    return str(random.choice("0123456789"))


# 加减
def generateAddOrSub():
    if getRandomBool():
        return "+"
    else:
        return "-"


# 空白字符
def generateBlankChar():
    if getRandomBool():
        return " "
    else:
        return "\t"


# 空白项
# def  generateBlankItem():
#     res = ""
#     for _ in range(random.randint(0, 10)):
#         res += generateBlankChar()
#     return res


# 允许带前导零的整数
def generateInt_withLeadingZeros(max_Int_length):
    res = ""
    if getRandomBool():
        res += "00"
    for _ in range(random.randint(1, max_Int_length)):
        res += getRandomSingleDigit()
    return res


# 带符号的整数
def generateSignedInteger():
    res = ""
    if getRandomBool():
        res += generateAddOrSub()
    res += generateInt_withLeadingZeros(max_int_length)
    return res


# 指数
def generateIndex():
    res = "^"
    # res += generateBlankItem()
    if getRandomBool():
        res += "+"
    res += str(random.randint(0, 5))
    return res


# 幂函数
def generatePowerFunction():
    res = "x"
    if getRandomBool():
        # res += generateBlankItem()
        res += generateIndex()
    return res


# 变量因子
def generateVariableFactor():
    return generatePowerFunction()


# 常数因子
def generateNumberFactor():
    return generateSignedInteger()


# 表达式因子
def generateExprFactor():
    res = "("
    res += generateExpr()
    res += ")"
    if getRandomBool():
        # res += generateBlankItem()
        res += generateIndex()
    return res


# 因子
def generateFactor():
    randNum = random.randint(0, 2)
    if randNum == 0:
        return generateExprFactor()
    elif randNum == 1:
        return generateVariableFactor()
    else:
        return generateExprFactor()


# 项
def generateTerm():
    global isFactor
    if isFactor:
        res = ""
        if getRandomBool():
            res += generateNumberFactor()
        else:
            res += generateVariableFactor()
        randNum = random.randint(0, max_factors)
        for _ in range(randNum - 1):
            res += "*"
            if getRandomBool():
                res += generateNumberFactor()
            else:
                res += generateVariableFactor()
            if len(res) > max_factor_length:
                return res
        return res
    isFactor = True
    res = ""
    res += generateFactor()
    randNum = random.randint(0, max_factors)
    for _ in range(randNum - 1):
        res += "*"
        res += generateFactor()
        if len(res) > max_term_length:
            return res
    isFactor = False
    return res


# 表达式
def generateExpr():
    global isFactor
    res = ""

    res += generateTerm()
    randNum = random.randint(0, max_terms)
    for _ in range(randNum - 1):
        res += generateAddOrSub()
        res += generateTerm()
        if len(res) > max_expr_length:
            return res
    return res


def remove_nested_parentheses(s):
    # 正则表达式匹配嵌套的小括号及其内容，但不匹配只有一层的小括号
    pattern = r'\((?!\()[^()]*\)'

    # 使用正则表达式替换函数，将匹配到的嵌套括号及其内容替换为空字符串
    s = re.sub(pattern, '', s)

    return s


# for _ in range(10):
#     print(generateExpr().replace(" ", "").replace("\t", ""))
#     print(generateFactor())

def genData():
    expr = generateExpr().replace("^", "**")
    x = sympy.Symbol('x')
    toEval = re.sub(r'\b0+(\d+)\b', r'\1', expr)
    simplified = sympy.expand(eval(toEval))
    return str(expr), str(simplified)
