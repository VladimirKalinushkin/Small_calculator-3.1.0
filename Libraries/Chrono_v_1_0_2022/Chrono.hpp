
//for linux system Chrono::Date::zeros_year must be 1900

namespace Chrono
{

    class Time
    {

    public:
        Time();
        Time(int hour, int sec, int min);

        void now();

        string get_this_Date_value();

    private:
        int _hour;
        int _min;
        int _sec;
    };

    class Date
    {

    public:
        long int number_day() const { return _number_day; }
        int day() const { return _day; };
        int month() const { return _month; };
        int year() const { return _year; };
        int day_of_week() const { return _day_of_week; }
        bool IsWorkDay();
        // bool is_error() const {return _is_error; }

        Date();
        Date(int day, int month, int year);
        Date(long int number_day);

        void set(int day, int month, int year);
        void set(long int number_day);
        void now();

        Date add_day(long int number_day);
        Date add_year(int number_year);
        Date add_month(int number_month);
        Date NextWorkDay();
        int WeekOfYear();

        class Invalid
        {
        };

    private:
        long int _number_day;
        int _day;
        int _month;
        int _year;
        int _day_of_week;
        // bool _is_error = false;

        void error_output(string message);
        Date add_minus_month(int number_month);

        static const int zero_s_year = 1900;
        static const int zero_s_Day_of_week = 0;

    public:
        bool operator>(const Date &d);
        bool operator>=(const Date &d);
        bool operator<(const Date &d);
        bool operator<=(const Date &d);
        bool operator==(const Date &d);
        bool operator!=(const Date &d);
    };

    ostream &operator<<(ostream &os, Time &tm);
    ofstream &operator<<(ofstream &ofs, Time &tm);

    //

    Time::Time()
    {
        now();
    }
    Time::Time(int hour, int sec, int min)
    {

        _hour = hour;
        _min = min;
        _sec = sec;

        if (_hour < 0 || _min < 0 || _sec < 0 || _hour > 23 || _min > 59 || _sec > 59)
        {

            cerr << "Неправильно введено время!\n";
            now();
        }
    }
    void Time::now()
    {

        time_t now = time(0);
        tm *ltm = localtime(&now);

        this->_hour = ltm->tm_hour;
        this->_min = ltm->tm_min;
        this->_sec = ltm->tm_sec;
    }
    string Time::get_this_Date_value()
    {
        return to_string(_hour) + ":" + to_string(_min) + ":" + to_string(_sec);
    }

    ostream &operator<<(ostream &os, Time &tm)
    {
        return os << tm.get_this_Date_value();
    }
    ofstream &operator<<(ofstream &ofs, Time &tm)
    {
        ofs << tm.get_this_Date_value();

        return ofs;
    }
    //

    int GetMonthDay(int year, int month);
    bool is_leap_year(int year);

    long int get_zero_s_century_length(const int &y, const int &zero_s_year);
    long int get_century_s_length(const int &y, const int &zero_s_year);
    long int get_last_century_s_length(const int &y, const int &zero_s_year);
    long int get_last_year_length(const int &y, const int &m);

    int get_year_in_zero_s_century(long int &number_day, const int &zero_s_year);
    int get_century(int &year, long int &number_day, const int &zero_s_year);
    int get_year_in_last_century(int &year, long int &number_day, const int &zero_s_year);
    int get_year(long int &number_day, const int &zero_s_year);
    int get_month(long int &number_day, const int &year);

    ostream &operator<<(ostream &os, Date &Dt);
    Date &operator>>(istream &is, Date &Dt);

    ofstream &operator<<(ofstream &ofs, Date &Dt);

    Date::Date()
    {

        // инициализация по умолчанию текущей датой

        try
        {

            now();
        }
        catch (Invalid)
        {

            error_output("Сбой в Операционной системе! Дата не может быть проинициализирована! Обратитесь к ситемному администратору!");
        }
    }
    Date::Date(int day, int month, int year)
    {

        set(day, month, year);
    }
    Date::Date(long int number_day)
    {

        set(number_day);
    }

