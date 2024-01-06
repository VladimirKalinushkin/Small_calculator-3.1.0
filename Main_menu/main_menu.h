
#include "welcome_words.cpp"

void main_menu(Settings &Main_settings,  TokenStream &Stream);

bool enable_Main_modes(Settings &Main_settings, TokenStream &Stream);
bool check_exit_simbol(TokenStream &Stream);


void help_out(Settings &Main_settings);


void menu_to_set_Main_settings(Settings &Main_settings);

void __set_mode_output(Settings &Main_settings);
void __set_mode_output_with_file(Settings &Main_settings);
void __set_name_file_to_output(Settings &Main_settings);


void set_filestream_to_input(Settings &Main_settings);
void check_correct_end_input(TokenStream &Stream);

void errors_handler(MainException &ex, Settings &Main_settings);

