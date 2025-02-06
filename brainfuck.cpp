#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <stack>

constexpr unsigned int MEMORY_SIZE = 30000;
constexpr char INCREMENT = '+';
constexpr char DECREMENT = '-';
constexpr char RIGHT = '>';
constexpr char LEFT = '<';
constexpr char LOOP_START = '[';
constexpr char LOOP_END = ']';
constexpr char OUTPUT = '.';
constexpr char INPUT = ',';

int main(int argc, char *argv[]){
    unsigned char memory[MEMORY_SIZE];
    unsigned int ptr = 0;
    unsigned int code_ptr = 0;
    unsigned int code_len = 0;

    std::stack<int> loops;

    memset(memory, 0, sizeof(memory));

    if(argc < 2){
        std::cerr << "Usage: " << argv[0] << " <brainfuck code>" << std::endl;
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
    code_len = code.size();

    while(code_ptr < code_len){
        switch(code[code_ptr]){
            case INCREMENT:
                memory[ptr]++;
                break;
            case DECREMENT:
                memory[ptr]--;
                break;
            case RIGHT:
                ptr = (ptr >= MEMORY_SIZE - 1) ? 0 : ptr + 1;
                    // syntax
                    // if (ptr >= MEMORY_SIZE-1)
                    //     ptr = 0;
                    // else
                    //     ptr++;
                    // break;
                break;
            case LEFT:
                ptr = (ptr == 0) ? MEMORY_SIZE - 1 : ptr - 1;
                    // syntax
                    // if (ptr == 0)
                    //     ptr = MEMORY_SIZE - 1;
                    // else
                    //     ptr--;
                    //
                break;
            case LOOP_START:
                loops.push(code_ptr);
                if(memory[ptr] == 0){
                    int depth = 1;
                    while(depth != 0){
                        code_ptr++;
                        if(code_ptr >= code_len){
                            std::cerr << "Error: Unmatched '['" << std::endl;
                            return 1;
                        }
                        if(code[code_ptr] == LOOP_START){
                            depth++;
                        } else if(code[code_ptr] == LOOP_END){
                            depth--;
                        }
                    }
                } else {
                    loops.push(code_ptr);
                }
                break;
            case LOOP_END:
                if(loops.empty()){
                    std::cerr << "Error: Unmatched ']'" << std::endl;
                    return 1;
                }
                code_ptr = loops.top() - 1;
                loops.pop();
                break;
            case OUTPUT:
                std::cout << memory[ptr];
                break;
            case INPUT:
                std::cin >> memory[ptr];
                break;
            default:
                break;
        }
        code_ptr++;
    }
    return 0;
}