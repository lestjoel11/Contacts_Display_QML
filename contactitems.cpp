#include "contactitems.h"
#include "QJniObject"
#include "QGuiApplication"
#include <QtCore/private/qandroidextras_p.h>
#include <QtCore/qglobal.h>
#include <QJsonDocument>
#include <QTimer>

ContactItems::ContactItems(QObject *parent)
    : QAbstractListModel(parent)
{
    loadData();
    callContentObs();

}

extern "C" {
JNIEXPORT void JNICALL
Java_com_example_contactsdisplay_MainActivity_onContactChangedNative(JNIEnv *env, jobject, jlong ptr) {
    //Error here it contactItems is null that means that the pointer maybe null
    qDebug() << "Pointer is: "<< ptr;

    QPointer<ContactItems> contactItems = reinterpret_cast<ContactItems*>(ptr);
    auto setupTimer = [](QPointer<ContactItems> contactItems) {
        QTimer *t = new QTimer(nullptr);
        t->setSingleShot(true);

        QObject::connect(t, &QTimer::timeout, [t, contactItems]() {
            if (!contactItems.isNull()) {
                contactItems->loadData();
                t->deleteLater();
            }
        });

        t->start(0);
    };
    QMetaObject::invokeMethod(contactItems->thread(), [setupTimer, contactItems]() {
        setupTimer(contactItems);
    });
}
}


void ContactItems::callContentObs() {
    className.callMethod<void>("readPointer","(J)V",(long long)(ContactItems*)this);
}
void ContactItems::loadData() {

    QJniObject jniArray = className.callObjectMethod(
        "loadContactDetails",
        "()Ljava/lang/String;"
        );
    qDebug() << "Loading Data";

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jniArray.toString().toUtf8());
    auto contacts = jsonDoc.toVariant().toList();
//    beginInsertRows(QModelIndex(), 0,contacts.size()-1);
    beginResetModel();
    setDatas(contacts);
//    endInsertRows();
    endResetModel();
}



int ContactItems::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
    return mDatas.size();
}

QVariant ContactItems::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    QVariantMap currentRow = mDatas.at(index.row()).toMap();
    //Lookup Key is also present here
    switch(role){
    case ContactName:
        return QVariant(currentRow.value("ContactName").toString());
    case ContactEmail:
        return QVariant(currentRow.value("ContactEmail").toString());
    case ContactPhone:
        return QVariant(currentRow.value("ContactPhone").toString());
    }
    return QVariant();
}

QHash<int, QByteArray> ContactItems::roleNames() const
{
    QHash<int, QByteArray> names;
    names[ContactName] = "ContactName";
    names[ContactEmail] = "ContactEmail";
    names[ContactPhone] = "ContactPhone";

    return names;
}

bool ContactItems::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags ContactItems::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable; // FIXME: Implement me!
}

QList<QVariant> ContactItems::datas() const
{
    return mDatas;
}

void ContactItems::setDatas(const QList<QVariant> &newDatas)
{
    if (mDatas == newDatas)
        return;
    mDatas = newDatas;
    emit datasChanged();
}
