# oi-workspace

写题工作区

## 使用方法

下载本仓库（clone 或 Download ZIP），使用 VSCode 打开文件夹（文件/打开文件夹...或 `Ctrl+K Ctrl+O`）打开即可使用

直接编译运行：`Ctrl+Shift+B` 编译后后在终端中使用命令行运行

调试运行：`F5`

若出现“检测到 include 错误，请更新 includePath”的错误信息，请按 `Ctrl+Shift+P` 搜索 `C/C++:编辑配置(JSON)`，在打开的 json 文件中输入以下内容：

```json
{
    "configurations": [
        {
            "name": "Win32",
            "compilerPath": "你的 g++ 路径"
        }
    ],
    "version": 4
}
```
