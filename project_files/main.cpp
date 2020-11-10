#include "Hanoi.h"

using namespace std;

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);


    Hanoi hanoi;
    hanoi.Loop();

    return 0;
}