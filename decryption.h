#include <bitset>
#include <fstream>

using namespace std;
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   decryption.h
 * Author: thomedy
 *
 * Created on April 23, 2017, 7:48 PM
 */

#ifndef DECRYPTION_H
#define DECRYPTION_H

namespace oortius {
    class decryption {
    
        private:
         
            fstream junk_file;
            int bit_gap;
            
            string source_file_path;
            string source_file_name;
            string target_file_name;
        
            string target_file_path;

            int decrypted_file_portion_size;
    public:    
            //constructor
            //does nothing
            decryption();
        
            //set_bit_gap
            //parameter : int bitGap
            //sets the bit gap to the parameter  
            //returns nothing;        
            void set_bit_gap(int bitGap);

            //set_source_file_path
            //parameter string file path which defaults to null
            //set the source file path to the parameter input
            //return void
            void set_source_file_path(string filePath);   

            //set_file   
            //takes in a file sets the path to that source file name
            void set_source_file_name(string file_name);
            
            //set_file   
            //takes in a file sets the path to that source file name
            void set_target_file_name(string file_name, int index, string imageExists);
            
            //set_target_file_path
            //parameter string file path which defaults to null
            //set the target file path to the parameter input
            //return void
            void set_target_file_path(string filePath); 
            
            //get_source_file_path
            //takes no parameters
            //returns the source file path
            string get_source_file_path();
            
            //get_target_file_path
            //takes no parameters
            //returns the target file path
            string get_target_file_path();
            
            
            //open_junk_file
            //parameter: none
            //opens the junk file for read 
            void open_source_file();

            //encrypt_file
            //takes fileContent char
            //flips the bit for each bit gap
            //returns encrypted file content
            char  decrypt_file(char  *fileContent);
            
            //set_file_portion_size
            //parameter: int filePortionSize
            //sets the file_portion_size 
            //return void
            void set_file_portion_size(int filePortionSize);
            
            //get_file_portion_size
            //parameter: none
            //gets the file portion size
            //return: integer file portion size
            int get_file_portion_size();
            
            //parse file
            //parameter: int start case , int stop case
            //processes the file and reads back the content
            //return : file open error
            int parse_file_from_start_time(
                           int currentIndex,
                           int startCase = 0,
                           int stopCase = 0,
                           float fileLengthInSec = 0, 
                           string is_image = "false", 
                           int fps = 30,
                           int bitDepth=16,
                           int samplesPerSecond = 44100,
                           int channels = 2
                           );

            //parse file
            //parameter: int start case , int stop case
            //processes the file and reads back the content
            //return : file open error
            int parse_file_from_portion_size(
                           int currentIndex,
                           float fileLengthInSec = 0, 
                           string is_image = "false", 
                           int fps = 30,
                           int bitDepth=16,
                           int samplesPerSecond = 44100,
                           int channels = 2 
                           );

            //destructor
            //closes the junk_file
            //manages memory
            ~decryption();
        
        
    };
};


#endif /* DECRYPTION_H */

