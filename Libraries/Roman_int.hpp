
/*

    Класс предназначен для хранения Римских цифр по правилам их записи.
        Предусмотрена работа с четырьмя арифметическими действиями как с целыми числами.
        Есть возможность конвертации из целого числа в римское и обратно. Методы соответственно from_int() и as_int().

    Способы записи: istream и ifstream, способы вывода - ostream и ofstream.

    При неудачной записи. свойство _empty
        устанавливаются в true. Для сброса флага _empty нужно записать
        в объект корректное значение или вызвать метод clear() (очищает, только, если внутренне значение не пусто).
        Проверка осуществляется методом empty().

    C версии 28.2.2023 - вызывается исключение Roman_int::Exception (наследник std::exception)
        Обрабатывать его нужно:
             - при работе с арифметическими операторами
             - при конвертации в целое или из целого
             - при установке и считывании числа (::set(string))

    При первичной инициализации объект помечается как пустой.
        empty() == true.


*/

class Roman_int
{

private:
    string _internal_value;

public:
    Roman_int();
    Roman_int set(string _r_i);

    friend istream &operator>>(istream &is, Roman_int &r_i);
    friend ifstream &operator>>(ifstream &ifs, Roman_int &r_i);
    friend ostream &operator<<(ostream &os, Roman_int &r_i);
    friend ofstream &operator<<(ofstream &ofs, Roman_int &r_i);

    Roman_int operator+(Roman_int &r_i);
    Roman_int operator-(Roman_int &r_i);
    Roman_int operator*(Roman_int &r_i);
    Roman_int operator/(Roman_int &r_i);

    Roman_int &operator+=(Roman_int &r_i);
    Roman_int &operator-=(Roman_int &r_i);
    Roman_int &operator*=(Roman_int &r_i);
    Roman_int &operator/=(Roman_int &r_i);

    int as_int();
    Roman_int &from_int(int i);

    bool empty();
    void clear();

    class Exception : public exception
    {
    public:
        Exception();
        Exception(char *msg);
        Exception(char *msg, char &bad_value);
        Exception(char *msg, int &bad_value);

        void what();

    private:
        char *message = NULL;
        int *bad_value_int = NULL;
        char *bad_value_char = NULL;
    };

private:
    bool _empty;

    bool check(string &_r_i);
    int Roman_Simbol_to_int(char &c);
};

Roman_int::Roman_int()
{
    _internal_value = "";
    _empty = true;
}
Roman_int Roman_int::set(string _r_i)
{

    try {

        _empty = !(_r_i.size());
        if (_empty)
            throw Exception("Передана пустая стрка! Возможно, на вход программы переданы неверные данные");

        if(check(_r_i))
            _internal_value = _r_i;
        
        else {
            _internal_value = _r_i;
            _empty = true;
        }

    }
    catch (Exception &ex) {

        _internal_value = _r_i;
        _empty = true;

        throw Exception(ex);

    }

    return *this;
}

istream &operator>>(istream &is, Roman_int &r_i)
{

    string _to_Roman;
    is >> _to_Roman;

    r_i = r_i.set(_to_Roman);

    return is;
}
ifstream &operator>>(ifstream &ifs, Roman_int &r_i)
{

    string _to_Roman;
    ifs >> _to_Roman;

    r_i = r_i.set(_to_Roman);

    return ifs;
}
ostream &operator<<(ostream &os, Roman_int &r_i)
{

    if (!r_i.empty())
        os << r_i._internal_value;
    else
        cout << "[ Невозможно напечатать пустой объект! ]\n";
    return os;
}
ofstream &operator<<(ofstream &ofs, Roman_int &r_i)
{

    if (!r_i.empty())
        ofs << r_i._internal_value;
    else
        cout << "[ Невозможно напечатать пустой объект! ]\n";
    return ofs;
}

Roman_int Roman_int::operator+(Roman_int &r_i)
{

    Roman_int ret(*this);
    ret += r_i;
    return ret;
}
Roman_int Roman_int::operator-(Roman_int &r_i)
{

    Roman_int ret(*this);
    ret -= r_i;
    return ret;
}
Roman_int Roman_int::operator*(Roman_int &r_i)
{

    Roman_int ret(*this);
    ret *= r_i;
    return ret;
}
Roman_int Roman_int::operator/(Roman_int &r_i)
{

    Roman_int ret(*this);
    ret /= r_i;
    return ret;
}

