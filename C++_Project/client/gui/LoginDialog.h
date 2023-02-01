#ifndef NOTYHELPER_LOGINDIALOG_H
#define NOTYHELPER_LOGINDIALOG_H


#include <QDialog>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class LoginDialog : public QWidget{
Q_OBJECT
private:

    int sock = 0;

    QLabel * username_label;
    QLabel * password_label;

    QLineEdit * username;
    QLineEdit * password;

    QPushButton * login_button;
    QPushButton * create_button;

    QLayout * frame_layout;
    QLayout * label_frame;
    QLayout * input_frame;
    QLayout * button_frame;

public:

    explicit LoginDialog(int sock, QWidget * parent = nullptr);
    ~LoginDialog() override = default;

    void place_items();
    void connect_items();

    inline QString getUsername() {
        return this->username->text();
    }

signals:
    void logged_in();

};


#endif //NOTYHELPER_LOGINDIALOG_H
