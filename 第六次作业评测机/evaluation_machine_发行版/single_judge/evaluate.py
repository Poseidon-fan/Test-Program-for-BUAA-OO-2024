import subprocess  
import threading  
import time  
import argparse 

  
# 定义一个函数来检查进程是否超时并终止它  
def check_and_terminate(proc, timeout):  
    
    try:  
        proc.wait(timeout)  # 等待进程结束或直到超时  
    except subprocess.TimeoutExpired:  
        print("JAR执行超时，正在强制终止...")  
        proc.terminate()  # 尝试礼貌地终止进程  
        # 如果terminate()没有成功，可以等待一段时间后再尝试kill  
        time.sleep(1)  
        if proc.poll() is None:  # 如果进程还在运行  
            proc.kill()  # 强制杀死进程  
        print("JAR执行已强制终止。")  
    else:  
        print("JAR执行完成。")  
  
# 运行JAR文件并设置时间上限  
def run_jar_with_timeout(jar_path, input_file, output_file, error_file, timeout):  
    with open(input_file, 'rb') as infile, open(output_file, 'wb') as outfile, open(error_file, 'wb') as errfile:  
        proc = subprocess.Popen(["java", "-jar", jar_path], stdin=infile, stdout=outfile, stderr=errfile) 
    # 使用单独的线程来检查超时  
    t = threading.Thread(target=check_and_terminate, args=(proc, timeout))  
    t.start()  
    # 主线程可以继续执行其他任务，或者等待线程t结束  
    t.join()  
    return proc.returncode
  
def check(input, output, error):
    cmd = ['./judge.exe', input, output, error]

    try:  
        # 使用check=True以便在exe文件返回非零退出码时抛出异常  
        completed_process = subprocess.run(cmd, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)  
          
        print("AC!") 
        return completed_process.returncode  
    except subprocess.CalledProcessError as e:  
        # 如果exe文件返回非零退出码，则捕获异常并打印错误信息  
        print(f"WA!")  
        return e.returncode  



def main():
    parser = argparse.ArgumentParser()  
  
    # 添加命令行参数  
    parser.add_argument('--jar', type=str)
    parser.add_argument('--input', type=str)  
    parser.add_argument('--output', type=str)
    parser.add_argument('--error', type=str)  
    parser.add_argument('--timeout', type=int)
  
    # 解析命令行参数  
    args = parser.parse_args()

    # 执行带有时间上限的JAR文件运行  
    return_code = run_jar_with_timeout(args.jar, args.input, args.output, args.error, args.timeout)

    if return_code != 0:
        print("运行时错误")
    else:
        check(args.input, args.output, args.error)

main()