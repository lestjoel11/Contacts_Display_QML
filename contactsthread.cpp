#include "contactsthread.h"
#include <QThread>

// Create a method that takes in a lamda and runs the method in the same qthread

ContactsThread::ContactsThread(QObject *parent)
    : QObject{parent}
{


}