    void Date::set(int day, int month, int year)
    {

        try
        {

            if (!(year >= zero_s_year && month > 0 && month < 13 && day > 0 && day <= GetMonthDay(year, month)))
            {

                throw Invalid();
            }

            _year = year;
            _month = month;
            _day = day;

            int z_e = zero_s_year;
            /* Если нулевой год - не нулевой в веке, вычисляем длину нулевого века - для переносимости кода */
            _number_day = 0;
            _number_day += _day;
            _number_day += get_last_year_length(_year, _month);
            _number_day += get_last_century_s_length(_year, z_e);
            _number_day += get_century_s_length(_year, z_e);
            _number_day += get_zero_s_century_length(_year, z_e);
            _number_day--;

            for (int i = 0; i <= (_number_day + zero_s_Day_of_week) % 7; i++)
                _day_of_week = i;
        }
        catch (Invalid &a)
        {

            error_output("Дата не может быть создана!\n");
        }
    }
    void Date::set(long int number_day)
    {

        try
        {

            if (number_day < 0)
                throw Invalid();

            int z_e = zero_s_year;
            number_day++;
            this->_year = get_year(number_day, z_e);
            this->_month = get_month(number_day, _year);
            this->_day = number_day;

            set(this->_day, this->_month, this->_year);
        }
        catch (Invalid)
        {

            error_output("Дата не может быть создана!\n");
        }
    }

    void Date::now()
    {

        time_t now = time(0);
        tm *ltm = localtime(&now);

        this->_year = zero_s_year + ltm->tm_year;

        int mm = ltm->tm_mon;
        this->_month = mm + 1;

        this->_day = ltm->tm_mday;

        set(this->_day, this->_month, this->_year);
    }

    Date Date::add_day(long int number_day)
    {

        Date ret(*this);
        ret.set(this->_number_day + number_day);

        return ret;
    }
    Date Date::add_year(int number_year)
    {

        Date ret;
        int year = this->_year + number_year;
        int month = this->_month;
        int day = this->_day;

        if (!is_leap_year(year) && month == 2 && day == 29)
        {
            month = 3;
            day = 1;
        }

        ret.set(day, month, year);

        return ret;
    }

    Date Date::add_minus_month(int number_month)
    {

        Date ret(*this);

        while (number_month > 0)
        {

            ret._month--;
            if (ret._month == 0)
            {

                ret._year--;
                ret._month = 12;
            }

            if (ret._day > GetMonthDay(ret._year, ret._month))
                ret._day = GetMonthDay(ret._year, ret._month);

            number_month--;
        }

        ret.set(ret._day, ret._month, ret._year);
        return ret;
    }
    Date Date::add_month(int number_month)
    {

        Date ret(*this);

        if (number_month < 0)
            return add_minus_month(-number_month);

        while (number_month > 0)
        {

            ret._month++;
            if (ret._month == 13)
            {

                ret._year++;
                ret._month = 1;
            }

            if (ret._day > GetMonthDay(ret._year, ret._month))
                ret._day = GetMonthDay(ret._year, ret._month);

            number_month--;
        }

        ret.set(this->_day, this->_month, this->_year);
        return ret;
    }

    void Date::error_output(string message)
    {

        cerr << message << "\n";

        this->now();
    }

    bool Date::IsWorkDay()
    {

        static const bool workDayArray[7] = {true, true, true, true, true, false, false};

        return workDayArray[this->_day_of_week];
    }
    Date Date::NextWorkDay()
    {

        Date ret(*this);

        ret = ret.add_day(1);
        while (ret.IsWorkDay() == false)
            ret = ret.add_day(1);

        return ret;
    }
    int Date::WeekOfYear()
    {

        int length = 0;
        Date min_day(1, 1, this->_year);

        length = (this->number_day() - min_day.number_day() + (7 - this->number_day() % 7) + 1);

        return length / 7;
    }

