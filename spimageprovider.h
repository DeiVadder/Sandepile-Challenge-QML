#ifndef SPIMAGEPROVIDER_H
#define SPIMAGEPROVIDER_H

#include <QObject>
#include <QImage>
#include <QQuickImageProvider>

class SpImageProvider : public QObject, public QQuickImageProvider
{
    Q_OBJECT
public:
    SpImageProvider(QObject *parent = nullptr);

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;

public slots:
    void updateImage(const QImage &image);

signals:
    void imageChanged();

private:
    QImage image;
};

#endif // SPIMAGEPROVIDER_H
