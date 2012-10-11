#ifndef KISTASFATURA_H
#define KISTASFATURA_H

#include <QDialog>
#include <QDate>
#include <QCloseEvent>
#include <QMessageBox>

namespace Ui {
class kistasfatura;
}

class kistasfatura : public QDialog
{
    Q_OBJECT
    
public:
    explicit kistasfatura(QWidget *parent = 0);
    ~kistasfatura();
    void ilkYukleme();
    void ontanimliAyarlar();
    bool getTurEtkinMi();
    bool getTarihEtkinMi();
    QDate getBaslangicTarih();
    QDate getBitisTarih();
    int getTurSecim();
    bool getSecim();
    void closeEvent(QCloseEvent *event);

public slots:
    void tamam();
    void iptal();
    void turEtkin();
    void tarihEtkin();
    
private:
    Ui::kistasfatura *ui;
    bool secim;//tamam mı yoksa iptale mi basıldı
    bool turEtkinMi;//tamama tıklanırken sonra tur cb'si tikli miydi
    bool tarihEtkinMi;//tamama tıklanırken sonra tarih cb'si tikli miydi
};

#endif // KISTASFATURA_H
