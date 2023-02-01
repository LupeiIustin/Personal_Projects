#ifndef NOTYHELPER_NOTIFICATIONCONTROLWIDGET_H
#define NOTYHELPER_NOTIFICATIONCONTROLWIDGET_H


#include <QWidget>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <QTimer>

class NotificationControlWidget : public QWidget {

Q_OBJECT

private:

    int sock = 0;

    QString username = nullptr;

    QLabel *notification_name_label = nullptr;
    QLineEdit *notification_name = nullptr;
    QDateTimeEdit *alert_time = nullptr;
    QCheckBox *is_shared = nullptr;
    QPushButton *submit_button = nullptr;

    QLayout *widget_frame = nullptr;

public:

    explicit NotificationControlWidget(int sock = 0, const QString & username = QString(), QWidget *parent = nullptr);

    ~NotificationControlWidget() override = default;
    void customize_items();
    void place_items();
    void connect_items();

    QString compose_noty();

};


#endif //NOTYHELPER_NOTIFICATIONCONTROLWIDGET_H
