#include "sandpilemodel.h"

#include <QtConcurrent>

//QRgb = 0xAARRGGBB
const QRgb color1 = QRgb(0xFF000000);
const QRgb color2 = QRgb(0xFF6666FF);
const QRgb color3 = QRgb(0xFF4747D1);
const QRgb color4 = QRgb(0xFFE68A00);

SandpileModel::SandpileModel(QObject *parent) : QObject(parent)
{
    //initialisation of variables and arrays
    cols = 500;
    rows = 500;

    m_GrainCount = 0;

    colors.append(&color1);
    colors.append(&color2);
    colors.append(&color3);
    colors.append(&color4);

    m_Image = QImage(cols,rows, QImage::Format_RGB32);

    arraySize = cols*rows;
    m_Grains = new uchar[arraySize];
    m_GrainsCopy = new uchar[arraySize];

    for(uint i(0); i < rows*cols; i++){
        m_Grains[i] = 0;
        m_GrainsCopy[i] = 0;
    }

    colStart = cols/2;
    rowStart = rows/2;

    //Qt Concurrent parallelization, to see QThread&Worker approach, see QWidget sandpile example
    QtConcurrent::run([=]{
        while(!atBorder && m_busy){
            m_GrainCount++;

            addGrainAt(colStart,rowStart);

            //To prevent unwanted interim states in the ui
            memcpy(m_GrainsCopy, m_Grains, arraySize);
        }

        setBusy(false);
        if(m_cancelRun)
            QMetaObject::invokeMethod(qApp, &QCoreApplication::quit,Qt::QueuedConnection);
    });

    //Update ui every 50ms -> 20Hz refreshrate
    connect(&tUpdate, &QTimer::timeout, this, &SandpileModel::updateGrid);
    tUpdate.start(50);
}

SandpileModel::~SandpileModel()
{
    delete [] m_Grains;
    delete [] m_GrainsCopy;
}

void SandpileModel::cancelRun()
{
    //To exit QtConcurrent before destruction
    tUpdate.stop();
    m_cancelRun = true;
    setBusy(false);
}

//void SandpileModel::addGrainAt(uint &x, uint &y)
void SandpileModel::addGrainAt(uint &x, uint &y)
{
    if(!m_busy)
        return;
    if(x < cols && y < rows){
        index1D = cols * y + x;
        m_Grains[index1D]++;

        if(m_Grains[index1D] > 3){
            //pile topples
            m_Grains[index1D] = 0;

            addGrainAt(x, --y);
            addGrainAt(++x, ++y);
            addGrainAt(--x, ++y);
            addGrainAt(--x, --y);
            x++;
        }
    }else
        atBorder = true;
}

void SandpileModel::updateGrid()
{
    for(uint i(0); i < arraySize; i++ ){
        memcpy(m_Image.bits() + (i*4), colors.at(m_GrainsCopy[i]), 4);
    }
    emit newImage(m_Image);
}
