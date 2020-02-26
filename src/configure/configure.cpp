#include "configure.h"

bool isready = false;
BasicConfigure* Configure::basicconfig = new BasicConfigure();
DBConfigure* Configure::dbconfig =
    new DBConfigure(Configure::basicconfig->getDbconfigurefilename());

Configure::~Configure() {}
