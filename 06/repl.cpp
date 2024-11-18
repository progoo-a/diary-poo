#include <iostream>
#include <string>
#include <regex>
#include <vector> 
#include <unordered_map>

struct Type {
    std::string name;
    std::string type;
    std::size_t size;
    Type(std::string name, std::string type, std::size_t size) : 
        name(name), type(type), size(size) {}
};

struct Integer : public Type {
    int value;
    Integer(std::string name, int value) : 
        Type(name, "int", sizeof(int)), value(value) {}
};


int main() {
    std::unordered_map<std::string, Type*> variables;

    std::regex assignation("^([a-zA-Z0-9]+)\\s*=\\s*([0-9]+)$");
    std::regex display("^print\\s+([a-zA-Z0-9]+)$"); // Correction pour afficher la variable

    std::cout << ">";
    while (true) { 
        std::string cmd;
        std::getline(std::cin, cmd); 

        std::smatch match;        
        if (std::regex_match(cmd, match, assignation)) {
            // Création d'une nouvelle variable entière
            std::string name = match[1];
            int value = std::stoi(match[2]);
            if (variables.find(name) != variables.end()) {
                std::cout << "Variable " << name << " already exists" << std::endl;
            } else {
                Integer* integer = new Integer(name, value);
                variables[name] = integer;
            }
        } else if (std::regex_match(cmd, match, display)) {
            // Affichage de la variable
            std::string name = match[1];
            bool found = false;
            if (variables.find(name) != variables.end()) {
                Type* var = variables[name];
                if (var->type == "int") {
                    Integer* integer = static_cast<Integer*>(var);
                    std::cout << integer->value << std::endl;
                }
                found = true;
            }
            // for (Type* var : variables) {
            //     if (var->name == name) {
            //         found = true;
            //         if (var->type == "int") {
            //             Integer* integer = static_cast<Integer*>(var);
            //             std::cout << integer->value << std::endl;
            //         }
            //     }
            // }
            if (!found) {
                std::cout << "Variable " << name << " not found" << std::endl;
            }
        } else {
            std::cout << "Invalid command" << std::endl;
        }
        std::cout << ">";
    }
}
