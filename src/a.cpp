#include <iostream>
#include <fstream>
#include <string>

int main( void ) {
    for (int i = 4; i <= 25; i++) {
        std::string filename;
        if (i < 10) {
            filename = "./0" + std::to_string(i) + "_2" + ".cpp";
        }
        else
            filename = "./" + std::to_string(i) + "_2" + ".cpp";
        std::ofstream file(filename);
        if (file.is_open()) {            
            if (i < 10)
                file << "#define path \"../res/input0" << i << ".txt\"" << std::endl;
            else
                file << "#define path \"../res/input" << i << ".txt\"" << std::endl;
            file << "#include \"utils.h\"" << std::endl;
            file << std::endl;
            file << "int main( void ) {" << std::endl;
            file << "   return 0;" << std::endl;
            file << "}" << std::endl;
            file.close();
        } else {
            std::cout << "Failed to create file: " << filename << std::endl;
        }
    }
    return 0;
}