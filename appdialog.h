#ifndef APPDIALOG_H
#define APPDIALOG_H

#include <QApplication>
#include <QMessageBox>

namespace AppDialog {
    int questionPopup(QString message, QString title, QString yesText, QString quitText);
    int informationPopup(QString message, QString title, QString buttonText);
}

#endif // APPDIALOG_H
