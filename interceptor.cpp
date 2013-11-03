#include <iostream>
#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include <list>
#include <string>
#include <map>
#include <ctype.h>

using namespace std;

enum class_type  { IDENTIFIER, INTEGER, OPERATOR, STAR, WHITESPACE, MISCELLANEOUS }; // This is the class of elements seen
int num_classes = 6;

// Token class maps each lexeme to its corresponding type
class token {
  public string lexeme;
  public class_type type;
};

// This is a list of all the keywords which are present in the C programming langauge
string keywords[] = {
  "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "int",
  "long", "register", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void" ,"volatile", "while"
};

// Total number of keywords in C
int num_keywords = 32;

// Reference: http://www.cs.mun.ca/~michael/c/op.html
string operators[] = {
  ",", "=", "?", ":", "||", "&&", "|", "^", "==", "!=", "<",">", "<=", ">=", "<<", ">>", "+", "-", "%", "/", "~", "!", "&", "->", ".", "(", ")", "{", "}", "[", "]"
};
// This is the total number of operators
int num_operators = 31;

// This function tests whether the given string is an operator or not 
bool is_operator (string str){
  int count;
  for (count = 0; count < num_operators; count++){
    if (str.compare(operators[count]) == 0){
      return true;
    }
  }
  return false;
}

// The set of all possible delimiters which cause a token to finish
char delimiters[] = {
  ' ', ',', '?', ':', '^', '%', '/', '~', '(', ')', '{', '}', '[', ']', ';', '+', '-', '=', '!', '&', '<', '>', '.', '!'
};

// The total number of such delimiters 
int length_delimiters = sizeof (delimiters) / sizeof (char);

bool has_token_finished (char c1, char c2){
  int count;
  // Checking for all the operators which have count > 2
  for (count = 0; count < num_operators; count++){
    if (operators[count].length() == 2 && c1 == operators[count][0] && c2 == operators[count][1])
	return true;
   }
  // If the second character is any of the delimiters then we break the current token
  for (count = 0; count < length_delimiters; count++){
    if (c2 == delimiters [count])
      return true;
   }
}

// This function checks whether the given str is a C keyword 
bool is_keyword (string str){
  int count;
  for (count = 0; count < num_keywords; count++){
    if (str.compare (keywords[count] == 0))
	return true;
  }
    return false;
}

// This function returns the class type of a given token string 
class_type get_class_type (string token){
  if (isdigit(token[0])) // We have assumed that our tokens for numbers have only integers in them
    return class_type.INTEGER;
  if (is_keyword (token))
    return class_type.KEYWORD;
  if (isalpha(token[0])) // Tokens with alphabets which (other than keywords) are identifiers
    return class_type.IDENTIFIER;
  if (is_operator(token))
    return class_type.OPERATOR;
  if (token[0] == '*')
    return class_type.STAR;
  return class_type.MISCELLANEOUS;
}

// This function extracts all the tokens from the given buffer and returns a list <tokens> 
list <string> extract_tokens (string buffer){
  list <string> token_list;
  string current_token;
  int count, token_size = 0, token_start, length = buffer.length();
  for (count = 0; count < length; count++){
    while (buffer[count] == ' '){
      count++;
    }
    token_start = count; // index within the buffer where the token starts 
    // Start of a new token  
    current_token = '';
    while ((count < length) && !has_token_finished(buffer[count], buffer[count+1])){
      current_token.push_back (buffer[count]);
    }
    token_list.push_back (current_token);
  }
}

// Searches for pointer (denoted by at least a single *) within the buffer. It returns -1 if no pointer has been found, else returns the value of the position where a star has been found 
int find_pointer(char *buffer){
  list <class_type> token_classes;
  int count = 0, len = strlen (buffer);
  bool pointer_found = false;
  char ch, next_ch, pointer_location = -1; 
  int classes[max_classes_per_line];
  while (count < len){
    
    

    if (ch == '*') { // seems like there is a pointer, there are two false positives 1) it could be a product literal 2)it could be part of a comment
      pointer_location = count; // tentative location of the pointer 
      // If it is a product literal surely there has to be a variable after it 
      while (count < len){
	next_ch = buf[++count];
	if (is_alpha (next_ch)){ // Keep iterating over the next symbols 
	  
	}
      }
    }
    count++;
  }
  return (pointer_found ? pointer_location : -1);
} 

// This function checks whether the given string str exists in the list (lstr) of strings 
bool exists (list <string> lstr, string str){
  for (list<string>::iterator it = lstr.begin(); it != lstr.end(); it++){
    if (str.compare(*it) == 0)
      return true;
  }
  return false;
}

// Function which maps a list of classes to its tokens
list <class_type> 

// Function which parses the file and interceptors each memory access with an event to the runtime 
void parse_file (fstream fs_in, fstream fs_out){
  int count;
  string buffer; // The buffer in which each of the line is read 
  string token; // Temporary variable to store a token in 
  list <string> dynamic_objects; // We need to maintain a list of all the dynamic variables by their names
  list <token> tokens;   // Tokens from each line
  list <class_type> token_classes; // This is a list of all the classes which correspond to each token 
  while (getline(fs_in, buffer)){ // reading each line from the file , currently we assume each statement == each line
    // removing all the empty lines, lines that are pragmas, header inclusions, single line comments 
    if (strlen (buffer) == 0 || buffer[0] == '#' || (buffer[0] = '/' && buffer[1] = '/')) 
      continue();
    // In each line we check whether all the identifiers and see if any of them are dynamic variables
    // Getting tokens from the current line and checking if they already exist as dynamic objects
    tokens = extract_tokens (buffer);
    // Check for two patterns currently <keyword, identifier (optional), *, identifier> then insert the token in the list of dynamic objects
    token_classes = extract_token_classes (tokens);
    for (count = 0;  count < tokens.size(); count++){
      token = tokens[count];
      if (exists(token, dynamic_objects)){
	cout << token << " is dynamic variable" << endl;
      }
    }
  }
}

int main(int argc, char** argv){
  if (argc < 3){  // the second argument (input file name must be passed as an argument)
    printf("Error!! Enter the file name to be parsed");
    return -1;
  }
  // Opening the input file
  fstream fs_in (argv[1], fstream::in);
  // Annotated program is written to the output file  
  fstream fs_out (argv[2], fstream::out);
  // Parse the file to plugin all memory accesses with events 
  parse_file (fs_in, fs_out);
  // Closing the files
  fs_in.close();
  fs_out.close();
  return 0;
}
