#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <stdexcept>

using namespace std;


enum OpCode { PUSH, ADD, SUB, MUL, DIV, PRINT, INPUT, DUP, SWAP, DROP, IF, ENDIF, EQ };

struct Instruction {
    OpCode op;
    string value;   // for PUSH only
    size_t jump = 0; // for IF: index to jump to ENDIF if false
};

class VM {
    vector<string> stack;
    vector<Instruction> program;

public:
    VM(const vector<Instruction>& prog) : program(prog) {}

    void run() {
        for (size_t ip = 0; ip < program.size(); ip++) {
            Instruction instr = program[ip];

            switch (instr.op) {
                case PUSH:
                    stack.push_back(instr.value);
                    break;

                case ADD: {
                    int b = stoi(pop());
                    int a = stoi(pop());
                    stack.push_back(to_string(a + b));
                    break;
                }
                case SUB: {
                    int b = stoi(pop());
                    int a = stoi(pop());
                    stack.push_back(to_string(a - b));
                    break;
                }
                case MUL: {
                    int b = stoi(pop());
                    int a = stoi(pop());
                    stack.push_back(to_string(a * b));
                    break;
                }
                case DIV: {
                    int b = stoi(pop());
                    int a = stoi(pop());
                    if (b == 0) throw runtime_error("Division by zero");
                    stack.push_back(to_string(a / b));
                    break;
                }
                case PRINT:
                    cout << pop() << endl;
                    break;
                case INPUT: {
                    string v;
                    getline(cin, v);
                    stack.push_back(v);
                    break;
                }
                case DUP:
                    stack.push_back(stack.back());
                    break;
                case SWAP: {
                    string a = pop();
                    string b = pop();
                    stack.push_back(a);
                    stack.push_back(b);
                    break;
                }
                case DROP:
                    pop();
                    break;
                case IF: {
                    int cond = stoi(pop());
                    if (cond == 0) ip = instr.jump; // skip to ENDIF
                    break;
                }
                case ENDIF:
                    break;
                case EQ: {
                    int b = stoi(pop());
                    int a = stoi(pop());
                    stack.push_back(to_string(a == b ? 1 : 0));
                    break;
                }

            }
        }
    }

private:
    string pop() {
        if (stack.empty()) throw runtime_error("Stack underflow");
        string v = stack.back();
        stack.pop_back();
        return v;
    }
};


vector<Instruction> parseProgram(const string& source) {
    vector<Instruction> program;
    istringstream input(source);
    string line;
    vector<size_t> ifStack;

    while (getline(input, line)) {
        if (line.empty()) continue;

        istringstream iss(line);
        string keyword;
        iss >> keyword;

        if (keyword == "tickle") {
            string value;
            getline(iss, value);
            if (!value.empty() && value[0] == ' ') value.erase(0, 1);
            program.push_back({PUSH, value});
        }
        else if (keyword == "+") program.push_back({ADD, ""});
        else if (keyword == "-") program.push_back({SUB, ""});
        else if (keyword == "*") program.push_back({MUL, ""});
        else if (keyword == "/") program.push_back({DIV, ""});
        else if (keyword == "yap") program.push_back({PRINT, ""});
        else if (keyword == "hearmeout") program.push_back({INPUT, ""});
        else if (keyword == "dupe") program.push_back({DUP, ""});
        else if (keyword == "swap") program.push_back({SWAP, ""});
        else if (keyword == "drop") program.push_back({DROP, ""});
        else if (keyword == "if_true") {
            program.push_back({IF, "", 0});
            ifStack.push_back(program.size() - 1); 
        }
        else if (keyword == "endif") {
            if (ifStack.empty()) throw runtime_error("ENDIF without matching IF");
            size_t ifIndex = ifStack.back();
            ifStack.pop_back();
            program.push_back({ENDIF, ""});
            program[ifIndex].jump = program.size() - 1;
        }
        else if (keyword == "eq") program.push_back({EQ, ""});
        else {
            throw runtime_error("Unknown instruction: " + keyword);
        }
    }

    return program;
}

#include <fstream>

// --- Entry Point ---
int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <sourcefile>" << endl;
        return 1;
    }

    string filename = argv[1];
    ifstream file(filename);
    if (!file) {
        cerr << "Error: could not open file " << filename << endl;
        return 1;
    }

    // Read the whole file into a string
    string programText((istreambuf_iterator<char>(file)),
                       istreambuf_iterator<char>());

    try {
        vector<Instruction> program = parseProgram(programText);
        VM vm(program);
        vm.run();
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
