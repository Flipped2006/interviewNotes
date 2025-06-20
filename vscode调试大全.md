# s

## **一、基础调试快捷键（通用）**

| 操作                     | Windows/Linux 快捷键 | Mac 快捷键     | 作用说明                                                                 |
|--------------------------|----------------------|----------------|--------------------------------------------------------------------------|
| 启动/继续调试           | `F5`                 | `⌘+F5`         | 启动调试会话，或从暂停处继续执行              ****                           |
| 暂停调试                 | `Ctrl+Pause`         | `⌘+Pause`      | 暂停正在运行的程序（部分环境支持，如 Node.js）                           |
| 停止调试                 | `Shift+F5`           | `⇧+⌘+F5`       | 终止当前调试会话                                                         |
| 切换断点                 | `F9`                 | `⌘+F9`         | 在当前行添加/删除断点                                                   |
| 单步跳过（Step Over）    | `F10`                | `⌘+F10`        | 执行当前行，不进入函数内部（跳过函数调用）                               |
| 单步进入（Step Into）    | `F11`                | `⌘+F11`        | 执行当前行，进入函数/方法内部（跟踪到嵌套逻辑）                         |
| 单步跳出（Step Out）     | `Shift+F11`          | `⇧+⌘+F11`      | 跳出当前函数/方法，回到调用处                                           |
| 运行到光标处             | `Ctrl+F10`           | `⌘+F10`        | 快速执行到光标所在行（跳过中间断点）                                     |
| 切换调试控制台           | ``Ctrl+` ``（反引号） | ``⌘+` ``       | 打开/关闭调试控制台，可执行临时代码、查看变量                             |

---

### **二、高级调试命令（通过命令面板触发）**

按 `Ctrl+Shift+P`（Windows/Linux）或 `⇧+⌘+P`（Mac）打开**命令面板**，输入以下命令：

#### 1. 断点管理

- **`Debug: Toggle Breakpoint`**  
  功能：同 `F9`，切换当前行断点。  
- **`Debug: Toggle Conditional Breakpoint`**  
  功能：添加**条件断点**（右键断点 → 编辑条件的快捷方式），仅满足条件时暂停。  
- **`Debug: Remove All Breakpoints`**  
  功能：清空所有断点，快速重置调试环境。  

#### 2. 调试会话控制

- **`Debug: Start Debugging`**  
  功能：同 `F5`，启动调试（根据 `launch.json` 配置）。  
- **`Debug: Restart Debugging`**  
  功能：重启调试会话（保留断点，重新执行程序）。  
- **`Debug: Attach to Process`**  
  功能：附加到正在运行的进程（需配置 `attach` 模式，适合调试已启动的服务）。  

#### 3. 变量与控制台

- **`Debug: Evaluate in Console`**  
  功能：在调试控制台执行表达式（如 `var + 1`、调用函数），实时查看结果。  
- **`Debug: Add to Watch`**  
  功能：将选中变量加入**监视窗口**，跟踪其值变化（也可右键变量 → 添加到监视）。  

#### 4. 多线程/多进程调试（复杂场景）

- **`Debug: Switch to Thread`**  
  功能：切换调试线程（多线程程序中，查看不同线程的调用栈）。  
- **`Debug: Freeze Thread`**  
  功能：冻结当前线程（专注调试单个线程，其他线程暂停）。  

---

### **三、调试配置核心（`launch.json` 关键字段）**

调试能力的灵活度，依赖 `.vscode/launch.json` 的配置。以下是常用字段及场景：

#### 1. 基础结构（以 C++ 为例）

```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "C++: 调试当前文件", // 调试任务名称（命令面板显示）
      "type": "cppdbg", // 调试器类型（cppdbg 对应 GDB/LLDB）
      "request": "launch", // 启动方式：launch（主动启动）或 attach（附加进程）
      "program": "${fileDirname}/${fileBasenameNoExtension}.exe", // 要调试的程序路径
      "args": [], // 程序启动参数（如命令行参数）
      "stopAtEntry": false, // 是否在 main 函数入口暂停
      "cwd": "${fileDirname}", // 工作目录（程序运行时的当前路径）
      "preLaunchTask": "C/C++: g++ 生成活动文件", // 调试前执行的任务（如编译代码）
      "miDebuggerPath": "gdb.exe", // 调试器路径（GDB/LLDB 位置）
    }
  ]
}
```

#### 2. 关键字段说明

- **`type`**：调试器类型，如 `cppdbg`（C++）、`python`（Python）、`node`（Node.js）、`chrome`（前端）。  
- **`request`**：  
  - `launch`：主动启动程序调试（常用）。  
  - `attach`：附加到已运行的进程（如调试后台服务）。  
