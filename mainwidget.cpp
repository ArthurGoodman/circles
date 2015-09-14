#include "mainwidget.h"
#include "circleswidget.h"

MainWidget::MainWidget()
    : w(new CirclesWidget) {
    qsrand(QTime::currentTime().msec());

    setWindowFlags(Qt::Tool);
    setWindowTitle("Fun!");
    setFixedSize(100, 100);
    setupUi();

    w->show();
}

MainWidget::~MainWidget() {
}

void MainWidget::setupUi() {
    QVBoxLayout *box = new QVBoxLayout(this);

    //    edit = new QLineEdit(this);
    //    edit->setFont(QFont("Courier New"));
    //    edit->setText("100");
    //    box->addWidget(edit);

    QPushButton *run = new QPushButton("Fun!", this);
    run->setMinimumHeight(80);
    connect(run, SIGNAL(pressed()), SLOT(run()));
    box->addWidget(run);

    setLayout(box);
}

void MainWidget::run() {
    w->init(100/*edit->text().toInt()*/);
    w->show();
}

void MainWidget::closeEvent(QCloseEvent *) {
    w->deleteLater();
    qApp->quit();
}
