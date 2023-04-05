
#include "contactmodel.h"


ContactModel::ContactModel(QObject *parent)
    : QAbstractListModel(parent)
{
    QVariantMap map;
    map.insert("name","Willma");
    map.insert("phone","99999999999999");
    map.insert("email", "akslda@gmail.com");
    mDatas.append(map);
}

int ContactModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
    mDatas.size();
}

QHash<int, QByteArray> ContactModel::roleNames()
{
    QHash<int, QByteArray> names;
    names[ContactId] = "Id";
    names[ContactDisplayName] = "DisplayName";
    names[ContactEmail] = "Email";

    return names;
}

QVariant ContactModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    switch(role) {
    case ContactId:
        return "";

    case ContactEmail:
        return "";

    case ContactDisplayName:
        return "";
    }
}

QList<QVariantMap> ContactModel::datas() const
{
    return mDatas;
}

void ContactModel::setDatas(const QList<QVariantMap> &newDatas)
{
    if (mDatas == newDatas)
        return;
    mDatas = newDatas;
    emit datasChanged();
}

