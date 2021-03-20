#include <QtGlobal>
#include <QMessageBox>
#include <QPicture>
#include <QPainter>
#include <QVBoxLayout>
#include <QGraphicsPixmapItem>
#include <QFile>
#include <QTextStream>
#include <QMouseEvent>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    krok = 0;
    metodaKrizeni = CROSSOVER_METHOD_OX;
    selectedMap = -1;

    if (qApp->arguments().size() != 4) {
        QMessageBox::critical( this, "Chyba", "Zadej parametrem vstupní data.\n"
                               "Očekávám CSV soubor s městy a maticí vzdáleností, mapu a pozice měst na mapě:\n"
                               "simulator <distance.csv> <mapa.png> <mapa.txt>");
        exit(1);
    }

    try {
        matrix = new TMatrix( qApp->arguments()[1].toLatin1().constData());
    }
    catch (const char *msg) {
        QMessageBox::critical( this, "Chyba",
                               QString("Chyba při zpracování souboru '%1':\n%2").
                                    arg( qApp->arguments()[1]).arg( msg));
        exit(1);
    }
    pocetMest = matrix->getNumberOfTargets();
    ui->txtCsvFileName->setText( QString("%1  (celkem %2 měst)").arg( qApp->arguments()[1]).arg( pocetMest));

    mapa = QImage( qApp->arguments()[2]);
    if (mapa.isNull()) {
        QMessageBox::critical( this, "Chyba", "Soubor s mapou se nepovedlo načíst.");
        exit(1);
    }

    QFile inputFile( qApp->arguments()[3]);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in( &inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          QRegExp re("^([^\\s]+)\\s+(\\d+),(\\d+)$");
          if (re.indexIn( line) < 0) {
              QMessageBox::critical( this, "Chyba", "Chyba syntaxe v souboru se souřadnicemi měst na této řádce:\n" + line);
              exit(1);
          }
          QString mesto = re.cap(1);
          int mestoIdx = matrix->getTargetByName( mesto.toUtf8().constData());
          if (mestoIdx < 0) {
              QMessageBox::critical( this, "Chyba", QString("Město %1 nebylo v matici vzdáleností nalezeno.").arg( mesto));
              exit(1);
          }
          poziceMest[ mestoIdx] = QPoint( re.cap(2).toInt(), re.cap(3).toInt());
       }
       inputFile.close();
    }

    reset();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->tabWidget->resize( ui->centralwidget->width(), ui->centralwidget->height() - 37);
    ui->btnDalsi->setGeometry( ui->centralwidget->width() - 300, ui->centralwidget->height() - 32, 300, 31);
    ui->txtStav->setGeometry( 5, ui->centralwidget->height() - 32, ui->centralwidget->width() - 200, 31);
    ui->txtCsvFileName->resize( ui->centralwidget->width() - ui->txtCsvFileName->x() - 5,
                                ui->txtCsvFileName->height());
    ui->cesty->resize( ui->tabWidget->width() - 4, ui->tabWidget->height() - 34);
    ui->graphicsView->resize( ui->tabWidget->width() - 4, ui->tabWidget->height() - 34);

    showState();

    QWidget::resizeEvent(event);
}

void MainWindow::mousePressEvent( QMouseEvent *event)
{
    if (ui->tabWidget->currentIndex() == 1) {
        if (selectedMap < 0) {
            int mx = event->x();
            int my = event->y() - 30;
            selectedMap = (int)((double) my / ui->graphicsView->height() * 5) * 8 +
                          (int)((double) mx / ui->graphicsView->width() * 8);
        }
        else {
            selectedMap = -1;
        }
        showState();
    }
}

void MainWindow::on_radioButton_clicked()
{
    metodaKrizeni = CROSSOVER_METHOD_OX;
}

void MainWindow::on_radioButton_2_clicked()
{
    metodaKrizeni = CROSSOVER_METHOD_PMX;
}

void MainWindow::on_doubleSpinBox_2_valueChanged(double arg1)
{
    PROBABILITY_CROSSOVER = arg1 / 100.0;
}

void MainWindow::on_doubleSpinBox_valueChanged(double arg1)
{
    PROBABILITY_MUT_STEP = arg1 / 100.0;
}

void MainWindow::on_lineEdit_3_textChanged(const QString &arg1)
{
    bool ok;
    int i;
    i = arg1.toInt( &ok);
    if (ok) {
        POPULATION = arg1.toInt();
        reset();
    }
}

void MainWindow::on_pushButton_clicked()
{
    reset();
}

