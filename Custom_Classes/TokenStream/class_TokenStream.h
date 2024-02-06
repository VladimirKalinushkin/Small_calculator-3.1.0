
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
    ifstream _file_for_input;
    // Файл создан внутри класса потока для "удобного" контроля его жизненного цикла
    
    Settings *Main_settings;
    // Я привязал Настройки указателем к потоку, потому что они "жизненно необходимы"
    // для работы потока.
    // Поэтому стоит исключить возможность, чтобы настройки были созданы после потока

    vector <Token> ConstantesStream;
    vector <Token> KeyWordsStream;
    vector <Token> FunctionsNameStream;
    vector <Token> VarriablesStream;


    Token set_Token_type(const Token &buffer);

    Token get_new_Token();
    Token read_Token(istream &is);
    Token read_number(istream &is, const char &first_digit);
    Token read_word(istream& is, const char &first_simbol);


    Token read_Token_from_file();
    void open_file_for_input();
    void close_file_for_input_with_end();
    void get_message_of_errors_file_for_input(); // В том числе и ошибки конца файла
    
};

