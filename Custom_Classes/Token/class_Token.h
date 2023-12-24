
class Token
{
public:

    char type = '\0';
    double value = -INFINITY;
    string word = "";

    Token() {}
    Token (string w, double v) {type = Type_lexeme::constante; word = w; value = v;}
    Token (double v) { type = Type_lexeme::number; value = v; }
    Token (string w) { type = Type_lexeme::word; word = w; }

};


