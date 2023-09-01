# oi-workspace

写题工作区

## 准备工作

1. 下载本仓库（clone 或 Download ZIP），使用 VSCode 打开文件夹（文件/打开文件夹...或 `Ctrl+K Ctrl+O`）打开；
2. 安装插件 `C/C++`；
3. 按 `Ctrl+Shift+P`，搜索并回车选择 `C/C++: Edit Configurations (UI)`；
4. 修改需要修改的内容：
   * 定义：在在其中添加 `LOCAL` 项；
   * 编译器路径：下拉选择或填入你想使用的编译器的**绝对路径**；
   * C++ 标准：填入你想使用的 `C++` 标准；
   * IntelliSense 模式：根据你的操作系统、你想使用的编译器以及架构选择。

## 运行程序

* 直接编译运行：`Ctrl+Shift+B` 编译后在终端中使用命令行运行，或者自己配置安装 `Code Runner` 等插件；
* 调试运行：`F5`。

## 代码模板使用方法

新建一个 `cpp` 文件，在里面打 `pre`，第一个就是，回车即可。

![template](https://github.com/StableAgOH/workspace/assets/50107074/c6567ade-28b3-4255-88f0-bb7ab839074d)

* 目前使用的代码模板需要 C++17 及以上；
* 若需要修改代码模板调用语句或内容，请修改 `.vscode/template.code-snippets` 文件；
* 注意带板子打带录屏的线上赛可能会被认定为携带代码进入考场算作作弊，请不要于这样的比赛中使用。

## 对拍脚本使用方法

1. 创建并撰写数据生成器文件 `gen.py`；
2. 运行对拍脚本：`python diff.py ${code1} ${code2}`

   `${code1}` 和 `${code2}` 为要对拍的两份代码文件。
