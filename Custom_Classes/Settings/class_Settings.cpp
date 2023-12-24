
#pragma once
#include "class_Settings.h"


bool Settings::promt_must_be_out() {

    return ( _mode_input == Modes_input::console || 
        _mode_output_with_file == Modes_output_with_file::on_to_console_and_file );
}
bool Settings::output_is_to_file() {

    return ( 
        _mode_input == Modes_input::file ||
        _mode_output == Modes_output::to_file ||
        _mode_output == Modes_output::to_console_and_file 
    );
}
bool Settings::output_is_to_console() {
    
    return ( 
        _mode_input == Modes_input::console && (
            _mode_output == Modes_output::to_console ||
            _mode_output == Modes_output::to_console_and_file ) ||  
        (
            _mode_input == Modes_input::file &&
            _mode_output_with_file == Modes_output_with_file::on_to_console_and_file 
        )
    );
}

