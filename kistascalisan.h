#ifndef KISTASCALISAN_H
#define KISTASCALISAN_H

#include <QDialog>
#include <QDate>
#include <QCloseEvent>
#include <QMessageBox>

namespace Ui {
class kistascalisan;
}

class kistascalisan : public QDialog
{
    Q_OBJECT
    
public:
    explicit kistascalisan(QWidget *parent = 0);
    ~kistascalisan();
    void ilkYukleme();
    QDate getBaslangicTarih();
    QDate getBitisTarih();
    QStringList getKonumSecim();
    bool getSecim();
    bool getKonumEtkinMi();
    bool getTarihEtkinMi();
    bool getMaasEtkinMi();
    void ontanimliAyarlar();
    int getBaslangicMaas();
    int getBitisMaas();
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *e);

public slots:
    void tamam();
    void iptal();
    void konumEtkin();
    void tarihEtkin();
    void maasEtkin();
    
private:
    Ui::kistascalisan *ui;
    bool secim;//tamam mı yoksa iptale mi basıldı
    bool konumEtkinMi;//tamama tıklanırken sonra tur cb'si tikli miydi
    bool tarihEtkinMi;//tamama tıklanırken sonra tarih cb'si tikli miydi
    bool maasEtkinMi;//tamama tıklanırken sonra maas cb'si tikli miydi
};

#endif // KISTASCALISAN_H