void MainWindow::showState()
{
    ui->txtStav->setText( (krok) ? QString("Stav po %1. kroku").arg( krok) : "Počáteční stav");

    ui->cesty->clear();
    for (auto ind = individuals.begin(); ind != individuals.end(); ind++) {
        QString c = QString("%1  [").arg( -ind->fitness, 4);
        bool first = true;
        for (auto i=ind->path.begin(); i != ind->path.end(); ++i) {
            if (!first) c.append(" - ");
            c.append( matrix->getTargetName(*i));
            first = false;
        }
        c.append( QString(" - %1]").arg( matrix->getTargetName( ind->path[0])));
        ui->cesty->addItem(c);
    }

    QGraphicsScene *scene = new QGraphicsScene( 0, 0, ui->tabWidget->width() - 6, ui->tabWidget->height() - 36);

    QPixmap *pixmap = new QPixmap( scene->width(), scene->height());
    pixmap->fill( Qt::white);
    QImage mapaImg;

    if (selectedMap >= 0) {
        // namaluje pouze vybranou mapu
        mapW = scene->width();
        mapH = scene->height();

        mapaImg = mapa.scaled( mapW, mapH);
        double pomerX = mapaImg.width() / (double) mapa.width();
        double pomerY = mapaImg.height() / (double) mapa.height();

        QPainter p( pixmap);

        p.drawImage( 0, 0, mapaImg);

        p.setPen( QPen( Qt::red, 5));
        TIndividual ind = individuals.at( selectedMap);

        int lastCity = 0;
        for (auto m = ind.path.begin(); m != ind.path.end(); m++) {
            p.drawLine( pomerX * (poziceMest[lastCity].x()),
                        pomerY * (poziceMest[lastCity].y()),
                        pomerX * (poziceMest[*m].x()),
                        pomerY * (poziceMest[*m].y()));
            lastCity = *m;
        }
        p.drawLine( pomerX * (poziceMest[lastCity].x()),
                    pomerY * (poziceMest[lastCity].y()),
                    pomerX * (poziceMest[0].x()),
                    pomerY * (poziceMest[0].y()));
        p.end();
    }
    else {
        // namaluje vsechny mapy
        mapW = scene->width() / 8;
        mapH = scene->height() / 5;

        mapaImg = mapa.scaled( mapW, mapH);
        double pomerX = mapaImg.width() / (double) mapa.width();
        double pomerY = mapaImg.height() / (double) mapa.height();

        QPainter p( pixmap);
        int x, y;

        p.setPen( QPen( Qt::lightGray));
        for (x=1; x<8; x++) {
            p.drawLine( x*mapW, 0, x*mapW, scene->height()-1);
        }
        for (y=1; y<5; y++) {
            p.drawLine( 0, y*mapH, scene->width()-1, y*mapH);
        }
        for (x=0; x<8; x++) {
            for (y=0; y<5; y++) {
                p.drawImage( x*mapW, y*mapH, mapaImg);
            }
        }

        int maxInd = qMin( (unsigned long) 40, individuals.size());
        int i;

        p.setPen( QPen( Qt::red));
        std::vector<TIndividual>::iterator ind = individuals.begin();
        for (i=0; (i<maxInd) && (ind != individuals.end()); i++, ind++) {
            int lastCity = 0;
            int offsetX = (i % 8) * mapW;
            int offsetY = (i / 8) * mapH;
            for (auto m = ind->path.begin(); m != ind->path.end(); m++) {
                p.drawLine( pomerX * (poziceMest[lastCity].x()) + offsetX,
                            pomerY * (poziceMest[lastCity].y()) + offsetY,
                            pomerX * (poziceMest[*m].x()) + offsetX,
                            pomerY * (poziceMest[*m].y()) + offsetY);
                lastCity = *m;
            }
            p.drawLine( pomerX * (poziceMest[lastCity].x()) + offsetX,
                        pomerY * (poziceMest[lastCity].y()) + offsetY,
                        pomerX * (poziceMest[0].x()) + offsetX,
                        pomerY * (poziceMest[0].y()) + offsetY);
        }
        p.end();
    }

    QGraphicsPixmapItem *pixmapItem = new QGraphicsPixmapItem;
    pixmapItem->setPixmap( *pixmap);

    scene->addItem( new QGraphicsPixmapItem( QPixmap::fromImage( mapaImg)));

    scene->addItem( pixmapItem);
    ui->graphicsView->setScene(scene);

}

void MainWindow::reset()
{
    salesmanProblemGeneticInit( matrix);
    krok = 0;
    showState();
}

void MainWindow::on_btnDalsi_clicked()
{
    salesmanProblemGeneticStep( matrix, metodaKrizeni);
    showState();
}
