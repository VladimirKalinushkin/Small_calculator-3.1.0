
#pragma once
#include "varriables.h"

bool create_or_set_varriable(TokenStream &Stream) {

    Token oper = Stream.get();
    if(oper.type == Type_lexeme::key_word && oper.word == "var"){

        create_varriable(Stream);
        return true;
    }    
    else if(oper.type == Type_lexeme::varriable) {

        Token new_oper = Stream.get();
        if( new_oper.type == Type_lexeme::equality) {

            set_Varriable(Stream, oper);
            return true;
        }
        else 
            Stream.putback(new_oper);
    }
    
    Stream.putback(oper);
    return false; 

}

void create_varriable(TokenStream &Stream){

    Token oper = Stream.get();
    if (oper.type == Type_lexeme::word) {

        if (Stream.get().type == Type_lexeme::equality) {

            string name = oper.word;
            double value = third_order(Stream);
            Stream.inicialise_Varriable(name, value);

        }
        else throw MainException("Пропущено '=' !");

    }
    else throw MainException(oper, " Имя переменной занято!");


}

void set_Varriable(TokenStream &Stream, const Token &oper) {

    double value = third_order(Stream);
    Stream.set_Varriable( oper.word, value );


}
