#include "mainwindow.h"

#include <QLabel>
#include <QToolBar>
#include <QBoxLayout>

Task::Task()
{
    QWidget* Widget = new QWidget(this);
    Widget->setStyleSheet("background-color: #ECF0F1");
    setCentralWidget(Widget);

    QVBoxLayout* MainLayout = new QVBoxLayout();
    Widget->setLayout(MainLayout);

    QLabel* Title = new QLabel("Task Manager", this);
    MainLayout->addWidget(Title);
    Title->setAlignment(Qt::AlignCenter);
    Title->setStyleSheet("font-size: 30pt; margin: 10%;");

    QHBoxLayout* LayoutLabels = new QHBoxLayout();
    MainLayout->addLayout(LayoutLabels);

    QLabel* Pending = new QLabel("Uncompleted", this);
    Pending->setStyleSheet("font-size: 15pt;");
    LayoutLabels->addWidget(Pending);

    QLabel* Cpmpleted = new QLabel("Completed", this);
    Cpmpleted->setStyleSheet("font-size: 15pt;");
    LayoutLabels->addWidget(Cpmpleted);

    QHBoxLayout* HLayout = new QHBoxLayout();
    MainLayout->addLayout(HLayout);

    wPending = new QListView(this);
    wPending->setDragEnabled(true);
    wPending->setAcceptDrops(true);
    wPending->setDropIndicatorShown(true);
    wPending->setDefaultDropAction(Qt::MoveAction);
    HLayout->addWidget(wPending);

    wCopleted = new QListView(this);
    wCopleted->setDragEnabled(true);
    wCopleted->setAcceptDrops(true);
    wCopleted->setDropIndicatorShown(true);
    wCopleted->setDefaultDropAction(Qt::MoveAction);
    HLayout->addWidget(wCopleted);

    wPending->setModel(new QStringListModel());
    wCopleted->setModel(new QStringListModel());

    wPending->setStyleSheet(
    "QlistView { font-size: 20pt; font-weight: bold; }"
    "QListView::item { background-color: red; padding: 10%;"
    "border: 1px solid #C0392B; }"
    "QListView::item::hover { background-color: #C0392B }");

    wCopleted->setStyleSheet(
    "QlistView { font-size: 20pt; font-weight: bold; }"
    "QListView::item { background-color: green; padding: 10%;"
    "border: 1px solid #27AE60; }"
    "QListView::item::hover { background-color: #27AE60 }");

    QToolBar* pToolBar = new QToolBar(this);
    addToolBar(pToolBar);

    pActAdd = new QAction(this);
    pActAdd->setIcon(QIcon(":/resources/add.png"));
    connect(pActAdd, &QAction::triggered, this, &Task::onAdd);

    pActRemove = new QAction(this);
    pActRemove->setIcon(QIcon(":/resources/remove.png"));
    connect(pActRemove, &QAction::triggered, this, &Task::onRemove);

    pToolBar->addAction(pActAdd);
    pToolBar->addAction(pActRemove);
}

void Task::onAdd()
{
    wPending->model()->insertRow(wPending->model()->rowCount());
    QModelIndex oIndex = wPending->model()->index(
                wPending->model()->rowCount() - 1, 0);
    wPending->edit(oIndex);
}

void Task::onRemove()
{
    QModelIndex oIndex = wPending->currentIndex();
    wPending->model()->removeRow(oIndex.row());
}

