#ifndef NOTYHELPER_APPWIDGET_H
#define NOTYHELPER_APPWIDGET_H


#include <QWidget>
#include <QListWidget>
#include "NotificationControlWidget.h"
#include "LoginDialog.h"

class AppWidget : public QWidget {

    Q_OBJECT

private:

    int sock = 0;

    QString username = QString();

    QLayout * frame_layout = nullptr;
    QLayout * control_layout = nullptr;
    QLayout * noty_layout = nullptr;
    QLayout * login_layout = nullptr;

    LoginDialog * login_widget = nullptr;
    NotificationControlWidget * notificationControlWidget = nullptr;

    QLabel * private_noty_label = nullptr;
    QLabel * shared_noty_label = nullptr;


    QListWidget * private_noty_list = nullptr;
    QListWidget * shared_noty_list = nullptr;
    QTimer * noty_timer = nullptr;
    QTimer * alert_timer = nullptr;

public:

    explicit AppWidget(int sock, const QString & username = QString(), QWidget * parent = nullptr);
    ~AppWidget() override = default;

    void place_noty_items();
    void connect_items();
    void fetch_noty();
    void fetch_alert();

};


#endif //NOTYHELPER_APPWIDGET_H
