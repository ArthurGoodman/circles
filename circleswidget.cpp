#include "circleswidget.h"
#include "renderer.h"

CirclesWidget::CirclesWidget() {
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setFocusPolicy(Qt::StrongFocus);
    showFullScreen();

    HWND hwnd = (HWND)winId();
    LONG styles = GetWindowLong(hwnd, GWL_EXSTYLE);
    SetWindowLong(hwnd, GWL_EXSTYLE, styles | WS_EX_TRANSPARENT);

    image = QImage(qApp->desktop()->size(), QImage::Format_ARGB32);

    r = new Renderer;
    connect(r, SIGNAL(rendered(QImage)), SLOT(updateImage(QImage)));
    t = new QThread;
    r->moveToThread(t);
    t->start();
}

CirclesWidget::~CirclesWidget() {
}

void CirclesWidget::init(int n) {
    r->init(n);
}

void CirclesWidget::updateImage(QImage image) {
    this->image.swap(image);
    update();
}

void CirclesWidget::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.drawImage(0, 0, image);
}

void CirclesWidget::closeEvent(QCloseEvent *) {
    t->terminate();
    r->deleteLater();
    t->deleteLater();
    deleteLater();
    qApp->quit();
}
