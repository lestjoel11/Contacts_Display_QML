#ifndef CONTACTSTHREAD_H
#define CONTACTSTHREAD_H

#include <QObject>

class ContactsThread : public QObject
{
    Q_OBJECT
public:
    explicit ContactsThread(QObject *parent = nullptr);

signals:

};

#endif // CONTACTSTHREAD_H
