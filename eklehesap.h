#ifndef HESAPEKLE_H
#define HESAPEKLE_H

#include <QDialog>
#include <QComboBox>
#include <QDebug>
#include <QDir>

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
    void ontanimliAyarlar();
    QStringList getListeHesap();
    QStringList getListeCbHesapTur();

public slots:
    void tamam();
    void satirSil();
    void satirEkle(int, int);
    
private:
    Ui::hesapekle *ui;
    QStringList listeHesaplar;
    QStringList listeCbHesapTur;
    int hspSutunSil;
    int hspSutunIsim;
    int hspSutunBaslangicMeblagi;
    int hspSutunTur;
};

#endif // HESAPEKLE_H
