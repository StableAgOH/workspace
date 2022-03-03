# oi-workspace

写题工作区

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
