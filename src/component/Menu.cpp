//
// Created by bayus on 06/05/22.
//

#include <obs-module.h>

#include "./Menu.h"
#include "../dialog/LoginDialog.h"
#include "plugin-config.h"
#include "lib/Observer/ObserverInstance.h"
#include <QMenuBar>
#include <QObject>

static QAction* login, *logout, *separator, *livestream;

void load_menu(QMainWindow* window) {
  QMenuBar* menu = window->menuBar();
  QMenu* iklanlive = menu->addMenu("Iklanlive");

  login = iklanlive->addAction("Login");
  logout = iklanlive->addAction("Logout");
  separator = iklanlive->addSeparator();
  livestream = iklanlive->addAction("Livestreams");

  QObject::connect(login, &QAction::triggered, on_login);
  QObject::connect(logout, &QAction::triggered, on_logout);

  blog(LOG_INFO, "Loaded Menu");

  Observer::Observer* observer = Observer::get_observer();

  observer->subscribe("update-menu", [](void*){
    blog(LOG_INFO, "Okayy");
    if(config.getActiveUser().isLogged()){
      login->setVisible(false);
      logout->setVisible(true);
      separator->setVisible(true);
      livestream->setVisible(true);
    }else{
      login->setVisible(true);
      logout->setVisible(false);
      separator->setVisible(false);
      livestream->setVisible(false);
    }
  });


  Observer::get_observer()->notify("update-menu");
}

void on_login() {
  LoginDialog ld;

  blog(LOG_INFO, "Login clicked...");

  ld.setWindowTitle("Livestream Login");
  ld.setModal(true);
  ld.exec();
}

void on_logout() {
  config.getActiveUser().setToken("");
  config.getActiveUser().setIsLogged(false);
  Observer::get_observer()->notify("update-menu");
}