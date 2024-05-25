#include "viewcontroller.h"

ViewController::ViewController(QObject *parent) : QObject(parent) {}

void ViewController::songView()
{
    qDebug() << "song selected";
    emit songViewSelected();
}

void ViewController::albumView()
{
    emit albumViewSelected();
}

void ViewController::selectAlbum()
{
    emit albumSelected();
}
