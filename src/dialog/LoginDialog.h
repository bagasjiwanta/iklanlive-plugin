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

  static void *login_helper(void *ctx);

public:
  explicit LoginDialog(QWidget *parent = nullptr);

  ~LoginDialog() override;

private:
  Ui::LoginDialog *ui;
};


#endif //IKLANLIVE_PLUGIN_LOGINDIALOG_H
