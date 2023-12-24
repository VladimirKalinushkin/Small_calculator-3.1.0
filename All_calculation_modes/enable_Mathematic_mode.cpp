
#include "enable_Mathematic_mode.h"

void enable_Mathematic_modes(TokenStream &Stream, Settings &Main_settings, Mathematic_result &result) {
    
    if( Main_settings.get_mode_input() == Modes_input::file)
        return get_delay_and_enable_mode(Main_settings.get_mode_calculating(), Stream, result);
    
    else if(Main_settings.get_mode_calculating() == Modes_calculating::arabian)
        expression_Mathematic_handler(Stream, result);

    else if(Main_settings.get_mode_calculating() == Modes_calculating::roman)
        expression_Mathematic_handler_for_Roman_int(Stream, result);

}

void get_delay_and_enable_mode(Modes_calculating mode, TokenStream &Stream, Mathematic_result &result) {

    if(mode == Modes_calculating::arabian)
        get_delay_for_mode(Stream, result, &expression_Mathematic_handler);
    
    if(mode == Modes_calculating::roman)
        get_delay_for_mode(Stream, result, &expression_Mathematic_handler_for_Roman_int);
    
    
}

void get_delay_for_mode(TokenStream &Stream, Mathematic_result &result, void(*_function)(TokenStream&, Mathematic_result&)) {

    bool end_delay = false;
    bool is_error = false;
    MainException ex;

    thread th([&Stream, &result, &_function, &end_delay, &is_error, &ex]() { 
        try {

            _function(Stream, result);
        }
        catch(MainException &_ex) {
            is_error = true;
            ex = _ex;
        }
        
        end_delay = true;
    } );

    th.detach();
    Delay_indicator(end_delay);

    if(is_error)
        throw MainException(ex);

}
