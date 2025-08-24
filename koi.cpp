#include "token.h"


int main()
{
    //std::vector<Token> token;
    Token_stream ts;
    std::cout << "Koi 0.0.1\n";
    std::cout << ">>";
    double val = 0;
    while (std::cin)
    {
        std::cout << ">>" << "\n";
        Token t = ts.get();
        if (t.kind == 'q')
        {
            break;
        }
        if (t.kind == ';')
        {
            std::cout << "=" << val << "\n";
        }
        else
        {
            ts.putback(t);
        }
        val = expression();
        
    }
    return 0;

}

