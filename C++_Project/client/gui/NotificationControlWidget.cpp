#include <QHBoxLayout>
#include "NotificationControlWidget.h"
#include "../defines.h"

NotificationControlWidget::NotificationControlWidget(int sock, const QString & username, QWidget *parent) {
    this->sock = sock;
    this->username = username;
    this->notification_name = new QLineEdit(this);
    this->notification_name_label = new QLabel(this);
    this->alert_time = new QDateTimeEdit(this);
    this->is_shared = new QCheckBox(this);
    this->submit_button = new QPushButton(this);
    this->widget_frame = new QVBoxLayout();

    this->setLayout(widget_frame);
    customize_items();
    place_items();
    connect_items();
}

void NotificationControlWidget::customize_items() {
    this->widget_frame->setAlignment(Qt::AlignCenter);
    this->notification_name_label->setText("Notification name:");
    this->alert_time->setMinimumDateTime(QDateTime::currentDateTime());
    this->alert_time->setDisplayFormat("dd.MM.yyyy hh:mm:ss");
    this->is_shared->setText("Shared");
    this->submit_button->setText("Submit notification");
}

void NotificationControlWidget::place_items() {
    this->widget_frame->addWidget(this->notification_name_label);
    this->widget_frame->addWidget(this->notification_name);
    this->widget_frame->addWidget(this->alert_time);
    this->widget_frame->addWidget(this->is_shared);
    this->widget_frame->addWidget(this->submit_button);
}

void NotificationControlWidget::connect_items() {
    connect(this->submit_button, & QPushButton::clicked, [this]{
        write_string("post_noty", this->sock);

        if(this->is_shared->isChecked())
            write_string("sharable", this->sock);
        else
            write_string("private", this->sock);

        write_string(compose_noty().toStdString(), this->sock);

        this->notification_name->clear();
        this->alert_time->setMinimumDateTime(QDateTime::currentDateTime());
        this->is_shared->setCheckState(Qt::Unchecked);
    });
}

QString NotificationControlWidget::compose_noty() {
    return QString().append(this->username)
    .append(": ")
    .append(this->notification_name->text())
    .append(" Deadline: ")
    .append(this->alert_time->text());
}