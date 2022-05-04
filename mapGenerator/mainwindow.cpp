#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "functions.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonGeneruj_clicked()
{
    mainMapGen(ui->spinRozmiar->value(), ui->spinTunele->value(),ui->spinPokoje->value(), ui->spinRozmiarPokoi->value());
}


void MainWindow::on_buttonImport_clicked()
{
    importMap(ui);
}

