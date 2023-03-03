
#include <iostream>
#include <fstream>
#include "ErrorHandling.h"
#include "Lexer.h"

template<class T>
T base_name(T const & path, T const & delims = "/\\")
{
  return path.substr(path.find_last_of(delims) + 1);
}
template<class T>
T remove_extension(T const & filename)
{
  typename T::size_type const p(filename.find_last_of('.'));
  return p > 0 && p != T::npos ? filename.substr(0, p) : filename;
}

int main(int argc, char *argv[]){
    bool debug = false;
    std::string source = "" , output = "", platform = "";

    if(argc <=1){
            std::cout << "        aliabasi [OPTIONS] file" << std::endl;
            std::cout << "            OR" << std::endl;
            std::cout << "        aliabasi [FILE OPTIONS] [OPTIONS]" << std::endl;
            std::cout << "" << std::endl;
            std::cout << "        (FILE OPTIONS) =>" << std::endl;
            std::cout << "            -s, --source        The source file that is going to be compiled." << std::endl;
            std::cout << "            -o, --output        The output file that is going to be executed." << std::endl;
            std::cout << "" << std::endl;
            std::cout << "        (OPTIONS) =>" << std::endl;
            std::cout << "            -h, --help          Help you to know what are the options and how to run the program." << std::endl;
            std::cout << "                                You may already know it!!" << std::endl;
            std::cout << "            -d, --debug         Show what program gets as variable." << std::endl;
            std::cout << "" << std::endl;
            std::cout << "Thats all for now!!" << std::endl;
            return 0;
    }else{
        for (size_t i = 1; i < argc; i++)
        {
            std::string arg = argv[i];
                if (arg.compare("-h")==0 || arg.compare("--help")==0)
                {
                    std::cout << "        aliabasi [OPTIONS] file" << std::endl;
                    std::cout << "            OR" << std::endl;
                    std::cout << "        aliabasi [FILE OPTIONS] [OPTIONS]" << std::endl;
                    std::cout << "" << std::endl;
                    std::cout << "        (FILE OPTIONS) =>" << std::endl;
                    std::cout << "            -s, --source        The source file that is going to be compiled." << std::endl;
                    std::cout << "            -o, --output        The output file that is going to be executed." << std::endl;
                    std::cout << "" << std::endl;
                    std::cout << "        (OPTIONS) =>" << std::endl;
                    std::cout << "            -h, --help          Help you to know what are the options and how to run the program." << std::endl;
                    std::cout << "                                You may already know it!!" << std::endl;
                    std::cout << "            -d, --debug         Show what program gets as variable." << std::endl;
                    std::cout << "" << std::endl;
                    std::cout << "Thats all for now!!" << std::endl;
                    return 0;
                }else if(arg.compare("-s")==0 || arg.compare("--source")==0){
                    if(i+2 <= argc){
                        source = argv[i+1];
                        i+=1;
                    }else{
                        ErrorHandling("You have to enter the file for the source.",0,ERROR);
                    }
                }else if(arg.compare("-o")==0 || arg.compare("--output")==0){
                    if(i+2 <= argc){
                        output = argv[i+1];
                        i+=1;
                    }else{
                        ErrorHandling("You have to enter the file for the output.",1,ERROR);
                    }
                }else if(arg.compare("-d")==0 || arg.compare("--debug")==0){
                    debug = true;
                }else{
                    if(source == ""){
                        source = argv[i];
                    }else{
                        if(output == ""){
                            output = argv[i];
                        }else{
                            ErrorHandling("The is no such a OPTION called '"+arg+"'",2,ERROR);
                        }
                    }
                }
        }
    }

    if(source == "")
        ErrorHandling("You haven't entered the source file",3,ERROR);

    #ifdef _WIN32
        platform = "win32"
        if(output=="") output = remove_extension(base_name(source))+".exe";
    #elif _WIN64
        platform = "win64"
        if(output=="") output = remove_extension(base_name(source))+".exe";
    #elif __linux__
        platform = "linux";
        if(output=="")  output = remove_extension(base_name(source));
    #elif __unix
        platform = "unix";
        if(output=="")  output = remove_extension(base_name(source));
    #elif __APPLE__
        platform = "mac";
        if(output=="")  output = remove_extension(base_name(source));
    #elif __FreeBSD__
        platform = "freebsd";
        if(output=="")  output = remove_extension(base_name(source));
    #endif // 0

    // Debug main variables.
    if(debug){
        std::cout << "Source: '" << source << "'" << std::endl;
        std::cout << "Output: '" << output << "'" << std::endl;
        std::cout << "Platform: '" << platform << "'" << std::endl;
    }

    std::ifstream file;
    file.open(source);
    if (!file)
    {
        if(platform == "linux" || platform == "unix")
            ErrorHandling("'"+source+"' file doesn't exist. \n\tThere is a chance that you haven't give this program or your user the permission to view the file or edit it. \n\tIf so, You can run 'sudo chmod 777 "+source+"' or 'chmod 777 "+source+"'. \nHope it works.",4,ERROR);
        else
            ErrorHandling("'"+source+"' file doesn't exist.",4,ERROR);
    }else
        if(file.is_open())
            file.close();

    Lexer *l = new Lexer(source,output);
}
