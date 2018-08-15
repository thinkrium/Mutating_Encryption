#include <bitset>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "decryption.h"

using namespace std;
using namespace oortius;

//constructor
//does nothing
decryption::decryption() {

}


//set_bit_gap
//parameter : int bitGap
//sets the bit gap to the parameter  
//returns nothing;        
void decryption::set_bit_gap(int bitGap) {
    bit_gap = bitGap;
}

//set_junk_file_path
//parameter string fisourcele path which defaults to null
//set the junk file path to the parameter input
//return void
void decryption::set_source_file_path(string filePath) {
    if(filePath != "") {
        source_file_path = filePath;
    }    
    else {
        source_file_path = "";
    }
    
}
   

//set_target_file_path
//parameter string file path which defaults to null
//set the target file path to the parameter input
//return void
void decryption::set_target_file_path(string filePath) {
    if(filePath != "") {
        target_file_path = filePath;
    }       
    else {
        target_file_path = "";
    }
}

//get_target_file_path
//parameter: none;
//returns the source_file_path
string decryption::get_source_file_path()  {
    return source_file_path;
}
   
//get_target_file_path
//parameter: none;
//returns the source_file_path
string decryption::get_target_file_path()  {
    return target_file_path;
}
   
// parameter: takes in file name
// sets the object file name to the parameter
//return : void;
void decryption::set_source_file_name(string fileName) {
    
    source_file_name = fileName;
};

// parameter: takes in file name
// sets the object file name to the parameter
//return : void;
void decryption::set_target_file_name(string fileName, int index, string imageExists) {

    if(imageExists == "false") {
         stringstream index_stream;
    
         index_stream << fileName << index;
    
         string file_name_with_index;
    
         index_stream >>  file_name_with_index;
    
         target_file_name = file_name_with_index;
    }
    else {
        target_file_name = fileName;
    }
};

//just type the name of the file this decrypts the jnk file    
// manually adds the .jnk file
void decryption::open_source_file() {
    
    string absolute_path = source_file_path + source_file_name + ".jnk";
    
    junk_file.open(absolute_path.c_str(),  ios::binary | ios::in );
}
            
    
//encrypt_file
//parameter: charcter fileContent
//flips the bit for each bit gap
//returns encrypted character bits
char  decryption::decrypt_file(char * fileContent) {

    char incoming_content = (*fileContent);
    char  decrypted_content =  incoming_content ^ bit_gap;
    return decrypted_content;
}
    

//set_file_portion_size
//parameter: int filePortionSize)
//sets the file_portion_size 
//return void
void decryption::set_file_portion_size(int filePortionSize) {
    decrypted_file_portion_size = filePortionSize;
}
            
