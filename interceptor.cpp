#include <algorithm>
#include <iostream>
#include "stdio.h"
#include "stdlib.h"
#include <list>
#include <string>
#include <map>
#include <ctype.h>
#include <fstream>

using namespace std;
int debug = 0;
enum class_type  { IDENTIFIER, KEYWORD, INTEGER, OPERATOR, STAR, WHITESPACE, POINTER, MISCELLANEOUS }; // This is the class of elements seen
int num_classes = 8;

// Token class maps each lexeme to its corresponding type
class token {
public:
  string lexeme;
  class_type type;
  void set (string s, class_type c){
    this->lexeme = s;
    this->type = c;
  }
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
  ",", "=", "?", ":", "||", "&&", "|", "^", "==", "!=", "<",">", "<=", ">=", "<<", ">>", "+", "-", "%", "/", "~", "!", "&", ".", "(", ")", "{", "}", "[", "]", "->"
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

// 'has_token_finished' checks the two characters c1, c2 and decides whether the token represented by c1 and its preceeding (if any) characters has ended because of char c2
bool has_token_finished (char c1, char c2){
  int count; // Temporary local variable
  // Checking for all the operators which have count > 2
  for (count = 0; count < num_operators; count++){
    if (operators[count].length() == 2 && c1 == operators[count][0] && c2 == operators[count][1])
	return true;
   }
  // If any of the characters is a delimiter then we break the current token
  for (count = 0; count < length_delimiters; count++){
    if (c2 == delimiters [count] || c1 == delimiters [count])
      return true;
   }
  if (c1 != c2 && (c1 == '*' || c2 == '*'))
    return true;
  return false;
}

// This function checks whether the given str is a C keyword 
bool is_keyword (string str){
  int count;
  for (count = 0; count < num_keywords; count++){
    if (str.compare (keywords[count]) == 0)
	return true;
  }
    return false;
}

// This function returns the class type of a given token string 
class_type get_class_type (string token){
  if (token.size()==0)
    return MISCELLANEOUS;
  if (isdigit(token[0])) // We have assumed that our tokens for numbers have only integers in them
    return INTEGER;
  if (is_keyword (token))
    return KEYWORD;
  if (isalpha(token[0])) // Tokens with alphabets which (other than keywords) are identifiers
    return IDENTIFIER;
  if (is_operator(token))
    return OPERATOR;
  if (token[0] == '*')
    return STAR; // STAR is identified as a special type of class 
  return MISCELLANEOUS;
}

// This function extracts all the tokens from the given buffer and returns a list <token objects> 
list <token> extract_tokens (string buffer){
  list <token> token_map; // This is the list of token objects from each line
  int count, token_start, length = buffer.length();
  token temp_token;
  string parent_token, current_token = "";
  bool temp_token_is_set = false;
  for (count = 0; count < length; count++, current_token="", temp_token_is_set = false){  // Start of a new token  
    while (buffer[count] == ' '){parent_token = ""; count++;}; // Skipping whitespaces
  while (count < length - 1){ // Checking whether count has exceeded the length of the buffer
    current_token.push_back(buffer[count]); // Keep appending the current character to the current token 
    if (has_token_finished(buffer[count], buffer[count+1])){
      	if ((count < length - 2) && (buffer[count + 1] == '-' && buffer[count + 2] == '>')){
     	  if (get_class_type(parent_token) == IDENTIFIER || get_class_type(parent_token) == POINTER){ // Case when dereferencing a pointer to a pointer 
	    parent_token.append ("->");
	    parent_token.append (current_token);
	    temp_token.set(parent_token, POINTER);
	    temp_token_is_set = true;
	  } else {
	    temp_token.set(current_token, POINTER);  
	    temp_token_is_set = true;
     	  }
	}
	//	count++;
	break;
    }
    count++;
  }
  if (count == length - 1)
    current_token.push_back(buffer[count]);
  if (!(temp_token_is_set))
    temp_token.set (current_token, get_class_type (current_token));
    token_map.push_back (temp_token);
      if (get_class_type(current_token) == IDENTIFIER)
       parent_token.assign(current_token);
}
  return token_map;
}

// This function checks whether the given string str exists in the list (lstr) of strings 
bool exists (string str, list <string> lstr){
  for (list<string>::iterator it = lstr.begin(); it != lstr.end(); it++){
    if (str.compare(*it) == 0)
      return true;
  }
  return false;
}

// Checks the order for an assignment to be pointer allocation (matches struct node * abc; type assignments) 
bool check_order (class_type c, int position){
  switch (position){
  case 1:
    return (c == KEYWORD);
  case 2:
    return (c == IDENTIFIER);
  case 3:
    return (c == STAR);
  case 4:
    return (c == IDENTIFIER);
  default: 
    return false;
  }
}

// function used to trim a string 
string trim (string str, string whitespace){
    int strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
      return ""; // no content
    int strEnd = str.find_last_not_of(whitespace);
    int strRange = strEnd - strBegin + 1;
    return str.substr(strBegin, strRange);
}

// This function is for debugging purposes
void debug_list (list <token> token_list){
  for (list<token>::iterator it = token_list.begin(); it != token_list.end(); it++){
    cout << it->lexeme << ",";
  } 
  cout << endl;
}  

// Function which parses the file and interceptors each memory access with an event to the runtime 
void parse_file(char *file_input, char *file_output){
  ifstream fs_in (file_input);
  if (!(fs_in.is_open())){
    cout << "Input File" << file_input << "could not be opened." << endl;
    return;
  }
  ofstream fs_out (file_output);
  fs_out << "#include \"memory_monitor.h\"" << endl;
  int count, len; // Temporary counter variables
  string buffer, temp_buffer; // The buffer in which each of the line is read 
  string token_str; // Temporary variable to store a token in 
  list <string> dynamic_objects; // We need to maintain a list of all the dynamic variables by their names
  list <token> token_list;   // Tokens from each line
  bool valid_dy_object = false; // Initially the no dynamic object has been seen, flag is set to false 
  while (getline(fs_in, buffer)){ // reading each line from the file , currently we assume each statement == each line
    //    buffer = trim (buffer, " \t"); // trimming the buffer
    // removing all the empty lines, lines that are pragmas, header inclusions, single line comments 
    len = buffer.size();
    if (len == 0 || buffer[0] == '#' || (len > 1 && buffer[0] == '/' && buffer[1] == '/')) {
      if (debug == 1)
	cout << "------------>>>> " << buffer << endl;
      fs_out << buffer << endl;
      continue;
    }

    // Need to filter out structs 
    if (buffer.compare(0, 6, "struct") == 0){
      size_t n = std::count(buffer.begin(), buffer.end(), '{');
      bool flag = (n > 0); // at least one { has been seen
      int count_p = n;
      while (count_p != 0 || !flag){
	fs_out << buffer << endl;
	n = std::count(buffer.begin(), buffer.end(), '}');
	count_p -= n;
	getline(fs_in, buffer);
	n = std::count(buffer.begin(), buffer.end(), '{');
	count_p += n;
	if (!flag)
	  flag = (n > 0) ;
      }
      continue;
    }

    // We also combine lines here 
    while (buffer[len-1] != ';' && buffer[len - 1] != '}' && buffer[len -1] != '{'){
      if (!getline(fs_in, temp_buffer))
	break;
      buffer.append(1, ' '); 
      buffer.append(temp_buffer);
      len = buffer.size();
    }
    if (debug)
     cout << "------------>>>> " << buffer << endl;
     fs_out << buffer << endl;
    // In each line we check whether all the identifiers and see if any of them are dynamic variables
    // Getting tokens from the current line and checking if they already exist as dynamic objects
    token_list = extract_tokens (buffer);
    if (debug == 1)
      debug_list(token_list); 
    // Check for two patterns currently <keyword, identifier (optional), *, identifier> then insert the token in the list of dynamic objects
    count = 0,valid_dy_object = false ; string dynamic_object_lexeme;
    for (list<token>::iterator it = token_list.begin(); it != token_list.end() && count < 4; it++){
      count++;
      if (count == 4)
	dynamic_object_lexeme = it->lexeme;
      valid_dy_object = check_order (it->type, count);
      if (!(valid_dy_object) && count == 2 && it->type == STAR){
	it++; 
	valid_dy_object = (it->type == IDENTIFIER); // Checking the case when (int * x) kind of an assignment occurs.
	dynamic_object_lexeme = it->lexeme;
	break;
      }
      if(!(valid_dy_object)) // If the check fails anywhere in between a pointer allocation has not been found
	break;
    }
    if (valid_dy_object){
      dynamic_objects.push_back(dynamic_object_lexeme);
      cout << dynamic_object_lexeme << endl;
    }
    for (list <token>::iterator it = token_list.begin(); it != token_list.end(); it++){
      token_str = it->lexeme;
      if (exists(token_str, dynamic_objects) || it->type == POINTER){
	if (debug)
	  cout << token_str << " is dynamic variable" << endl;
	fs_out << "access ((void *)"<< token_str << " ,1);" << endl;
      }
    }
  }
  fs_in.close ();
  fs_out.close ();
}

// The main function
int main(int argc, char** argv){
  if (argc < 3){  // the second argument (input file name must be passed as an argument)
    printf("Error!! Enter the file name to be parsed");
    return -1;
  }
  if (argc > 3)
    if (isdigit (argv[3][0]))
	debug = atoi (argv[3]);
  // Parse the file and annotate all memory accesses with events
   parse_file (argv[1], argv[2]);
  return 0;
}
