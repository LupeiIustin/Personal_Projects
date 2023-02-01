#ifndef NOTYHELPER_NOTY_H
#define NOTYHELPER_NOTY_H


#include <QWidget>
#include <QLabel>
#include <QtCore/qdatetime.h>
#include <QDateTimeEdit>

class Noty : public QWidget {
Q_OBJECT

private:

    QLabel *username = nullptr;
    QLabel *text = nullptr;
    QDateTimeEdit *deadline = nullptr;
    QLayout *frame_layout = nullptr;
    bool is_sharable = false;

public:

    explicit Noty(const QString &username, const QString &text, const QDateTime &deadline,
                  bool is_sharable, QWidget *parent = nullptr);

    ~Noty() override = default;

    void place_items();
};


#endif //NOTYHELPER_NOTY_H
