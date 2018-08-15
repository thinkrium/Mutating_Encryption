#include <ctime>
#include <string>
#include <deque>
#include <stdio.h>
#include <cstdlib>
#include "encryption.h"
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   calculator.h
 * Author: thomedy
 *
 * Created on April 17, 2017, 11:30 AM
 */

#ifndef CALCULATOR_H
#define CALCULATOR_H

namespace oortius {
    class calculator {
        private: 
          int current_time;
          int bit_gap;
          int equation_index;
          string equation[5];
          int order_of_importance;
          deque <int> numbers;
          deque <string> ops;
          deque <string> temp_operator;
          deque <int> temp_number;
    
    
          
        public:
            //constructor is empty and pointless
            calculator();
            //set_current_time sets up the current time and
            //takes in a current time parameter from outside
            void set_current_time(int currentTime);
            //choose_equation
            //uses the current time to randomize a seed
            // from there it automatically picks the equation
            void choose_equation();
            //set_equation
            //takes in a string parameter and pushes it into an 
            //equation
            void set_equation(encryption &obj);
            //pemdas
            //determines order of importance
            void pemdas();
            //process_equation
            //takes in a no parameters
            //works through the equation
            //processes the equation to the stack for processing
            void pre_process_equation();
            //process_equation
            //work through the vector stack to find the proper bitgap
            void process_equation();
            //get_bit_gap 
            //takes no parameter 
            //and returns the bit gap
            int get_bit_gap();
            //clears memory for memory management
            //destructor
            ~calculator();
    };
};


#endif /* CALCULATOR_H */

