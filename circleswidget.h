#include <QtWidgets>

class Renderer;

class CirclesWidget : public QWidget {
    Q_OBJECT

    QThread *t;
    Renderer *r;

    QImage image;

public:
    CirclesWidget();
    virtual ~CirclesWidget();

    void init(int n);

private slots:
    void updateImage(QImage image);

protected:
    void paintEvent(QPaintEvent *);

    void closeEvent(QCloseEvent *);
};
