
#define NOT_ARCHIVED_THIS_EXCEPTION false
#define NOT_ARCHIVED_MESSAGE_OF_END_FILE true
#define NOT_ARCHIVED_ERROR_INPUT_OF_END_FILE true

#define PRINT_RESULT ": "
#define PROMT ">> "

BETTER_ENUM(
    Type_lexeme, 
    char,     
    number = 'n',
    word = 'w',
    constante = 'c',
    key_word = 'k',
    varriable = 'v',
    function = 'f',
    
    equality = '=',
    minus = '-', 
    plus = '+',
    multiple = '*',
    drobbe = '/', 
    left_bracket = '(',
    right_bracket = ')', 
    mod = '^', 
    comma = ',',

    exit_simbol = 'q',
    help = '?',
    settings = 's',
    print = ';');

enum Modes_calculating {

    arabian = 'a',
    roman = 'r'

};
enum Modes_input {

    console = 'c',
    file = 'f'

};
enum Modes_output {

    to_console = 'c',
    to_file = 'f',
    to_console_and_file = 'a'

};
enum Modes_output_with_file {

    on_to_file = 'f',
    on_to_console_and_file = 'a'

};

const map <string, double> constantes = {

    {"pi", 3.14159265}, 
    {"e", 2.71828}

};
const set <string> key_vords = {

    "var",
    "from_file",
    "clear"

};
const set <string> mathematic_functions = {

    "cos", 
    "sin", 
    "tan", 
    "asin", 
    "acos", 
    "atan", 
    "sqrt", 
    "abs", 
    "ln", 
    "log", 
    "ceil", 
    "floor", 
    "fmod"

};
