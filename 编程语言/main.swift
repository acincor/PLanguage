//
//  main.swift
//  编程语言
//
//  Created by mhc team on 2023/9/29.
//
//import module
import Foundation
// define a class
//定义类
//有意义的，LL（自动下降分析）Lexer（词法分析器）
class LLLexer {
    var tokens = [""]//define a tokens array
                    //定义一个记录tokens的数组
    var nums = [Double]()//define a nums array
                    //定义一个记录常数的数组
    var symbols = [String]()//define a symbols array
                    //定义一个记录符号的数组
    var tI = 0//define a tI(tokens index)
            //定义tokens的索引
    //define your function in here...
    //在这里定义你的函数...
    /// params:
    /// 参数列表：
    /// a : String
    /// a: 字符串
    /// name:
    /// reserve
    /// 名字：
    /// 判断关键词并返回
    func reserve(_ a: String) -> Int{
        /// dictionary
        /// if 'dictionary[a]' != nil return dictionary[a] else return 0
        let dict = ["while":1,"if":2,"else":3,"switch":4,"case":5,"print":6]
        guard let ret = dict[a] else {// guard let expression
            return 0
        }
        return ret // if return never do it
    }
    //init函数
    init() {
        //iOS里通常readLine返回nil，但是如果是命令行，会输入
        ///文件地址(path)
        guard let read = readLine() else {
            exit(-1001)//something was error
        }
        /// do catch方法，do里如果异常（如果try扔出错误）会执行catch语句，并且直接退出
        do {
            //判断这里是否有文件
            if FileManager.default.fileExists(atPath: read) {
                ///String(contentsOfFile: <#String#>)里的String参数(parameter)必须是一个文件地址，否则throw(扔)出错误（这里一定不会出现错误，因为判断这里是否有文件，没有不会执行这里）
                let readFiles = try String(contentsOfFile: read)
                ///遍历每行
                for read in readFiles.split(separator: "\n") {
                    ///read加上\n
                    let read = read+"\n"
                    ///read的索引
                    var count = 0
                    var character = getChar()
                    ///getChar()返回count对应的值后将count+1
                    /// name:
                    /// getChar
                    func getChar() -> Character?{
                        let res = read[read.index(read.startIndex, offsetBy: count)]
                        count += 1
                        return res
                    }
                    ///getbe滤除空格
                    /// name:
                    /// getbe
                    var spaceCount = 0
                    func getbe() {
                        //character是否是空格
                        while character == " " {
                            //下一个
                            character = getChar()
                            //判断有几个空格
                            spaceCount += 1
                        }
                    }
                    //define your function in here...
                    /// name:
                    /// Lexer
                    func Lexer()->(Any,Any){
                        //if read == "" {
                            //return(("error","nothing of input!"))
                        //}
                        getbe()
                        /// fallthrough关键字作用是可以直接将case连在一起
                        switch character {
                        case Character("a"):
                            fallthrough
                        case Character("b"):
                            fallthrough
                        case Character("c"):
                            fallthrough
                        case Character("d"):
                            fallthrough
                        case Character("e"):
                            fallthrough
                        case Character("f"):
                            fallthrough
                        case Character("g"):
                            fallthrough
                        case Character("h"):
                            fallthrough
                        case Character("i"):
                            fallthrough
                        case Character("j"):
                            fallthrough
                        case Character("k"):
                            fallthrough
                        case Character("l"):
                            fallthrough
                        case Character("m"):
                            fallthrough
                        case Character("n"):
                            fallthrough
                        case Character("o"):
                            fallthrough
                        case Character("p"):
                            fallthrough
                        case Character("q"):
                            fallthrough
                        case Character("r"):
                            fallthrough
                        case Character("s"):
                            fallthrough
                        case Character("t"):
                            fallthrough
                        case Character("u"):
                            fallthrough
                        case Character("v"):
                            fallthrough
                        case Character("w"):
                            fallthrough
                        case Character("x"):
                            fallthrough
                        case Character("y"):
                            fallthrough
                        case Character("z"):
                            tI += 1//tokens Index自加
                            tokens[tI-1] = ""//tokens（当前未加字母）上一个字符设为空值
                            while (character ?? "\0").isLetter || (character ?? "\0").isNumber {
                                tokens[tI-1].append(String(character ?? "\0"))
                                character = getChar()
                            }
                            //character = "\0"
                            let c = reserve(tokens[tI-1])
                            if c == 0 {
                                //symbols里如果含有这个关键字，我们不添加
                                if !symbols.contains(tokens[tI-1]) {
                                    symbols.append(tokens[tI-1])
                                }
                                tokens.append(String("\n"))
                                return(("id",symbols.endIndex))
                            } else {
                                tokens.append(String("\n"))
                                return((c,"<null>"))
                            }
                        case Character("\""):
                            tI += 1
                            tokens[tI-1] = "\""
                            character = getChar()
                            while !((character ?? "\0") == "\""){
                                if(String(character ?? "\0") == "\\") {
                                    character = getChar()
                                    tokens[tI-1].append(String(character ?? "\0"))
                                } else {
                                    tokens[tI-1].append(String(character ?? "\0"))
                                }
                                character = getChar()
                            }
                            character = getChar()
                            tokens[tI-1].append("\"")
                            symbols.append(tokens[tI-1])
                            tokens.append(String("\n"))
                            return((tokens[tI-1],"<null>"))
                        case Character("0"):
                            fallthrough
                        case Character("1"):
                            fallthrough
                        case Character("2"):
                            fallthrough
                        case Character("3"):
                            fallthrough
                        case Character("4"):
                            fallthrough
                        case Character("5"):
                            fallthrough
                        case Character("6"):
                            fallthrough
                        case Character("7"):
                            fallthrough
                        case Character("8"):
                            fallthrough
                        case Character("9"):
                            tI += 1
                            tokens[tI-1] = ""
                            while (character ?? "\0").isNumber || (character ?? "\0") == "." {
                                tokens[tI-1].append(String(character ?? "\0"))
                                character = getChar()
                            }
                            //character = "\0"
                            nums.append(Double(tokens[tI-1])!)
                            tokens.append(String("\n"))
                            return(("num",nums.endIndex))
                        case Character("/"):
                            let char = character
                            character = getChar()
                            if character == "/" {
                                while (character ?? "\0") != "\n" {
                                    character = getChar()
                                }
                            } else {
                                tI += 1
                                tokens[tI-1] = String(char ?? "\0")
                                tokens.append("\n")
                            }
                            return(0,0)
                        case Character("+"):
                            fallthrough
                        case Character("-"):
                            fallthrough
                        case Character(";"):
                            fallthrough
                        case Character(":"):
                            fallthrough
                        case Character(","):
                            fallthrough
                        case Character("*"):
                            let char = character
                            character = getChar()
                            tI += 1
                            tokens[tI-1] = String(char ?? "\0")
                            tokens.append(String("\n"))
                            return((char ?? "\0","<null>"))
                        case Character("<"):
                            tI += 1
                            tokens[tI-1] = String(character ?? "\0")
                            character = getChar()
                            tokens.append(String("\n"))
                            if character == "=" {
                                tokens[tI-1].append(String(character ?? "\0"))
                                return(("relop","LE"))
                            } else {
                                //character = "\0"
                                return(("relop","LT"))
                            }
                        case Character("="):
                            tI += 1
                            tokens[tI-1] = String(character ?? "\0")
                            character = getChar()
                            tokens.append(String("\n"))
                            if character == "=" {
                                tokens[tI-1].append(String(character ?? "\0"))
                                return(("relop","EQ"))
                            } else {
                                //character = "\0"
                                return(("=","<null>"))
                            }
                        case Character("("):
                            fallthrough
                        case Character("["):
                            fallthrough
                        case Character(")"):
                            fallthrough
                        case Character("("):
                            fallthrough
                        case Character("}"):
                            fallthrough
                        case Character("{"):
                            tI += 1
                            tokens[tI-1] = String(character ?? "\0")
                            tokens.append(String("\n"))
                            let char = character
                            character = getChar()
                            return (char ?? "\0", "<null>")
                        default:
                            let char = character
                            character = getChar()
                            NSLog(">> error: illegal identifier '\(char ?? "\0")'")
                            return(("error","illegal identifier '\(char ?? "\0")'"))
                        }
                    }
                    func readOneLine() {
                        while character != "\n" {
                            _ = Lexer()
                            //NSLog(">> ('\(res.0)': \"\(res.1)\")")
                            //if res.0 as? String == "id" {
                            //NSLog(">> ('tip': \"'id' equals 'index': id '\(res.1)' equals '\(symbols[res.1 as? Int ?? 0])'\")")
                            //}
                        }
                    }
                    readOneLine()//读取一行
                }
            } else {
                NSLog("Your input is error, "+(read != "" ? "the read file is not exists.": "you input nothing."))
            }
        } catch {
            ///error是try抛出的错误
            NSLog("\(error)")
        }
    }
}
let lex = LLLexer()
//print(lex.tokens)
let parser = try LLParser(tokens: lex.tokens)
