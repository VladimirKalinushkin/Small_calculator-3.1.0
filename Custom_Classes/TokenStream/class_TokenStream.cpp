

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

void TokenStream::clear() {

    Stream.clear();

    if(Main_settings->get_mode_input() == Modes_input::file)
        clear_istream(_file_for_input);
    else
        clear_istream(cin);
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
         
    else if(Main_settings->get_mode_input() == Modes_input::file){

        open_or_close_file_with_end();

        if(_file_for_input.is_open())
            return read_Token(_file_for_input);

        else {

            Main_settings->set_mode_input(Modes_input::console);
            throw MainException("Ошибка при чтении файла!");
            
        }

    }

}
Token TokenStream::read_Token(istream &is) {

    Token ret;
    Type_lexeme type = Type_lexeme::_values()[0];
    is >> ret.type;

    if (isdigit(ret.type)) {

        is.putback(ret.type);
        is >> ret.value;
        ret.type = Type_lexeme::number;
        return ret;
    
    }

    else if ( isalpha(ret.type) && ( isalpha( is.peek()) || !(ret.type == Type_lexeme::settings || ret.type == Type_lexeme::exit_simbol) ) ) {

        is.putback(ret.type);
        ret.word = get_word_from_string(is);
        ret.type = Type_lexeme::word;
        return ret;
    
    }

    else if ((type._is_valid(ret.type)))
        return ret;
    
    else if(!is && is.peek() == EOF) {
        throw MainException("Конец файла!", NOT_ARCHIVED_ERROR_INPUT_OF_END_FILE);
    }
    else
        throw MainException(ret, "Неправильный ввод!");

}
void TokenStream::open_or_close_file_with_end() {

    if(Main_settings->get_mode_input() == Modes_input::file)
        if(!_file_for_input.is_open())
            _file_for_input.open(Main_settings->get_name_file_to_input());
    
    check_error_and_close_file(_file_for_input, *Main_settings);
    
}

void check_error_and_close_file(ifstream &file_for_input, Settings &Main_settings) {

    if( file_for_input.fail() || file_for_input.bad() || file_for_input.eof() || file_for_input.peek() == EOF) {
        file_for_input.close();
        Main_settings.set_mode_input(Modes_input::console);
    }

    if(file_for_input.fail())
        throw MainException("Невозможно открыть файл!");

    else if(file_for_input.bad())
        throw MainException("Ошибка при чтении файла!");

    else if(file_for_input.eof() || file_for_input.peek() == EOF)
        throw MainException("Файл успешно считан!", NOT_ARCHIVED_MESSAGE_OF_END_FILE);

}

