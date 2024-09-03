#ifndef MOODTAB_H
#define MOODTAB_H

#include <QWidget>

namespace Ui {
class MoodTab;
}

class MoodTab : public QWidget
{
    Q_OBJECT

public:
    explicit MoodTab(QWidget *parent = nullptr);
    ~MoodTab();

private:
    Ui::MoodTab *ui;
};

#endif // MOODTAB_H
