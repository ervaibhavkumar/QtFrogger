#include "appdialog.h"

#include <QMessageBox>
#include <QApplication>

namespace AppDialog {

int questionPopup(QString message, QString title, QString yesText, QString quitText) {
    QMessageBox msgBox(
                QMessageBox::Question,
                title,
                message,
                QMessageBox::Yes | QMessageBox::No);

    msgBox.setButtonText(QMessageBox::Yes, yesText);
    msgBox.setButtonText(QMessageBox::No, quitText);

    return msgBox.exec();
}

int informationPopup(QString message, QString title, QString buttonText) {
    QMessageBox msgBox(
                QMessageBox::Information,
                title,
                message,
                QMessageBox::Ok);

    msgBox.setButtonText(QMessageBox::Ok, buttonText);

    return msgBox.exec();
}

}
