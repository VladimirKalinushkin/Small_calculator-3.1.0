
class Settings
{

    public:

        Modes_calculating get_mode_calculating() { return _mode_calculating; }
        Modes_output get_mode_output() { return _mode_output; }
        Modes_output_with_file get_mode_output_with_file() { return _mode_output_with_file; }
        Modes_input get_mode_input() { return _mode_input; }

        string get_name_file_to_input() { return _name_file_to_input; }
        string get_name_file_to_output() { return _name_file_to_output; }


        void set_mode_calculating(Modes_calculating _mode){_mode_calculating = _mode;}
        void set_mode_output(Modes_output _mode) {_mode_output = _mode;}
        void set_mode_output_with_file(Modes_output_with_file _mode) {_mode_output_with_file = _mode;}
        
        void set_mode_input(Modes_input _mode) { _mode_input = _mode; }
        void set_mode_input(Modes_input _mode, string name) { _mode_input = _mode; _name_file_to_input = name; }
        void set_name_file_to_output(string _name) {_name_file_to_output = _name;}


        bool promt_must_be_out();
        bool output_is_to_file();
        bool output_is_to_console();


        const char* name_file_to_error_log = "error_log.log";
        const char* name_file_to_manual = "Manuals/manual";

    private:

        Modes_calculating _mode_calculating = Modes_calculating::arabian;
        Modes_input _mode_input = Modes_input::console;
        Modes_output _mode_output = Modes_output ::to_console;
        Modes_output_with_file _mode_output_with_file = Modes_output_with_file::on_to_console_and_file;

        string _name_file_to_input;
        string _name_file_to_output = "output.txt";

};
