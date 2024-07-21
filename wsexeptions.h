#ifndef WSEXEPTIONS_H
#define WSEXEPTIONS_H

#include <QException>
#include <QString>

class WSExeptions: public QException {
public:
    WSExeptions(const QString& message) : message(message) {}
    WSExeptions(const WSExeptions& other) : message(other.message) {} // Copy constructor
      ~WSExeptions() override = default;
    void raise() const override { throw *this; }
    WSExeptions* clone() const override { return new WSExeptions(*this); }
    QString getMessage() const { return message; }

private:
    QString message;
};



#endif // WSEXEPTIONS_H
