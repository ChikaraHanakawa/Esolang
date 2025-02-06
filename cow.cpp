#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <stack>
#include <array>
#include <algorithm>

#define INCREMENT "MoO"
#define DECREMENT "MOo"
#define RIGHT "moO"
#define LEFT "mOo"
#define LOOP_START "MOO"
#define LOOP_END "moo"
#define OUTPUT "OOM"
#define INPUT "oom"
#define COMMAND "mOO"
#define ZERO "OOO"
#define COPY "MMM"
#define IO "Moo"
constexpr unsigned int MEMORY_SIZE = 30000;

int main(int argc, char *argv[]){
    unsigned char memory[MEMORY_SIZE];
    unsigned int ptr = 0;
    unsigned int code_ptr = 0;
    unsigned int code_len = 0;
    std::stack<int> loops;
    int command = 0;
    int register_value = -1;
    memset(memory, 0, sizeof(memory));

    if(argc < 2){
        std::cerr << "Usage: " << argv[0] << " <cow code>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if(!file){
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string code(buffer.str());
    code.erase(std::remove_if(code.begin(), code.end(), ::isspace), code.end());
    code_len = code.size();

    while(code_ptr < code_len){
        std::string currend_command = code.substr(code_ptr, 3);
        if(currend_command == INCREMENT){
            memory[ptr]++;
        }
        else if(currend_command == DECREMENT){
            memory[ptr]--;
        }
        else if(currend_command == RIGHT){
            ptr = (ptr >= MEMORY_SIZE - 1) ? 0 : ptr + 1;
        }
        else if(currend_command == LEFT){
            ptr = (ptr == 0) ? MEMORY_SIZE - 1 : ptr - 1;
        }
        else if(currend_command == LOOP_START){
            loops.push(code_ptr);
        }
        else if(currend_command == LOOP_END){
            if(memory[ptr] != 0){
                code_ptr = loops.top();
            }
            else{
                loops.pop();
            }
        }
        else if(currend_command == OUTPUT){
            memory[ptr] > 128 ? memory[ptr] = memory[ptr] - 128 : memory[ptr];
            std::cout << memory[ptr];
        }
        else if(currend_command == INPUT){
            std::cin >> memory[ptr];
        }
        else if(currend_command == COMMAND){
            if(memory[ptr] == 0 || memory[ptr] == 3){
                continue;
            }
            command = (memory[ptr]) % 4;
            if(command == 2 || memory[ptr] == 1){
                ptr = (ptr >= MEMORY_SIZE - 1) ? 0 : ptr + 1;
            }else if(command == 3 || memory[ptr] == 2){
                ptr = (ptr == 0) ? MEMORY_SIZE - 1 : ptr - 1;
            }else if(command == 0){
                memory[ptr]++;
            }else if(command == 1){
                memory[ptr]--;
            }
        }
        else if(currend_command == ZERO){
            memory[ptr] = 0;
        }
        else if(currend_command == COPY){
            if(register_value == -1){
                register_value = memory[ptr];
            }
            else{
                memory[ptr] = register_value;
                register_value = -1;
            }
        }
        else if(currend_command == IO){
            if(memory[ptr] == 0){
                std::cin >> memory[ptr];
            }
            else{
                memory[ptr] > 128 ? memory[ptr] = memory[ptr] - 128 : memory[ptr];
                std::cout << memory[ptr];
            }
        }
        code_ptr += 3;
    }
    return 0;
}