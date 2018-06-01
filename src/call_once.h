// ====================================================
// ProductManagementTool Copyright(C) 2018 Furkan Türkal
// This program comes with ABSOLUTELY NO WARRANTY; This is free software,
// and you are welcome to redistribute it under certain conditions; See
// file LICENSE, which is part of this source code package, for details.
// ====================================================

// Reference: https://wiki.qt.io/Qt_thread-safe_singleton

#ifndef CALL_ONCE_H
#define CALL_ONCE_H

#include <QtGlobal>
#include <QAtomicInt>
#include <QMutex>
#include <QWaitCondition>
#include <QThreadStorage>
#include <QThread>

namespace CallOnce {
    enum ECallOnce {
        CO_Request,
        CO_InProgress,
        CO_Finished
    };

    Q_GLOBAL_STATIC(QThreadStorage<QAtomicInt*>, once_flag)
}

template <class Function>
inline static void qCallOnce(Function func, QBasicAtomicInt& flag)
{
    using namespace CallOnce;

#if QT_VERSION < 0x050000
    int protectFlag = flag.fetchAndStoreAcquire(flag);
#elif QT_VERSION >= 0x050000
    int protectFlag = flag.fetchAndStoreAcquire(flag.load());
#endif

    if (protectFlag == CO_Finished)
        return;
    if (protectFlag == CO_Request && flag.testAndSetRelaxed(protectFlag,
                                                           CO_InProgress)) {
        func();
        flag.fetchAndStoreRelease(CO_Finished);
    }
    else {
        do {
            QThread::yieldCurrentThread();
        }
        while (!flag.testAndSetAcquire(CO_Finished, CO_Finished));
    }
}

template <class Function>
inline static void qCallOncePerThread(Function func)
{
    using namespace CallOnce;
    if (!once_flag()->hasLocalData()) {
        once_flag()->setLocalData(new QAtomicInt(CO_Request));
        qCallOnce(func, *once_flag()->localData());
    }
}

#endif // CALL_ONCE_H
