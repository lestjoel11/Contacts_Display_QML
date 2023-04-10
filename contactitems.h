#ifndef CONTACTITEMS_H
#define CONTACTITEMS_H

#include <QAbstractListModel>
#include <QJniEnvironment>
#include <QJniObject>
#include <QGuiApplication>
#include <QtCore/private/qandroidextras_p.h>

class ContactItems : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QList<QVariant> datas READ datas WRITE setDatas NOTIFY datasChanged)


public:
    explicit ContactItems(QObject *parent = nullptr);

    enum Roles {
        ContactId = Qt::UserRole,
        ContactName,
        ContactPhone,
        ContactEmail,
    };


    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    QList<QVariant> datas() const;
    void setDatas(const QList<QVariant> &newDatas);
    QList<QMap<QString, QString>> loadContactDetailsFromJNI();

    void loadData();
    void registerObserver();
    void unregisterObserver();
    void onContactChanged();

    void TestNative();
    void updateContactItems(jstring updatedContacts);

    void runOnQmlThread() { qDebug() << "Calling from QTimer";};
    void callContentObs();
    bool checkPermissions();

    // Add a new method to set the instance pointer.
    static void setInstance(ContactItems* inst) {
        instance = inst;
    }
    QJniObject className = QNativeInterface::QAndroidApplication::context();


signals:
    void datasChanged();

private:
    ContactItems* contactItems;
    static ContactItems *instance;
    QList<QVariant> mDatas;
};

#endif // CONTACTITEMS_H
