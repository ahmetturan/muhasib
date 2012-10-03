#ifndef EKLEDIGERGELIR_H
#define EKLEDIGERGELIR_H

#include <QDialog>
#include <QCalendarWidget>
#include <QDir>
#include <QComboBox>

namespace Ui {
class ekledigergelir;
}

class ekledigergelir : public QDialog
{
    Q_OBJECT
    
public:
    explicit ekledigergelir(QWidget *parent = 0);
    ~ekledigergelir();
    void ontanimliAyarlar();
    void ilkYukleme();
    
private:
    Ui::ekledigergelir *ui;
    QCalendarWidget *cal;
    QStringList listeDigerGelir;//tamam a tıklanınca girişleri ana ekrana göndermek için
    QStringList listeHesap;//hesap isimlerini cb ye eklemek için
    bool takvimAcik;
    double toplamTutar;
    int satir;
    int sutun;
    int dgSutunSil;
    int dgSutunTarih;
    int dgSutunIsim;
    int dgSutunKimden;
    int dgSutunTutar;
    int dgSutunAciklama;
    int dgSutunHesap;
};

#endif // EKLEDIGERGELIR_H
