#ifndef RANDOMLISTIMAGESEDITADD_H
#define RANDOMLISTIMAGESEDITADD_H

#include <QWidget>

namespace Ui {
class RandomListImagesEditAdd;
}

class RandomListImagesEditAdd : public QWidget
{
    Q_OBJECT

public:
    explicit RandomListImagesEditAdd(QWidget *parent = nullptr);
    ~RandomListImagesEditAdd();

private:
    Ui::RandomListImagesEditAdd *ui;
};

#endif // RANDOMLISTIMAGESEDITADD_H
