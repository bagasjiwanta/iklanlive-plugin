//
// Created by bayus on 06/05/22.
//

#include <obs-module.h>

#include "plugin-macros.generated.h"
#include <QMenuBar>
#include "Menu.h"

void load_menu(QMainWindow* window) {
  QMenuBar* menu = window->menuBar();
  QMenu* iklanlive = menu->addMenu("Iklanlive");

  iklanlive->addAction("Login");
  iklanlive->addAction("Logout")->setEnabled(false);
}