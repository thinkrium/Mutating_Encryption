#include <sstream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <bitset>

using namespace std;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   encryption.h
 * Author: thomedy
 *
 * Created on April 14, 2017, 10:18 PM
 */

#ifndef ENCRYPTION_H
#define ENCRYPTION_H

namespace oortius {
    class encryption {
        private: 
 
            string source_file_path;
            string target_file_path;
            string source_file_name;
            string target_file_name;

            fstream file_reader;
            fstream junk_file;
        
            int equation_number [1000];

            int bit_gap;

            char op [4];
        
            string equations[10][5]; 
        
            int key_value;
        
    public: 

        encryption();
        //set source_file_path
        //parameter string representing the location of the source file path
        // sets the source file path
        //return void
        void set_source_file_path(string sourceFilePath);
        //set target_file_path
        //parameter string representing the location of the target file path
        // sets the target file path
        //return void
        void set_target_file_path(string targetFilePath);
        //get source file path
        // takes in no parameter 
        // returns the source file path
        string get_source_file_path();
        //get target file path
        // parameter takes no parmeter
        //returns the target file path
        string get_target_file_path();
        //set_file
        //parameter string file path which defaults to null
        //set the junk file path to the parameter input
        //return void
        void set_source_file_name(string fileName);
        //set_file
        //parameter string file path which defaults to null
        //set the junk file path to the parameter input
        //return void
        void set_target_file_name(string fileName);
        //read_file
        //sets the file content to a file content to a variable
        void read_file();
        //parse_file
        //takes an existing file name and parses it
        int parse_file_text();
        //create_seperate_file
        //uses the key value and opens a new file which the garbage 
        //goes into
        //returns the newly opened file
        void create_seperate_file();
        //set key value
        //runs every time and sets the key value
        void set_key_value(int keyValue);        
        //get key_value
        //runs every time and gets the key value
        int get_key_value();        
        //populate_calculator_arrays
        //takes the existing array of integers
        void populate_calculator_num_arrays();
        //populate_calculator_arrays
        //takes the existing array of chars
        void populate_calculator_op_arrays();
        //create algorithm uses the existing arrays to create the algorithm
        void create_algorithm();
        //close_file_streamschar
        //takes the previous file streams and closes them at the end
        //if it doesn't close then it returns 2
        int close_file_streams();
        //get_equations takes in 2 parameters, the element index and equation index
        //returns the equations;
        string get_equation(int equation_index, int equation_element);
        //set_bit_gap
        //takes int bitGap as parameter
        //sets the bit gap internally
        void set_bit_gap(int bitGap);
        //encrypt_file
        //takes fileContent char
        //flips the bit for each bit gap
        //returns encrypted file content
        char encrypt_file(char * fileContent);
        //get_encryption_object
        //returns encryption_object
        //takes no parameters
        encryption* get_encryption_object();
        //destructor
        //closes out the memory management
        ~encryption();        
    };    
};


#endif /* ENCRYPTION_H */

