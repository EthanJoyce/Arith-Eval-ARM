/*
 * ARITHMETIC EVALUATION LIBRARY
 * 
 * Author: Ethan Joyce
 * Date: October, 2019
 * Copyright: GPLv3.0 (license.txt)
 */

/*
 *  Takes an arithmetic expression, in the form of a string,
 * parses it, and returns the arithmetic evaluation evaluated
 * simply from left to right (no operation precedence). Numbers
 * must be positive, up to two digits.
 * 
 * Supported operations: +, -, *, /
 */
double evaluate_expression (const char *expression);

// Defines what type of result was parsed
enum parse_result_type { OPERAND, OPERATION };
// Defines what operation was given
enum operation_type { ADD, SUBTRACT, MULTIPLY, DIVIDE };

// Contains the results of the parsing
struct parse_results {
    enum parse_result_type type;
    enum operation_type operation;
    int operand;
    int end_point;
};

struct parse_results parse_string(const char *expression, int startPos);