#include "renderer.h"

Circle::Circle() {
    vector = speed * QVector2D(cos(qrand()), sin(qrand())).normalized();
    color = QColor(qrand() % 256, qrand() % 256, qrand() % 256, 150);
    side = 10 + qrand() % 91;
    pos = QPoint(qrand() % (qApp->desktop()->width() - side), qrand() % (qApp->desktop()->height() - side));
}

Renderer::Renderer()
    : pen(QPen(Qt::black, 1)) {
    image = QImage(qApp->desktop()->size(), QImage::Format_ARGB32);

    startTimer(6);
}

Renderer::~Renderer() {
}

void Renderer::init(int n) {
    circles.clear();
    for (int i = 0; i < n; ++i)
        circles << new Circle;
}

void Renderer::timerEvent(QTimerEvent *) {
    foreach (Circle *circle, circles) {
        double phi = (qrand() % (Circle::range + 1) - Circle::range / 2) * M_PI / 180;
        double c = cos(phi), s = sin(phi);

        circle->vector = QVector2D(circle->vector.x() * c + circle->vector.y() * s, -circle->vector.x() * s + circle->vector.y() * c);

        circle->pos = circle->pos + circle->vector.toPoint();

        if (circle->pos.x() < 0) {
            circle->vector = QVector2D(qAbs(circle->vector.x()), circle->vector.y());
            circle->pos = QPoint(0, circle->pos.y());
        } else if (circle->pos.x() > qApp->desktop()->width() - circle->side) {
            circle->vector = QVector2D(-qAbs(circle->vector.x()), circle->vector.y());
            circle->pos = QPoint(qApp->desktop()->width() - circle->side, circle->pos.y());
        }

        if (circle->pos.y() < 0) {
            circle->vector = QVector2D(circle->vector.x(), qAbs(circle->vector.y()));
            circle->pos = QPoint(circle->pos.x(), 0);
        } else if (circle->pos.y() > qApp->desktop()->height() - circle->side) {
            circle->vector = QVector2D(circle->vector.x(), -qAbs(circle->vector.y()));
            circle->pos = QPoint(circle->pos.x(), qApp->desktop()->height() - circle->side);
        }
    }

    image.fill(Qt::transparent);

    QPainter p(&image);

    p.setRenderHint(QPainter::Antialiasing);

    foreach (Circle *circle, circles) {
        QPainterPath path;
        path.addEllipse(circle->pos + QPoint(circle->side / 2, circle->side / 2), circle->side / 2, circle->side / 2);
        p.fillPath(path, circle->color);
        p.strokePath(path, pen);
    }

    emit rendered(image);
}
