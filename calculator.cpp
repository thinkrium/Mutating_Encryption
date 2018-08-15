#include <stdio.h>
#include <ctime>
#include <iostream>
#include <cmath>
#include <deque>
#include <string>
#include "calculator.h"
#include "encryption.h"
#include <sstream>
using namespace oortius;
using namespace std;
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

//constructor
//does nothing
calculator::calculator() {
    order_of_importance = 1;
};

//choose_equation
//parameter : none;
// uses randome to choose a main.cpp:126:23: error: no matching function for call to ‘oortius::calculator::set_equation()’random equation index
// sets the equation index to that number
void calculator::choose_equation() {
    equation_index = rand() % 9;
}

//set_current_time
//parameter: current time
//sets the current time to the number from encryption class
//return void
void calculator::set_current_time(int currentTime) {
    current_time = currentTime;
};

//pemdas
//parameter: none
//determines the order of importance
//return void;
void calculator::pemdas() {
   
}

//set_equation
//parameter: char pointerequationElement
//sets the equation
//return void
void calculator::set_equation(encryption &obj) {
    for(int index = 0; index < 5; index++) {
        equation[index] = obj.get_equation(equation_index, index);
    }
}

//pre_process_equation
//parameter: none
//processes the equation to the stack for processing
//return void
void calculator::pre_process_equation() {
    
    stringstream temp_element_string;
    int temp_element_number;
    
    for(int index = 0; index < 5; index++ ) { 
        if(index % 2 == 0) {
            temp_element_string << equation[index];
            temp_element_string >> temp_element_number;
            numbers.push_front(temp_element_number);
            temp_element_string.str("");
            temp_element_string.clear();
       
        }
        else {
            ops.push_front(equation[index]);
        }
        
    }   
};

//process equation
//parameter : none;
//works through the stack to find the proper bit gap
// return : void
void calculator::process_equation() {

    int left_number, right_number;
    while(!ops.empty() && order_of_importance == 1 ) {
        if(ops.back() == "*") {
            left_number = numbers.back();
            numbers.pop_back();
            right_number = numbers.back();
            numbers.pop_back();
            numbers.push_back(left_number * right_number);
            ops.pop_back();
        }
        else if(ops.back() == "/") {
            left_number = numbers.back();
            numbers.pop_back();
            right_number = numbers.back();
            numbers.pop_back();
            ops.pop_back();
            
            if(right_number != 0) {
                numbers.push_back(left_number / right_number);
            }
            else {
                right_number++;
                numbers.push_back(left_number / right_number);
            }
        }
        else {
            temp_operator.push_front(ops.back());
            ops.pop_back();
            temp_number.push_front(numbers.back());
            numbers.pop_back();
            
        }
        
    }
    while(!ops.empty() && order_of_importance == 2 ) {
        if(ops.back() == "+") {
            left_number = numbers.back();
            numbers.pop_back();
            right_number = numbers.back();
            numbers.pop_back();
            numbers.push_back(left_number + right_number);
            ops.pop_back();
        }
        else if(ops.back() == "-") {
            left_number = numbers.back();
            numbers.pop_back();
            right_number = numbers.back();
            numbers.pop_back();
            numbers.push_back(left_number - right_number);
            ops.pop_back();
        }
        else {
            temp_operator.push_front(ops.back());
            ops.pop_back();
            temp_number.push_front(numbers.back());
            numbers.pop_back();
        }
    }
    
    
    while(!temp_operator.empty()) {
        
        ops.push_back(temp_operator.front());
        temp_operator.pop_front();
        numbers.push_back(temp_number.front());
        temp_number.pop_front();
    }
    
    if(order_of_importance == 1) {
        order_of_importance++;
        process_equation();
    }
    else {
        bit_gap = numbers.back();
        numbers.pop_back();
    }
    
};

//get_bit_gap
//parameter: none
//gets the bitgap after processing the equation
//return integer bitgap
int calculator::get_bit_gap() {
    return bit_gap > 0 ? (abs(bit_gap) %  95 ) : 7;
}

//destructor: does nothing
calculator::~calculator() {
};