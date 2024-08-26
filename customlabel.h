#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H


#include <QLabel>
#include <QPixmap>
#include <QPainter>

class CustomLabel : public QLabel {
    Q_OBJECT

public:
    explicit CustomLabel(QWidget* parent = nullptr);

    void setPixmap(const QPixmap& pixmap);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QPixmap m_pixmap;
};


#endif // CUSTOMLABEL_H
