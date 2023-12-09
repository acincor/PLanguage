#PLanguage

![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/Mhc-Inc/PLanguage)

![GitHub License](https://img.shields.io/github/license/Mhc-Inc/PLanguage)

![GitHub release (latest by date including pre-releases)](https://img.shields.io/github/v/release/Mhc-Inc/PLanguage?include_prereleases)

![GitHub tag (latest by date)](https://img.shields.io/github/v/tag/Mhc-Inc/PLanguage.svg)

Installation
---------------

You can download the zip or clone this repository.

Stories
---------------

# What is PLanguage?

It can be divided into the parser and the lexer

# What is Lexer?
# 什么是Lexer(词法分析程序)
**
*
Lexer can split the source code to some words.
Lexer(词法分析程序)可以将源代码拆分为几个单词
*
**

# What is Parser? !
# 什么是Parser(语法、语义分析程序)
**
*
The parser can parse the tokens split by the lexer.
Parser(语法、语义分析程序)可以解析由Lexer(词法分析程序)拆分的单词
*
**

# For Example?

# NO.ONE
**variable = expr(if expr)
            /    \
      expr (+|-) expr(if expr)
      /             \
expr (*|/)expr      expr (*|/)expr
(if expr)           (if expr)
for example variable = 0*4
AST be like this one:
variable = expr
         /    \
        0 + expr //can delete
           /   \
          0 *   4 **
          
# NO.TWO
**
print(sth)
    /    \
data[sth]   sth
(if variable) (if expr)
for example expr = "something"
AST be like this one:
print(sth)
       |
       "something"
console:
       something
**

Tips
-------

-  If you have it, you can run the source code and see its principle.

-  If it really helps you, please tap the star of this repository to support us.
