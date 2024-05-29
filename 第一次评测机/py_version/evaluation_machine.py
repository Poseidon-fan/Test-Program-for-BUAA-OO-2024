import json
import re
import sympy
import subprocess
from tqdm import tqdm

import generate_data
import generate_data as gd


def execute_java(fname, stdin):
    cmd = ['java', '-jar', fname]
    proc = subprocess.Popen(cmd, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    stdout, stderr = proc.communicate(stdin.encode())
    return stdout.decode().strip()






def main(fname, times=100):
    exprDict = dict()
    for _ in tqdm(range(times)):
        poly, ans = gd.genData()
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


if __name__ == '__main__':
    fname = input("输入jar文件路径")
    time = int(input("要测评次数："))
    main(fname, time)
        

