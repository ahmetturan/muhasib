#ifndef CEKEKLE_H
#define CEKEKLE_H

#include <QDialog>
#include <QCalendarWidget>
#include <QDir>
#include <QComboBox>

namespace Ui {
class cekekle;
}

class cekekle : public QDialog
{
    Q_OBJECT
    
public:
    explicit cekekle(QWidget *parent = 0);
    ~cekekle();
    QStringList getListeCek();
    void ontanimliAyarlar();
    void ilkYukleme();
    void takvimAcikIseKapat();
    double getToplamTutar();
    QStringList getListeCbCekTur();

public slots:
    void tamam();
    void kapat();
    void satirSil();
    void satirEkle(int,int);
    void takvimiAc(int,int);
    void tarihiAl();
    void hucreyeTiklandi(int,int);
    
private:
    Ui::cekekle *ui;
    QStringList listeCek;//tamam a tıklanınca girişleri ana ekrana göndermek için
    QStringList listeCbCekTur;
    QCalendarWidget *cal;
    bool takvimAcik;
    double toplamTutar;
    int sutunSil;
    int sutunTarih;
    int sutunIsim;
    int sutunBanka;
    int sutunTutar;
    int sutunMuhatap;
    int sutunCekNo;
    int sutunAciklama;
    int sutunTur;
    int satir;
    int sutun;
};

#endif // CEKEKLE_H
