#include "configure.h"

BasicConfigure* Configure::basicconfig = new BasicConfigure();
DBConfigure* Configure::dbconfig =
    new DBConfigure(Configure::basicconfig->getDbconfigurefilename());
