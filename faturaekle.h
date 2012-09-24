#ifndef FATURAEKLE_H
#define FATURAEKLE_H

#include <QDebug>
#include <QDialog>
#include <QCalendarWidget>
#include <QTextCodec>
#include <QComboBox>
#include <QDir>

namespace Ui {
class faturaEkle;
}

class faturaEkle : public QDialog
{
    Q_OBJECT
    
public:
    explicit faturaEkle(QWidget *parent = 0);
    ~faturaEkle();
    void ilkYukleme();
    void takvimAcikIseKapat();
    void ontanimliAyarlar();
    QStringList getListeFatura();
    double getToplamTutar();
    QStringList getListeCbFaturaTur();
    void setListeHesap(QStringList);

public slots:
    void kapat();
    void satirEkle(int, int);
    void satirSil();
    void takvimiAc(int,int);
    void tarihiAl();
    void hucreyeTiklandi(int, int);
    void tamam();
    
private:
    Ui::faturaEkle *ui;
    QCalendarWidget *cal;
    QStringList listeFatura;//tamam a tıklanınca girişleri ana ekrana göndermek için
    QStringList listeCbFaturaTur;
    QStringList listeHesap;//hesap isimlerini cb ye eklemek için
    bool takvimAcik;
    double toplamTutar;
    int satir;
    int sutun;
    int ftrSutunSil;
    int ftrSutunTarih;
    int ftrSutunIsim;
    int ftrSutunMatrah;
    int ftrSutunKdvOrani;
    int ftrSutunKdvTutari;
    int ftrSutunTutar;
    int ftrSutunAciklama;
    int ftrSutunTur;
    int ftrSutunHesap;
};

#endif // FATURAEKLE_H
