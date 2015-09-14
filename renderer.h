#include <QtWidgets>

struct Circle {
    const static int speed = 10;
    const static int range = 10;

    QVector2D vector;
    QPoint pos;
    QColor color;
    int side;

    Circle();
};

class Renderer : public QObject {
    Q_OBJECT

    QList<Circle *> circles;
    QPen pen;

    QImage image;

public:
    Renderer();
    virtual ~Renderer();

    void init(int n);

protected:
    void timerEvent(QTimerEvent *);

signals:
    void rendered(QImage);
};
