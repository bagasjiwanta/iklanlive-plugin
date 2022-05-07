//
// Created by bayus on 07/05/22.
//

#ifndef IKLANLIVE_PLUGIN_USER_H
#define IKLANLIVE_PLUGIN_USER_H

#include <string>
#include "lib/Config/configable.h"

using namespace std;

namespace Auth {

  class User : public configable {
  public:
    void from_config(const config_t *config) override;
    void to_config(config_t *config) override;

    const string &getToken() const;

    void setToken(const string &token);

    bool isLogged() const;

    void setIsLogged(bool isLogged);

  private:
    string token = "";
    bool is_logged = false;
  };

} // Auth

#endif //IKLANLIVE_PLUGIN_USER_H
