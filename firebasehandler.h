#ifndef FIREBASEHANDLER_H
#define FIREBASEHANDLER_H


#include "qobject.h"
#include <QByteArray>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>
#include <QMetaObject>
class FireBaseHandler: public QObject
{ Q_OBJECT
public:
    explicit FireBaseHandler(QObject *parent = nullptr);
    ~FireBaseHandler();
    void setAPIKey(QString apiKey);
    void signUserUp(QString emailAddress,QString password);
    void signUserIn(QString emailAddress,QString password);
    void createColection(QJsonDocument doc);
    void updateColection();

public
        slots:
    void networkReplyReadyRead();
    void performAuthenticatedDatabaseCall();
    void creatUserTest();

signals:
    void userSignedIn();
private:
    void performPOST(QString url, QJsonDocument payload);
    void parseResponse(QByteArray reponse);
    QString m_apiKey;
    QNetworkAccessManager * m_networkAccessManager;
    QNetworkReply * m_networkReply;
    QString m_idToken;
    QString m_idUser= "xCAqqUVwcIgfdlI87ADRqRN4eP03";
};

#endif // FIREBASEHANDLER_H
