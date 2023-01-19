#include "firebasehandler.h"
#include <QJsonObject>
FireBaseHandler::FireBaseHandler(QObject *parent)
    : QObject(parent)
    , m_apiKey(QString())
{
    m_networkAccessManager = new QNetworkAccessManager(this);
    connect(this, &FireBaseHandler::userSignedIn, this, &FireBaseHandler::performAuthenticatedDatabaseCall);
    //connect(this, &FireBaseHandler::userSignedIn, this, &FireBaseHandler::creatUserTest);
}

FireBaseHandler::~FireBaseHandler()
{
     m_networkAccessManager->deleteLater();
}
void FireBaseHandler::setAPIKey(QString apiKey)
{
     m_apiKey = apiKey;
}

void FireBaseHandler::signUserUp(QString emailAddress, QString password)
{
    QString signUpEndpoint = "https://identitytoolkit.googleapis.com/v1/accounts:signUpWithCustomToken?key=" +  m_apiKey;

    QVariantMap variantPayload;
    variantPayload["email"] = emailAddress;
    variantPayload["password"] = password;
    variantPayload["returnSecureToken"] = true;

    QJsonDocument jsonPayload = QJsonDocument::fromVariant(variantPayload);
     performPOST( signUpEndpoint, jsonPayload );
}

void FireBaseHandler::signUserIn(QString emailAddress, QString password)
{
    QString signInEndpoint = "https://identitytoolkit.googleapis.com/v1/accounts:signInWithPassword?key=" +  m_apiKey;

    QVariantMap variantPayload;
    variantPayload["email"] = emailAddress;
    variantPayload["password"] = password;
    variantPayload["returnSecureToken"] = true;

    QJsonDocument jsonPayload = QJsonDocument::fromVariant(variantPayload);

     performPOST(signInEndpoint, jsonPayload);



}

void FireBaseHandler::createColection(QJsonDocument doc)
{   qDebug() << "entrou createColletion";
    qDebug() << "MYUSER ID: " << this->m_idUser;
    QString url = "https://onomequecedertatelha-default-rtdb.firebaseio.com/users/"+this->m_idUser+".json";
    qDebug() << "URL:  >>" << url;
    QNetworkRequest newRequest = QNetworkRequest(QUrl(url));
    newRequest.setHeader(QNetworkRequest::ContentTypeHeader,QString("application/json"));

    //qDebug()  << "value newRequest>>: " << newRequest.;
    //connect( m_networkReply,&QNetworkReply::readyRead,this,&FireBaseHandler::networkReplyReadyRead);
     m_networkReply = m_networkAccessManager->post(newRequest, doc.toJson());
     qDebug() << "ReadAllCReate: "<< m_networkReply->readAll();

     return;

}

void FireBaseHandler::updateColection()
{
    QVariantMap variantPayload;
    variantPayload["teste"] = "emailUpdated";
    variantPayload["password"] = "passwordUpdated";
    QJsonDocument jsonPayload = QJsonDocument::fromVariant(variantPayload);
    qDebug() << "entrou updateColllection";

        qDebug() << "MYUSER ID: " << this->m_idUser;
        QString url = "https://onomequecedertatelha-default-rtdb.firebaseio.com/users/"+this->m_idUser+".json";
        qDebug() << "URL:  >>" << url;
        QNetworkRequest newRequest = QNetworkRequest(QUrl(url));
        newRequest.setHeader(QNetworkRequest::ContentTypeHeader,QString("application/json"));

        //qDebug()  << "value newRequest>>: " << newRequest.;
        //connect( m_networkReply,&QNetworkReply::readyRead,this,&FireBaseHandler::networkReplyReadyRead);
         m_networkReply = m_networkAccessManager->post(newRequest, jsonPayload.toJson());
         qDebug() << "ReadAllCReate: "<< m_networkReply->readAll();

         return;
}

void FireBaseHandler::networkReplyReadyRead()
{
    QByteArray response =  m_networkReply->readAll();
    qDebug() << response;
     m_networkReply->deleteLater();

     parseResponse(response);
}

void FireBaseHandler::performAuthenticatedDatabaseCall()
{   qDebug() << "entrou em perfomrauthenticadeDAtaBaseCall";

    //qDebug() << "m_idUser" <<  m_idUser;
    QString endPoint = "https://onomequecedertatelha-default-rtdb.firebaseio.com/users/"+m_idUser+".json?auth="+m_idToken;
    qDebug() << "ENDPOINT: <<< " << endPoint;
    m_networkReply =  m_networkAccessManager->get(QNetworkRequest(QUrl(endPoint)));
    connect(m_networkReply, &QNetworkReply::readyRead, this, &FireBaseHandler::networkReplyReadyRead);
    return;
}

void FireBaseHandler::creatUserTest()
{

}

void FireBaseHandler::performPOST(QString url,QJsonDocument payload)
{
    QNetworkRequest newRequest( (QUrl( url )) );
    newRequest.setHeader( QNetworkRequest::ContentTypeHeader, QString( "application/json"));
     m_networkReply = m_networkAccessManager->post(newRequest, payload.toJson());
    connect(m_networkReply, &QNetworkReply::readyRead, this, &FireBaseHandler::networkReplyReadyRead);
}

void FireBaseHandler::parseResponse(QByteArray response)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(response);
    if (jsonDocument.object().contains("error"))
    {
        qDebug() << "Error occured!" << response;
    }
    else if (jsonDocument.object().contains("kind"))
    {
        QString idToken = jsonDocument.object().value("idToken").toString();
        QString idUser = jsonDocument.object().value("localId").toString();
        qDebug() << "Obtained user ID Token: " << idToken;
        qDebug() << "User signed in successfully!";
         this->m_idToken = idToken;
         this->m_idUser = idUser;
        //qDebug() << "UID: " <<  m_idUser;
        emit userSignedIn();

    }
    else
        qDebug() << "The response was: " << response;
        if(response == "null"){
            /*QJsonDocument doc;


            QJsonObject obj{

                {"uid", "xCAqqUVwcIgfdlI87ADRqRN4eP03"},
                {"email", "anderson_rockX@hotmail.com"},
                {"name", "andisus"}

            };

            doc.setObject(obj);
*/
            QVariantMap variantPayload;
            variantPayload["teste"] = "emailAddress";
            variantPayload["password"] = "password";
            //variantPayload["returnSecureToken"] = true;
            QJsonDocument jsonPayload = QJsonDocument::fromVariant(variantPayload);
            this->createColection(jsonPayload);

        }

        else{
            //QJsonArray arr_  = jsonDocument.array();
            //arr_[0].
            qDebug() << "valor RESPONSE ALL: " << jsonDocument;
            qDebug() << "valor RESPONSE ALL: " << jsonDocument.object().keys()[0];// encontra  o idDoRegistro

            qDebug() << "valor RESPONSE ALL: " << jsonDocument.toJson().split('\n')[1].split('\"')[1]; // encontra  o idDoRegistro

        }



}
