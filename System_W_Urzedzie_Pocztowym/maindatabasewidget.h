#ifndef MAINDATABASEWIDGET_H
#define MAINDATABASEWIDGET_H


#include "localdatabasewidget.h"
class MainDatabaseWidget : public LocalDatabaseWidget
{
    void checkIfRelocate(Database*,Database*, QString, QString);

public:
    MainDatabaseWidget() :LocalDatabaseWidget() {};
    void loadComboBoxChangeStatus(QString,QComboBox*&);

    void changeStatus(Database* ,Database* , QString, QString);

};

#endif // MAINDATABASEWIDGET_H
