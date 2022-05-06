//
// Created by bayus on 06/05/22.
//

#ifndef IKLANLIVE_PLUGIN_LOGINDIALOG_H
#define IKLANLIVE_PLUGIN_LOGINDIALOG_H

#include <QDialog>

namespace ui {
  class LoginDialog;
}

class LoginDialog: public QDialog {
  QObject
private:
  ui::LoginDialog* dialog;
public:
  LoginDialog(QWidget *parent = nullptr);

  LoginDialog(QWidget *parent, const Qt::WindowFlags &f, LoginDialog *dialog);

  ~LoginDialog();
};


#endif //IKLANLIVE_PLUGIN_LOGINDIALOG_H
