#include <QtWidgets>

class CirclesWidget;

class MainWidget : public QWidget {
    Q_OBJECT

    //QLineEdit *edit;
    CirclesWidget *w;

public:
    MainWidget();
    virtual ~MainWidget();

private:
    void setupUi();

private slots:
    void run();

protected:
    void closeEvent(QCloseEvent *);
};