- **`program`**：调试的目标程序路径（需与 `tasks.json` 编译输出一致）。  
- **`preLaunchTask`**：调试前自动执行的任务（如 `tasks.json` 中的编译命令，需与 `label` 匹配）。  

#### 3. 多环境配置示例（C++ 调试 + 发布模式）

```json
{
  "configurations": [
    {
      "name": "C++: 调试模式",
      "type": "cppdbg",
      "request": "launch",
      "program": "${fileDirname}/debug.exe",
      "args": [],
      "preLaunchTask": "编译调试版本", // 对应 tasks.json 中调试编译任务
      "miDebuggerPath": "gdb.exe",
      "stopAtEntry": true
    },
    {
      "name": "C++: 发布模式运行",
      "type": "cppdbg",
      "request": "launch",
      "program": "${fileDirname}/release.exe",
      "args": [],
      "preLaunchTask": "编译发布版本", // 对应 tasks.json 中优化编译任务
      "miDebuggerPath": "gdb.exe",
      "stopAtEntry": false
    }
  ]
}
```

---

### **四、场景化调试技巧（C++/Python/JS 为例）**

#### 1. C++ 调试关键配置（解决你的报错问题）

如果调试报错 `No such file or directory`，重点检查：  

- `tasks.json` 中编译输出路径（`-o` 参数）与 `launch.json` 中 `program` 路径**完全一致**。  
- 确保 `preLaunchTask` 名称与 `tasks.json` 中 `label` 一致（区分大小写）。  

示例 `tasks.json`（编译配置）：

```json
{
  "tasks": [
    {
      "label": "C/C++: g++ 生成活动文件",
      "type": "cppbuild",
      "command": "g++",
      "args": [
        "-g", // 必须加 -g 才能生成调试信息
        "${file}",
        "-o",
        "${fileDirname}/${fileBasenameNoExtension}.exe" // 输出路径
      ],
      "problemMatcher": ["$gcc"],
      "group": "build"
    }
  ]
}
```

#### 2. Python 调试特殊配置（异步/多线程）

- **异步代码调试**：在 `launch.json` 中添加环境变量启用异步调试：  

  ```json
  {
    "name": "Python: 异步调试",
    "type": "python",
    "request": "launch",
    "program": "${file}",
    "env": { "PYTHONASYNCIODEBUG": "1" } // 启用 asyncio 调试
  }
  ```

- **多线程调试**：设置 `justMyCode: false` 以调试库代码：  

  ```json
  {
    "name": "Python: 多线程调试",
    "type": "python",
    "request": "launch",
    "program": "${file}",
    "justMyCode": false // 允许进入标准库/第三方库代码
  }
  ```

#### 3. 前端（JavaScript/TypeScript）调试

- **浏览器调试**（`launch.json` 配置）：  

  ```json
  {
    "name": "Launch Chrome",
    "type": "chrome",
    "request": "launch",
    "url": "http://localhost:5500", // 本地运行的网页地址
    "webRoot": "${workspaceFolder}", // 代码根目录
    "sourceMaps": true // 启用 Source Map 关联源码
  }
  ```

- **Node.js 调试**：  

  ```json
  {
    "name": "Node.js: 启动程序",
    "type": "node",
    "request": "launch",
    "program": "${workspaceFolder}/index.js",
    "runtimeArgs": ["--inspect"] // 启用调试协议
  }
  ```

---

### **五、避坑指南（常见调试失败原因）**

1. **调试器与编译器不匹配**：  
   - C++ 中，`launch.json` 的 `miDebuggerPath` 需指向实际的 GDB/LLDB 路径（如 `C:\MinGW\bin\gdb.exe`）。  
2. **路径包含中文/空格**：  
   - 程序路径、工作目录（`cwd`）尽量用纯英文，避免调试器解析失败。  
3. **未生成调试信息**：  
   - C++ 编译时需加 `-g` 参数（`tasks.json` 中 `args` 必须包含 `-g`），否则无法断点调试。  
4. **`preLaunchTask` 未执行**：  
   - 检查 `tasks.json` 中任务是否正确，或手动执行 `Ctrl+Shift+B` 编译，确认可生成可执行文件。  

掌握这些命令和配置，无论是简单的代码调试，还是复杂的多线程、跨语言场景，都能高效定位问题。如果仍有报错，把具体的 `.vscode` 配置（`launch.json`/`tasks.json`）和错误信息补充，可进一步分析！
