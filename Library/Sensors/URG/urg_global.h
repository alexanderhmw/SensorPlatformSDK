#ifndef URG_GLOBAL_H
#define URG_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef URG_LIB
# define URG_EXPORT Q_DECL_EXPORT
#else
# define URG_EXPORT Q_DECL_IMPORT
#endif

#endif // URG_GLOBAL_H
