#include "mainwindow.h"
#include <QApplication>

#include <QCommandLineParser>
#include <QStringList>
#include <QCommandLineOption>
#include <QWebEngineProfile>
#include <QUrl>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QCommandLineOption opitn;
    QCommandLineOption url(QStringList() << "u" << "url", "descripiton url", "url");
    QCommandLineOption msg(QStringList() << "m" << "msg", "descripiton message", "msg");
    QCommandLineOption profileOpt(QStringList() << "p" << "profile", "second profile");
    QCommandLineOption navOpt(QStringList() << "n" << "navigation", "normal navigation, no posting");

    QCommandLineParser parser;

    parser.addOption(url);
    parser.addOption(msg);
    parser.addOption(profileOpt);
    parser.addOption(navOpt);


    parser.parse(a.arguments());


    QString urlStr = "";
    QString msgStr = "";

    msgStr ="[b]Épisode 30[/b] - Mort sur le Reik (partie 13):\n\r"
            "Troisième opus de la Campagne Impériale - Grissenwald (suite et fin)\n\r"
            "\n\r"
            "Fiche de l'épisode: http://blog.rolisteam.org/podcast/mort-sur-le-reik-partie-13\n\r"
            "Lien vers la vidéo Youtube: https://youtu.be/kCXfaYJZgx4\n\r"
            "\n\r"
            "Ecouter la campagne en podcast: http://blog.rolisteam.org/feed/podcast/warhammer\n\r"
            "Sur itunes: https://itunes.apple.com/fr/podcast/campagne-imp%C3%A9riale-warhammer/id1388335897?l=fr\n\r"
            "\n\r"
            "Venez discuter de la campagne sur notre discord: https://discord.gg/MrMrQwX\n\r"
            "\n\r"
            "Pour Rappel, la campagne est diffusée tous les mercredi à 21h sur la chaîne twitch: https://www.twitch.tv/rolisteam\n\r"
            "En rediffusion, le mercredi à 11h";

    QWebEngineProfile* profile = nullptr;
    bool nav = false;
    if(parser.isSet(url))
    {
        urlStr = parser.value(url);
    }
    if(parser.isSet(msg))
    {
        msgStr=parser.value(msg);

    }
    if(parser.isSet(profileOpt))
    {
        profile = new QWebEngineProfile("hythlodee");
    }
    if(parser.isSet(navOpt))
    {
        nav = true;
    }



    msgStr = msgStr.replace('\r',"");
    msgStr = msgStr.replace('\n',"&#13;&#10;");
    msgStr = msgStr.replace("'","&apos;");



    qDebug() << msgStr;




    MainWindow w(urlStr,msgStr,nav,profile);
    w.show();

    int i = a.exec();

    if(profile)
        delete profile;

    return i;
}
