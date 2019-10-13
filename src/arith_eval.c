/*
 * ARITHMETIC EVALUATION LIBRARY
 *  A library to evaluate simple expressions,
 *  designed to work with static memory microcontrollers.
 * 
 * Author: Ethan Joyce
 * Date: October, 2019
 * Copyright: GPLv3.0 (license.txt)
 */

#include "arith_eval_config.h"
#include <arith_eval.h>
#include <string.h>
#include <math.h>
#include <stdio.h>


int main() {
    printf("%lf\n", evaluate_expression((const char *) "100+99*2\0"));
    return 0;
}

double evaluate_expression(const char *expression) {
    double total_value = 0;
    
    int current_point = 0;
    do {
        if (expression[current_point] == '\0') // Check for null terminator
            break;

        if (current_point == 0) {
            struct parse_results first_operand = parse_string(expression, current_point);
            if (first_operand.type == OPERATION)
                return -1; // Error: no number given for initial operand

            current_point = first_operand.end_point;

            total_value = first_operand.operand;
        }

        struct parse_results operator = parse_string(expression, current_point);
        
        if (operator.type != OPERATION)
            return -2; // Error with parsing

        current_point = operator.end_point;

        struct parse_results second_operand = parse_string(expression, current_point);
        if (second_operand.type != OPERAND)
            return -3; // Error: no number given for operand
        
        current_point = second_operand.end_point;

        //printf("Second operand: %d\n", operator.operand);


        if (operator.operation == ADD)
            total_value += second_operand.operand;
        else if (operator.operation == SUBTRACT)
            total_value -= second_operand.operand;
        else if (operator.operation == MULTIPLY)
            total_value *= second_operand.operand;
        else if (operator.operation == DIVIDE)
            total_value /= second_operand.operand;
        
        printf("Totalval: %f\n", total_value);
    }
    while (current_point < strlen(expression) - 1);

    return total_value;
}

struct parse_results parse_string(const char *expression, int startPos) {
    printf("startPos: %d\n", startPos);
    
    struct parse_results results = {  };
    
    char c = expression[startPos];
    //printf("startPos: %d\n", startPos);

    if (c == '+') {
        results.type = OPERATION;
        results.operation = ADD;
        results.end_point = startPos + 1;
        return results;
    }
    else if (c == '-') {
        results.type = OPERATION;
        results.operation = SUBTRACT;
        results.end_point = startPos + 1;
        return results;
    }
    else if (c == '*') {
        results.type = OPERATION;
        results.operation = MULTIPLY;
        results.end_point = startPos + 1;
        return results;
    }
    else if (c == '/') {
        results.type = OPERATION;
        results.operation = DIVIDE;
        results.end_point = startPos + 1;
        return results;
    }
    else {
        int number = 0;
        int digits[8];
        int digitsLen = 0;

        int i = 0;
        do {
            c = expression[startPos + i];
            c -= '0'; // Convert to integer value

            if (c <= 9 && c >= 0) { // Check that it's a num
                digits[i] = (int) c;
                digitsLen++;
            }
            else
                break;            
        }
        while (++i);

        for (int i = digitsLen - 1; i >= 0; i--) { // End to beginning
            number += digits[i] * pow((double) 10, (double) digitsLen - 1 - i);
        }

        results.type = OPERAND;
        results.operand = number;
        results.end_point = startPos + digitsLen;

        return results;
    }
}
