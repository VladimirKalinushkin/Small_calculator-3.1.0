
void clear_istream(istream &is);
string get_word_from_string(istream &is);
void Delay_indicator(bool &end);

void clear_istream(istream &is)
{

    while (is.peek() != '\n' && is.peek() != '\0' && is.peek() != EOF)
        is.get();

    is.clear();
}

string get_word_from_string(istream &is)
{

    string word = "";

    while (is)
    {
        char c = is.get();
        if (isalpha(c) || c == '_')
            word += c;

        else
        {
            is.putback(c);
            return word;
        }
    }
}

void Delay_indicator(bool &end)
{
    static vector<char> delay_indicator = {'|', '/', '-', '\\'};

    while (!end)
    {
        for (int i = 0; i < delay_indicator.size() && !end; i++)
        {
            cout << delay_indicator[i];
            cout.flush();
            this_thread::sleep_for(chrono::milliseconds(50));
            cout << "\b";
        }
    }
}

//
