#include "Hanoi.h"

using namespace std;

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);

    wcout << L"\t\t\t��������� �� ����������:\n\n";
    wcout << L"> ��� �������� ����� ����� ��������������� ��������� W, E, Space, ���� �������� ���� (�����, ������ � �����������)." << endl;
    wcout << L"\t>������� W [������� �����] - ��������� ���� �� �������� ����� ��������." << endl;
    wcout << L"\t>������� E [������� ������] - ��������� ���� �� �������� ������ ��������." << endl;
    wcout << L"\t>������� Space [������� �����] - ��������� ���� ����� ���� �������� (�� ���������).\n" << endl;
    wcout << L"\t>����� ������ ���� - ��������� ���� �� �������� ����� ��������." << endl;
    wcout << L"\t>����������� ������ ���� - ��������� ���� ����� ���� �������� (�� ���������)." << endl;
    wcout << L"\t>������ ������ ���� - ��������� ���� �� �������� ������ ��������.\n" << endl;
    wcout << L"> ��� ����������/���������� ��������� ���������� ������� ����. ������� M ��� ���� ��� �����." << endl;
    wcout << L"> ��� ������ � ������� ���� ������� Esc." << endl;
    wcout << L"> ��� ����������� ��������� ������� R.\n" << endl;

    wcout << L"> �����:\n\t>����� ����������� � ���������� �������� �������. �������� ����� ��������� �������������� �������� 1, 2, 3.\n\n" << endl;

    wcout << L"\t\t\t������� ����:\n\n";
    wcout << L"> ���� ���������, ����������� �� ����� �� �������� ����� �������, ��� ������ ������� �������� ����� ������ ������ �������. " << endl;
    wcout << L"> ���������� ���������� ��������� � ������ ������� �� ������, ��� ���, ��� ������� ���� _������_ ������ �� ������� ����." << endl;

    Hanoi hanoi;
    hanoi.Loop();

    return 0;
}