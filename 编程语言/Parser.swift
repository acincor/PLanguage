import Foundation
/*LL下降分析器*/
class Function: NSObject {
    @objc func print(_ t: [String]){
        NSLog(t.joined(separator: " "))
    }
    @objc func print() {
        NSLog(" ")
    }
}
class LLParser {
    var varriables: [String:[String:Any]] = [:]
    var functions: [String:[String]] = ["print": ["内置"]]
    var tokens: [String]
    var lookahead: String
    var classIn: [String] = ["string","double"]
    var i: Int;
    func nextToken() {
        //NSLog(lookahead)
        i+=1
        lookahead = tokens[i]
        //NSLog(i)
    }
    var compilerStatus = ""
    func V() throws {
        compilerStatus+="V -> "
        while(lookahead.count > 1 ? true : lookahead.count > 0 ? Character(lookahead).isLetter : false){
            try value()
        }
    }
    func funct(_ l: String) throws -> Any?{
        nextToken()
        if let e = try F(), (functions[l] ?? []).first == "内置"{
            let fun = Function()
            var actionStr = l+":"
            var sel = NSSelectorFromString(actionStr)
            if e == "" {
                actionStr = l
                sel = NSSelectorFromString(actionStr)
                return fun.perform(sel).takeRetainedValue()
            } else {
                return fun.perform(sel, with: e.split(separator: "|{,}|")).takeRetainedValue()
            }
        }
        return nil
    }
    func value() throws {
        var l = lookahead
        if functions.keys.contains(l){
            if let _ = try funct(l){
                return
            }
            NSLog("语法错误")
        } else if (l.first, l.last) == ("\"","\"") {
            l.removeFirst()
            l.removeLast()
            NSLog(l)
            nextToken()
            return
        }
        else if Double(l) != nil {
            NSLog(l)
            nextToken()
            return
        }
             nextToken()
            if lookahead == "=" {
                nextToken()
            } else if lookahead == ":" {
                nextToken()
                varriables[l] = ["type":lookahead,"name":l,"value":lookahead]
                nextToken()
                try V()
            }
        if var v = varriables[l] {
            if classIn.contains(v["type"] as! String){
                v["value"] = try E()
                varriables[l] = v
                return
            }
            NSLog(">> Cannot assign value of type another to subscript of type '\(v["type"]!)'")
            return
        }
        varriables[l] = ["type":(l.first, l.last) == ("\"","\"") ? "string" : "double","name":l,"value":try E() ?? "nil"]
    }
    func E() throws -> String? {
        var result2 = ""
        var result:Double = 0
        let t0 = try T()
        compilerStatus+="E -> "
        if let t1 = Double(t0 ?? "") {
            result += t1
            
            while(lookahead == "+"){
                nextToken()
                if let t2 = try Double(T() ?? "") {
                    result += t2
                } else {
                    NSLog(">> 类型出现问题")
                    return nil
                }
            }
            if (lookahead == ",") {
                result2 += "\(t1)"
                while(lookahead == ","){
                    nextToken()
                    if let t2 = try T() {
                        result2 += "|{,}|"+"\(t2)"
                    } else {
                        NSLog(">> 类型出现问题")
                        return nil
                    }
                }
                return result2
            }
            while(lookahead == "-"){
                nextToken()
                if let t2 = try Double(T() ?? "") {
                    result -= t2
                } else {
                    NSLog(">> 类型出现问题")
                    return nil
                }
            }
            return "\(result)"
        }
        else if let t1 = t0 {
            result2 += t1
            while(lookahead == "+"){
                nextToken()
                if let t2 = try T() {
                    result2 += t2
                } else {
                    NSLog(">> 类型出现问题")
                    return nil
                }
            }
            while(lookahead == ","){
                nextToken()
                if let t2 = try T() {
                    result2 += "|{,}|"+t2
                } else {
                    NSLog(">> 类型出现问题")
                    return nil
                }
            }
        }
        return result2
    }
    func T() throws -> String? {
        compilerStatus+="T -> "
        let f0 = try F()
        if var f1 = Double(f0 ?? "") {
            while(lookahead == "*"){
                nextToken()
                let f2 = try F()
                if let f = Double(f2 ?? "") {
                    f1 *= f == 0 ? 1 : f1
                }
            }
            while(lookahead == "/"){
                nextToken()
                let f2 = try F()
                if let f = Double(f2 ?? "") {
                    f1 /= f == 0 ? 1 : f
                }
            }
            return "\(f1)"
        }
        return f0
    }
    func F() throws -> String?{
        compilerStatus+="F -> "
        if(Double(lookahead) != nil) {
            let l = lookahead
            nextToken()
            return l
        }
        else if (lookahead.first,lookahead.last) == ("\"","\"") {
            lookahead.removeFirst()
            lookahead.removeLast()
            let l = lookahead
            nextToken()
            return l
        }
        else if(lookahead == "(") {
            nextToken()
            //")"
            let e = try E()
            if(lookahead == ")") {
                nextToken()
                return e!
            }
            else {
                if(lookahead == ")") {
                    nextToken()
                    return e!
                }
                //NSLog("error: ')' is missing")//消失的括号笑死我了哈哈哈哈哈哈哈
                throw NSError(domain: "com.Mhc-inc", code: 500, userInfo: ["error":"')' is missing"])
            }
        }
        else{
            if varriables[lookahead] != nil {
                let f = varriables[lookahead]!
                nextToken()
                return f["value"]! as? String
            }
            if functions[lookahead] != nil {
                if let funct = try funct(lookahead){
                    return funct as? String ?? "()"
                }
                return "()"
            }
            if(lookahead == ")") {
                return ""
            }
            else if lookahead != "\n" {
                throw NSError(domain: "com.Mhc-inc", code: 500, userInfo: ["error":"unknown lookahead '\(lookahead)'"])
            }
        }
        return nil
    }
    init(tokens:[String]) throws {
        NSLog("==语法分析开始==")
        self.tokens = tokens
        i = 0
        lookahead = tokens.first!
        try V()
        //NSLog("status: \(compilerStatus+"end")")
        NSLog("==语法分析结束==")
    }
}
