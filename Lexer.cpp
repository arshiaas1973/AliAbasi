#include "Lexer.h"
#include "mylib.h"
#include "ErrorHandling.h"
#include "Compilation.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <unicode/unistr.h>
#include <unicode/ustream.h>
#include <unicode/locid.h>

Lexer::Lexer(std::string source, std::string output){
    std::string line;
    std::ifstream file;
    std::string final = "";
    bool look_for_num_loop = false;
    bool look_for_begin_loop = false;
    bool look_for_end_loop = false;
    int loop_in_loop_num = 0;
    int current_loop_in = 0;
    std::vector<int> loop_times;
    std::vector<std::vector<std::string>> loop_commands = {};

    int char_pos = 0;
    int line_num = 0;

    file.open(source);
    if (file.is_open())
    {
        while (getline(file,line))
        {
            line_num++;

            std::vector<std::string> words = mylib::Split(line,' ');
            for (int i = 0; i < words.size(); i++)
            {
               icu::UnicodeString word( words[i].c_str(), "UTF-8" );
               if(look_for_num_loop){
                    if(mylib::isNumeric(words[i])){
                        loop_times.insert(loop_times.end(),stoi(words[i]));
                        icu::UnicodeString word_for_begining( words[i+1].c_str(), "UTF-8" );
                        if((i+1)<words.size()){
                            if(word_for_begining.toLower("en_US")=="begin"){
                                look_for_end_loop = true;
                                loop_commands.insert(loop_commands.begin(),new std::vector<std::string>());
                            }else{
                                if(!look_for_end_loop){
                                    std::string msg = "You should put 'BEGIN' after times of repeating (example: 'REPEAT 3 BEGIN ALI END'). line "+std::to_string(line_num)+", word "+std::to_string(i+2)+".";
                                    ErrorHandling(msg,7,ERROR);
                                }else{
                                    std::string msg = "When you are defining a loop inside another loop, You should put 'BEGIN' before times of repeating (example: 'REPEAT BEGIN 3 ALI END'). line "+std::to_string(line_num)+", word "+std::to_string(i+2)+".";
                                    ErrorHandling(msg,7,ERROR);
                                }
                            }
                        }else{
                            look_for_begin_loop = true;
                        }
                    }else{
                        std::string msg = "Can't find how many time the text is going to be repeated. line "+std::to_string(line_num)+", word "+std::to_string(i+1)+".";
                        ErrorHandling(msg,6,ERROR);
                    }
                    look_for_num_loop = false;
               }else if(look_for_begin_loop){
                    if(word.toLower("en_US")=="begin"){
                        // THIS MAY CAUSE PROBLEM OR ERROR
                        if(look_for_end_loop)
                            loop_times.insert(loop_times.end(),stoi(words[i+1]));

                        look_for_end_loop = true;

                    }else{
                        if(!look_for_end_loop){
                            std::string msg = "You should put 'BEGIN' after times of repeating (example: 'REPEAT 3 BEGIN ALI END'). line "+std::to_string(line_num)+", word "+std::to_string(i+2)+".";
                            ErrorHandling(msg,7,ERROR);
                        }else{
                            std::string msg = "When you are defining a loop inside another loop, You should put 'BEGIN' before times of repeating (example: 'REPEAT BEGIN 3 ALI END'). line "+std::to_string(line_num)+", word "+std::to_string(i+2)+".";
                            ErrorHandling(msg,7,ERROR);
                        }
                    }
                    look_for_begin_loop = false;
               }else if(look_for_end_loop){
                    if(word.toLower("en_US")=="end"){

                    }else if(word.toLower("en_US")=="repeat"){

                        loop_in_loop_num++;
                        look_for_begin_loop = true;
                        current_loop_in++;
                    }else{
                        loop_commands[current_loop_in].insert(loop_commands[current_loop_in].end(),word);
                    }
               }else if(word.toLower("en_US") == "ali"){
                    if (char_pos>0)
                    {
                        char_pos--;
                    }else{
                        char_pos = 127;
                    }
               }else if(word.toLower("en_US") == "abasi"){
                    if (char_pos>0)
                    {
                        char_pos--;
                    }else{
                        char_pos = 0;
                    }
               }else if(word.toLower("en_US") == "sik"){
                    final += (char) char_pos;
               }else if(word.toLower("en_US").indexOf("repeat")==0){
                    if((i+1)<words.size()){
                        if(mylib::isNumeric(words[i+1])){
                            loop_times.insert(loop_times.end(),stoi(words[i+1]));
                            icu::UnicodeString word_for_begining( words[i+2].c_str(), "UTF-8" );
                            if((i+2)<words.size()){
                                if(word_for_begining.toLower("en_US")=="begin"){
                                    look_for_end_loop = true;
                                }else{
                                    if(!look_for_end_loop){
                                        std::string msg = "You should put 'BEGIN' after times of repeating (example: 'REPEAT 3 BEGIN ALI END'). line "+std::to_string(line_num)+", word "+std::to_string(i+2)+".";
                                        ErrorHandling(msg,7,ERROR);
                                    }else{
                                        std::string msg = "When you are defining a loop inside another loop, You should put 'BEGIN' before times of repeating (example: 'REPEAT BEGIN 3 ALI END'). line "+std::to_string(line_num)+", word "+std::to_string(i+2)+".";
                                        ErrorHandling(msg,7,ERROR);
                                    }
                                }
                            }else{
                                look_for_begin_loop = true;
                            }
                        }else{
                            std::string msg = "Can't find how many time the text is going to be repeated. line "+std::to_string(line_num)+", word "+std::to_string(i+1)+".";
                            ErrorHandling(msg,6,ERROR);
                        }
                    }else{
                        look_for_num_loop = true;
                    }
                    // final += "repeat";
               }else{
                    std::string msg = "Can't understand what does '"+words[i]+"' mean. line "+std::to_string(line_num)+", word "+std::to_string(i)+".";
                    ErrorHandling(msg,8,ERROR);
               }
            }

        }
    }
    file.close();

    std::cout << final << std::endl;

    Compilation::Compile(final,output);
}
