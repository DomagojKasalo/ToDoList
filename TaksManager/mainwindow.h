#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListView>
#include <QStringListModel>


class Task : public QMainWindow
{
    Q_OBJECT
public:
    Task();

protected slots:
    void onAdd();
    void onRemove ();

private:
    QListView* wPending = nullptr;
    QListView* wCopleted = nullptr;

    QAction* pActAdd = nullptr;
    QAction* pActRemove = nullptr;
};


#endif // MAINWINDOW_H
