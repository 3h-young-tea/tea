# tea

**tea_editor_ante** - 一个为真正程序员准备的轻量级终端文本编辑器

## 项目简介

一个用 c++ 编写的极简终端文本编辑器,  
支持 vim 风格的光标移动 (`hjkl`).  
追求简洁、速度, 以及贴近底层的编辑体验.  

本项目的学习和灵感主要来源于 [kilo](https://github.com/antirez/kilo),  
这是一个由 antirez 编写的极简终端文本编辑器, 非常经典.  

>	*real coder won't die*

## 功能

- 终端原始模式输入
- vim 风格的光标移动 (`hjkl`)
- 简单的命令模式 (`esc` `:wq`,  `:q!`)
- 屏幕清爽重绘
- 无外部依赖

## 安装与编译

```bash
g++ -o tea tea.cpp -std=c++14 -O2 -static -w
./tea
```

## 使用方法

`h` `j` `k` `l` - 移动光标

`esc :wq` - 退出 (类似 vim, 目前不支持保存)

`esc :q!` - 强制退出不保存

目前尚未加入文本编辑功能, 敬请期待.

## 参与贡献

等我读完 *计算机程序设计艺术*,   
或许我会重写一遍.  

## 协议

[gplv3](https://www.gnu.org/licenses/gpl-3.0.html)
