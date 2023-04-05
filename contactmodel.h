
#ifndef CONTACTMODEL_H
#define CONTACTMODEL_H

#include <QAbstractListModel>



class ContactModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ContactModel(QObject *parent = nullptr);
    enum Roles {
        ContactId = Qt::UserRole,
        ContactDisplayName,
        ContactEmail
    };
    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QHash<int, QByteArray> roleNames();

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QList<QVariantMap> datas() const;
    void setDatas(const QList<QVariantMap> &newDatas);

signals:
    void datasChanged();

private:
    QList<QVariantMap> mDatas;
    Q_PROPERTY(QList<QVariantMap> datas READ datas WRITE setDatas NOTIFY datasChanged)
};

#endif // CONTACTMODEL_H
