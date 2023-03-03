#include "Compilation.h"
#include "lib/sha256.h"
#include "ErrorHandling.h"
#include <filesystem>
#include <sys/stat.h>
#include <string>
#include <cstring>
#include <bits/stdc++.h>
#include <sys/types.h>


using namespace Compilation;

bool Compilation::Compile(std::string text, std::string output_file){
    std::string the_path = std::filesystem::current_path() / "tmp";
    const char* path = strcpy(new char[the_path.length() + 1], the_path.c_str());
    struct stat sb;
    std::string tmp_file_name = sha256(output_file)+".c";
    if((stat( path, &sb ) == 0)&&(sb.st_mode & S_IFDIR)){
        // std::cout << "exists" <<std::endl;
        makethefile:
            std::ofstream stream;
            std::string the_tmp_path = the_path+"/"+tmp_file_name;
            const char* tmp_path = strcpy(new char[the_tmp_path.length() + 1], the_tmp_path.c_str());
            stream.open(tmp_path);
            if(stream.is_open()){
                stream << "#include <iostream>\nint main(){std::cout << \""+text+"\" <<std::endl;}";
            }
            stream.close();
            std::string the_compile_txt = "g++ "+the_tmp_path+" -o "+output_file;
            const char* compile_txt = strcpy(new char[the_compile_txt.length() + 1], the_compile_txt.c_str());
            system(compile_txt);
            std::remove(tmp_path);
    }else{
        std::cout << "no" <<std::endl;

        if (mkdir(path, 0777) == -1)
            ErrorHandling("Could not create a temperory directory.",5,ERROR);
        else{
            // cout << "Directory created";
            goto makethefile;
        }
    }
    return true;
}
