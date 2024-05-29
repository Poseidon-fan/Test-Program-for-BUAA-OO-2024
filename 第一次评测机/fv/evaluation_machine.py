import random
import re
import sys
import sympy
import json
import subprocess
from tqdm import tqdm

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

def execute_java(fname, stdin):
    cmd = ['java', '-jar', fname]
    proc = subprocess.Popen(cmd, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    stdout, stderr = proc.communicate(stdin.encode())
    return stdout.decode().strip()






def main(fname, times=100):
    exprDict = dict()
    for _ in tqdm(range(times)):
        poly, ans = genData()
        ans = ans.replace("**", "^").replace(" ", "").replace("\t", "")
        # print(poly)
        forSympy = re.sub(r'\b0+(\d+)\b', r'\1', poly)
        f = sympy.parse_expr(forSympy)
        strr = execute_java(fname, poly.replace("**", "^"))
        # print(strr)
        try:
            g = sympy.parse_expr(strr.replace("^", "**"))
            if sympy.simplify(f).equals(g):
                # print("AC : " + str(cnt))
                exprDict[poly] = (len(strr.encode('utf-8')) / len(ans.encode('utf-8')), ans)
                # if len(strr.encode('utf-8')) / len(ans.encode('utf-8')) > 1:
                #     print(strr)
                #     print(ans)
                # print("x: {:.6f}".format(len(strr) / len(ans)))
                pass
            else:
                print("!!WA!! with " + "poly : " + poly.replace("**", "^"))
                print("yours: " + strr)
                print("sympy: ", end="")
                print(ans)
                return
        except Exception as e:
            print(e)
            print("!!WA!! with " + "poly : " + poly.replace("**", "^"))
            print("yours: " + strr)
            print("sympy: ", end="")
            print(ans)
            return
            pass
    sorted_exprDict = sorted(exprDict.items(), key=lambda x: x[1][0], reverse=True)
    print("worst score (x): " + str(sorted_exprDict[0][1][0]))
    print("best score (x): " + str(sorted_exprDict[-1][1][0]))
    output = list()
    for i in range(10):
        tmpdict = dict()
        tmpdict['generated_expression'] = sorted_exprDict[i][0].replace("**", "^")
        tmpdict['sympy_simplified'] = sorted_exprDict[i][1][1]
        tmpdict['score'] = sorted_exprDict[i][1][0]
        output.append(tmpdict)

        # print(sorted_exprDict[i][0].replace("**", "^"))
        # print(sorted_exprDict[i][1][1])
        # print(sorted_exprDict[i][1][0])
    with open('output.json', 'w') as f:
        json.dump(output, f)


fname = input("输入jar文件路径")
time = input("要测评次数：")
main(fname, int(time))
input("输入任何内容以退出")
