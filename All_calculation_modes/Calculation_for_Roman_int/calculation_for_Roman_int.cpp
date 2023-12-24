
#pragma once
#include "calculation_for_Roman_int.h"


void expression_Mathematic_handler_for_Roman_int(TokenStream &Stream, Mathematic_result &result) {

    try
    {
        Roman_int _result = third_order_for_Roman_int(Stream);
        result = Mathematic_result(_result);

    }
    catch(Roman_int::exeption ex)
    {
        ex.what();
    }

}

Roman_int third_order_for_Roman_int(TokenStream &Stream)
{
    Roman_int value = second_order_for_Roman_int(Stream);

    while (cin) {

        Token oper = Stream.get();
        
        switch (oper.type) {
            case '+':{
                Roman_int second_value = second_order_for_Roman_int(Stream);
                value += second_value;
                break;}
            case '-':{
                Roman_int second_value = second_order_for_Roman_int(Stream);
                value -= second_value;
                break;}
            default:{
                Stream.putback(oper);
                return value;
                break;}
        }
    }

    return value;
}

Roman_int second_order_for_Roman_int(TokenStream &Stream)
{
    Roman_int value = primary_for_Roman_int(Stream);

    while (cin) {

        Token oper = Stream.get();
        
        switch (oper.type) {
            case '*':{
                Roman_int second_value = primary_for_Roman_int(Stream);
                value *= second_value;
                break;}
            case '/':{
                Roman_int second_value = primary_for_Roman_int(Stream);
                value /= second_value;
                break;}
            default:{
                Stream.putback(oper);
                return value;
                break;}
        }
    }

    return value;
}

Roman_int primary_for_Roman_int(TokenStream &Stream)
{
    Token oper = Stream.get();
    Roman_int ret;

    switch (oper.type) {

        case Type_lexeme::word:{

            ret.set(oper.word);
            if(ret.empty())
                throw MainException(oper, "Неправильный ввод!");

            return ret;
            break;

        }
        case '+':{

            return primary_for_Roman_int(Stream);
            break;
            
        }
        case '(':{

            Roman_int result = third_order_for_Roman_int(Stream);

            oper = Stream.get();
            if (oper.type != ')')
                throw MainException(oper, "нет ')' !");

            return result;
            break;

        }
        default:{

            throw MainException(oper, "Нет первичного выражения!");
            break;
        
        }
    }

}