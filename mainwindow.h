#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void appendLog(QString log , bool withNewLine);
    void procCmd(QString cmd);
    void procCmd(QStringList cmd);

    void addToTree(QString name);
	void removeFromTree(QString name);
	void searchInTree(QString word);
    void printTree();
    void initStopWords();

private slots:
    void handleCmd();
};

#endif // MAINWINDOW_H
