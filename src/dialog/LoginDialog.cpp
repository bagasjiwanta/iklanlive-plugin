//
// Created by bayus on 06/05/22.
//

#include "LoginDialog.h"
#include "ui_LoginDialog.h"
#include <plugin-macros.generated.h>

LoginDialog::LoginDialog(QWidget *parent):
  QDialog(parent) {
  this->ui = new Ui::LoginDialog;
  ui->setupUi(this);
}

LoginDialog::~LoginDialog() {
  delete this->ui;
}
