

#pragma once
#include "class_TokenStream.h"


TokenStream::TokenStream(   const map <string, double> &constantes, 
                            const set <string> &key_vords, 
                            const set <string> &mathematic_functions, 
                            Settings &settings) {

    inicialiseStream(constantes, key_vords, mathematic_functions);

    Main_settings = &settings;

}

void TokenStream::inicialiseStream( const map <string, double> &constantes, 
                                    const set <string> &key_vords, 
                                    const set <string> &mathematic_functions){

    for(auto c : constantes) {
        
        Token T(c.first, c.second);
        T.type = Type_lexeme::constante;
        ConstantesStream.push_back(T);
    }

    for(auto k : key_vords) {

        Token T(k);
        T.type = Type_lexeme::key_word;
        KeyWordsStream.push_back(T);
    }

    for(auto m : mathematic_functions) {

        Token T(m);
        T.type = Type_lexeme::function;
        ConstantesStream.push_back(T);
    }

}



Token TokenStream::get() {

    Token buffer;

    if(Stream.size()) {

        buffer = Stream.back();
        Stream.pop_back();
        return buffer;

    }
    else {

        buffer = get_new_Token();
        
        if (buffer.type == Type_lexeme::word)
            return set_Token_type(buffer);

        return buffer;

    }

}
void TokenStream::putback(Token buffer) {

    Stream.push_back(buffer);

}

void TokenStream::clear() {

    Stream.clear();

    if(Main_settings->get_mode_input() == Modes_input::file)
        clear_istream(_file_for_input);
    else
        clear_istream(cin);
}

void TokenStream::inicialise_Varriable(const string &s, const double &value){

    Token new_Varriable(s, value);
    new_Varriable.type = Type_lexeme::varriable;
    VarriablesStream.push_back(new_Varriable);

}
void TokenStream::set_Varriable(const string &s, const double &value) {

    for(int i = 0; i < VarriablesStream.size(); i++)
    {
        if(VarriablesStream[i].word == s)
        {
            VarriablesStream[i].value = value;
            return;
        }
    }

    throw MainException(("Неизвестная переменная!"));

}


Token TokenStream::set_Token_type(const Token &buffer) {

    string s = buffer.word;
    
    try {
    
        Roman_int r_i;
        Token ret;
        r_i.set(s);

        if(!r_i.empty()) {
            ret.word = s;
            ret.type = Type_lexeme::Roman_int;
            return ret;
        }
    }
    catch (Roman_int::Exception &ex) { ; }

    for(auto t : ConstantesStream)
        if(t.word == s)
            return t;
        
    for(auto t : KeyWordsStream)
        if(t.word == s)
            return t;
        
    for(auto t : FunctionsNameStream)
        if(t.word == s)
            return t;
    
    for(auto t : VarriablesStream)
        if(t.word == s)
            return t;
    
    return buffer;

}

Token TokenStream::get_new_Token() {

    if(Main_settings->get_mode_input() == Modes_input::console)
        return read_Token(cin);
         
    else if(Main_settings->get_mode_input() == Modes_input::file)
        return read_Token_from_file();

}
Token TokenStream::read_Token(istream &is) {

    Token ret;
    Type_lexeme type = Type_lexeme::_values()[0];
    //Требования для BETTER_ENUM

    is >> ret.type;

    //Будьте внимательны: порядок считывания лексемы важен!
    //Типы лексем могут быть числами, поэтому считывание числа должно быть в первую очередь!

    if (isdigit(ret.type))
        return read_number(is, ret.type);

    else if ( isalpha(ret.type) && ( isalpha( is.peek()) || !type._is_valid(ret.type) ))
        return read_word(is, ret.type);

    else if ((type._is_valid(ret.type)))
        return ret;
    
    else if(!is && is.peek() == EOF)
        throw MainException("Конец файла!", NOT_ARCHIVED_ERROR_INPUT_OF_END_FILE);
    
    else
        throw MainException(ret, "Неправильный ввод!");

}
Token TokenStream::read_number(istream& is, const char &first_digit) {

    Token ret;

    is.putback(first_digit);
    is >> ret.value;
    ret.type = Type_lexeme::number;

    return ret;

}
Token TokenStream::read_word(istream &is, const char &first_simbol) {

    Token ret;

    is.putback(first_simbol);
    ret.word = get_word_from_string(is);
    ret.type = Type_lexeme::word;

    return ret;

}


Token TokenStream::read_Token_from_file() {
   
    if( !_file_for_input.is_open() )
        open_file_for_input();

    // Сразу же проверяем, нет ли конца файла чтобы сбросить обработку выше и не заниматься ей тут
    close_file_for_input();
    get_message_of_errors_file_for_input();

    if(_file_for_input.is_open())
        return read_Token(_file_for_input);

    // На случай непойманной ошибки при обработке файла
    Main_settings->set_mode_input(Modes_input::console);
    throw MainException("Ошибка при чтении файла!");

}
void TokenStream::open_file_for_input() {

    if(Main_settings->get_mode_input() == Modes_input::file)
        _file_for_input.open(Main_settings->get_name_file_to_input());

}
void TokenStream::close_file_for_input() {
    
    bool file_must_be_closed = ( _file_for_input.fail() ||
                                 _file_for_input.bad() ||
                                 _file_for_input.eof() ||
                                 _file_for_input.peek() == EOF
                                );

    if(file_must_be_closed) {
        _file_for_input.close();
        Main_settings->set_mode_input(Modes_input::console);
    }

}
void TokenStream::get_message_of_errors_file_for_input() {

    if(_file_for_input.fail())
        throw MainException("Невозможно открыть файл!");

    else if(_file_for_input.bad())
        throw MainException("Ошибка при чтении файла!");

    else if(_file_for_input.eof() || _file_for_input.peek() == EOF)
        throw MainException("Файл успешно считан!", NOT_ARCHIVED_MESSAGE_OF_END_FILE);

}
