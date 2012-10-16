#ifndef HESAPEKLE_H
#define HESAPEKLE_H

#include <QDialog>
#include <QComboBox>
#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include <QCloseEvent>

namespace Ui {
class hesapekle;
}

class hesapekle : public QDialog
{
    Q_OBJECT
    
public:
    explicit hesapekle(QWidget *parent = 0);
    ~hesapekle();
    void ilkYukleme();
    void ontanimliAyarlar(QStringList mevcutHesaplar);
    QStringList getListeHesap();
    QStringList getListeCbHesapTur();
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *e);

public slots:
    void tamam();
    void kapat();
    void satirSil();
    void satirEkle(int, int);
    
private:
    Ui::hesapekle *ui;
    QStringList listeHesaplar;
    QStringList listeCbHesapTur;
    QStringList listeMevcutHesaplar;
    int hspSutunSil;
    int hspSutunIsim;
    int hspSutunBaslangicMeblagi;
    int hspSutunTur;
};

#endif // HESAPEKLE_H
