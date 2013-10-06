#ifndef USBCAMERA_GLOBAL_H
#define USBCAMERA_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef USBCAMERA_LIB
# define USBCAMERA_EXPORT Q_DECL_EXPORT
#else
# define USBCAMERA_EXPORT Q_DECL_IMPORT
#endif

#endif // USBCAMERA_GLOBAL_H
