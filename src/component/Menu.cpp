//
// Created by bayus on 06/05/22.
//

#include <obs-module.h>

#include <QMenuBar>
#include "Menu.h"
#include <dialog/LoginDialog.h>
#include <QObject>

void load_menu(QMainWindow* window) {
  QMenuBar* menu = window->menuBar();
  QMenu* iklanlive = menu->addMenu("Iklanlive");

  QAction* login = iklanlive->addAction("Login");
  iklanlive->addAction("Logout")->setEnabled(false);

  QObject::connect(login, &QAction::triggered, on_login);
  blog(LOG_INFO, "Loaded Menu");
}

void on_login() {
  LoginDialog ld;

  blog(LOG_INFO, "Login clicked...");

  ld.setWindowTitle("Iklanlive Login");
  ld.setModal(true);
  ld.exec();
}