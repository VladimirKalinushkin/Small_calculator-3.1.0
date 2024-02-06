
class Packet_exception_output
{

public:
    Chrono::Date _now_Date;
    Chrono::Time _now_Time;

    Token _value;
    const char *_message = NULL;

    Packet_exception_output() {}
    Packet_exception_output(const char *message);
    Packet_exception_output(const Token &value, const char *message);

};

ostream &operator<<(ostream &os, Packet_exception_output p);
ostream &operator<<(ostream &os, Token t);


class MainException : public exception
{

public:
    MainException() {}
    MainException(const char *message);
    MainException(const Token &value, const char *message);

    MainException(bool not_archived);
    MainException(const char *message, bool not_archived);
    MainException(const Token &value, const char *message, bool not_archived);

    void what();
    void put_to_file(ofstream &file_to_output_log);

private:
    Packet_exception_output _value;
    
    bool _not_archived = false;
};

