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

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QString::fromUtf8("LoginDialog"));
        LoginDialog->resize(388, 213);
        label = new QLabel(LoginDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 71, 31));
        QFont font;
        font.setPointSize(16);
        label->setFont(font);
        username_input = new QLineEdit(LoginDialog);
        username_input->setObjectName(QString::fromUtf8("username_input"));
        username_input->setGeometry(QRect(20, 80, 341, 28));
        password_input = new QLineEdit(LoginDialog);
        password_input->setObjectName(QString::fromUtf8("password_input"));
        password_input->setGeometry(QRect(20, 120, 341, 28));
        password_input->setEchoMode(QLineEdit::Password);
        pushButton = new QPushButton(LoginDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(270, 160, 91, 31));

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
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
