import os
import shutil
import subprocess
import random
import threading
from tqdm import tqdm


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


def get_time():
    de = random.randint(0, 5)
    return de * 0.1


# 四波数据：第二波在电梯上行时加入的向上的请求；第三波为在电梯下行时加入的向下的请求；第一、四波在电梯等待时加入的随机请求
def make_data():
    str_result = ""
    person_id = 0
    time = 1
    case = random.randint(1, 5)
    elevator_selected = str(random.randint(1, 6))

    if case == 1:
        for i in range(15):
            person_id += 1
            time = round(time + get_time(), 1)
            from_floor = random.randint(1, 11)
            to_floor = random.randint(1, 11)
            while to_floor == from_floor:
                to_floor = random.randint(1, 11)
            str_result = str_result + "[" + str(time) + "]" + str(person_id) + "-FROM-" + str(
                from_floor) + "-TO-" + str(
                to_floor) + "-BY-" + elevator_selected + "\n"

    if case == 2:
        for i in range(random.randint(3, 5)):
            person_id += 1
            time = round(time + get_time(), 1)
            from_floor = random.randint(1, 11)
            to_floor = random.randint(1, 11)
            while to_floor == from_floor:
                to_floor = random.randint(1, 11)
            str_result = str_result + "[" + str(time) + "]" + str(person_id) + "-FROM-" + str(
                from_floor) + "-TO-" + str(
                to_floor) + "-BY-" + elevator_selected + "\n"

        time += 2  # second wave of request
        for i in range(random.randint(3, 5)):
            person_id += 1
            time = round(time + get_time(), 1)
            from_floor = random.randint(1, 10)
            to_floor = random.randint((from_floor + 1), 11)
            str_result = str_result + "[" + str(time) + "]" + str(person_id) + "-FROM-" + str(
                from_floor) + "-TO-" + str(
                to_floor) + "-BY-" + elevator_selected + "\n"

        time += 2  # third wave of request
        for i in range(random.randint(3, 5)):
            person_id += 1
            time = round(time + get_time(), 1)
            from_floor = random.randint(2, 11)
            to_floor = random.randint(1, (from_floor - 1))
            str_result = str_result + "[" + str(time) + "]" + str(person_id) + "-FROM-" + str(
                from_floor) + "-TO-" + str(
                to_floor) + "-BY-" + elevator_selected + "\n"

        time += 20  # forth wave of request
        for i in range(random.randint(3, 5)):
            person_id += 1
            time = round(time + get_time(), 1)
            from_floor = random.randint(1, 11)
            to_floor = random.randint(1, 11)
            while to_floor == from_floor:
                to_floor = random.randint(1, 11)
            str_result = str_result + "[" + str(time) + "]" + str(person_id) + "-FROM-" + str(
                from_floor) + "-TO-" + str(
                to_floor) + "-BY-" + elevator_selected + "\n"

    if case == 3:
        for i in range(20):
            person_id += 1
            time = round(time + get_time(), 1)
            from_floor = random.randint(1, 11)
            to_floor = random.randint(1, 11)
            while to_floor == from_floor:
                to_floor = random.randint(1, 11)
            str_result = str_result + "[" + str(time) + "]" + str(person_id) + "-FROM-" + str(
                from_floor) + "-TO-" + str(
                to_floor) + "-BY-" + str(random.randint(1, 6)) + "\n"

    if case == 4:
        for i in range(15):
            person_id += 1
            time = round(time + get_time(), 1)
            from_floor = 5
            to_floor = random.randint(1, 11)
            while to_floor == from_floor:
                to_floor = random.randint(1, 11)
            str_result = str_result + "[" + str(time) + "]" + str(person_id) + "-FROM-" + str(
                from_floor) + "-TO-" + str(
                to_floor) + "-BY-" + elevator_selected + "\n"

    if case == 5:
        for i in range(15):
            person_id += 1
            time = round(time + get_time(), 1)
            from_floor = random.randint(1, 11)
            to_floor = 5
            while to_floor == from_floor:
                from_floor = random.randint(1, 11)
            str_result = str_result + "[" + str(time) + "]" + str(person_id) + "-FROM-" + str(
                from_floor) + "-TO-" + str(
                to_floor) + "-BY-" + elevator_selected + "\n"

    return str_result


