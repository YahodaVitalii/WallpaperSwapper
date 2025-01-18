#ifndef WSEXCEPTION_H
#define WSEXCEPTION_H

#include <QException>
#include <QString>

class WSException: public QException {
public:
    WSException(const QString& message) : message(message) {}
    WSException(const WSException& other) : message(other.message) {} // Copy constructor
      ~WSException() override = default;
    void raise() const override { throw *this; }
    WSException* clone() const override { return new WSException(*this); }
    QString getMessage() const { return message; }

private:
    QString message;
};



#endif // WSEXCEPTION_H
