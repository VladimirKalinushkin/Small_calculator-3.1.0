
#pragma once
#include "calculation.h"

double third_order(TokenStream &Stream) {

    double value = second_order(Stream);

    while (cin) {

        Token oper = Stream.get();
        switch (oper.type) {
            case '+':{
                value += second_order(Stream);
                break;}
            case '-':{
                value -= second_order(Stream);
                break;}
            default:{
                Stream.putback(oper);
                return value;
                break;}
        }
    }

    return 0;

}

double second_order(TokenStream &Stream) {

    double value = first_order(Stream);

    while (cin) {

        Token oper = Stream.get();

        switch (oper.type) {
            case '*':{
                value *= first_order(Stream);
                break;}
            case '/':{
                double second_value = first_order(Stream);
                if (second_value == 0)
                    throw MainException(" Деление на нуль!");
                value /= second_value;
                break;}
            default:{
                Stream.putback(oper);
                return value;
                break;}
        }
    

    }
    return 0;

}

double first_order(TokenStream &Stream) {

    double value = primary(Stream);

    while (cin) {

        Token oper = Stream.get();
        if (oper.type == '^') {
            double second_value = primary(Stream);
            value = pow (value, second_value);
        }
        else {
            Stream.putback(oper);
            return value;
        }
    }

    return 0;

}

double primary(TokenStream &Stream) {

    Token oper = Stream.get();

    switch (oper.type) {

        case Type_lexeme::constante:
        case Type_lexeme::number:
        case Type_lexeme::varriable:{

            return oper.value;
            break;

        }
        case Type_lexeme::Roman_int: {
            Roman_int ret;
            ret.set(oper.word);
            return ret.as_int();
            break;
        }
        case '+':{
            return primary(Stream);
            break;}
        case '-':{
            return  -primary(Stream);
            break;}
        case '(':{

            double result = third_order(Stream);
            oper = Stream.get();
            if (oper.type != ')')
                throw MainException(oper, "нет ')'");
            else return result;
            break;

        }
        case Type_lexeme::function:{
            Stream.putback(oper);
            return math_function(Stream);
            break;
        }
        case Type_lexeme::word: {
            throw MainException(oper, " Переменная не инициализирована!");
            break;}
        case Type_lexeme::key_word: {
            throw MainException(oper, " Имя занято!");
            break;}
        default:{
            throw MainException(oper, " Нет первичного выражения!");
            break;}
    }

    return 0;
}

double math_function(TokenStream &Stream) {
    //Будьте внимательны: порядок обработки функций очень важен!

    Token oper = Stream.get();
    string name = oper.word;

    if (name == "fmod") return instead_of_reading_fmod_calculation(Stream);

    double result = primary(Stream);
    
    if (name == "abs") return abs ( result );
    else if (name == "ln") return log ( result );
    else if (name == "log") return log10 ( result );
    else if (name == "ceil") return ceil ( result );
    else if (name == "floor") return floor (result );
    else if (name == "cos") return cos ( result );
    else if (name == "sin") return sin ( result );
    else if (name == "tan") return tan ( result );

    if (name == "sqrt" )
        if(result >= 0)
            return sqrt ( result );
        else
            throw MainException(" Корень можно извлечь только из неотрицательного числа!");
    
    if (result < -1 || result > 1)
        throw MainException("Для обратных тригонометрических функций должно испооьзоваться значение от -1 до 1!");

    if (name == "asin") return asin ( result );
    else if (name == "acos") return acos ( result );
    else if (name == "atan") return atan ( result );

    throw MainException(oper, "Неизвестная функция, ошибка в логике программы!");

}

double instead_of_reading_fmod_calculation(TokenStream &Stream)
{
        
        char left_bracket = Stream.get().type;
        if(left_bracket != '(')
            throw MainException(left_bracket, "Нет открывающей скобки!");

        double left = primary(Stream);

        char punkt = Stream.get().type;
        if(punkt != ',')
            throw MainException(punkt, "Пропущена запятая!");

        double right = primary(Stream);

        if ( right == 0 )
            throw "Деление на нуль!\n";

        char right_bracket = Stream.get().type;
        if(right_bracket != ')')
            throw MainException(right_bracket, "Нет закрывающей скобки!");

        return fmod ( left, right );

}
