#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cctype>

using namespace std;

double chet(istringstream& st);

double chet2(istringstream& st);

double skobochki(istringstream& st);

bool correct(istringstream& st);

double Trigo(const string& st, double x);

double Tre(istringstream& st, double x);

int main() {
    setlocale(LC_ALL, "RU");
    string resul;

    cout << "Введите выражение: ";
    getline(cin, resul);

    istringstream st(resul);//создаем поток из resul
    double result = chet(st);
    cout << "Результат: " << result << endl;
    if (!correct(st)) {
        cout << "Выражение некорректно " << endl;
        return 1;
    }
    return 0;
}


double chet(istringstream& st) {
    double fr = chet2(st);
    char ind;//для хранения символа

    while (st >> ind) {//считываем из потока 
        if (ind == '+' || ind == '-') {
            double nextfr = chet2(st);
            fr = (ind == '+') ? fr + nextfr : fr - nextfr;
        }
        else {
            st.unget(); // вернуть символ обратно, если это не операция,unget-возвращает только что прочитанный символ обратно в поток
            break;
        }
    }

    return fr;
}


double chet2(istringstream& st) {
    double hf = skobochki(st);
    char el;

    while (st >> el) {
        if (el == '*' || el == '/') {
            double nexthf = skobochki(st);
            hf = (el == '*') ? hf * nexthf : hf / nexthf;
        }
        else {
            st.unget(); // возвращает символ обратно, если это не операция
            break;
        }
    }

    return hf;
}


double skobochki(istringstream& st) {
    double qt;
    char cr;
    if (st >> cr) {
        if (isdigit(cr) || cr == '-') {//проверяем цифра это или знак минус 
            st.putback(cr);//возвращаем обратно в поток 
            st >> qt;//опять достаем его,но уже целиком и записываем
            return qt;
        }
        else if (cr == 's' || cr == 'c' || cr == 't' || cr == 'e' || cr == 'x') {
            string namef;
            namef += cr;
            st >> cr;
            while (isalpha(cr)) {
                namef += cr;
                st >> cr;
            }
            st.putback(cr);
            st >> qt;
            return Trigo(namef, qt);
        }
        else {
            cout << "Неверно введеное выражение" << endl;
        }
    }
    return 0;
}

bool correct(istringstream& st) {
    int count = 0;
    char ht;
    st >> ht;
    if (isdigit(ht) || ht == 'x' || ht == '.' || ht == '(' || ht == ')' || ht == '+' || ht == '-' || ht == '/' || ht == '*') {
        if (ht == '(') {
            ++count;
        }
        if (ht == ')') {
            --count;
        }
        if (count < 0) {//то есть, есть закрывающиеся скобочки,но для них нету открывающихся 
            return false;
        }
    }
    return count == 0;
}

double Trigo(const string& st, double x) {
    if (st == "sin") {
        return sin(x);
    }
    if (st == "cos") {
        return cos(x);
    }
    if (st == "tg") {
        return tan(x);
    }
    if (st == "ctg") {
        return 1 / tan(x);
    }
    if (st == "exp") {
        return exp(x);
    }
    if (st != "sin" || st != "cos" || st != "tg" || st != "ctg" || st != "exp") {
        cout << "Некорректная функция" << endl;
    }
}

double Tre(istringstream& st, double x) {
    double ot;
    if (st >> ot) {
        return ot;
    }
    else {
        cout << "Некорректное выражение" << endl;
    }
}
