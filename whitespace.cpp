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

int main(int argc, char *argv[]){
    unsigned int ptr = 0;
    unsigned int code_ptr = 0;

    if(argc != 2){
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
    std::ifstream file(argv[1]);
    if(!file.is_open()){
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string code = buffer.str();
    std::istringstream iss(code);
    std::string line;
    bool previous_newline = false;
    while (std::getline(iss, line)){
        std::string document = "";
        if(line[0] == SPACE && line[1] == SPACE){
            if(line[2] == SPACE){
                document += "+";
                pushstack(line, document);
            }else if(line[2] == TAB){
                document += "-";
                pushstack(line, document);
            }
        }
        if(line.empty()){
            if(previous_newline){
                remove();
                previous_newline = false;
            } else {
                previous_newline = true;
            }
        } else {
            previous_newline = false;
            if(line[0] == SPACE && line[1] == SPACE){
                if(line[2] == SPACE){
                    document += "+";
                    pushstack(line, document);
                }else if(line[2] == TAB){
                    document += "-";
                    pushstack(line, document);
                }
            }else if(line[0] == SPACE){
                copystack();
            }else if(line[0] == TAB){
                exchange();
            }
        }
        if(line[0] == SPACE && line[1] == TAB){
            if(line[2] == SPACE){
                std::string n = "";
                select_copystack(line, n);
            }
        }
    }
}