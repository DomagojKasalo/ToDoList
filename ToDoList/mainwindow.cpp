#include "mainwindow.h"

#include <QLabel>
#include <QToolBar>
#include <QBoxLayout>

CToDoList::CToDoList()
{
    QWidget* pWidget = new QWidget(this);
    pWidget->setStyleSheet("background-color: #ECF0F1");
    setCentralWidget(pWidget);

    QVBoxLayout* pMainLayout = new QVBoxLayout();
    pWidget->setLayout(pMainLayout);

    QLabel* pwTitle = new QLabel("To Do List", this);
    pMainLayout->addWidget(pwTitle);
    pwTitle->setAlignment(Qt::AlignCenter);
    pwTitle->setStyleSheet("font-size: 30pt; margin: 10%;");

    QHBoxLayout* pHLayoutLabels = new QHBoxLayout();
    pMainLayout->addLayout(pHLayoutLabels);

    QLabel* plblPending = new QLabel("Pending", this);
    plblPending->setStyleSheet("font-size: 15pt;");
    pHLayoutLabels->addWidget(plblPending);

    QLabel* plblCpmpleted = new QLabel("Completed", this);
    plblCpmpleted->setStyleSheet("font-size: 15pt;");
    pHLayoutLabels->addWidget(plblCpmpleted);

    QHBoxLayout* pHLayout = new QHBoxLayout();
    pMainLayout->addLayout(pHLayout);

    m_pwPending = new QListView(this);
    m_pwPending->setDragEnabled(true);
    m_pwPending->setAcceptDrops(true);
    m_pwPending->setDropIndicatorShown(true);
    m_pwPending->setDefaultDropAction(Qt::MoveAction);
    pHLayout->addWidget(m_pwPending);

    m_pwCopleted = new QListView(this);
    m_pwCopleted->setDragEnabled(true);
    m_pwCopleted->setAcceptDrops(true);
    m_pwCopleted->setDropIndicatorShown(true);
    m_pwCopleted->setDefaultDropAction(Qt::MoveAction);
    pHLayout->addWidget(m_pwCopleted);

    m_pwPending->setModel(new QStringListModel());
    m_pwCopleted->setModel(new QStringListModel());

    m_pwPending->setStyleSheet(
    "QlistView { font-size: 20pt; font-weight: bold; }"
    "QListView::item { background-color: red; padding: 10%;"
    "border: 1px solid #C0392B; }"
    "QListView::item::hover { background-color: #C0392B }");

    m_pwCopleted->setStyleSheet(
    "QlistView { font-size: 20pt; font-weight: bold; }"
    "QListView::item { background-color: green; padding: 10%;"
    "border: 1px solid #27AE60; }"
    "QListView::item::hover { background-color: #27AE60 }");

    QToolBar* pToolBar = new QToolBar(this);
    addToolBar(pToolBar);

    m_pActAdd = new QAction(this);
    m_pActAdd->setIcon(QIcon(":/resources/add.png"));
    connect(m_pActAdd, &QAction::triggered, this, &CToDoList::onAdd);

    m_pActRemove = new QAction(this);
    m_pActRemove->setIcon(QIcon(":/resources/remove.png"));
    connect(m_pActRemove, &QAction::triggered, this, &CToDoList::onRemove);

    pToolBar->addAction(m_pActAdd);
    pToolBar->addAction(m_pActRemove);
}

void CToDoList::onAdd()
{
    m_pwPending->model()->insertRow(m_pwPending->model()->rowCount());
    QModelIndex oIndex = m_pwPending->model()->index(
                m_pwPending->model()->rowCount() - 1, 0);
    m_pwPending->edit(oIndex);
}

void CToDoList::onRemove()
{
    QModelIndex oIndex = m_pwPending->currentIndex();
    m_pwPending->model()->removeRow(oIndex.row());
}

