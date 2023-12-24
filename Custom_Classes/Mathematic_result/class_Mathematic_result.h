
class Mathematic_result {

public:
    Mathematic_result() {};
    Mathematic_result(double _result) { _double_result = _result; _activate_output = true; }
    Mathematic_result(Roman_int _result) { _roman_int_result = _result; _activate_output = true; }

    void out_math_expression_s_result(Settings & Main_Settings);

private:
    double _double_result;
    Roman_int _roman_int_result;

    bool _activate_output = false;
    ofstream file_to_output;

    void output_result_to_file(Settings &Main_settings);
    void output_resuilt_to_console(Settings &Main_settings);
    void self_output_result(Settings &Main_settings, ostream &os);
    bool open_file_to_output(const string  name);
};
