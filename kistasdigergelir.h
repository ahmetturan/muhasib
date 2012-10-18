#ifndef KISTASDIGERGELIR_H
#define KISTASDIGERGELIR_H

#include <QDialog>
#include <QDate>
#include <QKeyEvent>
#include <QCloseEvent>
#include <QMessageBox>

namespace Ui {
class kistasdigergelir;
}

class kistasdigergelir : public QDialog
{
    Q_OBJECT
    
public:
    explicit kistasdigergelir(QWidget *parent = 0);
    ~kistasdigergelir();
    void ontanimliAyarlar();
    void ilkYukleme();
    bool getSecim();
    QDate getBaslangicTarih();
    QDate getBitisTarih();
    bool getTutarEtkinMi();
    bool getTarihEtkinMi();
    double getBaslangicTutar();
    double getBitisTutar();
    void keyPressEvent(QKeyEvent *e);
    void closeEvent(QCloseEvent *event);

public slots:
    void tutarEtkin();
    void tarihEtkin();
    void iptal();
    void tamam();

private:
    Ui::kistasdigergelir *ui;
    bool secim;//tamam mı yoksa iptale mi basıldı
    bool tutarEtkinMi;//tamama tıklanırken sonra tur cb'si tikli miydi
    bool tarihEtkinMi;//tamama tıklanırken sonra tarih cb'si tikli miydi
};

#endif // KISTASDIGERGELIR_H