    int GetMonthDay(int year, int month)
    {

        static const int monthArray[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        if (month == 2 && is_leap_year(year))
        {
            return 29;
        }

        return monthArray[month];
    }
    bool is_leap_year(int year)
    {

        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
            return true;

        else
            return false;
    }

    long int get_zero_s_century_length(const int &y, const int &zero_s_year)
    {

        long int length = 0;

        if ((zero_s_year) % 100 == 0)
            return 0;

        int min_year = zero_s_year;
        int max_year = (zero_s_year) - ((zero_s_year) % 100) + 100 - 1;

        if (y <= max_year)
            max_year = y - 1;

        int number_year_s = max_year - min_year + 1;

        if (number_year_s == 0)
            return 0;

        length += number_year_s * 365;

        int number_leap_years = (min_year % 4 + number_year_s - 1) / 4;
        if (number_leap_years > 0)
            length += number_leap_years;

        return length;
    }
    long int get_century_s_length(const int &y, const int &zero_s_year)
    {

        long int length = 0;

        int min_year = zero_s_year;
        if ((zero_s_year) % 100 != 0)
        {
            min_year = (zero_s_year);
            min_year -= (zero_s_year) % 100;
            min_year += 100;
        }

        int max_year = y - y % 100 - 1;

        int number_year_s = max_year - min_year + 1;

        if (number_year_s <= 0)
            return 0;

        length += number_year_s * 365;

        int min_century = min_year / 100;
        int number_century_s = number_year_s / 100;

        length += number_century_s * 24;

        int number_leap_years = (min_century % 4 + number_century_s - 1) / 4;
        if (number_leap_years > 0)
            length += number_leap_years;

        return length;
    }
    long int get_last_century_s_length(const int &y, const int &zero_s_year)
    {

        long int length = 0;

        int min_year = y - y % 100;
        int max_year = y - 1;

        if (min_year < zero_s_year)
            return 0;

        int number_year_s = max_year - min_year + 1;

        if (number_year_s == 0)
            return 0;

        length += number_year_s * 365;

        int number_leap_years = (max_year % 100) / 4;
        if (number_leap_years > 0)
            length += number_leap_years;

        if (is_leap_year(min_year))
            length += 1;

        return length;
    }
    long int get_last_year_length(const int &year, const int &month)
    {

        long int last_year_length = 0;

        int m = month;

        while (m > 0)
        {

            m--;
            last_year_length += GetMonthDay(year, m);
        }

        return last_year_length;
    }

    int get_year_in_zero_s_century(long int &number_day, const int &zero_s_year)
    {

        int year = zero_s_year;

        while (number_day > get_zero_s_century_length(year, zero_s_year))
        {

            if (year % 100 == 0)
            {

                number_day -= get_zero_s_century_length(year, zero_s_year);
                return year;
            }

            year++;
        }

        year--;
        number_day -= get_zero_s_century_length(year, zero_s_year);

        return year;
    }
    int get_century(int &year, long int &number_day, const int &zero_s_year)
    {

        while (number_day > get_century_s_length(year, zero_s_year))
        {

            year += 100;
        }

        year -= 100;
        number_day -= get_century_s_length(year, zero_s_year);

        return year;
    }
    int get_year_in_last_century(int &year, long int &number_day, const int &zero_s_year)
    {

        while (number_day > get_last_century_s_length(year, zero_s_year))
        {

            year++;
        }

        year--;
        number_day -= get_last_century_s_length(year, zero_s_year);

        return year;
    }
    int get_year(long int &number_day, const int &zero_s_year)
    {

        int year = get_year_in_zero_s_century(number_day, zero_s_year);

        if (year % 100 != 0)
            return year;

        year = get_century(year, number_day, zero_s_year);
        year = get_year_in_last_century(year, number_day, zero_s_year);

        return year;
    }
    int get_month(long int &number_day, const int &year)
    {

        int month = 1;

        while (number_day > GetMonthDay(year, month))
        {

            number_day -= GetMonthDay(year, month);
            month++;
        }

        return month;
    }

    ostream &operator<<(ostream &os, Date &d)
    {

        return os << d.day() << '.' << d.month() << '.' << d.year();
    }
    Date &operator>>(istream &is, Date &d)
    {

        int day;
        int month;
        int year;

        char sep_one;
        char sep_two;

        is >> day >> sep_one >> month >> sep_two >> year;

        if ((sep_one == '.' && sep_two == '.') || cin)
            d.set(day, month, year);

        else
            is.clear(ios_base::failbit);

        return d;
    }

    ofstream &operator<<(ofstream &ofs, Date &d)
    {

        ofs << d.day() << '.' << d.month() << '.' << d.year();

        return ofs;
    }

    bool Date::operator>(const Date &d)
    {

        return ((_year > d._year) || (_year == d._year && _month > d._month) || (_year == d._year && _month == d._month && _day > d._day));
    }
    bool Date::operator==(const Date &d)
    {

        return (_year == d._year && _month == d._month && _day == d._day);
    }
    bool Date::operator>=(const Date &d)
    {

        return *this > d || *this == d;
    }
    bool Date::operator<(const Date &d)
    {

        return !(*this >= d);
    }
    bool Date::operator<=(const Date &d)
    {

        return !(*this > d);
    }
    bool Date::operator!=(const Date &d)
    {

        return !(*this == d);
    }
}
