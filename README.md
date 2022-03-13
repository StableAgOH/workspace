# oi-workspace

写题工作区

## 使用方法

1. 下载本仓库（clone 或 Download ZIP），使用 VSCode 打开文件夹（文件/打开文件夹...或 `Ctrl+K Ctrl+O`）打开
2. 配置 C/C++ 插件，请按 `Ctrl+Shift+P` 搜索 `C/C++:编辑配置(JSON)`，在打开的 json 文件中输入以下内容：

```json
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**"
            ],
            "defines": [
                "LOCAL"
            ],
            "compilerPath": "D:/TDM-GCC-64/bin/g++.exe",  // 请根据实际情况更改
            "cppStandard": "c++17",  // 请按需更改
            "intelliSenseMode": "windows-gcc-x64"
        }
    ],
    "version": 4
}
```

直接编译运行：`Ctrl+Shift+B` 编译后在终端中使用命令行运行

调试运行：`F5`
