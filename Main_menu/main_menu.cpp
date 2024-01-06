
#pragma once
#include "main_menu.h"


void main_menu(Settings &Main_settings, TokenStream &Stream) {

    while (cin) {

        try {

            if(Main_settings.promt_must_be_out())
                cout << PROMT;

            if(Main_settings.get_mode_input() == Modes_input::console && check_exit_simbol(Stream))
                return;

            if(Main_settings.get_mode_input() == Modes_input::console && enable_Main_modes(Main_settings, Stream))
                continue;

            Mathematic_result result;
            enable_Mathematic_modes(Stream, Main_settings, result);
            result.out_math_expression_s_result(Main_settings);

            check_correct_end_input(Stream);
        
        }
        catch (MainException &ex) {
        
            errors_handler(ex, Main_settings);
        
        }
        catch (Roman_int::Exception &ex) {

            ex.what();
            MainException _ex("Приозошло исключение при обработке Римских чисел!\n");
            errors_handler(_ex, Main_settings);

        }
    }
}

bool enable_Main_modes(Settings &Main_settings, TokenStream &Stream) {

    Token oper = Stream.get();

    if(oper.type == Type_lexeme::help) {
        help_out(Main_settings);
        return true;
    }
    else if(oper.type == Type_lexeme::settings) {
        menu_to_set_Main_settings(Main_settings);
        return true;
    }
    else if(oper.type == Type_lexeme::key_word && oper.word == "from_file") {
        set_filestream_to_input(Main_settings);
        return true;
    }
    else if(oper.type == Type_lexeme::key_word && oper.word == "clear") {
        system("clear");
        welcome_words(); 
        return true;
    }
    else
        Stream.putback(oper);

    return false;

}
bool check_exit_simbol(TokenStream &Stream) {

    Token oper = Stream.get();
    if(oper.type == Type_lexeme::exit_simbol)
        return true;

    Stream.putback(oper);
    return false;

}


void help_out(Settings &Main_settings) {

    ifstream manual(Main_settings.name_file_to_manual);
    char ch;

    if(!manual.good() || manual.bad() || manual.fail())
        throw MainException("Невозможно отобразить файл справки!\n", NOT_ARCHIVED_THIS_EXCEPTION);

    while(manual) {
        
        manual.get(ch);
        cout << ch;

    }

}


void menu_to_set_Main_settings(Settings &Main_settings) {

    while (cin) {

        cout << "Для настройки вывода файла - o, "
             << "для режима вывода при вводе из файла - f, " 
             << "чтобы указать имя файла для вывода - n, "
             << "для выхода - e: " 
             << '\n'
             << PROMT;

        char ch;
        cin >> ch;

        if (ch == 'e')
            return;

        try {
            switch (ch)
            {
            case 'o':
                __set_mode_output(Main_settings);
                break;
            case 'f':
                __set_mode_output_with_file(Main_settings);
                break;
            case 'n':
                __set_name_file_to_output(Main_settings);
                break;
            default:
                throw MainException("Неправильный ввод! Экстренный выход из меню!\n", NOT_ARCHIVED_THIS_EXCEPTION);
                break;
            }
        }
        catch (MainException &ex) {
            errors_handler(ex, Main_settings);
            return;
        }
    }
}

void __set_mode_output(Settings &Main_settings) {

    cout << "Введите режим вывода (только в консоль, в консоль и в файл, или только в файл): "
         << char(Modes_output::to_console) << " / " << char (Modes_output::to_console_and_file) << " / " << char(Modes_output::to_file)
         << '\n' << PROMT;

    char mode;
    cin >> mode;

    switch(mode) {

    case Modes_output::to_console:
    case Modes_output::to_console_and_file:
    case Modes_output::to_file:
        Main_settings.set_mode_output(Modes_output(mode));
        return;
        break;

    default:
        throw MainException("Неправильный ввод!\n");

    };

}
void __set_mode_output_with_file(Settings &Main_settings) {

    cout << "Введите режим вывода при вводе из файла (в консоль и файл или только в файл): "
         << char(Modes_output_with_file::on_to_console_and_file) << " / " << char (Modes_output_with_file::on_to_file)
         << '\n' << PROMT;

    char mode;
    cin >> mode;

    switch(mode) {

    case Modes_output_with_file::on_to_console_and_file:
    case Modes_output_with_file::on_to_file:
        Main_settings.set_mode_output_with_file(Modes_output_with_file(mode));
        return;
        break;

    default:
        throw MainException("Неправильный ввод!\n");

    };

}
void __set_name_file_to_output(Settings &Main_settings) {

    string name;
    cout    << "Введите имя файла. \n"
            << "Установлено - "
            << Main_settings.get_name_file_to_output()
            << "\n"
            << PROMT;
    cin >> name;

    Main_settings.set_name_file_to_output(name);


}


void set_filestream_to_input(Settings &Main_settings) {

    string name;
    cout << "Введите имя файла: " << PROMT;
    cin >> name;

    Main_settings.set_mode_input(Modes_input::file, name);
}
void check_correct_end_input(TokenStream &Stream) {

    Token oper = Stream.get();
    if(oper.type != Type_lexeme::print) {
        throw MainException(oper, "Выражение неправильно завершено! Нет ';' !");
    };

}

void errors_handler(MainException &ex, Settings &Main_settings) {

    ex.what();
    Stream.clear();

    ofstream file_to_output_log(Main_settings.name_file_to_error_log, ios::app);

    if(file_to_output_log.is_open()) {
        ex.put_to_file(file_to_output_log);
        file_to_output_log.close();
    }
    else
        cerr << "Не удалось открыть файл вывода лога! \n";

    file_to_output_log.close();

}
