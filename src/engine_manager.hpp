#ifndef ENGINEMANAGER_HPP
#define ENGINEMANAGER_HPP

#include <QObject>

class EngineManager : public QObject
{
    Q_OBJECT
public:
    explicit EngineManager(QObject *parent = nullptr);
private slots:
signals:

};

#endif // ENGINEMANAGER_HPP
