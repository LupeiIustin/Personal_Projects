#include <QVBoxLayout>
#include "Noty.h"

Noty::Noty(const QString &username, const QString &text, const QDateTime &deadline, bool is_sharable, QWidget *parent) {

    this->username = new QLabel(username, this);
    this->text = new QLabel(text, this);
    this->deadline = new QDateTimeEdit(deadline);
    this->is_sharable = is_sharable;

    this->frame_layout = new QVBoxLayout();

    this->setLayout(frame_layout);
    place_items();
}

void Noty::place_items() {
    this->frame_layout->addWidget(this->username);
    this->frame_layout->addWidget(this->text);
    this->frame_layout->addWidget(this->deadline);
}
