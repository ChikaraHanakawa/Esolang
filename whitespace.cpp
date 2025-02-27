#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>

constexpr const char SPACE = ' ';
constexpr const char TAB = '\t';
constexpr const char NEWLINE = '\n';
std::vector<int> stack;

void pushstack(std::string line, std::string document){
    int index = 3;
    while(index < line.size() && line[index] != NEWLINE){
        if(line[index] == SPACE){
            document += "0";
        }else if(line[index] == TAB){
            document += "1";
        }
        index++;
    }
    int num = std::stoi(document, nullptr, 2);
    stack.push_back(num);
}

void copystack(){
    int num = stack[0];
    stack.push_back(num);
}

void exchange(){
    int num = stack[0];
    stack[0] = stack[1];
    stack[1] = num;
}

void remove(){
    stack.erase(stack.begin(), stack.begin() + 1);
}

void select_copystack(std::string line, std::string document){
    int index = 3;
    while(index < line.size() && line[index] != NEWLINE){
        if(line[index] == SPACE){
            document += "0";
        }else if(line[index] == TAB){
            document += "1";
        }
        index++;
    }
    int num = std::stoi(document, nullptr, 2);
    if(num < stack.size()){
        stack.insert(stack.begin(), stack[num]);
    }
}

void calculate_add(){
    int num = stack[1] + stack[0];
    std::cout << num << std::endl;
}

void calculate_sub(){
    int num = stack[1] - stack[0];
    std::cout << num << std::endl;
}

void calculate_mul(){
    int num = stack[1] * stack[0];
    std::cout << num << std::endl;
}

void calculate_div(){
    int num = stack[1] / stack[0];
    std::cout << num << std::endl;
}

void calculate_mod(){
    int num = stack[1] % stack[0];
    std::cout << num << std::endl;
}

class WhitespaceInterpreter {
public:
    void interpret(const std::string& code) {
        std::istringstream iss(code);
        std::string line;
        bool previous_newline = false;

        while (std::getline(iss, line)) {
            if (line.empty()) {
                handleEmptyLine(previous_newline);
            } else if (line[0] == SPACE && line[1] == SPACE) {
                handleSpaceSpace(line);
            } else if (line[0] == SPACE && previous_newline) {
                handleSpaceNewline(previous_newline);
            } else if (line[0] == TAB && previous_newline) {
                handleTabNewline(previous_newline);
            } else if (line[0] == SPACE && line[1] == TAB) {
                handleSpaceTab(line);
            } else if (line[0] == TAB && line[1] == SPACE) {
                handleTabSpace(line);
            }
        }
    }

private:
    void handleSpaceSpace(const std::string& line) {
        std::string document = "";
        if (line[2] == SPACE) {
            document += "+";
            pushstack(line, document);
        } else if (line[2] == TAB) {
            document += "-";
            pushstack(line, document);
        }
    }

    void handleEmptyLine(bool& previous_newline) {
        if (previous_newline) {
            remove();
            previous_newline = false;
        } else {
            previous_newline = true;
        }
    }

    void handleSpaceNewline(bool& previous_newline) {
        copystack();
        previous_newline = false;
    }

    void handleTabNewline(bool& previous_newline) {
        exchange();
        previous_newline = false;
    }

    void handleSpaceTab(const std::string& line) {
        if (line[2] == SPACE) {
            std::string n = "";
            select_copystack(line, n);
        }
    }

    void handleTabSpace(const std::string& line) {
        if (line[2] == SPACE && line[3] == SPACE) {
            calculate_add();
        } else if (line[2] == SPACE && line[3] == TAB) {
            calculate_sub();
        } else if (line[2] == SPACE && line[3] == NEWLINE) {
            calculate_mul();
        } else if (line[2] == TAB && line[3] == SPACE) {
            calculate_div();
        } else if (line[2] == TAB && line[3] == TAB) {
            calculate_mod();
        }
    }
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string code = buffer.str();

    WhitespaceInterpreter interpreter;
    interpreter.interpret(code);
}