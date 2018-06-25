#ifndef SANDPILEMODEL_H
#define SANDPILEMODEL_H

#include <QObject>
#include <QTimer>
#include <QVector>
#include <QVariant>
#include <QImage>
#include <QFuture>


class SandpileModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint64 grainCount READ grainCount NOTIFY newImage)
    Q_PROPERTY(bool busy READ busy WRITE setBusy NOTIFY busyChanged)

public:
    explicit SandpileModel(QObject *parent = nullptr);
    ~SandpileModel();

    quint64 grainCount(){return m_GrainCount;}
    QImage img(){return m_Image;}

    Q_INVOKABLE void cancelRun();
    Q_INVOKABLE QColor getColor(const int index){return QColor(*colors.at(index));}

    bool &busy(){return m_busy;}
    void setBusy(const bool &b){
        if( b!= m_busy){
            m_busy = b;
            emit busyChanged();
        }
    }

private slots:
    void addGrainAt(uint &x, uint &y);
    void updateGrid();

signals:
    void newImage(const QImage &);
    void busyChanged();

    void forceClose();

private:
    bool atBorder = false;
    bool m_busy = true;
    bool m_cancelRun = false;

    uchar *m_Grains, *m_GrainsCopy;

    uint colStart, rowStart, cols, rows, index1D, arraySize;
    quint64 m_GrainCount;

    QTimer tUpdate;

    QImage m_Image;

    QVector<const QRgb*> colors;
};

#endif // SANDPILEMODEL_H
