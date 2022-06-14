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
#include <stdexcept>


LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent) {
  this->ui = new Ui::LoginDialog;

  ui->setupUi(this);
  QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onClickLogin()));
}

LoginDialog::~LoginDialog() {
  delete this->ui;
}

void *LoginDialog::login_helper(void *ctx) {
  LoginDialog *form = static_cast<LoginDialog *>(ctx);
  try {
    Auth::User u = Auth::login(form->ui->username_input->text().toStdString(),
                               form->ui->password_input->text().toStdString());

    config.getActiveUser().setIsLogged(u.isLogged());
    config.getActiveUser().setToken(u.getToken());

    QMessageBox::information(form, "Login Information", "Login Success");
    Observer::get_observer()->notify("update-menu");
    form->close();
  } catch (AuthException *e) {
    if (e->getError() == INPUT_NOT_COMPLETE) {
      QMessageBox::warning(form, "Login Validation", QString(e->to_string().c_str()));
    } else if (e->getError() == CREDENTIAL_MISMATCH) {
      QMessageBox::critical(form, "Login Error", "Pair of username and password is not found");
    } else {
      QMessageBox::critical(form, "Login Error", QString(e->to_string().c_str()));
    }
  } catch (std::exception const &err) {
    QMessageBox::critical(form, "Login Error", "Some unexpected error happened");

  }

  return nullptr;
}

void LoginDialog::onClickLogin() {
  this->login_helper(this);
}
