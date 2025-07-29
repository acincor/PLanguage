//
//  std.cpp
//
//
//  Created by Acinc on 20/04/2025.
//

#include <iostream>
#include <vector>
#include<map>
#include<tuple>
#include <string>
#include <set>
#include <mutex>
#include<sstream>
#include <functional>
#include<algorithm>
#include<iomanip>
#include<fstream>

using namespace std;
string ToString(double t)
{
    std::stringstream ss;
    ss << std::setprecision(15) << t;
    return string(ss.str());
}
char scanstr(string s)
{
    switch (s[1]) {
        case 'b':
            return '\b';
        case '\"':
            return '\"';
        case '\\':
            return '\\';
        case 'f':
            return '\f';
        case 'n':
            return '\n';
        case 'r':
            return '\r';
        case 't':
            return '\t';
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7': {
            unsigned long octVal = 0;
            for (int k = 1; s[k] >= '0' && s[k] <= '7' && k < 3; k++){
                octVal = (octVal << 3) + (s[k] - '0');
            }
            return((char)octVal);
        } break;
        default:
            return s[1];
            break;
    }
}

class LLLexer {
public:
    vector<string> tokens = {""};
    vector<double> nums;
    vector<string> symbols;
    int tI = 0;
    string errors = "";
    string read;
    long unsigned int count = 0;
    int spaceCount = 0;
    int reserve(string a) {
        map<string,int> dict = {{"while",1},{"if",2},{"else",3},{"switch",4},{"case",5},{"print",6}};
        if(dict.find(a) == dict.end())
            return 0;
        return dict[a];
    }
    char getChar() {
        if (count >= read.size()) {
            return '\0';
        }
        char res = read[count];
        count += 1;
        return res;
    }
    void getbe() {
        while (character == ' ') {
            character = getChar();
            spaceCount += 1;
        }
    }
    auto Lexer()->tuple<string,string>{
        getbe();
        int c;
        char cha;
        switch (character) {
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'g':
            case 'h':
            case 'i':
            case 'j':
            case 'k':
            case 'l':
            case 'm':
            case 'n':
            case 'o':
            case 'p':
            case 'q':
            case 'r':
            case 's':
            case 't':
            case 'u':
            case 'v':
            case 'w':
            case 'x':
            case 'y':
            case 'z':
                tI ++;
                tokens[tI-1] = "";
                while (isalpha(character) || isdigit(character)) {
                    tokens[tI-1]+=character;
                    character = getChar();
                }
                c = reserve(tokens[tI-1]);
                if (c == 0) {
                    if (find(symbols.begin(), symbols.end(), tokens[tI-1]) != symbols.end()) {
                        symbols.push_back(tokens[tI-1]);
                    }
                    tokens.push_back("\n");
                    return tuple<string,string>("id",to_string(symbols.size()));
                } else {
                    tokens.push_back("\n");
                    return tuple<string,string>(to_string(c),"<null>");
                }
            case '\"':
                tI ++;
                tokens[tI-1] = "\"";
                character = getChar();
                while (character != '\"' && count < read.size()-1) {
                    if(character == '\\') {
                        character = getChar();
                        string f = "\\";
                        if(isalpha(character) || character == '\\' || character == '\"') f+=character;
                        
                        while(isdigit(character) && count < read.size()-1) {
                            f+=character;
                            character = getChar();
                        }
                        tokens[tI-1]+=scanstr(f);
                    } else {
                        tokens[tI-1] += character;
                    }
                    character = getChar();
                }
                if(character == '\"') {
                    tokens[tI-1] += '\"';
                    character = getChar();
                } else {
                    character = '\n';
                }
                symbols.push_back(tokens[tI-1]);
                tokens.push_back("\n");
                return tuple<string,string>(tokens[tI-1],"<null>");
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                tI ++;
                tokens[tI-1] = "";
                while (isdigit(character) || character == '.') {
                    tokens[tI-1] += character;
                    character = getChar();
                }
                tokens.push_back("\n");
                try {
                    double d = stod(tokens[tI-1]);
                    nums.push_back(d);
                    return tuple<string, string>("num",to_string(nums.size()));
                    
                } catch(const std:: invalid_argument &ia) {
                    tokens.push_back("\n");
                    errors+=">> error: illegal identifier '"+tokens[tI-1]+"'\n";
                    return tuple<string, string>("error","illegal identifier '"+tokens[tI-1]+"'");
                } catch(const std::out_of_range& oor) {
                    tokens.push_back("\n");
                    errors+=">> error: illegal identifier '"+tokens[tI-1]+"'\n";
                    return tuple<string, string>("error","illegal identifier '"+tokens[tI-1]+"'");
                }
                break;
            case '/':
                cha = character;
                character = getChar();
                if (character == '/') {
                    while (character != '\n') {
                        character = getChar();
                    }
                } else {
                    tI ++;
                    tokens[tI-1] = cha;
                    tokens.push_back("\n");
                }
                return tuple<string,string>("0","0");
            case '+':
            case '-':
            case ':':
            case ';':
            case ',':
            case '*':
                cha = character;
                character = getChar();
                tI += 1;
                tokens[tI-1] = cha;
                tokens.push_back("\n");
                return tuple<string, string>(to_string(cha),"<null>");
            case '<':
                tI += 1;
                tokens[tI-1] = character;
                character = getChar();
                tokens.push_back("\n");
                if (character == '=') {
                    tokens[tI-1].push_back(character);
                    return tuple<string,string>("relop","LE");
                } else {
                    return tuple<string,string>("relop","LT");
                }
            case '=':
                tI ++;
                tokens[tI-1] = character;
                character = getChar();
                tokens.push_back("\n");
                if (character == '=') {
                    tokens[tI-1].push_back(character);
                    return tuple<string,string>("relop","EQ");
                } else {
                    return tuple<string,string>("=","<null>");
                }
            case '(':
            case '[':
            case ')':
            case '}':
            case '{':
                tI ++;
                tokens[tI-1] = character;
                tokens.push_back("\n");
                cha = character;
                character = getChar();
                return tuple<string,string>(to_string(cha), "<null>");
            default:
                cha = character;
                character = getChar();
                tI ++;
                tokens[tI-1] = cha;
                tokens.push_back("\n");
                ostringstream oss;
                oss << "illegal identifier '" << cha << "'";
                errors+=">> error: "+oss.str()+"\n";
                return tuple<string, string>("error",oss.str());
        }
    }
    void readOneLine() {
        count=0;
        character = getChar();
        while (character != '\n') {
            tuple<string,string> res = Lexer();
        }
    }
    char character;
    LLLexer() {
        while(getline(cin, read)) {
            read += "\n";
            readOneLine();//读取一行
        }
    }
};
char first(string s) {
    if(s.size() < 0)
        return '\0';
    return s[0];
}
string first(vector<string> s) {
    if(s.size() < 0)
        return "NULL";
    return s[0];
}
char last(string s) {
    if(s.size() <= 0)
        return '\0';
    return s[s.size()-1];
}
string results = "";
void addingResult(string message) {
    results+=message;
}
std::vector<std::string> split(const std::string& str, const std::string& delimiter, bool keep_empty = false) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    size_t len = delimiter.length();
    
    if (len == 0) return {str};
    
    while (true) {
        size_t found = str.find(delimiter, pos);
        if (found == std::string::npos) {
            std::string token = str.substr(pos);
            if (keep_empty || !token.empty()) {
                tokens.push_back(token);
            }
            break;
        }
        
        std::string token = str.substr(pos, found - pos);
        if (keep_empty || !token.empty()) {
            tokens.push_back(token);
        }
        pos = found + len;
    }
    
    return tokens;
}
typedef const void* SEL;
SEL NSSelectorFromString(const std::string& str) {
    static std::mutex mutex;
    static std::set<std::string> selectorStrings;
    std::lock_guard<std::mutex> lock(mutex);
    auto it = selectorStrings.find(str);
    if (it != selectorStrings.end()) {
        return reinterpret_cast<SEL>(&(*it));
    } else {
        auto result = selectorStrings.insert(str);
        return reinterpret_cast<SEL>(&(*result.first));
    }
}
class Function {
public:
    
