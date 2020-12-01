#ifndef QWA_BACKEND_GLOBAL_H
#define QWA_BACKEND_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QWA_BACKEND_LIBRARY)
#  define QWA_BACKEND_EXPORT Q_DECL_EXPORT
#else
#  define QWA_BACKEND_EXPORT Q_DECL_IMPORT
#endif

#endif // QWA_BACKEND_GLOBAL_H
