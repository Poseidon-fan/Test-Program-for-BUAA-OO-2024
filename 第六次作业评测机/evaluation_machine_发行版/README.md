# evaluation_machine发行版使用说明

## checker

该文件夹下存有正确性检验工具`judge.exe`，用于检验输出是否符合输入。

使用方法：在该文件夹下终端里运行`judge.exe [input_path] [output_path] [error_path]`即可，其中三个参数替换为相应的文件路径

## single_judge

该文件夹下的工具支持运行自定义数据的评测，并**支持TLE检测**。

使用方法：在该文件夹下终端里运行`python evaluate.py --jar [jar_path] --input [input_path] --output [output_path] --error [error_path] --timeout [time]`

其中前4个参数均为文件路径，最后一个参数指定了最大运行时间

## multi-threaded evaluation

多线程自动化评测机，支持数据自动生成，并自定义线程数与评测次数

使用前置条件：本地安装了`tqdm`库

使用方法：保证自己的jar包命名为`code.jar`，并放在该文件夹下。在该文件夹下终端里运行`python pipeline.py`

**注：本工具链要求的jar包均用TestMain打包**