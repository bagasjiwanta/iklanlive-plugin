/********************************************************************************
** Form generated from reading UI file 'LoginDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QLabel *label;
    QLineEdit *username_input;
    QLineEdit *password_input;
    QPushButton *pushButton;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QString::fromUtf8("LoginDialog"));
        LoginDialog->resize(388, 336);
        label = new QLabel(LoginDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 90, 71, 31));
        QFont font;
        font.setPointSize(16);
        label->setFont(font);
        username_input = new QLineEdit(LoginDialog);
        username_input->setObjectName(QString::fromUtf8("username_input"));
        username_input->setGeometry(QRect(20, 160, 341, 28));
        password_input = new QLineEdit(LoginDialog);
        password_input->setObjectName(QString::fromUtf8("password_input"));
        password_input->setGeometry(QRect(20, 230, 341, 28));
        password_input->setEchoMode(QLineEdit::Password);
        pushButton = new QPushButton(LoginDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(270, 270, 91, 31));
        label_2 = new QLabel(LoginDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 130, 91, 21));
        label_3 = new QLabel(LoginDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 200, 91, 21));
        label_4 = new QLabel(LoginDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 280, 151, 21));
        label_5 = new QLabel(LoginDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 20, 60, 60));
        label_5->setStyleSheet(QString::fromUtf8("border-image:  url(:/resources/logo.png) 0 0 0 0 stretch stretch;\n"
""));

        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("LoginDialog", "Login", nullptr));
        username_input->setPlaceholderText(QCoreApplication::translate("LoginDialog", "Username", nullptr));
        password_input->setInputMask(QString());
        password_input->setPlaceholderText(QCoreApplication::translate("LoginDialog", "Password", nullptr));
        pushButton->setText(QCoreApplication::translate("LoginDialog", "Login", nullptr));
        label_2->setText(QCoreApplication::translate("LoginDialog", "Username", nullptr));
        label_3->setText(QCoreApplication::translate("LoginDialog", "Password", nullptr));
        label_4->setText(QCoreApplication::translate("LoginDialog", "<html><head/><body><p><a href=\"https://iklanlive.com/signup\"><span style=\" text-decoration: underline; color:#0000ff;\">Create New Account</span></a></p></body></html>", nullptr));
        label_5->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
