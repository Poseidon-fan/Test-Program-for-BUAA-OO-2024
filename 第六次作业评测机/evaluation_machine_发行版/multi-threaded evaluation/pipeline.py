import os
import shutil
import subprocess
from tqdm import tqdm
import threading

import random

GROUP_NUMBER = 70


def get_time(time, max_time):
    de = random.randint(0, max_time)
    return round(time + de * 0.1, 1)


def get_elevator():
    return random.randint(1, 6)


def get_speed():
    return round(0.1 * random.randint(2, 6), 1)


def get_capacity():
    return random.randint(3, 8)


def make_data():
    str_result = ""
    person_id = 0
    time = 1
    case = random.randint(1, 3)

    if case == 1:
        for i in range(GROUP_NUMBER):
            person_id += 1
            time = get_time(time, 3)
            from_floor = random.randint(1, 11)
            to_floor = random.randint(1, 11)
            while to_floor == from_floor:
                to_floor = random.randint(1, 11)
            str_result = (str_result +
                          "[" + str(time) + "]" + str(person_id) +
                          "-FROM-" + str(from_floor) +
                          "-TO-" + str(to_floor) + "\n")
    if case == 2:
        for i in range(GROUP_NUMBER):
            time = get_time(time, 0)
            person_id += 1
            from_floor = random.randint(1, 11)
            to_floor = random.randint(1, 11)
            while to_floor == from_floor:
                to_floor = random.randint(1, 11)
            str_result = (str_result +
                          "[" + str(time) + "]" + str(person_id) +
                          "-FROM-" + str(from_floor) +
                          "-TO-" + str(to_floor) + "\n")

    if case == 3:
        last_reset = dict()
        reset_count = 0
        for i in range(7):
            last_reset[i] = 0.0
        for i in range(GROUP_NUMBER):
            time = get_time(time, 10)
            elevator = get_elevator()
            if reset_count < 20 and random.randint(1, 10) < 4 and (
                    last_reset[elevator] < (time - 5) or last_reset[elevator] == 0.0):
                last_reset[elevator] = time
                elevator_id = str(elevator)
                elevator_capacity = str(get_capacity())
                elevator_speed = str(get_speed())
                str_result = (str_result + "[" + str(time) + "]" + "RESET-Elevator-"
                              + elevator_id + "-" + elevator_capacity + "-" + elevator_speed + "\n")
            else:
                person_id += 1
                from_floor = random.randint(1, 11)
                to_floor = random.randint(1, 11)
                while to_floor == from_floor:
                    to_floor = random.randint(1, 11)
                str_result = (str_result +
                              "[" + str(time) + "]" + str(person_id) +
                              "-FROM-" + str(from_floor) +
                              "-TO-" + str(to_floor) + "\n")

    return str_result


def genDir(num):
    baseName = "machine"
    folderNames = [f"{baseName}_{x}" for x in range(num)]

    for folderName in folderNames:
        folderPath = os.path.join(os.getcwd(), folderName)
        # check if the folder has already been created
        if os.path.exists(folderPath):
            shutil.rmtree(folderPath)
        
        # make directory
        os.makedirs(folderPath, exist_ok=True)

# 运行java程序，支持输入输出重定向，并返回运行是否成功的结果
def run_jar(jar_path, input_file_path, output_file_path):  
    with open(input_file_path, 'rb') as input_file:  
        # 启动Java进程，并将输入和输出重定向  
        process = subprocess.Popen(  
            ['java', '-jar', jar_path],  
            stdin=subprocess.PIPE,  # 将输入通过PIPE传递给进程  
            stdout=subprocess.PIPE,  # 将输出通过PIPE获取  
            stderr=subprocess.PIPE  # 也可以捕获错误输出  
        )  
          
        # 读取输入文件内容并传递给Java进程  
        output, error = process.communicate(input_file.read())  
          
        # 将Java进程的输出写入到文件  
        with open(output_file_path, 'wb') as output_file:  
            output_file.write(output)  
          
        # 检查进程返回码  
        if process.returncode != 0:  
            print(f"Java程序执行出错，返回码：{process.returncode}")  
            print(f"错误信息：{error.decode('utf-8')}")  
            return False
        else:  
            return True 
        

def run_cpp_judge(input_path, output_path, error_path):
    # 获取当前脚本的目录  
    current_directory = '.\\' 
    
    # 构建judge.exe的完整路径  
    exe_path = os.path.join(current_directory, 'judge.exe')

    arguments = [input_path, output_path, error_path]

    # 使用subprocess运行exe文件并传递参数   
    try:  
        # 使用check=True来确保命令执行成功，否则抛出CalledProcessError异常  
        res = subprocess.run([exe_path] + arguments, check=True)   
        return res.returncode  # 返回退出码，正常为0
    except subprocess.CalledProcessError as e:  
        print(f"WA!!!  judge.exe执行失败")
        return 1
    


def execute_one_judge(i, pbar):   
    current_directory_path = '.\\'
    input_path = os.path.join(current_directory_path, 'machine_' + str(i), 'input.txt')
    output_path = os.path.join(current_directory_path, 'machine_' + str(i), 'output.txt')
    error_path = os.path.join(current_directory_path, 'machine_' + str(i), 'error.txt')
    jar_path = os.path.join(current_directory_path, 'code.jar')
    
    # 生成数据，并保存
    input_data = make_data()
    with open(input_path, 'w') as f:
        f.write(input_data)
    
    # 运行jar包
    jar_res = run_jar(jar_path, input_path, output_path)
    if jar_res == False:
        return False

    #运行judge
    cpp_res = run_cpp_judge(input_path, output_path, error_path)
    pbar.update(1)
    if cpp_res != 0:
        return False  

    return True

def start_one_machine(i, time, pbar):
    for tmp in range(time):
        res = execute_one_judge(i, pbar)
        if res == False: 
            return False
    return True


def start_machine(thread_num, time_for_each_thread, pbar):
    genDir(thread_num)
    stop_event = threading.Event()

    def run_start_one_machine(stop_event, i, time, pbar):
        if not start_one_machine(i, time, pbar):
            stop_event.set()
            print('Error in ', i)
    
    threads = []
    for i in range(thread_num):
        thread = threading.Thread(target=run_start_one_machine, args=(stop_event, i, time_for_each_thread, pbar))
        threads.append(thread)
        thread.start()

    for thread in threads:
        thread.join()
        if stop_event.is_set():
            break


def main():
    thread_num = input('要启动的线程数')
    thread_num = int(thread_num)
    time = input('每个线程的评测次数')
    time = int(time)
    pbar = tqdm(range(thread_num * time))
    start_machine(thread_num, time, pbar)

main()
