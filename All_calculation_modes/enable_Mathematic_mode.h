
void enable_Mathematic_modes(Settings & _setting, TokenStream &Stream, Mathematic_result &result);
void get_delay_and_enable_mode(Modes_calculating mode, TokenStream &Stream, Mathematic_result &result);
void get_delay_for_mode(TokenStream &Stream, Mathematic_result & result, void(*_function)(TokenStream &, Mathematic_result &));
