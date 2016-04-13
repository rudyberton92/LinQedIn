#ifndef USERNAME_H
#define USERNAME_H

#include <string>
using std::string;

class Username {
private:
    string login;
    string password;

public:
    Username();
    Username(string, string);
    Username(const Username&);
    string getLogin() const;
    string getPassword() const;
    bool contrPassword(const string&) const;
    void stampaUsername() const;
    bool operator==(const Username&) const;
    bool operator!=(const Username&) const;
    void modificaPassword(const string&);
};

#endif
