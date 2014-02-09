#include "utils.h"

QString substringAfter (QString bigStr, QString littleStr)
{
    return bigStr.right (bigStr.size() - (bigStr.lastIndexOf (littleStr) + littleStr.size() ) );
}

QString suppressExtension (QString str)
{
    str.chop (str.size() - str.lastIndexOf (".") );
    return str;
}
