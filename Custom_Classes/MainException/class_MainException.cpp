
#include "class_MainException.h"


Packet_exception_output::Packet_exception_output(const char *message) {
    _message = message;
}
Packet_exception_output::Packet_exception_output(const Token &value, const char *message) {
    _value = value;
    _message = message;
}

ostream &operator<<(ostream &os, Token t)
{

    if (t.type)
        os << "\t"
           << "type:"
           << "\t"
           << t.type
           << "\n"
           << "\t"
           << "value:"
           << "\t"
           << t.value
           << "\n"
           << "\t"
           << "word:"
           << "\t"
           << t.word
           << '\n';

    else
        os << "{ -- No Token -- }\n";

    return os;
}
ostream &operator<<(ostream &os, Packet_exception_output p)
{

    //Был выбран XML-подобный синтаксис как наиболее удобочитаемый
    os << '\n'
       << "</ "
       << p._now_Date
       << " "
       << p._now_Time
       << '\n';

    os << "value:"
       << '\n'
       << p._value;

    os << "message:"
       << '\n';

    if (p._message)
        os << "\t\""
           << p._message
           << "\""
           << '\n';
    else
        os << "\t\""
           << "Сообщения не передано!"
           << "\""
           << '\n';

    os << ">"
       << '\n';

    return os;
}


MainException::MainException(bool not_archived) {

    *this = MainException();
    not_archived = not_archived;

}
MainException::MainException(const char *message, bool not_archived) {

    *this = MainException(message); 
    _not_archived = not_archived;

}
MainException::MainException(const Token &value, const char *message, bool not_archived) {

    *this = MainException(value, message);
    _not_archived = not_archived;

}

MainException::MainException(const char *message) {

    _value = Packet_exception_output(message);

}
MainException::MainException(const Token &value, const char *message) {

    _value = Packet_exception_output(value, message);

}

void MainException::what() {

    cerr << this->_value._message
         << '\n';
            
    if(_value._value.type)
        cerr    << "( "
                << "Передано: "
                << _value._value.type
                << ' '
                << _value._value.value
                << ' '
                << _value._value.word
                << " )"
                << '\n';

}

void MainException::put_to_file(ofstream &file_to_output_log) {

    if(_not_archived)
        return;
        
    file_to_output_log << _value;

}