    void print(std::vector<std::string> t) {
        for (auto& i : t)
            addingResult(i + " ");
        addingResult("\n");
    }
    
    void print() {
        addingResult(" \n");
    }

    void perform(SEL selector, const std::vector<std::string>& args = {}) {
        static const auto& handlerMap = getHandlerMap();
        auto it = handlerMap.find(selector);
        if (it != handlerMap.end()) {
            it->second(this, args);
        } else {
            std::cerr << "Unrecognized selector" << std::endl;
        }
    }
    
private:
    using Handler = std::function<void(Function*, const std::vector<std::string>&)>;
    static const std::map<SEL, Handler>& getHandlerMap() {
        static const std::map<SEL, Handler> handlerMap = {
            { NSSelectorFromString("print"),
                [](Function* obj, const auto& args) { obj->print(); }},
            
            { NSSelectorFromString("printWithVector"),
                [](Function* obj, const auto& args) { obj->print(args); }}
        };
        return handlerMap;
    }
};
class LLParser {
    int status_code = 200;
    public:
    map<string,map<string,string>> variables;
    map<string,vector<string>> functions = {{"print", {"内置"}}};
    vector<string> tokens;
    string lookahead;
    vector<string> classIn = {"string","double"};
    int i;
    double convertToDouble(const std::string& str) {
        status_code = 200;
        double val;
        std::istringstream iss(str);
        if (!(iss >> val)) {
            status_code = 404;
            return 0;
        }
        return val;
    }
    
