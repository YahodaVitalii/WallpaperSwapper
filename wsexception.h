#ifndef WSEXCEPTION_H
#define WSEXCEPTION_H

#include <QException>
#include <QString>

class WSExceptions: public QException {
public:
    WSExceptions(const QString& message) : message(message) {}
    WSExceptions(const WSExceptions& other) : message(other.message) {} // Copy constructor
      ~WSExceptions() override = default;
    void raise() const override { throw *this; }
    WSExceptions* clone() const override { return new WSExceptions(*this); }
    QString getMessage() const { return message; }

private:
    QString message;
};



#endif // WSEXCEPTION_H
