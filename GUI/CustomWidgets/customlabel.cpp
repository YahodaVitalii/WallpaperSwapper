#include "customlabel.h"

CustomLabel::CustomLabel(QWidget* parent)
    : QLabel(parent) {}

void CustomLabel::setPixmap(const QPixmap& pixmap) {
    m_pixmap = pixmap;
    update();
}

void CustomLabel::paintEvent(QPaintEvent* event) {
    if (m_pixmap.isNull()) {
        QLabel::paintEvent(event);
        return;
    }

    QPainter painter(this);
    QSize widgetSize = size();
    QSize pixmapSize = m_pixmap.size();

    // Масштабування зображення з збереженням пропорцій
    QSize scaledSize = m_pixmap.scaled(widgetSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation).size();

    QRect targetRect(0, 0, widgetSize.width(), widgetSize.height());
    QRect sourceRect;

    if (scaledSize.width() > widgetSize.width()) {
        // Якщо ширина перевищує, обрізаємо по ширині
        int xOffset = (scaledSize.width() - widgetSize.width()) / 2;
        sourceRect = QRect(xOffset, 0, widgetSize.width(), scaledSize.height());
    } else {
        // Якщо висота перевищує, обрізаємо по висоті
        int yOffset = (scaledSize.height() - widgetSize.height()) / 2;
        sourceRect = QRect(0, yOffset, scaledSize.width(), widgetSize.height());
    }

    // Малюємо зображення
    painter.drawPixmap(targetRect, m_pixmap.scaled(scaledSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation), sourceRect);
}
