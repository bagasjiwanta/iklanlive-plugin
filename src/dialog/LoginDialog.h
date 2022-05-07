//
// Created by bayus on 06/05/22.
//

#ifndef IKLANLIVE_PLUGIN_LOGINDIALOG_H
#define IKLANLIVE_PLUGIN_LOGINDIALOG_H

#include <QDialog>

namespace Ui {
  class LoginDialog;
}

class LoginDialog : public QDialog {
  Q_OBJECT

  private slots:
    void onClickLogin();

  public:
    LoginDialog(QWidget *parent = nullptr);

    ~LoginDialog();

  private:
    Ui::LoginDialog *ui;
};


#endif //IKLANLIVE_PLUGIN_LOGINDIALOG_H