Roman_int &Roman_int::operator+=(Roman_int &r_i)
{

    int first_operand = this->as_int();
    int second_operand = r_i.as_int();

    int resuilt = first_operand + second_operand;

    this->from_int(resuilt);
    return *this;
}
Roman_int &Roman_int::operator-=(Roman_int &r_i)
{

    int first_operand = this->as_int();
    int second_operand = r_i.as_int();

    *this = this->from_int(first_operand - second_operand);
    return *this;
}
Roman_int &Roman_int::operator*=(Roman_int &r_i)
{

    int first_operand = this->as_int();
    int second_operand = r_i.as_int();

    *this = this->from_int(first_operand * second_operand);
    return *this;
}
Roman_int &Roman_int::operator/=(Roman_int &r_i)
{

    int first_operand = this->as_int();
    int second_operand = r_i.as_int();

    if (second_operand == 0)
        throw Exception("Деление на Нуль!");

    *this = this->from_int(first_operand / second_operand);
    return *this;
}

int Roman_int::as_int()
{

    if (this->empty())
        throw Exception("Преобразование в целое невозможно! Ошибочное или пустое число!");

    int ret = Roman_Simbol_to_int(this->_internal_value[((this->_internal_value.size()) - 1)]);

    for (int i = ((this->_internal_value.size()) - 1); i > 0; --i)
    {
        int right = Roman_Simbol_to_int(this->_internal_value[(i)]);
        int left = Roman_Simbol_to_int(this->_internal_value[i - 1]);

        ret = (left < right) ? ret - left : ret + left;
    }

    return ret;
}
Roman_int &Roman_int::from_int(int i)
{
    if (i <= 0)
        throw Exception("Число для переобразования должно быть больше нуля!", i);

    string s_resuilt = "";

    static const vector<pair<string, int>> names_simbol = {
        {"M", 1000},
        {"CM", 900},
        {"D", 500},
        {"CD", 400},
        {"C", 100},
        {"XC", 90},
        {"L", 50},
        {"XL", 40},
        {"X", 10},
        {"IX", 9},
        {"V", 5},
        {"IV", 4},
        {"I", 1},
    };

    for (auto [name, integer] : names_simbol)
    {
        while (i >= integer)
        {
            i -= integer;
            s_resuilt += name;
        }
    }

    *this = set(s_resuilt);

    return *this;
}

bool Roman_int::check(string &_r_i)
{

    if(!_r_i.size())
        return false;

    string ret;

    try {

        for (char c : _r_i)
            if (Roman_Simbol_to_int(c))
                ret+= c;
      
        _r_i = ret;
        return true;

    }
    catch(Exception &ex) {     
        if(ret.size())
            _r_i = ret;

        else
            _r_i.clear();

        throw Exception(ex);
    }

}
int Roman_int::Roman_Simbol_to_int(char &c)
{
    static const map<char, int> names_simbol = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000},
    };

    if (!names_simbol.count(c))
        throw Exception("Найден некорректный символ - ", c);

    return names_simbol.at(c);
}

bool Roman_int::empty()
{
    return _empty;
}
void Roman_int::clear()
{
    _empty = (_internal_value.size()) ? false : true;
}

Roman_int::Exception::Exception()
{
    message = "Неизвестная ошибка!\n";
}
Roman_int::Exception::Exception(char *msg)
{
    message = msg;
}
Roman_int::Exception::Exception(char *msg, char &bad_value)
{
    message = msg;
    bad_value_char = &bad_value;
}
Roman_int::Exception::Exception(char *msg, int &bad_value)
{
    message = msg;
    bad_value_int = &bad_value;
}
void Roman_int::Exception::what()
{

    if (message)
        cerr << message << "\n";
    if (bad_value_char)
        cerr << "  Передано: " << *bad_value_char << "\n";
    if (bad_value_int)
        cerr << "  Передано: " << *bad_value_int << "\n";
    if (!message)
        cerr << "Неизвестная ошибка!\n";
}
