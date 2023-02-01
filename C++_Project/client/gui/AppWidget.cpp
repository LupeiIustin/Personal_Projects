#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include "AppWidget.h"
#include "../defines.h"

AppWidget::AppWidget(int sock, const QString & username, QWidget *parent) {
    this->sock = sock;
    this->username = username;

    this->frame_layout = new QHBoxLayout();
    this->login_layout = new QHBoxLayout();
    this->control_layout = new QVBoxLayout();
    this->noty_layout = new QVBoxLayout();
    this->noty_timer = new QTimer();
    this->alert_timer = new QTimer();

    this->login_widget = new LoginDialog(this->sock, this);

    this->login_layout->addWidget(login_widget);
    this->login_layout->setAlignment(Qt::AlignCenter);

    this->setLayout(login_layout);

    connect_items();
}

void AppWidget::place_noty_items() {
    this->notificationControlWidget = new NotificationControlWidget(this->sock, username, this);

    this->private_noty_label = new QLabel("My notys", this);
    this->shared_noty_label = new QLabel("Shared notys", this);

    this->private_noty_list = new QListWidget(this);
    this->shared_noty_list = new QListWidget(this);

    this->frame_layout->addItem(control_layout);
    this->frame_layout->addItem(noty_layout);

    this->control_layout->addWidget(notificationControlWidget);

    this->noty_layout->addWidget(private_noty_label);
    this->noty_layout->addWidget(private_noty_list);
    this->noty_layout->addWidget(shared_noty_label);
    this->noty_layout->addWidget(shared_noty_list);

    delete login_layout;
    this->setLayout(frame_layout);
    this->noty_timer->start(1000);
    this->alert_timer->start(1000);
}

void AppWidget::connect_items() {
    connect(this->login_widget, &LoginDialog::logged_in, [this]{
        this->username = login_widget->getUsername();
        place_noty_items();
    });

    connect(this->noty_timer, &QTimer::timeout, this, [this]{
        write_string("fetch_noty", this->sock);
        fetch_noty();
    });

    connect(this->alert_timer, &QTimer::timeout, [this]{
        write_string("alert", this->sock);
        write_string(QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm:ss").toStdString(), this->sock);
        fetch_alert();
    });
}

void AppWidget::fetch_noty() {
    int noty_list_size = std::stoi(read_string(this->sock));
    QStringList private_plain_noty;
    while(noty_list_size--){
        private_plain_noty.push_back(QString::fromStdString(read_string(this->sock)));
    }
    private_noty_list->clear();
    private_noty_list->addItems(private_plain_noty);

    noty_list_size = std::stoi(read_string(this->sock));
    QStringList shared_plain_noty;
    while(noty_list_size--){
        shared_plain_noty.push_back(QString::fromStdString(read_string(this->sock)));
    }
    shared_noty_list->clear();
    shared_noty_list->addItems(shared_plain_noty);
}

void AppWidget::fetch_alert() {
    std::string response = read_string(this->sock);
    if(response != NO_ALERT){
        QMessageBox::warning(this, "Notification Alert", QString::fromStdString(response));
        return;
    }
}

