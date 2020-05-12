#include "settings.h"

Settings::Settings()
{

}

int Settings::iniReadInt(QSettings *settings, QString path, int defaultValue, bool *okFind, bool *okParce)
{

    if (!settings->contains(path))
    {
        qCritical() << EL_FORMAT_ERR("Path " + path + " not found in INI file");

        if (okFind)
            *okFind = false;

        return 0;
    }

    if (okFind)
        *okFind = true;


    return settings->value(path, defaultValue).toInt(okParce);
}
