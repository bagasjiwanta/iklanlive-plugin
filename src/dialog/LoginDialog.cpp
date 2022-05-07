//
// Created by bayus on 06/05/22.
//

#include "LoginDialog.h"
#include "ui_LoginDialog.h"
#include "api/Auth/Login.h"
#include "plugin-config.h"
#include "exception/AuthException.h"
#include "lib/Observer/ObserverInstance.h"
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
  try{
    Auth::User u = Auth::login(this->ui->username_input->text().toStdString(), this->ui->password_input->text().toStdString());

    config.getActiveUser().setIsLogged(u.isLogged());
    config.getActiveUser().setToken(u.getToken());

    QMessageBox::information(this, "Login Information", "Login Success");
    Observer::get_observer()->notify("update-menu");
    this->close();
  }catch(AuthException* e){
    if(e->getError() == INPUT_NOT_COMPLETE){
      QMessageBox::warning(this, "Login Validation", QString(e->to_string().c_str()));
    }else if(e->getError() == CREDENTIAL_MISMATCH){
      QMessageBox::critical(this, "Login Error", "Pair of username and password is not found");
    }else{
      QMessageBox::critical(this, "Login Error", QString(e->to_string().c_str()));
    }
  }

}