def are_files_equal(file1, file2):  
    with open(file1, 'r') as f1, open(file2, 'r') as f2:  
        return f1.read() == f2.read()


# 运行java程序，支持输入输出重定向，并返回运行是否成功的结果
def runJar(jar_path, input_file_path, output_file_path):  
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



def run_cpp_judge(orgin_input_path, origin_output_path, standard_input_path, reversed_input_path, error_path):
    # 获取当前脚本的目录  
    current_directory = '.\\' 
    
    # 构建judge.exe的完整路径  
    exe_path = os.path.join(current_directory, 'judge.exe')  
    
    # 定义要传递给judge.exe的参数  
    arguments = [orgin_input_path, origin_output_path, standard_input_path, reversed_input_path, error_path]  
    
    # 使用subprocess运行exe文件并传递参数   
    try:  
        # 使用check=True来确保命令执行成功，否则抛出CalledProcessError异常  
        res = subprocess.run([exe_path] + arguments, check=True)  
        # print("judge.exe执行成功。")  
    except subprocess.CalledProcessError as e:  
        print(f"judge.exe执行失败，返回值：{e.returncode}")
    return res.returncode  # 返回退出码，正常为0


def execute_one_judge(i):   
    current_directory_path = '.\\'
    origin_input_path = os.path.join(current_directory_path, 'machine_' + str(i), 'origin_input.txt')
    origin_output_path = os.path.join(current_directory_path, 'machine_' + str(i), 'origin_output.txt')
    standard_input_path = os.path.join(current_directory_path, 'machine_' + str(i), 'standard_input.txt')
    reversed_input_path = os.path.join(current_directory_path, 'machine_' + str(i), 'reversed_input.txt')
    error_path = os.path.join(current_directory_path, 'machine_' + str(i), 'error.txt')
    jar_path = os.path.join(current_directory_path, 'code.jar')
    
    # 生成数据，并保存
    input_data = make_data()
    with open(origin_input_path, 'w') as f:
        f.write(input_data)
    
    # 运行jar包
    jar_res = runJar(jar_path, origin_input_path, origin_output_path)
    if jar_res == False:
        return False

    # 运行cpp逆向生成器
    cpp_res = run_cpp_judge(origin_input_path, origin_output_path, standard_input_path, reversed_input_path, error_path)
    if cpp_res != 0:
        return False
    
    # 进行结果比对
    if not are_files_equal(standard_input_path, reversed_input_path):
        print('Your reversed_input does not match the standard_input')
        with open(error_path, 'w') as file:  
            file.write('Your reversed_input does not match the standard_input')
        return False

    return True


def start_one_machine(i, time, pbar):
    # pbar = tqdm(total = time, desc = 'machine' + str(i))
    for tmp in range(time):
        res = execute_one_judge(i)
        if res == False: 
            return False
        # print(tmp, ' has finished')
        pbar.update(1)
    # pbar.close()
    return True
    # for tmp in tqdm(range(time)):
    #     res = execute_one_judge(i)
    #     if res == False: 
    #         return False
    #     # print(tmp, ' has finished')
    # return True


def start_machine(thread_num, time_for_each_thread, pbar):
    genDir(thread_num)
    stop_event = threading.Event()

    def run_start_one_machine(stop_event, i, time):
        if not start_one_machine(i, time, pbar):
            stop_event.set()
            print('Error in ', i)
    
    threads = []
    for i in range(thread_num):
        thread = threading.Thread(target=run_start_one_machine, args=(stop_event, i, time_for_each_thread))
        threads.append(thread)
        thread.start()

    for thread in threads:
        thread.join()
        if stop_event.is_set():
            break
    
    if stop_event.is_set():
        print("WA")
    else:
        print("AC")
    

def main():
    thread_num = input('要启动的线程数')
    thread_num = int(thread_num)
    time = input('每个线程的评测次数')
    time = int(time)
    pbar = tqdm(range(thread_num * time))
    start_machine(thread_num, time, pbar)
    input('按任意键以退出')

main()