#ifndef KISTASMAAS_H
#define KISTASMAAS_H

#include <QDialog>
#include <QDate>
#include <QCloseEvent>
#include <QMessageBox>

namespace Ui {
class kistasmaas;
}

class kistasmaas : public QDialog
{
    Q_OBJECT
    
public:
    explicit kistasmaas(QWidget *parent = 0);
    ~kistasmaas();
    void ilkYukleme();
    QDate getBaslangicTarih();
    QDate getBitisTarih();
    QStringList getTurSecim();
    bool getSecim();
    bool getTurEtkinMi();
    bool getTarihEtkinMi();
    void ontanimliAyarlar();
    void closeEvent(QCloseEvent *event);

public slots:
    void tamam();
    void iptal();
    void turEtkin();
    void tarihEtkin();

private:
    Ui::kistasmaas *ui;
    bool secim;//tamam mı yoksa iptale mi basıldı
    bool turEtkinMi;//tamama tıklanırken sonra tur cb'si tikli miydi
    bool tarihEtkinMi;//tamama tıklanırken sonra tarih cb'si tikli miydi
};

#endif // KISTASMAAS_H
