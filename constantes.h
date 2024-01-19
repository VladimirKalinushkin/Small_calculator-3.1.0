
#define NOT_ARCHIVED_THIS_EXCEPTION false
#define NOT_ARCHIVED_MESSAGE_OF_END_FILE true
#define NOT_ARCHIVED_ERROR_INPUT_OF_END_FILE true

#define PRINT_RESULT ": "
#define PROMT ">> "

BETTER_ENUM(
    Type_lexeme, 
    char,     
    number = '1',
    Roman_int = '2',
    word = '3',
    constante = '4',
    key_word = '5',
    varriable = '6',
    function = '7',
    
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


// Тут и далее разные имена одинаковых по функциям значениям перечислений
// Обусловлены требования компилятора

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
