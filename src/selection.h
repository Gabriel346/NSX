
#ifndef SELECTION_H
#define SELECTION_H

#include <QObject>
#include <QVariant>

extern int const MAX_SELECTION_ID;

enum SelectionType {
  NONE = 0,
  OBJECT = 1,
  VERTEX = 2,
  EDGE = 4,
  POLYGON = 8,
  TRIANGLE = 16,
  CORNER = 32
};

//enum SelectionMode {
//  PICK = 0,
//  RECTANGLE = 1,
//  VERTEX = 2,
//  EDGE = 4,
//  POLYGON = 8,
//  TRIANGLE = 16,
//  CORNER = 24
//};

class Selection : public QObject
{
    Q_OBJECT
public:
    explicit Selection(QObject *parent = nullptr);

    SelectionType selection_type = NONE;

    QVariant *component_mode_object;

    std::vector<QVariant> data;



signals:

public slots:
};


#endif // SELECTION_H