//get_file_portion_size
//parameter: none
//gets the file portion size
//return: integer file portion size
int decryption::get_file_portion_size() {
    return decrypted_file_portion_size;
}
            

    
// parse file
// parameter: none
// opens a temporary file which holds only bits and pieces of the encrypted content in the temporary
// decrypted state
// processes the file and reads back the content
// return : void
int decryption::parse_file_from_start_time(
                int currentIndex,
                int startCase, 
                int stopCase, 
                float fileLengthInSec,
                string is_image, 
                int fps,
                int bitDepth,
                int samplesPerSecond, 
                int channels
                ) {
    fstream temp_file;

    string temp_target_path = get_target_file_path();
    
    char * content = new char;
    char decrypted_content;
    int content_size = 1;   
    
    if(fileLengthInSec != -1) {

        string temp_file_name = temp_target_path + target_file_name + ".gud";
             
    
        temp_file.open(temp_file_name.c_str(), ios::out|ios::binary);
        
        int file_portion_size = stopCase - startCase;
        
        int processed_start_case = currentIndex  * file_portion_size;
        int processed_stop_case =  processed_start_case + file_portion_size;
        

        junk_file.seekg(0, ios::end);
        int fileSize = junk_file.tellg();
        int fileSizeStart = (( junk_file.tellg()  / fileLengthInSec)  * processed_start_case);
        int fileSizeEnd = ((junk_file.tellg()  / fileLengthInSec) * processed_stop_case);
        
        junk_file.seekg(fileSizeStart, ios::beg);

        if(junk_file.is_open()) {


            if(currentIndex > 1) {
                temp_file << 'I';
                temp_file << 'D';
                temp_file << '3';
            }
 
            
            while(!junk_file.eof()) {
                junk_file.read(content, content_size);
                decrypted_content = decrypt_file(content);
                temp_file.write(&decrypted_content, content_size);

                
                
                if(junk_file.tellg() >= fileSizeEnd) {                 
                    break;
                }
            }
        }
        else {
            delete [] content; 
            return 1;
        }
    }
    else {
        
        string temp_file_name = temp_target_path + target_file_name;
    
        temp_file.open(temp_file_name.c_str(), ios::out|ios::binary);
        
        junk_file.seekg(0, ios::end);

        int fileSize = junk_file.tellg();
 
        
        junk_file.seekg(0, ios::beg);

        if(junk_file.is_open()) {
            
            while(!junk_file.eof()) {

                junk_file.read(content, content_size);
                decrypted_content = decrypt_file(content);
                temp_file.write(&decrypted_content, content_size);
            }
        }
        else {
            delete [] content; 
            return 1;
        }
    
    }
    delete [] content;
    return 0;
}


// parse file
// parameter: none
// opens a temporary file which holds only bits and pieces of the encrypted content in the temporary
// decrypted state
// processes the file and reads back the content
// return : void
int decryption::parse_file_from_portion_size(
                int currentIndex,
                float fileLengthInSec,
                string is_image, 
                int fps,
                int bitDepth,
                int samplesPerSecond, 
                int channels
                
                ) {
    fstream temp_file;

    string temp_target_path = get_target_file_path();
    
    char * content = new char;
    char decrypted_content;
    int content_size = 1;   
    
    if(fileLengthInSec != -1) {


        string temp_file_name = temp_target_path + target_file_name + ".gud";
             
        temp_file.open(temp_file_name.c_str(), ios::out|ios::binary);
        
        int file_portion_size = get_file_portion_size();
        
        int processed_start_case = currentIndex  * file_portion_size;
        int processed_stop_case =  processed_start_case + file_portion_size;
        
        junk_file.seekg(0, ios::end);
        int fileSize = junk_file.tellg();
        int fileSizeStart = (( junk_file.tellg()  / fileLengthInSec)  * processed_start_case);
        int fileSizeEnd = ((junk_file.tellg()  / fileLengthInSec) * processed_stop_case);
        
        junk_file.seekg(fileSizeStart, ios::beg);

        if(junk_file.is_open()) {

            if(currentIndex > 0) {

                temp_file << 'I';
                temp_file << 'D';
                temp_file << '3';
            }
 
            
            while(!junk_file.eof()) {
                junk_file.read(content, content_size);
                decrypted_content = decrypt_file(content);
                temp_file.write(&decrypted_content, content_size);

                
                
                if(junk_file.tellg() >= fileSizeEnd) {                 
                    break;
                }
            }
        }
        else {
            delete [] content; 
            return 1;
        }
    }
    else {
        
        
        string temp_file_name = temp_target_path + target_file_name;
    
        temp_file.open(temp_file_name.c_str(), ios::out|ios::binary);
        
        junk_file.seekg(0, ios::end);

        int fileSize = junk_file.tellg();
 
        
        junk_file.seekg(0, ios::beg);

        if(junk_file.is_open()) {
            
            while(!junk_file.eof()) {

                junk_file.read(content, content_size);
                decrypted_content = decrypt_file(content);
                temp_file.write(&decrypted_content, content_size);
            }
        }
        else {
            delete [] content; 
            return 1;
        }
    
    }
    delete [] content;
    return 0;
}



//destructor
//manages memory
//closes the file stream junk_file
decryption::~decryption() {
    junk_file.close();
}
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

