#include <bitset>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "encryption.h"

using namespace oortius;
using namespace std;
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

    //plain vanilla constructor does nothing but is needed
    encryption::encryption() {
      
    };
   
    // parameter: takes in file name
    // sets the object file name to the parameter
    //return : void;
    void encryption::set_source_file_name(string fileName) {
        source_file_name = fileName;
    };
    
    // parameter: takes in file name
    // sets the object file name to the parameter
    //return : void;
    void encryption::set_target_file_name(string fileName) {
        target_file_name = fileName;
    };
    
    //set source_file_path
    //parameter: string file path for the source file
    //return void
    void encryption::set_source_file_path(string sourceFilePath) {
        if(sourceFilePath != "") {
            source_file_path = sourceFilePath;
        }
        else {
            source_file_path = "";
        }
    } 
 
    
    //set source_file_path
    //parameter: string file path for the source file
    //return void
    void encryption::set_target_file_path(string targetFilePath) {
        if(targetFilePath != "") {
            target_file_path = targetFilePath;
        }
        else {
            target_file_path = targetFilePath;
        }
    } 
 
    
    //get source_file_path
    //parameter: string file path for the source file
    //return file path for source
    string encryption::get_source_file_path() {
        return source_file_path;
    } 
 
    
    //get source_file_path
    //parameter: string file path for the source file
    //return file path for target
    string encryption::get_target_file_path() {
       return target_file_path;
    } 
 
    // parameter: takes in nothing
    // opens the file and parses it into a variable to read
    //return : error code;
    int encryption::parse_file_text() {
        
        string source_file_path = get_source_file_path();
        string absolute_source_path = source_file_path + source_file_name; 
       
        file_reader.open(absolute_source_path.c_str(),  ios::binary | ios::in);
        
        char * content = new char;
        char encrypted_content;
        int content_size = 1;
        
        if(file_reader.is_open() && junk_file.is_open()) {

            
            while(!file_reader.eof()) {
                file_reader.read(content, content_size); 
                encrypted_content = encrypt_file(content);
                junk_file.write(&encrypted_content, content_size);
            }
        }
        else {
            delete[] content;
            return 1; // 1 = error file open failure
        }
        delete[] content;
        return 0;
    };

     
    void encryption::create_seperate_file() {
        string target_file_path = get_target_file_path();
        string junk_file_name = target_file_path + target_file_name + ".jnk";

        junk_file.open(junk_file_name.c_str(), ios::out | ios::binary);

    };
 
    //parameter : none
    // uses a time key that is seeded  for random and creates 
    // 10 seperate equations which are automated and randomized
    //return : void;
    void encryption::create_algorithm() {
       srand(key_value);
              
       stringstream el;
       string temp_element;
       char elem;       
       for(int equation_index = 0; equation_index < 10; equation_index++) {
           for(int equation_char_index = 0; equation_char_index < 5; equation_char_index++) {
               if(equation_char_index % 2 == 0) {
                   int index = abs(rand() % 999);
                   el << equation_number[index];
                   temp_element = el.str();
                   equations[equation_index][equation_char_index] = temp_element.c_str();
                   el.str(" ");
                   el.clear();
               }
               else {
                   equations[equation_index][equation_char_index] = op[abs(rand() % 4)];
               }
           }
       }
         
    };
    
    //parameter : none
    //populates a number array for use to create the equation;
    //return : void;
    void encryption::populate_calculator_num_arrays() {
        for(int index = 0; index < 1000; index++) {
            equation_number[index] = index;
        }
    };
    
    //parameter: none;
    //populates the operator array for equation creation
    //return : void;
    void encryption::populate_calculator_op_arrays() {
        op[0] = '+';
        op[1] = '-';
        op[2] = '*';
        op[3] = '/';
    };
    
    void encryption::read_file() {
    
    };
    
    //parameter:  number value to use as key
    //sets the key value
    //return : void
    void encryption::set_key_value(int keyValue) {
        key_value = keyValue;
    };
    
    
    //parameter:  none
    //gets the key value
    //return : integer key value
    int encryption::get_key_value() {
        return key_value;
    };
    
    //parameter: none;
    //closes the file streams for file access management
    //returns error code
    int encryption::close_file_streams() {
       junk_file.close();        
       file_reader.close();
       if(file_reader.is_open()) {
           return 2;
       }
       if(junk_file.is_open()) {
           return 2;
       }
       return 0;
    };
    
    //get equations 
    //parameter: int equation index, element index;
    //gets the equations;
    //return : string;
    string encryption::get_equation(int equation_index, int equation_element) {
        return equations[equation_index][equation_element];
    };
    
    //set_bit_gap
    //parameter: int bitGap
    //set the bit_gap to the parameter
    //return void
    void encryption::set_bit_gap(int bitGap) {
        bit_gap = bitGap;
    }

    //get_encryption_object
    //returns encryption_object
    //takes no parameters
    encryption* encryption::get_encryption_object() {
        return this;
    }
    
    //encrypt_file
    //parameter: charcter fileContent
    //flips the bit for each bit gap
    //returns encrypted character bits
    char encryption::encrypt_file(char * fileContent) {

        char encrypted_content;
        encrypted_content = (*fileContent) ^ bit_gap;
        return encrypted_content;
    }
    
    
    encryption::~encryption() {
    };
    