#include <QMessageBox>
#include "LoginDialog.h"
#include "../defines.h"

LoginDialog::LoginDialog(int sock, QWidget *parent) {

    this->sock = sock;

    this->username_label = new QLabel("Username", this);
    this->password_label = new QLabel("Password", this);
    this->username = new QLineEdit(this);
    this->password = new QLineEdit(this);
    this->login_button = new QPushButton("Login", this);
    this->create_button = new QPushButton("Create Account", this);

    this->frame_layout = new QVBoxLayout();
    this->label_frame = new QHBoxLayout();
    this->input_frame = new QHBoxLayout();
    this->button_frame = new QHBoxLayout;

    this->password->setEchoMode(QLineEdit::Password);

    this->setLayout(frame_layout);

    place_items();
    connect_items();
}

void LoginDialog::place_items() {

    this->label_frame->addWidget(username_label);
    this->label_frame->addWidget(password_label);

    this->input_frame->addWidget(username);
    this->input_frame->addWidget(password);

    this->button_frame->addWidget(login_button);
    this->button_frame->addWidget(create_button);

    this->frame_layout->addItem(label_frame);
    this->frame_layout->addItem(input_frame);
    this->frame_layout->addItem(button_frame);

}

void LoginDialog::connect_items() {
    connect(login_button, &QPushButton::clicked, [this] {
        if (this->username->text().isEmpty() || this->password->text().isEmpty())
            return;

        std::string u = this->username->text().toStdString();
        std::string p = this->password->text().toStdString();

        write_string("login", sock);
        write_string(u, sock);
        write_string(p, sock);

        auto response = read_string(sock);
        if (response == OK) {
            emit logged_in();
            this->close();
            return;
        }
        QMessageBox::warning(this, "Login", "Invalid credentials.");
        return;
    });

    connect(create_button, &QPushButton::clicked, [this] {
        if (this->username->text().isEmpty() || this->password->text().isEmpty())
            return;
        std::string u = this->username->text().toStdString();
        std::string p = this->password->text().toStdString();

        write_string("create", sock);
        write_string(u, sock);
        write_string(p, sock);

        auto response = read_string(sock);
        if (response == ACCOUNT_CREATED) {
            emit logged_in();
            this->close();
            return;
        }
        if(response == ALREADY_EXISTS) {
            QMessageBox::warning(this, "Create Account", "Username already taken");
            return;
        }
        return;
    });
}


