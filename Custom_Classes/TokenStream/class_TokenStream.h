
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
    void open_or_close_file_with_end();
    
    Token set_Token_type(const Token &buffer);

    ifstream _file_for_input;
    
    Settings *Main_settings;

};

void check_error_and_close_file(ifstream &_file_for_input, Settings &Main_settings);
