# tea

**tea_editor_ante** - a lightweight terminal text editor for real coders.

>  华夏同袍点这里 -> [readme_zh](https://github.com/3h-young-tea/tea/blob/main/README.zh.md)

## project description

a minimal terminal-based text editor written in c++,  
with vim-style navigation (`hjkl`).  
designed for simplicity, speed, and staying close to the metal.  

this project is primarily inspired by [kilo](https://github.com/antirez/kilo),  
a classic minimal terminal text editor created by antirez.  

>	*real coder won't die*

## features

- terminal raw mode
- vim-style movement (`hjkl`)
- simple command mode (`esc` `:wq`, `:q!`)
- clean screen redraw
- no external dependencies

## installation / build

```bash
g++ -o tea tea.cpp -std=c++14 -O2 -static -w
./tea
```

## usage

`h` `j` `k` `l` - move the cursor

`esc :wq` - exit (like vim, but no saving yet)

`esc :q!` - force quit without saving

editing functionality will be added later.

## contributing

wait for me to finish reading *the art of computer programming*.  
then I might rewrite everything.  

## license

[gplv3](https://www.gnu.org/licenses/gpl-3.0.html)
