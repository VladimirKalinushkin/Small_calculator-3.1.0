
class TokenStream {

public:

    TokenStream( const map <string, double> &constantes,
                 const set <string> &key_vords,
                 const set <string> &mathematic_functions,
                 Settings &settings
                );

    Token get();
    void putback(Token buffer);

    void clear();

    void inicialise_Varriable(const string &s, const double &value);
    void set_Varriable(const string &s, const double &value);

private:
    
    void inicialiseStream(  const map <string, double> &constantes, 
                            const set <string> &key_vords, 
                            const set <string> &mathematic_functions
                          );

    vector <Token> Stream;

    vector <Token> ConstantesStream;
    vector <Token> KeyWordsStream;
    vector <Token> FunctionsNameStream;
    vector <Token> VarriablesStream;

    Token get_new_Token();
    Token read_Token(istream &is);
    Token read_number(istream &is, const char &first_digit);
    Token read_word(istream& is, const char &first_simbol);

    void open_or_close_file_with_end();
    
    Token set_Token_type(const Token &buffer);

    ifstream _file_for_input;

    // Файл создан внутри класса потока для "удобного" контроля его жизненного цикла
    
    Settings *Main_settings;

    // Я привязал Настройки указателем к потоку, потому что они "жизненно необходимы"
    // для работы потока.
    // Поэтому стоит исключить возможность, чтобы настройки были созданы после потока
};

void check_error_and_close_file(ifstream &_file_for_input, Settings &Main_settings);
