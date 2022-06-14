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
#include <QDesktopServices>
#include <QUrl>

static QAction* login, *logout, *separator, *show_livestream, *add_livestream ;
static QMenu* livestream;

void on_add_livestream();
void on_show_livestreams();


void load_menu(QMainWindow* window) {
  QMenuBar* menu = window->menuBar();
  QMenu* iklanlive = menu->addMenu("Iklanlive");

  login = iklanlive->addAction("Login");
  logout = iklanlive->addAction("Logout");
  separator = iklanlive->addSeparator();
  livestream = iklanlive->addMenu("Livestreams");

  show_livestream = livestream->addAction("Show Livestreams");
  livestream->addSeparator();
  add_livestream = livestream->addAction("New Livestream");

  QObject::connect(show_livestream, &QAction::triggered, on_show_livestreams);
  QObject::connect(add_livestream, &QAction::triggered, on_add_livestream);
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
      livestream->menuAction()->setVisible(true);
      add_livestream->setVisible(true);
      show_livestream->setVisible(true);
    }else{
      login->setVisible(true);
      logout->setVisible(false);
      separator->setVisible(false);
      add_livestream->setVisible(false);
      show_livestream->setVisible(false);
      livestream->menuAction()->setVisible(false);
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

void on_add_livestream(){
  QDesktopServices::openUrl(QUrl("https://www.iklanlive.com/new-livestream"));
}

void on_show_livestreams(){
  QDesktopServices::openUrl(QUrl("https://www.iklanlive.com/livestreams"));
}