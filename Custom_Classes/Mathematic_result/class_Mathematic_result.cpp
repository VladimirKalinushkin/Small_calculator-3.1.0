
#pragma once
#include "class_Mathematic_result.h"


void Mathematic_result::out_math_expression_s_result(Settings & Main_Settings) {

    if(!this->_activate_output)
        return;
        
    if( Main_Settings.output_is_to_file() )
        output_result_to_file(Main_Settings); 

    if(Main_Settings.output_is_to_console() || !file_to_output ) 
        output_resuilt_to_console(Main_Settings);
        
}

void Mathematic_result::output_result_to_file(Settings &Main_settings) {

    if(!open_file_to_output(Main_settings.get_name_file_to_output()))
        return;

    Chrono::Date _now;
    Chrono::Time _now_time;

    file_to_output << '\t' << _now << ' ' << _now_time << ' '<< "\t-\t";
    file_to_output << _double_result << '\n';

    file_to_output.close(); 

}
void Mathematic_result::output_resuilt_to_console(Settings &Main_settings) {

    cout << PRINT_RESULT;
    cout << _double_result << '\n';

}

bool Mathematic_result::open_file_to_output(const string  name) {

    file_to_output.open(name, ios::app);
    if(!file_to_output) {
        cerr <<"Невозможно открыть файл для вывода!\n";
        return false;
    }

    return true;

}