    void nextToken() {
        i++;
        lookahead = tokens[i];
    }
    void backToken() {
        i--;
        lookahead = tokens[i];
    }
    int check(string s) {
        return (s.size() > 1 && s != "()") ? true : (s.size() > 0 ? isalpha(first(s)) || isdigit(first(s)) : false);
    }
    void V() {
        compileStatus+="V";
        while(check(lookahead)) {
            string tmp = lookahead, type = "NULL";
            nextToken();
            if(lookahead == "=") {
                nextToken();
                dealWithVariables(type, tmp);
            } else if(lookahead == ":") {
                nextToken();
                type = lookahead;
                dealWithVariables(type, tmp);
                nextToken();
            } else {
                backToken();
                auto e = E();
                if(check(e)) {
                    convertToDouble(e);
                    if(status_code != 200) {
                        e = "\"" + e + "\"";
                    }
                    addingResult(e+"\n");
                }
            }
            if(lookahead == ";")nextToken();
        }
    }
    string getAndNext() {
        auto l = lookahead;
        nextToken();
        return l;
    }
    string funct(string l) {
        nextToken();
        string e = F();
        if (functions.find(l) != functions.end() ? first(functions[l]) == "内置" : false) {
            auto fun = Function();
            auto actionStr = l+"WithVector";
            auto sel = NSSelectorFromString(actionStr);
            if (e == "") {
                actionStr = l;
                sel = NSSelectorFromString(actionStr);
                fun.perform(sel);
            } else {
                fun.perform(sel, split(e, "|{,}|"));
            }
            return "()";
        }
        return "NULL";
    }
    void dealWithVariables(string type, string name) {
        if(variables.find(name) == variables.end()) {
            if(type != "NULL")
                if (find(classIn.begin(),classIn.end(), type) == classIn.end()) {
                    addingResult(">> Use of undeclared identifier '"+type+"'\n");
                    return;
                }
            variables[name] = {{"type",type},{"name",name},{"value", (type != "NULL") ? "NULL" : E()}};
            return;
        }
        if(type != "NULL") {
            addingResult(">> Cannot have duplicate definitions\n");
            return;
        }
        auto e = E();
        if (variables[name]["type"] == ((first(e) == last(e) && first(e) == '\"') ? "string" : "double"))
            variables[name]["value"] = e;
        else
            addingResult(">> Cannot assign value of type another to subscript of type '"+variables[name]["type"]+"'\n");
    }
    string deal(int op, double &result) {
        double t2 = convertToDouble(T());
        if(status_code == 200) {
            result += op * t2;
            return "plus all right!";
        }
        addingResult(">> 类型出现问题\n");
        return "NULL";
    }
    string dealWithExpression(string s, string &result) {
        auto t2 = T();
        if (t2 != "NULL") {
            result += s+t2;
            return "plus all right!";
        }
        addingResult(">> 类型出现问题\n");
        return "NULL";
    }
    string dealWithArgs(string &result) {
        while(lookahead == ","){
            nextToken();
            if(dealWithExpression("|{,}|",result) == "NULL")
                return "NULL";
        }
        return "OK";
    }
    string E() {
        compileStatus+="E";
        string result2 = "";
        double result = 0;
        auto t0 = T();
        auto t1 = convertToDouble(t0);
        if(status_code == 200) {
            
            result += t1;
            while(lookahead == "+"){
                nextToken();
                if(deal(1, result) == "NULL")
                    return "NULL";
            }
            if (lookahead == ",") {
                result2 += t0;
                if(dealWithArgs(result2) == "NULL")
                    return "NULL";
                return result2;
            }
            while(lookahead == "-"){
                nextToken();
                if(deal(-1, result) == "NULL")
                    return "NULL";
            }
            return ToString(result);
        }
        if(t0 != "NULL") {
            auto t1 = t0;
            result2 += t1;
            while(lookahead == "+"){
                nextToken();
                if(dealWithExpression("",result2) == "NULL")
                    return "NULL";
            }
            if(dealWithArgs(result2) == "NULL")
                return "NULL";
        }
        return result2;
    }
    string T() {
        compileStatus+="T";
        auto f0 = F();
        auto f1 = convertToDouble(f0);
        if(status_code == 200){
            while(lookahead == "*"){
                nextToken();
                auto f2 = convertToDouble(F());
                f1 *= f2 == 0 ? 1 : f1;
            }
            while(lookahead == "/"){
                nextToken();
                auto f2 = convertToDouble(F());
                f1 /= f2 == 0 ? 1 : f2;
            }
            return ToString(f1);
        }
        return f0;
    }
    string F() {
        compileStatus+="F";
        auto _ = convertToDouble(lookahead);
        if(status_code == 200) {
            return getAndNext();
        }
            if (first(lookahead) == '\"') {
                if(last(lookahead) != '\"' || lookahead.size() == 1) {
                    addingResult("error='\"' is missing\n");
                    nextToken();
                    return "NULL";
                }
                lookahead.erase(0,1);
                lookahead.erase(lookahead.size()-1);
                return getAndNext();
            }
            else if(lookahead == "(") {
                nextToken();
                auto e = E();
                if(lookahead == ")") {
                    nextToken();
                    return e;
                }
                else
                    addingResult("error=')' is missing\n");
            }
            else{
                if (variables.find(lookahead) != variables.end()) {
                    auto f = variables[lookahead];
                    nextToken();
                    return f["value"];
                }
                if (functions.find(lookahead) != functions.end()) {
                    auto func = funct(lookahead);
                    if (func != "NULL"){
                        return func;
                    }
                    return "()";
                }
                if(lookahead == ")") {
                    return "";
                }
                else if (lookahead != "\n") {
                    addingResult("error=unknown lookahead '"+lookahead+"'\n");
                    nextToken();
                }
            }
        return "NULL";
    }
public:
    string compileStatus = "";
    LLParser(vector<string> token) {
        results = "==语法分析开始==\n";
        tokens = token;
        i = 0;
        lookahead = tokens[0];
        V();
        results+="==语法分析结束==\n";
    }
};
int main(int argc, const char * argv[]) {
    LLLexer lexer = LLLexer();
    LLParser parser(lexer.tokens);
    //printf("%s", (lexer.errors+results).c_str()); 可能缺少函数输出值
    cout << lexer.errors+results;
    return 0;
}
