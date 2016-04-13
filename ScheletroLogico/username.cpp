#include "username.h"
#include <fstream>

using std::ofstream;
using std::ios;

Username::Username() {}

Username::Username(string us,string pw): login(us), password(pw) {}

Username::Username(const Username& u):login(u.login),password(u.password){}

string Username::getLogin() const {
    return login;
}

string Username::getPassword() const {
    return password;
}

bool Username::contrPassword(const string& pw) const {
    return password==pw;
}

void Username::stampaUsername() const {
    ofstream OUT("FileDB.txt",ios::app);
    OUT<<"Dati accesso:"<<login<<"%"<<password<<"$"<<"\n";
    OUT.close();
}


bool Username::operator==(const Username& us) const{
    return login==us.login && password== us.password;
}

bool Username::operator!=(const Username& us) const{
    return login!=us.login || password!=us.password;
}

void Username::modificaPassword(const string& pw) {
    password=pw;
}
