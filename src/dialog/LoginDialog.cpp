//
// Created by bayus on 06/05/22.
//

#include "LoginDialog.h"
#include "ui_LoginDialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent):
  QDialog(parent) {
  this->ui = new Ui::LoginDialog;

  ui->setupUi(this);
  QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onClickLogin()));
}

LoginDialog::~LoginDialog() {
  delete this->ui;
}

void LoginDialog::onClickLogin() {
  QMessageBox::information(this, "Login Information", "Login Success", QMessageBox::Ok);
}
