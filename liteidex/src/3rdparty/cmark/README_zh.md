### 一、什么是 cmark？

`cmark` 是 **CommonMark** 规范的 **C 语言参考实现**。



- **CommonMark**：一种标准化、合理化的 Markdown 语法，解决了传统 Markdown 解析器行为不一致的问题（有明确的[语法规范](http://spec.commonmark.org/)）。
- **定位**：提供一个轻量、高效的库和命令行工具，用于解析 CommonMark 文档并渲染为多种格式。
- **对应 JS 实现**：[commonmark.js](https://github.com/commonmark/commonmark.js)（客户端解析常用）。

### 二、核心功能

cmark 主要通过两部分组件提供功能：

1. **共享库 `libcmark`**：提供编程接口，支持：
   - 解析 CommonMark 文档为**抽象语法树（AST）**；
   - 操作 / 修改 AST；
   - 将 AST 渲染为多种输出格式：HTML、groff man（手册页）、LaTeX、CommonMark（反向渲染）、AST 的 XML 表示。
2. **命令行工具 `cmark`**：直接通过终端解析和渲染 CommonMark 文件，无需编程。

### 三、核心优势

文档强调了 cmark 相比其他 Markdown 解析器的核心竞争力：



| 优势           | 说明                                                         |
| -------------- | ------------------------------------------------------------ |
| **可移植性**   | 标准 C99 编写，无外部依赖，支持 MSVC、gcc、clang、tcc 等编译器。 |
| **极致性能**   | 渲染《战争与和平》的 Markdown 版本仅需 127ms（十年前笔记本），比原版 `Markdown.pl` 快 10000 倍。 |
| **规范兼容**   | 完全通过 CommonMark 一致性测试，解析行为与所有兼容解析器一致（如客户端用 commonmark.js，服务端用 cmark 无差异）。 |
| **鲁棒性**     | 经 [american fuzzy lop](http://lcamtuf.coredump.cx/afl/) 模糊测试，能处理极端案例（如千级嵌套括号 / 块引用）。 |
| **灵活性**     | 支持通过 AST 编程修改文档内容后再渲染。                      |
| **多格式输出** | 内置 HTML、LaTeX 等渲染器，扩展新格式也很简单。              |
| **开源免费**   | BSD2 许可证，可自由使用和修改。                              |

### 四、安装方法

安装依赖：`cmake`（构建工具）；若修改 `scanners.re`，还需 `re2c >= 0.14.2`（生成词法分析器）。

#### 1. 通用方法（GNU Make）

最简便的方式，适用于 Linux/macOS：

```bash
# 1. 克隆仓库（若未获取源码）
git clone https://github.com/commonmark/cmark.git
cd cmark

# 2. 编译（生成 build 目录，内含 Makefile）
make

# 3. 运行测试（验证编译正确性）
make test

# 4. 安装（默认前缀 /usr/local）
# 若需自定义安装路径：make INSTALL_PREFIX=/your/path install
make install
```



编译后的二进制文件（`cmark` 工具和 `libcmark` 库）在 `build/src` 目录下。

#### 2. 手动 cmake 构建（更灵活，支持多平台）

适用于 FreeBSD、自定义构建系统等场景：

```bash
# 1. 创建构建目录并进入
mkdir build && cd build

# 2. 生成构建文件（可选指定安装前缀）
cmake ..  # 或 cmake -DCMAKE_INSTALL_PREFIX=/your/path ..

# 3. 编译
make

# 4. 测试 + 安装
make test
make install
```

#### 3. macOS 生成 Xcode 项目

```bash
mkdir build && cd build
cmake -G Xcode ..
open cmark.xcodeproj  # 用 Xcode 打开并编译
```

#### 4. Windows 安装

- **MSVC + NMAKE**：直接运行 `nmake`；
- **Linux 交叉编译 Windows 版本**：`make mingw`，生成的二进制在 `build-mingw/windows/bin`。

### 五、开发者常用目标（GNU Make）

除了基础的编译安装，`Makefile` 还提供了开发者常用的工具目标：



| 命令             | 功能                                                        |
| ---------------- | ----------------------------------------------------------- |
| `make bench`     | 运行基准测试（性能测试）。                                  |
| `make newbench`  | 运行更详细的基准测试。                                      |
| `make leakcheck` | 用 valgrind 检测内存泄漏。                                  |
| `make format`    | 用 clang-format 格式化源码。                                |
| `make fuzztest`  | 用随机生成的长输入进行模糊测试。                            |
| `make afl`       | 用 american fuzzy lop 进行系统模糊测试（需指定 AFL 路径）。 |
| `make libFuzzer` | 用 libFuzzer 进行模糊测试（需自定义 LLVM 路径）。           |
| `make archive`   | 生成发布用的 tarball 和 zip 压缩包。                        |

### 六、使用说明

#### 1. 命令行工具 `cmark`

具体用法可查看手册页：`man cmark`，核心参数示例：

```bash
# 将 input.md 渲染为 HTML 并输出到 stdout
cmark input.md

# 渲染为 LaTeX 并保存到 output.tex
cmark -t latex input.md -o output.tex

# 允许原始 HTML 和危险链接（默认禁用，需谨慎使用）
cmark --unsafe input.md
```

#### 2. 库 `libcmark` 编程

`libcmark` 提供完整的 C 语言 API，可用于解析、操作 AST 和渲染。手册页 `man libcmark` 提供详细接口说明。
此外，已有多种语言的封装库，可直接在非 C 项目中使用：

- Go：[go-commonmark](https://github.com/rhinoman/go-commonmark)
- Python：[paka.cmark](https://pypi.python.org/pypi/paka.cmark)
- Ruby：[commonmarker](https://github.com/gjtorikian/commonmarker)
- Haskell、Lua、Perl、R、Scala 等（见文档 “wrappers/ 子目录” 和链接）。

### 七、安全说明

- **默认行为**：`libcmark` 会过滤原始 HTML 和危险链接（`javascript:`、`vbscript:`、`data:`、`file:` 等），防止 XSS 攻击。
- **允许危险内容**：若需保留原始 HTML，可使用选项 `CMARK_OPT_UNSAFE`（库）或 `--unsafe`（命令行），但**强烈建议**搭配专用 HTML sanitizer 进一步防护。

### 八、贡献与社区

- **讨论论坛**：[CommonMark 论坛](http://talk.commonmark.org/)（用于问题咨询和开放讨论）；
- **Issue 跟踪**：[GitHub Issues](http://github.com/commonmark/CommonMark/issues)（仅用于明确、可行动的问题）。

### 九、核心作者

- John MacFarlane：原始库和工具的作者；
- David Greenspan：合作设计块解析算法；
- Vicent Marti：性能优化（提速 10 倍）；
- Kārlis Gaņģis：改进链接 / 强调解析算法；
- Nick Wellnhofer：贡献 API 和测试框架。